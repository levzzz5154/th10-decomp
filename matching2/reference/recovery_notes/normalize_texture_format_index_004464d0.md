# Texture format index mapping at 0x004464D0

Ghidra identifies a 42-byte function with no incoming xrefs. Retail receives
a format-table index in EAX. If rendering option bit zero in `data_00491D78`
is clear, it returns the index unchanged. Otherwise it looks up the value in
the table at `0x0046F288`, maps values `0x15` and zero to index five, maps
value `0x14` to index three, and returns any other index unchanged. The same
mapping occurs in neighboring texture-upload and texture-creation routines.

The [C++ source](../semantic_candidates/normalize_texture_format_index_004464d0.cpp)
expresses this selection directly. The manifest retains the old assembly
record in `previous_record`. Its typed cdecl argument replaces the retail EAX
input ABI; byte matching remains unverified, and no build or byte comparison
was run.

**Build status (2026-09-25):** the full byte-verified build showed that this model does not reproduce the retail bytes. The maintained source keeps the exact assembly, and the model is preserved in `reference/semantic_candidates/`.
