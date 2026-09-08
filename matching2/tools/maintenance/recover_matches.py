#!/usr/bin/env python3
"""Rebuild the preserved MSVC overlay sources and measure historical matches.

This produces objects and evidence, not an executable or a coverage claim.
"""

import sys
from pathlib import Path

if __package__ in (None, ""):
    sys.path.insert(0, str(Path(__file__).resolve().parents[3]))


from matching2.tools.common.wine import DEFAULT_TOOLKIT, compiler_environment, toolchain_hashes, winpath

import argparse
from collections import Counter
import csv
import hashlib
import io
import json
import re
import subprocess
import tarfile

from matching2.tools.common.coff import read_coff_function
from matching2.tools.matching.compare_obj import read_original


ROOT = Path(__file__).resolve().parents[3]
REVISION = "2b8f23229ab45b9e8cdcfda5ac12689204897a5a"
TOOLKIT = DEFAULT_TOOLKIT
FLAGS = ["/nologo", "/c", "/O2", "/Gz", "/MT", "/Gy", "/G6", "/GF", "/Dnullptr=0"]


def adapt_snapshot(snapshot):
    """Translate later ECL declarations to C++98 in the generated snapshot only."""
    edits = []
    replacements = {
        "include/th10/script/ecl.hpp": [
            ("using ECLSpawnEnemyCallback = int (*)(", "typedef int (*ECLSpawnEnemyCallback)(", 1),
            ("using ECLProjectileSpawnCallback = int (*)(", "typedef int (*ECLProjectileSpawnCallback)(", 1),
        ],
        "src/script/ecl_vm.cpp": [("constexpr int ", "const int ", 4)],
    }
    for relative, changes in replacements.items():
        path = snapshot / "matching2" / relative
        content = path.read_text()
        for before, after, count in changes:
            if content.count(before) != count:
                raise ValueError("unexpected compatibility-patch input: " + relative)
            content = content.replace(before, after)
            edits.append({"path": relative, "before": before, "after": after, "count": count})
        path.write_text(content)
    return edits


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--toolkit", type=Path, default=TOOLKIT)
    parser.add_argument("--exe", type=Path, default=Path.home() / "Games/TH10 - Mountain of Faith/th10.exe")
    parser.add_argument("--output", type=Path, default=ROOT / "matching2/build/recovered-matches")
    args = parser.parse_args()
    args.toolkit = args.toolkit.resolve()
    args.output = args.output.resolve()
    expected = json.loads((ROOT / "decompiled/reference_bytes_validation.json").read_text())["executable_sha256"]
    actual = hashlib.sha256(args.exe.read_bytes()).hexdigest()
    if actual != expected:
        parser.error("retail executable SHA-256 does not match the supported reference")
    if not (args.toolkit / "bin/cl.exe").is_file():
        parser.error("toolkit must contain bin/cl.exe")

    inventory = json.loads((ROOT / "matching2/data/historical_overlays.json").read_text())
    entries = inventory["entries"]
    build_script = subprocess.check_output(
        ["git", "show", REVISION + ":matching2/build.sh"], cwd=ROOT, text=True)
    sources = re.findall(r"^    (src/\S+\.cpp)$", build_script, re.MULTILINE)
    source_map = {Path(source).stem + ".obj": source for source in sources}
    required = sorted({entry["object"] for entry in entries})
    if any(obj not in source_map for obj in required):
        raise ValueError("historical build script does not cover inventory")
    args.output.mkdir(parents=True, exist_ok=True)
    snapshot = args.output / "snapshot"
    snapshot.mkdir(exist_ok=True)
    paths = ["matching2/include"] + ["matching2/" + source_map[obj] for obj in required]
    archive = subprocess.check_output(["git", "archive", REVISION, *paths], cwd=ROOT)
    with tarfile.open(fileobj=io.BytesIO(archive)) as tar:
        tar.extractall(snapshot, filter="data")
    compatibility_edits = adapt_snapshot(snapshot)
    env = compiler_environment(args.toolkit, include_library=True)
    # Record actual binaries, including the compiler backends, for repeatability.
    identities = toolchain_hashes(args.toolkit, ("cl.exe", "link.exe", "c1.dll", "c1xx.dll", "c2.dll"))
    banner = subprocess.run(["wine", str(args.toolkit / "bin/cl.exe")], env=env,
                            capture_output=True, text=True)
    builds = {}
    include = "/I" + winpath(snapshot / "matching2/include")
    for index, obj in enumerate(required, 1):
        source = snapshot / "matching2" / source_map[obj]
        output = args.output / obj
        # A failed rebuild must never fall back to a stale object.
        output.unlink(missing_ok=True)
        command = ["wine", str(args.toolkit / "bin/cl.exe"), *FLAGS, include,
                   "/Fo" + winpath(output), winpath(source)]
        run = subprocess.run(command, env=env, cwd=args.output, capture_output=True, text=True)
        log = obj + ".log"
        (args.output / log).write_text(run.stdout + run.stderr)
        builds[obj] = {"source": source_map[obj], "returncode": run.returncode, "log": log,
                       "object_exists": output.exists(),
                       "source_sha256": hashlib.sha256(source.read_bytes()).hexdigest(),
                       "source_contains_asm": bool(re.search(r"\b(?:__asm|_asm|asm)\b", source.read_text()))}
        if index % 10 == 0 or index == len(required):
            print(f"Compiled {index}/{len(required)} translation units", flush=True)

    with (ROOT / "decompiled/ghidra_full/index.tsv").open() as f:
        boundaries = {int(row["address"], 16): row for row in csv.DictReader(f, delimiter="\t")}
    results = []
    for entry in entries:
        row = {**entry, "source": source_map[entry["object"]]}
        build = builds[entry["object"]]
        if build["returncode"] or not build["object_exists"]:
            row["status"] = "compile_failed"
            results.append(row)
            continue
        try:
            symbol, compiled, ignored = read_coff_function(args.output / entry["object"], entry["symbol"])
            address = int(entry["address"], 16)
            original = read_original(args.exe, address, len(compiled))
            if not compiled or len(original) != len(compiled):
                raise ValueError("empty object body or truncated retail range")
            if any(i < 0 or i >= len(compiled) for i in ignored):
                raise ValueError("relocation mask extends outside compared range")
            compared = [i for i in range(len(compiled)) if i not in ignored]
            if not compared:
                raise ValueError("no unmasked bytes to compare")
            differences = [i for i in compared if compiled[i] != original[i]]
            reference = boundaries.get(address)
            extent_equal = bool(reference and reference["body_ranges"].lower() ==
                                f"{address:08x}-{address + len(compiled) - 1:08x}")
            row.update(resolved_symbol=symbol, object_bytes=len(compiled),
                       compared_bytes=len(compared), masked_bytes=len(ignored),
                       matching_bytes=len(compared) - len(differences),
                       first_mismatch_offsets=differences[:16],
                       saved_ghidra_body_ranges=reference["body_ranges"] if reference else None,
                       extent_matches_saved_ghidra=extent_equal,
                       status="different" if differences else "masked_match" if ignored else "exact_bytes")
        except (ValueError, IndexError) as error:
            row.update(status="comparison_failed", error=str(error))
        results.append(row)
    summary = dict(Counter(row["status"] for row in results))
    report = {"source_revision": REVISION, "inventory_revision": inventory["source_revision"],
              "toolkit": str(args.toolkit), "toolchain_sha256": identities,
              "compiler_banner": banner.stdout + banner.stderr, "flags": FLAGS,
              "snapshot_compatibility_edits": compatibility_edits,
              "retail_sha256": actual, "summary": summary,
              "limitations": [
                  "Historical sources, not current production sources.",
                  "Exact_bytes describes the compared COFF range; consult saved Ghidra extent separately.",
                  "Masked matches exclude address operands; relocation targets have not been verified.",
                  "Saved Ghidra boundaries are analysis evidence, not guaranteed original function extents.",
                  "Assembly presence is recorded per source file, not classified per function.",
                  "No independent executable is linked by this recovery command."],
              "builds": builds, "functions": results}
    (args.output / "report.json").write_text(json.dumps(report, indent=2) + "\n")
    print(json.dumps(summary, sort_keys=True))
    print(args.output / "report.json")
    return int(any(row["status"] in ("compile_failed", "comparison_failed") for row in results))


if __name__ == "__main__":
    raise SystemExit(main())
