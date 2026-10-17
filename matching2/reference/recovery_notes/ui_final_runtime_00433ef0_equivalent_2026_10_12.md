# The music room 0x00433EF0 as an equivalent C++ model (2026-10-12)

**Status (2026-10-12, later the same day): registered equivalent recovery, 694 of 741 instructions identical.**
The model is a rewrite from the retail disassembly on top of the title cluster's helpers, linked
with the real stage-text and animation-registrar sources (`context_sources`). The 47 remaining
instructions are in 31 recorded differences: 14 register choices, 9 evaluation-order swaps,
3 alignment fillers, 4 code-shape hunks (a split read-modify-write of the sprite flags, a jump
over loop padding, two copies through another register) and one loop branch whose target moves
with that padding (both ends were compared by hand: the same loop head). No call, callee or
named address differs. Everything below this paragraph describes the earlier parked draft.

Region: 0x00433EF0..0x004349DB (2796 bytes; 2780 code + 16-byte phase table
at 0x004349CC whose fifth entry sits in the padding at 0x004349DC). The
equivalent model lives in `msvc/equivalent/game/ui_final_runtime_00433ef0.cpp`
with the room view `msvc/include/th10/game/ui_final_runtime_00433ef0.hpp`,
compiled in the title cluster
`layout/ltcg/difficulty_select_update_00430320.json` and registered as
`layout/equivalent/ui_final_runtime_00433ef0.json`.

## Semantics

The music room of the title menu (four-entry phase table, dispatch at
0x00433F07 through the table at 0x004349CC):

- Phase 0 (0x00433F0E): on `timer.current == 1`, install the cursor and
  background slots (95 and 103), load `musiccmt.txt` through
  Archive_LoadFile 0x0044B360, and parse it: every section opened by `#` or
  `@` yields one title (32×64 at +0x698), one comment (32×66 at +0xE98) and
  eight preview lines (32×8×66 at +0x16D8) through StageText_ExtractLine
  0x00434A20 / StageText_SkipLine 0x004349E0. Eight preview-line text
  objects are created (0x00449950 allocate, 0x00449870 script start,
  0x004489D0 register, handles at +0x664). The draw loop slides the next
  two rows in (20.0f pitch at 0x00470CA0, base y 96.0f at 0x00470C80) and
  titles unknown tracks with the "No.%d" format at 0x0046ECF4. Confirm at
  `timer.current >= 10` retargets phase 1.
- Phase 1 (0x00434346): reveal two characters of the selected track's
  preview lines per even frame (up to 8), then phase 2 after
  `timer.current > 4`.
- Phase 2 (0x0043441B): the same reveal, cursor movement (0x0044BEA0 with
  the input mask at 0x00474E36), scroll clamping, row repositioning with a
  40.0f slide threshold (0x00470C64), and the confirm/cancel pair. Confirm
  stops the row text objects at frame 3 and starts the preview of the
  selected track; a track whose comment was never heard requires a second
  confirm (the spoiler acknowledgement, `preview_armed` at +0x694). The
  music requests go through the table at 0x00492590 (commands 2/3/4 via
  0x0043E460), the heard flags live at 0x0047783C + 0x1D892 + track.
  Cancel frees the file buffer (0x00452422), stops the rows and previews,
  and retargets phase 3.
- Phase 3 (0x0043494E): after ten frames remove the slots, free the
  fallback handle, disable the timer, load `bgm/th10_02.wav` and return to
  the main menu.

## Recorded differences (155 hunks, 404 instructions; 337 of 741 identical)

Dominated by two compiler choices the source cannot spell differently:

1. The zero register: the model zeroes EBX/ESI once per block and uses it
   as the source of the constant 0 (`push ebx`, `mov [ebp+0x440],ebx`,
   `cmp eax,ebx`) where retail materializes the immediate 0 at every site
   (`push 0x0`, `test eax,eax`). 131 hunks are of this family.
2. Frame slot choices ([esp+0x24] against [esp+0x28]) and the register a
   short-lived value lives in — 24 register-choice hunks.

The phase dispatch compiles to the same jump-table shape (the model's table
at model offset 2528 with entries matching the case order); the tail
comparison bridges the retail table at 0x004349CC with the model's.

## 2026-10-17: zero-candidate family named; parked

The residual is the `msvc-c2-immediate-register-candidates` family in
reverse of `anm_texture_fill_transparent`: here the model shares the zero in
EBX/ESI (`push ebx`, `cmp eax,ebx`) where retail materializes the immediate
at every site (`push 0x0`, `test eax,eax`). The memory's lever is to stop
the zero being shared in the blocks where it competes (an immediate becomes
a candidate only at the second same-value same-type use), but the candidate
spellings that split a type without changing bytes (signed vs unsigned vs
pointer zero) are all one candidate per the memory's own rule, so the split
has to come from the value paths themselves. The 24 register-choice hunks
are the frame-slot/short-lived-value contest of the note's residual 2.

Region stays equivalent (1640 differing bytes).
