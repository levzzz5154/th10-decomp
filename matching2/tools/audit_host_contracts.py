#!/usr/bin/env python3
"""Expose inert/constant host callback candidates for manual contract review.

This is deliberately a heuristic inventory, not a C++ parser or equivalence
gate. --check verifies report freshness; --strict fails while candidates remain.
Nothing is waived merely because the normal build's placeholder scan passed.
"""
from __future__ import annotations

import argparse
import hashlib
import json
import re
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
REPORT = ROOT / "docs/audit/host_contracts.json"
MARKDOWN = ROOT / "docs/audit/host_contracts.md"
FUNCTION = re.compile(
    r"^[ \t]*(?:static\s+)?(?:void|int|unsigned\s+int|long|bool|float)\s*"
    r"\**\s*(?P<name>[A-Za-z_]\w*)\s*\([^;{}]*?\)\s*"
    r"\{(?P<body>[^{}]*)\}", re.M)
DISCARD = re.compile(r"\(void\)\s*[A-Za-z_]\w*\s*;")
CONSTANT = re.compile(r"return\s+(?:true|false|nullptr|[-+]?(?:0x[\da-fA-F]+|\d+(?:\.\d*)?)[uUlLfF]*)\s*;")
FALLBACK = re.compile(r"static\s+(?:int|float)\s+(\w+)\s*;\s*return\s+&\1\s*;")


def strip_comments(text: str) -> str:
    # Mask comments and literals, preserving offsets for citations. A function
    # example inside a raw-string literal must not become a code candidate.
    token = re.compile(r'R"(?P<delim>[^ ()\\\t\r\n]{0,16})\(.*?\)(?P=delim)"|"(?:\\.|[^"\\])*"|\'(?:\\.|[^\'\\])*\'|//[^\n]*|/\*.*?\*/', re.S)
    return token.sub(lambda m: re.sub(r"[^\n]", " ", m.group()), text)


def candidates(text: str) -> list[dict]:
    clean = strip_comments(text)
    rows = []
    for match in FUNCTION.finditer(clean):
        body = DISCARD.sub("", match["body"]).strip()
        kind = None
        if not body:
            kind = "no_work"
        elif CONSTANT.fullmatch(body):
            kind = "constant_result"
        elif FALLBACK.fullmatch(body):
            kind = "shared_fallback_slot"
        if kind:
            original = text[match.start():match.end()]
            rows.append({"function": match["name"], "line": text.count("\n", 0, match.start()) + 1,
                         "kind": kind, "body": original.strip(),
                         "body_sha256": hashlib.sha256(original.encode()).hexdigest(),
                         "review_status": "pending_contract_review"})
    return rows


def generate() -> dict:
    paths = sorted((ROOT / "standalone").glob("*.cpp"))
    sources = sorted((ROOT / "src").rglob("*.cpp")) + paths
    contents = {str(p.relative_to(ROOT)): p.read_bytes() for p in sources}
    texts = {name: data.decode("utf-8", errors="replace") for name, data in contents.items()}
    rows = []
    for path in paths:
        relative = str(path.relative_to(ROOT))
        for row in candidates(texts[relative]):
            row["source"] = relative
            pattern = re.compile(r"\b" + re.escape(row["function"]) + r"\b")
            row["textual_occurrences"] = [
                {"source": name, "line": line, "text": value.strip()}
                for name, text in texts.items()
                for line, value in enumerate(text.splitlines(), 1) if pattern.search(value)
            ]
            rows.append(row)
    return {"schema_version": 1,
            "scope": "Named shallow-body functions in standalone/*.cpp; src/*.cpp occurrences included",
            "limits": ["Regex candidates include inactive preprocessor branches and intentional adapters.",
                       "Only the listed return types and shallow function syntax are recognized; this is not a C++ parser.",
                       "No nested-body/lambda/indirect-call completeness claim; absence of a candidate proves nothing.",
                       "A token occurrence is not proof of execution. Verify providers and their exact retail contracts.",
                       "Existing placeholder exemptions are prior claims, not inherited audit verdicts."],
            "files": [{"path": name, "sha256": hashlib.sha256(data).hexdigest()}
                      for name, data in contents.items()],
            "candidate_count": len(rows), "rows": rows}


def markdown(report: dict) -> str:
    lines = ["# Host callback contract review queue", "",
             f"{report['candidate_count']} heuristic candidates require contract review. "
             "This count is neither a bug count nor an exhaustive placeholder count.", "",
             "The ordinary placeholder gate checks different syntax. Its zero result does not clear these rows.", "",
             "For each candidate establish whether the operation is unreachable, owned elsewhere, "
             "intentionally adapted, or missing. Cite the binding and retail effect before accepting an adapter.", ""]
    lines += ["- " + limit for limit in report["limits"]]
    lines += ["", "| Function | Source | Signal | Status |", "| --- | --- | --- | --- |"]
    for row in report["rows"]:
        lines.append(f"| `{row['function']}` | `{row['source']}:{row['line']}` | {row['kind']} | pending |")
    lines += ["", "The JSON companion preserves bodies, hashes and all textual occurrences in `src/**/*.cpp` and `standalone/*.cpp`.", "",
              "`--check` verifies freshness only. `--strict` returns nonzero while this review queue is nonempty.", ""]
    return "\n".join(lines)


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--write", action="store_true")
    parser.add_argument("--check", action="store_true")
    parser.add_argument("--strict", action="store_true")
    args = parser.parse_args()
    report = generate()
    for path, text in [(REPORT, json.dumps(report, indent=2) + "\n"), (MARKDOWN, markdown(report))]:
        if args.check and (not path.exists() or path.read_text(encoding="utf-8") != text):
            raise SystemExit(f"host contract report stale: {path.relative_to(ROOT)}")
        if args.write:
            path.parent.mkdir(parents=True, exist_ok=True)
            path.write_text(text, encoding="utf-8")
    print(f"HOST_CONTRACT_CANDIDATES={report['candidate_count']}")
    print("HOST_CONTRACT_PARITY=not_established")
    return 1 if args.strict and report["rows"] else 0


if __name__ == "__main__":
    raise SystemExit(main())
