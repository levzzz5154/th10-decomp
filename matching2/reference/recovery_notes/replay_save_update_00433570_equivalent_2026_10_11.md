# Replay save screen 0x00433570: equivalent (2026-10-11)

`matching2/msvc/equivalent/game/replay_save_update_00433570.cpp`, verified by
`layout/equivalent/replay_save_update_00433570.json` against the context of
the title-menu cluster `layout/ltcg/difficulty_select_update_00430320.json`:
1,460 of 1,460 bytes used, 397 of 399 instructions identical, two
base/index swaps, nothing else.

## The two instructions

Both inlined `strcpy` loops (name proposal in phase 2, last-name store in
phase 3) store through `walk + (destination - source)`. Retail encodes the
walked pointer as base (`mov [eax+ecx],dl`), the model the difference
(`mov [ecx+eax],dl`). The sibling name entry 0x00432CB0 has the model's order
in retail, with the same statements.

## Why

`FactCanonSort`/`OptCmpHashVal` put the operand with the larger node hash
first. For a temporary the hash is `0x10000 + ((id << 6) & 0xFFFF)`, so it
**wraps at symbol id 1024**. The walked pointer is a front-end temporary read
from the IL (ids 176 and 338 here); the loop-invariant difference is created
by a loop pass (caller chain 0x1078F5B5 <- 0x1078679E through the new-temp
routine 0x1074B014) and always gets a fresh id, here 982 and 999. Retail's
order needs those ids at 1024 or above, that is 42 or more further symbols
in the function before that pass.

Measured with scratch tracers on the cluster link (SymAlloc returns
0x10791DF7 / 0x1074A357 / 0x1074B88E, function marker 0x107B1491, breakpoints
armed only after the preceding function so one run takes 40 s):

- ids are per function: the first symbol of every function is 65, whatever
  else the translation unit or the link holds. One translation unit for five
  handlers changed nothing.
- moving blocks into `__forceinline` helpers, named locals, accessors and a
  phase-as-inline-function form leave both ids at 982/999: inlinee symbols
  are freed and their records reused.
- the pre-optimizer symbol count moves in steps of 32. 60 calls of a no-op
  inline `Touch(room, k)` at the top of the function change nothing, 75 give
  +32 (ids 1014/1031, the phase 2 copy flips), 86 give +64 (1046/1063, both
  flip and the function is byte-exact with no other change).

So retail's function carried a few dozen more live symbols than any natural
spelling of the visible code produces, most likely inline calls that leave no
instructions. The padding is not source, so the region is parked as
equivalent rather than shipped with it.

## Source shapes that mattered for the other 397 instructions

- the replay header is reached through `ReplayFileHeader** header =
  &data_00477838->header` for the `time()` call and the stage store (retail
  keeps `&replay->header` in ESI and reloads through it);
- left/right on the grid are `if (cell % 13 != 0) Advance(-1); else
  Advance(12);` statements (a ternary argument becomes branch-free);
- the slot written after the save is a named local read before
  `ReplayFile_Open`;
- phase 4 frees the replays with the delete written out; the call in phase 3
  uses 0x004297B0, whose stand-in (`equivalent/game/replay_delete_004297b0.cpp`)
  gets the retail ESI convention by itself;
- backspace on an empty name is a `break` out of the switch, which also skips
  the confirm sound and the cancel test.

## 2026-10-17: operand-order sweep, still parked

The recorded idea that the operand order or computation order in the source
could pick the base/index order was tested against `equivalence.py --record`
(each variant one build):

- `&save->name[0]` / `&g_score->last_name[0]` index form at both strcpy sites;
- named destination/source pointer locals around each call, in both
  declaration orders (which one is computed first);
- dropping the named `header` pointer local (the 0x004250B0 lever) — that one
  keeps the model at base/index 2 and adds 10 other differences;
- dropping the `grid` pointer local — no change.

None moved a single instruction. A diagnostic hand-written byte loop replaces
both swaps (base/index 0) but of course loses the compiler's inlined `strcpy`
shape that the other 397 matched instructions are built from, which confirms
the two stores are decided entirely inside the expansion by the temp-id hash
wrap at 1024 (see `msvc-c2-operand-order-mechanism`). The only measured mover
remains the pre-optimizer symbol count (86 no-op inline calls = +64 = the
function byte-exact); that padding is not source, so the region stays parked.
