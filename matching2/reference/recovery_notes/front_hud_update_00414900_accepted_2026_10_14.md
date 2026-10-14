# Front HUD update 0x00414900: accepted as an equivalent recovery (2026-10-14)

`equivalent/game/front_hud_update_00414900.cpp`, built through
`layout/equivalent/front_hud_update_00414900.json` with
`src/game/front_script_tick_00415e90.cpp` as context. Result: all 3,836
bytes, **1,064 of 1,089 instructions identical**, 22 recorded hunks (block-order 18,
evaluation-order 10, code-shape 7, alignment-padding 2). The structural
weight is 25. The parked model stood at 502.

## Semantic fixes (the bulk of the distance)

- **The dispatcher takes the sequence runtime.** Retail pushes
  `front->sequence_9eb8` (ESI) into 0x415E90. The model passed `front`.
- **The notice-slot loop runs only while the boss gauge is active.** It
  follows the pending-banner create inside the gauge branch. The inactive
  branch flags the pending banner, clears the gauge fields and goes
  straight to the sequence tick.
- **The 0x474C84 progress counter is signed** (`jl`/`setge`). The shared
  header declares it unsigned, so the switch casts to `int` at each read,
  and retail reloads it at each read.
- **The gauge flag test.** `if (flags & 8)`: the stop-frame-2 (close) path
  falls through, and the stop-frame-3 (open) path is the branch target.

## Shape facts

- **Drop the ABI-freezing roots.** Only the 0x415AE0 callback stays
  rooted. Rooting every helper froze their declared ABI (502 -> 579).
- **The resource pointer is read before `Allocate`** in both creates.
  Retail keeps it in a callee-saved register across the call. For the
  slot-loop create, this single change took the count from 674 to 995.
- **Stop frames are a plain `unsigned short` local** shared by the node and
  its children (retail's `mov ecx,N` reused in the children loop). They are
  not a volatile slot.
- The list registration mirrors 0x4489D0 (`tail->next->previous = node`).
- Gate word: `~(flags >> 4) & 1`, then `~flags & 1`. The difficulty lane
  `(flags >> 1) & 3` is recomputed inside each state branch.
- Boss alpha: `if (offset >= limit) alpha = 0xFF; else ...` (retail's
  fall-through is the 0xFF store).
- The pending stop-frame-2 call is `if (pending) Flag(pending);` followed by a
  single shared `flags &= ~8`.
- Slot index: `unsigned` with an `(int)i < count` test (retail `jb` on the
  ten-slot bound and `jge` on the count).

## Remaining differences (recorded)

- The next-id wrap: retail copies the incremented id to a second register,
  tests it and `inc`s the copy. The model stores the constant 1. The
  standalone 0x4489D0 has the same retail shape. Six source forms all
  give the model's shape inside this function.
- The sequence-slot clear stores (`slots[k] = 0`) are scheduled one load
  later.
- Two `fadd` operand orders and a `test byte [mem]` loaded into `cl` first.
