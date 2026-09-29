# Three cursor value readers at 0x00454EB8

Ghidra identifies three independent functions in the old 31-byte assembly
region, with no incoming xrefs:

- `0x00454EB8..0x00454EC0` advances the cursor by four and returns the
  previous 32-bit value in EAX.
- `0x00454EC1..0x00454ECC` advances by eight and returns the previous 64-bit
  value through EDX:EAX.
- `0x00454ECD..0x00454ED6` advances by four and loads the previous 16-bit
  value into AX. Retail leaves the upper EAX bits from the cursor pointer.

Each receives the cursor address in EAX. The earlier
[cdecl candidate](../semantic_candidates/cursor_value_readers_00454eb8.cpp)
passed it on the stack and did not reproduce the retail bytes.

The maintained [word/halfword source](../../msvc/src/unidentified/unassigned_00454eb8.cpp)
uses `regparm(1)` and the pinned GCC/LLVM-COFF profile; the
[pair source](../../msvc/src/unidentified/unassigned_00454ec1.cpp) uses the
same entry convention and the pinned Clang/LLVM-COFF profile. The cursor update
is volatile so both compilers retain the memory increment. GCC's halfword
return writes only AX, preserving retail's upper EAX bits; Clang returns the
pair in EDX:EAX. The manifest splits all three functions at the Ghidra
boundaries, with the original assembly region in each `previous_record`.
The focused compiler probe verifies all 31 bytes without assembly or
relocations.
The complete `make` build also verifies the 487,936-byte executable.
