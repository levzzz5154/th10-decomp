#!/usr/bin/env python3
"""Flag reconstructions that cannot plausibly implement the retail functions
they are credited with.

A promoted source file is measured against the IDA pseudocode of every retail
function the registry assigns to it. Two independent signals fire:

  compression  The reconstruction has far less content than the pseudocode it
               claims. Measured on non-whitespace characters, with IDA's
               variable-declaration block removed so the comparison is body to
               body. Readable C++ normally lands well under 2x; a one-line
               model of a 500-line function lands above 7x.

  text-idiom   The file parses text (istringstream/getline/strtol/isspace)
               while claiming retail functions that consume binary data. This
               catches verbose fabrications that the ratio cannot see.

Both were calibrated against hand-verified files. On the current tree the
compression signal separates five confirmed fabrications (7.2x - 22.5x) from
seven confirmed-genuine reconstructions (max 5.8x), and the text-idiom signal
matches three files, all confirmed fabrications, with no false positives.

Known violations live in reconstruction_fidelity_baseline.json so the gate
ratchets: a new violation, or a baselined file getting worse, fails the build.
Improvements are reported and the baseline can be re-cut with --update-baseline.
"""

from pathlib import Path
import argparse
import collections
import json
import re
import sys

ROOT = Path(__file__).resolve().parents[1]
IDA_SOURCE = ROOT.parent / "ida" / "th10.exe.c"
REGISTRY = ROOT / "function_registry.json"
BASELINE = ROOT / "tools" / "reconstruction_fidelity_baseline.json"

# Above this the reconstruction is too small to be implementing the function.
ERROR_RATIO = 6.5
# Reported but not fatal: dense, worth a look, historically still genuine.
WARN_RATIO = 4.0

# Function-section parsing lives in ida_export.py so the gate and the query
# tool share one view of the export.
from ida_export import IDA_DECLARATION, body_sizes, sections  # noqa: E402

TEXT_IDIOM = re.compile(
    r"std::(istringstream|ostringstream|getline|stof|strtof)"
    r"|\bstrtol\s*\(|find\(['\"]:|isspace"
)
# A file may justify a signal in place; the reason is reviewed in the diff.
WAIVER = re.compile(r"//\s*fidelity-audit:\s*(.+)")


def strip_ws(text):
    return re.sub(r"\s", "", text)


def load_ida_bodies():
    """Map retail address -> non-whitespace body size of its IDA pseudocode."""
    if not IDA_SOURCE.is_file():
        raise SystemExit(f"IDA export not found: {IDA_SOURCE}")
    return body_sizes()


def measure():
    sizes = load_ida_bodies()
    registry = json.loads(REGISTRY.read_text())
    credited = collections.defaultdict(lambda: {"chars": 0, "functions": 0,
                                                "bytes": 0, "unmapped": 0})
    for function in registry["functions"]:
        source = function.get("promoted_source")
        if not source:
            continue
        entry = credited[source]
        entry["functions"] += 1
        entry["bytes"] += function.get("size") or 0
        address = int(function["address"], 16)
        if address in sizes:
            entry["chars"] += sizes[address]
        else:
            # Not function-ized by IDA (reached only indirectly, or a chunk).
            entry["unmapped"] += 1

    rows = []
    for source, entry in credited.items():
        path = ROOT / source
        if not path.is_file():
            continue
        text = path.read_text(errors="replace")
        code = [line for line in text.splitlines()
                if line.strip() and not line.strip().startswith("//")]
        own = max(len(strip_ws("".join(code))), 1)
        ratio = entry["chars"] / own
        waiver = WAIVER.search(text)
        rows.append({
            "source": source,
            "ratio": round(ratio, 2),
            "functions": entry["functions"],
            "retail_bytes": entry["bytes"],
            "unmapped": entry["unmapped"],
            "text_idioms": len(TEXT_IDIOM.findall(text)),
            "waiver": waiver.group(1).strip() if waiver else None,
        })
    rows.sort(key=lambda row: -row["ratio"])
    return rows


def violations(rows):
    for row in rows:
        reasons = []
        if row["ratio"] > ERROR_RATIO:
            reasons.append(f"compression {row['ratio']}x")
        if row["text_idioms"]:
            reasons.append(f"text-idiom x{row['text_idioms']}")
        if reasons:
            yield row, reasons


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("--check", action="store_true",
                        help="exit non-zero on a new or worsened violation")
    parser.add_argument("--update-baseline", action="store_true",
                        help="re-cut the baseline from the current tree")
    args = parser.parse_args()

    rows = measure()
    current = {row["source"]: row for row, _ in violations(rows)}

    if args.update_baseline:
        BASELINE.write_text(json.dumps(
            {"comment": "Known unfaithful reconstructions. This list may only "
                        "shrink; see tools/reconstruction_fidelity_audit.py.",
             "files": {s: {"ratio": r["ratio"], "functions": r["functions"],
                           "retail_bytes": r["retail_bytes"],
                           "text_idioms": r["text_idioms"]}
                       for s, r in sorted(current.items())}},
            indent=2) + "\n")
        print(f"baseline written: {len(current)} files")
        return 0

    baseline = {}
    if BASELINE.is_file():
        baseline = json.loads(BASELINE.read_text()).get("files", {})

    for row in rows:
        if row["ratio"] > WARN_RATIO or row["text_idioms"]:
            if row["source"] not in current:
                state = "warn"
            elif row["waiver"]:
                state = "waived"
            elif row["source"] in baseline:
                state = "baselined"
            else:
                state = "NEW"
            print(f"{state:10} ratio={row['ratio']:7.2f} "
                  f"fns={row['functions']:3} bytes={row['retail_bytes']:6} "
                  f"text={row['text_idioms']:2}  {row['source']}"
                  + (f"\n           waiver: {row['waiver']}" if row["waiver"] else ""))

    new = {s: r for s, r in current.items()
           if s not in baseline and not r["waiver"]}
    worse = {s: r for s, r in current.items()
             if s in baseline and r["ratio"] > baseline[s]["ratio"] + 0.01
             and not r["waiver"]}
    fixed = [s for s in baseline if s not in current]

    print(f"\nFIDELITY_VIOLATIONS={len(current)}")
    print(f"FIDELITY_BASELINED={len(baseline)}")
    print(f"FIDELITY_NEW={len(new)}")
    print(f"FIDELITY_WORSENED={len(worse)}")
    print(f"FIDELITY_FIXED={len(fixed)}")
    for source in fixed:
        print(f"  fixed (drop from baseline): {source}")

    if args.check and (new or worse):
        for source, row in sorted(new.items()):
            print(f"NEW unfaithful reconstruction: {source} "
                  f"(ratio {row['ratio']}x, {row['functions']} functions, "
                  f"{row['retail_bytes']} retail bytes)", file=sys.stderr)
        for source, row in sorted(worse.items()):
            print(f"WORSENED: {source} {baseline[source]['ratio']}x -> "
                  f"{row['ratio']}x", file=sys.stderr)
        print("\nA reconstruction must plausibly implement the retail function "
              "it is credited with. Either implement it, drop the "
              "promoted_source credit, or add a reviewed "
              "'// fidelity-audit: <reason>' waiver.", file=sys.stderr)
        return 1
    return 0


if __name__ == "__main__":
    sys.exit(main())
