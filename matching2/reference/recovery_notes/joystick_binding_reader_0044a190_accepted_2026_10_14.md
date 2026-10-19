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

## 2026-10-17: the colour dump, and the residual measured exactly

`compiler_traces/stackpack/trace_stackcolors_cl.py` was broken here — it armed
its `hbreak` before `c2.dll` was mapped, so gdb parked the breakpoint and the
run ended in `ERR error('No registers.')`. Fixed in the tracer (wait on
`stop-on-solib-events` until the module is in `gdb.objfiles()`, then arm);
it now produces a full dump for this unit:

```
LIST ... index=0 size=4   weight=8  _buttons  conflicts=[1, 2]
LIST ... index=1 size=4   weight=3  _pad      conflicts=[0, 2]
LIST ... index=2 size=4   weight=1  _set      conflicts=[0, 1]
LIST ... index=3 size=52  weight=7  _info     conflicts=[0, 1, 3, 4]
LIST ... index=4 size=272 weight=11 _js       conflicts=[0, 1, 3, 4]
ALLOTEMP ecx(size)=272 esi/0x1c=4
ALLOTEMP ecx(size)=52  esi/0x1c=3
```

The five elements' sizes sum to 336, which with alignment is retail's
`sub esp,0x154` (340). The model's frame is `sub esp,0x14c` (332) — exactly
**8 bytes short** — and that shows up as the `rgbButtons` array landing at
`[esp+0x78]` in retail against `[esp+0x70]` in the model (the five
`movzx eax,BYTE PTR [esp+reg*1+0x78]` hunks are all that same shift).

So the residual is one missing 8-byte slot below `info`, not a general
misordering: everything else about the frame agrees. The `DeadZone {x,y}`
spelling already recorded was dropped as dead stores, and a live-field struct
moves the allocation without landing it; the remaining question is what
8-byte element retail carried. Region stays equivalent.

The obvious 8-byte candidates were then tested — the retry loop's `long hr`
and `int retryCount` (exactly 8 bytes of state) and the two axis deadzones,
each wrapped into one aggregate, plus both together and a declaration-order
swap. Six variants measured with the byte script:

| variant | identical | hunks | differing bytes |
| --- | --- | ---: | ---: |
| baseline | 251/282 | 10 | 157 |
| `retry-struct` | 251/282 | 10 | 157 |
| `retry-swapped` | 251/282 | 10 | 157 |
| `axis-pair-struct` | 251/282 | 10 | 157 |
| `retry-struct-init` | 238/282 | 16 | 508 |
| `axis-pair-direct` | 217/282 | 14 | 533 |
| `both-structs` | 238/282 | 16 | 508 |

The plain struct forms are folded back to the same allocation and the
aggregate-initialised ones regress, so the missing 8 bytes are not any of the
named pairs. Whatever retail carried left no name in this function. Region
stays equivalent.

## 2026-10-17: the 8-byte-home lever from item_update does not transfer

A frame-size survey across all 33 layouts found four regions whose prologue
disagrees, all by whole slots:

| region | retail | model | gap |
| --- | --- | --- | --- |
| `item_update` | `0x58` | `0x50` | 8 short — closed by `volatile double dx` |
| `joystick_poll` | `0x154` | `0x14c` | 8 short |
| `enemy_execute` | `0x2c4` | `0x2b4` | 16 short |
| `replay_save` | `0x124` | `0x12c` | 8 long |

For `item_update`, forcing one `double` product to memory supplies the missing
8-byte home and improves the match by 214 differing bytes. The same lever was
tried here, where there is no 64-bit value of its own, by forcing 8 bytes of
existing state to memory. Measured against the baseline 251/282, 10 hunks, 157
differing bytes:

| variant | identical | hunks | differing bytes |
| --- | --- | ---: | ---: |
| `volatile-buttons` | 265/282 | 12 | 401 |
| baseline | 251/282 | 10 | 157 |
| `volatile-retry-pair` (`hr` + `retryCount`) | 230/282 | 19 | 491 |
| `volatile-axis-pair` | 221/282 | 10 | 546 |
| `volatile-hr` | — | — | unexplained difference between the two model links |
| `volatile-double` | — | — | link error, `__fltused` unresolved |

Nothing lands: `volatile-buttons` picks up 14 instructions but more than
doubles the differing bytes, and the pairs regress outright. So the missing
slot here is not any of the named state, and unlike `item_update` there is no
value whose natural home is 8 bytes. Region stays equivalent.

# Joystick binding reader 0x0044A190: the frame closed (2026-10-18)

The frame lever finally fired: `info` is embedded in a small stack record
instead of standing alone, and the record's leading words fill retail's 8
unused bytes below `info`:

```cpp
struct State {
    unsigned int deadzone;
    unsigned int ymid;
    JoyInfoEx info;
} st;
```

Mechanism (font_atlas_convert_00436da0 / `msvc-local-aggregate-elements-limited-to-ecx-ebx`):
a local aggregate keeps its whole stack block, and the small members are
register candidates limited to ECX/EBX, so a promoted member leaves its home
dead — exactly the "8 unused bytes below `info`" this note has chased since
2026-10-14. With the block in place the whole frame group matches retail
(`sub esp,0x154`, cookie at `[esp+0x150]`, `info` at `[esp+0x14]`, `js` at
`[esp+0x48]`, `rgbButtons` at `[esp+0x78]`): the 17 frame-offset rows, the
five indexed `movzx` rows and the earlier `stack-slot-order` hunks all
disappear, `frame_offset` is now 0.

Two facts make the shape work:

- the aggregate needs at least one small member ahead of `info` (a bare
  `struct { JoyInfoEx info; }` changes nothing — measured 157 bytes, unchanged);
  one member is enough (`deadzone` alone or `ymid` alone reproduce the frame);
- the `ymid` member is what moves the Y midpoint off the rotating expression
  temporaries (aggregate members are ECX/EBX-constrained, so the midpoint is
  no longer placed in EAX like a single-use temporary). The Y block shrinks
  from three hunks to a reordered chain, and the retry-loop filler shrinks
  from the 7-byte `lea esp,[esp]` to a 2-byte `mov edi,edi`.

Measured with `variant.py` / `equivalence.py --layout` (~1.2 s/build), from
the 2026-10-14 accepted baseline **251/282 identical, 10 hunks, 157
differing bytes** to **264/282, 7 hunks, 116 differing bytes**,
`base_index_order: 0`, `frame_offset: 0`, `not_equivalent: []`. The layout's
`frame_shift` record is gone.

## Levers ruled out today (all measured)

| lever | result |
| --- | --- |
| separate `ydeadzone` (splitting the shared deadzone role) | 756 bytes — sharing one `deadzone` between X and Y is load-bearing |
| named `ymid` shared by both Y statements | 505 — the merged sum is wrong; retail recomputes |
| `ymid` reassigned per statement (plain local) | 135→156 on the old shape; folded back |
| ymin-only named limit | 134 (1 byte better) but adds a load-order hunk; kept the ymax spelling |
| both limits named / declaration hoisting | 498–800 |
| helper parameter reorder with call sites matched (candidate numbering) | identical to base (helpers front-end inline) |
| `static`/`__forceinline`/non-static helpers, `__forceinline` midpoint and deadzone functions, `GetPadDevice`/`GetCaps` accessors | all byte-identical to base |
| by-value `{set, pad}` struct parameter | frame 0x15c (8 too big), entry loses the `mov ebx,eax` binding copy, model function name changes |
| `unsigned __int64 selection` parameter | 785 |
| one big `PollState { reserved[2]; info; js; }` | 350, frame 0x15c, aliasing shifts the button tests |
| `DeadZone {x,y}` / `dz[2]` / `dz[3]` / retry `[2]` aggregates | 157 (scalarized) or 756+ (deadzone split) |
| `PadDevice* dev` local, caps-reference local | 736–768 |
| volatile/signed/long deadzone, shift spelling, ypos naming, y-high/low named thresholds, X/Y statement swaps, one-expression returns, twin locals, restated statements | 116-equivalent, 137, 152–157, or 487–762 — none below 116 |

## Remaining differences (7 hunks, 116 bytes)

- the Y threshold block (5 hunks, offsets 0x15a–0x17c): retail computes the
  low threshold in EBX (`mov ebx,edi; add ebx,edx … shr ebx,1; sub ebx,ecx;
  mov eax,ebx`) with the `dwYpos` reload late in EBX; the model reorders the
  two Y terms and holds the midpoint in EDI/EBX with `dwYpos` in EDI. The
  whole delta is one ChoosePhysReg decision (the Y midpoint candidate lands
  in EAX like a rotation temporary instead of EBX like a named/multi-use
  value); the scheduler difference (`shr` placement, the ypos hoist) follows
  from the register, because the anti-edges from EAX's later redefinitions
  (`sbb eax,eax`, `and eax,0x10`, the OR chain) inflate the temporary's
  successor count and hoist it.
- one DirectInput scratch register (0x19e): retail loads the pad index into
  EDX for the device table lookup, the model into EAX (the argument-evaluation
  rotation is one step apart, `msvc-inline-accessors-and-comdat-callees`).
- the retry-loop filler (0x1cb): retail `jmp` over `lea ecx,[ecx+0x0]`, model
  `mov edi,edi` — 5 filler bytes vs 2, a consequence of the Y block being
  3 bytes shorter.

`msvc-c2-choosephysreg-cost-score` is the rule for the last step: the Y
midpoint must present as a candidate (not a rotation temporary) before
ChoosePhysReg, or its contest with the `dwYpos` load for EBX must flip. The
regalloc tracer (`trace_choose_physreg.py`, cmds.json from the plain `cl`
line) dumps the contest per candidate.

## 2026-10-19: dead `st.ymid` store removed (5 -> 4 differences)

A 12-spelling sweep over the Y block was run. It varied named `ymin`/`ymax` locals, `st.ymid` reuse, and the 0x20/0x10 order. Only dropping the `st.ymid` assignment moved anything; nothing else reads that store. Both Y tests now use `JOYSTICK_MIDPOINT(wYmin, ymax)` directly, which gives 274/282 identical. The remaining hunks are still one EBX decision: the model holds `[esp+0x20]` in EBX early, while retail computes the midpoint in EBX. The 0x1cb hunk is the retail `jmp` plus its padding.

### 2026-10-19 (later): 40 more Y-block spellings

The X block matches retail. In the Y block, retail loads `wYmin` into EDI and `wYmax` into EDX once each. It builds the `mid - deadzone` threshold in EBX, copies it to EAX, and only then loads `dwYpos` into EBX. The model loads `dwYpos` into EBX early, at the tail of the X block, and builds the threshold in EAX.

Sweep: ymin/ymax each as a local or a caps read, the 0x20 or 0x10 test first, and named `ylow`/`yhigh` threshold locals (none, either one, or both in either order).
- The best is the shipped form: 4 hunks, 274/282.
- Named thresholds are folded back to the same code.
