"""Pinned Clang C++ -> assembly -> unchanged LLVM i386 COFF compilation."""

from __future__ import annotations

import json
from pathlib import Path
import subprocess

from matching2.tools.common.coff_regions import CoffRegionError, _read_object
from matching2.tools.common.process import sha
from matching2.tools.matching.gcc_llvm_backend import (
    _dependencies, _environment, _fields, _hash, _snapshot, _unchanged,
    project_file,
)

KIND = 'clang-llvm-coff'
TOOLS = {'clangxx', 'llvm_mc'}
FLAGS = {'-Oz', '-O0', '-O1', '-O2', '-O3', '-mno-sse', '-mno-sse2',
         '-ffunction-sections', '-fno-exceptions', '-fno-rtti', '-fno-ident',
         '-fno-stack-protector', '-falign-functions=1', '-fomit-frame-pointer',
         '-fno-asynchronous-unwind-tables', '-fno-unwind-tables'}


class ClangBackendError(ValueError):
    """A Clang profile or fresh compilation failed its preservation contract."""


def load_profile(project, name):
    project = Path(project).resolve()
    path = project_file(project, name, 'compiler profile', '.json')
    try:
        contents = path.read_bytes()
        profile = json.loads(contents)
    except (OSError, json.JSONDecodeError) as error:
        raise ClangBackendError(f'cannot read compiler profile {path}: {error}') from error
    _fields(profile, {'schema_version', 'kind', 'description', 'flags', 'tools'},
            'compiler profile')
    if type(profile['schema_version']) is not int or profile['schema_version'] != 1:
        raise ClangBackendError('compiler profile schema_version must be 1')
    if profile['kind'] != KIND:
        raise ClangBackendError('unknown compiler profile kind: ' + str(profile['kind']))
    if not isinstance(profile['description'], str) or not profile['description'].strip():
        raise ClangBackendError('compiler profile description must be nonempty')
    flags = profile['flags']
    if (not isinstance(flags, list) or any(not isinstance(flag, str) for flag in flags) or
            len(flags) != len(set(flags)) or set(flags) - FLAGS or
            len(set(flags) & {'-O0', '-O1', '-O2', '-O3', '-Oz'}) != 1):
        raise ClangBackendError('compiler flags must be distinct reviewed Clang flags with '
                                'one optimization level')
    _fields(profile['tools'], TOOLS, 'compiler tools')
    for label, pin in profile['tools'].items():
        _fields(pin, {'path', 'sha256'}, label)
        if (not isinstance(pin['path'], str) or not Path(pin['path']).is_absolute() or
                not Path(pin['path']).is_file()):
            raise ClangBackendError(label + ' must name an existing absolute tool path')
        _hash(pin['sha256'], label + ' sha256')
    return {**profile, '_path': path, '_project': project, '_sha256': sha(contents)}



def compile_clang_llvm(project, output, index, source, profile):
    """Emit a fresh ordinary COFF object, rejecting mutated inputs or outputs."""
    obj = None
    try:
        project, output = Path(project).resolve(), Path(output).resolve()
        source_path = project_file(project, source, 'compiler-owned source', '.cpp')
        objects, logs = output / 'objects', output / 'logs'
        work = output / 'clang' / f'unit{index:04d}'
        for directory in (objects, logs, work):
            directory.mkdir(parents=True, exist_ok=True)
        obj, assembly = objects / f'unit{index:04d}.obj', work / 'generated.s'
        deps, actual = work / 'source.d', work / 'source-actual.d'
        for path in (obj, assembly, deps, actual):
            path.unlink(missing_ok=True)
        tools = profile['tools']
        initial = {name: {'path': pin['path'], 'resolved_path': str(Path(pin['path']).resolve()),
                          'sha256': sha(Path(pin['path']).read_bytes())}
                   for name, pin in tools.items()}
        for name, pin in tools.items():
            if initial[name]['sha256'] != pin['sha256']:
                raise ClangBackendError('tool pin differs: ' + name)
        if sha(profile['_path'].read_bytes()) != profile['_sha256']:
            raise ClangBackendError('compiler profile changed after validation')
        include = project / 'include'
        project_paths = [source_path, profile['_path']]
        if include.is_dir():
            project_paths += [p for p in include.rglob('*') if p.is_file()]
        inputs = _snapshot(project_paths)
        include_snapshot = {str(p.relative_to(project)): sha(p.read_bytes())
                            for p in include.rglob('*') if p.is_file()} if include.is_dir() else {}
        framework = Path(__file__).resolve().parent
        framework_inputs = _snapshot([framework / n for n in
                                      ('clang_llvm_backend.py', 'gcc_llvm_backend.py',
                                       'build_msvc.py', 'probe.py')] +
                                     [framework.parent / 'common' / 'coff_regions.py'])
        env = _environment()
        commands = []

        def run(stage, args):
            args = list(map(str, args))
            log = logs / f'unit{index:04d}.{stage}.log'
            record = {'stage': stage, 'command': args, 'log': str(log), 'returncode': None}
            commands.append(record)
            (work / 'commands.json').write_text(json.dumps(commands, indent=2) + '\n')
            result = subprocess.run(args, cwd=work, env=env, capture_output=True, text=True, timeout=180)
            log.write_text(result.stdout + result.stderr)
            record.update(returncode=result.returncode, log_sha256=sha(log.read_bytes()))
            (work / 'commands.json').write_text(json.dumps(commands, indent=2) + '\n')
            if result.returncode:
                raise ClangBackendError(f'{stage} failed for {source}; see {log}')
            return result.stdout

        def check():
            _unchanged(inputs, 'compiler inputs')
            now = {str(p.relative_to(project)): sha(p.read_bytes())
                   for p in include.rglob('*') if p.is_file()} if include.is_dir() else {}
            if now != include_snapshot:
                raise ClangBackendError('project include files changed during compilation')
            _unchanged(framework_inputs, 'compiler framework')
            if sha(profile['_path'].read_bytes()) != profile['_sha256']:
                raise ClangBackendError('compiler profile changed during compilation')
            for name, pin in tools.items():
                path = Path(pin['path'])
                if (sha(path.read_bytes()) != pin['sha256'] or
                        str(path.resolve()) != initial[name]['resolved_path']):
                    raise ClangBackendError('compiler tool changed during compilation: ' + name)

        clang = tools['clangxx']['path']
        target = ['--target=i686-pc-windows-gnu']
        common = [clang, *target, *profile['flags'], '-I' + str(include)]
        versions = {name: run('version-' + name, [tools[name]['path'], '--version'])
                    for name in ('clangxx', 'llvm_mc')}
        check()
        run('dependencies', [*common, '-M', '-MF', deps, '-MT', assembly, source_path])
        source_inputs = _snapshot(_dependencies(deps))
        check()
        run('cpp', [*common, '-MD', '-MF', actual, '-S', source_path, '-o', assembly])
        _unchanged(source_inputs, 'C++ dependencies')
        if _dependencies(actual) != sorted(source_inputs):
            raise ClangBackendError('C++ dependency ownership changed during compilation')
        if not assembly.is_file() or not assembly.stat().st_size:
            raise ClangBackendError('compiler produced no fresh assembly')
        assembly_sha = sha(assembly.read_bytes())
        check()
        mc = tools['llvm_mc']['path']
        run('assemble', [mc, '-triple=i686-pc-windows-gnu', '-filetype=obj', assembly, '-o', obj])
        if sha(assembly.read_bytes()) != assembly_sha:
            raise ClangBackendError('generated assembly changed during assembly')
        _unchanged(source_inputs, 'C++ dependencies')
        check()
        if not obj.is_file() or not obj.stat().st_size:
            raise ClangBackendError('assembler produced no fresh nonempty COFF object')
        try:
            parsed = _read_object(obj)
        except CoffRegionError as error:
            raise ClangBackendError('assembler produced malformed COFF: ' + str(error)) from error
        if parsed['machine'] != 0x14c or not parsed['sections'] or not parsed['records']:
            raise ClangBackendError('assembler did not produce a fresh ordinary i386 COFF object')
        return {'source': source, 'object': str(obj), 'command': commands[-2]['command'],
                'source_sha256': inputs[str(source_path)], 'compiler_kind': KIND,
                'compiler_translation_unit_count': 1, 'commands': commands,
                'compiler_profile': {'path': str(profile['_path']), 'sha256': inputs[str(profile['_path'])]},
                'compiler_tools': initial, 'compiler_versions': versions,
                'input_sha256': {**inputs, **source_inputs}, 'framework_sha256': framework_inputs,
                'artifacts': {str(path): sha(path.read_bytes()) for path in
                              (assembly, obj, deps, actual)},
                'assembly_unchanged': True, 'post_emission_code_rewrites': 0,
                'masked_bytes': 0, 'retail_executable_used_for_build': False}
    except Exception as error:
        if obj is not None:
            obj.unlink(missing_ok=True)
        if isinstance(error, OSError):
            raise ClangBackendError('compiler input or artifact is unavailable: ' + str(error)) from error
        raise
