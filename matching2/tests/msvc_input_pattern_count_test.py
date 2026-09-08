"""Exercise the fixed signed input-pattern table contract in C++98."""
from pathlib import Path
import shutil
import subprocess
import tempfile
import unittest

ROOT = Path(__file__).resolve().parents[2]


class InputPatternCountTest(unittest.TestCase):
    def test_fixed_table_and_signed_queries(self):
        compiler = shutil.which('g++')
        self.assertIsNotNone(compiler, 'g++ is required for the C++98 contract test')
        with tempfile.TemporaryDirectory(prefix='th10-pattern-test-') as temporary:
            executable = Path(temporary) / 'pattern-test'
            result = subprocess.run([
                compiler, '-std=c++98', '-O2', '-Wall', '-Wextra', '-Werror',
                str(ROOT / 'matching2/tests/msvc_input_pattern_count_test.cpp'),
                '-o', str(executable),
            ], capture_output=True, text=True, timeout=60)
            self.assertEqual(result.returncode, 0, result.stdout + result.stderr)
            result = subprocess.run([str(executable)], capture_output=True,
                                    text=True, timeout=10)
            self.assertEqual(result.returncode, 0, result.stdout + result.stderr)


if __name__ == '__main__':
    unittest.main()
