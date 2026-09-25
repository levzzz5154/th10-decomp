# Indexed flag readers at 0x0044A130 and 0x0044A160

Ghidra identifies two independent functions with no incoming xrefs. Both
reject a negative signed 16-bit index, OR a selected SI bit into a 16-bit
output word when active, and return that bit or zero.

At `0x0044A130`, AX indexes signed bytes at a table supplied in ECX. A
negative byte marks the bit active. Retail reads that byte a second time
after updating the output word; the C++ source preserves the read order for
possible overlapping pointers.

At `0x0044A160`, CX selects a bit in a 32-bit stack mask. The x86 shift uses
the low five index bits, so the C++ source masks the shift count with 31. EDX
holds the output word in both retail functions.

The [C++ source](../semantic_candidates/indexed_flag_readers_0044a130.cpp)
uses typed parameters and keeps the mask and return behavior explicit. The
manifest retains both assembly records in `previous_record`. The typed cdecl
arguments replace the retail register and stack ABIs; byte matching remains
unverified, and no build or byte comparison was run.

**Build status (2026-09-25):** the full byte-verified build showed that this model does not reproduce the retail bytes. The maintained source keeps the exact assembly, and the model is preserved in `reference/semantic_candidates/`.
