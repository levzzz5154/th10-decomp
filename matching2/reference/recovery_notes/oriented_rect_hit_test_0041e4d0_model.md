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
