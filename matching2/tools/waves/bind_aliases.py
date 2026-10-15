#!/usr/bin/env python3
"""Bind decorated __stdcall/__fastcall aliases for every whole-function region.

A recovered C++ caller may only call an unrecovered region if the name MSVC
emits is bound in the layout script. A __cdecl callee already decorates to the
plain bound name, but __stdcall decorates to ``_name@N`` and __fastcall to
``@name@N`` where N is the callee's stack-argument bytes. That N is the operand
of the region's own final ``ret N``, so no signature guesswork is needed.
"""
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[3]
sys.path.insert(0, str(ROOT))

import argparse
import json
import struct

from matching2.tools.common.pe import PEImage

from matching2.tools.common.project_paths import project_support
MANIFEST = project_support((ROOT) / 'matching2/msvc', 'regions.json')
ORACLE = ROOT / "matching2/build/oracle/th10.exe"


def aliases(manifest, raw):
    text_start = int(manifest["text_start"], 0)
    result = {}
    for region in manifest["regions"]:
        if region["kind"] != "asm" or not region.get("owner"):
            continue
        address = int(region["address"], 0)
        if int(region["owner"], 0) != address:
            continue
        body = raw[address - text_start:address - text_start + region["size"]]
        if len(body) < 3 or body[-3] != 0xC2:
            continue  # plain RET, or not a complete function
        stack_bytes = struct.unpack_from("<H", body, len(body) - 2)[0]
        name = region["symbol"]
        result[f"{name}@{stack_bytes}"] = region["address"]
        result[f"@{name.lstrip('_')}@{stack_bytes}"] = region["address"]
    return result


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--apply", action="store_true")
    args = parser.parse_args()
    manifest = json.loads(MANIFEST.read_text())
    raw = PEImage(ORACLE.read_bytes()).read(int(manifest["text_start"], 0), manifest["text_bytes"])
    added = aliases(manifest, raw)
    fresh = {name: address for name, address in added.items() if name not in manifest["symbols"]}
    print(f"{len(added)} decorated aliases derived; {len(fresh)} are new")
    for name in sorted(fresh)[:5]:
        print(f"  {name} = {fresh[name]}")
    if args.apply:
        manifest["symbols"].update(fresh)
        MANIFEST.write_text(json.dumps(manifest, indent=2) + "\n")
        print(f"bindings now {len(manifest['symbols'])}")
    return 0


if __name__ == "__main__":
    sys.exit(main())
