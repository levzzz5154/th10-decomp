# Entity-region sweep recovery note

The archived semantic model, coverage entry, callers, and IDA/Ghidra listings
agree on the behavior at `0x00408210`: derive an axis-aligned rectangle from
the owner center/full extent, scan 2000 entries at stride `0x7F0`, skip state
0 and 3, use inclusive two-dimensional overlap, set entry flag bit 3, and on
a hit optionally spawn effect `0x0041BB00`, create script 371 through
`0x00448DB0`, resolve it through `0x004491C0`, select the small/medium/large
palette from descriptor radius thresholds 16 and 32, write record color
`+0x2FC`, and clear the entry timer at `+0x450`.  The third-axis bounds are
computed by retail but are dead in the overlap test.

Checkpoint result: `0x00408210`, size 585, was **NOT PROBED** because the
requested terminal checkpoint arrived before the entity candidate was staged.
Production `src/game/entity_region_sweep.cpp` remains the legacy assembly
implementation, and no entity-region LTCG manifest, context source, or probe
output was created.  It is therefore not integrated and has no exact claim.

Next dependency: stage a focused native-LTCG candidate with the actual owner
and external animation/effect ABIs, then accept it only after the exact probe
matches all 585 bytes and relocations.  The likely blockers to resolve first
are the retail owner-in-`EBX` loop convention and the `0x0041BB00` /
`0x00448DB0` / `0x004491C0` register-and-stack call conventions; a behavioral
match alone is insufficient.
