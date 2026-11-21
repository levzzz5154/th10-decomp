"""Pinned Clang C++ -> assembly -> unchanged LLVM i386 COFF compilation."""

from __future__ import annotations

from pathlib import Path

from matching2.tools.common.process import sha
from matching2.tools.matching import _llvm_coff as coff
from matching2.tools.matching._llvm_coff import project_file

KIND = 'clang-llvm-coff'
TOOLS = {'clangxx', 'llvm_mc'}
FLAGS = {'-Oz', '-O0', '-O1', '-O2', '-O3', '-mno-sse', '-mno-sse2',
         '-ffunction-sections', '-fno-exceptions', '-fno-rtti', '-fno-ident',
         '-fno-stack-protector', '-falign-functions=1', '-fomit-frame-pointer',
         '-fno-asynchronous-unwind-tables', '-fno-unwind-tables'}


class ClangBackendError(ValueError):
    """A Clang profile or fresh compilation failed its preservation contract."""


def load_profile(project, name):
    profile = coff.read_profile(project, name, KIND, ClangBackendError)
    flags = profile['flags']
    if (not isinstance(flags, list) or any(not isinstance(flag, str) for flag in flags) or
            len(flags) != len(set(flags)) or set(flags) - FLAGS or
            len(set(flags) & {'-O0', '-O1', '-O2', '-O3', '-Oz'}) != 1):
        raise ClangBackendError('compiler flags must be distinct reviewed Clang flags with '
                                'one optimization level')
    coff.validate_tool_specs(profile['tools'], TOOLS, ClangBackendError)
    return profile


def _include_snapshot(include):
    if not include.is_dir():
        return {}
    return {str(p.relative_to(include)): sha(p.read_bytes())
            for p in include.rglob('*') if p.is_file()}


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
        initial = coff.snapshot_tools(tools, ClangBackendError)
        if sha(profile['_path'].read_bytes()) != profile['_sha256']:
            raise ClangBackendError('compiler profile changed after validation')
        include = project / 'include'
        inputs = coff.snapshot_project_inputs(include, source_path, profile['_path'])
        include_snapshot = _include_snapshot(include)
        framework_inputs = coff.snapshot_framework('clang_llvm_backend.py', 'gcc_llvm_backend.py')
        commands = coff.CommandLog(work, logs, source, coff.compiler_environment(), ClangBackendError)

        def check_compiler_inputs():
            coff.require_unchanged(inputs, 'compiler inputs')
            if _include_snapshot(include) != include_snapshot:
                raise ClangBackendError('project include files changed during compilation')
            coff.require_unchanged(framework_inputs, 'compiler framework')
            if sha(profile['_path'].read_bytes()) != profile['_sha256']:
                raise ClangBackendError('compiler profile changed during compilation')
            for name, pin in tools.items():
                path = Path(pin['path'])
                if (sha(path.read_bytes()) != pin['sha256'] or
                        str(path.resolve()) != initial[name]['resolved_path']):
                    raise ClangBackendError('compiler tool changed during compilation: ' + name)

        common = [tools['clangxx']['path'], '--target=i686-pc-windows-gnu',
                  *profile['flags'], '-I' + str(include)]
        versions = {name: commands.run('version-' + name, [tools[name]['path'], '--version'])
                    for name in ('clangxx', 'llvm_mc')}
        check_compiler_inputs()
        commands.run('dependencies', [*common, '-M', '-MF', deps, '-MT', assembly, source_path])
        source_inputs = coff.snapshot_dependencies(deps)
        check_compiler_inputs()
        compile_command = [*common, '-MD', '-MF', str(actual), '-S', str(source_path), '-o', str(assembly)]
        commands.run('cpp', compile_command)
        coff.require_unchanged(source_inputs, 'C++ dependencies')
        coff.check_dependency_ownership(actual, source_inputs, 'C++', ClangBackendError)
        assembly_sha = coff.fresh_assembly_hash(assembly, ClangBackendError)
        check_compiler_inputs()
        mc = tools['llvm_mc']['path']
        commands.run('assemble', [mc, '-triple=i686-pc-windows-gnu', '-filetype=obj', assembly, '-o', obj])
        if sha(assembly.read_bytes()) != assembly_sha:
            raise ClangBackendError('generated assembly changed during assembly')
        coff.require_unchanged(source_inputs, 'C++ dependencies')
        check_compiler_inputs()
        coff.require_ordinary_coff(obj, ClangBackendError)
        return {'source': source, 'object': str(obj), 'command': compile_command,
                'source_sha256': inputs[str(source_path)], 'compiler_kind': KIND,
                'compiler_translation_unit_count': 1, 'commands': commands.records,
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
