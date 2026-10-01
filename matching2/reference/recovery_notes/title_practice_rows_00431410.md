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

The dispatcher at 0x0042D260 (and its 7-byte adapter at 0x0042D2F0) still
needs 0x004329F0, which also takes the menu in EDI.
