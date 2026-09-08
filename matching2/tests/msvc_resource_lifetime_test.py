"""Run the maintained C++98 resource loader against scripted API boundaries."""
from pathlib import Path
import shutil
import subprocess
import tempfile
import unittest

ROOT = Path(__file__).resolve().parents[2]


class ResourceLifetimeTest(unittest.TestCase):
    def test_loader_failures_copy_reopen_and_destructor(self):
        compiler = shutil.which('g++')
        self.assertIsNotNone(compiler, 'g++ is required for the C++98 contract test')
        with tempfile.TemporaryDirectory(prefix='th10-resource-test-') as temporary:
            executable = Path(temporary) / 'resource-test'
            result = subprocess.run([
                compiler, '-std=c++98', '-O2', '-Wall', '-Wextra', '-Werror',
                '-I' + str(ROOT / 'matching2/msvc/include'),
                str(ROOT / 'matching2/tests/msvc_resource_lifetime_test.cpp'),
                '-o', str(executable),
            ], capture_output=True, text=True, timeout=60)
            self.assertEqual(result.returncode, 0, result.stdout + result.stderr)
            result = subprocess.run([str(executable)], capture_output=True,
                                    text=True, timeout=10)
            self.assertEqual(result.returncode, 0, result.stdout + result.stderr)


if __name__ == '__main__':
    unittest.main()
