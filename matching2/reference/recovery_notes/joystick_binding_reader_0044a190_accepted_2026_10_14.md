# Joystick binding reader 0x0044A190: accepted as an equivalent recovery (2026-10-14)

`equivalent/platform/joystick_poll_0044a190.cpp` through
`layout/equivalent/joystick_poll_0044a190.json`: 833/833 bytes, **251 of 282
instructions identical**, 17 frame-offset instructions (frame 8 bytes
smaller), 10 classified hunks covering 16 instructions (6 structural).
The earlier drafts stood at 126/282 with every reconnaissance note calling the
remaining allocation "semantic". It was not; two source-shape facts closed it.

## 1. The action word is address-taken (the th06 controller shape)

The decompiled th06 `Controller::GetControllerInput` sets the buttons through
small helpers that take `&buttons`:

```cpp
SetButtonFromControllerInputs(&buttons, mapping.shootButton, TH_BUTTON_SHOOT, info.dwButtons);
```

Writing th10's reader the same way (helpers inlined by the compiler) changes the
IR the whole function is built from: the action word starts as a memory
variable and is promoted to a register later, after the CSE passes ran with
the pointer stores in place. Two retail facts that no earlier spelling
reproduced follow directly:

- the mask has no entry spill and lives in ESI for the whole function, with
  temporaries in EAX and the buttons word in EDX (the "parameter-lowering
  memory home" of the earlier notes only appears when the mask is a plain
  by-value parameter that is written after a call);
- the X axis reloads `wXmax`/`wXmin` for its second threshold (the store
  through `&buttons` between the two X statements killed the load CSE).

## 2. The signature is a stack-parameter function under the LTCG private convention

Retail takes the action word in ECX and pops `set`/`pad` (`RET 8`). The model
declares `unsigned short __stdcall ReadPad(unsigned short buttons, int set,
int pad)` and a synthetic direct caller (`JoystickPollEntry@12`, no roots), so
the whole-program pass moves `buttons` into ECX by itself (MdmFlexParams, see
memory note `msvc-c2-flex-params-entry-scan`). A declared `__fastcall` with an
unused EDX slot, rooted with no caller, measured 107 differing instructions
with the same body: the register parameter is lowered differently.

## 3. The Y axis: one limit read into a local

With the shape above the X block became byte-exact, but the Y block either
reloaded both limits (base register then forced out of EAX by the return
chain, 46 differing) or, with both limits in locals, merged the midpoint sum
(retail recomputes it). A 96-variant sweep over the Y spellings (limit
sources global/local/one local, test order, dead-zone statement or inline,
statement grouping, midpoint macro / shift / plain) found the retail shape:
`unsigned int ymax = caps.wYmax;` read once into a local, the dead zone as a
statement, and the 0x20 test written before the 0x10 test. The midpoint
spelling and the grouping are canonicalized away (all variants of those
compile identically).

## Remaining differences (all recorded)

- the frame is 0x154 in retail, 0x14C in the model: retail has 8 unused bytes
  below `info`. Any 8-byte struct local whose fields are enregistered leaves
  such a slot (a `DeadZone {x, y}` struct or a by-value `{set, pad}` struct
  parameter both reproduce the 0x154 frame) but each of those also moved the
  allocation, so the model keeps the plain locals; 17 frame-offset rows plus
  five indexed `movzx` rows (classed stack-slot-order) follow from it;
- the Y low threshold is computed directly in EAX instead of EBX plus a copy,
  with the Y position loaded one instruction earlier (3 hunks);
- the retry loop is aligned with `lea esp,[esp]` instead of `jmp` over
  `lea ecx,[ecx]` (the loop head sits one byte later).

## Method that worked

Measure every variant with the real gate (`equivalence.py --layout`, about one
second per build; the scratch wrapper kept the work directory for side-by-side
disassembly), and prefer whole-shape hypotheses from the sibling games' known
source over register-allocator tracing: the c2 traces explained *why* EAX was
unavailable to the caps base (its live range reached the return-value chain
through the unshared Y loads), but the fix was a source shape.

## 2026-10-17: named-local and goto-loop levers probed; parked

Probed the residual trio against the documented compiler levers, each measured
with `equivalence.py --layout` (~1.4 s/build):

- The Y low threshold as a named local (`unsigned int ylow = ...;` and with a
  named `ypos` too) compiles byte-identically to the inline expression:
  the single-use value is folded back, so the temp-register-rotation lever
  (named locals land in long-lived registers like retail's EBX) cannot fire.
- An 8-byte `DeadZone {x, y}` local with dead stores is removed outright; the
  note's live-field struct and by-value parameter forms were not re-run since
  the note records both move the allocation.
- The retry loop as `retry: ... if (again) goto retry;` (the memory's
  `jmp`-over-padding form) compiles byte-identically to the `while` spelling;
  the inverted top-tested `goto` form (`retry: if (hr != X) return; ...`) does
  move codegen but overshoots to 12 hunks (the loop back-edge becomes a single
  `jl` and the function tail gains 13 `int3` bytes).

Region stays equivalent (157 differing bytes). The frame-shape lever still
needs a struct form whose colour lands below `info` without shifting the
rgbButtons array; the stackpack colour mechanics
(`msvc-c2-stack-slot-order-by-reference-weight`) are the route.
