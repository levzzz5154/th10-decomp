# Indexed 16-byte record setter at 0x00412750

Ghidra identifies a 56-byte function with no incoming xrefs. Retail uses ESI
for a base address, EDX for an index, ECX for a status, and three stack words
for the payload. It writes status at `base + 0x2494 + 0x10 * index`. If status
is nonnegative, it writes the three following words from the stack; if status
is negative, the existing payload remains untouched. The last store uses
`base + 0x10 * (index + 0x24A)`, which is the same record's fourth word.

The [C++ source](../semantic_candidates/set_indexed_record_00412750.cpp)
names the 16-byte record fields and conditional update. The manifest retains
the old assembly record in `previous_record`. The typed cdecl arguments
replace the retail register and callee-cleanup stack ABI; byte matching is
unverified, and no build or byte comparison was run.

**Build status (2026-09-25):** the full byte-verified build showed that this model does not reproduce the retail bytes. The maintained source keeps the exact assembly, and the model is preserved in `reference/semantic_candidates/`.
