"""Pinned C++ -> GCC assembly -> unchanged LLVM i386 COFF compilation.

This optional ordinary-object route never receives expected bytes. GCC's
reviewed RTL pass is built afresh as part of compilation; no assembly or COFF
payload is patched. Whole-section ownership remains the existing normalizer's
responsibility.
"""

from __future__ import annotations

import json
import os
from pathlib import Path
import shutil

from matching2.tools.common.process import sha
from matching2.tools.matching import _llvm_coff as coff
from matching2.tools.matching._llvm_coff import GCCBackendError, project_file

KIND = 'gcc-llvm-coff'
TOOLS = {'gcc', 'cc1plus', 'llvm_mc', 'host_cxx', 'host_cc1plus',
         'host_as', 'host_ld', 'host_collect2'}
FLAGS = {
    '-mfpmath=387', '-mno-sse', '-mno-sse2', '-funsafe-math-optimizations',
    '-fno-asynchronous-unwind-tables', '-fno-unwind-tables', '-fno-exceptions',
    '-fno-rtti', '-fno-stack-protector', '-fno-ident', '-ffunction-sections',
    '-falign-functions=1', '-falign-jumps=1', '-falign-loops=1', '-falign-labels=1',
    '-O0', '-O1', '-O2', '-O3', '-Os', '-Oz', '-mpreferred-stack-boundary=2',
    '-mincoming-stack-boundary=2', '-fomit-frame-pointer', '-fcall-saved-edx',
}
HOST_FLAGS = ['-std=c++17', '-fPIC', '-shared', '-fno-rtti', '-O2']


def load_profile(project, name):
    profile = coff.read_profile(project, name, KIND, GCCBackendError, extra_fields=('plugin',))
    flags = profile['flags']
    if (not isinstance(flags, list) or any(not isinstance(flag, str) for flag in flags) or
            len(flags) != len(set(flags)) or set(flags) - FLAGS or
            '-ffunction-sections' not in flags or
            len(set(flags) & {'-O0', '-O1', '-O2', '-O3', '-Os', '-Oz'}) != 1):
        raise GCCBackendError('compiler flags must be distinct reviewed GCC flags with '
                              'one optimization level and -ffunction-sections')
    coff.validate_tool_specs(profile['tools'], TOOLS, GCCBackendError)
    plugin = profile['plugin']
    coff.require_fields(plugin, {'source', 'source_sha256', 'sdk', 'sdk_sha256'}, 'compiler plugin')
    source = project_file(profile['_project'], plugin['source'], 'compiler pass source', '.cc')
    coff.require_hash(plugin['source_sha256'], 'compiler pass source sha256')
    coff.require_hash(plugin['sdk_sha256'], 'compiler plugin SDK sha256')
    if (not isinstance(plugin['sdk'], str) or not Path(plugin['sdk']).is_absolute() or
            not Path(plugin['sdk']).is_dir()):
        raise GCCBackendError('compiler plugin SDK must be an existing absolute directory')
    profile['_pass'] = source
    return profile


def validate_source_compilers(project, config, clusters=None):
    """Reject unowned mappings and every overlap with native LTCG compilation."""
    project = Path(project).resolve()
    mapping = config.get('source_compilers', {})
    if not isinstance(mapping, dict):
        raise GCCBackendError('source_compilers must map maintained sources to profiles')
    if not mapping:
        return {}
    owned = {}
    for region in config.get('regions', []):
        owned.setdefault(region['source'], []).append(region)
    # compile_raw is also a public probe path. Validate overlap there even if
    # the caller has not already loaded the fully validated cluster records.
    if clusters is None:
        clusters = []
        for name in config.get('ltcg_clusters', []):
            path = project_file(project, name, 'LTCG manifest', '.json')
            clusters.append(json.loads(path.read_text()))
    native = set()
    for cluster in clusters:
        native.update(cluster.get('source_names', [cluster['source'],
                       *cluster.get('additional_sources', [])]))
        native.update(cluster.get('included_sources', []))
        if cluster.get('driver'):
            native.add(cluster['driver'])
    native_paths = {project_file(project, name, 'native LTCG source', '.cpp') for name in native}
    mapped_paths = set()
    result = {}
    for source, profile_name in mapping.items():
        source_path = project_file(project, source, 'compiler-owned source', '.cpp')
        if source not in owned:
            raise GCCBackendError('compiler source has no maintained region ownership: ' + source)
        if source in native or source_path in native_paths:
            raise GCCBackendError('compiler source overlaps native LTCG: ' + source)
        if source_path in mapped_paths:
            raise GCCBackendError('compiler mappings must own distinct source files: ' + source)
        mapped_paths.add(source_path)
        if config.get('source_flags', {}).get(source):
            raise GCCBackendError('compiler-owned source cannot mix MSVC source_flags: ' + source)
        if any(region.get('kind') != 'semantic' for region in owned[source]):
            raise GCCBackendError('ordinary compiler sources must own only semantic regions: ' + source)
        profile_path = project_file(project, profile_name, 'compiler profile', '.json')
        try:
            kind = json.loads(profile_path.read_text()).get('kind')
        except (OSError, json.JSONDecodeError, AttributeError) as error:
            raise GCCBackendError(f'cannot read compiler profile kind {profile_path}: {error}') from error
        if kind == KIND:
            result[source] = load_profile(project, profile_name)
        elif kind == 'clang-llvm-coff':
            from matching2.tools.matching.clang_llvm_backend import load_profile as load_clang_profile
            result[source] = load_clang_profile(project, profile_name)
        else:
            raise GCCBackendError('unknown compiler profile kind: ' + str(kind))
    return result


def tree_snapshot(directory):
    """Canonical file names and hashes include all SDK files and symlink targets."""
    directory = Path(directory)
    result, visited = {}, set()
    for root, directories, files in os.walk(directory, followlinks=True):
        root = Path(root)
        if root.resolve() in visited:
            raise GCCBackendError('compiler input tree contains a directory alias or cycle')
        visited.add(root.resolve())
        directories.sort()
        for name in sorted(files):
            path = root / name
            result[str(path.relative_to(directory))] = sha(path.read_bytes())
    return result


def tree_hash(snapshot):
    return sha(json.dumps(snapshot, sort_keys=True, separators=(',', ':')).encode())


def _pin_snapshot(profile):
    if sha(profile['_path'].read_bytes()) != profile['_sha256']:
        raise GCCBackendError('compiler profile changed after validation')
    tools = coff.snapshot_tools(profile['tools'], GCCBackendError)
    sdk = tree_snapshot(profile['plugin']['sdk'])
    if tree_hash(sdk) != profile['plugin']['sdk_sha256']:
        raise GCCBackendError('compiler plugin SDK pin differs')
    if sha(profile['_pass'].read_bytes()) != profile['plugin']['source_sha256']:
        raise GCCBackendError('compiler pass source pin differs')
    return tools, sdk


def compile_gcc_llvm(project, output, index, source, profile):
    """Fail closed: a failed run cannot leave an object usable by a later link."""
    try:
        return _compile_gcc_llvm(project, output, index, source, profile)
    except Exception as error:
        (Path(output) / 'objects' / f'unit{index:04d}.obj').unlink(missing_ok=True)
        if isinstance(error, OSError):
            raise GCCBackendError('compiler input or artifact is unavailable: ' + str(error)) from error
        raise


def _compile_gcc_llvm(project, output, index, source, profile):
    """Produce one fresh i386 COFF object, with pinned inputs and full provenance."""
    project, output = Path(project).resolve(), Path(output).resolve()
    source_path = project_file(project, source, 'compiler-owned source', '.cpp')
    objects, logs = output / 'objects', output / 'logs'
    work = output / 'gcc' / f'unit{index:04d}'
    for directory in (objects, logs, work):
        directory.mkdir(parents=True, exist_ok=True)
    obj = objects / f'unit{index:04d}.obj'
    assembly, plugin = work / 'generated.s', work / 'initialize_stack_home.so'
    host_deps, host_actual = work / 'host.d', work / 'host-actual.d'
    source_deps, source_actual = work / 'source.d', work / 'source-actual.d'
    for path in (obj, assembly, plugin, host_deps, host_actual, source_deps, source_actual):
        path.unlink(missing_ok=True)
    env = coff.compiler_environment()
    commands = coff.CommandLog(work, logs, source, env, GCCBackendError)
    plugin_sha, selected_tools = None, []
    pins = _pin_snapshot(profile)
    include = project / 'include'
    include_inputs = tree_snapshot(include) if include.is_dir() else {}
    initial_inputs = coff.snapshot_project_inputs(include, source_path, profile['_path'], profile['_pass'])
    framework_inputs = coff.snapshot_framework('gcc_llvm_backend.py')

    def check_compiler_inputs():
        coff.require_unchanged(initial_inputs, 'compiler inputs')
        if (tree_snapshot(include) if include.is_dir() else {}) != include_inputs:
            raise GCCBackendError('project include files changed during compilation')
        coff.require_unchanged(framework_inputs, 'compiler framework')
        if plugin_sha is not None and sha(plugin.read_bytes()) != plugin_sha:
            raise GCCBackendError('fresh compiler plugin changed during compilation')
        if _pin_snapshot(profile) != pins:
            raise GCCBackendError('compiler tools or SDK changed during compilation')
        for selection, target, execution_path in selected_tools:
            actual = Path(shutil.which(selection, path=env.get('PATH')) or selection)
            if (str(actual) != execution_path or
                    actual.resolve() != Path(profile['tools'][target]['path']).resolve() or
                    sha(actual.read_bytes()) != profile['tools'][target]['sha256']):
                raise GCCBackendError('compiler tool selection changed during compilation: ' + target)

    tools = profile['tools']
    for driver, program, target in [('gcc', 'cc1plus', 'cc1plus'),
                                   ('host_cxx', 'cc1plus', 'host_cc1plus'),
                                   ('host_cxx', 'as', 'host_as'),
                                   ('host_cxx', 'ld', 'host_ld'),
                                   ('host_cxx', 'collect2', 'host_collect2')]:
        resolved = commands.run('resolve-' + target,
                                [tools[driver]['path'], '-print-prog-name=' + program]).strip()
        execution_path = Path(shutil.which(resolved, path=env.get('PATH')) or resolved)
        if execution_path.resolve() != Path(tools[target]['path']).resolve():
            raise GCCBackendError('compiler selected an unpinned tool: ' + target)
        selected_tools.append((resolved, target, str(execution_path)))
    versions = {name: commands.run('version-' + name, [tools[name]['path'], '--version'])
                for name in ('gcc', 'llvm_mc', 'host_cxx')}
    host = [tools['host_cxx']['path'], *HOST_FLAGS, '-I' + profile['plugin']['sdk']]
    commands.run('host-dependencies', [*host, '-M', '-MF', host_deps, '-MT', plugin, profile['_pass']])
    host_inputs = coff.snapshot_dependencies(host_deps)
    check_compiler_inputs()
    commands.run('plugin', [*host, '-MD', '-MF', host_actual, profile['_pass'], '-o', plugin])
    coff.require_unchanged(host_inputs, 'plugin dependencies')
    coff.check_dependency_ownership(host_actual, host_inputs, 'plugin', GCCBackendError)
    if not plugin.is_file() or not plugin.stat().st_size:
        raise GCCBackendError('compiler produced no fresh plugin')
    plugin_sha = sha(plugin.read_bytes())
    check_compiler_inputs()
    gcc = [tools['gcc']['path'], *profile['flags'], '-fplugin=' + str(plugin), '-I' + str(include)]
    commands.run('source-dependencies', [*gcc, '-M', '-MF', source_deps, '-MT', assembly, source_path])
    source_inputs = coff.snapshot_dependencies(source_deps)
    check_compiler_inputs()
    compile_command = [*gcc, '-MD', '-MF', str(source_actual), '-S', str(source_path), '-o', str(assembly)]
    commands.run('cpp', compile_command)
    coff.require_unchanged(source_inputs, 'C++ dependencies')
    coff.require_unchanged(host_inputs, 'plugin dependencies')
    coff.check_dependency_ownership(source_actual, source_inputs, 'C++', GCCBackendError)
    assembly_sha = coff.fresh_assembly_hash(assembly, GCCBackendError)
    check_compiler_inputs()
    commands.run('assemble', [tools['llvm_mc']['path'], '-triple=i686-pc-windows-gnu',
                              '-filetype=obj', assembly, '-o', obj])
    if sha(assembly.read_bytes()) != assembly_sha or sha(plugin.read_bytes()) != plugin_sha:
        raise GCCBackendError('generated assembly or plugin changed during assembly')
    coff.require_unchanged(host_inputs, 'plugin dependencies')
    coff.require_unchanged(source_inputs, 'C++ dependencies')
    check_compiler_inputs()
    coff.require_ordinary_coff(obj, GCCBackendError)
    return {'source': source, 'object': str(obj), 'command': compile_command,
            'source_sha256': initial_inputs[str(source_path)], 'compiler_kind': KIND,
            'compiler_translation_unit_count': 1, 'commands': commands.records,
            'compiler_profile': {'path': str(profile['_path']),
                                 'sha256': initial_inputs[str(profile['_path'])]},
            'compiler_tools': pins[0], 'compiler_versions': versions,
            'selected_tools': [{'compiler_selection': selection, 'tool': target, 'execution_path': path}
                               for selection, target, path in selected_tools],
            'plugin_sdk': {'path': profile['plugin']['sdk'], 'sha256': tree_hash(pins[1])},
            'input_sha256': {**initial_inputs, **host_inputs, **source_inputs},
            'framework_sha256': framework_inputs,
            'artifacts': {str(path): sha(path.read_bytes()) for path in
                          (plugin, assembly, obj, host_deps, host_actual, source_deps, source_actual)},
            'assembly_unchanged': True, 'post_emission_code_rewrites': 0,
            'masked_bytes': 0, 'retail_executable_used_for_build': False}
