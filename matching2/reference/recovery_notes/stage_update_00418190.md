# Stage update recovery: `0x00418190` / 1544 bytes

## Status

Not promoted. The production target remains the original naked assembly unit
`matching2/msvc/src/game/stage_update.cpp`, and its manifest record remains
`asm_FUN_00418190_00418190`, `0x00418190`, size `1544`, kind `asm`. No target
LTCG entry was added. Existing unrelated edits in `regions.json`, source
files, and shared matching tools were preserved.

The archived `function_registry.json` is stale for this target: it describes a
semantic function of size `1664`, while the supported retail image and current
manifest both establish `1544` bytes. The current manifest/retail pair is the
authoritative extent.

## Recovered behavior

IDA/Ghidra, the exact disassembly, callers (`00417870`/`004187c0`), neighboring
stage routines, and the archived semantic draft agree on this state machine:

1. At stage frame zero, a context flag `0x08` enters the transition lock and
   publishes result `((~(global_00491ff4 >> 12)) & 1) | 2`. Otherwise the
   player manager is started when present, or the full stage runtime reset is
   performed.
2. At frame `30`, flag `0x800` selects the delayed reset path. Reset clears
   stage arena/runtime state, resets the two frame counters, initializes the
   main stage task/configuration, invalidates the task links, refreshes the
   stage panel, and performs the normal or delayed music/timer/player-spawn
   work.
3. A game-state object whose `+0x2A18` has bit `0x08` is destroyed and freed.
   Context flag `0x04` then marks `0x80` and returns `1`.
4. The routine stops the stage worker, updates the transition result, emits
   frame `0xB7C`/`3000` transition milestones, ticks the stage thread, and
   returns `3` for context flags `0x70`.
5. Otherwise it increments the selected score record's frame count using
   stride `17276` and offset `0x4CC`, capped at `215999999`, conditionally
   updates the score threshold after frame `90`, increments the two global
   frame counters, ticks the context timer, and returns `1`.

## Exact-ABI dependency boundary

The body is coupled to existing exact helper units, not ordinary source-level
calls. The required register inputs observed in retail are:

| helper | retail input |
| --- | --- |
| `0044C150`, `00405ED0`, `00424D90`, `00417040`, `00404ED0` | `ESI` |
| `004045B0`, `00417770`, `00409E50`, `0040AC90`, `00405410` | `EAX` |
| `0042A450`, `0043C8B0` | `EBX` (the latter also has stack arguments) |
| `0040CFB0` | local 16-word state in `EAX`, manager/string on the stack |
| `0043E460` | `EAX`/`EDX` plus stack arguments |

The stack helpers (`00404450`, `00409F90`, `00426F70`, `00420B10`, game-state
destroy/free) also have exact cleanup conventions. In particular, the three
`00409E50` calls use `game_thread + 0x9E14`, `+0x89A0`, and `+0x89A4`; mapping
these to the similarly named `00418A00` recovery helper is not behaviorally
equivalent.

## Focused experiments and mismatch

An isolated semantic C++ candidate was built without changing the production
tree. A forced-inline direct-global version emitted `1553` bytes in the first
shape and `1559` bytes after restoring the retail scratch/state sequencing;
the requested extent is `1544`, so the focused probe stopped on extent before
byte comparison. The direct candidate also exposed the ABI problem: normal
C++ calls placed custom `EAX`/`ESI`/`EBX` arguments nowhere reliably.

A second isolated version added small inline register bridges. It emitted
`1920` bytes and introduced an MSVC frame-pointer prologue (`push ebp; mov
ebp, esp; sub esp, 0x4C`) instead of retail's `sub esp, 0x40; push ebx; push
ebp; push esi; push edi`. It was discarded.

A bounded native-LTCG driver was then tried with the semantic source and the
direct helper boundary. The native linker produced a target contribution of
`0x617` (`1559`) bytes and a `0x29`-byte compiler context; the target image's
first bytes were:

```text
actual:  51 53 8b 5c 24 0c 8b 43 14 55 33 ed 3b c5 56 57
retail:  83 ec 40 53 55 56 57 8b 7c 24 54 8b 47 14 33 ed
```

The native output therefore fails at `0x00418190`, independently of the
later unresolved semantic/helper details. The existing shared cluster
validator then rejected the linker MAP's zero-length `.text` marker (`invalid
MAP contribution on line 8`). Shared Python tooling was not modified.

The production state was verified afterward with:

```text
python3 matching2/tools/matching/probe.py \
  --source src/game/stage_update.cpp --project matching2/msvc \
  --oracle matching2/build/oracle/th10.exe \
  --output matching2/build/probe-stage-update-production-1 --json
```

Result: `EXACT`; the focused region was `_asm_FUN_00418190_00418190`,
`0x00418190`, size `1544`.

## Next dependency checkpoint

Keep the retail target and manifest unchanged. A viable promotion attempt needs
one explicit native-LTCG experiment that models the target's `0x40` local
state and makes each custom register ABI an owned, compiler-visible boundary:
first the `00409E50` timer-state calls and `0040CFB0` local-state call, then
the `EAX`/`ESI`/`EBX` stage helpers. It must validate the complete target
contribution and the compiler context with a clean MAP parser before any
manifest entry or source replacement is considered.
