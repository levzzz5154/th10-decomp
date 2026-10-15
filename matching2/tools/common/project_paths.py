"""Locations of private build support in current and legacy project copies."""
from pathlib import Path


def project_support(project, relative):
    project = Path(project)
    if (project / 'build_support').is_dir():
        if relative == 'equivalent' or relative.startswith('equivalent/'):
            relative = 'contexts/' + relative
        return project / 'build_support' / relative
    return project / relative
