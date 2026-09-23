# `ungetc` semantic model at `0x0045E204`

The source expresses the 108-byte region `0x0045E204..0x0045E26F` as ordinary C++, and the manifest now registers it as a semantic source. The shared declaration records the observed two-argument `__cdecl` interface. This is not a byte-match claim.

Ghidra labels the function `FID_conflict:_ungetc`, with library matches for both `__ungetc_lk` and `_ungetc`. Its visible behavior is the CRT pushback operation:

- Reject `EOF` (`ch == -1`) and streams that do not have the accepted flag combination: bit 0 set, or the sign bit in the low flag byte set while bit 1 is clear.
- If `_base` is null, call `__getbuf` at `0x00459F39` with the stream pointer.
- When `_ptr == _base`, fail if `_cnt` is nonzero; otherwise advance once and then decrement `_ptr` to reserve the preceding byte.
- If flag `0x40` is set, accept only when the existing byte at `_ptr` equals the requested low byte. On mismatch, restore `_ptr` and fail. Otherwise write the low byte there.
- Increment `_cnt`, clear flag `0x10`, set flag `1`, and return `ch & 0xFF`. Failure returns `-1`.

The local `UngetcStream_0045e204` type models only the FILE prefix this function accesses. Its fields are `_ptr` at `+0x00`, `_cnt` at `+0x04`, `_base` at `+0x08`, and `_flag` at `+0x0C`; each is four bytes in the 32-bit target.

## ABI and references

The confirmed signature is `int __cdecl(int ch, FILE *stream)`. `ch` is at entry `[ESP+4]`, `stream` at `[ESP+8]`, EAX carries the result, and the function returns with plain `RET` so the caller removes the two arguments. There are no private register inputs. The body preserves EBX and ESI. Its `__getbuf` call is cdecl with one stack argument and caller cleanup.

Ghidra reports `FUN_00457A7C` as a caller at `0x00457B2C`, `0x00457FB1`, `0x0045804F`, `0x004583BB`, `0x0045842C`, `0x004585F7`, `0x00458715`, `0x00458815`, and `0x0045882D`. Two additional references are tail-forwarded from `0x00457A59` in the ownerless `0x00457A52` fragment and called from `0x0045E28F` in the ownerless `0x0045E270` SEH wrapper. The direct callee is `__getbuf` at `0x00459F39`.

## Remaining uncertainty

The four accessed fields and the operation are clear from Ghidra's decompilation and instruction stream. The name remains ambiguous because the library signature database reports both locked and unlocked CRT matches. The source assumes the 32-bit FILE prefix above. C++ code generation has not been checked, so this promotion records the semantic model without claiming that it reproduces the retail bytes.
