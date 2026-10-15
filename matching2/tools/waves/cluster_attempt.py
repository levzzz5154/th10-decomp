#!/usr/bin/env python3
"""Drive a variant sweep for one region through the native-LTCG cluster path.

Written while landing 0x0042C850, 0x00449590, 0x004495E0 and 0x00449670; the
procedure it automates is in `recovery_notes/ltcg_cluster_landing_procedure.md`
and the pitfalls in `recovery_notes/ltcg_cluster_lessons.md`. Intended to run
against a *throwaway copy* of the project (`cp -a matching2/msvc
/tmp/<name>/msvc`) so the maintained tree is never left broken; point `PROJECT`
and `BUILD` at that copy before calling `attempt`.

What it does per variant: writes the source, resets the layout to the declared
sizes (so an adaptive fix cannot leak between variants), registers the cluster
through `register_cluster.py`, builds it, and compares the emitted bytes against
the retail image. On failure it reads back what the compiler emitted - function
size, context size and context address - rewrites the layout accordingly and
retries, which is what makes a layout converge without hand-editing. Registration
and the source file are rolled back when nothing lands.

Usage from a driver script next to the copy:

    import cluster_attempt as ca
    ca.PROJECT = Path('/tmp/<name>/msvc')
    ca.BUILD = Path('/tmp/<name>/ltcg')
    ca.attempt(name=..., source_rel=..., address=..., size=..., symbol=...,
               fn_name=..., context_symbol=..., context_text=..., header=...,
               variants={'model': None})

Remembers four things the hard way: the model needs `#pragma code_seg` and
`__declspec(noinline)`, a free function needs an explicit convention under /Gz,
the layout's context symbol must be the decorated name, and a gap must never be
zero (the synthesised padding source then fails with C2466).
"""
from __future__ import annotations

import json
import re
import shutil
import subprocess
import sys
from pathlib import Path

ROOT = Path('/home/levzzz/Games/th10Decomp')
sys.path.insert(0, str(ROOT))
from matching2.tools.common.pe import PEImage
from matching2.tools.matching.ltcg_cluster import (LTCGClusterError,
                                                   build_cluster, load_cluster)
from matching2.tools.matching.ltcg_semantic import LTCGSemanticError
from matching2.tools.matching.probe import DEFAULT_TOOLKIT, load_manifest, load_oracle

PROJECT = ROOT / 'matching2/msvc'
BUILD = Path('/tmp/cluster-attempts')


from matching2.tools.common.project_paths import project_support
def oracle_bytes(address, size):
    config = load_manifest(project_support(PROJECT, 'regions.json'))
    oracle = load_oracle(ROOT / 'matching2/build/oracle/th10.exe', config)
    start = int(config['text_start'], 0)
    return bytes(oracle[address - start:address - start + size])


def _map_offset(build_dir, section):
    """Section-relative offset of a section in the link map, or None."""
    maps = sorted(build_dir.glob('**/cluster.map'))
    if not maps:
        return None
    match = re.search(r'[0-9A-Fa-f]{4}:([0-9A-Fa-f]{8})\s+[0-9A-Fa-f]{8}H\s+' + re.escape(section) + r'\b', maps[-1].read_text())
    return int(match.group(1), 16) if match else None


def _map_section(build_dir, section):
    """Size of a section as the link map reports it, or None.

    The map prints `seg:offset  LENGTHH  section`, so the size is the second
    hex field after the address. Capturing the first field here fed the section
    offset back as a size, which silently exhausted the adaptive retries.
    """
    maps = sorted(build_dir.glob('**/cluster.map'))
    if not maps:
        return None
    match = re.search(r'[0-9A-Fa-f]{4}:[0-9A-Fa-f]{8}\s+([0-9A-Fa-f]{8})H\s+' + re.escape(section) + r'\b', maps[-1].read_text())
    return int(match.group(1), 16) if match else None


def _register(layout_rel, unregister=False):
    # --project is required: the registration resolves the layout against the
    # manifest's own directory, so without it a sweep against a throwaway copy
    # still writes the maintained manifest and then fails to find its layout.
    command = [sys.executable, str(ROOT / 'matching2/tools/waves/register_cluster.py'),
               '--project', str(PROJECT), '--layout', layout_rel, '--apply']
    if unregister:
        command.insert(-1, '--unregister')
    return subprocess.run(command, capture_output=True, text=True, cwd=PROJECT, timeout=120)


def attempt(name, source_rel, address, size, symbol, fn_name, context_symbol,
            context_text, context_size=40, variants=None, header='', expect=None,
            keep=False, absolute_symbols=None, roots=None):
    expected = expect if expect is not None else oracle_bytes(address, size)
    source_path = PROJECT / source_rel
    driver_path = PROJECT / f'layout/ltcg/{name}_context.cpp'
    layout_path = PROJECT / f'layout/ltcg/{name}.json'
    layout_rel = f'layout/ltcg/{name}.json'
    original_source = source_path.read_text()
    driver_path.write_text(context_text)

    def write_layout(fn_size, ctx_size, ctx_address):
        layout = {
            'schema_version': 1,
            'name': name,
            'source': source_rel,
            'driver': f'layout/ltcg/{name}_context.cpp',
            'headers': [],
            'image_base': '0x00400000',
            'description': f'{fn_name} compiled with native LTCG so the argument arrives in EAX.',
            'functions': [{
                'name': fn_name, 'symbol': symbol, 'section': '.text$01accessor',
                'address': f'0x{address:08X}', 'size': fn_size,
                'actual_abi': 'argument in EAX',
            }],
            'context': {
                'symbol': context_symbol, 'section': '.text$03context',
                'address': f'0x{ctx_address:08X}', 'size': ctx_size,
                'description': 'Synthetic array-walking caller that establishes the observed '
                               'register convention; not recovered game code.',
            },
            'gaps': [
                {'section': '.text$00layout', 'address': '0x00401000', 'size': address - 0x401000},
                {'section': '.text$02layout', 'address': f'0x{address + fn_size:08X}',
                 'size': max(0, ctx_address - (address + fn_size))},
            ],
            'constants': [],
            'roots': list(roots or []),
            'absolute_symbols': list(absolute_symbols or []),
        }
        layout_path.write_text(json.dumps(layout, indent=2) + '\n')

    # leave a positive gap between the function and the synthetic context
    write_layout(size, context_size, (address + size + 31) & ~15)
    registration = _register(layout_rel)
    if registration.returncode != 0:
        print('registration failed:', (registration.stdout + registration.stderr).strip()[:160])
        source_path.write_text(original_source)
        layout_path.unlink(missing_ok=True)
        driver_path.unlink(missing_ok=True)
        return False, None

    bodies = variants or {'body': None}
    landed = False
    try:
        for body_name, body in bodies.items():
            source_path.write_text(header + (body or ''))
            fn_size, ctx_size = size, context_size
            ctx_address = (address + fn_size + 31) & ~15
            # restore the layout file to the declared sizes for this variant, since
            # the adaptive retries rewrite it with whatever the compiler emitted
            write_layout(size, context_size, (address + size + 31) & ~15)
            for attempt_index in range(4):
                config = load_manifest(project_support(PROJECT, 'regions.json'))
                if attempt_index == 0:
                    spec = load_cluster(PROJECT, layout_rel, config['regions'])
                spec['functions'][0]['size'] = fn_size
                spec['gaps'][1]['address'] = address + fn_size
                spec['gaps'][1]['size'] = max(16, ctx_address - (address + fn_size))
                spec['context']['address'] = ctx_address
                spec['context']['size'] = ctx_size
                build_dir = BUILD / f'{name}-{body_name}-{attempt_index}'
                shutil.rmtree(build_dir, ignore_errors=True)
                try:
                    result = build_cluster(spec, DEFAULT_TOOLKIT.resolve(), build_dir,
                                           config['flags'])
                except (LTCGClusterError, LTCGSemanticError) as error:
                    seen = _map_section(build_dir, '.text$01accessor')
                    ctx = _map_section(build_dir, '.text$03context')
                    ctx_offset = _map_offset(build_dir, '.text$03context')
                    if ctx_offset is not None:
                        emitted_address = 0x401000 + ctx_offset
                        if emitted_address != ctx_address:
                            ctx_address = emitted_address
                            write_layout(fn_size, ctx_size, ctx_address)
                            continue
                    if ctx is not None and ctx != ctx_size:
                        ctx_size = ctx
                        write_layout(fn_size, ctx_size, ctx_address)
                        continue
                    if seen is not None and seen != fn_size:
                        fn_size = seen
                        ctx_address = max((address + fn_size + 15) & ~15, ctx_address)
                        write_layout(fn_size, ctx_size, ctx_address)
                        continue
                    print(f'{name:34s} {body_name:12s} ERR size={seen} ctx={ctx} '
                          f'{str(error)[:60]}')
                    break
                exe = Path(result['native_build']['native_executable'])
                pe = PEImage(exe.read_bytes())
                compiled = pe.read(address, fn_size)
                compare = expected[:max(len(compiled), len(expected))]
                differing = sum(1 for index in range(len(compare))
                                if (compiled[index] if index < len(compiled) else None)
                                != expected[index])
                first = next((index for index in range(len(compare))
                              if (compiled[index] if index < len(compiled) else None)
                              != expected[index]), None)
                detail = f'len={len(compiled)} (want {size}) different={differing}'
                if first is not None:
                    detail += (f' first={first:#x}'
                               f' got {compiled[first]:02x} want {expected[first]:02x}')
                print(f'{name:34s} {body_name:12s} {detail}')
                if differing == 0 and len(compiled) == size:
                    landed = True
                break
    finally:
        if not landed and not keep:
            _register(layout_rel, unregister=True)
            source_path.write_text(original_source)
            layout_path.unlink(missing_ok=True)
            driver_path.unlink(missing_ok=True)
    return landed, None
