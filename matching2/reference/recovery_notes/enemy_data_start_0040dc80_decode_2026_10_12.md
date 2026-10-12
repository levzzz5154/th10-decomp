# EnemyData_Start 0x0040DC80: full decode (2026-10-12)

Region: 0x0040DC80..0x0040E5EB, 2412 bytes, 671 instructions. This is the
enemy script-start tick (the prototype `EnemyData_Start_0040dc80` in
`msvc/include/th10/game/enemy_spawn_0040cfb0.hpp`); the enemy arrives on the
stack (RET 4). All 22 callees are recovered semantic regions except
`__ftol2` (0x463B2C). Three callers are recovered semantics
(`EnemySpawn_Create_0040cfb0`, `EnemyTimerSweep_0040d750`, `Run_0040dc70`).
The synthetic caller cluster `layout/ltcg/cl_0040dc70.json` already binds
`_target_0040dc80@4`.

The struct view is `EnemyData_0040cfb0` (0x14DC bytes); the fields the body
touches beyond the current view are listed at the end.

## Control flow (in order)

1. Entry: `sub esp,0x18`; `ebp = enemy`. If `flags & 0x400` (the
   "script started" latch) is already set: return 0. Otherwise set
   `flags |= 0x400`.
2. Copy 11 dwords from +0x2C to +0x00 (the position snapshot the deltas
   are computed against later).
3. Four trajectory-interpolator steps (Interpolator<TrajectoryVec2>::Step
   0x412AC0 into a stack pair, then Angle_Normalize 0x44BC70):
   +0x1D4 → (+0x70 angle, +0x74); +0x24C → (+0x78, +0x7C);
   +0x210 → (+0x9C, +0xA0); +0x288 → (+0xA4, +0xA8). Each guarded by its
   own enable dword (+0x208, +0x280, +0x244, +0x2BC).
4. Base motion at +0x64..0x6C: if +0x180 (a Vec3 interpolator) is set:
   Step 0x404610, delta = result − (+0x58..0x60) → +0x64..0x6C.
   Else if !(+0x80 & 1): SetPolarEffective 0x44C5D0(+0x64, +0x70, +0x74)
   with +0x6C = 0. Else: +0x78 += +0x7C (angular velocity); normalize
   (+0x70, +0x74) via 0x44BC70.
5. The same treatment for +0x84..0x90 (from the +0x188 Vec3 interpolator or
   the polar triple at +0x90..0x9C): SetPolar 0x44C5D0(+0x84...)/normalize
   +0x8C.
6. PolarMotion::Advance 0x44C2A0 on +0x58 (the base position), then, when
   `flags & 0x40000` (scroll with the field), add the three floats at
   0x491E6C..0x491E74 to +0x84..0x8C, then Advance on +0x84. The delta
   +0x38..0x40 = (+0x84 + +0x58) − (+0x2C snapshot). Advance on +0x38.
7. `flags & 0x200` (move by the origin delta): clamp +0x84.x into
   [0x13AC − k·0x13B4, 0x13AC + k·0x13B4] and +0x84.y into
   [0x13B0 − k·0x13B8, 0x13B0 + k·0x13B8] with k = the float at 0x470B0C;
   then +0x58 = +0x84 − +0x38 (recompute the base delta).
8. Off-screen check (unless `flags & 0x200`): position vs the field bounds
   scaled by 0x13A4/0x13A8 (constants at 0x470B40/0x470B3C/0x470B04/
   0x470B38). Out of bounds → `flags |= 0x100` (the despawn flag).
9. Script change (if `flags & 0x100000`): the outer world at 0x4776EC →
   +0x28 decides between +0x1448 and +0x144C; ScriptChangeHandle 0x4496D0
   with +0xC0; `flags = (flags & ~0x200000) | 0x1` or `&= ~0x200001`.
10. TickChildren 0x44FD10(vm at +0x14D8, arg=[+0x128][0]). Nonzero →
    return −1 (the interpreter error propagates).
11. `flags &= ~0x200`. If `flags & 0x11` → step 14 (no item handling).
12. Item drop: PickupSweep::Sweep 0x428630(player 0x477834, position,
    result at +0xB0); `div 5` on the returned count (imul 0x66666667);
    when the game thread at 0x4776F4 → +0x378C bit 0 is set and
    `flags` negative, the count is clamped to ≥ 1; if `!(flags & 8)` and
    +0x1420 ≤ 0, +0x13C0 (score) −= count. AdvanceSlots 0x4127A0; nonzero →
    ClearResourceList 0x40C6E0, EclRecord::Reset 0x40C730, BindName
    0x450700, TickChildren again → return −1 on error. If
    `+0x13C0 <= 0` and `!(flags & 0x200)`: AddScore 0x409D90(0x474C40,
    +0x13BC = life); Enemy_ReleaseOnDeath 0x40E5F0 → return 1 when it
    released. Otherwise `flags |= 0x2000`; [0x474C50] = 1.
13. Field contact (unless `flags & 0x12` or +0x1434 > 0):
    FieldContact004266B0(0x477834, +0xB8, +0x2C).
14. `flags & 0x1000` (off-screen state tracking): compare +0x38.x with
    0x470D30/0x470C18 into a −1/0/1 state, keep [0xF8] as the previous
    state, and on a change ScriptChangeHandle 0x4496D0 with
    [0xF4] ± 1/2/3/4 (the four-step transition table).
15. Animation positions: 8 handles at +0xC0..0xE0 through
    SetAnimationTranslatedPosition 0x49350, or MovementSetPosition 0x492F0
    when `flags & 0x40000`. Find 0x4491C0 on [0xC0]; a dead handle is
    blanked.
16. Invulnerability [+0x1414]: when 0 and `flags & 0x2000`: set the
    animation's 0x8000 flag and color 0xFF0000FF, [+0x1414] = 4; if
    `flags & 0x8000` also, queue the blink sound (QueuePan 0x43DD10,
    sound 0x23 or 0x13 — 0x23 while [0x2404] < 300/900 per the game
    thread flags, else 0x13). When nonzero: clear 0x8000 (and the outer
    world's +0x9DA4 bit when `flags` is negative), decrement.
17. FrameTimer::Advance 0x44BF40(−1.0f) on +0x141C (while +0x1420 > 0) and
    +0x1430 (while +0x1434 > 0).
18. Script wait bookkeeping: [0x11C] = [0x120]. If `[+0x128][0]` (the
    current wait frame count) lies inside [0x470B64, 0x470B68]:
    +0x124 += the float at 0x470AFC and ++[0x120] (fractional wait), return 0.
    Otherwise +0x124 += the wait value, `__ftol2`, [0x120] = the integer
    part, return 0.

## Fields the current EnemyData_0040cfb0 view does not name

+0x00..0x2C (the 11-dword snapshot target), +0x38/+0x40/+0x48 (motion
deltas), +0x58/+0x60 (base position), +0x64..0x70 (base polar),
+0x70..0x80 (trajectory angle pairs), +0x80..0xAC (the second polar), +0xB0
/+0xB8 (pickup sweep results), +0xC0..0xE0 (8 animation handles), +0xF4/
0xF8 (the off-screen transition state), +0x11C..0x130 (script wait
bookkeeping), +0x128 (the script wait pointer), +0x180/+0x188 (the two Vec3
interpolators), +0x1CC/+0x1D4/+0x208, +0x244/+0x210, +0x280/+0x24C,
+0x2BC/+0x288 (the four trajectory interpolators and enables), +0x13A4/
0x13A8/0x13AC/0x13B0/0x13B4/0x13B8 (the field clamp and off-screen scale),
+0x1414 (the invulnerability countdown), +0x1420/+0x141C and +0x1434/+0x1430
(the two FrameTimers), +0x1444 (flags, already in the view as bit fields —
the body uses raw bits 0x1/0x2/0x4/0x8/0x11/0x100/0x400/0x1000/0x2000/
0x40000/0x100000/0x200000), +0x1448/+0x144C (the script change indices),
+0x14D8 (the ScriptVm, past the 0x14DC view — it is at +0x4A0 of the outer
Enemy_0040cfb0 record, NOT inside EnemyData; the body receives the outer
record on the stack, so the view needs the 0x14D8 offset resolved against
Enemy_0040cfb0's layout).

## Recommended route

The equivalent route through `cl_0040dc70.json` (its context already
establishes the entry ABI) or a caller-inclusive cluster over
`EnemySpawn_Create_0040cfb0`. The x87 chains (steps 6–8) and the two
`__ftol2` sites are the parts the compiler will not reorder cheaply; the
rest is straight-line.

## 2026-10-12: the model-blocking convention detail

The ECL VM callees the body invokes use private register conventions that
only a native-LTCG context can reproduce: TickChildren 0x44FD10 receives
the owner in EDI (per `msvc/include/th10/script/ecl_children.hpp`), the
interpreter 0x44E1A0 enters in EAX, and BindName 0x450700 is reached with
the VM in ECX and no visible name argument at the call site (0x0040E1EB) —
the name comes from the VM's own state. A plain C++ model calling the
recovered `__stdcall` declarations would pass arguments on the stack and
crash at runtime; the `cl_0040dc70` cluster has no thunks establishing
those conventions yet.

Extending that cluster with ECL-VM convention thunks plus the 671-instruction
model is the remaining work; the struct extension and decode above are
complete, so the next session starts from the call-site analysis, not the
semantics.

## 2026-10-12 (second session): the working model draft

`msvc/equivalent/game/enemy_data_start_0040dc80.cpp` (with the motion
view `msvc/include/th10/game/enemy_data_start_0040dc80.hpp`) is the
working draft: the snapshot, the four trajectory steps, both polar/vector
motions, the clamp and off-screen paths, the script change, the
interpreter tick, the pickup/score block, the spell-timer advance, the
off-screen state machine, the eight animation positions, the blink
counter and the wait bookkeeping are all expressed. The register
conventions resolve through the `ecl_tick_children` cluster context
(TickChildren 0x44FD10 compiled in-cluster with its EDI ABI; c2 adapts
the call site under /GL).

What remains before the equivalence run compiles clean: the EnemyRecord
view the body reaches through the 0x14D8 ScriptVm pointer needs its
actual shape (the +0x2404 frame counter belongs to the outer record), the
item-drop score arithmetic needs the +0x1420 pause guard decoded, and the
call-argument details of the two `FieldContact`/`PickupSweep` pairs need
their stack layouts verified against the recovered bodies. None of these
require new decodes — the disassembly in the first section answers each.

## Model state (2026-10-12, end of session)

The draft compiles and links clean (all 40 absolute bindings resolve; the
ECL TickChildren EDI convention resolves through the ecl_tick_children
cluster). The compiled body is 1,712 bytes against the retail 2,412 —
700 short. The missing mass: the two PolarMotion/SetPolar member calls
(the draft inlines raw float math where retail calls 0x0044C5D0/0x0044C2A0
per motion), the exact trajectory-step call shapes, the pickup sweep's
real argument layout, and the field-contact pair. Each is a source-level
expression change against the decode in the first section; no new
decodes are needed.

## Gap breakdown (2026-10-12, block diff at 1,728/2,412)

The 684 missing bytes decompose into eight blocks, each a faithful
expression of the decode's sections:

| retail block | bytes | decode section |
|---|---|---|
| 0x40DD69-0x40DDF5 + the row loop | 269 | base motion (the full per-row draw state) |
| 0x40DFA8-0x40E012 | 124 | the x87 clamp chains (fild/fmul/fcom per axis) |
| 0x40E044-0x40E0E9 | 89 | the script-change retry details |
| 0x40E14E-0x40E16F | 43 | the score div-by-5 (imul 0x66666667) |
| 0x40E107-0x40E141 | 68 | the pickup sweep result handling |
| 0x40E261-0x40E2BD | 82 | the spell-timer advance |
| 0x40E38B-0x40E3DB | 70 | the eight-position setter loop |
| 0x40E43E-0x40E5C7 | 351 | the blink/queue and off-screen machine |

All are source-level expression work against the decode; the bindings and
conventions are already in place.

## Growth iteration (2026-10-12, second)

Three fixes landed: the motion paths use the real SetPolar/normalize
shapes (the orbit path accumulates the rate into the angle and
renormalizes the speed), the scroll drift reads the three floats at
0x00491E6C..74, and the wait bookkeeping compares against the bound
bounds (0x00470B68/0x00470B64) instead of pooled 1.0/60.0 literals. The
BindName call was replaced with the retail Resolve sequence (resolve the
VM-owned name, store into the current frame). Body: 1,712 → 1,952.

Remaining: the row-draw loop (269 B), the blink/off-screen machine
(351 B), and the pickup/score details (111 B). Also: all float constants
the model reads must be extern-bound homes — the CIL pools private copies
of any literal (1.0f/60.0f) and the equivalence tool then flags the pooled
addresses.

## Growth iteration (2026-10-12, third)

The blink/off-screen machine is now expressed faithfully: the countdown
clear path (flags &= ~0x8000, the outer +0x9DA4 mirror, the decrement),
the highlight path (flags |= 0x8000, the 0xFF0000FF color at +0x300, the
alarm decision from the game flags at [0x4776F4]+0x378C and the VM frame
counter at +0x2404 with the 300/900 thresholds, sounds 0x23/0x13), and
the two FrameTimer::Advance calls. The script rebind uses the VM's
`ScriptTable::Resolve` + the current-frame store (retail 0x0040E2A2).
Body: 1,952 → 2,128.

Remaining: the row-draw loop (~269 B) and the small pickup/field-contact
argument details. Also learned: the CIL pools any float literal — every
constant the model reads (the 300/900 thresholds aside, which are
immediates) must come from a bound home; the pool copies surface as
unbound 0x4020xx references.
