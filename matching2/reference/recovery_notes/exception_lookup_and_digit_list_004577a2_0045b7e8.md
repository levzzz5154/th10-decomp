# CRT exception lookup and digit-list decoder

Ghidra identifies a 44-byte function at `0x004577A2` with no incoming xrefs.
It receives a table in EDX and a key in ESI, scans `data_00473654` entries of
12 bytes each, compares the first word, and returns the matching entry or
null. `__XcptFilter` at `0x004577CE` uses the same table layout: first word
exception code, second word signal number, third word action. The maintained
[C++ lookup](../semantic_candidates/find_exception_map_entry_004577a2.cpp)
uses that record type. Retail reads the first entry before checking whether
the table count is zero; the typed loop skips that unused read.

Ghidra also identifies a 51-byte function at `0x0045B7E8`, again with no
incoming xrefs. It receives a mutable string in ECX, replaces ASCII digits
with numeric byte values zero through nine, removes semicolons by shifting the
remaining string left, and leaves other bytes unchanged. The maintained
[C++ decoder](../semantic_candidates/decode_digit_list_0045b7e8.cpp)
keeps the cursor at a removed semicolon so the next shifted byte is processed.

Both manifest entries retain their assembly records in `previous_record`.
Typed cdecl arguments replace the retail register ABIs; byte matching remains
unverified, and no build or byte comparison was run.

**Build status (2026-09-25):** the full byte-verified build showed that this model does not reproduce the retail bytes. The maintained source keeps the exact assembly, and the model is preserved in `reference/semantic_candidates/`.
