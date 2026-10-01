# Title practice menu rows (0x00431410)

2026-10-02. `src/game/title_practice_rows_00431410.cpp` owns the 419-byte row
draw as ordinary C++ in the new `title_practice_rows_00431410` native-LTCG
cluster, which compiles verbatim copies of the record writer (0x00401530) and
formatter (0x00401630) as unselected anchors plus a synthetic array caller.
The menu receiver in EDI and the text position in EBX follow from that.
Incremental `make` verifies the whole EXE exactly.

* **Alias knowledge again.** Retail reloads the selected shot type, character
  and difficulty after each store of the text colour, but keeps the score file
  pointer and the game thread pointer in registers. Declaring the three
  selections as members of one game state object at 0x00474C68 and taking that
  object's address in the synthetic caller reproduces exactly this split;
  as independent `int` globals they were never reloaded.
* **No record pointer local.** Retail shares only `character + index * 8`
  between the unlocked test and the score load, then applies the member
  offsets (`+0x4E1`, `+0x4DC`). Writing the full member expression at both
  uses gives that; a `PracticeRecord*` local folds `+0x4DC` into the pointer.
* The unlocked flag is at +5 of the 8-byte practice record.

## High score table (0x004329F0), render task (0x0042D260, 0x0042D2F0)

Same day, same cluster. `src/game/title_score_rows_004329f0.cpp` (689 bytes)
and `src/game/title_menu_draw_0042d260.cpp` (the 116-byte page switch with
its jump table, and the 7-byte scheduler callback, rooted as `__fastcall`).

What decided the score table's bytes:

* **A table pointer for one access only.** Retail tests the row's date with
  one folded address, then builds the `localtime` argument in two `lea`s
  (`character + 8`, then `+ offset + 0x20`). The score rows sit in a
  sub-object at +8 of the character block; taking `&character.table` into a
  local for the `localtime` argument and spelling the full path everywhere
  else reproduces it. That one change also moved the menu receiver from ESI
  to EDI, kept the rank in memory and put the constant 1 in EAX ahead of the
  page test, i.e. everything that had looked like separate problems.
* A single-case `switch (phase)` gives retail's `sub eax,2`.
* The shade must be defined before the rank for the loop-end update order,
  and the position declared before the selected difficulty for the order of
  the entry stores.
* The practice records start at +0x4E4 (index `stage - 1`); the five
  per-difficulty clear counts sit in front of them at +0x4D0.

The three replay pages the switch calls (0x00431BA0, 0x00433230,
0x00433B30) are still assembly and take the menu on the stack.

## Replay browser draw at `0x00431BA0` (2026-10-02)

`src/game/title_replay_browser_00431ba0.cpp` owns the 825-byte replay browser
page (case 12 of the overlay dispatch): the 25-slot list in phase 2 and the
selected replay's stage list in phase 4. It is a rooted one-argument stdcall.

The stage loop only matches when every stage slot access spells the whole
`menu->replays[menu->selected_replay]->stages[...]` path and the next stage's
data pointer is held in a local for the two formatted fields. A replay or slot
pointer local keeps the 0x24 stride in a register and folds it into indexed
addressing; the full path leaves the stride in the dead argument's stack home
and forms `replay + stride` once, as retail does.

## High score name entry page at `0x00433230` (2026-10-02)

`src/game/title_score_entry_00433230.cpp` owns the 826-byte page (case 15 of
the overlay dispatch; earlier notes called it a replay stage page). It is a
rooted one-argument stdcall in section `.text$08entry`, placed after the
synthetic context. The menu gained the typed name (+0x58DC), its length
(+0x58E8), the confirmed flag (+0x58EC) and the chosen grid cell (+0x58F4);
`data_004746d8` is the grid's character string.

The compiler decides per function whether to build an 8-byte aligned EBP frame
for the `double` varargs. Probes showed the decision weighs the double
conversions inside loops against the conditional structure of those loops: one
more compare, select or branch in either loop removes the frame, plain stores
and loads do not. Retail has no frame, and the source that reproduces it draws
the grid with two calls (letters, and the three trailing symbols through a
nested conditional); the compiler tail-merges them into the single retail call.
A single call with a `symbol` local gives identical code inside an aligned
frame.

This supersedes `replay_stage_name_draw_00433230_abi_blocker.md`: the formatter's
EBX position argument comes from compiling the real formatter in the cluster.
