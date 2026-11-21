#!/usr/bin/env python3
"""Report matching-source progress from region entries, independently of a build."""

import argparse
from collections import Counter
import json
import re
from pathlib import Path
import sys

if __package__ in (None, ""):
    sys.path.insert(0, str(Path(__file__).resolve().parents[3]))

from matching2.tools.common.project_paths import DEFAULT_PROJECT, project_support

MANIFEST = project_support(DEFAULT_PROJECT, 'regions.json')
KINDS = ("semantic", "asm", "library", "data", "padding")
REPORTED = ("semantic", "equivalent", "asm", "library", "data", "padding")
LABELS = {
    "semantic": "Byte-matched game regions",
    "equivalent": "Equivalent C++ (assembly kept for the exact build)",
    "asm": "Assembly-only (no C++ recovery)",
    "library": "Toolkit runtime library",
    "data": "Embedded .text data",
    "padding": "Padding",
}


def summarize(regions, equivalent=()):
    """Use actual entries, never the generator's historical cached summary.

    ``equivalent`` is the manifest's ``equivalent_recoveries`` list: assembly
    regions that also have a checked C++ model.  They are reported apart from
    both exact C++ and the remaining assembly.
    """
    modelled = {entry["region"] for entry in equivalent}
    counts = Counter()
    sizes = Counter()
    for region in regions:
        kind = region["kind"]
        size = region["size"]
        if kind not in KINDS or type(size) is not int or size <= 0:
            raise ValueError("invalid region classification or size")
        if region["name"] in modelled:
            if kind != "asm":
                raise ValueError("an equivalent recovery must name an assembly region")
            modelled.discard(region["name"])
            kind = "equivalent"
        counts[kind] += 1
        sizes[kind] += size
    if modelled:
        raise ValueError("equivalent recovery names an unknown region")
    return {"regions": {kind: counts[kind] for kind in REPORTED},
            "bytes": {kind: sizes[kind] for kind in REPORTED}}


def recovered(summary, equivalent=None):
    """Share of the game's own code (C++ plus remaining assembly) that has C++ source.

    When built reports are available, also count matching bytes at their
    final retail offsets. Instruction alignment is not byte identity.
    """
    code = ("semantic", "equivalent", "asm")
    total_regions = sum(summary["regions"][kind] for kind in code)
    total_bytes = sum(summary["bytes"][kind] for kind in code)
    regions = summary["regions"]["semantic"] + summary["regions"]["equivalent"]
    size = summary["bytes"]["semantic"] + summary["bytes"]["equivalent"]
    exact = summary["bytes"]["semantic"]
    line = (f"Recovered: {100 * size / total_bytes:.1f}% of bytes ({size:,} of {total_bytes:,}), "
            f"{100 * regions / total_regions:.1f}% of regions ({regions:,} of {total_regions:,}); "
            f"byte-exact alone {100 * exact / total_bytes:.1f}% of bytes")
    if equivalent is not None:
        matching = size - sum(item['differing_bytes'] for item in equivalent)
        line += f"; matching retail offsets in recovered regions: {matching:,} of {total_bytes:,} game bytes"
    return line


# Match assembly keywords as C++ tokens, not in comments, strings or character literals.
_ASM = rb'\b(?:asm|_asm|__asm(?:__)?|_+emit)\b'
_ASM_WORD = re.compile(_ASM)
_CPP_TOKENS = re.compile(
    rb'//[^\n]*|/\*.*?\*/|(?:u8|[uUL])?R"(?P<delimiter>[^\s()\\]{0,16})\(.*?\)(?P=delimiter)"'
    rb'|"(?:\\.|[^"\\])*"|\'(?:\\.|[^\'\\])*\'|(?P<assembly>' + _ASM + rb')', re.S)


def cpp_parity_issues(project, regions, image_exact):
    """Check the packaged image and the maintained project, including build support."""
    if not image_exact:
        yield 'packaged executable SHA-256 differs from retail'
    for region in regions:
        if region['kind'] == 'asm':
            yield f"{region['address']}: exact link still uses {region['source']}"
    for path in sorted(project.rglob('*')):
        suffix = path.suffix.lower()
        if suffix in ('.s', '.asm') and path.is_file():
            yield f'{path.relative_to(project)}: assembly source'
        elif suffix in ('.c', '.cc', '.cpp', '.cxx', '.h', '.hh', '.hpp', '.hxx', '.inc', '.inl') and path.is_file():
            # Join physical lines before recognizing comments or multi-line tokens.
            source = re.sub(rb'\\\r?\n', b'', path.read_bytes())
            if _ASM_WORD.search(source) and any(m['assembly'] for m in _CPP_TOKENS.finditer(source)):
                yield f'{path.relative_to(project)}: inline assembly or instruction emitter'


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--manifest", type=Path, default=MANIFEST)
    parser.add_argument("--json", action="store_true", help="print machine-readable counts")
    args = parser.parse_args()
    manifest = json.loads(args.manifest.read_text())
    summary = summarize(manifest["regions"], manifest.get("equivalent_recoveries", ()))
    if sum(summary["bytes"].values()) != manifest["text_bytes"]:
        parser.error("region byte counts disagree with the declared .text size")
    if args.json:
        print(json.dumps(summary, indent=2))
    else:
        for kind in REPORTED:
            print(f"{LABELS[kind]}: {summary['regions'][kind]:,} regions / {summary['bytes'][kind]:,} bytes")
        print(f"Total .text: {sum(summary['bytes'].values()):,} bytes")
        print(recovered(summary))


if __name__ == "__main__":
    main()
