#!/usr/bin/env python3
"""Build explicitly placed C++ LTCG clusters and preserve their complete bodies.

MSVC 7.1 can choose internal register conventions only during native /LTCG
linking. Schema 1 uses a synthetic compiler context; schema 2 compiles the
real callers and callees as separate /GL inputs with a real function as the
link entry. Zero-filled layout gaps are never recovered game code. Only complete
named function contributions from the freshly compiled native PE enter the outer
fixed-address COFF link.  No instruction or address operand is rewritten.
"""

from __future__ import annotations

import json
from pathlib import Path
import re
import struct
import tempfile
from typing import Any, Mapping, Sequence

from matching2.tools.common.coff_regions import _read_object, _write_name_table
from matching2.tools.common.process import sha
from matching2.tools.common.wine import compiler_environment, toolchain_hashes, winpath
from matching2.tools.matching.ltcg_semantic import (
    LTCGSemanticError, PEImage, _run_logged, _verify_toolchain,
    extract_functions, parse_map, validate_map_pe,
)


class LTCGClusterError(LTCGSemanticError):
    """A declared cluster cannot be built or selected without guessing."""


BASE_FLAGS = (
    '/nologo', '/c', '/O2', '/Gz', '/MT', '/Gy', '/G6', '/GF', '/GS', '/Zl',
)
TOOL_FILES = ('cl.exe', 'c1.dll', 'c1xx.dll', 'c2.dll', 'link.exe')


def _integer(value: Any, field: str, *, minimum: int = 0) -> int:
    if isinstance(value, bool) or not isinstance(value, (str, int)):
        raise LTCGClusterError(f'{field} must be an integer')
    try:
        result = int(value, 0) if isinstance(value, str) else value
    except ValueError as error:
        raise LTCGClusterError(f'{field} must be an integer') from error
    if not minimum <= result <= 0xffffffff:
        raise LTCGClusterError(f'{field} is outside the supported range')
    return result


def _string(value: Any, field: str) -> str:
    if (not isinstance(value, str) or not value
            or any(ord(c) < 0x20 or ord(c) == 0x7f or c == '"' for c in value)):
        raise LTCGClusterError(f'{field} must be a nonempty name without control characters or quotes')
    try:
        value.encode('ascii')
    except UnicodeEncodeError as error:
        raise LTCGClusterError(f'{field} must use ASCII') from error
    return value


def _fields(item: Any, allowed: set[str], required: set[str], field: str) -> dict[str, Any]:
    if not isinstance(item, dict) or set(item) - allowed or required - set(item):
        raise LTCGClusterError(f'{field} has missing or unknown fields')
    return dict(item)


def _project_file(project: Path, value: Any, field: str, suffix: str) -> Path:
    relative = Path(_string(value, field))
    path = (project / relative).resolve()
    if relative.is_absolute() or not path.is_relative_to(project) or path.suffix != suffix:
        raise LTCGClusterError(f'{field} must be a project-relative {suffix} file')
    if not path.is_file():
        raise LTCGClusterError(f'{field} does not exist: {relative}')
    return path


def load_cluster(project: Path, manifest_path: str, regions: Sequence[Mapping[str, Any]]) -> dict[str, Any]:
    """Validate layout and exact maintained-region ownership before compilation."""
    project = project.resolve()
    path = _project_file(project, manifest_path, 'cluster manifest', '.json')
    try:
        raw = json.loads(path.read_text())
    except (OSError, json.JSONDecodeError) as error:
        raise LTCGClusterError(f'cannot read cluster manifest {path}: {error}') from error
    version = raw.get('schema_version') if isinstance(raw, dict) else None
    if type(version) is not int or version not in (1, 2):
        raise LTCGClusterError('cluster schema_version must be 1 or 2')
    required = {'schema_version', 'name', 'source', 'headers', 'image_base',
                'functions', 'gaps', 'constants', 'absolute_symbols', 'description'}
    required |= {'driver', 'context'} if version == 1 else {'entry', 'calls'}
    allowed = required | {'additional_sources'}
    spec = _fields(raw, allowed, required, 'cluster manifest')
    name = _string(spec['name'], 'cluster name')
    if not re.fullmatch(r'[a-z][a-z0-9_]*', name):
        raise LTCGClusterError('cluster name must be a lowercase identifier')
    source = _project_file(project, spec['source'], 'source', '.cpp')
    driver = _project_file(project, spec['driver'], 'driver', '.cpp') if version == 1 else None
    if source == driver:
        raise LTCGClusterError('the compiler-context driver must be separate from maintained game source')
    additional_names = spec.get('additional_sources', [])
    if not isinstance(additional_names, list) or any(not isinstance(item, str) for item in additional_names):
        raise LTCGClusterError('additional_sources must be an array of project C++ sources')
    additional_paths = [_project_file(project, item, 'additional source', '.cpp')
                        for item in additional_names]
    if source in additional_paths or len(additional_paths) != len(set(additional_paths)):
        raise LTCGClusterError('additional_sources must be distinct from source and each other')
    source_names = [spec['source'], *additional_names]
    source_paths = [source, *additional_paths]
    spec['additional_sources'] = additional_names
    if not isinstance(spec['headers'], list):
        raise LTCGClusterError('headers must be an array')
    headers = [_project_file(project, item, 'header', '.hpp') for item in spec['headers']]
    if len(headers) != len(set(headers)):
        raise LTCGClusterError('duplicate cluster header')
    image_base = _integer(spec['image_base'], 'image_base')
    if image_base != 0x400000:
        raise LTCGClusterError('the supported fixed-address image base is 0x400000')
    _string(spec['description'], 'description')
    if not isinstance(spec['functions'], list) or not spec['functions']:
        raise LTCGClusterError('functions must be a nonempty array')
    functions = []
    for item in spec['functions']:
        required_keys = {'name', 'symbol', 'section', 'address', 'size', 'actual_abi'}
        function = _fields(item, required_keys | {'source'}, required_keys, 'function')
        for key in ('name', 'symbol', 'section', 'actual_abi'):
            function[key] = _string(function[key], 'function ' + key)
        if not re.fullmatch(r'\.text\$[a-zA-Z0-9_]+', function['section']):
            raise LTCGClusterError('functions need a dedicated .text$ section')
        function['address'] = _integer(function['address'], 'function address', minimum=image_base)
        function['size'] = _integer(function['size'], 'function size', minimum=1)
        function_source = _string(function.get('source', spec['source']), 'function source')
        if function_source not in source_names:
            raise LTCGClusterError('function source is not declared by the cluster: ' + function_source)
        function['_source'] = function_source
        functions.append(function)
    if len({item['symbol'] for item in functions}) != len(functions):
        raise LTCGClusterError('duplicate cluster function symbol')
    if len({item['section'] for item in functions}) != len(functions):
        raise LTCGClusterError('each function needs a distinct complete contribution')
    owned = [region for region in regions if region['source'] in source_names]
    if (len(owned) != len(functions)
            or {region['symbol'] for region in owned} != {item['symbol'] for item in functions}):
        raise LTCGClusterError('cluster functions disagree with maintained source ownership')
    for function in functions:
        region = next(region for region in owned if region['symbol'] == function['symbol'])
        if (region['source'] != function['_source'] or region['kind'] != 'semantic'
                or _integer(region['address'], 'region address') != function['address']
                or region['size'] != function['size']):
            raise LTCGClusterError('cluster function address/extent/classification disagrees with region: ' + function['symbol'])
    context = None
    calls = []
    if version == 1:
        context_keys = {'symbol', 'section', 'address', 'size', 'description'}
        context = _fields(spec['context'], context_keys, context_keys, 'compiler context')
        for key in ('symbol', 'section', 'description'):
            context[key] = _string(context[key], 'context ' + key)
        if not re.fullmatch(r'\.text\$[a-zA-Z0-9_]+', context['section']):
            raise LTCGClusterError('compiler context needs a dedicated .text$ section')
        context['address'] = _integer(context['address'], 'context address', minimum=image_base)
        context['size'] = _integer(context['size'], 'context size', minimum=1)
        if any(item['symbol'] == context['symbol'] or item['section'] == context['section'] for item in functions):
            raise LTCGClusterError('compiler context must not be selected as recovered code')
        entry = context
    else:
        by_symbol = {item['symbol']: item for item in functions}
        entry_symbol = _string(spec['entry'], 'entry')
        if entry_symbol not in by_symbol:
            raise LTCGClusterError('whole-program entry must be a selected real function')
        entry = by_symbol[entry_symbol]
        if set(source_names) != {item['_source'] for item in functions}:
            raise LTCGClusterError('every whole-program source must own selected functions')
        if not isinstance(spec['calls'], list) or not spec['calls']:
            raise LTCGClusterError('whole-program calls must declare at least one real caller/callee edge')
        for item in spec['calls']:
            keys = {'caller', 'callee', 'address', 'instruction'}
            call = _fields(item, keys, keys, 'internal call')
            for key in ('caller', 'callee'):
                if _string(call[key], 'call ' + key) not in by_symbol:
                    raise LTCGClusterError('both ends of an internal call must be selected in the same link')
            call['address'] = _integer(call['address'], 'call address', minimum=image_base)
            caller = by_symbol[call['caller']]
            if not caller['address'] <= call['address'] <= caller['address'] + caller['size'] - 5:
                raise LTCGClusterError('internal call lies outside its caller')
            if call['instruction'] not in ('call', 'jmp'):
                raise LTCGClusterError('internal call instruction must be call or jmp (REL32)')
            calls.append(call)
        if len({item['address'] for item in calls}) != len(calls):
            raise LTCGClusterError('duplicate internal call site')
    contexts = [context] if context else []
    gaps = []
    if not isinstance(spec['gaps'], list):
        raise LTCGClusterError('gaps must be an array')
    for index, item in enumerate(spec['gaps']):
        keys = {'section', 'address', 'size'}
        gap = _fields(item, keys, keys, 'layout gap')
        gap['section'] = _string(gap['section'], 'gap section')
        if not re.fullmatch(r'\.text\$[a-zA-Z0-9_]+|\.rdata', gap['section']):
            raise LTCGClusterError('layout gaps must use .text$ sections or .rdata')
        gap['address'] = _integer(gap['address'], 'gap address', minimum=image_base)
        gap['size'] = _integer(gap['size'], 'gap size', minimum=1)
        if gap['size'] > 0x100000:
            raise LTCGClusterError('layout gap exceeds the supported image')
        gap['symbol'] = f'_ltcg_gap_{index}'
        gaps.append(gap)
    code_sections = [item['section'] for item in functions + contexts]
    if len(set(code_sections + [item['section'] for item in gaps])) != len(code_sections) + len(gaps):
        raise LTCGClusterError('layout gaps overlap selected/context section ownership')
    constants = []
    if not isinstance(spec['constants'], list):
        raise LTCGClusterError('constants must be an array')
    for item in spec['constants']:
        keys = {'symbol', 'address', 'value'}
        constant = _fields(item, keys, keys, 'compiler constant')
        constant['symbol'] = _string(constant['symbol'], 'constant symbol')
        constant['address'] = _integer(constant['address'], 'constant address', minimum=image_base)
        if isinstance(constant['value'], bool) or not isinstance(constant['value'], (float, int)):
            raise LTCGClusterError('compiler constant must be a scalar float32 value')
        try:
            constant['bytes'] = struct.pack('<f', constant['value'])
        except (OverflowError, struct.error) as error:
            raise LTCGClusterError('compiler constant is not representable as float32') from error
        constant['size'] = 4
        constants.append(constant)
    absolute = []
    if not isinstance(spec['absolute_symbols'], list):
        raise LTCGClusterError('absolute_symbols must be an array')
    for item in spec['absolute_symbols']:
        keys = {'symbol', 'address', 'kind'}
        symbol = _fields(item, keys, keys, 'absolute symbol')
        symbol['symbol'] = _string(symbol['symbol'], 'absolute symbol name')
        symbol['address'] = _integer(symbol['address'], 'absolute symbol address')
        if symbol['kind'] not in ('data', 'relative_code', 'metadata'):
            raise LTCGClusterError('absolute symbol kind must be data, relative_code or metadata')
        if symbol['kind'] != 'metadata' and symbol['address'] < image_base:
            raise LTCGClusterError('external code/data address must be an image VA')
        # Native LINK 7.10 applies the image base to absolute REL32 targets.
        symbol['coff_value'] = symbol['address'] - image_base if symbol['kind'] == 'relative_code' else symbol['address']
        absolute.append(symbol)
    all_symbols = [item['symbol'] for item in functions + gaps + constants + absolute + contexts]
    if len(set(all_symbols)) != len(all_symbols):
        raise LTCGClusterError('duplicate symbol across cluster code/context/layout/bindings')
    ranges = sorted((item['address'], item['address'] + item['size'])
                    for item in functions + gaps + constants + contexts)
    if any(end > 0x100000000 for _, end in ranges) or any(a[1] > b[0] for a, b in zip(ranges, ranges[1:])):
        raise LTCGClusterError('cluster code/context/layout extents overlap or overflow')
    return {**spec, 'path': path, 'project': project, 'source_path': source,
            'source_paths': source_paths, 'source_names': source_names,
            'additional_source_paths': additional_paths, 'driver_path': driver,
            'header_paths': headers, 'image_base': image_base, 'functions': functions,
            'context': context, 'gaps': gaps, 'constants': constants, 'absolute_symbols': absolute,
            'entry_symbol': entry['symbol'], 'entry_address': entry['address'], 'calls': calls,
            'regions': [dict(region) for region in owned]}


def load_clusters(project: Path, config: Mapping[str, Any], regions: Sequence[Mapping[str, Any]]) -> list[dict[str, Any]]:
    manifests = config.get('ltcg_clusters', [])
    if (not isinstance(manifests, list) or any(not isinstance(item, str) for item in manifests)
            or len(set(manifests)) != len(manifests)):
        raise LTCGClusterError('ltcg_clusters must be an array of distinct manifest paths')
    clusters = [load_cluster(project, manifest, regions) for manifest in manifests]
    if len({item['name'] for item in clusters}) != len(clusters):
        raise LTCGClusterError('clusters must have distinct names')
    source_names = [source for cluster in clusters for source in cluster['source_names']]
    if len(set(source_names)) != len(source_names):
        raise LTCGClusterError('clusters must have distinct maintained sources')
    return clusters


def _snapshot(spec: Mapping[str, Any]) -> dict[str, str]:
    paths = [spec['path'], *spec['source_paths'], *spec['header_paths']]
    if spec['driver_path']:
        paths.append(spec['driver_path'])
    return {str(path): sha(path.read_bytes()) for path in paths}


def _verify_snapshot(expected: Mapping[str, str]) -> None:
    for name, digest in expected.items():
        path = Path(name)
        if not path.is_file() or sha(path.read_bytes()) != digest:
            raise LTCGClusterError('cluster input changed during compilation: ' + name)


def _require_fresh_output(path: Path) -> None:
    # Every compilation starts in a unique, previously nonexistent directory.
    if path.is_symlink() or not path.is_file() or not path.stat().st_size:
        raise LTCGClusterError('compiler/linker did not produce a fresh nonempty output: ' + str(path))


def _padding_source(gaps: Sequence[Mapping[str, Any]]) -> str:
    lines = ['// Compiler layout gaps only. No gap is recovered game code.']
    for gap in gaps:
        execute = ', execute' if gap['section'].startswith('.text$') else ''
        lines += [f'#pragma section("{gap["section"]}", read{execute})',
                  'extern "C" {',
                  f'__declspec(allocate("{gap["section"]}")) extern const unsigned char {gap["symbol"][1:]}[{gap["size"]}] = {{0}};',
                  '}']
    return '\n'.join(lines) + '\n'


def _prepare_padding_object(source: Path, destination: Path, gaps: Sequence[Mapping[str, Any]]) -> dict[str, Any]:
    """Reflag only verified zero-filled layout sections; preserve all payloads."""
    obj = _read_object(source)
    data = bytearray(obj['data'])
    reports = []
    expected_names = {item['section'] for item in gaps}
    for section in obj['sections']:
        if section['name'] not in expected_names and section['characteristics'] & 0x20:
            raise LTCGClusterError('layout object unexpectedly contains executable instructions')
    for gap in gaps:
        matches = [section for section in obj['sections'] if section['name'] == gap['section']]
        if len(matches) != 1:
            raise LTCGClusterError('missing or ambiguous compiled layout section: ' + gap['section'])
        section = matches[0]
        symbols = [symbol for symbol in obj['records'] if symbol['name'] == gap['symbol']]
        if (len(symbols) != 1 or symbols[0]['section_number'] != section['number'] or symbols[0]['value'] != 0
                or symbols[0]['storage_class'] != 2 or section['relocations']
                or len(section['raw']) != gap['size'] or any(section['raw'])):
            raise LTCGClusterError('compiled layout gap is not the declared zero-filled array: ' + gap['section'])
        characteristics = (section['characteristics'] & ~0x00f00000) | 0x00100000
        if gap['section'].startswith('.text$'):
            characteristics = (characteristics & ~0x40) | 0x20
        offset = 20 + (section['number'] - 1) * 40 + 36
        struct.pack_into('<I', data, offset, characteristics)
        reports.append({'section': section['name'], 'size': len(section['raw']), 'sha256': sha(section['raw']),
                        'original_characteristics': section['characteristics'], 'characteristics': characteristics})
    destination.write_bytes(data)
    rewritten = _read_object(destination)
    if len(obj['sections']) != len(rewritten['sections']):
        raise LTCGClusterError('layout metadata rewrite changed the section count')
    for before, after in zip(obj['sections'], rewritten['sections']):
        if before['raw'] != after['raw'] or before['relocations'] != after['relocations']:
            raise LTCGClusterError('layout metadata rewrite changed section bytes or relocations')
    return {'input_sha256': sha(obj['data']), 'output_sha256': sha(data), 'sections': reports,
            'payload_bytes_changed': 0, 'recovered_code_bytes': 0}


def _absolute_object(path: Path, symbols: Sequence[Mapping[str, Any]]) -> None:
    """Write symbol metadata only, with no COFF sections or byte implementation."""
    specs = [{'name': item['symbol']} for item in symbols]
    names, strings = _write_name_table(specs)
    records = b''.join(struct.pack('<8sIhHBB', name, item['coff_value'], -1,
                                   0x20 if item['kind'] == 'relative_code' else 0, 2, 0)
                       for name, item in zip(names, symbols))
    path.write_bytes(struct.pack('<HHIIIHH', 0x14c, 0, 0, 20, len(symbols), 0, 0) + records + strings)
    parsed = _read_object(path)
    if parsed['sections'] or any(item['section_number'] != -1 for item in parsed['records']):
        raise LTCGClusterError('absolute bindings object unexpectedly contains implementation sections')


def validate_native_output(spec: Mapping[str, Any], executable: Path, map_path: Path,
                           origins: Sequence[str] | str,
                           source_origins: Mapping[str, str] | None = None
                           ) -> tuple[list[dict[str, Any]], dict[str, Any]]:
    """Require exact ownership, addresses, complete extents, context and layout."""
    if isinstance(origins, str):
        allowed_origins = {origins}
    else:
        allowed_origins = set(origins)
    _require_fresh_output(executable)
    _require_fresh_output(map_path)
    pe = PEImage.from_path(executable)
    link_map = parse_map(map_path.read_text())
    validate_map_pe(link_map, pe)
    if pe.image_base != spec['image_base'] or pe.entry != spec['entry_address']:
        raise LTCGClusterError('native cluster image base or entry address differs')
    if any(section.name not in ('.text', '.rdata') for section in pe.sections):
        raise LTCGClusterError('native cluster contains an undeclared PE section')
    function_reports = []
    contexts = [{**spec['context'], 'name': 'compiler context'}] if spec['context'] else []
    for function in [*spec['functions'], *contexts]:
        map_symbol = function['symbol']
        is_context = bool(spec['context'] and function['symbol'] == spec['context']['symbol'])
        if is_context:
            exact = [item for item in link_map.symbols if item.name == map_symbol]
            c_decorated = [item for item in link_map.symbols if item.name == '_' + map_symbol]
            if not exact and len(c_decorated) == 1:
                map_symbol = '_' + map_symbol
        reports = extract_functions([{'name': function['name'], 'symbol': map_symbol,
                                      'visibility': 'either', 'size': function['size']}], link_map, pe)
        report = reports[0]
        if int(report['address'], 0) != function['address'] or report['map_origin'] not in allowed_origins:
            raise LTCGClusterError('native function address or compiler origin differs: ' + function['symbol'])
        if (source_origins is not None and not is_context
                and report['map_origin'] != source_origins[function['_source']]):
            raise LTCGClusterError('native function was not emitted by its declared source: ' + function['symbol'])
        contributions = [item for item in link_map.contributions if item.name == function['section']]
        if (len(contributions) != 1 or contributions[0].section_class != 'CODE'
                or contributions[0].segment != int(report['map_segment'], 16)
                or contributions[0].start != int(report['map_offset'], 0)
                or contributions[0].length != function['size']):
            raise LTCGClusterError('function is not its entire declared compiler contribution: ' + function['symbol'])
        if not is_context:
            body, _, _ = pe.read(function['address'], function['size'])
            function_reports.append({**report, 'body': body, 'actual_abi': function['actual_abi']})
    for gap in spec['gaps']:
        matches = [symbol for symbol in link_map.symbols if symbol.name == gap['symbol']]
        if (len(matches) != 1 or matches[0].address != gap['address'] or matches[0].origin != 'layout.obj'
                or 'f' in matches[0].flags):
            raise LTCGClusterError('native layout gap address/origin differs: ' + gap['symbol'])
        raw, _, _ = pe.read(gap['address'], gap['size'])
        if any(raw):
            raise LTCGClusterError('native layout gap contains nonzero bytes')
        if gap['section'].startswith('.text$'):
            contributions = [item for item in link_map.contributions if item.name == gap['section']]
            if (len(contributions) != 1 or contributions[0].segment != matches[0].segment
                    or contributions[0].start != matches[0].offset or contributions[0].length != gap['size']):
                raise LTCGClusterError('native layout gap contribution differs')
    for constant in spec['constants']:
        matches = [symbol for symbol in link_map.symbols if symbol.name == constant['symbol']]
        if len(matches) != 1 or matches[0].address != constant['address'] or matches[0].origin not in allowed_origins:
            raise LTCGClusterError('compiler constant address/origin differs: ' + constant['symbol'])
        raw, section, _ = pe.read(constant['address'], 4)
        if raw != constant['bytes'] or section.name != '.rdata':
            raise LTCGClusterError('compiler constant has the wrong value or section')
    for external in spec['absolute_symbols']:
        matches = [symbol for symbol in link_map.symbols if symbol.name == external['symbol']]
        if len(matches) != 1 or matches[0].segment != 0 or matches[0].address != external['coff_value']:
            raise LTCGClusterError('native external binding differs: ' + external['symbol'])
    declared = {item['symbol'] for item in spec['functions']}
    if spec['context']:
        context_symbol = spec['context']['symbol']
        declared |= {context_symbol, '_' + context_symbol}
    if any('f' in symbol.flags and symbol.segment and symbol.name not in declared for symbol in link_map.symbols):
        raise LTCGClusterError('native compiler emitted an undeclared function')
    calls = validate_internal_calls(spec['calls'], function_reports)
    return function_reports, {'pe_sha256': sha(pe.data), 'map_sha256': sha(map_path.read_bytes()),
                              'entry_address': f'0x{pe.entry:08X}', 'image_base': f'0x{pe.image_base:08X}',
                              'internal_calls': calls}


def validate_internal_calls(calls: Sequence[Mapping[str, Any]],
                            functions: Sequence[Mapping[str, Any]]) -> list[dict[str, Any]]:
    """Check the native caller's unmodified REL32 against its co-compiled callee."""
    by_symbol = {item['symbol']: item for item in functions}
    reports = []
    for call in calls:
        caller, callee = by_symbol[call['caller']], by_symbol[call['callee']]
        offset = call['address'] - int(caller['address'], 0)
        body = caller['body']
        opcode = 0xe8 if call['instruction'] == 'call' else 0xe9
        if not 0 <= offset <= len(body) - 5 or body[offset] != opcode:
            raise LTCGClusterError('native internal call opcode or extent differs')
        target = call['address'] + 5 + struct.unpack_from('<i', body, offset + 1)[0]
        if target != int(callee['address'], 0):
            raise LTCGClusterError('native internal call does not reach its co-compiled callee')
        reports.append({**call, 'target': f'0x{target:08X}', 'verified': True})
    return reports


def export_bodies(path: Path, functions: Sequence[Mapping[str, Any]]) -> dict[str, Any]:
    """Wrap freshly validated, already linked bodies in COFF without editing them."""
    if not functions or len({item['symbol'] for item in functions}) != len(functions):
        raise LTCGClusterError('body export needs distinct validated functions')
    for item in functions:
        if len(item['body']) != item['size'] or sha(item['body']) != item['sha256']:
            raise LTCGClusterError('validated compiler body changed before export')
    names, strings = _write_name_table([{'name': item['symbol']} for item in functions])
    offset = 20 + 40 * len(functions)
    headers, payloads, symbols, reports = [], [], [], []
    for index, (item, name) in enumerate(zip(functions, names), 1):
        section = f'.r{index:06d}'
        headers.append(struct.pack('<8sIIIIIIHHI', section.encode(), 0, 0, len(item['body']), offset,
                                   0, 0, 0, 0, 0x60100020))
        payloads.append(item['body'])
        symbols.append(struct.pack('<8sIhHBB', name, 0, index, 0x20, 2, 0))
        offset += len(item['body'])
        reports.append({'name': item['name'], 'symbol': item['symbol'], 'address': int(item['address'], 0),
                        'size': item['size'], 'source_section': item['section'], 'section': section,
                        'sha256': item['sha256'], 'section_sha256': item['sha256'],
                        'original_relocations': [], 'relocation_count': 0})
    data = (struct.pack('<HHIIIHH', 0x14c, len(functions), 0, offset, len(functions), 0, 0)
            + b''.join(headers) + b''.join(payloads) + b''.join(symbols) + strings)
    path.write_bytes(data)
    output = _read_object(path)
    for index, (item, section) in enumerate(zip(functions, output['sections']), 1):
        matches = [symbol for symbol in output['records'] if symbol['name'] == item['symbol']]
        if (section['raw'] != item['body'] or section['relocations'] or len(matches) != 1
                or matches[0]['section_number'] != index or matches[0]['value'] != 0):
            raise LTCGClusterError('COFF container did not preserve the complete compiler body')
    return {'input': 'fresh native /LTCG PE', 'output': str(path), 'regions': reports,
            'output_sha256': sha(data), 'instruction_bytes_changed': 0, 'address_operands_changed': 0}


def _verify_includes(log: str, spec: Mapping[str, Any], toolkit: Path,
                     direct_sources: Sequence[Path] = ()) -> list[dict[str, str]]:
    permitted = {path.resolve() for path in [*spec['source_paths'], *spec['header_paths']]}
    roots = [(winpath(spec['project']).rstrip('\\'), spec['project']),
             (winpath(toolkit).rstrip('\\'), toolkit)]
    found = {path.resolve() for path in direct_sources}
    headers = []
    for line in log.splitlines():
        match = re.match(r'^Note: including file:\s*(.+?)\s*$', line)
        if not match:
            continue
        windows = match.group(1)
        resolved = None
        for prefix, root in roots:
            if windows.lower().startswith(prefix.lower() + '\\'):
                resolved = (root / windows[len(prefix) + 1:].replace('\\', '/')).resolve()
                break
        if resolved is None or not resolved.is_file():
            raise LTCGClusterError('compiler included a file outside the declared project/toolkit: ' + windows)
        if resolved not in permitted and not resolved.is_relative_to(toolkit / 'include'):
            raise LTCGClusterError('compiler included an undeclared source/header: ' + str(resolved))
        found.add(resolved)
        headers.append({'path': str(resolved), 'sha256': sha(resolved.read_bytes())})
    if not permitted.issubset(found):
        raise LTCGClusterError('compiler did not report every declared implementation/header include')
    return headers


def build_cluster(spec: Mapping[str, Any], toolkit: Path, output: Path, flags: Sequence[str]) -> dict[str, Any]:
    """Build from current maintained inputs; a new directory prevents stale reuse."""
    output.mkdir(parents=True, exist_ok=True)
    destination, report_path = output / 'bodies.obj', output / 'report.json'
    destination.unlink(missing_ok=True)
    report_path.unlink(missing_ok=True)
    if tuple(flags) != BASE_FLAGS:
        raise LTCGClusterError('fixed-address cluster requires the documented MSVC compilation profile')
    inputs = _snapshot(spec)
    toolkit = toolkit.resolve()
    work = Path(tempfile.mkdtemp(prefix='native-', dir=output))
    env = compiler_environment(toolkit)
    compiler, linker, tool_hashes = _verify_toolchain(toolkit, 'wine', env, work)
    source = work / 'layout.cpp'
    source.write_text(_padding_source(spec['gaps']))
    _absolute_object(work / 'bindings.obj', spec['absolute_symbols'])
    compile_commands = []
    include_logs = []
    if spec['context']:
        gl_inputs = [(spec['driver_path'], 'cluster.obj'),
                     *[(path, f'source_{index:03d}.obj')
                       for index, path in enumerate(spec['additional_source_paths'])]]
        direct_sources = spec['additional_source_paths']
    else:
        gl_inputs = [(path, f'source_{index:03d}.obj')
                     for index, path in enumerate(spec['source_paths'])]
        direct_sources = spec['source_paths']
    for input_path, object_name, extra in [
        *[(path, name, ['/GL', '/showIncludes']) for path, name in gl_inputs],
        (source, 'layout-original.obj', []),
    ]:
        obj = work / object_name
        command = ['wine', str(compiler), *flags, *extra, '/I' + winpath(spec['project'] / 'include'),
                   '/Fo' + winpath(obj), winpath(input_path)]
        result = _run_logged(command, env, work, work / (object_name + '.log'), 180)
        _require_fresh_output(obj)
        if object_name != 'layout-original.obj':
            include_logs.append(result.stdout + result.stderr)
        compile_commands.append({'source': str(input_path), 'object': str(obj), 'command': command,
                                 'source_sha256': sha(input_path.read_bytes()), 'object_sha256': sha(obj.read_bytes())})
    includes = _verify_includes(
        '\n'.join(include_logs), spec, toolkit, direct_sources)
    layout_report = _prepare_padding_object(work / 'layout-original.obj', work / 'layout.obj', spec['gaps'])
    executable, map_path = work / 'cluster.exe', work / 'cluster.map'
    link_command = ['wine', str(linker), '/nologo', '/LTCG', '/MACHINE:X86', '/BASE:0x400000',
                    '/FILEALIGN:512', '/SUBSYSTEM:WINDOWS', '/ENTRY:' + spec['entry_symbol'],
                    '/FIXED', '/INCREMENTAL:NO', '/NODEFAULTLIB', '/OPT:REF', '/OPT:NOICF',
                    *['/INCLUDE:' + gap['symbol'] for gap in spec['gaps']],
                    '/OUT:' + winpath(executable), '/MAP:' + winpath(map_path),
                    *[winpath(work / name) for _, name in gl_inputs],
                    winpath(work / 'layout.obj'), winpath(work / 'bindings.obj')]
    _run_logged(link_command, env, work, work / 'link.log', 300)
    _verify_snapshot(inputs)
    current_tools = toolchain_hashes(toolkit, TOOL_FILES)
    if any(tool_hashes['bin/' + name] != digest for name, digest in current_tools.items()):
        raise LTCGClusterError('compiler/linker changed during the native build')
    functions, native = validate_native_output(
        spec, executable, map_path, [name for _, name in gl_inputs],
        None if spec['context'] else dict(zip(spec['source_names'], [name for _, name in gl_inputs])))
    normalization = export_bodies(destination, functions)
    report = {'schema_version': spec['schema_version'], 'name': spec['name'], 'compiler_kind': 'native-ltcg',
              'source': spec['source'], 'sources': spec['source_names'],
              'driver': spec.get('driver'), 'layout': str(spec['path']),
              'input_sha256': inputs, 'compiler_includes': includes, 'tool_sha256': tool_hashes,
              'compile_commands': compile_commands, 'link_command': link_command,
              'native_executable': str(executable), 'native_map': str(map_path), **native,
              'functions': [{key: value for key, value in item.items()
                             if key not in {'body', '_source'}} for item in functions],
              'compiler_context': ({**spec['context'], 'selected': False, 'recovered_code_bytes': 0}
                                   if spec['context'] else None),
              'layout_gaps': layout_report, 'absolute_symbols': spec['absolute_symbols'],
              'normalization': normalization, 'instruction_bytes_changed': 0, 'masked_bytes': 0,
              'reference_bytes_used_for_build': False}
    report_path.write_text(json.dumps(report, indent=2) + '\n')
    return {'source': spec['source'], 'object': str(destination), 'compiler_kind': 'native-ltcg',
            'compiler_translation_unit_count': len(compile_commands), 'command': compile_commands[0]['command'],
            'source_sha256': inputs[str(spec['source_path'])], 'normalization': normalization,
            'native_report': str(report_path), 'native_report_sha256': sha(report_path.read_bytes()),
            'native_build': report}
