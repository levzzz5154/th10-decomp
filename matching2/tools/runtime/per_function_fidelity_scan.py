#!/usr/bin/env python3
"""Phase-0 candidate generator: per-function overcredit/stub audit.

For every registry function whose promoted_source exists, extract the
source claim region (via the '// 0x004XXXXX' comment convention) and
score it: compression ratio (retail pseudocode chars / claim chars),
stub signals (MissingEdge arms, return-1 bodies, MSVC-only bodies,
binding checks), and claim-presence (registry claims an address the
source never comments -> improper promotion).
"""

import sys
from pathlib import Path

if __package__ in (None, ""):
    sys.path.insert(0, str(Path(__file__).resolve().parents[3]))

import json, re, sys

ROOT = Path(__file__).resolve().parents[2]
REGISTRY = ROOT / "function_registry.json"
from matching2.tools.reference.ida_export import body_sizes

CLAIM = re.compile(r"0x004([0-9A-Fa-f]{5})")
STUB_SIGNALS = [
    (r"Runtime_MissingEdge", "missing-edge arm"),
    (r"return\s*1\s*;", "return-1"),
    (r"host injects", "host-inject note"),
    (r"unwired|TODO|FIXME|not implemented|placeholder", "unwired note"),
    (r"g_[A-Za-z0-9_]+_bindings\.[A-Za-z0-9_]+", "binding check"),
    (r"overlay-only|hybrid-only", "overlay-only note"),
]

def strip_ws(text):
    return re.sub(r"\s", "", text)

def main():
    reg = json.loads(REGISTRY.read_text())
    sizes = body_sizes()  # addr(int) -> pseudocode chars
    rows = []
    for fn in reg["functions"]:
        source = fn.get("promoted_source")
        if not source:
            continue
        path = ROOT / source
        if not path.is_file():
            rows.append({
                "addr": fn["address"], "file": source, "missing_file": True,
                "status": fn.get("recovery_status"),
            })
            continue
        addr = int(fn["address"], 16)
        text = path.read_text(errors="replace")
        lines = text.splitlines()
        # find the claim comment for this address (any line containing 0x004xxxxx)
        idx = None
        for i, line in enumerate(lines):
            m = CLAIM.search(line)
            if m and int(m.group(1), 16) == addr & 0xFFFFF:
                idx = i
                break
        if idx is None:
            # exact-overlay claims are the *_Overlay symbols - legitimate;
            # semantic claims without an in-file address comment are suspects.
            if fn.get("recovery_status") == "exact-overlay":
                continue
            rows.append({
                "addr": fn["address"], "file": source, "claim_missing": True,
                "status": fn.get("recovery_status"),
                "retail_chars": sizes.get(addr, 0),
                "retail_bytes": fn.get("size", 0),
            })
            continue
        # claim region: from the comment to the next claim comment
        region = [lines[idx]]
        for j in range(idx + 1, len(lines)):
            if CLAIM.search(lines[j]):
                break
            region.append(lines[j])
        code = [l for l in region if l.strip() and not l.strip().startswith("//")]
        chars = max(len(strip_ws("".join(code))), 1)
        retail = sizes.get(addr, 0)
        ratio = round(retail / chars, 2) if retail else None
        signals = []
        joined = "\n".join(region)
        for pat, name in STUB_SIGNALS:
            if re.search(pat, joined):
                signals.append(name)
        # return-1-only body check: the function body is just `return 1;`
        body_only = (len(code) <= 2 and re.search(r"return\s*1\s*;", joined)
                     and "Runtime_MissingEdge" not in joined)
        rows.append({
            "addr": fn["address"], "file": source,
            "status": fn.get("recovery_status"),
            "retail_bytes": fn.get("size", 0),
            "retail_chars": retail, "claim_chars": chars, "ratio": ratio,
            "signals": signals, "body_only": body_only,
            "region_lines": len(region),
        })

    # ranking: suspicious first
    def rank(r):
        score = 0
        if r.get("missing_file") or r.get("claim_missing"): score += 100
        if r.get("body_only"): score += 60
        if r.get("signals"): score += 30 * len(r["signals"])
        r_ = r.get("ratio") or 0
        if r_ > 5: score += 25
        elif r_ > 3: score += 10
        return -score

    rows.sort(key=rank)
    for r in rows:
        if r.get("missing_file") or r.get("claim_missing"):
            print(f"MISSING {r['addr']:12s} {r['file']} status={r.get('status')} "
                  f"retail_chars={r.get('retail_chars', '?')} "
                  f"retail_bytes={r.get('retail_bytes', '?')}")
        else:
            ratio = f"{r['ratio']:>7}" if r['ratio'] is not None else "      -"
            print(f"{ratio} {r['addr']:12s} {r['file']:<55s} "
                  f"retail={r['retail_bytes']:>6}B chars={r['claim_chars']:>6} "
                  f"lines={r['region_lines']:>4} body_only={r['body_only']} "
                  f"signals={','.join(r['signals']) if r['signals'] else '-'}")
    print(f"\nTOTAL {len(rows)} promoted functions "
          f"({sum(1 for r in rows if r.get('claim_missing'))} claim-missing, "
          f"{sum(1 for r in rows if r.get('missing_file'))} file-missing, "
          f"{sum(1 for r in rows if r.get('body_only'))} return-1-only)")

if __name__ == "__main__":
    main()
