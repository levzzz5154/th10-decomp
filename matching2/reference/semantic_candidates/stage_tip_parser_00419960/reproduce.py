#!/usr/bin/env python3
"""Probe the parked parser in a disposable project; never edit production inputs."""

import argparse
import json
from pathlib import Path
import shutil
import subprocess
import sys
import tempfile


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--output", type=Path,
                        help="new directory for the project copy and probe artifacts")
    args = parser.parse_args()
    here = Path(__file__).resolve().parent
    root = here.parents[3]
    if args.output is None:
        output = Path(tempfile.mkdtemp(prefix="th10-stage-parser-"))
    else:
        output = args.output.resolve()
        output.mkdir(parents=True, exist_ok=False)
    project = output / "msvc"
    shutil.copytree(root / "matching2/msvc", project)
    checkpoint = here / "claude_checkpoint"
    for source, target in [
        (here / "parser_candidate.cpp", "layout/ltcg/stage_reader_parser_context.cpp"),
        (here / "parser_candidate.json", "layout/ltcg/stage_reader_parser.json"),
        (checkpoint / "sp_improved_model.hpp", "include/stage_parser_model.hpp"),
        (checkpoint / "sp_improved_reader.cpp", "src/script/script_text_reader.cpp"),
    ]:
        shutil.copyfile(source, project / target)

    # Ownership changes exist only in this copied manifest. Selecting the parser
    # makes the normal probe validate its complete bytes, not merely its extent
    # as the reader's compiler context.
    source = "layout/ltcg/stage_reader_parser_context.cpp"
    manifest_path = project / "regions.json"
    manifest = json.loads(manifest_path.read_text())
    selected = set()
    for region in manifest["regions"]:
        address = int(region["address"], 0)
        if address in (0x419960, 0x419F40):
            selected.add(address)
            region.update(source=source, kind="semantic")
            if address == 0x419960:
                region["symbol"] = "_ParseStageTips@12"
    if selected != {0x419960, 0x419F40}:
        raise RuntimeError("production manifest no longer has the expected regions")
    manifest_path.write_text(json.dumps(manifest, indent=2) + "\n")

    print(f"Isolated project and evidence: {output}", flush=True)
    command = [sys.executable, str(root / "matching2/tools/matching/probe.py"),
               "--project", str(project), "--source", source,
               "--output", str(output / "probe"), "--json"]
    result = subprocess.run(command, cwd=root, capture_output=True, text=True)
    (output / "probe.stdout.txt").write_text(result.stdout)
    (output / "probe.stderr.txt").write_text(result.stderr)
    try:
        report = json.loads(result.stdout)
    except json.JSONDecodeError:
        print(result.stdout, end="")
    else:
        for region in report.get("regions", []):
            state = "EXACT" if region["exact"] else "DIFFERENT"
            print(f'{region["address"]:#010x} {region["size"]} bytes '
                  f'{region["symbol"]}: {state} '
                  f'({region.get("different_bytes", "unknown")} differing bytes)')
            if "first_difference" in region:
                print(f'  expected: {region["expected_instruction"]}')
                print(f'  actual:   {region["actual_instruction"]}')
        for failure in report.get("failures", []):
            print(failure)
    print(result.stderr, end="", file=sys.stderr)
    return result.returncode


if __name__ == "__main__":
    sys.exit(main())
