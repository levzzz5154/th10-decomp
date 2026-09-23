# `_memset` semantic model at `0x0045BED0`

The 96-byte body at `0x0045BED0..0x0045BF2F` now has a plain C++ model in `src/unidentified/memset_0045bed0.cpp`. The manifest classifies it as semantic under the unchanged `_asm_memset_0045bed0` C symbol and preserves the prior assembly record in `previous_record`. This records ordinary C++ semantics without claiming a retail-byte match.

Ghidra identifies the function as the Visual Studio CRT `_memset`. For a zero length it returns the destination without accessing memory. Otherwise it stores the low byte of `value` into each of `size` consecutive bytes and returns the original destination pointer. The retail implementation aligns the destination, writes repeated dwords, and handles remaining bytes; those are implementation details with the same byte-fill result.

## ABI and references

The ABI is `void *__cdecl _memset(void *destination, int value, size_t size)`: the three stack arguments are at entry `[ESP+4]`, `[ESP+8]`, and `[ESP+0xC]`; EAX returns the original destination; `RET` leaves cleanup to the caller. There are no private register inputs or direct callees. The machine body saves and restores EDI while using `rep stosd` for the aligned bulk fill.

Ghidra reports callers `___lc_strtolc`, `__cftof2`, `FUN_0045EE1D`, `FUN_004601E8`, `FUN_00457A7C`, `___crtGetStringTypeA`, and `FUN_0045794D`. The eight direct call references are at `0x004579D3`, `0x0045A328`, `0x0045F10F`, `0x0045F145`, `0x004602BB`, `0x00458260`, `0x004559C4`, and `0x0045DE81`.

The byte-fill behavior and ABI are supported by Ghidra's CRT match and disassembly. No code-generation probe or build was run, so this model does not establish byte equivalence or promotion readiness. The loop could be optimized differently from the retail alignment and dword-fill sequence.
