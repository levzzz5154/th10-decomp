# Oriented rectangle hit test at 0x0041E4D0: model at 207 of 226 bytes

2026-09-13. `0x0041E4D0` (226 bytes) is a fully self-contained `__thiscall`
region: no calls at all, its two arguments on the stack, and it needs no
cluster. A model now compiles to **207 of 226 bytes**.

## What the disassembly fixes

- The rectangle: centre at `+0x24` (three floats), rotation at `+0x3C`, the
  distance the point may sit behind the centre at `+0x40`, depth at `+0x44`.
- The head builds the point-to-centre difference into a *pair* of three-float
  locals (`var_18/var_14/var_10` and `var_C/var_8/var_4`, identical values), so
  the source stores the same difference twice — an explicit copy of one vector
  into another. Writing it as one vector, or as three scalars, compiles to 164
  bytes with a 4-byte frame; the two-copy form jumps to 207 with retail's
  six-slot frame.
- The rotation is `-rotation` through inline `fsin`/`fcos` (`fld [ecx+3Ch]`,
  `fchs`, `fld st`, `fsin`, `fxch st(1)`, `fcos`), i.e. `sinf`/`cosf` of one
  shared argument, used directly in the two rotated products. Assigning the
  sine and cosine to locals first spills one of them and loses the `fxch` form.
- The tests, in retail order: rotated y against `+0x40` (`>` fails),
  `depth * 0.5f` against the left edge (`<` fails), the right edge against the
  pooled `0.0f` at `0x470B04`, then `depth * -0.5f` (the pooled `-0.5f` at
  `0x470B78`) against the back edge (`>` fails); inside returns 2, outside 0.
  The constant at `0x470B0C` is the ordinary `0.5f`.

## The remaining 19 bytes

Retail re-uses its three slots for the rotated result (`var_C` holds the
relative x and is overwritten by the rotated x), so its frame stays six dwords.
The model keeps the relative vector live alongside the rotated locals, which
costs one extra slot and the frame is 0x1C instead of 0x18, with the store
offsets shifted by four throughout. Finding the source shape that lets the
rotated values overwrite the relative ones — most likely a compound assignment
into the same variables, or a helper that takes its vector by value — is the
next step, and it should also pull the 19 bytes in.

The model is preserved at `matching2/build/recovery-lab/oriented-rect/`; the
iteration loop is `matching2/build/diffunit.py --source src/math/oriented_rect.cpp
--symbol "?Contains@OrientedRect_0041e4d0@@QAEHPBUVector3_0041e4d0@@M@Z"
--address 0x41E4D0 --size 226`.
