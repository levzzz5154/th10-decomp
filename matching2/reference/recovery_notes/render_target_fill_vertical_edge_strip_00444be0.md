# Render target vertical edge strip at 0x00444BE0

## Ghidra evidence

Live Ghidra analysis of `th10.exe` identifies a 201-byte leaf body from
`0x00444BE0` through `0x00444CA8`. The function has no direct callers, incoming
xrefs, outgoing xrefs, or callees in the current database. A search for the
little-endian address as a stored pointer also found no matches. This does not
rule out a computed indirect entry, but no dispatch or call setup for this
function has been identified.

Ghidra assigns a `__fastcall` label because the target pointer is in ECX, but
the complete entry state is private: the signed vertex count is already in
EAX and the destination buffer is in EBX. Ordinary MSVC x86 `__fastcall`,
`__thiscall`, `__stdcall`, and `__cdecl` declarations cannot describe those
three locations together. The adjacent 0x00444B10 horizontal-strip filler has
the same ECX/EAX/EBX entry arrangement. The nearby 0x00444CE0 textured strip
renderer is a distinct function: it receives a manager/entity pair and two
stack arguments, and does not call either filler.

## Verified behavior

The function returns `-1` when `count < 3`; otherwise it writes geometry and
returns zero. Let `bounds` be the address loaded from `target + 0x394`. It
computes

```text
step     = (*(float *)(bounds + 0x2C) - *(float *)(bounds + 0x24))
           / ((count + 1) / 2 - 1)
y_start  = *(float *)(target + 0x58) + *(float *)(bounds + 0x2C)
x_left   = *(float *)(target + 0x54) + *(float *)(bounds + 0x20)
x_right  = *(float *)(target + 0x54) + *(float *)(bounds + 0x28)
```

The denominator uses integer division. Both y sequences start at `y_start`
and subtract `step` after each write.

For `i` starting at zero, with a `0x38`-byte stride, the first loop runs
`ceil(count / 2)` times and writes these four dwords at
`output + 0x0C + i * 0x38`:

| Offset | Value |
| --- | --- |
| `+0x00` | `1.0f` |
| `+0x04` | raw dword from `target + 0x2FC` |
| `+0x08` | `x_left` |
| `+0x0C` | current y coordinate |

The second loop runs `floor(count / 2)` times and writes the same four fields
at `output + 0x28 + i * 0x38`, using `x_right` for x. Each group starts
0x1C bytes after the previous logical vertex's group: the first loop fills
even-numbered slots, while the second fills odd-numbered slots. The gaps
between those four-dword groups are untouched. In assembly, x87 keeps
each loop's current y value in its floating-point stack while the loop writes
that sequence. The two loops write alternating groups in the destination
stride, but execute separately; this scheduling is part of the exact 201-byte
body and is not itself a semantic side effect.

The horizontal sibling at `0x00444B10` corroborates the same minimum-count
check, stride, raw depth/reciprocal fields, and two-boundary interpolation
pattern with the x/y axes exchanged.

## Status

No source-level implementation was substituted. A typed function with a
conventional signature could express the geometry, but it would not receive
the actual EAX/ECX/EBX entry state and cannot replace this address faithfully.
The exact naked wrapper remains until a real indirect caller or a compiler
context that establishes the private entry tuple is found. No build, probe, or
test was run for this audit.
