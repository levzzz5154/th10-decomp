"""Input and artifact checks shared by the pinned ordinary i386 COFF compilers."""

import json
import os
from pathlib import Path
import re
import subprocess

from matching2.tools.common.coff import CoffRegionError, read_object
from matching2.tools.common.process import sha


class GCCBackendError(ValueError):
    """Historical exception for GCC and the input checks shared with Clang."""


def require_fields(value, fields, label):
    if not isinstance(value, dict) or set(value) != fields:
        actual = set(value) if isinstance(value, dict) else set()
        raise GCCBackendError(f'{label}: unknown fields {sorted(actual - fields)}; '
                              f'missing fields {sorted(fields - actual)}')


def require_hash(value, label):
    if not isinstance(value, str) or not re.fullmatch('[0-9a-f]{64}', value):
        raise GCCBackendError(label + ' must be a lowercase SHA-256')


def project_file(project, name, label, suffix):
    if (not isinstance(name, str) or not name or '\\' in name or
            Path(name).is_absolute() or Path(name).as_posix() != name or
            any(part in ('.', '..') for part in Path(name).parts)):
        raise GCCBackendError(label + ' must be a canonical project-relative path')
    path = (project / name).resolve()
    if not path.is_relative_to(project) or path.suffix != suffix or not path.is_file():
        raise GCCBackendError(label + ' must be an existing project file: ' + name)
    return path


def read_profile(project, name, kind, error_type, *, extra_fields=()):
    project = Path(project).resolve()
    path = project_file(project, name, 'compiler profile', '.json')
    try:
        contents = path.read_bytes()
        profile = json.loads(contents)
    except (OSError, json.JSONDecodeError) as error:
        raise error_type(f'cannot read compiler profile {path}: {error}') from error
    require_fields(profile, {'schema_version', 'kind', 'description', 'flags', 'tools',
                             *extra_fields}, 'compiler profile')
    if type(profile['schema_version']) is not int or profile['schema_version'] != 1:
        raise error_type('compiler profile schema_version must be 1')
    if profile['kind'] != kind:
        raise error_type('unknown compiler profile kind: ' + str(profile['kind']))
    if not isinstance(profile['description'], str) or not profile['description'].strip():
        raise error_type('compiler profile description must be nonempty')
    return {**profile, '_path': path, '_project': project, '_sha256': sha(contents)}


def validate_tool_specs(tools, names, error_type):
    require_fields(tools, names, 'compiler tools')
    for label, pin in tools.items():
        require_fields(pin, {'path', 'sha256'}, label)
        if (not isinstance(pin['path'], str) or not Path(pin['path']).is_absolute() or
                not Path(pin['path']).is_file()):
            raise error_type(label + ' must name an existing absolute tool path')
        require_hash(pin['sha256'], label + ' sha256')


def snapshot_tools(tools, error_type):
    observed = {name: {'path': pin['path'], 'resolved_path': str(Path(pin['path']).resolve()),
                       'sha256': sha(Path(pin['path']).read_bytes())}
                for name, pin in tools.items()}
    for name, pin in tools.items():
        if observed[name]['sha256'] != pin['sha256']:
            raise error_type('tool pin differs: ' + name)
    return observed


def compiler_environment():
    env = dict(os.environ)
    for name in ('GCC_EXEC_PREFIX', 'COMPILER_PATH', 'LIBRARY_PATH', 'CPATH',
                 'C_INCLUDE_PATH', 'CPLUS_INCLUDE_PATH', 'OBJC_INCLUDE_PATH',
                 'DEPENDENCIES_OUTPUT', 'SUNPRO_DEPENDENCIES', 'LD_PRELOAD',
                 'LD_LIBRARY_PATH', 'LD_AUDIT'):
        env.pop(name, None)
    env.update(LC_ALL='C', LANG='C', TZ='UTC', SOURCE_DATE_EPOCH='0')
    return env


def snapshot(paths):
    return {str(Path(path).resolve()): sha(Path(path).read_bytes()) for path in paths}


def snapshot_project_inputs(include, *paths):
    headers = (p for p in include.rglob('*') if p.is_file()) if include.is_dir() else ()
    return snapshot([*paths, *headers])


def snapshot_framework(*backends):
    framework = Path(__file__).resolve().parent
    common = framework.parent / 'common'
    return snapshot([*(framework / name for name in backends), __file__,
                     framework / 'build_msvc.py', framework / 'unit_cache.py',
                     framework / 'probe.py', framework / 'retail.py',
                     common / 'coff.py', common / 'coff_regions.py', common / 'project_paths.py'])


def require_unchanged(original, label):
    try:
        current = snapshot(original)
    except OSError as error:
        raise GCCBackendError(label + ' removed during compilation') from error
    if current != original:
        raise GCCBackendError(label + ' changed during compilation')


def _dependencies(path):
    # Make dependencies escape spaces/backslashes/dollars and may span lines.
    text = path.read_text().replace('\\\n', '')
    if ':' not in text:
        raise GCCBackendError('compiler produced no dependency target')
    tokens, token, index = [], [], 0
    text = text.split(':', 1)[1]
    while index < len(text):
        char = text[index]
        if char == '\\' and index + 1 < len(text):
            index += 1
            token.append(text[index])
        elif char == '$' and text[index:index + 2] == '$$':
            token.append('$')
            index += 1
        elif char.isspace():
            if token:
                tokens.append(''.join(token))
                token = []
        else:
            token.append(char)
        index += 1
    if token:
        tokens.append(''.join(token))
    return sorted({str(Path(item).resolve()) for item in tokens})


def snapshot_dependencies(path):
    return snapshot(_dependencies(path))


def check_dependency_ownership(actual, expected, label, error_type):
    if _dependencies(actual) != sorted(expected):
        raise error_type(label + ' dependency ownership changed during compilation')


def fresh_assembly_hash(assembly, error_type):
    if not assembly.is_file() or not assembly.stat().st_size:
        raise error_type('compiler produced no fresh assembly')
    return sha(assembly.read_bytes())


def require_ordinary_coff(obj, error_type):
    if not obj.is_file() or not obj.stat().st_size:
        raise error_type('assembler produced no fresh nonempty COFF object')
    try:
        parsed = read_object(obj)
    except CoffRegionError as error:
        raise error_type('assembler produced malformed COFF: ' + str(error)) from error
    if parsed['machine'] != 0x14c or not parsed['sections'] or not parsed['records']:
        raise error_type('assembler did not produce a fresh ordinary i386 COFF object')


class CommandLog:
    """Record each command before launching it, then add its result and log hash."""

    def __init__(self, work, logs, source, env, error_type):
        self.work = work
        self.logs = logs
        self.source = source
        self.env = env
        self.error_type = error_type
        self.records = []

    def _save(self):
        (self.work / 'commands.json').write_text(json.dumps(self.records, indent=2) + '\n')

    def run(self, stage, args):
        args = list(map(str, args))
        log = self.logs / f'{self.work.name}.{stage}.log'
        record = {'stage': stage, 'command': args, 'log': str(log), 'returncode': None}
        self.records.append(record)
        self._save()
        result = subprocess.run(args, cwd=self.work, env=self.env, capture_output=True,
                                text=True, timeout=180)
        log.write_text(result.stdout + result.stderr)
        record.update(returncode=result.returncode, log_sha256=sha(log.read_bytes()))
        self._save()
        if result.returncode:
            raise self.error_type(f'{stage} failed for {self.source}; see {log}')
        return result.stdout
