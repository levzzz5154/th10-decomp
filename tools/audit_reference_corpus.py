#!/usr/bin/env python3
"""Index real reference availability; missing exports are never semantic passes."""
import argparse
import collections
import csv
import hashlib
import json
import re
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
OUT = ROOT / 'decompiled/reference_coverage'


def sha(data):
    return hashlib.sha256(data).hexdigest()


def seeds():
    c = (ROOT / 'ida/th10.exe.c').read_text()
    asm = (ROOT / 'ida/th10.exe.asm').read_text()
    addresses = set(re.findall(r'^//----- \(([0-9A-F]{8})\)', c, re.M))
    addresses.update(x.zfill(8) for x in re.findall(r'^sub_([0-9A-F]+)\s+proc\s', asm, re.M))
    addresses.update(x.zfill(8) for x in re.findall(r'\bsub_([0-9A-F]+)\b', c.split('//----- (')[0]))
    addresses.update(x.zfill(8) for x in re.findall(r'COLLAPSED FUNCTION sub_([0-9A-F]+)\.', asm))
    return sorted(addresses)


def tsv(path):
    return list(csv.DictReader(path.read_text().splitlines(), delimiter='\t'))


def reconstruction_addresses():
    inventory = json.loads((ROOT / 'matching2/docs/audit/inventory.json').read_text())
    return {row['address'].removeprefix('0x').upper() for row in inventory['functions']}


def verify_bytes(base, rows):
    memory = {}
    for line in (base / 'memory.hex').read_text().splitlines():
        address, encoded = line.split()
        start = int(address, 16)
        for offset, value in enumerate(bytes.fromhex(encoded)):
            if start + offset in memory: raise ValueError('overlapping memory export')
            memory[start + offset] = value
    verification = json.loads((ROOT / 'decompiled/reference_bytes_validation.json').read_text())
    block = next(row for row in tsv(base / 'memory_blocks.tsv') if row['name'] == '.text')
    raw = bytes(memory[int(block['start'], 16) + offset] for offset in range(int(block['size'])))
    if sha(raw) != verification['text_section_sha256'] or len(raw) != verification['text_section_bytes']:
        raise ValueError('exported .text differs from recorded executable comparison')
    program = {r['key']: r['value'] for r in tsv(base / 'program.tsv')}
    if program['sha256'] != verification['executable_sha256']: raise ValueError('wrong executable provenance')
    for row in rows:
        ranges = [(int(a, 16), int(b, 16)) for a,b in (pair.split('-') for pair in row['body_ranges'].split(','))]
        if sum(b-a+1 for a,b in ranges) != int(row['body_bytes']): raise ValueError('body range size mismatch')
        for line in (base / row['asm_file']).read_text().splitlines():
            if line.startswith(';') or not line: continue
            address, encoded, instruction = line.split('\t', 2)
            start = int(address, 16)
            data = bytes.fromhex(encoded.removesuffix('...'))
            if not any(a <= start <= b for a,b in ranges): raise ValueError('listing outside function body')
            if data != bytes(memory[start + offset] for offset in range(len(data))):
                raise ValueError('function listing bytes differ from memory: ' + address)


def generate():
    c_lines = (ROOT / 'ida/th10.exe.c').read_text().splitlines()
    asm_lines = (ROOT / 'ida/th10.exe.asm').read_text().splitlines()
    sections = [(i, re.match(r'//----- \(([0-9A-F]{8})\)', line).group(1))
                for i, line in enumerate(c_lines) if re.match(r'//----- \(([0-9A-F]{8})\)', line)]
    c_rows, name_addresses = {}, collections.defaultdict(set)
    for index, (start, address) in enumerate(sections):
        end = sections[index + 1][0] if index + 1 < len(sections) else len(c_lines)
        signature = next((line for line in c_lines[start+1:end] if line.strip() and not line.startswith('//')), '')
        match = re.search(r'([\w?$]+)(?:@<[^>]+>)?\s*\(', signature)
        name = match.group(1) if match else ''
        if name: name_addresses[name].add(address)
        c_rows[address] = {'path': 'ida/th10.exe.c', 'first_line': start + 1,
                           'last_line': end, 'signature': signature, 'name': name}
    ida_functions = []
    for line_number, line in enumerate(asm_lines, 1):
        proc = re.match(r'^(\S+)\s+proc\s', line)
        collapsed = re.search(r'\[([0-9A-F]+) BYTES: COLLAPSED FUNCTION (.*?)\. PRESS', line)
        if not proc and not collapsed: continue
        name = proc.group(1) if proc else collapsed.group(2)
        explicit = re.fullmatch(r'sub_([0-9A-Fa-f]+)', name)
        addresses = {explicit.group(1).upper().zfill(8)} if explicit else name_addresses.get(name, set())
        basis = 'explicit_name' if explicit else 'unique_c_signature'
        if not addresses and re.fullmatch(r'_\w+@\d+', name):
            addresses = name_addresses.get(re.sub(r'@\d+$', '', name[1:]), set())
            basis = 'unique_c_signature_stdcall_decoration_removed'
        end = line_number
        if proc:
            while end < len(asm_lines) and not re.match(re.escape(name) + r'\s+endp\b', asm_lines[end-1]): end += 1
            if end == len(asm_lines) and not re.match(re.escape(name) + r'\s+endp\b', asm_lines[end-1]):
                raise ValueError('unclosed IDA procedure: ' + name)
        ida_functions.append({'name': name, 'address': next(iter(addresses)) if len(addresses) == 1 else None,
                              'address_basis': basis if len(addresses) == 1 else 'unresolved',
                              'status': 'body' if proc else 'collapsed', 'path': 'ida/th10.exe.asm',
                              'first_line': line_number, 'last_line': end,
                              'collapsed_bytes': int(collapsed.group(1), 16) if collapsed else None})
    corpora, files = {}, {}
    for corpus in ('ghidra_full', 'ghidra_augmented'):
        base = ROOT / 'decompiled' / corpus
        rows = tsv(base / 'index.tsv')
        if len({r['address'] for r in rows}) != len(rows): raise ValueError('duplicate Ghidra address')
        verify_bytes(base, rows)
        for row in rows:
            for key in ('c_file', 'asm_file'):
                path = base / row[key]
                if not path.is_file() or not path.stat().st_size: raise ValueError('missing ' + str(path))
                row[key] = path.relative_to(ROOT).as_posix()
            if row['status'] == 'ok' and 'DECOMPILATION FAILED:' in (ROOT / row['c_file']).read_text():
                raise ValueError('failure falsely marked ok')
        corpora[corpus] = {row['address']: row for row in rows}
        for path in sorted(base.rglob('*')):
            if path.is_file(): files[path.relative_to(ROOT).as_posix()] = path.read_bytes()
    for path in sorted((ROOT / 'ida').glob('*')):
        if path.is_file(): files[path.relative_to(ROOT).as_posix()] = path.read_bytes()
    for relative in ('ghidra/ExportFullAudit.java', 'ghidra/PrepareFullAudit.java', 'tools/export_full_audit.sh',
                     'tools/audit_reference_corpus.py', 'decompiled/ida_archive_provenance.json',
                     'decompiled/reference_bytes_validation.json',
                     'matching2/docs/audit/inventory.json'):
        files[relative] = (ROOT / relative).read_bytes()
    tracked = reconstruction_addresses()
    addresses = sorted(set(c_rows) | set(seeds()) | set(corpora['ghidra_full']) | set(corpora['ghidra_augmented']) | tracked)
    by_address = collections.defaultdict(list)
    for row in ida_functions:
        if row['address']: by_address[row['address']].append(row)
    coverage = []
    for address in addresses:
        coverage.append({'address': address, 'reconstruction_inventory': address in tracked,
                         'ida_c': c_rows.get(address), 'ida_asm': by_address.get(address, []),
                         'ghidra_saved': corpora['ghidra_full'].get(address),
                         'ghidra_augmented': corpora['ghidra_augmented'].get(address)})
    summary = {'address_union': len(addresses), 'reconstruction_inventory': len(tracked),
               'ida_c_bodies': len(c_rows), 'ida_asm_bodies': sum(r['status'] == 'body' for r in ida_functions),
               'ida_asm_collapsed': sum(r['status'] == 'collapsed' for r in ida_functions),
               'ida_asm_unresolved_addresses': sum(r['address'] is None for r in ida_functions),
               'ghidra_saved_functions': len(corpora['ghidra_full']),
               'ghidra_augmented_functions': len(corpora['ghidra_augmented']),
               'ghidra_decompile_failures': sum(r['status'] != 'ok' for corpus in corpora.values() for r in corpus.values()),
               'ida_c_without_augmented_ghidra': len(set(c_rows) - set(corpora['ghidra_augmented'])),
               'tracked_without_augmented_ghidra': sorted(tracked - set(corpora['ghidra_augmented']))}
    manifest = {'schema_version': 1, 'summary': summary,
                'limitations': ['Not a proof of complete function discovery or semantic correctness.',
                    'IDA assembly omits collapsed bodies; unresolved named rows are retained separately.',
                    'Saved and augmented Ghidra analyses are distinct evidence; augmentation uses IDA starts and reconstruction address claims, not independent boundary discovery.',
                    'Imported external functions have signatures, not local bodies. memory.hex is loaded analysis memory, including synthetic/zero-filled regions.',
                    'Historical 703-function ghidra_raw and reconstruction inventory remain unchanged.'],
                'inputs': [{'path': p, 'bytes': len(b), 'sha256': sha(b)} for p,b in sorted(files.items())],
                'addresses': coverage, 'ida_assembly_functions': ida_functions}
    md = ['# Reference corpus coverage', '', 'This indexes available evidence; **complete IDA output for every function is unavailable**.', '',
          '| Measure | Count |', '| --- | --- |']
    md += [f'| {key} | {value} |' for key,value in summary.items()]
    md += ['', 'The original IDA export reports `nfuncs=1906 queued=1224 decompiled=1224`.',
           'Its 1,237 procedure bodies plus 669 collapsed entries account for those 1,906 entries.',
           'A fresh expanded IDA listing and complete Hex-Rays export require the original IDA database/tool.',
           'Ghidra supplements missing evidence but does not become IDA evidence.', '',
           'See [index.json](index.json) for all address rows, hashes, exact IDA line ranges, and unresolved named assembly entries.', '',
           '## Address navigation', '', '| Address | IDA C | IDA assembly | Saved Ghidra C / ASM | Augmented Ghidra C / ASM |', '| --- | --- | --- | --- | --- |']
    def link(path, label, line=None): return f'[{label}](../../{path}' + (f'#L{line}' if line else '') + ')'
    for row in coverage:
        c = row['ida_c']; assembly = row['ida_asm']; saved = row['ghidra_saved']; augmented = row['ghidra_augmented']
        gh = lambda r: (link(r['c_file'], 'C') + ' / ' + link(r['asm_file'], 'ASM')) if r else 'missing exact start'
        md.append('| ' + row['address'] + ' | ' + (link(c['path'], 'C', c['first_line']) if c else 'missing') + ' | '
                  + (', '.join(link(r['path'], r['status'], r['first_line']) for r in assembly) or 'unmapped')
                  + ' | ' + gh(saved) + ' | ' + gh(augmented) + ' |')
    return {'index.json': json.dumps(manifest, indent=2) + '\n', 'README.md': '\n'.join(md) + '\n'}


if __name__ == '__main__':
    parser = argparse.ArgumentParser(description=__doc__)
    action = parser.add_mutually_exclusive_group(required=True)
    action.add_argument('--seeds', type=Path)
    action.add_argument('--reconstruction-seeds', type=Path)
    action.add_argument('--write', action='store_true')
    action.add_argument('--check', action='store_true')
    args = parser.parse_args()
    if args.seeds:
        args.seeds.write_text('\n'.join(seeds()) + '\n')
    elif args.reconstruction_seeds:
        args.reconstruction_seeds.write_text('\n'.join(sorted(reconstruction_addresses())) + '\n')
    else:
        rendered = generate()
        if args.write:
            OUT.mkdir(parents=True, exist_ok=True)
            for name, text in rendered.items(): (OUT / name).write_text(text)
        else:
            for name, text in rendered.items():
                if (OUT / name).read_text() != text: raise SystemExit('stale reference index: ' + name)
        print('REFERENCE_CORPUS_INTEGRITY_PASS (availability; not complete IDA coverage or semantic equivalence)')
