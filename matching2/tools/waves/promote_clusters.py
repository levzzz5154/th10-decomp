#!/usr/bin/env python3
"""Promote byte-exact native-LTCG cluster units from the wave sandboxes.

The cluster labs proved 42 units byte-exact in their own project copies. This
tool moves each one into the maintained project: the recovered source, the
cluster layout, the compiler-context driver, the manifest region record, and
the ltcg_clusters registration. Units whose maintained source owns more than
one region are carved into a new single-region file first, because a cluster
must own its whole translation unit; only then is the source copied.

Every promoted unit is re-probed afterwards, so nothing enters the manifest on
an agent's say-so.

Usage:
    python3 promote_clusters.py --project matching2/msvc [--apply] [--verify]
"""
from __future__ import annotations

import argparse
import json
import re
import shutil
import subprocess
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[3]
WAVE = ROOT / "matching2/build/waves"
LAB = WAVE / "lab"
PROBE = ROOT / "matching2/tools/matching/probe.py"

# agent, cluster name, source (project-relative), address, size, carve source or None
UNITS = [
    ("Z01", "set_flag",                  "src/unidentified/FUN_00401cb0_00401cb0.cpp", 0x401CB0, 7,   None),
    ("Z01", "set_primary_color",         "src/unidentified/FUN_00401cc0_00401cc0.cpp", 0x401CC0, 7,   None),
    ("Z01", "get_sprite_metadata",       "src/unidentified/FUN_00401cd0_00401cd0.cpp", 0x401CD0, 7,   None),
    ("Z01", "set_sprite_metadata",       "src/unidentified/FUN_00401d10_00401d10.cpp", 0x401D10, 7,   None),
    ("Z01", "invoke_strided",            "src/unidentified/FUN_00401fd0_00401fd0.cpp", 0x401FD0, 31,  None),
    ("Z01", "copy_triple",               "src/unidentified/FUN_00405130_00405130.cpp", 0x405130, 17,  None),
    ("Z02", "format_record_text",        "src/unidentified/FUN_00401700_00401700.cpp", 0x401700, 94,  None),
    ("Z02", "clear_scale_velocity_x",    "src/unidentified/FUN_00401f50_00401f50.cpp", 0x401F50, 8,   None),
    ("Z02", "clear_angular_velocity_x",  "src/unidentified/FUN_00401f60_00401f60.cpp", 0x401F60, 8,   None),
    ("Z02", "clear_scale_velocity_x_alternate",
                                         "src/unidentified/FUN_00401f70_00401f70.cpp", 0x401F70, 8,   None),
    ("Z02", "clear_rotation_x",          "src/unidentified/FUN_00401f80_00401f80.cpp", 0x401F80, 8,   None),
    ("Z02", "release_pool_mask",         "src/unidentified/FUN_004052e0_004052e0.cpp", 0x4052E0, 21,  None),
    ("Z02", "set_pool_mask",             "src/unidentified/FUN_00405340_00405340.cpp", 0x405340, 17,  None),
    ("Z03", "fun_00401fb0",              "src/unidentified/FUN_00401fb0_00401fb0.cpp", 0x401FB0, 7,   None),
    ("Z03", "fun_00403060",              "src/unidentified/FUN_00403060_00403060.cpp", 0x403060, 7,   None),
    ("Z03", "fun_00403070",              "src/unidentified/FUN_00403070_00403070.cpp", 0x403070, 7,   None),
    ("Z03", "fun_00404410",              "src/unidentified/FUN_00404410_00404410.cpp", 0x404410, 11,  None),
    ("Z03", "fun_004053b0",              "src/unidentified/FUN_004053b0_004053b0.cpp", 0x4053B0, 23,  None),
    ("Z03", "fun_00405730",              "src/unidentified/FUN_00405730_00405730.cpp", 0x405730, 18,  None),
    ("Z03", "player_manager_start_mode_004045b0", "src/game/player_manager_start_mode_004045b0.cpp",
                                                                                      0x4045B0, 92,  "src/game/player.cpp"),
    ("Z03", "player_set_scheduler_value_00405410", "src/game/player_set_scheduler_value_00405410.cpp",
                                                                                      0x405410, 57,  "src/game/player.cpp"),
    ("Z03", "recovery_scale_color_00404da0", "src/game/recovery_scale_color_00404da0.cpp",
                                                                                      0x404DA0, 101, "src/game/recovery_leaves.cpp"),
    ("Z03", "vec_subtract_00404d40",     "src/math/vec_subtract_00404d40.cpp",        0x404D40, 92,  "src/math/math_utils.cpp"),
    ("Z04", "read_field44",              "src/unidentified/FUN_00404990_00404990.cpp", 0x404990, 4,   None),
    ("Z04", "set_field88",               "src/unidentified/FUN_00404c50_00404c50.cpp", 0x404C50, 7,   None),
    ("Z04", "set_field84",               "src/unidentified/FUN_00404c90_00404c90.cpp", 0x404C90, 7,   None),
    ("Z04", "get_field84",               "src/unidentified/FUN_00404ce0_00404ce0.cpp", 0x404CE0, 7,   None),
    ("Z04", "adjust_power",              "src/game/player_adjustpower_00405b60.cpp",  0x405B60, 42,  "src/game/player.cpp"),
    ("Z04", "release_managed_item",      "src/unidentified/FUN_00406140_00406140.cpp", 0x406140, 18,  None),
    ("Z05", "f405150",                   "src/unidentified/FUN_00405150_00405150.cpp", 0x405150, 4,   None),
    ("Z05", "f405160",                   "src/unidentified/FUN_00405160_00405160.cpp", 0x405160, 4,   None),
    ("Z05", "f404d30",                   "src/unidentified/FUN_00404d30_00404d30.cpp", 0x404D30, 11,  None),
    ("Z05", "f4051b0",                   "src/unidentified/FUN_004051b0_004051b0.cpp", 0x4051B0, 7,   None),
    ("Z05", "f409e20",                   "src/game/score_retire_callbacks_00409e20.cpp", 0x409E20, 28, "src/game/score.cpp"),
    ("Z05", "f40a010",                   "src/unidentified/FUN_0040a010_0040a010.cpp", 0x40A010, 36,  None),
    ("Z06", "object_interface_getter",   "src/unidentified/FUN_00405360_00405360.cpp", 0x405360, 4,   None),
    ("Z06", "object_field04_getter",     "src/unidentified/FUN_00405390_00405390.cpp", 0x405390, 4,   None),
    ("Z06", "object_field3c_getter",     "src/unidentified/FUN_004053d0_004053d0.cpp", 0x4053D0, 4,   None),
    ("Z06", "game_state_field3788_getter",
                                         "src/unidentified/FUN_00405580_00405580.cpp", 0x405580, 7,   None),
    ("Z06", "set_input_mode",            "src/game/set_input_mode_0040ac90.cpp",      0x40AC90, 37,  "src/game/score.cpp"),
    ("Z06", "input_mask_active",         "src/game/input_mask_active_0040ace0.cpp",   0x40ACE0, 33,  "src/game/score.cpp"),
    ("Z06", "score_owned_destroy",       "src/game/score_owned_destroy_0040b9d0.cpp", 0x40B9D0, 18,  "src/game/score.cpp"),
]

BINDINGS = {"_RetireCallbackOwner_00426f70@4": "0x00426F70"}
HEADERS = [("Z01", "include/th10/game/entity.hpp")]


NAKED = re.compile(r'extern "C" __declspec\(naked\) void __cdecl (\w+)\(\) \{')


def carve(text, symbol):
    """Remove one naked definition together with the comment lines directly above it.

    Only contiguous ``//`` lines are lifted, so a neighbouring comment block that
    documents a different function stays where it is.
    """
    hits = [match for match in NAKED.finditer(text) if match.group(1) == symbol]
    if len(hits) != 1:
        raise ValueError(f"expected one naked definition of {symbol}, found {len(hits)}")
    start = hits[0].start()
    end = text.index("\n}\n", hits[0].end()) + len("\n}\n")
    head = start
    while head > 0:
        line_start = text.rfind("\n", 0, head - 1) + 1
        if not text[line_start:head].lstrip().startswith("//"):
            break
        head = line_start
    if head > 0 and text[head - 1] == "\n":
        blank = text.rfind("\n", 0, head - 1) + 1
        if text[blank:head].strip() == "":
            head = blank
    tail = end + 1 if text[end:end + 1] == "\n" else end
    removed = text[head:tail]
    if "naked" in removed.replace(
            f'extern "C" __declspec(naked) void __cdecl {symbol}() {{', ""):
        raise ValueError(f"carve of {symbol} would remove another definition")
    return text[:head] + text[tail:]


def plan(project, manifest):
    """Return the work items and the manifest edits they imply."""
    by_address = {int(region["address"], 0): region for region in manifest["regions"]}
    items = []
    for agent, name, source, address, size, carve_source in UNITS:
        region = by_address.get(address)
        if region is None:
            raise ValueError(f"no manifest region at {address:#x}")
        if region["size"] != size:
            raise ValueError(f"region {address:#x} size {region['size']} != {size}")
        sandbox = LAB / agent / "msvc"
        layout = sandbox / f"layout/ltcg/{name}.json"
        if not layout.is_file():
            raise ValueError(f"missing cluster layout {layout}")
        cluster = json.loads(layout.read_text())
        if cluster["source"] != source:
            raise ValueError(f"{layout} declares source {cluster['source']}, not {source}")
        function = cluster["functions"][0]
        if int(function["address"], 0) != address or function["size"] != size:
            raise ValueError(f"{layout} function extent disagrees with the manifest")
        if not (sandbox / source).is_file():
            raise ValueError(f"missing sandbox source {sandbox / source}")
        if carve_source and not (project / carve_source).is_file():
            raise ValueError(f"missing carve source {carve_source}")
        if not carve_source and region["source"] != source:
            raise ValueError(f"region {address:#x} is owned by {region['source']}, not {source}")
        items.append({"agent": agent, "name": name, "source": source, "address": address,
                      "size": size, "carve": carve_source, "layout": layout,
                      "driver": cluster["driver"], "cluster": cluster,
                      "function": function, "symbol": function["symbol"],
                      "region": region})
    return items


import sys as _project_sys
from pathlib import Path as _ProjectPath
_project_sys.path.insert(0, str(_ProjectPath(__file__).resolve().parents[3]))
from matching2.tools.common.project_paths import project_support
def apply_item(project, manifest, item):
    """Copy one unit into the project and update the manifest in place."""
    sandbox = LAB / item["agent"] / "msvc"
    source = project / item["source"]
    source.parent.mkdir(parents=True, exist_ok=True)
    shutil.copy2(sandbox / item["source"], source)
    (project_support(project, 'layout/ltcg')).mkdir(parents=True, exist_ok=True)
    shutil.copy2(item["layout"], project / f"layout/ltcg/{item['name']}.json")
    shutil.copy2(sandbox / item["driver"], project / item["driver"])
    if item["carve"]:
        parent = project / item["carve"]
        symbol = item["region"]["symbol"].lstrip("_")
        text = parent.read_text()
        carved = carve(text, symbol)
        if carved.count("__declspec(naked)") != text.count("__declspec(naked)") - 1:
            raise ValueError(f"carve of {symbol} in {item['carve']} changed the naked count")
        parent.write_text(carved)
    region = item["region"]
    region["source"] = item["source"]
    region["symbol"] = item["symbol"]
    region["kind"] = "semantic"
    region["name"] = f"semantic_{item['function']['name']}_{item['address']:08x}"
    region.pop("requested_symbol", None)
    cluster_path = f"layout/ltcg/{item['name']}.json"
    if cluster_path not in manifest["ltcg_clusters"]:
        manifest["ltcg_clusters"].append(cluster_path)
    units = sorted({region["source"] for region in manifest["regions"]})
    manifest["translation_units"] = units
    return item


def verify(project, sources, output):
    output.mkdir(parents=True, exist_ok=True)
    command = [sys.executable, str(PROBE), "--project", str(project),
               *sum((["--source", source] for source in sources), []),
               "--json", "--output", str(output)]
    result = subprocess.run(command, capture_output=True, text=True, timeout=3600)
    try:
        report = json.loads(result.stdout)
    except json.JSONDecodeError:
        return None, result.stderr.strip()[:2000]
    return report, ""


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--project", type=Path, default=ROOT / "matching2/msvc")
    parser.add_argument("--apply", action="store_true")
    parser.add_argument("--check", action="store_true",
                       help="verify the promoted units in the project as it stands")
    args = parser.parse_args()
    project = args.project.resolve()
    manifest_path = project_support(project, 'regions.json')
    manifest = json.loads(manifest_path.read_text())
    items = plan(project, manifest)
    print(f"{len(items)} cluster unit(s) ready to promote")
    if not args.apply and not args.check:
        return 0
    if args.apply:
        # Validate every carve before writing anything.
        for item in items:
            if item["carve"]:
                try:
                    carve((project / item["carve"]).read_text(),
                          item["region"]["symbol"].lstrip("_"))
                except ValueError as error:
                    print(f"cannot carve {item['carve']}: {error}")
                    return 1
        for header_agent, header in HEADERS:
            shutil.copy2(LAB / header_agent / "msvc" / header, project / header)
            print(f"updated {header} from {header_agent}")
        for name, address in BINDINGS.items():
            if name not in manifest["symbols"]:
                manifest["symbols"][name] = address
                print(f"bound {name} = {address}")
        for item in items:
            apply_item(project, manifest, item)
            print(f"promoted {item['address']:#010x} {item['source']}")
        manifest_path.write_text(json.dumps(manifest, indent=2) + "\n")
    if not args.check and not args.apply:
        return 0
    sources = [item["source"] for item in items]
    sources += sorted({item["carve"] for item in items if item["carve"]})
    report, problem = verify(project, sources, WAVE / "promote2/probe")
    if report is None:
        print("probe did not report:", problem)
        return 1
    bad = [region for region in report["regions"] if not region["exact"]]
    print(f"probe: {len(report['regions'])} region(s), {len(bad)} not exact, "
          f"{len(report['failures'])} unit failure(s)")
    for failure in report["failures"]:
        print(f"  FAILED {failure['source']}: {failure['error'][:200]}")
    for region in bad:
        print(f"  DIFFERENT {region['address']:#010x} {region['symbol']}: "
              f"{region.get('detail') or region.get('first_difference')}")
    subprocess.run([sys.executable, str(ROOT / "matching2/tools/matching/progress.py"),
                    "--manifest", str(manifest_path)], cwd=ROOT)
    return 0 if report["exact"] else 1


if __name__ == "__main__":
    sys.exit(main())
