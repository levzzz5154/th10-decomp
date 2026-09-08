#!/usr/bin/env python3
"""Build the versioned full .text assembly and enforce an unmasked byte gate.

The retail executable is optional verification input, never a linker input.
"""

import argparse
import hashlib
import json
import os
from pathlib import Path
import shutil
import subprocess

from build_asm_proof import PEImage


ROOT = Path(__file__).resolve().parents[2]
SOURCE = ROOT / "matching2/asm/text"


def sha(data):
    return hashlib.sha256(data).hexdigest()


def run(command, log, cwd):
    result = subprocess.run(command, cwd=cwd, capture_output=True, text=True, timeout=180)
    log.write_text(result.stdout + result.stderr)
    if result.returncode:
        raise RuntimeError(f"command failed ({result.returncode}): see {log}")


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--source-dir", type=Path, default=SOURCE)
    parser.add_argument("--output", type=Path, default=ROOT / "matching2/build/asm-baseline/full")
    parser.add_argument("--assembler", default="i686-w64-mingw32-as")
    parser.add_argument("--linker", default="i686-w64-mingw32-ld")
    parser.add_argument("--extra-object", type=Path, action="append", default=[],
                        help="compiled COFF input placed by the source linker script")
    parser.add_argument("--no-pad-sections", action="store_true",
                        help="preserve exact extents when assembly is split around C++ slots")
    parser.add_argument("--verify", type=Path, help="add a direct comparison against this retail executable")
    args = parser.parse_args()
    source, output = args.source_dir.resolve(), args.output.resolve()
    output.mkdir(parents=True, exist_ok=True)
    # Even an early validation failure must invalidate the previous build.
    for name in ("text.obj", "linked.exe", "linked.map", "text.bin", "text.bin.tmp", "report.json"):
        (output / name).unlink(missing_ok=True)
    if (source / ".generation-in-progress").exists():
        raise ValueError("source regeneration did not complete; regenerate successfully before building")
    assembler, linker = shutil.which(args.assembler), shutil.which(args.linker)
    if not assembler or not linker:
        parser.error("GNU x86 PE assembler and linker are required")
    manifest = json.loads((source / "manifest.json").read_text())
    reference = json.loads((ROOT / "decompiled/reference_bytes_validation.json").read_text())
    if (manifest["text_sha256"] != reference["text_section_sha256"] or
            manifest["text_bytes"] != reference["text_section_bytes"] or
            manifest["retail_sha256"] != reference["executable_sha256"]):
        raise ValueError("source manifest does not describe the supported executable")
    oracle = None
    if args.verify:
        original = args.verify.read_bytes()
        if sha(original) != reference["executable_sha256"]:
            raise ValueError("verification executable does not match the supported SHA-256")
        oracle = PEImage(original)
    commands = [
        [assembler, *(["-no-pad-sections"] if args.no_pad_sections else []),
         "-I", str(source), str(source / "main.s"), "-o", str(output / "text.obj")],
        [linker, "--image-base", "0x400000", "--disable-auto-import", "--disable-reloc-section",
         "--no-insert-timestamp", "--entry", "_th10_text_start", "-T", str(source / "layout.ld"),
         "-Map", str(output / "linked.map"), str(output / "text.obj"),
         *[str(p.resolve()) for p in args.extra_object], "-o", str(output / "linked.exe")],
    ]
    for command, name in zip(commands, ("assemble.log", "link.log")):
        run(command, output / name, output)
    linked = PEImage((output / "linked.exe").read_bytes())
    sections = [s for s in linked.sections if s["name"] == ".text"]
    if len(sections) != 1:
        raise ValueError("link output must contain exactly one .text section")
    section = sections[0]
    if any(s["name"] == ".reloc" or (s["name"] != ".text" and s["characteristics"] & 0x20000000)
           for s in linked.sections):
        raise ValueError("unexpected relocation or executable section in link output")
    address = int(manifest["text_start"], 16)
    if (section["address"] != address or section["virtual_size"] != manifest["text_bytes"] or
            section["raw_size"] != manifest["text_bytes"]):
        raise ValueError("linked .text address or extent differs from the source manifest")
    text_bytes = linked.read(address, manifest["text_bytes"])
    if sha(text_bytes) != manifest["text_sha256"]:
        detail = ""
        if oracle:
            original = oracle.read(address, len(text_bytes))
            differences = [address + i for i, (a, b) in enumerate(zip(text_bytes, original)) if a != b]
            detail = f"; {len(differences)} differing bytes, first addresses {[hex(a) for a in differences[:20]]}"
        raise ValueError("linked .text SHA-256 differs" + detail)
    if oracle and text_bytes != oracle.read(address, len(text_bytes)):
        raise ValueError("direct .text comparison failed")
    report = {
        "text_start": manifest["text_start"], "text_bytes": len(text_bytes),
        "text_sha256": sha(text_bytes), "masked_bytes": 0,
        "retail_executable_used_for_build": False,
        "direct_retail_comparison": bool(oracle),
        "instruction_count": manifest["instruction_count"],
        "source_sha256": {str(p.relative_to(source)): sha(p.read_bytes())
                          for p in sorted(source.rglob("*")) if p.is_file()},
        "toolchain": {name: {"path": path, "sha256": sha(Path(path).read_bytes()),
                              "version": subprocess.check_output([path, "--version"], text=True).splitlines()[0]}
                      for name, path in (("assembler", assembler), ("linker", linker))},
        "commands": commands,
        "extra_objects": {str(p.resolve()): sha(p.read_bytes()) for p in args.extra_object},
        "note": "text.bin is built from versioned assembly; linked.exe is an intermediate, not the packaged game",
    }
    (output / "report.json").write_text(json.dumps(report, indent=2) + "\n")
    (output / "text.bin.tmp").write_bytes(text_bytes)
    os.replace(output / "text.bin.tmp", output / "text.bin")
    print(f"Verified {len(text_bytes):,}/{len(text_bytes):,} linked .text bytes; no relocation masks.")
    print(output / "text.bin")


if __name__ == "__main__":
    main()
