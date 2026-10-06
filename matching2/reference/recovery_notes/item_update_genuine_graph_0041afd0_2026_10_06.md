# Complete item update and genuine conversion graph, 2026-10-06

This note records the initial 2,448-byte / 238-case checkpoint. The
[precision follow-up](item_update_precision_0041afd0_2026_10_06.md) supersedes
its maintained measurements: it exposes and corrects falling-Y rounding
and screen-limit errors, passes 370 cases and measures the complete update at
2,452 bytes.
Initial sources and reports are preserved under the candidate's
`evidence/initial_graph/`; current receipt/evidence describe the corrected graph.

The complete ordinary C++ item-update candidate now passes **238 bounded
retail/native execution comparisons**. Production's existing 165-byte
`ConvertItems` recovery now uses its genuine complete update caller and passes
the normal raw fixed-address gate. Both whole-executable build modes pass.
Update and spawn remain assembly-owned; no new recovered bytes are claimed.

The maintained candidate is
[`item_update_0041afd0/`](../semantic_candidates/item_update_0041afd0/).
Its [receipt](../semantic_candidates/item_update_0041afd0/receipt.json) and
[`evidence/`](../semantic_candidates/item_update_0041afd0/evidence/) preserve
the source hashes, full contribution hashes, behavioral report, failing scalar
control, conversion gate and production audit.

## Complete source and field corrections

[`update.cpp`](../semantic_candidates/item_update_0041afd0/update.cpp)
contains the full 2,198-slot loop, all item states, delayed script activation,
falling/seeking behavior, collection kinds, point-value calculation, focused
and unfocused magnet boxes, animation/timer updates and full-power conversion.
It replaces the earlier partial semantic sketch with a complete callable body.

Retail accesses a third velocity component at item offset `0x3C0`. The coherent
item type now uses three floats, a motion counter at `0x3C4`, and the frame
timer at `0x3C8`; the record remains `0x3F0` bytes. The manager uses one actual
`items[2198]` array, permitting the complete loop without pointer arithmetic
across separate C++ array objects. Spawn still searches only the first 150
records and uses the remaining 2,048 as its special ring. Run-state score,
gauge, power, lives and timer fields share their real `0x00474C40` object.

The first complete scalar-displacement source failed seeded `random3`, slot
2,117, state 3, at speed 1.5. Retail's final Z bytes were `3c 28 b2 bf`; native
produced `3d 28 b2 bf`, a one-ULP difference. Retail rounds the displacement
before adding it. Constructing the existing `Vector3Value` displacement makes
that real float boundary explicit without volatile forcing or instruction
patches. The rejected source and entire failure observation are preserved in
`evidence/rejected_scalar_update.cpp` and `rejected_scalar_failure.json`.

## Complete native measurement

The maintained `visible_resource_graph` contains 24 complete function
contributions. The diagnostic runner links below retail at `0x00100000` and
again at `0x10000000`; its COFF absolute bindings and address normalizer use
the same bases. It rejects native/external entry collisions. Every emitted
switch-table byte is included: 64 for update and 23 for spawn.

| Function | Native / retail bytes | Result |
| --- | --- | --- |
| UpdateItems, `0041AFD0` | 2,448 / 2,320 | 2,202 unequal overlapping bytes; unselected |
| Spawn, `0041BB00` | 819 / 819 | Two unequal bytes, offsets `17A` and `17F`; unselected |
| ConvertItems, `0041BA50` | 165 / 165 | Full diagnostic equality, separately proven raw at its fixed address |

Fourteen complete bodies have diagnostic equality: LoadScript (203), the two
line callers (609/623), ConvertItems (165), AdjustPower (42), AddScore (46),
AddGauge (46), AdvanceGaugeTimer (93), FrameTimerAdvance (88), FloatingTextSpawn
(167), AngleFromPoint (67), SoundQueueQueuePan (149), SetPowerDigits (79), and
ResourceConfigure (356). This is comparison evidence for the complete graph;
it does not promote the unselected update or spawn bodies.

ResourceConfigure's full ordinary C++ body is visible to LTCG. With it,
SetPowerDigits becomes exactly 79 bytes. The four new scalar aliases are
verified against retail's pool: `40A6AAAB` at `00470B20`, `3F800000` at
`00470AFC`, `3F000000` at `00470B0C`, and `3B800000` at `00470B7C`.
The diagnostic native PE SHA-256 is
`8d2123842c4846ab067181249510c97a4fc379f6d8f5d1c80a0d4cecd7259ec2`.

## Execution evidence and limits

The 238 comparisons execute the unmodified complete retail/native loop over
all 2,198 records. Real score, timer, angle, floating-text, sound-pan, power-HUD
and resource-configuration bodies execute. Checks compare the entire item pool,
whole active records, run-state bytes, HUD/text/sound memory, call order and
arguments, return value, stack cleanup, preserved registers, floating-point
control word and x87 balance. They include normal/special array boundaries,
states 0–6, kinds 0–12, collection/magnet edges, fractional speeds, offscreen
retirement, full-power transitions, score tiers, timer initialization/clamping,
callback mutations, non-null digit resources, NaN/infinity coordinates and 80
seeded random cases.

Animation initialization/execution, banner creation/removal, life icons, the
sound Queue call, player PowerChanged, and terminal ConvertItems are scripted
shared boundaries. Their retail private register conventions and ordinary
candidate conventions are decoded independently by the fixture. No native code
is patched. Terminal conversion is proved separately by the full raw gate;
these comparisons do not constitute a complete game integration test.

Earlier 217- and 235-case reports used smaller fixtures. Only the maintained
resource-visible graph has the current 238-case claim. The fixture hash is
`6846d0aca231636e64b1cbb3f213feed69aecd7bd7bf8395d6c1d357add55a8e`.

## Production integration and verification

The manifest selects
[`item_convert_genuine_0041ba50.cpp`](../../msvc/src/game/item_convert_genuine_0041ba50.cpp)
through
[`item_convert_genuine_0041ba50.json`](../../msvc/layout/ltcg/item_convert_genuine_0041ba50.json).
Its driver includes the genuine full update, complete item/line/animation graph
and actual second translation unit. Update is declared as its full 2,448-byte
unselected context. The other complete contributions are unselected anchors;
only ConvertItems is selected. No synthetic caller or compiler entry is used.

The old player cluster retains its complete conversion body as an unselected
anchor, preserving the other eight selected functions' bytes. Only the new
cluster owns the selected conversion region. Unused scalar aliases were
properly omitted from the conversion layout after the normal validator rejected
them; no matching rule was loosened.

All 165 fixed-address conversion bytes equal retail. Their SHA-256 is
`d31835ee23314e37e524ed1ab5357a8354a94ad3f41cede33600555aa3aacd9a`.
The isolated proof and installed production report both record zero instruction
patches, zero masks, and no reference-code build use.

`make` and `make EXACT=1` both pass. The normal mode retains eight existing
equivalent recoveries. The final exact-mode EXE is raw-identical to the oracle:
487,936 bytes, SHA-256
`2f14760b6fbbf57549541583283badb9a19a4222b90f0a146d5aa17f01dc9040`.
The fresh audit verifies 964 native layouts, 1,483 selected functions and 3,984
unique current compiler inputs against their actual files and retail bytes.

Counts remain 2,254 ordinary C++ regions / 199,062 bytes and 60 actual remaining
assembly regions / 89,245 bytes. All four laser cutters remain assembly-owned.
New recovered bytes: **zero**. The full inline-asm-free decompilation goal
remains active. Reproduction commands are in the candidate README.
