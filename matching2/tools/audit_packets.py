#!/usr/bin/env python3
"""Build small independent-review packets from an immutable Git revision.

No generated report or prior verdict enters the packets. Source, headers and
retail references are read with git show, never from the mutable working tree.
Textual cross-references are navigation aids, not proof of runtime reachability.
"""
from __future__ import annotations

import argparse
import hashlib
import json
import re
import subprocess
from pathlib import Path

REPO = Path(__file__).resolve().parents[2]
OUTPUT = REPO / "matching2/docs/audit/packets"
BASELINE = "895c4202387d1c6099cf0cec2e8798bdae6a1754"
REMOTE = "https://github.com/levzzz5154/th10-decomp"
SPECS = [
    ("01_easing", "0x0044C350", [
        "src/game/trajectory_evaluate.cpp", "include/th10/game/trajectory_evaluate.hpp",
        "src/math/easing.cpp", "include/th10/math/easing.hpp"],
     ["Trajectory_EaseFraction", "Easing_Evaluate"]),
    ("02_trajectory", "0x00412AC0", [
        "src/game/trajectory_evaluate.cpp", "include/th10/game/trajectory_evaluate.hpp"],
     ["Trajectory_Evaluate2D"]),
    ("03_score_popup", "0x0042B9C0", [
        "src/game/score_popup.cpp", "include/th10/game/score_popup.hpp",
        "include/th10/math/timer.hpp"],
     ["ScorePopup_Enqueue"]),
    ("04_version_marker", "0x00420100", [
        "src/app/version_marker.cpp", "include/th10/app/version_marker.hpp"],
     ["VersionMarker_Load"]),
    ("05_fps", "0x004135D0", [
        "src/app/fps_counter.cpp", "include/th10/app/fps_counter.hpp",
        "include/th10/util/scalars.hpp"],
     ["FpsCounter_Render"]),
]


def git(*args: str) -> bytes:
    return subprocess.check_output(["git", *args], cwd=REPO)


def digest(data: bytes) -> str:
    return hashlib.sha256(data).hexdigest()


class Snapshot:
    def __init__(self, revision: str):
        self.commit = git("rev-parse", "--verify", revision + "^{commit}").decode().strip()
        self.paths = git("ls-tree", "-r", "--name-only", self.commit).decode().splitlines()
        self.cache: dict[str, bytes] = {}

    def read(self, path: str) -> bytes:
        if path not in self.cache:
            self.cache[path] = git("show", self.commit + ":" + path)
        return self.cache[path]

    def text(self, path: str) -> str:
        return self.read(path).decode("utf-8", errors="replace")


def ida_range(text: str, address: str, assembly: bool) -> tuple[int, int]:
    number = address[2:].upper()
    if assembly:
        name = "sub_" + number.lstrip("0")
        start = re.search(r"^" + name + r" proc near\b", text, re.M | re.I)
        end = re.search(r"^" + name + r" endp\b[^\n]*", text, re.M | re.I)
        if start is None or end is None or end.start() < start.start():
            raise ValueError(f"assembly procedure boundary unresolved: {address}")
        return text.count("\n", 0, start.start()) + 1, text.count("\n", 0, end.end()) + 1
    starts = list(re.finditer(r"^//----- \(([0-9A-F]{8})\) -+", text, re.M))
    for index, match in enumerate(starts):
        if match.group(1) == number:
            end = starts[index + 1].start() if index + 1 < len(starts) else len(text)
            last = text.count("\n", 0, end) if index + 1 < len(starts) else len(text.splitlines())
            return text.count("\n", 0, match.start()) + 1, last
    raise ValueError(f"pseudocode section unresolved: {address}")


def artifact(snapshot: Snapshot, path: str, first: int = 1,
             last: int | None = None) -> tuple[dict, str]:
    raw = snapshot.read(path)
    lines = raw.decode("utf-8", errors="replace").splitlines()
    last = len(lines) if last is None else last
    if first < 1 or last > len(lines) or first > last:
        raise ValueError(f"invalid evidence range: {path}:{first}-{last}")
    content = "\n".join(f"{i}: {lines[i - 1]}" for i in range(first, last + 1))
    url = f"{REMOTE}/blob/{snapshot.commit}/{path}#L{first}-L{last}"
    entry = {"path": path, "first_line": first, "last_line": last,
             "whole_file_sha256": digest(raw), "excerpt_sha256": digest(content.encode()),
             "url": url}
    rendered = f"\n### [{path}:{first}–{last}]({url})\n\n"
    rendered += f"Whole-file SHA-256: `{entry['whole_file_sha256']}`\n\n```text\n{content}\n```\n"
    return entry, rendered


def make_packets(snapshot: Snapshot) -> tuple[dict, dict[str, str]]:
    manifest = {"schema_version": 1, "baseline_commit": snapshot.commit,
                "baseline_tree": git("rev-parse", snapshot.commit + "^{tree}").decode().strip(),
                "purpose": "Independent static review; no prior verdicts included",
                "packets": []}
    rendered: dict[str, str] = {}
    sources = [p for p in snapshot.paths if p.startswith(("matching2/src/", "matching2/standalone/"))
               and p.endswith((".cpp", ".hpp", ".h"))]
    for name, address, paths, symbols in SPECS:
        rows = []
        text = f"# Calibration packet: {address}\n\nBaseline: `{snapshot.commit}`.\n\n"
        text += ("Review the exact address and each supplied C++ implementation independently. "
                 "Compare valid-state behavior, branches, constants, side effects, ownership, "
                 "return values and ABI adapters. Distinguish an actual mismatch from an "
                 "unmeasured precision boundary or a justified host contract. Source comments "
                 "and annotations are claims to check. No prior reviewer verdict is supplied.\n\n"
                 "Report one row per implementation, exact evidence lines, a minimal counterexample "
                 "when possible, production reachability evidence, and what remains unknown. "
                 "Assembly resolves decompiler disagreements. This packet does not establish "
                 "the live retail floating-point environment or gameplay reachability. "
                 "Request additional dependencies by path/address when needed; do not fill gaps "
                 "with assumptions.\n")
        for relative in paths:
            row, body = artifact(snapshot, "matching2/" + relative)
            rows.append(row)
            text += body
        for path, assembly in [("ida/th10.exe.c", False), ("ida/th10.exe.asm", True)]:
            first, last = ida_range(snapshot.text(path), address, assembly)
            row, body = artifact(snapshot, path, first, last)
            rows.append(row)
            text += body
        # Include numeric/string constants referenced by this assembly body.
        # Arbitrary global-owner layouts still need caller/consumer inspection.
        asm_text = snapshot.text("ida/th10.exe.asm")
        asm_lines = asm_text.splitlines()
        asm_body = "\n".join(asm_lines[first - 1:last])
        constants = set(re.findall(r"\b(?:flt|dbl)_[0-9A-Fa-f]+\b|(?<=offset )a[A-Za-z0-9_]+\b", asm_body))
        if constants:
            text += "\n## Referenced retail constants\n"
        for line, value in enumerate(asm_lines, 1):
            declaration = re.match(r"^(\w+)\s+(?:db|dw|dd|dq|dt)\b", value)
            if declaration and declaration.group(1) in constants:
                row, body = artifact(snapshot, "ida/th10.exe.asm", line, line)
                rows.append(row)
                text += body
        prefix = "decompiled/ghidra_raw/" + address[2:].upper() + "_"
        raw_paths = [p for p in snapshot.paths if p.startswith(prefix) and p.endswith(".c")]
        if len(raw_paths) != 1:
            raise ValueError(f"ambiguous/missing Ghidra evidence for {address}: {raw_paths}")
        row, body = artifact(snapshot, raw_paths[0])
        rows.append(row)
        text += body
        text += "\n## Production textual cross-references\n\n"
        text += ("All token occurrences in versioned `src/` and `standalone/` C++/headers "
                 "are listed below, including definitions and comments. These are navigation "
                 "aids; indirect calls and differently named adapters require further inspection. "
                 "Tests are deliberately excluded from this production search.\n\n")
        cross_refs = []
        pattern = re.compile(r"\b(?:" + "|".join(map(re.escape, symbols)) + r")\b")
        for path in sources:
            for line, value in enumerate(snapshot.text(path).splitlines(), 1):
                if pattern.search(value):
                    cross_refs.append({"path": path, "line": line, "text": value.strip()})
                    url = f"{REMOTE}/blob/{snapshot.commit}/{path}#L{line}"
                    text += f"- [{path}:{line}]({url}): `{value.strip().replace('`', '')}`\n"
        # Include caller surroundings in the packet, as well as immutable full-file links.
        owned = {"matching2/" + p for p in paths}
        for ref in cross_refs:
            if ref["path"] in owned:
                continue
            lines = snapshot.text(ref["path"]).splitlines()
            row, body = artifact(snapshot, ref["path"], max(1, ref["line"] - 8),
                                 min(len(lines), ref["line"] + 12))
            rows.append(row)
            text += body
        filename = name + ".md"
        rendered[filename] = text
        manifest["packets"].append({"file": filename, "address": address,
                                    "symbols": symbols, "artifacts": rows,
                                    "production_textual_cross_references": cross_refs,
                                    "sha256": digest(text.encode()), "bytes": len(text.encode())})
    return manifest, rendered


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--baseline", default=BASELINE)
    parser.add_argument("--write", action="store_true")
    parser.add_argument("--check", action="store_true")
    args = parser.parse_args()
    snapshot = Snapshot(args.baseline)
    manifest, packets = make_packets(snapshot)
    packets["manifest.json"] = json.dumps(manifest, indent=2) + "\n"
    for filename, text in packets.items():
        path = OUTPUT / filename
        if args.check and (not path.is_file() or path.read_text(encoding="utf-8") != text):
            raise SystemExit(f"packet is stale: {path.relative_to(REPO)}")
        if args.write:
            path.parent.mkdir(parents=True, exist_ok=True)
            path.write_text(text, encoding="utf-8")
    print(f"audit packets: {len(manifest['packets'])}, baseline {snapshot.commit}")
    for row in manifest["packets"]:
        print(f"  {row['file']}: {row['bytes']} bytes")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
