# `__errcode` semantic model at `0x0045E8B4`

The 45-byte body at `0x0045E8B4..0x0045E8E0` now has a plain C++ model in `src/unidentified/errcode_0045e8b4.cpp`. The manifest classifies it as semantic under the unchanged `_asm_errcode_0045e8b4` C symbol and preserves the prior assembly record in `previous_record`. This is a behavior model, with no byte-match claim.

Ghidra identifies it as the Visual Studio 2003 CRT `__errcode` helper. It checks the low byte of its input in this priority order and returns the corresponding code:

1. Bit `0x20` → `5`.
2. Bit `0x08` → `1`.
3. Bit `0x04` → `2`.
4. Bit `0x01` → `3`.
5. Otherwise return `(flags & 0x02) << 1`, which is either `4` or `0`.

The order matters if several status bits are set. The model deliberately uses an `unsigned char` parameter because the retail body reads only `AL` from the first stack argument.

## ABI and references

The ABI is `int __cdecl __errcode(unsigned char status_flags)`. The argument occupies the first x86 stack slot at `[ESP+4]`; only its low byte is consulted. The result is in EAX, the function uses plain `RET` so the caller cleans up, and there are no private register inputs or direct callees.

Ghidra reports callers `FUN_0045EA31` and `FUN_0045EAED`, with call sites at `0x0045EA88` and `0x0045EB54` respectively.

The behavior and calling convention are clear from the decompilation and instruction stream. C++ code generation has not been checked, so the edit does not claim retail-byte equivalence or manifest promotion readiness.
