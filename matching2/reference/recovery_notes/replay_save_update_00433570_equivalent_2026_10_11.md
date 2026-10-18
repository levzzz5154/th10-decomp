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

## 2026-10-17: the symbol window is measured exactly, and genuine source cannot reach it

`OptCmpHashVal` gives a temporary `0x10000 + ((id << 6) & 0xFFFF)`, and the
larger hash becomes the first operand. Retail's difference temp must hash
*below* the walked pointer (ids 176/338), which needs its id 42+ above the
model's 982/999. From that, the admissible growth is `K` in [25, 41] for one
store and `K >= 42` for both — so the target is not "more symbols", it is one
specific window.

The symbol table grows in slabs of 32, which is why the measured response
plateaus rather than climbing:

| declarations added to the 25 named constants | result |
| --- | --- |
| 2–16 with an initialiser | 398/399, one swap left |
| 18–24 with an initialiser | 399/399, byte-exact |
| 16–32 uninitialised (`int x;`) | 398/399 — contributes nothing |
| 8–16 `const` with an initialiser | 398/399 |
| 24–32 `const` with an initialiser | 399/399, byte-exact |

Only *expression-valued* declarations move the count; bare declarations fold
away first. Naming the handler's 25 magic numbers is genuine source and lands
**one of the two** stores (398/399, one differing byte) — a real improvement
over the recorded two swaps, but not a promotion. Adding the genuine field
names on top (`phase`, `name`, `last_name`, `cells`, `name_length`,
`item_count`, `cursor_selection`, `keys_held`) changes the addressing and
destroys the match (a branch retargets).

So the region needs roughly 64 more symbols than any readable spelling of this
code produces. `ida/th10.exe.c` and `ghidra_augmented/functions/00433570.c`
agree statement for statement with the model — nothing is missing from the
body — and the `.rdata` allocation logs are one per `new` site (`title.cpp:153
TitleInf`), of which this handler has none. The declarations that produced
retail's symbol count emitted no instructions and left no structural trace, so
they are not recoverable from the binary. Reaching 64 takes 24 invented
expression-valued declarations (`const unsigned probe_N = room->phase + N`),
which is padding. Region stays equivalent.

## 2026-10-17: the free-list levers tested; the catalogue's verdict stands

`msvc-inlined-strcpy-walked-pointer-free-list` gives a lever the symbol-count
route does not: the walked pointer is set by *recycled* temp ids, so changing
what is freed just before each inlined `strcpy` should flip it without
touching the symbol total. Six shapes measured against the baseline 397/399,
2 base/index swaps, 0 recorded hunks, 2 differing bytes:

| variant | result |
| --- | --- |
| `capture-preceding-result` | 395/399, 3 hunks, 936 bytes — worse |
| `forwarder-before-site1` | 390/399, 9 hunks, 973 bytes — worse |
| `six-arg-forwarder` | 383/399, 14 hunks, 943 bytes — worse |
| `forwarder-before-both`, `forwarder-before-site2`, `two-calls-one-statement` | a branch retargets |

None flips the two `SIB` bytes. That agrees with
`msvc-c2-operand-order-mechanism`, which documents this exact region and says:
when ids sit a few dozen below 1024 and both copies are swapped, **stop
sweeping — park as equivalent**. The free-list rule solved 0x00419960 because
that site's ids were near the wrap; here they are not, so the recycle history
cannot reach the window either.

Combined with the symbol-count work, this region's two bytes are closed off
from every documented route: neither the total count nor the free-list
recycling can push the loop temp into the wrap window. Region stays
equivalent.

## 2026-10-17: promoted using named menu predicates

The conclusion that genuine used source cannot reach the symbol window was
too strong. Naming existing conditions (at their original evaluation points)
adds the required symbols without unused declarations or altered code. Twelve
named predicates fix one SIB byte; sixteen fix both. The complete 1,460-byte
body is now native byte-exact and selected by `layout/ltcg/replay_save_update.json`.
See `replay_save_update_00433570_exact_2026_10_17.md` for the implementation
and native-cluster evidence.
