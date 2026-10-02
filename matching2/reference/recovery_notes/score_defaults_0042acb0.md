# 0x0042ACB0 score record defaults (parked)

The anchor model in `score_manager_native` hand-unrolled the spell loop and is
268 bytes against retail's 274.

Settled:

- The spell loop is the plain `for (spell = 0; spell < 110; ++spell)` writing
  `spell_id` and `difficulty`; the compiler unrolls it five times with the
  three counters retail has.
- The rank loop is indexed (`file->ranks[difficulty][rank]`, inner loop
  running on `score > 0`). A `ScoreRankEntry*` walked with `++entry` grows a
  second pointer for the name and spills the score.
- The strength-reduced pointer follows the last `char`-typed address formed
  in the body. Retail's sits on `stage` (+0x14) with `lea edi, [eax+2]` for
  the name; `char* text = (char*)&entry->stage; text[0] = 1;
  memcpy(text + 2, ...)` with `date`/`continues` as plain members gives that.

Open (9 diff lines):

- retail stores the ninth name byte after the loop compare; every order and
  copy form tried (memcpy, struct copy, strcpy of a literal, 8+1 split) stores
  it immediately or moves the pointer base;
- `movsx ebp, [ecx+edi]` in the unrolled loop has base and index swapped.
