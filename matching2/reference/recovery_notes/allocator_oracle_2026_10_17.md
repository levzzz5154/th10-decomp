# Allocator diagnostic oracle: animation changer and front dispatcher

## Contract and result

No source recovery or promotion landed. Production source/layout/manifest files
were restored unchanged. Compiler patches described below are diagnostic only;
their output must never be selected by the normal build or credited as recovery.

Artifacts (ignored, including binaries, commands and traces):
`matching2/build/experiments/allocator_oracle_2026_10_17/`.
The scripts there originated in the agent scratch directory; saved command paths
refer to that original directory. Re-run `prepare.py <recovery-name>` from its
preserved location to regenerate objects and commands with current paths.

## AnimationObject::ChangeScript 0x0043E8B0

Fresh maintained baseline: 287 bytes, 64/66 identical instructions, 14 differing
bytes. The old XOR update was rebuilt in isolation, with the production source
restored immediately after object compilation.

A fresh ChoosePhysReg trace reproduced flags candidate 4 at priority 44 and
script candidate 3 at priority 42. At c2.dll 13.10.6030 address `0x107AAC16`,
`[esp+0x20]` identifies the candidate and `[esp+0x10]` holds the selected register.
This breakpoint is AFTER the cost-based choice, not before it. For candidate
4/priority 44 only, replacing selected register 7 (ESI) with 8 (EDI), both in the
ordinary and relocated native links, produced **287/287 identical bytes** and
66/66 identical instructions, zero differences. Reports:
`animation_change_script_0043e8b0/animation-report.json` and corresponding
`animation-{model,moved}.txt` (exactly one patch per link).

This establishes a useful counterfactual: the XOR model can become exact by
changing that allocation choice alone. It does NOT establish that adding three
priority points has the same effect, nor identify a valid source change.

Additional legitimate-source controls failed:
- Wide test/update constants, short test, signed/unsigned flag/test/XOR
  combinations, pair aggregate initialization (early or at the final store), and
  a reference to the script slot: 22 differing bytes, 51/66 instructions.
- Chained pair assignment: 24 differing bytes, 51/66 instructions.
- Byte-alias test of the local flags: 261 differing bytes, 41/66 instructions.
- A full 64-bit flags local did not yield a comparable body (unbound compiler
  helper symbol); this is not an improvement.

Do not repeat these as new levers. The missing source lever must alter allocation
without introducing a new instruction, shifting a store, or replacing the XOR.

## ResultDispatcher2 0x00415E90

Fresh baseline: 4,480 bytes, 1,144/1,147 identical instructions, 25 differing
bytes, precisely the three existing stage-7 clear-count hunks.

The function-scoped global trace is
`front_script_tick/named/events.jsonl`. Global candidates named
`_g_globals_difficulty` were 86/priority 88 -> ECX and 87/priority 80 -> EAX,
both with zero register costs. Therefore a generic -1 ESI preference in the
whole link is NOT enough to identify the remaining difficulty load's owner.
Several preferences belong to unrelated inlined animation values.

In particular, anonymous candidate 225/priority 56 had available registers
EBX and ESI, costs 200 and -1. Forcing it to EBX introduced changes around
+0xB7A..+0xBF0, yielded 1,428 differing bytes and 1,130/1,147 identical
instructions, and left the clear-count differences intact. It is not the
sought local fix. See `front_script_tick/front-report.json`.

A temporary allocator trace (`front_script_tick/temporary/events.jsonl`)
found two ESI selections, temporaries 0x643 and 0x7AC. Naively forcing either
to EDX at RegAssign's late selection point crashed c2 at 0x1079C09F instead
of producing an image. These are invalid diagnostic interventions, NOT a
negative proof that a correct earlier allocation change is impossible.

Six source controls applied only to the stage-7 ClearCount call all canonicalized
to the unchanged baseline: dword pointer indexing, nested array, score pages,
difficulty-first addition, separate difficulty byte offset, and pointer addition.

Next useful tracing question: identify the defining IR operand and interference
of the stage-7 difficulty temporary before local RegAssign; do not assume that
an anonymous global candidate with an ESI preference is its owner.

## Restored-tree verification

Both maintained equivalence checks passed after restoration. `make` passed with
all 33 equivalent regions unchanged. `make EXACT=1` passed the complete image
gate: `Whole EXE exact: 487,936 bytes.` No verifier allowances, compiler files,
source flags, manifest ownership, or production implementation changed.
