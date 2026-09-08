#!/usr/bin/env python3
"""One-time conversion of the accepted assembly sources into structured C++ files.

This reads versioned assembly and analysis metadata, never the retail executable.
Normal builds compile the resulting .cpp files directly; they do not regenerate.
"""
import argparse
from collections import Counter, defaultdict
import hashlib
import json
from pathlib import Path
import re
import shutil
from msvc_instruction import inline_instruction

ROOT = Path(__file__).resolve().parents[2]
BASE = ROOT / 'matching2/asm/text'
PROJECT = ROOT / 'matching2/msvc'
SEMANTIC = ROOT / 'matching2/data/recovered_semantic_cpp'
SEMANTIC_MODULES = {
    'entity.cpp': 'src/game/entity.cpp', 'bullet.cpp': 'src/game/bullet.cpp',
    'heap.cpp': 'src/util/heap.cpp', 'file.cpp': 'src/platform/file.cpp',
    'memory_file.cpp': 'src/platform/memory_file.cpp',
    'resource_file.cpp': 'src/platform/resource_file.cpp',
    'runtime_pool.cpp': 'src/util/runtime_pool.cpp',
    'frame_counter.cpp': 'src/game/frame_counter.cpp',
    'angle.cpp': 'src/math/angle.cpp',
    'recovery_leaves.cpp': 'src/game/recovery_leaves.cpp',
    'sound_float_forward.cpp': 'src/platform/sound_float_forward.cpp',
    'process.cpp': 'src/platform/process.cpp',
    'sound_leaves.cpp': 'src/platform/sound_leaves.cpp',
}
START, END = 0x401000, 0x465c00


def source_rows():
    manifest = json.loads((BASE / 'manifest.json').read_text())
    for name, digest in manifest['source_sha256'].items():
        if hashlib.sha256((BASE / name).read_bytes()).hexdigest() != digest:
            raise ValueError('baseline source hash mismatch: ' + name)
    result = []
    address = START
    for path in sorted((BASE / 'chunks').glob('*.s')):
        lines = path.read_text().splitlines()
        kind, evidence = None, ''
        i = 0
        while i < len(lines):
            line = lines[i]
            match = re.fullmatch(r'\.globl _th10_([0-9a-f]{8})', line)
            if match:
                if int(match[1], 16) != address:
                    raise ValueError('baseline partition drift')
                last = i + 2
                if lines[last].strip() == 'fwait':
                    last += 1
                raw = bytes.fromhex(lines[last].split('  # ')[-1])
                result.append({'address': address, 'raw': raw, 'kind': 'asm'})
                address += len(raw)
                i = last + 1
                continue
            match = re.match(r'# (data|padding) ', line)
            if match:
                kind, evidence = match[1], line[2:]
            if line.startswith('.fill '):
                count, width, value = [int(part, 0) for part in line[6:].split(',')]
                if width != 1:
                    raise ValueError('unsupported data width')
                raw = bytes([value]) * count
            elif line.startswith('.byte '):
                raw = bytes(int(part, 0) for part in line[6:].split(','))
            else:
                i += 1
                continue
            if kind is None:
                raise ValueError('data directive without classification')
            result.append({'address': address, 'raw': raw, 'kind': kind, 'evidence': evidence})
            address += len(raw)
            i += 1
    if address != END or hashlib.sha256(b''.join(row['raw'] for row in result)).hexdigest() != manifest['text_sha256']:
        raise ValueError('source bytes do not partition the accepted .text')
    return result, manifest


def clean_name(name):
    name = name.replace('Overlay', '')
    return re.sub(r'[^A-Za-z0-9_]+', '_', name).strip('_')[:90] or 'sub'


def generate(ownership_path, output):
    rows, baseline = source_rows()
    ownership = json.loads(ownership_path.read_text())
    known_starts = {row['address'] for row in rows if row['kind'] == 'asm'}
    entries = {int(entry['address'], 0): entry for entry in ownership['entries']
               if int(entry['address'], 0) in known_starts}
    owners = [None] * (END - START)
    for address, entry in entries.items():
        for span in entry['body_ranges']:
            left, right = int(span['start'], 0), int(span['end'], 0) + 1
            for offset in range(max(left, START) - START, min(right, END) - START):
                if owners[offset] is not None and owners[offset] != address:
                    raise ValueError('overlapping ownership claims')
                owners[offset] = address
    semantic = json.loads((SEMANTIC / 'regions.json').read_text())
    semantic_regions = [{**region, 'source': SEMANTIC_MODULES[Path(region['source']).name], 'kind': 'semantic'}
                        for region in semantic['regions']]
    semantic_regions.append({'name': 'FrameCounterPair_AtInterval',
        'source': 'src/game/frame_counter.cpp', 'symbol': '?AtInterval@FrameCounterPair@@QAEHH@Z',
        'address': '0x00427C70', 'size': 29, 'kind': 'semantic', 'relocations': []})
    semantic_by_address = {int(region['address'], 0): region for region in semantic_regions}
    semantic_owners = {}
    for address, region in semantic_by_address.items():
        for offset in range(address, address + region['size']):
            if offset in semantic_owners:
                raise ValueError('overlapping semantic bodies')
            semantic_owners[offset] = address
    blocks = []
    for row in rows:
        address, size = row['address'], len(row['raw'])
        sem = semantic_owners.get(address)
        if any(semantic_owners.get(offset) != sem for offset in range(address, address + size)):
            raise ValueError('semantic extent crosses an instruction or data directive')
        owner = owners[address - START] if row['kind'] == 'asm' else None
        key = ('semantic', sem) if sem is not None else (row['kind'], owner)
        if not blocks or blocks[-1]['key'] != key:
            blocks.append({'address': address, 'key': key, 'rows': []})
        blocks[-1]['rows'].append(row)
    # An unassigned run is a physical code fragment, not a newly discovered function.
    for block in blocks:
        block['size'] = sum(len(row['raw']) for row in block['rows'])
        kind, owner = block['key']
        entry = entries.get(owner)
        address = block['address']
        if kind == 'asm':
            name = clean_name(entry['name']) if entry else 'unassigned'
            part = '_part' if owner is not None and owner != address else ''
            block['name'] = f'asm_{name}{part}_{address:08x}'
            path = entry.get('preferred_module_path') if entry else None
            block['source'] = path or f'src/unidentified/{name}_{(owner or address):08x}.cpp'
    body_names = {block['address']: block['name'] for block in blocks if block['key'][0] == 'asm'}
    def target_name(address):
        if address in body_names:
            return body_names[address]
        entry = entries.get(address)
        return f'asm_{clean_name(entry["name"]) if entry else "target"}_{address:08x}'
    contents = defaultdict(list)
    bindings, helper_counts, regions = {}, Counter(), []
    data_index = 0
    for block in blocks:
        kind, owner = block['key']
        address, size = block['address'], block['size']
        if kind == 'semantic':
            region = semantic_by_address[owner]
            if address != owner or size != region['size']:
                raise ValueError('semantic body extent is not one complete block')
            regions.append(region)
            continue
        if kind in ('data', 'padding'):
            name = f'text_{kind}_{address:08x}'
            source = f'src/data/text_{address >> 16:04x}.cpp'
            raw = b''.join(row['raw'] for row in block['rows'])
            lines = [f'// {kind}: 0x{address:08X}..0x{address + size - 1:08X}',
                     '// ' + block['rows'][0].get('evidence', ''),
                     f'#pragma data_seg(".d{data_index:06d}")',
                     f'extern "C" unsigned char {name}[] = {{']
            for offset in range(0, len(raw), 16):
                lines.append('    ' + ', '.join(f'0x{value:02x}' for value in raw[offset:offset + 16]) + ',')
            lines += ['};', '#pragma data_seg()', '']
            contents[source].extend(lines)
            data_index += 1
            regions.append({'name': name, 'source': source, 'symbol': '_' + name,
                            'address': f'0x{address:08X}', 'size': size, 'kind': kind})
            continue
        name, source = block['name'], block['source']
        entry = entries.get(owner)
        local = {row['address'] for row in block['rows']}
        lines = [f'// 0x{address:08X}..0x{address + size - 1:08X}: ' +
                 (entry['name'] if entry else 'unassigned code fragment'),
                 '// Naked body preserves the retail register/stack ABI.',
                 f'extern "C" __declspec(naked) void __cdecl {name}() {{', '    __asm {']
        for row in block['rows']:
            assembly, refs, helpers = inline_instruction(row['address'], row['raw'], local, target_name)
            bindings.update(refs)
            helper_counts.update(helpers)
            lines.append(f'    L_{row["address"]:08x}:')
            lines.extend('        ' + text for text in assembly)
        lines += ['    }', '}', '']
        contents[source].extend(lines)
        regions.append({'name': name, 'source': source, 'symbol': '_' + name,
                        'address': f'0x{address:08X}', 'size': size, 'kind': 'asm',
                        'owner': f'0x{owner:08X}' if owner is not None else None})
    for template, source in SEMANTIC_MODULES.items():
        contents[source].extend(['// Recovered semantic C++ definitions.',
                                 (SEMANTIC / 'src' / template).read_text()])
    shutil.copytree(SEMANTIC / 'include', output / 'include', dirs_exist_ok=True)
    for source, lines in sorted(contents.items()):
        path = output / source
        path.parent.mkdir(parents=True, exist_ok=True)
        includes = '#include "asm_encoding.hpp"\n#include "asm_symbols.hpp"\n\n' if '/data/' not in source else ''
        path.write_text(includes + '\n'.join(lines))
    declarations = ['#pragma once', '// Fixed retail anchors; the linker verifies every placed function.']
    for name, address in sorted(bindings.items()):
        if name.startswith('asm_'):
            declarations += [f'extern "C" void __cdecl {name}();', f'#define VA_{name} 0x{address:08x}']
        else:
            declarations.append(f'extern "C" unsigned char {name};')
    (output / 'include/asm_symbols.hpp').write_text('\n'.join(declarations) + '\n')
    # Keep relocation bindings from the historical C++ recovery explicit. No
    # original operand bytes are used to manufacture linked instruction bytes.
    semantic_bindings = {}
    for region in semantic_regions:
        for relocation in region.get('relocations', []):
            name, address = relocation['symbol'], int(relocation['original_target'], 0)
            if name in semantic_bindings and semantic_bindings[name] != address:
                raise ValueError('inconsistent semantic symbol targets: ' + name)
            semantic_bindings[name] = address
    manifest = {'schema_version': 2, 'compiler_version': '13.10.6030',
        'flags': semantic['flags'], 'text_start': f'0x{START:08X}', 'text_bytes': END - START,
        'text_sha256': baseline['text_sha256'], 'retail_sha256': baseline['retail_sha256'],
        'dos_regions': [{'name': 'dos_stub_code', 'symbol': '_dos_stub_code', 'address': '0x0', 'size': 14, 'source': 'src/platform/dos_stub.cpp'}, {'name': 'dos_stub_message', 'symbol': '_dos_stub_message', 'address': '0xe', 'size': 50, 'source': 'src/platform/dos_stub.cpp'}],
        'regions': regions, 'symbols': {**{'_' + name: f'0x{address:08X}' for name, address in bindings.items()},
                                     **{name: f'0x{address:08X}' for name, address in semantic_bindings.items()}},
        'translation_units': sorted({region['source'] for region in regions}),
        'summary': {'regions_by_kind': dict(Counter(region['kind'] for region in regions)),
                    'bytes_by_kind': {kind: sum(region['size'] for region in regions if region['kind'] == kind)
                                      for kind in ('semantic', 'asm', 'data', 'padding')},
                    'encoding_helpers': dict(helper_counts)},
        'provenance': {'assembly_manifest_sha256': hashlib.sha256((BASE / 'manifest.json').read_bytes()).hexdigest(),
                       'ownership_sha256': hashlib.sha256(ownership_path.read_bytes()).hexdigest()},
        'notes': ['Every executable body is compiled from C++; unported bodies use MSVC inline assembly.',
                  'Unidentified bodies are physical code fragments, not inferred source-level functions.',
                  'Normal builds do not read the retail executable, disassembly, or source generator.']}
    layout = output / 'layout'
    layout.mkdir(exist_ok=True)
    shutil.copyfile(ownership_path, layout / 'function_ownership.json')
    (output / 'regions.json').write_text(json.dumps(manifest, indent=2) + '\n')
    print(json.dumps(manifest['summary'], indent=2))


if __name__ == '__main__':
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--ownership', type=Path, default=ROOT / 'matching2/build/msvc/function_ownership.json')
    parser.add_argument('--output', type=Path, default=PROJECT)
    parser.add_argument('--replace', action='store_true', help='explicitly overwrite existing generated sources')
    args = parser.parse_args()
    if (args.output / 'regions.json').exists() and not args.replace:
        parser.error('project already exists; --replace is required to overwrite edited C++ sources')
    generate(args.ownership, args.output)
