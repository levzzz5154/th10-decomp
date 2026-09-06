#!/usr/bin/env python3
"""Reproduce the frozen observation probe against its original Git source tree."""
import argparse
import io
import subprocess
import tarfile
import tempfile
from pathlib import Path

REPO = Path(__file__).resolve().parents[2]
BASELINE = '895c4202387d1c6099cf0cec2e8798bdae6a1754'
PROBE_COMMIT = '88a44c6367c9a8e2fd9d7d8fa638a73bbab27cad'
SOURCES = ['math/easing.cpp', 'game/trajectory_evaluate.cpp', 'game/score_popup.cpp',
           'app/version_marker.cpp', 'app/fps_counter.cpp']


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--cxx', default='g++')
    args = parser.parse_args()
    with tempfile.TemporaryDirectory(prefix='th10-baseline-probe-') as directory:
        root = Path(directory)
        paths = ['matching2/include'] + ['matching2/src/' + name for name in SOURCES]
        archive = subprocess.check_output(['git', 'archive', BASELINE, *paths], cwd=REPO)
        with tarfile.open(fileobj=io.BytesIO(archive)) as contents:
            contents.extractall(root, filter='data')
        probe = root / 'probe.cpp'
        probe.write_bytes(subprocess.check_output(
            ['git', 'show', PROBE_COMMIT + ':matching2/tests/audit_calibration_probe.cpp'], cwd=REPO))
        binary = root / 'probe'
        subprocess.run([args.cxx, '-std=c++17', '-O2', '-Wall', '-Wextra', '-Werror',
                        '-D__fastcall=', '-D__stdcall=', '-D__cdecl=', '-D__thiscall=',
                        '-D__declspec(x)=', '-I' + str(root / 'matching2/include'), str(probe),
                        *[str(root / 'matching2/src' / name) for name in SOURCES],
                        '-o', str(binary)], check=True)
        subprocess.run([str(binary)], check=True)


if __name__ == '__main__':
    main()
