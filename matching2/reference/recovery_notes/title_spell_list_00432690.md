# Title spell card list page at `0x00432690` (parked)

2026-10-02. Not promoted; the region stays assembly. A readable candidate
compiles to the right structure inside the `right_aligned_text_00447ae0`
cluster (rooted `int TitleMenu_00431410::BuildSpellList()`, menu in ECX) but
the named-card branch allocates registers differently.

## Behaviour

- `spell_page` (+0x1D4) selects ten cards of the menu's difficulty (+0xFC)
  from `g_spell_difficulty` (0x4743C0, 110 entries); the first loop skips
  `spell_page * 10 - 10` matching cards.
- `listed_spells` (+0x2AC) counts the lines filled; `spell_lines[10]` (+0x5D4)
  are the ids of the ten text animations. Each id is resolved through the
  animation manager's two lists (inlined three times) and cleared when stale.
- A card met at least once (`records[6].spells[i].attempts`, the all-shot
  total) shows `"No.%3d %s %4d/%4d"` with the name copied into a 168-byte
  buffer and padded with spaces to 42 characters, coloured 0xFFFF80 when the
  selected shot (`cursor`, +0x24) has captured it and 0xEFEFEF otherwise.
  Other cards show 21 full-width question marks in 0x808080. Lines past the
  last card get `" "` in white.
- `ScoreSpellRecord` is name[0x80], captures +0x80, attempts +0x84.

## What matched and what did not

- `size_t pad = 42 - length; memset(name + length, ' ', pad); length += pad;`
  reproduces retail's `add edx,esi`; writing `42 - length` twice folds the
  length to the constant 42.
- The unmet-card branch and the blanking loop match with a per-branch
  `record` pointer and `manager` local.
- In the named-card branch retail loads the manager into ESI right after the
  cursor, keeps the lookup result in EAX and moves it to ESI at the call.
  The candidate gets the result straight into ESI. Declaring
  `record, manager, terminator` in that order gives retail's instruction order
  but moves the menu to EBX for the whole function.
- The formatter really is `text->FormatCentered(manager, ...)`: with the
  manager as the receiver or as a leading parameter LTCG drops the unused
  argument, and retail pushes it.

The candidate source is kept in `reference/semantic_candidates/title_spell_list_00432690.cpp`.

2026-10-06: a new complete three-unit native graph measures the retained
candidate at 834/850 bytes, and the earlier-manager order at 850/850 with
register and stack-home differences. The formatter and dispatcher both
match exactly. The smaller graph also changes the blank-loop counter and
masked path, so the branch-level observations above describe the earlier
larger cluster only. The shared header's missing member declaration has
been repaired. See `title_spell_list_native_2026_10_06.md` and the tracked
`reference/semantic_candidates/title_spell_list_00432690/probe.py`.
