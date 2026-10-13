# Equivalent recovery: `0x004236F0` — replay/result submenu dispatch

Date: 2026-10-13

## Status

Accepted equivalent recovery (not exact). The verdict of
`matching2/tools/matching/equivalence.py` over
`layout/equivalent/replay_submenu_004236f0.json`:

```text
replay_submenu_004236f0: 3,224 of 3,260 bytes used, 751 of 923 instructions
identical, 1 base/index swaps, 0 frame-offset, 171 instructions in 80 recorded
differences
```

(exit code 0; gate passed: external references equal, no call/branch
substitutions in tie-break hunks, structural weight 108/923 ≤ 12.5%, total
weight ≤ 33%.)

The production region stays `asm` (`_asm_FUN_004236f0_004236f0`,
3260 bytes); the C++ model ships as an equivalent recovery and is registered
by adding to `equivalent_recoveries` in `matching2/msvc/regions.json`:

```json
{"region": "asm_FUN_004236f0_004236f0",
 "layout": "layout/equivalent/replay_submenu_004236f0.json"}
```

No other `regions.json` change is required. `main_menu_dispatch.cpp` keeps the
naked body (the exact link still builds it); the equivalent model lives in the
new files listed below and is compiled only by the recovery build.

## Model

`src/game/replay_submenu_update_004236f0.cpp` is the readable state machine
(states 6–13 of the result-screen record: confirm gate, ranking-gate
high-score publication or `PrepareNameEntry`, the three-row save choice, the
25-row replay browser with manager creation/release, the 13-column keyboard
editor with letter/space/backspace/save cells, the alternate (`no_entry`)
keyboard path, and the final-choice dispatch). The record view and every
global live in `include/th10/game/replay_submenu_004236f0/state.hpp`
(`SubmenuState_004236f0`: `state` +0x4, timer +0x10, rows cursor +0x24, grid
cursor +0xFC, handle +0x1D4, `name_length` +0x1E0, `extra_cleared` +0x1E4,
`no_entry` +0x1E8, 25 replay managers +0x1EC, name +0x2B4).

The private-ABI dependency bodies are scoped copies compiled into the model
translation unit (`layout/ltcg/replay_submenu_004236f0/*.cpp`: the animation
find/setstop/child/mark6/stop3/stop1/node-flag family, the sound queue, the
scheduler value, the menu cursor trio, the input-mode publisher, the
frame-maximum update, the timed-state reset and the platform-resource
release), plus `?InputMaskActive@KeyRepeatState@@QAEHG@Z` linked from its
maintained source. `0x00429B60` is called through a `__fastcall` binding
(ECX = replay manager, EDX = target path, name on the stack) bound at its
retail address; the `ReplayManager` destructor (0x004294A0, receiver on the
stack, RET 4) is bound through a stdcall alias; `PrepareNameEntry`,
`ReplayManager_Create`, `UpdateBoundedCounter`, the sprintf/time32/free shims
and the security cookie bind at their retail addresses. The pooled literals
("th10_%.2d.rpy" and the eight-space name) are `data_aliases` at 0x0046E0C8 /
0x0046E354.

## What the recorded differences are

80 hunks, 171 instructions, all tie-breaks or reviewed block placements:

- `block-order` (the only structural runs): state B/C's shared length-bump and
  clamp block sits after the two write cells in retail and partially inline in
  the model; the state C cancel region (`selection < 0` branch) and the
  state-C timer gate are placed at the other end of the same tail; the
  state-B cancel test is reached with an inverted branch over the same code.
- `branch-target` (8): the jump table (0x42438C) plus seven tail jumps whose
  targets were proven equivalent by following unconditional jumps.
- `code-shape` (4): `lea` vs `add` for the child-lookup script id, the state D
  dispatch (`sub eax,0` + dec chain vs `test`/`cmp` chain), and the state C
  row-select compare (immediate vs register-held 2).
- `evaluation-order` (15): the strlen/grid/selection loads, the summary-slot
  loads around the time32 call, the save-cell sprintf arguments, and the
  stage-table write addressing chain.
- `register-choice` (37) and `alignment-padding` (4): scratch-register
  renames (EBX=0xA/1 materializations, ESI/EBX cursor pointers) and nop
  fillers.

## Nonobvious insights recovered on the way

- The two legacy "flag" fields are the `MenuCursor` wrap flags: +0xF4 is the
  rows cursor's wrap and +0x1CC the grid cursor's wrap; +0x2C/+0x104 are the
  two `item_count`s, so the whole record is `state; timer; MenuCursor rows;
  MenuCursor list; handle; ...; managers[25]; name[8]`.
- State A navigates the rows cursor; confirming hands the grid cursor to the
  keyboard editor (states B/C).
- The append/space paths of both keyboard editors queue sound 10 and FALL
  THROUGH into the cancel test in the same frame (no return); only the
  backspace and save cells return early, and the state C armed
  (`no_entry != 0`) path queues no sound at all.
- State C's three row re-selections use `Select(0)` (not `Select(2)` as the
  legacy host model claimed), and state D's selection 1 and 2 both dispatch
  `SetInputMode(&data_00491C28, 4)` through the same dec/dec chain.
- The `0x00429B60` serialize call takes the manager in ECX, the target path in
  EDX and the name on the stack — expressible from ordinary C++ as a
  three-argument `__fastcall` declaration bound at the retail address.

## Files

- `src/game/replay_submenu_update_004236f0.cpp` (model body; also includes the
  scoped dependency bodies at the bottom)
- `include/th10/game/replay_submenu_004236f0/state.hpp`
- `layout/ltcg/replay_submenu_004236f0/{animation.hpp,find.cpp,setstop.cpp,
  child.cpp,mark6.cpp,stop3.cpp,stop1.cpp,nodeflag.cpp,inputmode.cpp,
  timer.cpp,queue.cpp,cursor.cpp,frame.cpp,timed.cpp,destroy.cpp}`
- `layout/ltcg/replay_submenu_004236f0_context.cpp` +
  `layout/ltcg/replay_submenu_004236f0_context.json` (the equivalence build's
  context cluster: driver + the maintained `input_mask_active` source)
- `equivalent/game/replay_submenu_004236f0_stub.cpp`
- `layout/equivalent/replay_submenu_004236f0.json` (the layout to register)

The scratch lab lives under `scratch/submenu_004236f0/` (reflink copy; the
schema-2 cluster manifest tried there was removed after the equivalent path
succeeded).
