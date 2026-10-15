#!/usr/bin/env python3
"""Bind compiler constant-pool names a probe run reports as unbound.

MSVC emits a float literal as a reference to ``__real@<bit pattern>``; the name
must resolve to the pool slot the retail image already holds. Likewise an import
thunk is ``__imp__Name@N``. The probe already knows the retail target of every
relocation, so a missing binding is derived, never guessed.
"""
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[3]
sys.path.insert(0, str(ROOT))

import argparse
import json
import re
import subprocess

from matching2.tools.common.project_paths import project_support
MANIFEST = project_support((ROOT) / 'matching2/msvc', 'regions.json')
PROBE = ROOT / "matching2/tools/matching/probe.py"
BINDABLE = re.compile(r"^(__real@[0-9a-f]{8}(?:[0-9a-f]{8})?|__imp__.*|_data_[0-9a-f]{8})$")


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--source", action="append", required=True)
    parser.add_argument("--project", type=Path, default=ROOT / "matching2/msvc")
    parser.add_argument("--proposal", action="append", default=[],
                        help="proposal JSON to probe with, as the agent would")
    parser.add_argument("--apply", action="store_true")
    args = parser.parse_args()
    manifest_path = project_support(args.project.resolve(), 'regions.json')
    manifest = json.loads(manifest_path.read_text())
    command = [sys.executable, str(PROBE), *sum((["--source", item] for item in args.source), []),
               *sum((["--proposal", item] for item in args.proposal), []),
               "--project", str(args.project), "--json",
               "--output", str(ROOT / "matching2/build/waves/bindcheck")]
    result = subprocess.run(command, capture_output=True, text=True, timeout=1800)
    try:
        report = json.loads(result.stdout)
    except json.JSONDecodeError:
        print("probe did not return a report:", result.stderr.strip()[:400])
        return 1
    wanted = {}
    for region in report["regions"]:
        for relocation in region.get("relocations", []):
            if relocation.get("matches") or relocation.get("bound") is not None:
                continue
            name = relocation.get("symbol", "")
            if BINDABLE.match(name):
                wanted[name] = f"0x{relocation['target']:08X}"
    fresh = {name: address for name, address in wanted.items() if name not in manifest["symbols"]}
    print(f"{len(wanted)} bindable name(s) reported unbound; {len(fresh)} are new")
    for name in sorted(fresh):
        print(f"  {name} = {fresh[name]}")
    if args.apply and fresh:
        manifest["symbols"].update(fresh)
        manifest_path.write_text(json.dumps(manifest, indent=2) + "\n")
        print(f"bindings now {len(manifest['symbols'])}")
    return 0


if __name__ == "__main__":
    sys.exit(main())
