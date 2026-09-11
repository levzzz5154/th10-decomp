#!/usr/bin/env python3
"""Print everything needed to recover one region as matching C++.

Bundle: the current source, the retail bytes disassembled at their real
addresses, the recovered Ghidra/IDA references, and the name of every code and
data address the function references.
"""
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[3]
sys.path.insert(0, str(ROOT))

import argparse
import hashlib
import json
import re
import shutil
import struct
import subprocess
import tempfile


def sha256(data):
    return hashlib.sha256(data).hexdigest()

CONFIG = json.loads((ROOT / "matching2/msvc/regions.json").read_text())
ORACLE_CANDIDATES = (ROOT / "matching2/build/oracle/th10.exe",
                     ROOT / "matching2/build/msvc/th10.exe")
TEXT_START = int(CONFIG["text_start"], 0)
SYMBOLS = {int(address, 0): name for name, address in CONFIG["symbols"].items()}
for region in [*CONFIG["regions"], *CONFIG["dos_regions"]]:
    SYMBOLS.setdefault(int(region["address"], 0), region["name"])


def oracle_bytes():
    from matching2.tools.common.pe import PEImage
    for candidate in ORACLE_CANDIDATES:
        if not candidate.is_file():
            continue
        raw = PEImage(candidate.read_bytes()).read(TEXT_START, CONFIG["text_bytes"])
        if sha256(raw) == CONFIG["text_sha256"]:
            return raw
    raise SystemExit("no local image holds the required .text bytes; set TH10_ORACLE")


def disassemble(raw, address):
    objdump = shutil.which("i686-w64-mingw32-objdump") or shutil.which("objdump")
    with tempfile.TemporaryDirectory(prefix="th10-ref-") as temporary:
        path = Path(temporary) / "region.bin"
        path.write_bytes(raw)
        result = subprocess.run(
            [objdump, "-D", "-z", "-b", "binary", "-m", "i386", "-M", "intel",
             "--insn-width=16", f"--adjust-vma={address:#x}", str(path)],
            capture_output=True, text=True, timeout=20)
    lines = [line.rstrip() for line in result.stdout.splitlines()
             if re.match(r"\s*[0-9a-f]+:", line)]
    return "\n".join(lines)


def ida_excerpt(address, limit=400):
    path = ROOT / "ida/th10.exe.c"
    if not path.is_file():
        return ""
    text = path.read_text(errors="replace")
    marker = f"//----- ({address:08X})"
    start = text.find(marker)
    if start < 0:
        return ""
    end = text.find("//----- (", start + len(marker))
    return "\n".join(text[start:end if end > 0 else len(text)].splitlines()[:limit])


def references(raw, address):
    """Name every code and data address the region's operands point at."""
    rows = []
    for offset in range(len(raw) - 4):
        value = struct.unpack_from("<i", raw, offset)[0]
        for base in (address + offset, address + offset + 4):
            target = base + value
            if target in SYMBOLS:
                rows.append(f"  +{offset:#04x}: {target:#010x} {SYMBOLS[target]}")
                break
    return "\n".join(rows)


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--source", help="project-relative translation unit")
    parser.add_argument("--address", help="region address such as 0x00401100")
    parser.add_argument("--no-reference", action="store_true", help="omit Ghidra/IDA excerpts")
    args = parser.parse_args()
    address = int(args.address, 0) if args.address else None
    source = args.source
    if source is None and address is not None:
        source = next(region["source"] for region in CONFIG["regions"] if int(region["address"], 0) == address)
    if source is None:
        parser.error("pass --source or --address")
    regions = [region for region in CONFIG["regions"] if region["source"] == source]
    if not regions:
        parser.error(f"no maintained region is owned by {source}")
    raw = oracle_bytes()
    print(f"# Translation unit: {source}")
    print(f"# Path: matching2/msvc/{source}")
    print(Path(ROOT / "matching2/msvc" / source).read_text())
    for region in sorted(regions, key=lambda item: int(item["address"], 0)):
        start, size = int(region["address"], 0), region["size"]
        body = raw[start - TEXT_START:start - TEXT_START + size]
        print(f"\n## Region {region['name']} at {start:#010x}, {size} bytes, kind={region['kind']}, "
              f"owner={region.get('owner')}")
        print(f"# symbol now: {region['symbol']}")
        print("## Retail bytes (ground truth; C++ must compile to exactly these)")
        print(f"{start:#010x}: {body.hex(' ')}")
        print(disassemble(body, start))
        names = references(body, start)
        if names:
            print("## Addresses referenced by this region")
            print(names)
        if args.no_reference:
            continue
        ghidra = ROOT / f"decompiled/ghidra_augmented/functions/{start:08x}.c"
        if ghidra.is_file():
            print(f"## Ghidra pseudocode ({ghidra.relative_to(ROOT)})")
            print(ghidra.read_text().strip())
        excerpt = ida_excerpt(start)
        if excerpt:
            print("## IDA Hex-Rays pseudocode (ida/th10.exe.c)")
            print(excerpt)
    return 0


if __name__ == "__main__":
    sys.exit(main())
