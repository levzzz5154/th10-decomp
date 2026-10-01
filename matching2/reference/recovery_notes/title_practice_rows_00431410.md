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
