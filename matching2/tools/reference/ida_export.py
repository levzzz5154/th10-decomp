#!/usr/bin/env python3
"""Query the checked-in IDA exports (ida/th10.exe.{c,asm,h}) the way the
Ghidra MCP bridge queries the live project.

The ida/ folder is the static, portable decompiler evidence: Hex-Rays
pseudocode (th10.exe.c), the instruction listing (th10.exe.asm) and the type
library (th10.exe.h).  The reconstruction-fidelity gate measures promoted
sources against the .c; the .asm is the instruction-level truth for exactness
claims; the .h carries the local type definitions.  Everything is checked in,
so no IDA license or Ghidra installation is needed to work from it.

This module mirrors the Ghidra bridge's query surface (decompile, callers,
asm, types) over the static files.  Scripts can import it directly; the CLI
wraps the same functions.

CLI:
  python3 tools/reference/ida_export.py functions [--json]
  python3 tools/reference/ida_export.py decompile 0x0044DF70 [--strip-decls]
  python3 tools/reference/ida_export.py callers 0x0044DF70
  python3 tools/reference/ida_export.py callees 0x0044DF70
  python3 tools/reference/ida_export.py asm 0x0044DF70
  python3 tools/reference/ida_export.py types [substring]
"""

import argparse
import json
import re
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
IDA_DIR = ROOT.parent / "ida"
C_SOURCE = IDA_DIR / "th10.exe.c"
ASM_SOURCE = IDA_DIR / "th10.exe.asm"
H_SOURCE = IDA_DIR / "th10.exe.h"

# The same section marker the fidelity audit keys on: `//----- (0044DF70)`.
FUNCTION_HEADER = re.compile(r"^//----- \(([0-9A-F]{8})\) -+", re.M)
# IDA emits one declaration per line, each with a trailing register comment.
IDA_DECLARATION = re.compile(r"^\s+[A-Za-z_][\w \*]*;\s*//.*$", re.M)
# A call-site token in the pseudocode: `sub_44DF70(` (uppercase hex).
CALL_TOKEN = re.compile(r"\bsub_([0-9A-Fa-f]{3,8})\b")

_cache = {}


def _read(path):
    if path not in _cache:
        if not path.is_file():
            raise SystemExit(f"IDA export not found: {path}")
        _cache[path] = path.read_text(errors="replace")
    return _cache[path]


def _c_text():
    return _read(C_SOURCE)


def _asm_text():
    return _read(ASM_SOURCE)


def _h_text():
    return _read(H_SOURCE)


def _strip_ws(text):
    return re.sub(r"\s", "", text)


def sections():
    """Ordered (address, body) pairs for every function section in the .c."""
    text = _c_text()
    starts = [(int(m.group(1), 16), m.start()) for m in FUNCTION_HEADER.finditer(text)]
    result = []
    for index, (address, start) in enumerate(starts):
        end = starts[index + 1][1] if index + 1 < len(starts) else len(text)
        result.append((address, text[start:end]))
    return result


def functions():
    """List all functions in the export: address, signature, body sizes."""
    rows = []
    for address, body in sections():
        lines = [line for line in body.splitlines() if line.strip()]
        signature = ""
        for line in lines[1:]:  # first line is the section marker
            if not line.startswith("//"):
                signature = line.strip()
                break
        stripped = IDA_DECLARATION.sub("", body)
        rows.append({
            "address": f"0x{address:08X}",
            "signature": signature,
            "code_chars": len(_strip_ws(stripped)),
            "lines": len(lines),
        })
    return rows


def decompile(address, strip_decls=False):
    """Pseudocode section for one function, or None when not function-ized."""
    want = int(address, 16) if isinstance(address, str) else int(address)
    for got, body in sections():
        if got == want:
            if strip_decls:
                return IDA_DECLARATION.sub("", body)
            return body
    return None


def body_sizes():
    """Map retail address -> non-whitespace pseudocode size (audit view)."""
    return {address: len(_strip_ws(IDA_DECLARATION.sub("", body)))
            for address, body in sections()}


def callers(address):
    """Addresses of functions whose pseudocode calls `address` directly."""
    want = int(address, 16) if isinstance(address, str) else int(address)
    token = f"sub_{want:X}"
    pattern = re.compile(rf"\b{re.escape(token)}\b", re.IGNORECASE)
    found = []
    for got, body in sections():
        if got == want:
            continue
        if pattern.search(body):
            found.append(got)
    return found


def callees(address):
    """Addresses this function's pseudocode calls directly (best effort)."""
    want = int(address, 16) if isinstance(address, str) else int(address)
    body = decompile(want)
    if body is None:
        return []
    known = {f"sub_{got:X}": got for got, _ in sections()}
    found = []
    for token in CALL_TOKEN.findall(body):
        key = f"sub_{token.upper()}"
        if key in known and known[key] not in found and known[key] != want:
            found.append(known[key])
    return found


def asm(address):
    """Instruction listing for one function, or None when not in the .asm."""
    want = int(address, 16) if isinstance(address, str) else int(address)
    token = f"sub_{want:X}"
    text = _asm_text()
    match = re.search(
        rf"^; [^\n]*\n{re.escape(token)} proc near\r?\n(.*?)\r?\n{re.escape(token)} endp",
        text, re.M | re.S | re.IGNORECASE)
    if not match:
        return None
    return match.group(0)


def types(substring=None):
    """Type-library entries from the .h: struct names, or full definitions
    when a substring is given."""
    text = _h_text()
    if substring is None:
        names = re.findall(r"^struct (\w+)", text, re.M)
        names += re.findall(r"^typedef .*?(\w+);", text, re.M)
        return sorted(set(names))
    blocks = re.findall(r"^struct \w+ \{.*?\n\};", text, re.M | re.S)
    blocks += re.findall(r"^typedef .*?;", text, re.M | re.S)
    return [block for block in blocks if substring in block]


def main():
    parser = argparse.ArgumentParser(description=__doc__,
                                     formatter_class=argparse.RawDescriptionHelpFormatter)
    sub = parser.add_subparsers(dest="command", required=True)

    p = sub.add_parser("functions", help="list every function in the export")
    p.add_argument("--json", action="store_true")

    p = sub.add_parser("decompile", help="print a function's pseudocode")
    p.add_argument("address")
    p.add_argument("--strip-decls", action="store_true")

    p = sub.add_parser("callers", help="find direct callers in the pseudocode")
    p.add_argument("address")

    p = sub.add_parser("callees", help="find direct callees in the pseudocode")
    p.add_argument("address")

    p = sub.add_parser("asm", help="print a function's instruction listing")
    p.add_argument("address")

    p = sub.add_parser("types", help="list types, or show matching definitions")
    p.add_argument("substring", nargs="?")
    args = parser.parse_args()

    if args.command == "functions":
        rows = functions()
        if args.json:
            print(json.dumps(rows, indent=1))
        else:
            for row in rows:
                print(f"{row['address']}  {row['code_chars']:6d} chars  "
                      f"{row['lines']:5d} lines  {row['signature']}")
    elif args.command == "decompile":
        body = decompile(args.address, args.strip_decls)
        if body is None:
            sys.exit(f"no pseudocode section for {args.address}")
        print(body, end="")
    elif args.command == "callers":
        found = callers(args.address)
        if not found:
            sys.exit(f"no direct pseudocode callers of {args.address}")
        for address in found:
            print(f"0x{address:08X}")
    elif args.command == "callees":
        found = callees(args.address)
        if not found:
            sys.exit(f"no direct pseudocode callees for {args.address}")
        for address in found:
            print(f"0x{address:08X}")
    elif args.command == "asm":
        listing = asm(args.address)
        if listing is None:
            sys.exit(f"no proc block for {args.address} in the .asm")
        print(listing)
    elif args.command == "types":
        for entry in types(args.substring):
            print(entry)
            if args.substring:
                print()


if __name__ == "__main__":
    main()
