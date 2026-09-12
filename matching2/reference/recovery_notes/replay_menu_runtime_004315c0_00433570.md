# Replay-menu runtime recovery note: 0x004315C0 and 0x00433570

Date: 2026-09-12

Status: semantic recovery was not integrated this pass. The production source
was restored after the focused semantic probe failed, and the tracked
production probe is exact for both owned regions.

## Scope and production state

Owned regions:

- `matching2/msvc/src/game/replay_menu_runtime.cpp`,
  `0x004315C0`, required extent `1492` bytes (`0x5d4`)
- `matching2/msvc/src/game/replay_menu_runtime.cpp`,
  `0x00433570`, required extent `1460` bytes (`0x5b4`)
- total owned body extent: `2952` bytes (`0xb88`)
- task-specific LTCG layout/context and only these two manifest entries

Both handlers remain the original naked retail bodies, with symbols
`_asm_FUN_004315c0_004315c0` and `_asm_FUN_00433570_00433570`, kind `asm`, and
the existing sizes. No manifest entry, shared Python tooling, or another
worker's source was edited. No task-specific LTCG layout remains registered:
the semantic candidate did not pass the focused body-extent gate.

Focused validation after restoration:

```text
python3 matching2/tools/matching/probe.py \
  --source src/game/replay_menu_runtime.cpp \
  --output matching2/build/probe_replay_restored --show 32

EXACT
0x004315c0    1492 bytes  _asm_FUN_004315c0_004315c0  EXACT
0x00433570    1460 bytes  _asm_FUN_00433570_00433570  EXACT
```

The temporary focused-probe outputs and candidate proposal were removed after
the evidence was captured.

## Evidence used

The semantic model and ABI inventory were reconstructed from the archived
source and types in
`matching2/reference/legacy_semantic/src/game/replay_menu_runtime.cpp:10-39`
and
`matching2/reference/legacy_semantic/include/th10/game/replay_menu_runtime.hpp:7-15`.
The concrete control flow, switch tables, call sites, and field offsets were
cross-checked against:

- `decompiled/ghidra_augmented/functions/004315C0.c:1-245`
- `decompiled/ghidra_augmented/functions/004315C0.asm:1-519`
- `decompiled/ghidra_augmented/functions/00433570.c:1-273`
- `decompiled/ghidra_augmented/functions/00433570.asm:1-568`
- `ida/th10.exe.c`, `sub_4315C0` and `sub_433570` entries and their callers
- `matching2/msvc/src/game/title_menu_runtime.cpp` call sites
- related active replay/menu runtime and draw sources

The archived implementation is useful as behavioral guidance, but its
edge-based abstraction does not encode the retail register calls, resource
enumeration, animation slots, or the full state layout.

## Recovered 0x004315C0 model

This is the replay-load menu state machine. Its state pointer is recovered
from `[esp+0x190]` after the prologue; the retail body ends with `ret 4` and
contains a five-entry jump table at the end of the owned region. Important
state fields include phase `+0x20`, cursor `+0x24`, previous cursor `+0x28`,
row count `+0x2c`, timer pair `+0x2b0..+0x2c0`, selected slot `+0x59dc`,
selected stage `+0x59e0`, and the 50 replay pointers at `+0x59e4`.

- Phase 0 initializes the 25 built-in `th10_01.rpy` through `th10_25.rpy`
  entries, creates the `replay` directory/user-file enumeration path, installs
  the menu animation resources, arms timer target 1, clears the 50-slot array,
  and falls through to phase 1.
- Phase 1 waits for the opening timer and initializes the timer pair before
  entering browsing phase 2.
- Phase 2 advances the replay-slot cursor, queues movement sound 12, handles
  cancel (`0x0a`) by targeting phase 5, and on confirm (`0x1001`) records the
  chosen slot, calls the input-history push helper, scans seven stage records
  in the selected replay, and populates the available-stage array.
- Phase 3 handles the stage-selection transition and, after the timer reaches
  the launch threshold, publishes the chosen replay/player/character/shot/
  difficulty fields before entering the replay launch path.
- Phase 4 waits for the stage-menu entry delay, moves through the available
  stages, uses input-mask repeat handling, and either pops the input history on
  cancel or records the selected stage and targets phase 3 on confirm.
- Phase 5 waits for the exit timer, releases and clears all 50 replay records,
  clears animation slots `0x65`, `0x5a`, `0x5b`, and `0x5e`, disables the timer,
  restores the prior cursor/phase from the input-history stack, and returns 1.

## Recovered 0x00433570 model

This is the replay-save slot and eight-character name-entry state machine. IDA
identifies it as a `__userpurge` body with the title host in `ECX` and one
state argument on the stack; the active source reads that state from
`[esp+0x4c]` after its prologue, ends with `ret 4`, and has a five-entry jump
table. Key fields are phase `+0x20`, slot cursor `+0x24`, previous cursor
`+0x28`, timer pair `+0x2b0..+0x2c0`, name-grid cursor `+0x58f4`, previous
name-grid cursor `+0x58f8`, alphabet length `+0x58fc`, name length
`+0x58e8`, selected slot `+0x59dc`, and the 25 replay pointers at
`+0x59e4`.

- Phase 0 initializes the 25 save slots, resets the slot cursor, publishes the
  title host/global menu state, installs animation slot `0x69`, and arms timer
  target 1. Phase 1 waits for the opening timer and targets phase 2.
- Phase 2 browses save slots with the menu cursor and movement sound 12. Cancel
  targets cleanup phase 4 with sound 11. Confirm stores the slot, resets the
  name-grid cursor and name length, snapshots time, copies the existing
  eight-character player name, and targets phase 3 with sound 10.
- Phase 3 moves the name-grid cursor by vertical 13-row and horizontal one-row
  steps, with the observed wrap behavior. Confirm appends an alphabet character
  or space, backs up over the delete cell, or saves at the final cell by
  destroying/reloading the selected replay resource and calling the replay
  serializer. Cancel deletes the last character, or returns to phase 2 when
  the name is empty.
- Phase 4 waits for the exit timer, clears animation slot `0x69` and the other
  menu resources, pops the input history, releases the title host and all 25
  replay slots, clears the 50-slot storage, and returns 1.

The alphabet at `0x004746D8` is the archived
`ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789 .,-!?`
sequence. The concrete body also preserves title-host teardown and resource
calls that the archived semantic edge model leaves abstract.

## ABI and coupled-helper constraints

These contracts are part of the exact body shape and are not represented by
ordinary C++ prototypes:

- Both handlers use a callee-cleaning `ret 4` despite the surrounding callers'
  register setup; the state argument is read from a post-prologue stack slot.
- `0x0044BEA0` (`MenuCursor::Advance`) receives `this` in `EAX`, the delta on
  the stack, returns the cursor in `EAX`, and cleans its delta argument.
- `0x0044BE20`/`0x0044BE70` push/pop the input-selection stack using the menu
  cursor in `EAX`.
- `0x0042C620` (`GameStateTimer::SetTimerTarget`) receives the timer object in
  `EAX` and the target in `ECX`; the handler emits those register moves
  explicitly.
- `0x0040ACE0` uses its custom input-mask register convention, while
  `0x0043DC90` queues sounds through the global animation manager.
- `0x0042C670`/`0x0042C6D0` install and clear animation resources with manager,
  slot, and resource arguments in the retail-specific registers/stack slots.
- `0x004296F0`, `0x004297B0`, `0x00429B60`, `0x00452AE8`, and the time helper
  retain their observed resource-loader, deleting-destructor, serializer,
  formatting, and timestamp call shapes.
- The save-name teardown uses the title host in `ECX` for the final coupled
  cleanup calls. A handler-level semantic promotion therefore depends on the
  title host, timer, menu cursor, input-mask, animation, resource, and replay
  serializer cluster as one bounded dependency group.

## Semantic candidate probe and mismatch

A temporary readable C++ save-name candidate was added only for a focused
probe. It modeled the phase transitions, slot loading, name-grid movement,
alphabet/space/delete behavior, save/reload path, and cleanup calls through
typed function-pointer edges. It was not added to the manifest or any LTCG
layout. The focused probe rejected it before byte comparison:

```text
python3 matching2/tools/matching/probe.py \
  --source src/game/replay_menu_runtime.cpp \
  --output matching2/build/probe_replay_candidate \
  --proposal matching2/reference/recovery_notes/replay_menu_probe_proposal.json \
  --show 32

NOT EXACT
src/game/replay_menu_runtime.cpp: FAILED TO COMPILE
region _ReplaySaveName_Update_Candidate@4: section .text extent 1268 differs from requested size 1460
```

The probe's generic `FAILED TO COMPILE` line is the unit-level result for the
extent gate; the candidate object was emitted and measured as a 1268-byte
section. It was 192 bytes short of the retail body before byte comparison, so
there was no basis for changing the required region size or registering a
semantic symbol. The candidate and proposal were removed, and the production
assembly was rechecked exact afterward.

## Next experiment

Keep both naked bodies as the production baseline. The next semantic attempt
should use an isolated multi-source native-LTCG topology only after a compiler
context can express the custom register ABIs above. Begin with a save-name
handler bridge for `MenuCursor::Advance`, `SetTimerTarget`, animation
installation/clearing, and title-host teardown; then add the load-menu bridge
for input-mask repeat, input-history push/pop, stage-list population, and
launch publication. Require each handler section to measure exactly `0x5d4`
and `0x5b4`, respectively, in a focused probe before changing `regions.json`.
Keep any candidate layout/proposal outside the tracked manifest and remove it
on failure. Coordinate with the existing owners of the coupled helpers rather
than editing their sources or shared Python tooling.

## Follow-up save-name bridge probe

The requested save-name bridge was attempted first. Its probe-only source
candidate kept the phase 0..4 state machine and routed the required edges for
cursor advance, timer target, animation-slot install/clear, and title-host
teardown through the existing fixed-address symbols. A task-local native-LTCG
driver supplied the explicit custom timer-register smoke edge. No load-handler
candidate was attempted after this bridge failed its extent gate.

The direct source probe compiled the candidate but measured only `612` bytes:

```text
python3 matching2/tools/matching/probe.py \
  --source src/game/replay_menu_runtime.cpp \
  --output matching2/build/probe_replay_save_bridge_direct \
  --proposal matching2/reference/recovery_notes/replay_save_name_bridge_00433570_proposal.json \
  --show 32

NOT EXACT
src/game/replay_menu_runtime.cpp: FAILED TO COMPILE
region _ReplaySaveName_Update_Bridge_Candidate@4: section .text$01save extent 612 differs from requested size 1460
```

The first multi-source layout also showed that retaining the two original
public naked handlers in the context driver pulls in 51 unresolved retail
symbols. The bounded driver was then narrowed to the bridge candidate and
its declared fixed-address edges; native `/LTCG` linked successfully. Its map
recorded:

```text
.text$01save    0x00433570  length 0x248  (584 bytes)
.text$03context 0x004338A0  length 0x05B  (91 bytes)
```

The required body is `0x5b4` bytes and the task-local layout expected the
context after the full `0x5b4` body, so validation stopped with
`native cluster image base or compiler-context entry address differs` before
body-byte comparison. The native candidate was shorter than the direct
candidate because native LTCG folded the simple bridge paths. The temporary
layout, context, proposal, native outputs, and candidate source were removed;
the production source and original `asm` manifest entries were restored.

The compiler-specific next dependency is an ABI-aware bridge that can make
the compiler retain the real call-site shapes, not another ordinary C++
spelling: `MenuCursor::Advance` needs `this` in `EAX` with a stack delta,
`SetTimerTarget` needs `this` in `EAX` and target in `ECX`, animation install
and clear need their `EDI`/`ESI`/stack contracts, and title-host teardown must
keep the host in `ESI` across the release/delete pair. The next productive
experiment should isolate those helper shims in a task-local native-LTCG
context or use exact helper-owner contributions without retaining unrelated
replay naked bodies. Do not attempt the load handler until that save bridge
has an exact `0x5b4` section and exact focused bytes.
