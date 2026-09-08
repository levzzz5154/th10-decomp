#!/usr/bin/env python3
"""Regression gate for the retail probe's GDB script generation.

The probe once assigned gdb's `$pc` program-counter register from inside the
tick handler, which resumed the inferior at `ip & 0xFFFF` and crashed the
game. This test generates the GDB script for every mode and asserts that no
`set $...` assignment targets a register name, and that every mode produces
the expected anchors and balanced command blocks.
"""
import re
import subprocess
import tempfile
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
PROBE = ROOT / "tools" / "runtime" / "retail_bounded_probe.sh"

# x86/x86-64 general-purpose, segment, flag, and floating-point registers,
# plus the common pseudo-register names gdb exposes.
REGISTER_NAMES = (
    "eax", "ebx", "ecx", "edx", "esi", "edi", "esp", "ebp", "eip",
    "rax", "rbx", "rcx", "rdx", "rsi", "rdi", "rsp", "rbp", "rip",
    "ax", "bx", "cx", "dx", "si", "di", "sp", "bp", "ip", "pc",
    "cs", "ds", "es", "fs", "gs", "ss", "eflags", "flags",
    "xmm0", "xmm1", "xmm2", "xmm3", "xmm4", "xmm5", "xmm6", "xmm7",
    "st0", "st1", "st2", "st3", "st4", "st5", "st6", "st7",
)
_ASSIGN_RE = re.compile(r"set \$(\w+)")
_REGISTER_RE = re.compile(r"^(?:%s)$" % "|".join(REGISTER_NAMES))


def generate(env: str) -> str:
    start = PROBE.read_text(encoding="utf-8").index(
        '{\n  if [ "${DIAG:-0}" = 1 ]; then')
    end = PROBE.read_text(encoding="utf-8").index(
        '} > "$PROBE_GDB"') + len('} > "$PROBE_GDB"')
    block = PROBE.read_text(encoding="utf-8")[start:end]
    with tempfile.NamedTemporaryFile("w", suffix=".gdb", delete=False) as out:
        path = out.name
    script = 'PROBE_GDB="%s"\n%s\n%s\n' % (path, env, block)
    with tempfile.NamedTemporaryFile("w", suffix=".sh", delete=False) as sh:
        sh.write(script)
        gen = sh.name
    result = subprocess.run(["bash", gen], capture_output=True, text=True)
    assert result.returncode == 0, result.stderr
    content = Path(path).read_text(encoding="utf-8")
    Path(path).unlink()
    Path(gen).unlink()
    return content


def main() -> None:
    modes = {
        "default (hbreak+full)": "",
        "count": "TICK_MODE=count",
        "break": "TICK_MODE=break",
        "no tick": "NO_TICK=1",
        "diag": "DIAG=1",
    }
    for name, env in modes.items():
        content = generate(env)
        for match in _ASSIGN_RE.finditer(content):
            name_part = match.group(1)
            assert not _REGISTER_RE.match(name_part), (
                f"mode {name} assigns register ${name_part}: "
                f"{match.group(0)}"
            )
        # Top-level block balance: gdb's `commands`/`end` tokens sit at
        # column 0; nested `if`/`else`/`end` arms are indented. Exact
        # column-0 counts avoid comment text and inner structure.
        command_lines = [l for l in content.splitlines() if l == "commands"]
        end_lines = [l for l in content.splitlines() if l == "end"]
        assert len(command_lines) == len(end_lines), (
            f"mode {name}: {len(command_lines)} top-level commands vs "
            f"{len(end_lines)} top-level ends"
        )
        expected_blocks = 5 if name == "no tick" else 6
        assert len(command_lines) == expected_blocks, (
            f"mode {name}: {len(command_lines)} command blocks, expected "
            f"{expected_blocks} (catchpoint + frame + tick + stage_load + "
            f"script_register + stage_enter)"
        )
        numbered = [l for l in content.splitlines()
                    if l.strip().startswith("commands ") and
                    l.strip().split()[-1].isdigit()]
        assert not numbered, (
            f"mode {name}: numbered command binding would clobber the "
            f"catchpoint (breakpoint 1): {numbered}"
        )
        anchors = content.count("*0x0044E1A0")
        if name == "no tick":
            assert anchors == 0, f"mode {name}: tick anchor present"
        else:
            assert anchors == 1, f"mode {name}: tick anchor count {anchors}"
        assert "break *0x00439390" in content, f"mode {name}: frame anchor"
        assert "break *0x00403850" in content, f"mode {name}: stage_load"
        assert "break *0x00417870" in content, f"mode {name}: stage_enter"
        if name == "diag":
            assert "handle SIGSEGV stop print nopass" in content
        else:
            assert "handle SIGSEGV nostop noprint pass" in content
    print("RETAIL_PROBE_SCRIPT_TEST_PASS")


if __name__ == "__main__":
    main()
