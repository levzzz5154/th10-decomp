"""Locations of maintained sources and build support in current and legacy projects."""
from pathlib import Path

ROOT = Path(__file__).resolve().parents[3]
DEFAULT_PROJECT = ROOT / 'matching2/msvc'


def project_support(project, relative):
    project = Path(project)
    if (project / 'build_support').is_dir():
        if relative == 'equivalent' or relative.startswith('equivalent/'):
            relative = 'contexts/' + relative
        return project / 'build_support' / relative
    return project / relative


def compilation_source(project, source, config):
    """Resolve the private compiler wrapper without changing maintained ownership."""
    units = config.get('compilation_units', {})
    if not isinstance(units, dict) or any(not isinstance(k, str) or not isinstance(v, str)
                                          for k, v in units.items()):
        raise ValueError('compilation_units must map sources to project C++ files')
    path = (project / units.get(source, source)).resolve()
    if not path.is_relative_to(project) or path.suffix != '.cpp' or not path.is_file():
        raise ValueError('compiler translation unit must be a project C++ source: ' + str(path))
    return path
