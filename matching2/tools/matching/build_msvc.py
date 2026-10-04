#!/usr/bin/env python3
"""Compile the complete C++ project into an independently linked PE.

Every region is first linked from its exact source and the .text image is
required to match retail byte for byte.  Regions registered as equivalent
recoveries are then rebuilt from their C++ source, which must differ from the
exact bytes only by the differences its layout records.  ``--exact`` keeps
the assembly for those regions and produces the bit-identical executable.
"""

import sys
from pathlib import Path

if __package__ in (None, ""):
    sys.path.insert(0, str(Path(__file__).resolve().parents[3]))

import argparse
from collections import defaultdict
from concurrent.futures import ThreadPoolExecutor, as_completed
import hashlib
import json
import re
import shutil
import subprocess

from matching2.tools.common.pe import PEImage
from matching2.tools.common.process import run, sha
from matching2.tools.common.coff_regions import normalize_object
from matching2.tools.common.coff import read_coff_function
from matching2.tools.common.library import is_library_source, read_library_member
from matching2.tools.matching.pack_asm_pe import build_image
from matching2.tools.common.wine import DEFAULT_TOOLKIT, compiler_environment, toolchain_hashes, winpath
from matching2.tools.matching.progress import recovered, summarize
from matching2.tools.matching.equivalence import apply_bodies, describe, verify_all
from matching2.tools.matching.mismatch import describe_mismatch
from matching2.tools.matching.ltcg_cluster import build_cluster, load_clusters
from matching2.tools.matching.gcc_llvm_backend import (
    compile_gcc_llvm, validate_source_compilers,
)
from matching2.tools.matching.clang_llvm_backend import compile_clang_llvm

ROOT = Path(__file__).resolve().parents[3]
DEFAULT_PROJECT = ROOT / 'matching2/msvc'


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
        if region['kind'] not in ('semantic', 'asm', 'data', 'padding', 'library'):
            raise ValueError('unclassified C++ region')
        if (region['kind'] == 'library') != is_library_source(region['source']):
            raise ValueError('library regions and only library regions come from a toolkit library: '
                             + region['name'])
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
        expected = None
        detail = 'Pass --verify <retail.exe> for expected-byte diagnostics.'
        if oracle is not None:
            expected = PEImage(oracle).read(0x401000, len(raw))
        if expected is not None:
            if len(expected) == len(raw) and sha(expected) == config['text_sha256']:
                detail = describe_mismatch(raw, expected, config)
            else:
                detail = 'Diagnostic reference does not match the required .text hash.'
        raise ValueError('linked .text SHA-256 differs\n' + detail)
    return raw


def extract_library_unit(toolkit, output, index, source):
    """Copy the toolkit library member a library translation unit names."""
    blob = read_library_member(toolkit, source)
    objects = output / 'objects'
    objects.mkdir(parents=True, exist_ok=True)
    obj = objects / f'unit{index:04d}.obj'
    obj.write_bytes(blob)
    return {'source': source, 'object': str(obj), 'command': None, 'member_sha256': sha(blob)}


def compile_raw(project, toolkit, output, index, source, config, *, compiler_profiles=None):
    """Compile one maintained source to a raw COFF object without selecting regions."""
    profiles = (validate_source_compilers(project, config) if compiler_profiles is None
                else compiler_profiles)
    if source in profiles:
        if profiles[source]['kind'] == 'gcc-llvm-coff':
            return compile_gcc_llvm(project, output, index, source, profiles[source])
        if profiles[source]['kind'] == 'clang-llvm-coff':
            return compile_clang_llvm(project, output, index, source, profiles[source])
        raise ValueError('unsupported compiler profile kind: ' + profiles[source]['kind'])
    if is_library_source(source):
        return extract_library_unit(toolkit, output, index, source)
    source_path = (project / source).resolve()
    if not source_path.is_relative_to(project) or source_path.suffix != '.cpp':
        raise ValueError('translation unit must be a project C++ source: ' + source)
    objects, logs = output / 'objects', output / 'logs'
    objects.mkdir(parents=True, exist_ok=True)
    logs.mkdir(parents=True, exist_ok=True)
    env = compiler_environment(toolkit)
    compiler = toolkit / 'bin/cl.exe'
    win_project, win_objects = winpath(project), winpath(objects)
    obj = objects / f'unit{index:04d}.obj'
    obj.unlink(missing_ok=True)
    command = ['wine', str(compiler), *config['flags'],
               *config.get('source_flags', {}).get(source, []),
               '/I' + win_project + '\\include',
               '/Fo' + win_objects + '\\' + obj.name, win_project + '\\' + source.replace('/', '\\')]
    result = subprocess.run(command, env=env, cwd=output, capture_output=True, text=True, timeout=180)
    (logs / f'unit{index:04d}.log').write_text(result.stdout + result.stderr)
    if result.returncode:
        raise ValueError(f'MSVC compilation failed for {source}; see {logs / ("unit%04d.log" % index)}')
    return {'source': source, 'object': str(obj), 'command': command,
            'source_sha256': sha(source_path.read_bytes())}


def normalize_unit(object_path, destination, source, config, regions):
    """Select the named whole-section regions of a compiled object."""
    destination.unlink(missing_ok=True)
    report = normalize_object(object_path, destination, regions,
                              config.get('coff_aliases', {}).get(source))
    return {'object': str(destination), 'normalization': report}


def compile_unit(project, toolkit, output, config, by_source, cluster_by_source, index, source,
                 compiler_profiles=None):
    """Compile one maintained unit into the normalized COFF object the link consumes.

    Shared by the exact-match build and by per-unit probes so both consume one
    compile path. ``by_source`` maps a source to the region records it owns.
    """
    if source in cluster_by_source:
        if compiler_profiles is None and config.get('source_compilers'):
            validate_source_compilers(project, config, list(cluster_by_source.values()))
        cluster = cluster_by_source[source]
        return build_cluster(cluster, toolkit, output / 'clusters' / cluster['name'], config['flags'])
    raw = compile_raw(project, toolkit, output, index, source, config,
                      compiler_profiles=compiler_profiles)
    normalized = output / 'objects' / f'unit{index:04d}.normalized.obj'
    return {**raw, **normalize_unit(raw['object'], normalized, source, config, by_source[source])}


INCLUDE_PATTERN = re.compile(rb'^[ \t]*#[ \t]*include[ \t]*["<]([^">]+)[">]', re.MULTILINE)


class UnitCache:
    """Reuse a unit's normalized object while everything that produced it is unchanged.

    A unit's key covers the build tools, the compiler binaries, the compile
    profile, the regions it owns and the content of every project file it can
    read: its sources and the transitive closure of their project includes
    (conditional includes are all followed, so the closure only over-approximates).
    The link and the whole-image comparison always run, so a reused object is
    still verified as part of the exact executable.
    """

    def __init__(self, project, toolkit, directory, config):
        self.project, self.directory = project, directory
        self.file_digests, self.closures = {}, {}
        tools = hashlib.sha256()
        for path in sorted((ROOT / 'matching2/tools').rglob('*.py')):
            tools.update(str(path.relative_to(ROOT)).encode() + b'\0' + path.read_bytes())
        for path in sorted((toolkit / 'bin').iterdir()):
            if path.is_file():
                tools.update(path.name.encode() + b'\0' + path.read_bytes())
        self.base = {'tools': tools.hexdigest(), 'flags': config['flags'],
                     'compiler_version': config['compiler_version']}

    def digest(self, path):
        path = Path(path)
        if path not in self.file_digests:
            self.file_digests[path] = sha(path.read_bytes())
        return self.file_digests[path]

    def closure(self, path):
        """Project files reachable from a source through #include."""
        path = Path(path).resolve()
        if path in self.closures:
            return self.closures[path]
        seen, stack = set(), [path]
        while stack:
            current = stack.pop()
            if current in seen:
                continue
            seen.add(current)
            for name in INCLUDE_PATTERN.findall(current.read_bytes()):
                name = name.decode('latin-1').replace('\\', '/')
                for base in (current.parent, self.project / 'include'):
                    candidate = (base / name).resolve()
                    if candidate.is_file() and candidate.is_relative_to(self.project):
                        stack.append(candidate)
                        break
        self.closures[path] = seen
        return seen

    def key(self, source, config, regions, cluster, profile):
        if cluster is not None:
            roots = [cluster['path'], *cluster['source_paths'], *cluster['included_source_paths'],
                     *cluster['header_paths'], *cluster['additional_source_paths'],
                     *cluster.get('ordinary_source_paths', [])]
            if cluster['driver_path']:
                roots.append(cluster['driver_path'])
        else:
            roots = [self.project / source]
        files = set()
        for root in roots:
            root = Path(root).resolve()
            files |= self.closure(root) if root.suffix in ('.cpp', '.hpp', '.h') else {root}
        record = {**self.base, 'source': source, 'regions': regions,
                  'source_flags': config.get('source_flags', {}).get(source),
                  'coff_aliases': config.get('coff_aliases', {}).get(source),
                  'profile': profile, 'cluster': cluster,
                  'files': {str(path.relative_to(self.project)): self.digest(path)
                            for path in sorted(files)}}
        return sha(json.dumps(record, sort_keys=True, default=str).encode())

    def load(self, key):
        entry = self.directory / key[:2] / key
        try:
            result = json.loads((entry / 'result.json').read_text())
            if sha(Path(result['object']).read_bytes()) != result['cached_object_sha256']:
                return None
        except (OSError, ValueError, KeyError):
            return None
        return result

    def store(self, key, result):
        entry = self.directory / key[:2] / key
        staging = entry.with_name(entry.name + '.partial')
        shutil.rmtree(staging, ignore_errors=True)
        staging.mkdir(parents=True)
        shutil.copyfile(result['object'], staging / 'unit.obj')
        result = {**result, 'object': str(entry / 'unit.obj'),
                  'cached_object_sha256': sha((staging / 'unit.obj').read_bytes())}
        (staging / 'result.json').write_text(json.dumps(result) + '\n')
        shutil.rmtree(entry, ignore_errors=True)
        staging.rename(entry)
        return result


def compile_unit_cached(cache, project, toolkit, output, config, by_source, cluster_by_source, index,
                        source, compiler_profiles):
    """compile_unit, skipped when an identical unit was already built."""
    if cache is None or is_library_source(source) or source in compiler_profiles:
        return compile_unit(project, toolkit, output, config, by_source, cluster_by_source, index,
                            source, compiler_profiles), False
    key = cache.key(source, config, by_source[source], cluster_by_source.get(source), None)
    result = cache.load(key)
    if result is not None:
        return result, True
    result = compile_unit(project, toolkit, output, config, by_source, cluster_by_source, index,
                          source, compiler_profiles)
    return cache.store(key, result), False


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--project', type=Path, default=DEFAULT_PROJECT)
    parser.add_argument('--toolkit', type=Path, default=DEFAULT_TOOLKIT)
    parser.add_argument('--output', type=Path, default=ROOT / 'matching2/build/msvc')
    parser.add_argument('--verify', type=Path, help='optional post-build comparison with retail')
    parser.add_argument('--jobs', type=int, default=4)
    parser.add_argument('--exact', action='store_true',
                        help='build equivalent regions from their assembly: the bit-identical executable')
    parser.add_argument('--no-cache', action='store_true',
                        help='recompile every unit instead of reusing unchanged ones')
    args = parser.parse_args()
    project, toolkit, output = args.project.resolve(), args.toolkit.resolve(), args.output.resolve()
    if args.jobs < 1 or args.jobs > 32:
        parser.error('--jobs must be between 1 and 32')
    output.mkdir(parents=True, exist_ok=True)
    for name in ('th10.exe', 'port-report.json', 'text.bin', 'report.json', 'linked.exe'):
        (output / name).unlink(missing_ok=True)
    config = json.loads((project / 'regions.json').read_text())
    reference = json.loads((project / 'pe_layout.json').read_text())['reference']
    regions, units = validate_project(config, reference)
    clusters = load_clusters(project, config, regions)
    compiler_profiles = validate_source_compilers(project, config, clusters)
    cluster_by_source = {source: cluster for cluster in clusters for source in cluster['source_names']}
    cluster_additional_sources = {
        source for cluster in clusters for source in cluster['additional_sources']
    }
    dos_regions = config['dos_regions']
    dos_units = sorted({region['source'] for region in dos_regions})
    units = sorted((set(units + dos_units) - cluster_additional_sources))
    oracle = args.verify.read_bytes() if args.verify else None
    if oracle is not None and sha(oracle) != reference['executable_sha256']:
        raise ValueError('verification executable does not match the supported reference')
    env = compiler_environment(toolkit)
    compiler = toolkit / 'bin/cl.exe'
    banner = subprocess.run(['wine', str(compiler)], env=env, capture_output=True, text=True, timeout=60)
    if config['compiler_version'] not in banner.stdout + banner.stderr:
        raise ValueError('compiler version does not match project: ' + banner.stdout + banner.stderr)
    objects, logs = output / 'objects', output / 'logs'
    objects.mkdir(exist_ok=True)
    logs.mkdir(exist_ok=True)
    by_source = defaultdict(list)
    for region in regions + dos_regions:
        by_source[region['source']].append(region)
    compiled, failures, reused = [], [], 0
    cache = None if args.no_cache else UnitCache(project, toolkit, output / 'cache', config)
    print(f'Building {len(units)} maintained C++ sources with MSVC {config["compiler_version"]}'
          f' and {len(config.get("source_compilers", {}))} optional compiler sources...', flush=True)
    with ThreadPoolExecutor(max_workers=args.jobs) as executor:
        pending = {executor.submit(compile_unit_cached, cache, project, toolkit, output, config,
                                   by_source, cluster_by_source, index, source,
                                   compiler_profiles): source
                   for index, source in enumerate(units)}
        for index, future in enumerate(as_completed(pending), 1):
            try:
                unit, hit = future.result()
                compiled.append(unit)
                reused += hit
            except Exception as error:
                failures.append({'source': pending[future], 'error': str(error)})
            if index % 100 == 0 or index == len(units):
                print(f'Built {index}/{len(units)} sources; {len(failures)} failures', flush=True)
    uncached = sum(is_library_source(source) for source in units)
    print(f'Reused {reused} unchanged units; compiled {len(units) - reused - uncached - len(failures)};'
          f' {uncached} library members extracted.', flush=True)
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
    equivalent, bodies = verify_all(project, config, regions, toolkit, raw, output)
    packed = output / 'text.bin'
    if bodies and not args.exact:
        packed = output / 'text-equivalent.bin'
        packed.write_bytes(apply_bodies(raw, regions, bodies))
    dos_code = bytearray()
    for region in sorted(dos_regions, key=lambda r: int(r['address'], 0)):
        item = selected[region['symbol']]
        if item['relocation_count']:
            raise ValueError('DOS payload must have no relocations')
        _, payload, _ = read_coff_function(item['object'], region['symbol'])
        dos_code.extend(payload)
    package = build_image(project / 'pe_layout.json', packed, output / 'th10.exe',
                          args.verify.resolve() if args.verify else None, dos_code=bytes(dos_code),
                          exact=packed == output / 'text.bin')
    summary = summarize(regions, config.get('equivalent_recoveries', ()))
    report = {'compiler': banner.stdout + banner.stderr,
        'compiler_sha256': toolchain_hashes(toolkit, ('cl.exe', 'c1.dll', 'c1xx.dll', 'c2.dll')),
        'translation_unit_count': sum(unit.get('compiler_translation_unit_count', 1) for unit in compiled),
        'maintained_source_count': len(units), 'compiled_units': compiled, 'summary': summary,
        'equivalent_recoveries': equivalent,
        'source_sha256': {str(path.relative_to(project)): sha(path.read_bytes())
                          for path in sorted(project.rglob('*')) if path.is_file()},
        'link_command': command, 'package': package, 'masked_bytes': 0,
        'retail_executable_used_for_build': False,
        'equivalent_regions_built_from': 'assembly' if package['exact'] else 'c++',
        'note': 'Built from maintained C++ sources using the recorded compilers, including inline-assembly scaffolding. The link from exact sources is required to match retail byte for byte. Unless --exact is given, each equivalent region is then built from its C++ source, which is checked to differ from the exact bytes only by its recorded differences.'}
    (output / 'port-report.json').write_text(json.dumps(report, indent=2) + '\n')
    if package['exact']:
        print(f"Whole EXE exact: {package['size']:,} bytes.")
    else:
        print(f"EXE exact outside {len(bodies)} equivalent regions built from C++ "
              f"({sum(map(len, bodies.values())):,} bytes): {package['size']:,} bytes. "
              "Use --exact for the bit-identical image.")
    print(f"Ordinary C++: {summary['regions'].get('semantic', 0):,} regions / {summary['bytes']['semantic']:,} bytes.")
    print(f"Equivalent C++: {summary['regions']['equivalent']:,} regions / {summary['bytes']['equivalent']:,} bytes.")
    for item in equivalent:
        print('  ' + describe(item))
    print(f"Remaining assembly: {summary['regions'].get('asm', 0):,} regions / {summary['bytes']['asm']:,} bytes.")
    print(f"Toolkit runtime library: {summary['regions']['library']:,} regions / {summary['bytes']['library']:,} bytes.")
    print(f"Embedded .text data: {summary['bytes']['data']:,} bytes; padding: {summary['bytes']['padding']:,} bytes.")
    print(recovered(summary))
    print(output / 'th10.exe')


if __name__ == '__main__':
    main()
