# Multibyte code-page sentinel resolver at 0x0045CD10

Ghidra identifies a 70-byte function ending at `0x0045CD55`, with no incoming
xrefs. Its retail entry takes a code-page value in EAX. It clears
`data_00477690`, then treats -2 as the OEM code page from `GetOEMCP`, -3 as the
ANSI code page from `GetACP`, and -4 as the current value in `data_00477664`.
Each special value sets the flag to one; other values return unchanged. The
same special-value handling appears in `__setmbcp` at `0x0045D15C`.

The [C++ source](../semantic_candidates/resolve_multibyte_code_page_0045cd10.cpp)
uses an explicit cdecl argument and the existing typed import-pointer pattern.
The original register entry ABI and retail byte identity are not yet reproduced.
The assembly record remains in `previous_record`; no build or byte comparison
was run.

**Build status (2026-09-25):** the full byte-verified build showed that this model does not reproduce the retail bytes. The maintained source keeps the exact assembly, and the model is preserved in `reference/semantic_candidates/`.
