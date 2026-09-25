# Indexed platform-interface query at 0x0044D400

Ghidra identifies the complete 52-byte function through `0x0044D433` and
reports no incoming references. Retail receives the state in EAX, the index
in EDX, and the output pointer in ECX. It returns `0x800401F0` when the
interface table is absent and `0x80070057` when the index exceeds its count.
For a valid slot, it clears the output and invokes the first virtual method
of the selected interface with the 16-byte interface identifier at
`0x0046747C`. That call's result is returned unchanged.

The [C++ source](../semantic_candidates/query_indexed_interface_0044d400.cpp)
models the table and the virtual method explicitly. The manifest retains the
original assembly record. Its ordinary cdecl parameters replace the three
retail register inputs; byte matching has not been verified, and no build or
byte comparison was run.

**Build status (2026-09-25):** the full byte-verified build showed that this model does not reproduce the retail bytes. The maintained source keeps the exact assembly, and the model is preserved in `reference/semantic_candidates/`.
