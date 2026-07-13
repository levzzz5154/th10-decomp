#!/usr/bin/env python3
"""Build a runnable TH10 image by overlaying matched functions on the retail PE.

The retail executable supplies the not-yet-reimplemented code, global data,
imports, and resources. Every overlay is compiled from this tree and must match
the retail bytes outside linker relocation operands. This keeps the intermediate
binary playable while functions are replaced incrementally.
"""

import argparse
import hashlib
import shutil
import sys
from pathlib import Path

from compare_obj import IMAGE_BASE, read_coff_function


EXPECTED_SHA256 = "2f14760b6fbbf57549541583283badb9a19a4222b90f0a146d5aa17f01dc9040"
DEFAULT_EXE = Path("/home/levzzz/Games/TH10 - Mountain of Faith/th10.exe")

# object, unique symbol fragment, original virtual address
OVERLAYS = (
    ("entity.obj", "Entity_Destructor", 0x00401FF0),
    ("entity.obj", "Entity_Constructor", 0x00402050),
    ("entity.obj", "EntitySecondaryResource_Release", 0x00405DE0),
    ("entity.obj", "EntityAnimation_Release", 0x0041AD60),
    ("heap.obj", "HeapBuffer_Release", 0x00435250),
    ("heap.obj", "0HeapBuffer", 0x004352C0),
    ("file.obj", "??_GFileHandle", 0x00435320),
    ("file.obj", "??1FileHandle", 0x00435340),
    ("file.obj", "Close@FileHandle", 0x00435460),
    ("file.obj", "Read@FileHandle", 0x00435490),
    ("file.obj", "Write@FileHandle", 0x004354D0),
    ("file.obj", "Tell@FileHandle", 0x00435510),
    ("file.obj", "GetSize@FileHandle", 0x00435530),
    ("file.obj", "Seek@FileHandle", 0x00435550),
    ("file.obj", "??1FileInterface", 0x00435690),
    ("file.obj", "??_GFileInterface", 0x004356A0),
    ("heap.obj", "LegacyString_Clear", 0x004381F0),
    ("entity.obj", "DestroyEntityList", 0x00438A30),
)


def read_pe_sections(image):
    pe_offset = int.from_bytes(image[0x3C:0x40], "little")
    if image[pe_offset:pe_offset + 4] != b"PE\0\0":
        raise ValueError("input is not a PE image")
    coff = pe_offset + 4
    section_count = int.from_bytes(image[coff + 2:coff + 4], "little")
    optional_size = int.from_bytes(image[coff + 16:coff + 18], "little")
    table = coff + 20 + optional_size
    sections = []
    for index in range(section_count):
        offset = table + index * 40
        name = image[offset:offset + 8].rstrip(b"\0").decode("ascii")
        virtual_size = int.from_bytes(image[offset + 8:offset + 12], "little")
        virtual_address = int.from_bytes(image[offset + 12:offset + 16], "little")
        raw_size = int.from_bytes(image[offset + 16:offset + 20], "little")
        raw_offset = int.from_bytes(image[offset + 20:offset + 24], "little")
        sections.append((name, virtual_address, virtual_size, raw_offset, raw_size))
    return sections


def virtual_to_file(sections, address, size):
    rva = address - IMAGE_BASE
    for name, virtual_address, virtual_size, raw_offset, raw_size in sections:
        extent = max(virtual_size, raw_size)
        if virtual_address <= rva and rva + size <= virtual_address + extent:
            relative = rva - virtual_address
            if relative + size > raw_size:
                raise ValueError("overlay at 0x{:08X} reaches uninitialized {} data"
                                 .format(address, name))
            return raw_offset + relative
    raise ValueError("address 0x{:08X} is not backed by a PE section".format(address))


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("--original", type=Path, default=DEFAULT_EXE)
    parser.add_argument("--objects", type=Path, required=True)
    parser.add_argument("--output", type=Path, required=True)
    args = parser.parse_args()

    original_hash = hashlib.sha256(args.original.read_bytes()).hexdigest()
    if original_hash != EXPECTED_SHA256:
        raise SystemExit("unsupported original executable (SHA-256 {})".format(original_hash))

    image = bytearray(args.original.read_bytes())
    sections = read_pe_sections(image)
    overlay_count = 0
    overlay_bytes = 0

    for object_name, symbol, address in OVERLAYS:
        resolved_name, compiled, relocation_bytes = read_coff_function(
            args.objects / object_name, symbol)
        file_offset = virtual_to_file(sections, address, len(compiled))
        retail = image[file_offset:file_offset + len(compiled)]
        mismatches = [index for index in range(len(compiled))
                      if index not in relocation_bytes and compiled[index] != retail[index]]
        if mismatches:
            preview = ", ".join("+0x{:X}".format(index) for index in mismatches[:8])
            raise SystemExit("{} is not matched: {} differing byte(s), {}"
                             .format(resolved_name, len(mismatches), preview))

        # Relocation fields in COFF objects are linker placeholders. Preserve
        # their already-resolved retail values while overlaying compiled bytes.
        for index, value in enumerate(compiled):
            if index not in relocation_bytes:
                image[file_offset + index] = value
        overlay_count += 1
        overlay_bytes += len(compiled) - len(relocation_bytes)
        print("overlay: {} at 0x{:08X} ({} verified bytes)"
              .format(resolved_name, address, len(compiled) - len(relocation_bytes)))

    args.output.parent.mkdir(parents=True, exist_ok=True)
    temporary = args.output.with_suffix(args.output.suffix + ".tmp")
    temporary.write_bytes(image)
    shutil.copymode(args.original, temporary)
    temporary.replace(args.output)

    result_hash = hashlib.sha256(image).hexdigest()
    print("built: {}".format(args.output))
    print("verified overlays: {} functions, {} bytes".format(overlay_count, overlay_bytes))
    print("SHA-256: {}".format(result_hash))
    if result_hash == original_hash:
        print("image match: 100% (all current C++ overlays are byte-identical)")


if __name__ == "__main__":
    main()
