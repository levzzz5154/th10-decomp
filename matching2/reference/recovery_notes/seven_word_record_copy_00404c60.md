# Paired seven-word copy functions at 0x00404C60

Ghidra identifies two independent functions within the old 35-byte assembly
region. The first (`0x00404C60..0x00404C6F`) copies seven 32-bit words from
EAX to EDX. The second (`0x00404C70..0x00404C82`) copies seven words from EDX
to the block at EAX + `0x1C`, the second slot in a pair. Both use forward copy
order and have no incoming Ghidra xrefs.

The [C++ source](../semantic_candidates/seven_word_record_copy_00404c60.cpp)
uses typed pointers and forward loops. The manifest splits the old region at
the function boundary and retains its old assembly record in `previous_record`
on the first entry. The typed cdecl arguments replace the retail register
ABIs; byte matching remains unverified, and no build or byte comparison was
run.

**Build status (2026-09-25):** the full byte-verified build showed that this model does not reproduce the retail bytes. The maintained source keeps the exact assembly, and the model is preserved in `reference/semantic_candidates/`.
