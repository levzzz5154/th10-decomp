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
from dataclasses import dataclass
import json
import subprocess

from matching2.tools.common.pe import PEImage
from matching2.tools.common.process import run, sha
from matching2.tools.common.coff_regions import normalize_object
from matching2.tools.common.library import is_library_source, read_library_member
from matching2.tools.common.project_paths import DEFAULT_PROJECT, ROOT, compilation_source, project_support
from matching2.tools.matching.pack_asm_pe import build_image
from matching2.tools.common.wine import DEFAULT_TOOLKIT, compiler_environment, toolchain_hashes, winpath
from matching2.tools.matching.progress import cpp_parity_issues, recovered, summarize
from matching2.tools.matching.equivalence import apply_bodies, describe, verify_all
from matching2.tools.matching.mismatch import describe_mismatch
from matching2.tools.matching.ltcg_cluster import build_cluster, load_clusters
from matching2.tools.matching.gcc_llvm_backend import (
    compile_gcc_llvm, validate_source_compilers,
)
from matching2.tools.matching.clang_llvm_backend import compile_clang_llvm
from matching2.tools.matching.unit_cache import UnitCache


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


def verify_linked(linked, config, oracle=None):
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
    source_path = compilation_source(project, source, config)
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
               '/Fo' + win_objects + '\\' + obj.name, winpath(source_path)]
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

    A native cluster already exports normalized sections. Other sources, like
    the per-unit probe, go through raw compilation followed by normalization.
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


@dataclass
class CompilationPlan:
    sources: list[str]
    regions_by_source: dict
    clusters_by_source: dict
    compiler_profiles: dict

    @classmethod
    def from_manifest(cls, project, config, regions, text_sources):
        clusters = load_clusters(project, config, regions)
        profiles = validate_source_compilers(project, config, clusters)
        clusters_by_source = {s: c for c in clusters for s in c['ownership_names']}
        # A cluster builds all of its owners, even bodies kept in included files.
        sources = sorted(s for s in text_sources
                         if s not in clusters_by_source or clusters_by_source[s]['source'] == s)
        regions_by_source = defaultdict(list)
        for region in regions:
            regions_by_source[region['source']].append(region)
        return cls(sources, regions_by_source, clusters_by_source, profiles)


def compile_sources(plan, project, toolkit, output, config, *, jobs, cache):
    for directory in (output / 'objects', output / 'logs'):
        directory.mkdir(exist_ok=True)

    def build_one(index, source):
        key = None
        # Toolkit members are just extracted. Optional compilers must make
        # fresh objects and check their pinned inputs on every invocation.
        if cache is not None and not is_library_source(source) and source not in plan.compiler_profiles:
            cluster = plan.clusters_by_source.get(source)
            owned = cluster['regions'] if cluster else plan.regions_by_source[source]
            key = cache.key(source, config, owned, cluster)
            cached = cache.load(key)
            if cached is not None:
                return cached, True
        unit = compile_unit(project, toolkit, output, config, plan.regions_by_source,
                            plan.clusters_by_source, index, source, plan.compiler_profiles)
        return (cache.store(key, unit) if key is not None else unit), False

    count = len(plan.sources)
    compiled, failures, reused = [], [], 0
    print(f'Building {count} maintained C++ sources with MSVC {config["compiler_version"]}'
          f' and {len(plan.compiler_profiles)} optional compiler sources...', flush=True)
    with ThreadPoolExecutor(max_workers=jobs) as executor:
        pending = {executor.submit(build_one, i, source): source for i, source in enumerate(plan.sources)}
        for completed, future in enumerate(as_completed(pending), 1):
            try:
                unit, hit = future.result()
                compiled.append(unit)
                reused += hit
            except Exception as error:
                failures.append({'source': pending[future], 'error': str(error)})
            if completed % 100 == 0 or completed == count:
                print(f'Built {completed}/{count} sources; {len(failures)} failures', flush=True)
    libraries = sum(is_library_source(source) for source in plan.sources)
    print(f'Reused {reused} unchanged units; compiled {count - reused - libraries - len(failures)};'
          f' {libraries} library members extracted.', flush=True)
    failure_log = output / 'compile-failures.json'
    if failures:
        failure_log.write_text(json.dumps(failures, indent=2) + '\n')
        raise ValueError(f'{len(failures)} C++ units failed; see {failure_log}')
    failure_log.unlink(missing_ok=True)
    return sorted(compiled, key=lambda item: item['source'])


def compiler_banner(toolkit, expected_version):
    result = subprocess.run(['wine', str(toolkit / 'bin/cl.exe')], env=compiler_environment(toolkit),
                            capture_output=True, text=True, timeout=60)
    banner = result.stdout + result.stderr
    if expected_version not in banner:
        raise ValueError('compiler version does not match project: ' + banner)
    return banner


def link_exact_text(output, config, regions, selected, compiled, oracle):
    script = output / 'layout.ld'
    make_link_script(regions, selected, config['symbols'], script)
    objects = [unit['object'] for unit in compiled]
    linked = output / 'linked.exe'
    command = ['i686-w64-mingw32-ld', '--image-base', '0x400000', '--disable-auto-import',
               '--disable-reloc-section', '--no-insert-timestamp', '--entry', '_port_text_start',
               '-T', str(script), '-Map', str(output / 'linked.map'), *objects, '-o', str(linked)]
    run(command, output / 'link.log', output)
    image = PEImage(linked.read_bytes())
    text = verify_linked(image, config, oracle)
    (output / 'text.bin').write_bytes(text)
    return text, image.dos_stub(), command


def print_summary(report):
    package = report['package']
    equivalent = report['equivalent_recoveries']
    summary = report['summary']
    if package['exact']:
        print(f"Whole EXE exact: {package['size']:,} bytes.")
    else:
        total = sum(item['bytes'] for item in equivalent)
        identical = set(report['equivalent_bodies_identical_to_retail'])
        identical_bytes = sum(item['bytes'] for item in equivalent if item['region'] in identical)
        print(f"EXE exact outside {len(equivalent)} equivalent regions built from C++ "
              f"({total:,} bytes): {package['size']:,} bytes. "
              "Use --exact for the bit-identical image.")
        print(f"Equivalent C++ bodies already byte-identical to retail: {len(identical):,} of "
              f"{len(equivalent):,} regions / {identical_bytes:,} of {total:,} bytes.")
    if package['verified_against_oracle']:
        print(f"Full-file comparison against retail: {package['oracle_differing_bytes']:,} differing bytes.")
    counts, sizes = summary['regions'], summary['bytes']
    print(f"Byte-matched game regions: {counts['semantic']:,} regions / {sizes['semantic']:,} bytes.")
    print(f"Equivalent C++: {counts['equivalent']:,} regions / {sizes['equivalent']:,} bytes.")
    for item in equivalent:
        print('  ' + describe(item))
    print(f"Assembly-only (no C++ recovery): {counts['asm']:,} regions / {sizes['asm']:,} bytes.")
    print(f"Toolkit runtime library: {counts['library']:,} regions / {sizes['library']:,} bytes.")
    print(f"Embedded .text data: {sizes['data']:,} bytes; padding: {sizes['padding']:,} bytes.")
    print(recovered(summary, equivalent))
    print(package['output'])


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--project', type=Path, default=DEFAULT_PROJECT)
    parser.add_argument('--toolkit', type=Path, default=DEFAULT_TOOLKIT)
    parser.add_argument('--output', type=Path, default=ROOT / 'matching2/build/msvc')
    parser.add_argument('--verify', type=Path, help='optional post-build comparison with retail')
    parser.add_argument('--jobs', type=int, default=4)
    mode = parser.add_mutually_exclusive_group()
    mode.add_argument('--exact', action='store_true',
                      help='build equivalent regions from their assembly: the bit-identical executable')
    mode.add_argument('--require-cpp-parity', action='store_true',
                      help='require the retail image hash, no assembly regions, and no explicit assembly in project sources')
    parser.add_argument('--no-cache', action='store_true',
                        help='recompile every unit instead of reusing unchanged ones')
    args = parser.parse_args()
    project, toolkit, output = args.project.resolve(), args.toolkit.resolve(), args.output.resolve()
    if args.jobs < 1 or args.jobs > 32:
        parser.error('--jobs must be between 1 and 32')
    output.mkdir(parents=True, exist_ok=True)
    for name in ('th10.exe', 'port-report.json', 'text.bin', 'report.json', 'linked.exe'):
        (output / name).unlink(missing_ok=True)
    layout = project_support(project, 'pe_layout.json')
    config = json.loads(project_support(project, 'regions.json').read_text())
    reference = json.loads(layout.read_text())['reference']
    regions, sources = validate_project(config, reference)
    plan = CompilationPlan.from_manifest(project, config, regions, sources)
    oracle = args.verify.read_bytes() if args.verify else None
    if oracle is not None and sha(oracle) != reference['executable_sha256']:
        raise ValueError('verification executable does not match the supported reference')
    banner = compiler_banner(toolkit, config['compiler_version'])
    cache = None if args.no_cache else UnitCache(project, toolkit, output / 'cache', config)
    compiled = compile_sources(plan, project, toolkit, output, config, jobs=args.jobs, cache=cache)
    selected = {region['symbol']: {**region, 'object': unit['object']}
                for unit in compiled for region in unit['normalization']['regions']}
    raw, dos_stub, command = link_exact_text(output, config, regions, selected, compiled, oracle)
    equivalent, bodies = verify_all(project, config, regions, toolkit, raw, output)
    identical_bodies = sorted(item['region'] for item in equivalent if item['differing_bytes'] == 0)
    use_cpp_models = bool(bodies) and not args.exact
    packed = output / 'text.bin'
    if use_cpp_models:
        packed = output / 'text-equivalent.bin'
        packed.write_bytes(apply_bodies(raw, regions, bodies))
    expected_differences = sum(item['differing_bytes'] for item in equivalent) if use_cpp_models else 0
    package = build_image(layout, packed, output / 'th10.exe', dos_stub=dos_stub,
                          expected_differing_bytes=expected_differences, oracle=oracle)
    report = {
        'compiler': banner,
        'compiler_sha256': toolchain_hashes(toolkit, ('cl.exe', 'c1.dll', 'c1xx.dll', 'c2.dll')),
        'translation_unit_count': sum(unit.get('compiler_translation_unit_count', 1) for unit in compiled),
        'maintained_source_count': len(plan.sources),
        'compiled_units': compiled,
        'summary': summarize(regions, config.get('equivalent_recoveries', ())),
        'equivalent_recoveries': equivalent,
        'equivalent_bodies_identical_to_retail': identical_bodies,
        'source_sha256': {str(path.relative_to(project)): sha(path.read_bytes())
                          for path in sorted(project.rglob('*')) if path.is_file()},
        'link_command': command,
        'package': package,
        'masked_bytes': 0,
        'retail_executable_used_for_build': False,
        'equivalent_regions_built_from': ('c++' if use_cpp_models else 'assembly') if bodies else None,
        'note': ('Built from maintained C++ sources using the recorded compilers, including inline-assembly '
                 'scaffolding. The link from exact sources is required to match retail byte for byte. Unless '
                 '--exact is given, each equivalent region is then built from its C++ source, which is checked '
                 'to differ from the exact bytes only by its recorded differences.'),
    }
    (output / 'port-report.json').write_text(json.dumps(report, indent=2) + '\n')
    print_summary(report)
    if args.require_cpp_parity:
        issues = list(cpp_parity_issues(project, regions, package['exact']))
        if issues:
            raise SystemExit('C++ parity check failed:\n  ' + '\n  '.join(issues))
        print('C++ parity check passed.')


if __name__ == '__main__':
    main()
