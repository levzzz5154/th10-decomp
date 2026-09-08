"""Explain a linked byte mismatch without changing the exact-match gate."""

from pathlib import Path
import re
import shutil
import subprocess
import tempfile


def instruction_at(data, start, address):
    """Decode from the region start so an operand byte is not treated as an opcode."""
    objdump = shutil.which("i686-w64-mingw32-objdump") or shutil.which("objdump")
    if not objdump:
        return "unavailable (objdump is not installed)"
    try:
        with tempfile.TemporaryDirectory(prefix="th10-mismatch-") as temporary:
            path = Path(temporary) / "region.bin"
            path.write_bytes(data)
            result = subprocess.run(
                [objdump, "-D", "-z", "-b", "binary", "-m", "i386", "-M", "intel",
                 "--insn-width=16", f"--adjust-vma={start:#x}", str(path)],
                capture_output=True, text=True, timeout=10,
            )
        if result.returncode:
            return "unavailable (objdump failed)"
        for line in result.stdout.splitlines():
            match = re.match(r"\s*([0-9a-fA-F]+):\s+((?:[0-9a-fA-F]{2}\s+)+)(.*)", line)
            if match:
                location = int(match[1], 16)
                encoded = bytes.fromhex(match[2])
                if location <= address < location + len(encoded):
                    return f"{location:#010x}: {encoded.hex(' ')}  {match[3].strip()}"
        return "unavailable (no instruction covers the differing byte)"
    except (OSError, subprocess.TimeoutExpired):
        return "unavailable (objdump could not complete)"


def describe_mismatch(actual, expected, config):
    if len(actual) != len(expected):
        raise ValueError("diagnostic inputs must have equal extents")
    offsets = [index for index, pair in enumerate(zip(actual, expected)) if pair[0] != pair[1]]
    if not offsets:
        return "No differing bytes."
    text_start = int(config["text_start"], 0)
    address = text_start + offsets[0]
    region = next((entry for entry in config["regions"]
                   if int(entry["address"], 0) <= address < int(entry["address"], 0) + entry["size"]), None)
    lines = [f"{len(offsets):,} differing byte(s); first at {address:#010x}."]
    if region:
        start = int(region["address"], 0)
        lines += [f"Region: {region['name']} + {address - start:#x} ({region['kind']})",
                  f"Source: {region['source']}", f"Symbol: {region['symbol']}"]
    window = slice(offsets[0], offsets[0] + 8)
    lines += [f"Expected bytes at {address:#010x}: {expected[window].hex(' ')}",
              f"Actual bytes at   {address:#010x}: {actual[window].hex(' ')}"]
    if region and region["kind"] in ("semantic", "asm"):
        extent = slice(start - text_start, start - text_start + region["size"])
        lines += ["Disassembly from region start:",
                  "  Expected: " + instruction_at(expected[extent], start, address),
                  "  Actual:   " + instruction_at(actual[extent], start, address)]
    return "\n".join(lines)
