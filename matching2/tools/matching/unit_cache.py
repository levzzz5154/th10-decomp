"""Content-addressed storage for normalized MSVC and native LTCG objects."""
import hashlib
import json
from pathlib import Path
import re
import shutil

from matching2.tools.common.process import sha
from matching2.tools.common.project_paths import ROOT, compilation_source


INCLUDE_PATTERN = re.compile(rb'^[ \t]*#[ \t]*include[ \t]*["<]([^">]+)[">]', re.MULTILINE)


class UnitCache:
    """Reuse objects, never the link or whole-image comparison.

    A key covers the tools, flags, ownership, layout and project input bytes.
    Following even conditional includes makes the closure an overestimate.
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
        if path not in self.file_digests:
            self.file_digests[path] = sha(path.read_bytes())
        return self.file_digests[path]

    def closure(self, path):
        """Project files reachable from a source through #include."""
        if path in self.closures:
            return self.closures[path]
        seen, stack = set(), [path]
        while stack:
            current = stack.pop()
            if current in seen:
                continue
            seen.add(current)
            for raw_name in INCLUDE_PATTERN.findall(current.read_bytes()):
                name = raw_name.decode('latin-1').replace('\\', '/')
                for base in (current.parent, self.project / 'include'):
                    candidate = (base / name).resolve()
                    if candidate.is_file() and candidate.is_relative_to(self.project):
                        stack.append(candidate)
                        break
        self.closures[path] = seen
        return seen

    def key(self, source, config, regions, cluster):
        if cluster is None:
            roots = [self.project / source, compilation_source(self.project, source, config)]
        else:
            roots = [cluster['path'], *cluster['source_paths'], *cluster['included_source_paths'],
                     *cluster['header_paths'], *cluster['additional_source_paths'],
                     *cluster.get('ordinary_source_paths', []), *cluster.get('compilation_paths', [])]
            if cluster['driver_path']:
                roots.append(cluster['driver_path'])
        files = set()
        for root in roots:
            root = Path(root).resolve()
            if root.suffix in ('.cpp', '.hpp', '.h'):
                files.update(self.closure(root))
            else:
                files.add(root)
        record = {**self.base, 'source': source, 'regions': regions, 'cluster': cluster,
                  'source_flags': config.get('source_flags', {}).get(source),
                  'coff_aliases': config.get('coff_aliases', {}).get(source),
                  'files': {str(path.relative_to(self.project)): self.digest(path) for path in files}}
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
