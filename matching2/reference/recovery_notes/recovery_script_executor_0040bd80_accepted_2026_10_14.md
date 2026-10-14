# Script executor 0x0040BD80: accepted as an equivalent recovery (2026-10-14)

`equivalent/game/recovery_script_executor_0040bd80.cpp` through
`layout/equivalent/recovery_script_executor_0040bd80.json`: 1,564 of 1,568
bytes (code plus the 18-entry jump table), **400 of 444 instructions
identical**, 28 classified hunks (register-choice, evaluation-order, a
3-instruction code-shape, the case 13/14 block order and one table target).

The context is the marktext dispatcher cluster's driver and anchors, minus
its executor copy. Two of its files are replaced by equivalent-only copies
under `equivalent/game/context/`, so the registered marktext cluster keeps
building unchanged.

## What moved the count (305 -> 400)

- **Switch case order.** Source cases follow retail block order: 0, 3, 4, 5,
  6, 7, 8, 15, 16, 17, 9, 10, 11, 12, 13, 14. Case 10 is
  `strcmp(name, "bgm/th10_13.wav")`; with a real literal it folds to
  `repe cmpsb`.
- **ASCII factory 0x43C8B0 in its real shape** (as in
  `src/game/ascii_manager_create_retail_0043c8b0.cpp`). A constructor wipes
  the object and sets flag 2, then a noinline *member* `Configure` runs.
  With that context, LTCG passes draw priority 0x31 in EBX and the five
  stack words exactly as retail does. The old anchor (memset plus a free
  stdcall register function) passed the mode in EBX instead.
- **Handle validation 0x449450 is a free function** with the handle in ESI.
  Retail pushes no receiver for it. The shared context's `__cdecl` member
  spelling pushes the manager and then pops it.
- **Case 8 handle pointer:** `unsigned int* handle = &animation_handles[arg0]`,
  then SetFlag(*handle) and `*handle = 0`. This alone was worth +30. The
  out-record is a case-scoped local.
- **Case 3, ring == 0:** the post-loop MarkText reuses the `manager` local
  read for Find. The else branch is one expression,
  `Validate(...)->MarkText(data_00491c10, color, Decode(...))`.
- **Case 12:** an index loop with a plain manager read per iteration.

## Recorded residuals

- ESI/EDI and EBX/EDI choices in case 3 and case 12. Retail hoists the
  manager into EBX for case 12. The model re-reads it, a 3-instruction
  code-shape hunk.
- The else branch reads the manager before the Validate call; retail reads
  it after.
- LoadAsset: the owner load and the command-pointer store are emitted in
  another order.
- Cases 13 and 14 share their factory tail. Retail places case 13 first and
  jumps forward; the model places case 14 first.
- The flags `or 4` in case 7 uses EDX vs ECX.
