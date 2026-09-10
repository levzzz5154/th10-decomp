"""Exercise the maintained C++98 RNG recurrence, packing and x87 float contract."""
from pathlib import Path
import shutil
import subprocess
import tempfile
import unittest

ROOT = Path(__file__).resolve().parents[2]


class RngTest(unittest.TestCase):
    def test_all_seeds_counters_sequences_and_float_rounding(self):
        compiler = shutil.which('g++')
        self.assertIsNotNone(compiler, 'g++ is required for the C++98 contract test')
        with tempfile.TemporaryDirectory(prefix='th10-rng-test-') as temporary:
            executable = Path(temporary) / 'rng-test'
            result = subprocess.run([
                compiler, '-std=c++98', '-O2', '-Wall', '-Wextra', '-Werror',
                # Retail keeps unsigned conversion and subtraction in x87
                # registers until the final float store. SSE evaluation can
                # round the integer conversion earlier and changes the result.
                '-mfpmath=387', '-fexcess-precision=fast',
                '-D__fastcall=', '-D__forceinline=inline',
                '-I' + str(ROOT / 'matching2/msvc/include'),
                str(ROOT / 'matching2/tests/msvc_rng_test.cpp'),
                # Compile the implementation separately so host inlining cannot
                # share rounded intermediates between independent API calls.
                str(ROOT / 'matching2/msvc/src/math/rng.cpp'),
                '-o', str(executable),
            ], capture_output=True, text=True, timeout=60)
            self.assertEqual(result.returncode, 0, result.stdout + result.stderr)
            result = subprocess.run([str(executable)], capture_output=True,
                                    text=True, timeout=10)
            self.assertEqual(result.returncode, 0, result.stdout + result.stderr)


if __name__ == '__main__':
    unittest.main()
