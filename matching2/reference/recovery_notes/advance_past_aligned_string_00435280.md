# Four-byte padded string cursor at 0x00435280

Ghidra identifies a 51-byte function with no incoming xrefs. The retail entry
takes the address of a string cursor in EDX. It scans through the string's NUL,
rounds the consumed byte count up to a multiple of four, advances the stored
cursor by that count, and returns the new cursor in EAX. Padding is relative to
the string length, regardless of the cursor's absolute alignment.

The [C++ source](../semantic_candidates/advance_past_aligned_string_00435280.cpp)
expresses the scan and rounding with `strlen` and a typed `char**` argument.
The manifest retains the old assembly record in `previous_record`. The typed
cdecl argument replaces the retail EDX input ABI; byte matching remains
unverified, and no build or byte comparison was run.

**Build status (2026-09-25):** the full byte-verified build showed that this model does not reproduce the retail bytes. The maintained source keeps the exact assembly, and the model is preserved in `reference/semantic_candidates/`.
