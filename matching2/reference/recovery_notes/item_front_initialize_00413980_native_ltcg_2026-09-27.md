# 0x00413980 — exact ItemFront initializer

> Integration status (2026-09-27): the exact routine(s) described here are now integrated in the maintained project. The combined 487,936-byte executable matches retail byte for byte. See [the fourth checkpoint](native_recoveries_2026-09-27_fourth.md) for current proof and remaining work. Scratch-only and promotion instructions below describe the original recovery handoff. Unmatched candidates remain in scratch.

2026-09-27. All 147 bytes emit exactly as ordinary C++ under native MSVC
13.10.6030 `/GL` + LINK `/LTCG`. The initializer receives its state in EBX,
returns an integer in EAX, takes no stack argument and uses plain RET.

## Fresh evidence

Ghidra MCP decompilation, disassembly, 147-byte memory read and the factory
caller's disassembly are retained in this experiment. The factory calls at
0x00414878 with the new manager already in EBX. Ghidra memory equals the oracle
region, SHA-256
`ce9f0c14517bc2bab7e315db5949d66193c2363329d8b3c85b86140f88a68a1d`.

The source loads `front.anm` into cache slot 6 and writes the result to the
state's +0x9EC8 field even on failure. It logs a missing resource and returns
-1, then calls the already recovered public stdcall ScoreTask setup. A nonzero
setup result returns -1 before any task creation. Successful setup creates the
update/render callbacks, clears task flag bit 1 through its typed bitfield,
sets the context, registers priorities 0x18/0x2B, and publishes the task
pointers at +8/+0xC. The shared header checks those three state offsets and
represents only fields reached here; it is not an allocation-size model.

## Compiler integration

The target joins a copied version of the established
`bullet_manager_load_scripts_0040ae70` native cluster. Its existing scheduler
bodies and genuine TextLog Append body preserve the required task-in-ESI,
priority-in-EDI and logger-in-ECX agreements. The target is unrooted, with one
unselected array-context call added so LTCG derives the observed EBX receiver.
The declared stdcall pointer parameter describes the C++ interface; the native
link report and complete byte comparison prove the actual private entry.

ScoreTask setup is bound through its already verified public stack ABI and
requires no archive cluster merge. Callback creation also retains its public
stdcall interface, with a typed `TaskRoutine` parameter. The fixed callback
addresses are passed as function pointers without casts. The new body and
header contain no inline assembly, naked functions, emitted bytes, raw memory
field accesses or instruction transformations. No compiler barrier was needed.

The first native body was already exactly 147 bytes. Updating the unselected
compiler-context extent to 455 bytes satisfied the complete-contribution gate.
Typing the callback argument preserved the exact bytes.

## Verification and promotion

Fresh `final_probe.json` reports all 26 selected regions exact: this initializer
and all 25 existing cluster functions. It reports zero relocations, masks,
changed instruction bytes, changed address operands, or reference bytes as
build inputs. Compiler context contributes no recovered code.

```sh
python3 matching2/tools/matching/probe.py \
  --project matching2/build/experiments/item_front_init_00413980_2026_09_27/msvc \
  --source src/game/task_registration.cpp \
  --output matching2/build/experiments/item_front_init_00413980_2026_09_27/final_probe --json
```

Copy `msvc/src/game/task_registration.cpp` and
`msvc/include/th10/game/item_front_initialize_00413980.hpp`. Use
`promotion_delta.json` to extend the current maintained bullet cluster and its
existing context, retaining their names and other current edits. The unique
experiment layout is a full isolated copy, not a parallel registration of its
25 existing functions. Register the extended cluster and select
`_ItemFront_Initialize_00413980@4` at 0x00413980; retain the original assembly
name as the fixed-address alias used by the unrecovered factory caller.

Final source SHA-256:
`69762442731dbc5bd5963b8e424023e22e3f9d6de43d1f6c107b0126fa35c498`.
No maintained files were edited by this experiment.
