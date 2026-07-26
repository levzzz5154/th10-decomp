#!/usr/bin/env python3
"""Inventory production fallbacks that can make an inert runtime look green.

Every pattern here marks a call site that compiles and links but performs no
recovered work: a host adapter that only logs, a hook bound to an empty
lambda, or a runtime binding whose call site is skipped when the binding is
unset. Pass --check to fail the build when any of them survive.
"""

from pathlib import Path
import re
import sys

ROOT = Path(__file__).resolve().parents[1]
FILES = [
    *sorted((ROOT / "src").rglob("*.cpp")),
    *sorted((ROOT / "standalone").glob("*.cpp")),
]

# Matched against the whole file, not line by line: a Log("host adapter call
# split across lines used to slip through the line-oriented scan.
PATTERNS = (
    ("host-adapter", re.compile(r'Log\(\s*"host adapter', re.DOTALL)),
    ("empty-lambda", re.compile(r'=\s*\[\][^{;]*\{\s*\}\s*;', re.DOTALL)),
    ("optional-binding", re.compile(
        r'g_[A-Za-z0-9_]+_bindings\.[A-Za-z0-9_]+\s*!=\s*0')),
)
SOFTWARE_RENDER_PATTERNS = (
    re.compile(r'HostDrawAnmVmSoftware'),
    re.compile(r'SetDIBitsToDevice'),
)


def scan(text, pattern):
    """Yield (line_number, line_text) for every match in the file body."""
    for match in pattern.finditer(text):
        line_no = text.count("\n", 0, match.start()) + 1
        line_start = text.rfind("\n", 0, match.start()) + 1
        line_end = text.find("\n", match.start())
        if line_end < 0:
            line_end = len(text)
        yield line_no, text[line_start:line_end].strip()


rows = []
software_render_rows = []
for path in FILES:
    text = path.read_text(errors="replace")
    relative = path.relative_to(ROOT)
    for kind, pattern in PATTERNS:
        for line_no, line in scan(text, pattern):
            rows.append((kind, relative, line_no, line))
    for pattern in SOFTWARE_RENDER_PATTERNS:
        for line_no, line in scan(text, pattern):
            software_render_rows.append(
                ("software-renderer", relative, line_no, line))

rows.sort(key=lambda row: (str(row[1]), row[2]))
software_render_rows.sort(key=lambda row: (str(row[1]), row[2]))

for kind, path, line_no, line in rows + software_render_rows:
    print(f"{kind}\t{path}:{line_no}\t{line}")

print(f"RUNTIME_PLACEHOLDER_COUNT={len(rows)}")
print(f"SOFTWARE_RENDERER_COUNT={len(software_render_rows)}")

if "--check" in sys.argv and (rows or software_render_rows):
    print(
        f"runtime placeholder audit failed: {len(rows)} placeholder(s), "
        f"{len(software_render_rows)} software-renderer fallback(s)",
        file=sys.stderr,
    )
    sys.exit(1)
sys.exit(0)
