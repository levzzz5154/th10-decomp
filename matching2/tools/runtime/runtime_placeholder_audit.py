#!/usr/bin/env python3
"""Inventory production fallbacks that can make an inert runtime look green.

Every pattern here marks a call site that compiles and links but performs no
recovered work: a host adapter that only logs, a hook bound to an empty
lambda, or a runtime binding whose call site is skipped when the binding is
unset. Pass --check to fail the build when any of them survive.
"""

from pathlib import Path
import json
import re
import sys

ROOT = Path(__file__).resolve().parents[2]
FILES = [
    *sorted((ROOT / "src").rglob("*.cpp")),
    *sorted((ROOT / "standalone").glob("*.cpp")),
    *sorted((ROOT / "include").rglob("*.hpp")),
    *sorted((ROOT / "include").rglob("*.h")),
]

# Matched against the whole file, not line by line: a Log("host adapter call
# split across lines used to slip through the line-oriented scan.
PATTERNS = (
    # Reconstructed functions must remain C++; the build-generated assembly
    # used to import retail data is outside these production source files.
    ("naked-function", re.compile(
        r'__declspec\s*\(\s*naked\s*\)|__attribute__\s*\(\([^)]*\bnaked\b')),
    ("inline-assembly", re.compile(
        r'\b(?:__asm__?|asm)\s*(?:(?:__volatile__|volatile)\s*)?[({]')),

    ("host-adapter", re.compile(r'Log\(\s*"host adapter', re.DOTALL)),
    ("empty-lambda", re.compile(r'=\s*\[\][^{;]*\{\s*\}\s*;', re.DOTALL)),
    # The pattern above only sees a lambda that is ASSIGNED. An inert lambda
    # passed straight into a hook struct or a call argument - which is how most
    # of them are actually written - slipped past it entirely, hiding fifteen
    # do-nothing sound and MIDI teardown edges from this gate.
    ("empty-lambda-arg", re.compile(
        r'\[\]\s*\([^)]*\)\s*(?:->\s*[A-Za-z_][\w:<>*&\s]*?)?\{\s*\}')),
    ("optional-binding", re.compile(
        r'g_[A-Za-z0-9_]+_bindings\.[A-Za-z0-9_]+\s*!=\s*0')),
    # A named function with an empty body is the same inert edge as an empty
    # lambda; the lambda-only pattern missed 22 of them, so the count read
    # zero while the boot path was still full of do-nothing stubs.
    ("empty-function", re.compile(
        r'^[ \t]*(?:static\s+)?(?:void|int|unsigned int|long|bool)\s+'
        r'\**[A-Za-z_]\w*\s*\([^;{)]*\)\s*\{\s*\}', re.MULTILINE)),
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

# host-adapter, empty-lambda and optional-binding are all genuinely cleared,
# so they stay hard-zero. empty-function was invisible until the pattern was
# added and has a standing population, so it ratchets against a baseline: the
# count may fall but never rise.
BASELINE = ROOT / "tools" / "runtime" / "runtime_placeholder_baseline.json"
RATCHETED = ("empty-function", "empty-lambda-arg")
empty_functions = [r for r in rows if r[0] in RATCHETED]
strict = [r for r in rows if r[0] not in RATCHETED]

baseline_count = 0
exemptions = {}
if BASELINE.is_file():
    _baseline = json.loads(BASELINE.read_text())
    baseline_count = _baseline.get("empty_function_count", 0)
    # A named empty function is normally an inert edge standing in for work
    # that has not been recovered, which is exactly what the ratchet is for.
    # A few are empty because the host genuinely has no work to do at that
    # edge - a retail callback whose retail-side job does not exist in an
    # immediate-mode host, for instance. Those may be exempted, but only by
    # naming the exact function and writing down why, so that adding one is a
    # reviewable diff rather than a silent count bump.
    exemptions = _baseline.get("exempt", {})

# Keyed by "<path>\t<declaration>" rather than by line number: an exemption
# has to survive unrelated edits above it, and the declaration is also what a
# reviewer needs to see to judge the reason.
def exemption_key(row):
    return f"{row[1]}\t{' '.join(row[3].split())}"

exempt_hits = [r for r in empty_functions if exemption_key(r) in exemptions]
empty_functions = [r for r in empty_functions
                   if exemption_key(r) not in exemptions]
for row in exempt_hits:
    print(f"exempt\t{row[1]}:{row[2]}\t{exemptions[exemption_key(row)]}")

print(f"RUNTIME_PLACEHOLDER_COUNT={len(strict)}")
print(f"SOFTWARE_RENDERER_COUNT={len(software_render_rows)}")
print(f"EMPTY_FUNCTION_COUNT={len(empty_functions)}")
print(f"EMPTY_FUNCTION_BASELINE={baseline_count}")
print(f"EMPTY_FUNCTION_EXEMPT={len(exempt_hits)}")

if "--update-baseline" in sys.argv:
    BASELINE.write_text(json.dumps({
        "comment": "Named empty host functions and inert hook lambdas. This "
                   "count may only fall. It was re-established when the "
                   "empty-lambda-arg pattern was added: that pattern exposed "
                   "19 do-nothing hook edges the assigned-lambda pattern had "
                   "never seen. Thirteen of those were fixed on the spot; the "
                   "rest are edges whose subsystem the host does not build. "
                   "see tools/runtime/runtime_placeholder_audit.py.",
        "empty_function_count": len(empty_functions),
        "files": sorted(f"{r[1]}:{r[2]}" for r in empty_functions),
        "exempt": exemptions,
    }, indent=2) + "\n")
    print(f"baseline written: {len(empty_functions)} empty functions")
    sys.exit(0)

if "--check" in sys.argv:
    failed = False
    if strict or software_render_rows:
        print(f"runtime placeholder audit failed: {len(strict)} placeholder(s), "
              f"{len(software_render_rows)} software-renderer fallback(s)",
              file=sys.stderr)
        failed = True
    if len(empty_functions) > baseline_count:
        print(f"empty host functions rose from {baseline_count} to "
              f"{len(empty_functions)}; an inert stub was added",
              file=sys.stderr)
        failed = True
    if failed:
        sys.exit(1)
sys.exit(0)
