# Sprite descriptor update helper `0x00424480`

The new source-only model is in
[`sprite_descriptor_update_00424480_semantic.cpp`](../../msvc/src/game/sprite_descriptor_update_00424480_semantic.cpp).
It is separate from the assembly baseline in `src/game/sprite_descriptor.cpp`;
the manifest and shared declarations are unchanged.

## Behavior

The helper looks up the supplied animation handle in the primary animation
bucket, then the secondary bucket, using the manager pointer stored at
`0x00491C10`. It reads the animation object's resource pointer at `+0x394`,
then converts four resource floats in this order: `+0x30`, `+0x34`, `+0x0C`,
and `+0x08`. It does this work before checking the destination slot.

If the signed dword at descriptor `+0x04` is nonnegative, it leaves the
descriptor untouched and returns `-1` in EAX. Otherwise it writes the first
dword pointed to by animation object `+0x308` into descriptor `+0x04`, copies
the four caller dwords into `+0x08`, `+0x0C`, `+0x10`, and `+0x14`, writes the
converted values from resource `+0x08`, `+0x0C`, `+0x34`, and `+0x30` to
descriptor `+0x18`, `+0x1C`, `+0x20`, and `+0x24`, then zeros `+0x28`. Retail
returns EAX `0` on this path. Field names remain offset-based because the
helper does not establish their higher-level meanings.

The lookup returns null for handle zero or a missing handle, but this helper
does not check that result before reading the animation object's `+0x394`.
The model keeps that precondition: the handle must resolve. It also assumes a
valid 32-bit retail manager, animation object, resource descriptor, and
destination buffer of at least `0x2C` bytes.

## ABI and call graph

The retail region is 162 bytes, `0x00424480..0x00424521`. The helper's actual
inputs are a private destination pointer in ESI and five stack dwords: handle,
then values for destination offsets `+0x08`, `+0x0C`, `+0x10`, and `+0x14`.
Both exits use `RET 0x14`, so the callee removes those five stack dwords. The
body saves ECX as scratch and later overwrites that stack slot with the second
conversion result; ECX is not a receiver input. Ghidra initially inferred
`__thiscall` and labeled ECX as `this`; the current annotation records the five
stack arguments and documents the actual ESI live-in separately.

Direct callers are `0x00422AB0` (call at `0x00422B5D`), `0x004231D0` (call at
`0x004232A1`), and `0x00423370` (call at `0x00423441`). Each loads the manager
pointer from `0x00491C10` into ESI, then passes the handle followed by `0x20`,
`0x10`, `0x180`, and `0x1C0`; this manager pointer is also the output receiver
for the offset writes. Direct callees are:

| Address | Role |
| --- | --- |
| `0x004491C0` | Find an animation by handle, searching the primary then secondary bucket. The private call has manager context in EDX and the handle on the stack; the ECX input is unused by this leaf. |
| `0x00463B2C` | Retail `__ftol2` helper, called four times with each float loaded into x87 ST0. |

The source model exposes
`extern "C" int UpdateSpriteDescriptorModel_00424480(void* descriptor, int handle, int value_08, int value_0C, int value_10, int value_14)`.
All six parameters use the ordinary C++ compiler convention. The first
parameter represents the retail ESI pointer explicitly; the model does not
place it in ESI, pass the five remaining values using the retail stack layout,
or clean 20 bytes with `RET 0x14`. Its `int` return represents only EAX status;
the helper's incidental EDX value is not modeled or consumed by these callers.
The pause-menu source candidate calls this model with the manager pointer as
the explicit descriptor argument instead of calling the retail address
through an ordinary function pointer.

## Ghidra annotation

Ghidra now names the retail function `UpdateAnimationDescriptorFromHandle`
and records an `int __stdcall` prototype with the five stack arguments. Its
plate comment identifies ESI as the undocumented live-in and records the
three callers, register handoff, store behavior, and source-model caveats.
This standard prototype represents the stack cleanup and EAX result; the
private ESI input still requires the comment.

## Exactness limits

The model spells conversion as ordinary `static_cast<int>(float)`. This
captures normal finite, in-range float-to-integer use, but does not claim the
retail helper's exact x87 precision, rounding-control, exceptional, or
out-of-range behavior. The lookup is represented by its recovered bucket
walk rather than a call using the private `0x004491C0` register convention.
This is a semantic source model, not a replacement ABI entry or byte-match
claim. No build, probe, or test was run.
