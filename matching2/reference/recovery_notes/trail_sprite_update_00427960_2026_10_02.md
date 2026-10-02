# Trail sprite update and callback

2026-10-02: the complete trail update at `0x00427960` and its registered
scheduler callback at `0x00427950` match retail as ordinary C++ in
`src/game/fun_00427960_00427960.cpp`. The schema-2 layout is
`layout/ltcg/trail_sprite_update_00427960.json`; its real callback is the link
entry, and its sole internal call is the retail call at `0x00427953`.

| Address | Complete contribution | Bytes | SHA-256 |
| --- | --- | ---: | --- |
| `0x00427950` | `TrailSpriteUpdateCallback_00427950` | 12 | `57a30cec3156249fee03a3367ed680dd580b6b3a5ab152b2f820387b23f19103` |
| `0x00427960` | `TrailSprite_00427960::Update` | 359 | `d1ee34eef67ae788818f1759d95615006b85ff67982d21f29c613047a6f38799` |

The global player table has an integer anchor at `+0x3CC`, 33 integer point
pairs at `+0x436C`, and a trail mode at `+0x4474`. Each sprite chooses a
head at `index * 8 + 8`. With the mode zero it remembers that head's
offset from the anchor. With a nonzero mode it moves the head to the anchor plus
the remembered offset and interpolates points `index * 8 + 1` through
`index * 8 + 7`, retaining the fraction in x87 across the integer conversions.
Both paths publish the anchor plus the offset and save the trail mode.

Two ordinary source shapes settled the remaining compiler differences:

- `TrailPoint_00427960::CopyFrom` copies x and then y through a const point
  reference. A generated aggregate assignment reused the first head pointer;
  this explicit coordinate copy naturally emits retail's address recomputation
  before the head stores. It also keeps the complete 359-byte extent.
- The final sum is `player->anchor + offset`. Reversing the sum's operands
  preserved the result but changed the last block's registers and store order.

The entire loop, its six-byte alignment instruction, both float-to-integer
calls and all surrounding code are the unchanged output of the documented
MSVC `/GL` and native `/LTCG` path. No portion is selected separately; no
synthetic caller, raw byte construction, inline assembly, forced volatile,
barrier, compiler plugin, or tool change is used. The obsolete callback-only
assembly source was removed.

The maintained source and layout were rebuilt and their complete contributions
compared without masking to the stable retail oracle. Evidence is retained at:

- `matching2/build/experiments/trail_callback_2026_10_02/maintained_verified/report.json`
- `matching2/build/experiments/trail_callback_2026_10_02/verified_bytes.json`
- `matching2/build/experiments/trail_callback_2026_10_02/integration_proposal.json`

The older parked entry in `callback_thunk_pairs_2026-10-01.md` is superseded by
this recovery.

The manifest is integrated and obsolete assembly owners were deleted. The final
incremental whole-executable build passed with 1,608 unchanged units reused and
three compiled: all 487,936 bytes match retail, with zero masked bytes. SHA-256:
`2f14760b6fbbf57549541583283badb9a19a4222b90f0a146d5aa17f01dc9040`.
All six new callback/worker bodies (1,003 bytes across this and the pause/trail/player
families) were hashed directly from the final executable; evidence is in
`matching2/build/experiments/callback_pairs_2026_10_02_verification.json`.
