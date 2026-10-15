#!/usr/bin/env python3
"""Build explicitly placed C++ LTCG clusters and preserve their complete bodies.

MSVC 7.1 can choose internal register conventions only during native /LTCG
linking. Schema 1 uses a synthetic compiler context; schema 2 compiles the
real callers and callees as separate /GL inputs with a real function as the
link entry. Zero-filled layout gaps are never recovered game code. Complete
named function contributions and complete declared C++ unwind contributions
from the freshly compiled native PE enter the outer fixed-address COFF link.
No instruction or address operand is rewritten.

A compiler pools each distinct float literal once, and the pool address depends
on the whole translation-unit set, not on the cluster layout.  When retail put
such a literal at an address the layout cannot reach, ``constant_aliases``
binds the compiler's own ``__real@<bits>`` symbol absolutely at the retail
address instead; the link tolerates the discarded pooled copy and the report
records that duplicate.  The alias wins the symbol resolution outright, so a
selected body references the retail address without any byte being patched.

Exception-enabled clusters also validate the compiler's static unwind funclets
as one complete .text$x contribution, and their native .xdata$x bytes against
the preserved final-image metadata. The compiler's $L numbers may vary with
declarations; selection checks their static origin, address, bounds and complete
contribution coverage, then gives the exported COFF symbol a stable name.

A callee whose parameter register no declaration names (an argument in EDI, for
instance) can only get that register from a body the /LTCG pass can see, so
``anchors`` declares such a compiled body: the linker selects it at the retail
address, the layout's gaps place it there and the modelled caller's call bakes
the retail displacement.  Anchors are validated like selected functions (symbol,
address and complete contribution) and are never exported as recovered code.
Data aliases default to references in selected bodies only; an
explicit ``reference_scope: compiled_graph`` may also use a complete validated
context or anchor, additionally checking compiler origin and bounded code
selection for each anchor. Compiler float literal aliases remain selected-body-only.
"""

from __future__ import annotations

import json
from pathlib import Path
import re
import shutil
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
    # Schema 1 contexts may explicitly root independently reachable functions
    # as well.  This keeps a real game's public ABI while still linking the
    # caller/callee cluster under native LTCG.  Schema 2 uses the same field
    # for additional whole-program entry roots.
    #
    # constant_aliases rebind a compiler-generated float literal to the
    # retail address instead of placing its pooled copy; see the docstring.
    allowed = required | {'additional_sources', 'included_sources', 'roots', 'constant_aliases', 'data_aliases',
                          'anchors', 'exceptions', 'native_data', 'ordinary_sources', 'anchor_roots', 'owned_includes', 'compilation_units'}
    spec = _fields(raw, allowed, required, 'cluster manifest')
    exceptions = spec.get('exceptions', False)
    if type(exceptions) is not bool:
        raise LTCGClusterError('exceptions must be a boolean')
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
    included_names = spec.get('included_sources', [])
    if not isinstance(included_names, list) or any(not isinstance(item, str) for item in included_names):
        raise LTCGClusterError('included_sources must be an array of project C++ sources')
    included_paths = [_project_file(project, item, 'included source', '.cpp') for item in included_names]
    if len(included_paths) != len(set(included_paths)) or any(item in source_paths for item in included_paths):
        raise LTCGClusterError('included_sources must be distinct from maintained cluster sources and each other')
    # Source ownership and compiler translation units are separate: selected
    # bodies may live in included files while their established native unit
    # stays intact. Every owned include must remain a declared dependency.
    owned_includes = spec.get('owned_includes', {})
    if (not isinstance(owned_includes, dict)
            or any(not isinstance(k, str) or not isinstance(v, str)
                   for k, v in owned_includes.items())):
        raise LTCGClusterError('owned_includes must map included C++ sources to maintained source owners')
    if any(k not in included_names or v not in source_names for k, v in owned_includes.items()):
        raise LTCGClusterError('owned includes require a declared include and a compiled source owner')
    ownership_names = [*source_names, *owned_includes]
    compilation_units = spec.get('compilation_units', {})
    if (not isinstance(compilation_units, dict)
            or any(k not in source_names or not isinstance(v, str)
                   for k, v in compilation_units.items())):
        raise LTCGClusterError('compilation_units must map maintained sources to compiler C++ units')
    compilation_paths = [_project_file(project, compilation_units.get(n, n),
                                       'compiler translation unit', '.cpp') for n in source_names]
    if len(set(compilation_paths)) != len(compilation_paths):
        raise LTCGClusterError('compiler translation units must be distinct')
    raw_ordinary = spec.get('ordinary_sources', [])
    if not isinstance(raw_ordinary, list):
        raise LTCGClusterError('ordinary_sources must be an array')
    ordinary_sources = []
    for item in raw_ordinary:
        ordinary = _fields(item, {'source', 'section_renames'}, {'source', 'section_renames'}, 'ordinary source')
        ordinary['source'] = _string(ordinary['source'], 'ordinary source')
        _project_file(project, ordinary['source'], 'ordinary source', '.cpp')
        if not exceptions:
            raise LTCGClusterError('ordinary EH sources require exceptions')
        renames = ordinary['section_renames']
        if not isinstance(renames, list) or len(renames) != 2:
            raise LTCGClusterError('ordinary sources need paired EH code/data section renames')
        ordinary['section_renames'] = []
        for rename in renames:
            rename = _fields(rename, {'from', 'to'}, {'from', 'to'}, 'ordinary section rename')
            old, new = rename['from'], rename['to']
            if (old not in ('.text$x', '.xdata$x') or not isinstance(new, str) or len(new) > 8
                    or not re.fullmatch(r'\.text\$[a-zA-Z0-9_]+' if old == '.text$x' else r'\.rdata\$[a-zA-Z0-9_]+', new)
                    or new in ('.text$x', '.xdata$x')):
                raise LTCGClusterError('ordinary section renames must isolate complete EH code/data headers')
            ordinary['section_renames'].append(rename)
        if {rename['from'] for rename in ordinary['section_renames']} != {'.text$x', '.xdata$x'}:
            raise LTCGClusterError('ordinary sources need paired EH code/data section renames')
        ordinary_sources.append(ordinary)
    ordinary_names = [item['source'] for item in ordinary_sources]
    ordinary_paths = [_project_file(project, name, 'ordinary source', '.cpp') for name in ordinary_names]
    if (len(set(ordinary_paths)) != len(ordinary_paths)
            or any(path in [*source_paths, *included_paths, driver] for path in ordinary_paths)):
        raise LTCGClusterError('ordinary sources must be distinct from all other compiler inputs')
    ordinary_sections = [rename['to'] for item in ordinary_sources for rename in item['section_renames']]
    if len(set(ordinary_sections)) != len(ordinary_sections):
        raise LTCGClusterError('ordinary EH islands must be distinct')
    ordinary_by_source = {item['source']: item for item in ordinary_sources}
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
        function = _fields(item, required_keys | {'source', 'generated', 'native_symbol_pattern'}, required_keys, 'function')
        for key in ('name', 'symbol', 'section', 'actual_abi'):
            function[key] = _string(function[key], 'function ' + key)
        if not re.fullmatch(r'\.text\$[a-zA-Z0-9_]+', function['section']):
            raise LTCGClusterError('functions need a dedicated .text$ section')
        function['address'] = _integer(function['address'], 'function address', minimum=image_base)
        function['size'] = _integer(function['size'], 'function size', minimum=1)
        function_source = _string(function.get('source', spec['source']), 'function source')
        if function_source not in ownership_names:
            raise LTCGClusterError('function source is not declared by the cluster: ' + function_source)
        function['_source'] = function_source
        generated = function.get('generated', False)
        if type(generated) is not bool:
            raise LTCGClusterError('generated function flag must be a boolean')
        if generated and (not exceptions or function['section'] != '.text$x'):
            raise LTCGClusterError('generated functions require exception handling and .text$x')
        if 'native_symbol_pattern' in function:
            if not generated or function['native_symbol_pattern'] != r'\$L[0-9]+':
                raise LTCGClusterError('only generated unwind funclets may select a native $L number')
        functions.append(function)
    if len({item['symbol'] for item in functions}) != len(functions):
        raise LTCGClusterError('duplicate cluster function symbol')
    for section in {item['section'] for item in functions}:
        members = [item for item in functions if item['section'] == section]
        if len(members) > 1 and (not all(item.get('generated') for item in members)
                                or len({item['_source'] for item in members}) != 1):
            raise LTCGClusterError('each function needs a distinct complete contribution')
    owned = [region for region in regions if region['source'] in ownership_names]
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
    roots = []
    by_symbol = {item['symbol']: item for item in functions}
    raw_roots = spec.get('roots', [])
    if not isinstance(raw_roots, list) or any(not isinstance(item, str) for item in raw_roots):
        raise LTCGClusterError('whole-program roots must be an array of selected symbols')
    for item in raw_roots:
        root_symbol = _string(item, 'root symbol')
        if root_symbol not in by_symbol:
            raise LTCGClusterError('whole-program root must be a selected real function')
        if by_symbol[root_symbol].get('generated'):
            raise LTCGClusterError('generated unwind functions cannot be whole-program roots')
        roots.append(root_symbol)
    if len(set(roots)) != len(roots):
        raise LTCGClusterError('whole-program roots must be distinct')
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
        entry_symbol = _string(spec['entry'], 'entry')
        if entry_symbol not in by_symbol:
            raise LTCGClusterError('whole-program entry must be a selected real function')
        entry = by_symbol[entry_symbol]
        if set(source_names) != {owned_includes.get(item['_source'], item['_source']) for item in functions}:
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
    # ABI anchors: a compiled C++ body for a callee whose parameter register no
    # declaration names.  The body is selected into the native /LTCG link (so
    # the whole-program pass can assign the register) and placed at the retail
    # address by the layout, but it is never exported as recovered code.
    anchors = []
    raw_anchors = spec.get('anchors', [])
    if not isinstance(raw_anchors, list):
        raise LTCGClusterError('anchors must be an array')
    for item in raw_anchors:
        keys = {'name', 'symbol', 'section', 'address', 'size'}
        anchor = _fields(item, keys | ({'source', 'generated', 'native_symbol_pattern'} if ordinary_sources else set()), keys, 'ABI anchor')
        for key in ('name', 'symbol', 'section'):
            anchor[key] = _string(anchor[key], 'anchor ' + key)
        if not re.fullmatch(r'\.text\$[a-zA-Z0-9_]+', anchor['section']):
            raise LTCGClusterError('ABI anchors need a dedicated .text$ section')
        anchor['address'] = _integer(anchor['address'], 'anchor address', minimum=image_base)
        anchor['size'] = _integer(anchor['size'], 'anchor size', minimum=1)
        generated = anchor.get('generated', False)
        if type(generated) is not bool:
            raise LTCGClusterError('generated anchor flag must be a boolean')
        if 'source' in anchor:
            anchor['_source'] = _string(anchor['source'], 'anchor source')
            if anchor['_source'] not in ordinary_by_source:
                raise LTCGClusterError('anchor source must name a declared ordinary source')
        if generated:
            if '_source' not in anchor:
                raise LTCGClusterError('ordinary generated anchors require their source')
            code_section = next(rename['to'] for rename in ordinary_by_source[anchor['_source']]['section_renames']
                                if rename['from'] == '.text$x')
            if anchor['section'] != code_section:
                raise LTCGClusterError('generated anchor section must be its ordinary source EH island')
        elif anchor['section'] in ordinary_sections:
            raise LTCGClusterError('ordinary EH code islands require generated anchors')
        if 'native_symbol_pattern' in anchor:
            if not generated or anchor['native_symbol_pattern'] != r'\$L[0-9]+':
                raise LTCGClusterError('only generated ordinary unwind anchors may select a native $L number')
        anchors.append(anchor)
    if len({item['symbol'] for item in anchors}) != len(anchors):
        raise LTCGClusterError('duplicate ABI anchor symbol')
    for section in {item['section'] for item in anchors}:
        members = [item for item in anchors if item['section'] == section]
        if len(members) > 1 and (not all(item.get('generated') for item in members)
                                or len({item.get('_source') for item in members}) != 1):
            raise LTCGClusterError('each ABI anchor needs a distinct complete contribution')
    anchor_roots = spec.get('anchor_roots', [])
    if not isinstance(anchor_roots, list) or any(not isinstance(item, str) for item in anchor_roots):
        raise LTCGClusterError('anchor_roots must be an array')
    if len(set(anchor_roots)) != len(anchor_roots):
        raise LTCGClusterError('anchor roots must be distinct')
    for symbol in anchor_roots:
        matches = [item for item in anchors if item['symbol'] == symbol
                   and not item.get('generated')]
        if len(matches) != 1:
            raise LTCGClusterError('anchor root must be a declared complete non-generated function')
        # A /GL helper can have a public entry just like an ordinary EH helper.
        # Rooting it preserves that boundary without selecting it as new code.
        # Native validation still checks its compiler origin, fixed address and
        # entire dedicated CODE contribution before any selected body is used.
    taken_symbols = {item['symbol'] for item in functions} | ({context['symbol']} if context else set())
    taken_sections = {item['section'] for item in functions} | ({context['section']} if context else set())
    if any(item['symbol'] in taken_symbols or item['section'] in taken_sections for item in anchors):
        raise LTCGClusterError('an ABI anchor must be distinct from the selected functions and context')
    contexts = [context] if context else []
    gaps = []
    if not isinstance(spec['gaps'], list):
        raise LTCGClusterError('gaps must be an array')
    for index, item in enumerate(spec['gaps']):
        keys = {'section', 'address', 'size'}
        gap = _fields(item, keys, keys, 'layout gap')
        gap['section'] = _string(gap['section'], 'gap section')
        if not re.fullmatch(r'\.text\$[a-zA-Z0-9_]+|\.rdata(?:\$[a-zA-Z0-9_]+)?', gap['section']):
            raise LTCGClusterError('layout gaps must use .text$ or .rdata sections')
        gap['address'] = _integer(gap['address'], 'gap address', minimum=image_base)
        gap['size'] = _integer(gap['size'], 'gap size', minimum=1)
        if gap['size'] > 0x100000:
            raise LTCGClusterError('layout gap exceeds the supported image')
        gap['symbol'] = f'_ltcg_gap_{index}'
        gaps.append(gap)
    code_sections = list({item['section'] for item in functions}) + list({item['section'] for item in contexts + anchors})
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
    # A compiler emits one pooled definition per distinct literal value
    # (``__real@`` plus its binary32 bit pattern).  When retail's own pool put
    # that literal at an address the cluster layout cannot reproduce, the
    # manifest aliases the literal to the retail address instead: the bindings
    # object defines it absolutely, the link tolerates the discarded pooled
    # copy, and validation proves the alias is the definition that survived.
    aliases = []
    raw_aliases = spec.get('constant_aliases', [])
    if not isinstance(raw_aliases, list):
        raise LTCGClusterError('constant_aliases must be an array')
    for item in raw_aliases:
        keys = {'symbol', 'address', 'value'}
        alias = _fields(item, keys, keys, 'constant alias')
        alias['symbol'] = _string(alias['symbol'], 'constant alias symbol')
        literal = re.fullmatch(r'__real@([0-9a-f]{8})', alias['symbol'])
        if not literal:
            raise LTCGClusterError('constant alias must name a compiler float literal')
        alias['address'] = _integer(alias['address'], 'constant alias address', minimum=image_base)
        if isinstance(alias['value'], bool) or not isinstance(alias['value'], (float, int)):
            raise LTCGClusterError('constant alias must be a scalar float32 value')
        try:
            bits = struct.unpack('<I', struct.pack('<f', alias['value']))[0]
        except (OverflowError, struct.error) as error:
            raise LTCGClusterError('constant alias is not representable as float32') from error
        if f'{bits:08x}' != literal.group(1):
            raise LTCGClusterError('constant alias value does not match its compiler literal name')
        alias['size'] = 4
        aliases.append(alias)
    data_aliases = []
    raw_data_aliases = spec.get('data_aliases', [])
    if not isinstance(raw_data_aliases, list):
        raise LTCGClusterError('data_aliases must be an array')
    for item in raw_data_aliases:
        keys = {'symbol', 'address', 'bytes'}
        alias = _fields(item, keys | {'reference_scope'}, keys, 'data alias')
        alias['symbol'] = _string(alias['symbol'], 'data alias symbol')
        alias['address'] = _integer(alias['address'], 'data alias address', minimum=image_base)
        scope = alias.get('reference_scope', 'selected')
        if not isinstance(scope, str) or scope not in ('selected', 'compiled_graph'):
            raise LTCGClusterError('data alias reference_scope must be selected or compiled_graph')
        if scope == 'compiled_graph' and alias['symbol'].startswith('__real@'):
            raise LTCGClusterError('compiler literal data aliases require selected reference scope')
        alias['reference_scope'] = scope
        if (not isinstance(alias['bytes'], str) or len(alias['bytes']) % 2
                or not re.fullmatch(r'[0-9a-fA-F]+', alias['bytes'])):
            raise LTCGClusterError('data alias bytes must be nonempty hexadecimal octets')
        alias['bytes_value'] = bytes.fromhex(alias['bytes'])
        alias['size'] = len(alias['bytes_value'])
        data_aliases.append(alias)
    native_data = []
    raw_data = spec.get('native_data', [])
    if not isinstance(raw_data, list):
        raise LTCGClusterError('native_data must be an array')
    for item in raw_data:
        keys = {'section', 'address', 'bytes', 'description'}
        datum = _fields(item, keys | ({'source'} if ordinary_sources else set()), keys, 'native compiler data')
        _string(datum['section'], 'native compiler data section')
        if 'source' in datum:
            datum['source'] = _string(datum['source'], 'native compiler data source')
            if datum['source'] not in ordinary_by_source:
                raise LTCGClusterError('native compiler data source must name a declared ordinary source')
            data_section = next(rename['to'] for rename in ordinary_by_source[datum['source']]['section_renames']
                                if rename['from'] == '.xdata$x')
            if datum['section'] != data_section:
                raise LTCGClusterError('ordinary native data must use its source EH data island')
        elif datum['section'] in ordinary_sections:
            raise LTCGClusterError('ordinary EH metadata requires its compiler source')
        if not exceptions or not re.fullmatch(r'\.xdata\$x|\.rdata\$[a-zA-Z0-9_]+', datum['section']):
            raise LTCGClusterError('native compiler data requires declared exception data sections')
        datum['address'] = _integer(datum['address'], 'native compiler data address', minimum=image_base)
        _string(datum['description'], 'native compiler data description')
        if (not isinstance(datum['bytes'], str) or len(datum['bytes']) % 2
                or not re.fullmatch(r'[0-9a-fA-F]+', datum['bytes'])):
            raise LTCGClusterError('native compiler data bytes must be nonempty hexadecimal octets')
        datum['bytes_value'] = bytes.fromhex(datum['bytes'])
        datum['size'] = len(datum['bytes_value'])
        native_data.append(datum)
    if len({item['section'] for item in native_data}) != len(native_data):
        raise LTCGClusterError('native compiler data contributions must be distinct')
    if any(item['section'] in {gap['section'] for gap in gaps} for item in native_data):
        raise LTCGClusterError('native compiler data overlaps layout section ownership')
    for ordinary in ordinary_sources:
        code_section, data_section = [next(rename['to'] for rename in ordinary['section_renames']
                                          if rename['from'] == name) for name in ('.text$x', '.xdata$x')]
        if (not any(item.get('_source') == ordinary['source'] and item.get('generated')
                    and item['section'] == code_section for item in anchors)
                or not any(item.get('source') == ordinary['source'] and item['section'] == data_section
                           for item in native_data)):
            raise LTCGClusterError('ordinary source requires a complete unwind group and metadata')
    if any(item.get('generated') for item in functions) and not any(item['section'] == '.xdata$x' for item in native_data):
        raise LTCGClusterError('generated unwind functions require their complete native exception table')
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
    all_symbols = [item['symbol'] for item in functions + gaps + constants + aliases + data_aliases + absolute + contexts + anchors]
    if len(set(all_symbols)) != len(all_symbols):
        raise LTCGClusterError('duplicate symbol across cluster code/context/layout/bindings')
    range_items = functions + gaps + constants + aliases + contexts + anchors + native_data
    ranges = sorted((item['address'], item['address'] + item['size']) for item in range_items)
    if any(end > 0x100000000 for _, end in ranges) or any(a[1] > b[0] for a, b in zip(ranges, ranges[1:])):
        raise LTCGClusterError('cluster code/context/layout extents overlap or overflow')
    # A data alias binds a symbol to a retail address without contributing
    # bytes, so it may lie inside an .rdata filler gap (the gap that positions
    # exception tables spans the whole read-only data); it must still stay
    # clear of every real contribution.
    solid_items = [item for item in range_items
                   if not (item in gaps and item['section'].startswith('.rdata'))]
    solid_ranges = [(item['address'], item['address'] + item['size']) for item in solid_items]
    for alias in data_aliases:
        if alias['address'] + alias['size'] > 0x100000000:
            raise LTCGClusterError('cluster code/context/layout extents overlap or overflow')
        if any(alias['address'] < end and start < alias['address'] + alias['size']
               for start, end in solid_ranges):
            raise LTCGClusterError('cluster code/context/layout extents overlap or overflow')
    for index, alias in enumerate(data_aliases):
        for other in data_aliases[index + 1:]:
            overlap = alias['address'] < other['address'] + other['size'] and other['address'] < alias['address'] + alias['size']
            if overlap and not (alias['address'] == other['address'] and alias['bytes_value'] == other['bytes_value']):
                raise LTCGClusterError('overlapping data aliases must describe identical bytes at one address')
    return {**spec, 'path': path, 'project': project, 'source_path': source,
            'source_paths': source_paths, 'source_names': source_names,
            'owned_includes': owned_includes, 'ownership_names': ownership_names,
            'compilation_paths': compilation_paths,
            'additional_source_paths': additional_paths, 'driver_path': driver,
            'ordinary_sources': ordinary_sources, 'ordinary_source_paths': ordinary_paths,
            'anchor_roots': anchor_roots,
            'header_paths': headers, 'included_source_paths': included_paths,
            'image_base': image_base, 'functions': functions,
            'context': context, 'gaps': gaps, 'constants': constants, 'absolute_symbols': absolute,
            'constant_aliases': aliases,
            'data_aliases': data_aliases,
            'exceptions': exceptions, 'native_data': native_data,
            'anchors': anchors,
            'entry_symbol': entry['symbol'], 'entry_address': entry['address'], 'calls': calls,
            'roots': roots,
            'regions': [dict(region) for region in owned]}


def load_clusters(project: Path, config: Mapping[str, Any], regions: Sequence[Mapping[str, Any]]) -> list[dict[str, Any]]:
    manifests = config.get('ltcg_clusters', [])
    if (not isinstance(manifests, list) or any(not isinstance(item, str) for item in manifests)
            or len(set(manifests)) != len(manifests)):
        raise LTCGClusterError('ltcg_clusters must be an array of distinct manifest paths')
    clusters = [load_cluster(project, manifest, regions) for manifest in manifests]
    if len({item['name'] for item in clusters}) != len(clusters):
        raise LTCGClusterError('clusters must have distinct names')
    source_names = [source for cluster in clusters for source in cluster['ownership_names']]
    if len(set(source_names)) != len(source_names):
        raise LTCGClusterError('clusters must have distinct maintained sources')
    return clusters


def _snapshot(spec: Mapping[str, Any]) -> dict[str, str]:
    paths = [spec['path'], *spec['source_paths'], *spec.get('compilation_paths', []), *spec['included_source_paths'], *spec['header_paths'],
             *spec.get('ordinary_source_paths', [])]
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


def _prepare_ordinary_object(source: Path, destination: Path,
                             renames: Sequence[Mapping[str, str]]) -> dict[str, Any]:
    """Rename only whole ordinary compiler EH section headers, never payloads."""
    original = _read_object(source)
    if original['machine'] != 0x14c:
        raise LTCGClusterError('ordinary source did not emit an x86 COFF object')
    data = bytearray(original['data'])
    changes = []
    for rename in renames:
        sections = [section for section in original['sections'] if section['name'] == rename['from']]
        if len(sections) != 1 or not sections[0]['raw']:
            raise LTCGClusterError('ordinary EH rename needs one complete nonempty source section')
        if any(section['name'] == rename['to'] for section in original['sections']):
            raise LTCGClusterError('ordinary EH rename destination already exists')
        section = sections[0]
        code = rename['from'] == '.text$x'
        if (bool(section['characteristics'] & 0x20) != code
                or bool(section['characteristics'] & 0x20000000) != code
                or not section['characteristics'] & 0x40000000
                or section['characteristics'] & 0x80000000):
            raise LTCGClusterError('ordinary EH section has the wrong code/data characteristics')
        offset = 20 + (section['number'] - 1) * 40
        data[offset:offset + 8] = rename['to'].encode('ascii').ljust(8, b'\0')
        changes.append({'section': section['number'], 'before': rename['from'],
                        'after': rename['to'], 'offset': offset, 'size': len(section['raw']),
                        'payload_sha256': sha(section['raw'])})
    destination.write_bytes(data)
    _verify_ordinary_object(source, destination, changes)
    return {'input_sha256': sha(original['data']), 'output_sha256': sha(data),
            'section_renames': changes, 'instruction_bytes_changed': 0,
            'relocation_bytes_changed': 0, 'symbol_bytes_changed': 0}


def _verify_ordinary_object(source: Path, destination: Path,
                            changes: Sequence[Mapping[str, Any]]) -> None:
    """Prove that every changed byte lies in an explicitly renamed name slot."""
    before, after = _read_object(source), _read_object(destination)
    if len(before['data']) != len(after['data']):
        raise LTCGClusterError('ordinary section rename changed the object extent')
    slots = [(item['offset'], item['offset'] + 8) for item in changes]
    if any(a != b and not any(start <= offset < end for start, end in slots)
           for offset, (a, b) in enumerate(zip(before['data'], after['data']))):
        raise LTCGClusterError('ordinary section rename changed bytes outside section names')
    expected_names = {item['section']: item['after'] for item in changes}
    if len(before['sections']) != len(after['sections']) or before['records'] != after['records']:
        raise LTCGClusterError('ordinary section rename changed symbols or section count')
    for old, new in zip(before['sections'], after['sections']):
        expected = {**old, 'name': expected_names.get(old['number'], old['name'])}
        if new != expected:
            raise LTCGClusterError('ordinary section rename changed payload, relocations or headers')


def _validate_ordinary_anchors(spec, pe, link_map, allowed_origins, ordinary_objects):
    """Validate unselected ordinary functions and every complete generated group."""
    from dataclasses import replace
    reports = []
    declared = set()
    for anchor in spec['anchors']:
        origin = (ordinary_objects[anchor['_source']].name
                  if '_source' in anchor else None)
        matches = [symbol for symbol in link_map.symbols
                   if ((re.fullmatch(anchor['native_symbol_pattern'], symbol.name)
                        if 'native_symbol_pattern' in anchor else symbol.name == anchor['symbol'])
                       and symbol.address == anchor['address']
                       and (symbol.origin == origin if origin else symbol.origin in allowed_origins))]
        if len(matches) != 1 or not matches[0].segment or 'f' not in matches[0].flags:
            raise LTCGClusterError('native ABI anchor address/origin differs: ' + anchor['symbol'])
        symbol = matches[0]
        if anchor.get('generated') and symbol.visibility != 'static':
            raise LTCGClusterError('ordinary unwind anchor must be a static compiler function')
        # Static compiler $L names can legitimately repeat in different TUs.
        bounded_map = replace(link_map, symbols=tuple(item for item in link_map.symbols
                              if item.name != symbol.name or item is symbol))
        report = extract_functions([{'name': anchor['name'], 'symbol': symbol.name,
                                     'visibility': 'either', 'size': anchor['size']}], bounded_map, pe)[0]
        contributions = [item for item in link_map.contributions if item.name == anchor['section']]
        generated = anchor.get('generated', False)
        if (len(contributions) != 1 or contributions[0].section_class != 'CODE'
                or contributions[0].segment != symbol.segment
                or (not generated and (contributions[0].start != symbol.offset
                                       or contributions[0].length != anchor['size']))
                or (generated and not contributions[0].start <= symbol.offset
                    < symbol.offset + anchor['size'] <= contributions[0].end)):
            raise LTCGClusterError('ABI anchor is not its entire declared compiler contribution: '
                                   + anchor['symbol'])
        body, _, _ = pe.read(anchor['address'], anchor['size'])
        reports.append({**report, 'symbol': anchor['symbol'], 'native_symbol': symbol.name,
                        'body': body, 'selected': False, 'recovered_code_bytes': 0, 'kind': 'anchor'})
        declared.add((symbol.name, symbol.address, symbol.origin))
    _validate_generated_contributions(spec['anchors'], reports, link_map)
    return reports, declared


def _validate_ordinary_contributions(spec, link_map, ordinary_objects):
    """Tie every separate ordinary EH island to its full fresh COFF section."""
    if set(ordinary_objects) != {item['source'] for item in spec['ordinary_sources']}:
        raise LTCGClusterError('ordinary compiler objects disagree with declared sources')
    reports = []
    for source in spec['ordinary_sources']:
        path = ordinary_objects[source['source']]
        _require_fresh_output(path)
        obj = _read_object(path)
        for rename in source['section_renames']:
            sections = [item for item in obj['sections'] if item['name'] == rename['to']]
            contributions = [item for item in link_map.contributions if item.name == rename['to']]
            if (len(sections) != 1 or len(contributions) != 1
                    or contributions[0].length != len(sections[0]['raw'])
                    or contributions[0].section_class != ('CODE' if rename['from'] == '.text$x' else 'DATA')):
                raise LTCGClusterError('ordinary EH island is not its complete compiler input contribution')
            if rename['from'] == '.xdata$x':
                declarations = [item for item in spec['native_data']
                                if item['section'] == rename['to'] and item.get('source') == source['source']]
                if len(declarations) != 1 or declarations[0]['size'] != len(sections[0]['raw']):
                    raise LTCGClusterError('ordinary unwind group requires its complete source-bound metadata')
            else:
                declarations = [item for item in spec['anchors']
                                if item['section'] == rename['to'] and item.get('_source') == source['source']
                                and item.get('generated')]
                if not declarations:
                    raise LTCGClusterError('ordinary compiler unwind group is undeclared')
            reports.append({'source': source['source'], 'origin': path.name, 'section': rename['to'],
                            'size': len(sections[0]['raw']), 'input_object_sha256': sha(obj['data']),
                            'selected': False, 'recovered_code_bytes': 0})
        if any(item['name'].startswith('.xdata$') for item in obj['sections']):
            raise LTCGClusterError('ordinary compiler emitted an unaccounted exception table')
    return reports


def validate_native_output(spec: Mapping[str, Any], executable: Path, map_path: Path,
                           origins: Sequence[str] | str,
                           source_origins: Mapping[str, str] | None = None,
                           ordinary_objects: Mapping[str, Path] | None = None
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
    ordinary = spec.get('ordinary_sources', [])
    ordinary_reports = (_validate_ordinary_contributions(spec, link_map, ordinary_objects or {})
                        if ordinary else [])
    native_keys = set()
    function_reports = []
    compiled_bodies = []
    graph_references = any(alias.get('reference_scope') == 'compiled_graph'
                          for alias in spec['data_aliases'])
    native_symbols = set()
    contexts = [{**spec['context'], 'name': 'compiler context'}] if spec['context'] else []
    for function in [*spec['functions'], *contexts]:
        map_symbol = function['symbol']
        generated = function.get('generated', False)
        if 'native_symbol_pattern' in function:
            matches = [item for item in link_map.symbols
                       if re.fullmatch(function['native_symbol_pattern'], item.name)
                       and item.address == function['address']
                       and (not ordinary or item.origin == 'CIL library: CIL module')]
            if len(matches) != 1:
                raise LTCGClusterError('generated unwind function has no unique native symbol: ' + function['symbol'])
            map_symbol = matches[0].name
        is_context = bool(spec['context'] and function['symbol'] == spec['context']['symbol'])
        if is_context:
            exact = [item for item in link_map.symbols if item.name == map_symbol]
            c_decorated = [item for item in link_map.symbols if item.name == '_' + map_symbol]
            if not exact and len(c_decorated) == 1:
                map_symbol = '_' + map_symbol
        extraction_map = link_map
        if ordinary and generated:
            from dataclasses import replace
            extraction_map = replace(link_map, symbols=tuple(item for item in link_map.symbols
                                     if item.name != map_symbol
                                     or (item.address == function['address']
                                         and item.origin == 'CIL library: CIL module')))
        reports = extract_functions([{'name': function['name'], 'symbol': map_symbol,
                                      'visibility': 'either', 'size': function['size']}], extraction_map, pe)
        report = reports[0]
        origin_valid = report['map_origin'] in allowed_origins
        if generated:
            origin_valid = (report['map_origin'] == 'CIL library: CIL module'
                            and report['visibility'] == 'static')
        if int(report['address'], 0) != function['address'] or not origin_valid:
            raise LTCGClusterError('native function address or compiler origin differs: ' + function['symbol'])
        if (source_origins is not None and not is_context and not generated
                and report['map_origin'] != source_origins[function['_source']]):
            raise LTCGClusterError('native function was not emitted by its declared source: ' + function['symbol'])
        contributions = [item for item in link_map.contributions if item.name == function['section']]
        if (len(contributions) != 1 or contributions[0].section_class != 'CODE'
                or contributions[0].segment != int(report['map_segment'], 16)
                or (not generated and (contributions[0].start != int(report['map_offset'], 0)
                                       or contributions[0].length != function['size']))
                or (generated and not contributions[0].start <= int(report['map_offset'], 0)
                    < int(report['map_offset'], 0) + function['size'] <= contributions[0].end)):
            raise LTCGClusterError('function is not its entire declared compiler contribution: ' + function['symbol'])
        native_symbols.add(map_symbol)
        native_keys.add((map_symbol, int(report['address'], 0), report['map_origin']))
        body, _, _ = pe.read(function['address'], function['size'])
        compiled_bodies.append({**report, 'body': body, 'symbol': function['symbol'],
                                'selected': not is_context,
                                'kind': 'context' if is_context else 'function'})
        if not is_context:
            function_reports.append({**report, 'symbol': function['symbol'],
                                     'native_symbol': map_symbol, 'body': body,
                                     'actual_abi': function['actual_abi']})
    _validate_generated_contributions(spec['functions'], function_reports, link_map)
    native_data_reports = []
    for datum in spec.get('native_data', []):
        contributions = [item for item in link_map.contributions if item.name == datum['section']]
        body, section, offset = pe.read(datum['address'], datum['size'])
        if (len(contributions) != 1 or contributions[0].section_class != 'DATA'
                or section.name != '.rdata'
                or contributions[0].start != datum['address'] - section.address
                or contributions[0].length != datum['size']
                or body != datum['bytes_value']):
            raise LTCGClusterError('native compiler data address, complete extent or bytes differ: ' + datum['section'])
        native_data_reports.append({'section': datum['section'], 'address': f"0x{datum['address']:08X}",
                                    'size': datum['size'], 'sha256': sha(body), 'verified': True,
                                    'selected': False, 'file_offset': offset})
    declared_tables = {item['section'] for item in spec.get('native_data', [])}
    if any(item.name.startswith('.xdata$') and item.name not in declared_tables
           for item in link_map.contributions):
        raise LTCGClusterError('native compiler emitted an undeclared exception table')
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
    for alias in spec['constant_aliases']:
        # The absolute binding must be the definition that survived: a single
        # segment-0 symbol at the retail address, with no pooled copy left.
        matches = [symbol for symbol in link_map.symbols if symbol.name == alias['symbol']]
        if len(matches) != 1 or matches[0].segment != 0 or matches[0].address != alias['address']:
            raise LTCGClusterError('native constant alias is not bound to its declared address: ' + alias['symbol'])
        encoded = struct.pack('<I', alias['address'])
        if not any(encoded in item['body'] for item in function_reports):
            raise LTCGClusterError('constant alias is not referenced by any selected body: ' + alias['symbol'])
    unselected_reports = []
    if ordinary:
        unselected_reports, anchor_keys = _validate_ordinary_anchors(
            spec, pe, link_map, allowed_origins, ordinary_objects)
        compiled_bodies.extend(unselected_reports)
        native_keys.update(anchor_keys)
    else:
        for anchor in spec.get('anchors', []):
            matches = [symbol for symbol in link_map.symbols if symbol.name == anchor['symbol']]
            if len(matches) != 1 or matches[0].address != anchor['address'] or 'f' not in matches[0].flags:
                raise LTCGClusterError('native ABI anchor address/origin differs: ' + anchor['symbol'])
            if anchor['symbol'] in spec['anchor_roots'] and matches[0].origin not in allowed_origins:
                raise LTCGClusterError('rooted ABI anchor is not from a compiled input: ' + anchor['symbol'])
            contributions = [item for item in link_map.contributions if item.name == anchor['section']]
            if (len(contributions) != 1 or contributions[0].section_class != 'CODE'
                    or contributions[0].segment != matches[0].segment
                    or contributions[0].start != matches[0].offset
                    or contributions[0].length != anchor['size']):
                raise LTCGClusterError('ABI anchor is not its entire declared compiler contribution: '
                                       + anchor['symbol'])
            if any(matches[0].address == int(item['address'], 0) for item in function_reports):
                raise LTCGClusterError('ABI anchor overlaps a selected recovered function: ' + anchor['symbol'])
            if graph_references:
                if matches[0].origin not in allowed_origins:
                    raise LTCGClusterError('native ABI anchor address/origin differs: ' + anchor['symbol'])
                report = extract_functions([{'name': anchor['name'], 'symbol': anchor['symbol'],
                                             'visibility': 'either', 'size': anchor['size']}], link_map, pe)[0]
                body, _, _ = pe.read(anchor['address'], anchor['size'])
                compiled_bodies.append({**report, 'body': body, 'selected': False, 'kind': 'anchor'})
    data_alias_reports = []
    for alias in spec['data_aliases']:
        matches = [symbol for symbol in link_map.symbols if symbol.name == alias['symbol']]
        if len(matches) != 1 or matches[0].segment != 0 or matches[0].address != alias['address']:
            raise LTCGClusterError('native data alias is not bound to its declared address: ' + alias['symbol'])
        scope = alias.get('reference_scope', 'selected')
        bodies = compiled_bodies if scope == 'compiled_graph' else function_reports
        encoded = struct.pack('<I', alias['address'])
        references = [item for item in bodies if encoded in item['body']]
        if not references:
            label = 'compiled graph' if scope == 'compiled_graph' else 'selected body'
            raise LTCGClusterError('data alias is not referenced by any ' + label + ': ' + alias['symbol'])
        data_alias_reports.append({'symbol': alias['symbol'], 'reference_scope': scope,
                                   'references': [{key: item[key] for key in
                                                   ('symbol', 'address', 'size', 'map_origin')}
                                                  | {'selected': item.get('selected', True),
                                                     'kind': item.get('kind', 'function')}
                                                  for item in references]})
    declared = native_symbols
    declared |= {item['symbol'] for item in spec.get('anchors', [])}
    declared |= {item['native_symbol'] for item in unselected_reports}
    if spec['context']:
        context_symbol = spec['context']['symbol']
        declared |= {context_symbol, '_' + context_symbol}
    if ordinary and any('f' in symbol.flags and symbol.segment
                        and (symbol.name, symbol.address, symbol.origin) not in native_keys
                        for symbol in link_map.symbols):
        raise LTCGClusterError('native compiler emitted an undeclared function or origin')
    if any('f' in symbol.flags and symbol.segment and symbol.name not in declared for symbol in link_map.symbols):
        raise LTCGClusterError('native compiler emitted an undeclared function')
    calls = validate_internal_calls(spec['calls'], function_reports)
    return function_reports, {'pe_sha256': sha(pe.data), 'map_sha256': sha(map_path.read_bytes()),
                              'entry_address': f'0x{pe.entry:08X}', 'image_base': f'0x{pe.image_base:08X}',
                              'internal_calls': calls, 'native_data': native_data_reports,
                              'data_alias_references': data_alias_reports,
                              'ordinary_contributions': ordinary_reports,
                              'unselected_functions': [{key: value for key, value in item.items()
                                                        if key not in {'body', 'bytes_hex'}}
                                                       for item in unselected_reports]}


def _validate_generated_contributions(functions, reports, link_map):
    """Every byte of a compiler .text$x contribution must be accounted for.

    C++ unwinding emits several static functions in one contribution. Select
    each bounded function, then require their union to equal that entire
    contribution. This does not permit slicing arbitrary ordinary code.
    """
    by_symbol = {item['symbol']: item for item in reports}
    sections = {item['section'] for item in functions if item.get('generated')}
    for section in sections:
        members = [by_symbol[item['symbol']] for item in functions
                   if item.get('generated') and item['section'] == section]
        contributions = [item for item in link_map.contributions if item.name == section]
        if len(contributions) != 1:
            raise LTCGClusterError('generated functions have no unique compiler contribution')
        contribution = contributions[0]
        cursor = contribution.start
        for member in sorted(members, key=lambda item: int(item['map_offset'], 0)):
            if int(member['map_segment'], 16) != contribution.segment or int(member['map_offset'], 0) != cursor:
                raise LTCGClusterError('generated functions omit or overlap compiler contribution bytes')
            cursor += member['size']
        if cursor != contribution.end:
            raise LTCGClusterError('generated functions omit compiler contribution suffix bytes')


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
    permitted = {path.resolve() for path in [*spec['source_paths'], *spec.get('compilation_paths', []), *spec['included_source_paths'], *spec['header_paths'],
                                           *spec.get('ordinary_source_paths', [])]}
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


DUPLICATE_DEFINITION = re.compile(r'(?:warning|error) LNK(?:4006|2005): (?:(?:"[^"]+" )?\(([^)]+)\)|(\S+)) already defined')


def _verify_duplicates(log: str, aliases: Sequence[Mapping[str, Any]]) -> list[dict[str, Any]]:
    """Require every tolerated duplicate definition to be a declared alias.

    ``/FORCE:MULTIPLE`` is passed only for clusters that rebind a compiler
    literal to its retail address.  LINK reports each tolerated duplicate as
    "already defined in a previous module; second definition ignored"; any
    other duplicate definition would mean the forced link silently accepted an
    unintended conflict, and a declared alias without that report would mean
    no pooled definition existed to rebind.
    """
    declared = {alias['symbol']: alias for alias in aliases}
    tolerated, seen = [], set()
    for line in log.splitlines():
        match = DUPLICATE_DEFINITION.search(line)
        if match is None:
            continue
        symbol = match.group(1) or match.group(2)
        if symbol not in declared:
            raise LTCGClusterError('linker tolerated an undeclared duplicate definition: ' + symbol)
        tolerated.append({'symbol': symbol, 'address': f"0x{declared[symbol]['address']:08X}",
                          'message': line.strip()})
        seen.add(symbol)
    missing = [alias['symbol'] for alias in aliases if alias['symbol'] not in seen]
    if missing:
        raise LTCGClusterError('declared constant alias has no pooled definition to rebind: '
                               + ', '.join(missing))
    return tolerated


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
    # Earlier builds' work directories are never read again; only this build's is reported.
    for stale in output.glob('native-*'):
        shutil.rmtree(stale, ignore_errors=True)
    work = Path(tempfile.mkdtemp(prefix='native-', dir=output))
    env = compiler_environment(toolkit)
    compiler, linker, tool_hashes = _verify_toolchain(toolkit, 'wine', env, work)
    source = work / 'layout.cpp'
    source.write_text(_padding_source(spec['gaps']))
    _absolute_object(work / 'bindings.obj', [
        *spec['absolute_symbols'],
        *[{'symbol': alias['symbol'], 'address': alias['address'], 'kind': 'data',
           'coff_value': alias['address']} for alias in [*spec['constant_aliases'], *spec['data_aliases']]]])
    compile_commands = []
    include_logs = []
    if spec['context']:
        gl_inputs = [(spec['driver_path'], 'cluster.obj'),
                     *[(path, f'source_{index:03d}.obj')
                       for index, path in enumerate(spec.get('compilation_paths', spec['source_paths'])[1:])]]
        direct_sources = [spec['driver_path'], *spec.get('compilation_paths', spec['source_paths'])[1:]]
    else:
        gl_inputs = [(path, f'source_{index:03d}.obj')
                     for index, path in enumerate(spec.get('compilation_paths', spec['source_paths']))]
        direct_sources = spec.get('compilation_paths', spec['source_paths'])
    ordinary_inputs = [(path, f'ordinary_{index:03d}-original.obj')
                       for index, path in enumerate(spec.get('ordinary_source_paths', []))]
    direct_sources = [*direct_sources, *spec.get('ordinary_source_paths', [])]
    for input_path, object_name, extra in [
        *[(path, name, ['/GL', '/showIncludes']) for path, name in gl_inputs],
        *[(path, name, ['/showIncludes']) for path, name in ordinary_inputs],
        (source, 'layout-original.obj', []),
    ]:
        obj = work / object_name
        command = ['wine', str(compiler), *flags,
                   *(['/EHsc'] if spec.get('exceptions') and object_name != 'layout-original.obj' else []),
                   *extra, '/I' + winpath(spec['project'] / 'include'),
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
    ordinary_objects = {}
    ordinary_preparations = []
    for index, item in enumerate(spec.get('ordinary_sources', [])):
        obj = work / f'ordinary_{index:03d}.obj'
        preparation = _prepare_ordinary_object(work / ordinary_inputs[index][1], obj, item['section_renames'])
        ordinary_objects[item['source']] = obj
        ordinary_preparations.append({'source': item['source'], 'object': str(obj), **preparation})
    executable, map_path = work / 'cluster.exe', work / 'cluster.map'
    # LINK decorates an x86 C entry name supplied with /ENTRY.  The manifest
    # stores its COFF spelling (leading underscore), so remove that underscore
    # for this option while retaining the decorated name for symbol checks.
    entry_option = spec['entry_symbol'][1:] if spec['entry_symbol'].startswith('_') else spec['entry_symbol']
    link_command = ['wine', str(linker), '/nologo', '/LTCG', '/MACHINE:X86', '/BASE:0x400000',
                    '/FILEALIGN:512', '/SUBSYSTEM:WINDOWS', '/ENTRY:' + entry_option,
                    '/FIXED', '/INCREMENTAL:NO', '/NODEFAULTLIB', '/OPT:REF', '/OPT:NOICF',
                    *(['/SAFESEH:NO'] if spec.get('exceptions') else []),
                    # A constant alias replaces a compiler-pooled definition
                    # with the absolute binding; /FORCE:MULTIPLE keeps that
                    # conflict from being fatal.  _verify_duplicates then
                    # requires every tolerated duplicate to be a declared
                    # alias, so no undeclared duplicate can pass.
                    *(['/FORCE:MULTIPLE'] if spec['constant_aliases'] or spec['data_aliases'] else []),
                    *['/INCLUDE:' + gap['symbol'] for gap in spec['gaps']],
                    # /ENTRY roots the context or selected real entry. Both
                    # schema variants may also contain independently reachable
                    # functions; retain only explicitly declared roots so
                    # LINK does not discard their complete contributions.
                    *['/INCLUDE:' + symbol for symbol in [*spec.get('roots', []), *spec.get('anchor_roots', [])]],
                    '/OUT:' + winpath(executable), '/MAP:' + winpath(map_path),
                    *[winpath(work / name) for _, name in gl_inputs],
                    *[winpath(path) for path in ordinary_objects.values()],
                    winpath(work / 'layout.obj'), winpath(work / 'bindings.obj')]
    link = _run_logged(link_command, env, work, work / 'link.log', 300)
    duplicates = _verify_duplicates(link.stdout + link.stderr, [*spec['constant_aliases'], *spec['data_aliases']])
    _verify_snapshot(inputs)
    current_tools = toolchain_hashes(toolkit, TOOL_FILES)
    if any(tool_hashes['bin/' + name] != digest for name, digest in current_tools.items()):
        raise LTCGClusterError('compiler/linker changed during the native build')
    source_origins = dict(zip(spec['source_names'], [name for _, name in gl_inputs]))
    source_origins.update({name: source_origins[owner]
                           for name, owner in spec.get('owned_includes', {}).items()})
    functions, native = validate_native_output(
        spec, executable, map_path, [name for _, name in gl_inputs],
        None if spec['context'] else source_origins,
        ordinary_objects)
    normalization = export_bodies(destination, functions)
    report = {'schema_version': spec['schema_version'], 'name': spec['name'], 'compiler_kind': 'native-ltcg',
              'source': spec['source'], 'sources': spec['source_names'],
              'roots': spec.get('roots', []), 'anchor_roots': spec.get('anchor_roots', []),
              'ordinary_sources': ordinary_preparations,
              'driver': spec.get('driver'), 'layout': str(spec['path']),
              'input_sha256': inputs, 'compiler_includes': includes, 'tool_sha256': tool_hashes,
              'compile_commands': compile_commands, 'link_command': link_command,
              'native_executable': str(executable), 'native_map': str(map_path), **native,
              'functions': [{key: value for key, value in item.items()
                             if key not in {'body', '_source'}} for item in functions],
              'compiler_context': ({**spec['context'], 'selected': False, 'recovered_code_bytes': 0}
                                   if spec['context'] else None),
              'layout_gaps': layout_report, 'absolute_symbols': spec['absolute_symbols'],
              'constant_aliases': spec['constant_aliases'],
              'data_aliases': [{key: value for key, value in alias.items() if key != 'bytes_value'}
                               for alias in spec['data_aliases']],
              'duplicate_definitions': duplicates,
              'normalization': normalization, 'instruction_bytes_changed': 0, 'masked_bytes': 0,
              'reference_bytes_used_for_build': False}
    report_path.write_text(json.dumps(report, indent=2) + '\n')
    return {'source': spec['source'], 'object': str(destination), 'compiler_kind': 'native-ltcg',
            'compiler_translation_unit_count': len(compile_commands), 'command': compile_commands[0]['command'],
            'source_sha256': inputs[str(spec['source_path'])], 'normalization': normalization,
            'native_report': str(report_path), 'native_report_sha256': sha(report_path.read_bytes()),
            'native_build': report}
