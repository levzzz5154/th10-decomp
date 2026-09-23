# First byte search at `0x00452730`

The 190-byte routine at `0x00452730` now has an ordinary C++ body named
`FirstByteSearch_00452730`. A linker alias preserves the external C symbol
`_asm_FUN_00452730_00452730` for existing assembly callers. The raw address
binding remains in the matching layout. The source models the observable operation:
scan forward and return the first matching byte, or null if the string ends
first. A search for byte zero returns the address of the terminator.

## Ghidra and caller evidence

Live Ghidra identifies a leaf function with two stack arguments, no callees,
10 caller functions, and 18 call references. The entry reads the low byte of
the second argument at `[ESP+8]` and the string pointer at `[ESP+4]`; the
result pointer is returned in EAX. For example, the caller at `0x00419F73`
pushes the byte value and text pointer, calls this entry, then adds eight to
ESP and checks EAX. This confirms the two-argument cdecl contract and caller
stack cleanup.

The retail body aligns the input and scans dwords using the `7EFEFEFFh` /
`81010100h` zero-byte detection pattern, then checks individual bytes. The
C++ loop retains the first-match and terminator behavior without inline
assembly. The original routine's match-to-NUL path used the separate return
tail at `0x00452720`; that separately mapped region is left intact.

The exact generated code and byte-for-byte codegen equivalence have not been
verified. No build, probe, or test was run.
