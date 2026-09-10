"""Exercise the maintained startup-dialog and MIDI callbacks as C++98."""
from pathlib import Path
import shutil
import subprocess
import tempfile
import unittest

ROOT = Path(__file__).resolve().parents[2]


class NativeCallbackTest(unittest.TestCase):
    def test_dialog_messages_choices_and_timer_target(self):
        compiler = shutil.which('g++')
        self.assertIsNotNone(compiler, 'g++ is required for the C++98 contract test')
        with tempfile.TemporaryDirectory(prefix='th10-dialog-test-') as temporary:
            executable = Path(temporary) / 'dialog-test'
            result = subprocess.run([
                compiler, '-std=c++98', '-O2', '-Wall', '-Wextra', '-Werror',
                '-I' + str(ROOT / 'matching2/msvc/include'),
                str(ROOT / 'matching2/tests/msvc_dialog_test.cpp'),
                '-o', str(executable),
            ], capture_output=True, text=True, timeout=60)
            self.assertEqual(result.returncode, 0, result.stdout + result.stderr)
            result = subprocess.run([str(executable)], capture_output=True,
                                    text=True, timeout=10)
            self.assertEqual(result.returncode, 0, result.stdout + result.stderr)


if __name__ == '__main__':
    unittest.main()
