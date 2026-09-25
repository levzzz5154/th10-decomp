# Packed field accumulators at 0x00446530 and 0x00446570

Ghidra identifies two separate 55-byte functions with no incoming xrefs.
Both receive RGB running totals in EAX, a packed 16-bit pixel in EDX, and a
qualifying-pixel count in ESI. The first (`0x00446530`) handles ARGB1555: it
requires alpha bit 15 and adds the red, green, and blue 5-bit fields at shifts
10, 5, and 0. The second (`0x00446570`) handles ARGB4444: it requires a
nonzero high alpha nibble and adds the RGB 4-bit fields at shifts 8, 4, and
0. Each increments the count only when its alpha rule holds. The adjacent
`0x00446500` helper accumulates enabled RGB records; the latter packed helper
has the same behavior as the previously recovered one at `0x00436D60`.

The [C++ source](../semantic_candidates/packed_field_accumulators_00446530.cpp)
uses typed totals and makes both masks explicit. The manifest retains each
assembly record in `previous_record`. Typed cdecl arguments replace the
retail register ABIs; byte matching remains unverified, and no build or byte
comparison was run.

**Build status (2026-09-25):** the full byte-verified build showed that this model does not reproduce the retail bytes. The maintained source keeps the exact assembly, and the model is preserved in `reference/semantic_candidates/`.
