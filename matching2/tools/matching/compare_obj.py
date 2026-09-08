#!/usr/bin/env python3
"""Compare one function in an MSVC COFF object with the original executable."""

import sys
from pathlib import Path

if __package__ in (None, ""):
    sys.path.insert(0, str(Path(__file__).resolve().parents[3]))


from matching2.tools.common.coff import read_coff_function

import argparse
import struct


DEFAULT_EXE = Path.home() / "Games/TH10 - Mountain of Faith/th10.exe"
IMAGE_BASE = 0x400000
TEXT_RVA = 0x1000
TEXT_RAW = 0x400


def read_original(path, address, size):
    file_offset = TEXT_RAW + (address - IMAGE_BASE - TEXT_RVA)
    with Path(path).open("rb") as executable:
        executable.seek(file_offset)
        return executable.read(size)


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("object", type=Path)
    parser.add_argument("symbol", help="exact name or a unique name fragment")
    parser.add_argument("address", type=lambda value: int(value, 0))
    parser.add_argument("--exe", type=Path, default=DEFAULT_EXE)
    args = parser.parse_args()

    name, compiled, ignored = read_coff_function(args.object, args.symbol)
    original = read_original(args.exe, args.address, len(compiled))
    compared = [index for index in range(len(compiled)) if index not in ignored]
    mismatches = [index for index in compared if compiled[index] != original[index]]
    matched = len(compared) - len(mismatches)
    percentage = 100.0 if not compared else matched * 100.0 / len(compared)

    print("symbol: {}".format(name))
    print("size: {} bytes".format(len(compiled)))
    print("match: {}/{} bytes ({:.2f}%)".format(matched, len(compared), percentage))
    print("ignored relocations: {} bytes".format(len(ignored)))
    if mismatches:
        preview = ", ".join("+0x{:X}".format(offset) for offset in mismatches[:16])
        if len(mismatches) > 16:
            preview += ", ..."
        print("mismatches: {}".format(preview))
        raise SystemExit(1)


if __name__ == "__main__":
    main()
