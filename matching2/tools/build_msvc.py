#!/usr/bin/env python3
"""Compile the complete C++ project and require an exact independently linked PE."""
import argparse
from collections import Counter, defaultdict
from concurrent.futures import ThreadPoolExecutor, as_completed
import json
import os
from pathlib import Path
import subprocess

from build_asm_proof import PEImage
from build_asm_text import run, sha
from coff_regions import normalize_object
from compare_obj import read_coff_function
from pack_asm_pe import build_image
from recover_matches import winpath

ROOT = Path(__file__).resolve().parents[2]
DEFAULT_PROJECT = ROOT / 'matching2/msvc'
DEFAULT_TOOLKIT = Path.home() / '.local/share/th10-toolchains/msvc-13.10.6030'


def validate_project(config, reference):
    if config.get('schema_version') != 2:
        raise ValueError('expected the complete schema-2 C++ project')
    if (config.get('text_sha256') != reference['text_section_sha256'] or
            config.get('text_bytes') != reference['text_section_bytes'] or
            config.get('retail_sha256') != reference['executable_sha256']):
        raise ValueError('project manifest does not identify the supported retail image')
    cursor, symbols = 0x401000, set()
    regions = sorted(config['regions'], key=lambda region: int(region['address'], 0))
    for region in regions:
        if int(region['address'], 0) != cursor or region['size'] <= 0:
            raise ValueError(f'project partition has a gap, overlap or invalid extent at {cursor:#x}')
        if region['symbol'] in symbols:
            raise ValueError('duplicate selected symbol: ' + region['symbol'])
        if region['kind'] not in ('semantic', 'asm', 'data', 'padding'):
            raise ValueError('unclassified C++ region')
        symbols.add(region['symbol'])
        cursor += region['size']
    if cursor != 0x465c00:
        raise ValueError('C++ project does not cover the complete .text section')
    units = sorted({region['source'] for region in regions})
    if units != sorted(config['translation_units']):
        raise ValueError('translation unit list disagrees with region ownership')
    return regions, units


def make_link_script(regions, selected, bindings, output):
    lines = ['SECTIONS', '{', '  .text 0x00401000 : SUBALIGN(1) {']
    for region in regions:
        address = int(region['address'], 0)
        item = selected[region['symbol']]
        lines += [f'    _slot_start_{address:x} = .;',
                  f'    KEEP("{item["object"]}"({item["section"]}))',
                  f'    _slot_end_{address:x} = .;']
    lines += ['  }', '  _port_text_start = ADDR(.text);']
    definitions = {region['symbol']: int(region['address'], 0) for region in regions}
    for region in regions:
        address = int(region['address'], 0)
        lines += [f'  ASSERT(_slot_start_{address:x} == {address:#x}, "wrong slot start: {region["name"]}")',
                  f'  ASSERT(_slot_end_{address:x} == {address + region["size"]:#x}, "wrong slot end: {region["name"]}")',
                  f'  ASSERT("{region["symbol"]}" == {address:#x}, "wrong symbol address: {region["name"]}")']
    for name, encoded_address in sorted(bindings.items()):
        address = int(encoded_address, 0)
        if name in definitions:
            if definitions[name] != address:
                raise ValueError('binding conflicts with selected C++ definition: ' + name)
            continue  # Let COFF relocations resolve to the actual compiled definition.
        if '"' in name or '\n' in name:
            raise ValueError('invalid symbol spelling')
        lines.append(f'  "{name}" = {address:#x};')
    lines += ['  ASSERT(SIZEOF(.text) == 412672, "wrong .text extent")', '}']
    output.write_text('\n'.join(lines) + '\n')


def verify_linked(path, config, oracle=None):
    linked = PEImage(path.read_bytes())
    sections = [section for section in linked.sections if section['name'] == '.text']
    if len(sections) != 1 or any(section['name'] != '.text' and section['raw_size'] for section in linked.sections):
        raise ValueError('unexpected output section in C++ link')
    section = sections[0]
    if (section['address'] != 0x401000 or section['virtual_size'] != config['text_bytes'] or
            section['raw_size'] != config['text_bytes']):
        raise ValueError('linked .text address or extent differs')
    raw = linked.read(0x401000, config['text_bytes'])
    if sha(raw) != config['text_sha256']:
        detail = ''
        if oracle is not None:
            expected = PEImage(oracle).read(0x401000, len(raw))
            differences = [0x401000 + i for i, (left, right) in enumerate(zip(raw, expected)) if left != right]
            detail = f'; {len(differences)} differing bytes, first {[hex(a) for a in differences[:20]]}'
        raise ValueError('linked .text SHA-256 differs' + detail)
    return raw


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--project', type=Path, default=DEFAULT_PROJECT)
    parser.add_argument('--toolkit', type=Path, default=DEFAULT_TOOLKIT)
    parser.add_argument('--output', type=Path, default=ROOT / 'matching2/build/msvc')
    parser.add_argument('--verify', type=Path, help='optional post-build comparison with retail')
    parser.add_argument('--jobs', type=int, default=4)
    args = parser.parse_args()
    project, toolkit, output = args.project.resolve(), args.toolkit.resolve(), args.output.resolve()
    if args.jobs < 1 or args.jobs > 32:
        parser.error('--jobs must be between 1 and 32')
    output.mkdir(parents=True, exist_ok=True)
    for name in ('th10.exe', 'port-report.json', 'text.bin', 'report.json', 'linked.exe'):
        (output / name).unlink(missing_ok=True)
    config = json.loads((project / 'regions.json').read_text())
    reference = json.loads((ROOT / 'decompiled/reference_bytes_validation.json').read_text())
    regions, units = validate_project(config, reference)
    dos_regions = config['dos_regions']
    dos_units = sorted({region['source'] for region in dos_regions})
    units = sorted(set(units + dos_units))
    oracle = args.verify.read_bytes() if args.verify else None
    if oracle is not None and sha(oracle) != reference['executable_sha256']:
        raise ValueError('verification executable does not match the supported reference')
    env = {**os.environ, 'WINEDEBUG': '-all', 'INCLUDE': winpath(toolkit / 'include')}
    compiler = toolkit / 'bin/cl.exe'
    banner = subprocess.run(['wine', str(compiler)], env=env, capture_output=True, text=True, timeout=60)
    if config['compiler_version'] not in banner.stdout + banner.stderr:
        raise ValueError('compiler version does not match project: ' + banner.stdout + banner.stderr)
    objects, logs = output / 'objects', output / 'logs'
    objects.mkdir(exist_ok=True)
    logs.mkdir(exist_ok=True)
    win_project, win_objects = winpath(project), winpath(objects)
    by_source = defaultdict(list)
    for region in regions + dos_regions:
        by_source[region['source']].append(region)
    def compile_unit(index, source):
        source_path = (project / source).resolve()
        if not source_path.is_relative_to(project) or source_path.suffix != '.cpp':
            raise ValueError('translation unit must be a project C++ source: ' + source)
        obj = objects / f'unit{index:04d}.obj'
        normalized = objects / f'unit{index:04d}.normalized.obj'
        obj.unlink(missing_ok=True)
        normalized.unlink(missing_ok=True)
        command = ['wine', str(compiler), *config['flags'],
                   '/I' + win_project + '\\include',
                   '/Fo' + win_objects + '\\' + obj.name, win_project + '\\' + source.replace('/', '\\')]
        result = subprocess.run(command, env=env, cwd=output, capture_output=True, text=True, timeout=180)
        (logs / f'unit{index:04d}.log').write_text(result.stdout + result.stderr)
        if result.returncode:
            raise ValueError(f'MSVC compilation failed for {source}; see {logs / ("unit%04d.log" % index)}')
        normalized_report = normalize_object(obj, normalized, by_source[source])
        return {'source': source, 'object': str(normalized), 'command': command,
                'normalization': normalized_report, 'source_sha256': sha(source_path.read_bytes())}
    compiled, failures = [], []
    print(f'Compiling {len(units)} C++ translation units with MSVC {config["compiler_version"]}...', flush=True)
    with ThreadPoolExecutor(max_workers=args.jobs) as executor:
        pending = {executor.submit(compile_unit, index, source): source for index, source in enumerate(units)}
        for index, future in enumerate(as_completed(pending), 1):
            try:
                compiled.append(future.result())
            except Exception as error:
                failures.append({'source': pending[future], 'error': str(error)})
            if index % 100 == 0 or index == len(units):
                print(f'Compiled {index}/{len(units)} units; {len(failures)} failures', flush=True)
    if failures:
        (output / 'compile-failures.json').write_text(json.dumps(failures, indent=2) + '\n')
        raise ValueError(f'{len(failures)} C++ units failed; see {output / "compile-failures.json"}')
    (output / 'compile-failures.json').unlink(missing_ok=True)
    compiled.sort(key=lambda item: item['source'])
    selected = {}
    for unit in compiled:
        for region in unit['normalization']['regions']:
            selected[region['symbol']] = {**region, 'object': unit['object']}
    script = output / 'layout.ld'
    make_link_script(regions, selected, config['symbols'], script)
    command = ['i686-w64-mingw32-ld', '--image-base', '0x400000', '--disable-auto-import',
               '--disable-reloc-section', '--no-insert-timestamp', '--entry', '_port_text_start',
               '-T', str(script), '-Map', str(output / 'linked.map'),
               *[unit['object'] for unit in compiled if unit['source'] not in dos_units], '-o', str(output / 'linked.exe')]
    run(command, output / 'link.log', output)
    raw = verify_linked(output / 'linked.exe', config, oracle)
    (output / 'text.bin').write_bytes(raw)
    dos_code = bytearray()
    for region in sorted(dos_regions, key=lambda r: int(r['address'], 0)):
        item = selected[region['symbol']]
        if item['relocation_count']:
            raise ValueError('DOS payload must have no relocations')
        _, payload, _ = read_coff_function(item['object'], region['symbol'])
        dos_code.extend(payload)
    package = build_image(project / 'pe_layout.json', output / 'text.bin', output / 'th10.exe',
                          args.verify.resolve() if args.verify else None, 'i686-w64-mingw32-as', 'objcopy', dos_code=bytes(dos_code))
    summary = {'regions': dict(Counter(region['kind'] for region in regions)),
               'bytes': {kind: sum(region['size'] for region in regions if region['kind'] == kind)
                         for kind in ('semantic', 'asm', 'data', 'padding')}}
    report = {'compiler': banner.stdout + banner.stderr, 'compiler_sha256': {
        name: sha((toolkit / 'bin' / name).read_bytes()) for name in ('cl.exe', 'c1.dll', 'c1xx.dll', 'c2.dll')},
        'translation_unit_count': len(units), 'compiled_units': compiled, 'summary': summary,
        'source_sha256': {str(path.relative_to(project)): sha(path.read_bytes())
                          for path in sorted(project.rglob('*')) if path.is_file()},
        'link_command': command, 'package': package, 'masked_bytes': 0,
        'retail_executable_used_for_build': False,
        'note': 'All Windows .text code and embedded data were compiled from C++ source. No assembly fallback.'}
    (output / 'port-report.json').write_text(json.dumps(report, indent=2) + '\n')
    print(f"Whole EXE exact: {package['size']:,} bytes; {summary['regions']['semantic']} semantic C++ functions.")
    print(output / 'th10.exe')


if __name__ == '__main__':
    main()
