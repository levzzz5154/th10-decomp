# Shared asset path copy at 0x00418850

Ghidra identifies a 65-byte function with no incoming xrefs. Retail receives a
NUL-terminated source string in EAX, clears the first byte of the shared
filename buffer at `0x00497C38`, appends the source string, and returns the
buffer pointer in EAX. Other recovered asset loaders use this buffer with the
same clear-and-append sequence.

The [C++ source](../semantic_candidates/copy_asset_path_00418850.cpp)
expresses this as `strcat` after clearing the buffer. The manifest retains the
old assembly record in `previous_record`. The typed cdecl parameter replaces
the retail EAX input ABI; byte matching has not been verified, and no build or
byte comparison was run.

**Build status (2026-09-25):** the full byte-verified build showed that this model does not reproduce the retail bytes. The maintained source keeps the exact assembly, and the model is preserved in `reference/semantic_candidates/`.
