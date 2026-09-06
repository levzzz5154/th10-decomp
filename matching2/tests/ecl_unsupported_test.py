"""Unsupported ECL operations must stop with an actionable diagnostic."""
import resource
import signal
import subprocess
import sys

resource.setrlimit(resource.RLIMIT_CORE, (0, 0))
opcodes = (0x124, 0x125, 0x156, 0x15c, 0x165, 0x166, 0x167,
           0x19a, 0x19c, 0x19d, 0x1ac, 0x1ad, 0x1ae, 0x1af,
           0x1b0, 0x1b1, 0x1b2)
for opcode in opcodes:
    result = subprocess.run([sys.argv[1], "--unsupported", hex(opcode)],
                            capture_output=True, text=True, timeout=10)
    assert result.returncode == -signal.SIGABRT, (hex(opcode), result)
    assert "FATAL missing runtime edge 0x0040E770" in result.stderr, result.stderr
    assert f"ECL opcode 0x{opcode:03X}:" in result.stderr, result.stderr
print(f"ECL_UNSUPPORTED_PASS opcodes={len(opcodes)}")
