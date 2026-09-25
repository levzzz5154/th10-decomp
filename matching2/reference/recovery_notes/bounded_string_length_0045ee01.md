# Bounded string length at 0x0045EE01

Ghidra identifies a separate 28-byte function immediately after the return
at `0x0045EE00`. Its body is instruction for instruction the same as the
`_strncnt` helper at `0x00461ADD`: it returns the smaller of the first NUL
position and the supplied bound. The retail entry receives the string in EAX
and the bound on the stack. Ghidra reports no incoming xrefs to this copy.

The maintained [C++ source](../semantic_candidates/bounded_string_length_0045ee01.cpp)
uses two explicit cdecl arguments and a bounded scan. This removes the copy's
inline assembly while leaving the referenced `_strncnt` entry at `0x00461ADD`
for its caller cluster. The manifest keeps the original assembly record in
`previous_record`. The original EAX entry ABI and retail byte identity are
not yet reproduced by the new source; no build or byte comparison was run.

**Build status (2026-09-25):** the full byte-verified build showed that this model does not reproduce the retail bytes. The maintained source keeps the exact assembly, and the model is preserved in `reference/semantic_candidates/`.
