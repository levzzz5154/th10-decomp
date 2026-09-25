# Three cursor value readers at 0x00454EB8

Ghidra identifies three independent functions in the old 31-byte assembly
region, with no incoming xrefs:

- `0x00454EB8..0x00454EC0` advances the cursor by four and returns the
  previous 32-bit value in EAX.
- `0x00454EC1..0x00454ECC` advances by eight and returns the previous 64-bit
  value through EDX:EAX.
- `0x00454ECD..0x00454ED6` advances by four and loads the previous 16-bit
  value into AX. Retail leaves the upper EAX bits from the cursor pointer.

Each receives the address of the cursor in EAX. The [C++ source](../semantic_candidates/cursor_value_readers_00454eb8.cpp)
uses typed pointer and return values. The manifest splits the original region
at the three Ghidra function boundaries and retains the old assembly record
in `previous_record` on the first entry. The typed cdecl argument replaces
the retail EAX input ABI, and the 16-bit return omits the incidental upper EAX
bits. Byte matching remains unverified; no build or byte comparison was run.

**Build status (2026-09-25):** the full byte-verified build showed that this model does not reproduce the retail bytes. The maintained source keeps the exact assembly, and the model is preserved in `reference/semantic_candidates/`.
