"""Exercise maintained C++98 strings with scripted growth, error and free boundaries."""
from pathlib import Path
import shutil
import subprocess
import tempfile
import unittest

ROOT = Path(__file__).resolve().parents[2]


class LegacyStringTest(unittest.TestCase):
    def test_assignment_overlap_ranges_storage_and_error_order(self):
        compiler = shutil.which('g++')
        self.assertIsNotNone(compiler, 'g++ is required for the C++98 contract test')
        with tempfile.TemporaryDirectory(prefix='th10-legacy-string-test-') as temporary:
            executable = Path(temporary) / 'legacy-string-test'
            result = subprocess.run([
                compiler, '-std=c++98', '-O2', '-Wall', '-Wextra', '-Werror',
                '-D__fastcall=', '-D__cdecl=',
                '-I' + str(ROOT / 'matching2/msvc/include'),
                str(ROOT / 'matching2/tests/msvc_legacy_string_test.cpp'),
                str(ROOT / 'matching2/msvc/src/util/legacy_string.cpp'),
                '-o', str(executable),
            ], capture_output=True, text=True, timeout=60)
            self.assertEqual(result.returncode, 0, result.stdout + result.stderr)
            result = subprocess.run([str(executable)], capture_output=True,
                                    text=True, timeout=10)
            self.assertEqual(result.returncode, 0, result.stdout + result.stderr)


if __name__ == '__main__':
    unittest.main()
