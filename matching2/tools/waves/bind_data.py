#!/usr/bin/env python3
"""Bind every data address the still-assembly regions reference.

A recovered unit that materialises an absolute address (a vtable pointer, a
function table entry, a lookup array) needs a name bound at that address, or the
link step has nothing to resolve it against. This disassembles the exact image
once and collects absolute operands inside the data range that no binding covers.
"""
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[3]
sys.path.insert(0, str(ROOT))

import argparse
import json
import re
import shutil
import subprocess
import tempfile

from matching2.tools.common.pe import PEImage

MANIFEST = ROOT / "matching2/msvc/regions.json"
ORACLE = ROOT / "matching2/build/oracle/th10.exe"
OPERAND = re.compile(r"0x([0-9a-f]+)")


def disassemble(raw, start, stop):
    objdump = shutil.which("i686-w64-mingw32-objdump") or shutil.which("objdump")
    with tempfile.TemporaryDirectory(prefix="th10-scan-") as temporary:
        path = Path(temporary) / "text.bin"
        path.write_bytes(raw)
        result = subprocess.run([objdump, "-D", "-z", "-b", "binary", "-m", "i386", "-M", "intel",
                                 f"--adjust-vma={start:#x}", str(path)],
                                capture_output=True, text=True, timeout=600)
    entries = []
    for line in result.stdout.splitlines():
        match = re.match(r"\s*([0-9a-f]+):\s+(?:[0-9a-f]{2} )+\s*(.*)$", line)
        if not match:
            continue
        address = int(match.group(1), 16)
        if start <= address < stop:
            entries.append((address, match.group(2)))
    return entries


def referenced_data(manifest, raw, data_start, data_stop):
    """Absolute data-range operands per region."""
    regions = sorted(manifest["regions"], key=lambda region: int(region["address"], 0))
    text_start = int(manifest["text_start"], 0)
    instructions = disassemble(raw, text_start, text_start + manifest["text_bytes"])
    found = {}
    index = 0
    for region in regions:
        if region["kind"] not in ("asm", "semantic"):
            continue
        start = int(region["address"], 0)
        stop = start + region["size"]
        while index < len(instructions) and instructions[index][0] < start:
            index += 1
        scan = index
        while scan < len(instructions) and instructions[scan][0] < stop:
            for value in OPERAND.findall(instructions[scan][1]):
                target = int(value, 16)
                if data_start <= target < data_stop:
                    found.setdefault(target, region["name"])
            scan += 1
    return found


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--apply", action="store_true")
    args = parser.parse_args()
    manifest = json.loads(MANIFEST.read_text())
    text_start = int(manifest["text_start"], 0)
    text_stop = text_start + manifest["text_bytes"]
    raw = PEImage(ORACLE.read_bytes()).read(text_start, manifest["text_bytes"])
    # Addresses between the end of .text and the end of the image hold the
    # vtables, tables and globals those regions name.
    referenced = referenced_data(manifest, raw, text_stop, 0x49A000)
    bound = {int(address, 0) for address in manifest["symbols"].values()}
    missing = {address: region for address, region in referenced.items() if address not in bound}
    print(f"{len(referenced)} data addresses referenced, {len(missing)} unbound")
    for address in sorted(missing)[:8]:
        print(f"  {address:#010x}  first seen in {missing[address]}")
    if args.apply:
        additions = {f"_data_{address:08x}": f"0x{address:08X}" for address in sorted(missing)}
        manifest["symbols"].update(additions)
        MANIFEST.write_text(json.dumps(manifest, indent=2) + "\n")
        print(f"bindings now {len(manifest['symbols'])}")
    return 0


if __name__ == "__main__":
    sys.exit(main())
