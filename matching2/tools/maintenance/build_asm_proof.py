#!/usr/bin/env python3
"""Assemble and link two retail regions, verify every byte, then run a harness."""

import sys
from pathlib import Path

if __package__ in (None, ""):
    sys.path.insert(0, str(Path(__file__).resolve().parents[3]))


from matching2.tools.common.pe import PEImage
from matching2.tools.common.process import run
from matching2.tools.common.wine import DEFAULT_TOOLKIT, winpath

import argparse
import hashlib
import json
import os
import re
import shutil
import struct
import subprocess


ROOT = Path(__file__).resolve().parents[3]
SOURCE = ROOT / "matching2/asm/proof"


def verify_regions(retail, built, manifest, symbols):
    if built.image_base != int(manifest["image_base"], 16):
        raise ValueError("wrong linked image base")
    results = []
    for region in manifest["regions"]:
        address, size = int(region["address"], 16), region["size"]
        symbol = f"_th10_{address:08x}"
        if symbols.get(symbol) != address or symbols.get(symbol + "_end") != address + size:
            raise ValueError("linked symbol extent differs: " + region["name"])
        expected, actual = retail.read(address, size), built.read(address, size)
        if actual != expected:
            offsets = [i for i, (a, b) in enumerate(zip(actual, expected)) if a != b]
            raise ValueError(f"{region['name']} differs at offsets {offsets}")
        results.append({**region, "sha256": hashlib.sha256(actual).hexdigest(),
                        "matching_bytes": size, "masked_bytes": 0})
    calls = []
    for call in manifest["external_calls"]:
        address, target = int(call["instruction"], 16), int(call["target"], 16)
        encoded = built.read(address, 5)
        resolved = address + 5 + struct.unpack_from("<i", encoded, 1)[0]
        if encoded[0] != 0xE8 or resolved != target or symbols.get(call["symbol"]) != target:
            raise ValueError("incorrect external call relocation")
        calls.append({**call, "verified_target": f"0x{resolved:08X}"})
    return results, calls


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--exe", type=Path, default=Path.home() / "Games/TH10 - Mountain of Faith/th10.exe")
    parser.add_argument("--toolkit", type=Path, default=DEFAULT_TOOLKIT)
    parser.add_argument("--assembler", default="i686-w64-mingw32-as")
    parser.add_argument("--output", type=Path, default=ROOT / "matching2/build/asm-baseline/proof")
    args = parser.parse_args()
    args.output = args.output.resolve()
    args.toolkit = args.toolkit.resolve()
    # Retail is a comparison oracle only. It is never an assembler/linker input.
    data = args.exe.read_bytes()
    retail_sha = hashlib.sha256(data).hexdigest()
    expected_sha = json.loads((ROOT / "decompiled/reference_bytes_validation.json").read_text())["executable_sha256"]
    if retail_sha != expected_sha:
        parser.error("retail SHA-256 does not match the supported reference")
    retail = PEImage(data)
    assembler = shutil.which(args.assembler)
    if not assembler:
        parser.error("assembler not found: " + args.assembler)
    manifest = json.loads((SOURCE / "regions.json").read_text())
    args.output.mkdir(parents=True, exist_ok=True)
    env = {**os.environ, "WINEDEBUG": "-all"}
    # A failed run must not leave an old success report or executable.
    for name in ("report.json", "proof.exe", "proof.map"):
        (args.output / name).unlink(missing_ok=True)
    objects = []
    commands = []
    for name in ("layout", "symbols", "harness"):
        obj = args.output / (name + ".obj")
        obj.unlink(missing_ok=True)
        command = [assembler, "-I", str(SOURCE), str(SOURCE / (name + ".s")), "-o", str(obj)]
        run(command, args.output / (name + ".log"), args.output, env=env, timeout=60)
        commands.append(command)
        objects.append(obj)

    executable = args.output / "proof.exe"
    linker = args.toolkit / "bin/link.exe"
    command = ["wine", str(linker), "/nologo", "/machine:x86", "/base:0x400000",
               "/filealign:512", "/subsystem:console", "/entry:probe_entry", "/fixed",
               "/incremental:no", "/opt:noref", "/opt:noicf",
               "/out:" + winpath(executable), "/map:" + winpath(args.output / "proof.map"),
               *[winpath(obj) for obj in objects], winpath(args.toolkit / "lib/kernel32.lib")]
    run(command, args.output / "link.log", args.output, env=env, timeout=60)
    commands.append(command)
    linked_data = bytearray(executable.read_bytes())
    built = PEImage(linked_data)
    # link.exe 7.10 has no reproducible timestamp switch. Normalize only its
    # COFF timestamp to the recorded retail timestamp; no code/data is patched.
    struct.pack_into("<I", linked_data, built.pe + 8, retail.timestamp)
    executable.write_bytes(linked_data)
    built = PEImage(linked_data)
    map_text = (args.output / "proof.map").read_text()
    symbols = {name: int(address, 16) for name, address in re.findall(
        r"^\s+[0-9a-fA-F]{4}:[0-9a-fA-F]{8}\s+(\S+)\s+([0-9a-fA-F]{8})\b", map_text, re.MULTILINE)}
    results, calls = verify_regions(retail, built, manifest, symbols)
    if built.entry != symbols.get("_probe_entry"):
        raise ValueError("entry point does not select the test harness")
    runtime = run(["wine", str(executable)], args.output / "runtime.log", args.output, env=env, timeout=60)
    report = {
        "purpose": "Small independent assembly-to-PE proof; not a complete retail executable",
        "retail_sha256": retail_sha,
        "proof_sha256": hashlib.sha256(linked_data).hexdigest(),
        "assembler_version": subprocess.check_output([assembler, "--version"], text=True).splitlines()[0],
        "assembler_sha256": hashlib.sha256(Path(assembler).read_bytes()).hexdigest(),
        "linker_sha256": hashlib.sha256(linker.read_bytes()).hexdigest(),
        "import_library_sha256": hashlib.sha256((args.toolkit / "lib/kernel32.lib").read_bytes()).hexdigest(),
        "source_sha256": {str(p.relative_to(SOURCE)): hashlib.sha256(p.read_bytes()).hexdigest()
                          for p in sorted(SOURCE.rglob("*")) if p.is_file()},
        "timestamp_normalization": {"offset": built.pe + 8, "value": retail.timestamp},
        "sections": built.sections, "regions": results, "external_calls": calls,
        "runtime_exit_code": runtime.returncode,
        "runtime_cases": ["interval true", "unchanged frame false", "non-divisible frame false",
                          "callee stack cleanup", "destructor null path"],
        "commands": commands,
        "limitations": ["Only the named 63 instruction bytes are claimed to match retail.",
                        "Unconverted .text gaps contain synthetic INT3 fill.",
                        "The external free target is an INT3-guarded symbol, without an implementation.",
                        "The test harness never executes the destructor's non-null path.",
                        "The harness, imports, other sections and PE layout are proof-only."]}
    (args.output / "report.json").write_text(json.dumps(report, indent=2) + "\n")
    print("Matched 63/63 bytes at original addresses, including the linked call operand.")
    print("Runtime harness passed; no retail executable code was a build input.")
    print(args.output / "report.json")


if __name__ == "__main__":
    main()
