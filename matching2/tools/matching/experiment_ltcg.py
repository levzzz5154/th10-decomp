#!/usr/bin/env python3
"""Reproduce the worker caller/callee LTCG experiment with positive/negative controls.

Uses the maintained schema-2 cluster and the production build path. Controls
change only /GL participation, translation-unit boundaries, or ABI visibility.
None of the executables is run; the retail image is a post-build byte oracle.
"""
from __future__ import annotations

import sys
from pathlib import Path

if __package__ in (None, ''):
    sys.path.insert(0, str(Path(__file__).resolve().parents[3]))

import argparse
import json
import shutil
import subprocess
import tempfile

from matching2.tools.common.process import sha
from matching2.tools.common.wine import DEFAULT_TOOLKIT, compiler_environment, winpath
from matching2.tools.matching.ltcg_cluster import (
    build_cluster, load_cluster, _snapshot, _verify_snapshot,
)
from matching2.tools.matching.ltcg_semantic import (
    PEImage, _run_logged, extract_functions, parse_map, validate_map_pe,
)
from matching2.tools.matching.probe import DEFAULT_PROJECT, default_oracle, load_oracle

MANIFEST = 'layout/ltcg/platform_worker_shutdown.json'


def measure(spec, executable, map_path, oracle, text_start):
    pe = PEImage.from_path(executable)
    link_map = parse_map(map_path.read_text())
    validate_map_pe(link_map, pe)
    functions = []
    for function in spec['functions']:
        contributions = [item for item in link_map.contributions if item.name == function['section']]
        if len(contributions) != 1:
            raise ValueError('missing/ambiguous function contribution: ' + function['symbol'])
        measured = extract_functions([{
            'name': function['name'], 'symbol': function['symbol'],
            'visibility': 'either', 'size': contributions[0].length,
        }], link_map, pe)[0]
        address = int(measured['address'], 0)
        body, _, _ = pe.read(address, measured['size'])
        start = function['address'] - text_start
        expected = oracle[start:start + function['size']]
        different = sum(a != b for a, b in zip(body, expected)) + abs(len(body) - len(expected))
        functions.append({**measured, 'bytes': body.hex(),
                          'expected_address': f"0x{function['address']:08X}",
                          'expected_size': function['size'], 'expected_sha256': sha(expected),
                          'different_bytes': different,
                          'exact': address == function['address'] and body == expected})
    # Keep a compact, address-aligned disassembly alongside every measured PE.
    first = min(int(item['address'], 0) for item in functions)
    last = max(int(item['address'], 0) + item['size'] for item in functions)
    assembly = subprocess.check_output([
        'objdump', '-d', '-Mintel', f'--start-address={first}', f'--stop-address={last}',
        str(executable),
    ], text=True)
    (executable.parent / 'disassembly.txt').write_text(assembly)
    return {'functions': functions, 'exact': all(item['exact'] for item in functions),
            'executable': str(executable), 'map': str(map_path), 'pe_sha256': sha(pe.data)}


def control(name, spec, production, output, toolkit):
    """Replay production commands in a fresh directory with one controlled change."""
    work = output / name
    work.mkdir()
    native_dir = Path(production['native_executable']).parent
    native_windows, work_windows = winpath(native_dir), winpath(work)
    env = compiler_environment(toolkit)

    def relocate(command):
        return [argument.replace(native_windows, work_windows) for argument in command]

    # These two objects contain only zero layout gaps and absolute symbol metadata.
    for filename in ('layout.obj', 'bindings.obj'):
        shutil.copyfile(native_dir / filename, work / filename)
    commands = []
    compile_commands = production['compile_commands'][:-1]
    for index, item in enumerate(compile_commands):
        command = relocate(item['command'])
        if (name == 'ordinary' or name == 'native_caller' and index == 0
                or name == 'native_callee' and index == 1):
            command.remove('/GL')
        if name == 'unity_gl':
            if index:
                continue
            unity = work / 'unity.cpp'
            unity.write_text(''.join('#include "' + winpath(path).replace('\\', '/') + '"\n'
                                     for path in spec['source_paths']))
            command[-1] = winpath(unity)
        _run_logged(command, env, work, work / f'compile_{index}.log', 180)
        commands.append(command)
    link_command = relocate(production['link_command'])
    if name == 'unity_gl':
        link_command.remove(winpath(work / 'source_001.obj'))
    elif name == 'exported_callee':
        link_command.append('/EXPORT:' + spec['functions'][1]['symbol'])
    elif name == 'escaped_callee':
        # An externally observable member-function pointer fixes the public ABI.
        escape = work / 'escape.cpp'
        escape.write_text(
            '#include "th10/platform/worker.hpp"\n'
            '#pragma code_seg(".text$90escape")\n'
            'typedef void (PlatformWorker::*WorkerMethod)();\n'
            'extern "C" __declspec(dllexport) WorkerMethod __cdecl EscapeWorkerStop() {\n'
            '    return &PlatformWorker::Stop;\n'
            '}\n')
        command = relocate(compile_commands[0]['command'])
        command[-2:] = ['/Fo' + winpath(work / 'escape.obj'), winpath(escape)]
        _run_logged(command, env, work, work / 'escape.log', 180)
        commands.append(command)
        link_command.append(winpath(work / 'escape.obj'))
    _run_logged(link_command, env, work, work / 'link.log', 300)
    return work, {'compile_commands': commands, 'link_command': link_command,
                  'layout_objects_from': str(native_dir)}


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--project', type=Path, default=DEFAULT_PROJECT)
    parser.add_argument('--toolkit', type=Path, default=DEFAULT_TOOLKIT)
    parser.add_argument('--oracle', type=Path)
    parser.add_argument('--output', type=Path, default=DEFAULT_PROJECT.parent / 'build/ltcg-experiment')
    args = parser.parse_args()
    project, toolkit, output = args.project.resolve(), args.toolkit.resolve(), args.output.resolve()
    config = json.loads((project / 'regions.json').read_text())
    spec = load_cluster(project, MANIFEST, config['regions'])
    inputs = _snapshot(spec)
    output.mkdir(parents=True, exist_ok=True)
    work = Path(tempfile.mkdtemp(prefix='run-', dir=output))
    first = build_cluster(spec, toolkit, work / 'separate_gl', config['flags'])['native_build']
    # The compiler has finished before the oracle is opened.
    oracle_path = args.oracle or default_oracle()
    oracle = load_oracle(oracle_path, config)
    text_start = int(config['text_start'], 0)
    results = {'separate_gl': measure(spec, Path(first['native_executable']),
                                      Path(first['native_map']), oracle, text_start)}
    results['separate_gl']['build_report'] = str(work / 'separate_gl/report.json')
    for name in ('ordinary', 'native_caller', 'native_callee', 'unity_gl',
                 'exported_callee', 'escaped_callee'):
        variant, commands = control(name, spec, first, work, toolkit)
        results[name] = {**measure(spec, variant / 'cluster.exe', variant / 'cluster.map',
                                   oracle, text_start), **commands}
    repeat = build_cluster(spec, toolkit, work / 'separate_gl_repeat', config['flags'])['native_build']
    results['separate_gl_repeat'] = measure(spec, Path(repeat['native_executable']),
                                          Path(repeat['native_map']), oracle, text_start)
    results['separate_gl_repeat']['build_report'] = str(work / 'separate_gl_repeat/report.json')
    _verify_snapshot(inputs)
    if first['tool_sha256'] != repeat['tool_sha256']:
        raise ValueError('toolchain changed during the experiment')
    positive = {'separate_gl', 'unity_gl', 'separate_gl_repeat'}
    passed = all(result['exact'] == (name in positive) for name, result in results.items())
    # Both functions, including their relative call operand, must reproduce on
    # a fresh compile; native PE timestamps are intentionally not compared.
    baseline = [item['bytes'] for item in results['separate_gl']['functions']]
    passed &= all([item['bytes'] for item in results[name]['functions']] == baseline
                  for name in positive)
    ordinary = [item['bytes'] for item in results['ordinary']['functions']]
    passed &= all([item['bytes'] for item in result['functions']] == ordinary
                  for name, result in results.items() if name not in positive)
    report = {'passed': passed, 'manifest': MANIFEST, 'input_sha256': inputs,
              'tool_sha256': first['tool_sha256'], 'cases': results, 'masked_bytes': 0,
              'oracle': str(oracle_path), 'oracle_used_only_for_comparison': True}
    report_path = work / 'experiment.json'
    report_path.write_text(json.dumps(report, indent=2) + '\n')
    for name, result in results.items():
        extents = '/'.join(str(item['size']) for item in result['functions'])
        verdict = 'EXACT' if result['exact'] else 'DIFFERENT (control)'
        print(f'{name:20} caller/callee bytes {extents:7} {verdict}')
    print(report_path)
    print('PASS' if passed else 'FAIL')
    return 0 if passed else 1


if __name__ == '__main__':
    sys.exit(main())
