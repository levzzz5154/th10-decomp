# Main-menu dispatch recovery note: `0x004236F0`

Date: 2026-09-12

## Status

Semantic recovery was attempted but was not exact. The production source
`matching2/msvc/src/game/main_menu_dispatch.cpp` remains the original naked
retail body, and the production `matching2/msvc/regions.json` was not edited.
No candidate semantic source, task-local layout/context, proposal, or build
output was retained after the failed probe. The target remains an `asm`
region owned by `0x004236F0`.

## Scope and retail extent

The authoritative live manifest entry is:

```text
0x004236F0  3260 bytes (0xCBC)  _asm_FUN_004236f0_004236f0  kind=asm
```

The executable code is disassembled as `0x004236F0..0x0042438A`; the live
manifest extent continues through `0x004243AB`, with the next manifest region
starting at `0x004243AC`. The handler has a security-cookie prologue and a
callee-cleaning `ret 4`. Its state pointer is loaded from the post-prologue
stack argument at `[esp+0x54]`, while the state field is at `record+0x04`.

## Recovered behavior

The archived semantic model in
`matching2/reference/legacy_semantic/src/game/main_menu_dispatch.cpp` and
`include/th10/game/main_menu_dispatch.hpp` agrees with the control-flow
topology recovered from the live disassembly and Ghidra output in
`decompiled/ghidra_augmented/functions/004236F0.{asm,c}`. The handler is a
replay/result submenu update with these important fields:

- `+0x14` is the transition timer; `+0x24` is the selected row;
  `+0x28` preserves the previous row and `+0x2C` is the active row count.
- `+0xF4`, `+0xFC`/`+0x100`/`+0x104`, `+0x1D4`, `+0x1E0`, and `+0x1E8`
  carry menu/keyboard/animation flags, cursor state, name length, and the
  alternate result-path flag. (The source/disassembly spell the cursor
  offsets as `+0xFC`, `+0x100`, and `+0x104`.)
- The 25 replay/resource handles begin at `+0x1EC`; the editable name buffer
  begins at `+0x2B4`.

The state table covers states 6, 7, 8, `0xA`, `0xB`, `0xC`, and `0xD`:

- State 6 waits for the ten-tick entry delay. Input mask `0x1001` queues
  sound 10, changes to state 7, stops the entry animation at frame 2, and
  resets the timer.
- State 7 advances the result/name-entry setup after the same delay. The
  high-score path updates the stage/mode/subslot/difficulty record; the
  alternate path invokes name-entry setup and can transition to state 12.
  It then enters state 8, initializes the three-row choice menu, and
  publishes the selected sprite frame.
- State 8 handles held/repeated up/down navigation through masks `0x10` and
  `0x20`, cursor movement and sound 12, confirmation sound 10, animation
  child lookup/tree marking, replay-slot initialization, and cancel restore.
  Its selection 1 path enters the 25-slot replay/name flow; selection 2
  enters the alternate continuation state.
- State `0xA` waits for its timer, navigates the result cursor, enters name
  editing at `0xB` on confirmation, copies the existing name/alphabet state,
  updates the selected difficulty, and releases the 25 replay handles on
  cancel before returning to state 8.
- State `0xB` is the 13-column keyboard editor. It moves the cursor with the
  retail cursor helper, appends alphabet/space characters, deletes on the
  backspace cell, and formats `th10_XX.rpy` and serializes the replay at the
  save cell. Cancel deletes the final character or returns to the prior
  state when the name is empty.
- State `0xC` is the flagged/alternate keyboard path. It has the same
  movement and editing behavior, but saves the name into the selected
  stage/mode/subslot table, clears and re-registers the animation/task path,
  and returns to state 8.
- State `0xD` waits for the exit threshold, tears down the menu, captures the
  selection, and enters the next state. Its first two selections dispatch the
  retail input-mode helper; the zero selection publishes the launch mode
  through `0x00491FB8`.

## Proven and coupled ABI dependencies

The exact semantic helpers already available to a bounded cluster are:

| Address | Role and observed contract |
| --- | --- |
| `0x00405410` | Set scheduler/timer value; record in `EAX`, value on stack, `ret 4`. |
| `0x0040ACE0` | Test an input mask; object in `ECX`, mask in `EAX`, boolean in `EAX`. |
| `0x00421F60` | Update/read the frame-maximum game-state timer. |
| `0x0044BE20`, `0x0044BE70` | Menu cursor/input-history push and pop. |
| `0x0044BEA0` | Advance cursor; `this` in `EAX`, delta at `[ESP+4]`, result in `EAX`, `ret 4`. |

The handler also depends on unresolved retail custom-ABI edges. The most
important animation edges are `0x0043DC90` (queue sound), `0x00449470` (set
stop frame), `0x004497D0` (find child), `0x004243F0` (mark animation tree),
and `0x004495E0` (clear animation state), with related calls at
`0x00449590`, `0x00449210`, `0x00449250`, `0x004492A0`, `0x004492F0`,
`0x00449350`, `0x004491C0`, and `0x00449630`. Timer/name setup uses
`0x00423510` and `0x00423570`; replay/resource behavior uses `0x004296F0`,
`0x00429B60`, `0x004524A1`, `0x00452AE8`, and `0x00452B71`. The cookie edge
is `0x00458EA5`.

These are caller/callee register contracts, not interchangeable ordinary
C++ calls. In particular, the animation manager/handle/slot values are
distributed across `ECX`, `EAX`, `ESI`, `EDI`, and stack scratch slots at
different call sites. The handler's `ret 4`, cookie check, jump-table layout,
and caller-preserved register choices must remain part of one native-LTCG
cluster.

## Candidate probe and exactness evidence

A disposable readable C++ candidate modeled the complete state switch,
record offsets, globals, keyboard/replay writers, timer/input/cursor helpers,
and the retail animation/replay edges. A temporary native-LTCG driver and
layout placed the candidate at the required address and reserved a context
slot at the expected post-body location. The temporary manifest row was
used only in the lab and was never copied to production.

The linked map measured:

```text
.text$00layout    0x00401000  0x226F0
.text$10dispatch  0x004236F0  0x0A60  _MainMenuDispatchSemanticCandidate@4
.text$20gap       0x00424150  0x0054
.text$30context   0x004241B0  0x0028  _MainMenuDispatchCompilerContext@8
```

The required body extent is `0xCBC`/3260 bytes, but the candidate body was
only `0xA60`/2656 bytes, short by `604` bytes. The required context address
was `0x00424400`; the candidate context landed at `0x004241B0`. Direct
comparison of the emitted body against the retail oracle therefore failed
at the entry prologue. The first 40 bytes were:

```text
retail: 83 ec 4c a1 60 36 47 00 33 c4 55 8b 6c 24 54 89 44 24 4c 8b 45 04 83 c0 fa 83 f8 07 0f 87 67 0c 00 00 53 56 57 ff 24 85
native: 81 ec 8c 00 00 00 a1 60 36 47 00 33 c4 53 55 56 8b f1 8b 4e 14 89 84 24 94 00 00 00 8b 46 04 83 c0 fa 83 f8 07 8d 9e b4
```

Within the emitted `0xA60` bytes, `2510` bytes differed. This is an
ordinary semantic/compiler/ABI mismatch, not proof that the routine is
irreducible or `exact-assembly-required`: the candidate is behaviorally
substantial but lacks the retail frame/register topology and required body
extent.

## Next dependency and cleanup

The next concrete dependency is a custom-register animation bridge, beginning
with the sound/stop-frame/child/tree/clear group (`0x0043DC90`,
`0x00449470`, `0x004497D0`, `0x004243F0`, `0x004495E0`) and the proven
`0x00405410`/`0x0044BEA0` compiler context. That bridge must be combined with
the caller's stack/cookie topology and the menu's jump-table placement before
another handler-level native-LTCG attempt. Keep the handler and all coupled
sources bounded; do not infer an exact-assembly-only classification from an
ordinary failed C++ candidate.

The temporary lab, candidate, probe outputs, marker, and proposal were
removed after the failure. No production source, `regions.json`, shared
tooling, unrelated source, or other worker's files were changed by this
attempt.
