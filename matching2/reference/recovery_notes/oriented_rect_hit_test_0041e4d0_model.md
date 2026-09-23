# OrientedRect 0x0041E4D0 — variant sweep, prior model still best

2026-09-17. Re-measured the retained model against six new source shapes; none
beat the recorded 207/226.

| variant | extent | outcome |
| --- | ---: | --- |
| retained model (twin copies, direct `cos(-rotation)`) | 207 | prior best, 169 differing in common prefix |
| same with `float angle = -rotation;` hoisted | 211/220/217 | the named angle local reintroduces the `angle` spill slot and shifts the frame to `0x1C`; no byte gain |
| shared `sin(angle)`/`cos(angle)` locals `s`,`c` | 220 | the two named locals add two scratch slots, lose the shared `fld st(0)` x87 block (two separate `fsin`/`fcos` pairs) |
| single relative vector, no twin copy | 168 | frame drops to `push ecx`; loses the retail copy entirely |
| rotated values written back into the relative vector | 217 | frees the frame but the scheduler then drops both edge pairs to register locals and emits `fstp st(0)` discards retail keeps |

Two facts confirmed: (1) the byte-identical `fld [ecx+3Ch]; fchs; fld st(0);
fsin; fxch; fcos` block appears only when the sine/cosine *expressions* (not
named locals) share one negated argument — hoisting `-rotation` into a named
local or naming `s`/`c` reorders or duplicates the x87 sequence. (2) The 19-byte
residual is the twin-copy frame: every shape that frees the copy slot also frees
the edge slots, losing a different region of the body. The retail source shape
is still the twin copy with the *expression-shared* angle.

## Readable source model addendum — 2026-09-23

`matching2/msvc/src/math/oriented_rect.cpp` now contains an inline-assembly-free
semantic model for `0x0041E4D0`. Ghidra reports a `__thiscall` shape with the
receiver in ECX, a point pointer at `[esp+4]`, a float at `[esp+8]`, and
`RET 8`. The point is translated by the three stored center components; the
XY offset is rotated by the negative object rotation, then compared against
the stored extents with the stack float expanding both sides. The function
returns `2` when every comparison passes and `0` otherwise. The stack float is
called `radius` in the source because it is added to/subtracted from the
transformed coordinates; rotation comes from the object field at `+0x3C`.

Ghidra reports one data reference to the function from `0x0046DA80`. The
little-endian pointer sequence there begins with `0x0041E4D0` and continues
with `0x0041BF90`, consistent with a vtable-style entry; Ghidra reports no
direct code caller. Field names in the source retain offsets for the less
certain structure members.

This source change does not promote the function or establish a byte match.
The historical best readable candidate remains 207 bytes against the 226-byte
retail body, with 169 differing bytes in the common prefix. In that candidate
shape, the direct `sin(-rotation)` / `cos(-rotation)` expressions sharing the
negated angle retained the target's `fld`, `fchs`, `fld st(0)`, `fsin`, `fxch`,
`fcos` block. Named trigonometric locals or a hoisted negated-angle local
changed that schedule. The rest of the x87/body schedule remains unresolved;
the current source has not been built or measured.


## Semantic source registration (2026-09-23)

The readable member body now owns the `0x0041E4D0` region under
`?IntersectsCircle@OrientedRect_0041E4D0@@QBEHPBUPoint3_0041E4D0@@M@Z`. The
old ASM row is preserved in `previous_record`, with its raw aliases retained.
This records the source-level model only: the earlier 207/226-byte candidate
and x87 instruction ordering caveats remain, and current byte equivalence has
not been checked.
