"""Exercise finite FrameTimer contracts using the maintained C++98 source."""
from pathlib import Path
import shutil
import subprocess
import tempfile
import unittest

ROOT = Path(__file__).resolve().parents[2]


class FrameTimerTest(unittest.TestCase):
    def test_thresholds_bookkeeping_scaled_steps_and_decrement(self):
        compiler = shutil.which('g++')
        self.assertIsNotNone(compiler, 'g++ with multilib is required for the C++98 timer test')
        with tempfile.TemporaryDirectory(prefix='th10-frame-timer-test-') as temporary:
            executable = Path(temporary) / 'frame-timer-test'
            result = subprocess.run([
                compiler, '-std=c++98', '-m32', '-O2', '-Wall', '-Wextra', '-Werror',
                '-mfpmath=387', '-fexcess-precision=fast', '-Wno-unknown-pragmas',
                '-D__declspec(attribute)=__attribute__((attribute))',
                '-I' + str(ROOT / 'matching2/msvc/include'),
                str(ROOT / 'matching2/tests/msvc_frame_timer_test.cpp'),
                str(ROOT / 'matching2/msvc/src/math/frame_timer.cpp'),
                '-o', str(executable),
            ], capture_output=True, text=True, timeout=60)
            self.assertEqual(result.returncode, 0, result.stdout + result.stderr)
            result = subprocess.run([str(executable)], capture_output=True,
                                    text=True, timeout=10)
            self.assertEqual(result.returncode, 0, result.stdout + result.stderr)


if __name__ == '__main__':
    unittest.main()
