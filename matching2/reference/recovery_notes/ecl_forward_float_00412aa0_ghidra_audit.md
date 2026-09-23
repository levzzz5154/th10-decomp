# `Ecl_ForwardFloat` audit at `0x00412AA0`

## Decision

Keep the entry as retail assembly. The ordinary C++ signature suggested by the decompiler does not describe its live ABI: the entry consumes the VM pointer from `EAX`, translates two stack arguments into a second nonstandard register/stack call, and leaves the resolver's x87 result in `ST(0)` for the caller. A source-level `__stdcall` or `__thiscall` function cannot express that input register contract. Replacing the entry with an adapter would require inline/naked assembly or changing its callers, neither of which is an ordinary C++ conversion of this entry.

## Ghidra boundary and references

The live Ghidra program is `th10.exe` (x86, image base `0x00400000`). Ghidra names the function `ForwardEclFloat`, starts it at `0x00412AA0`, and gives its body the inclusive range `0x00412AA0`–`0x00412AB9` (26 bytes). Its decompiler reports `undefined __stdcall ForwardEclFloat(byte, float)` and a `void`-like call-through, but that signature omits the observed `EAX` input and does not account for the x87 value consumed by callers.

All 13 direct call references come from `FUN_0040e770` at `0x0040E770`, whose assembly is in `src/script/ecl_vm.cpp`:

`0x0040E82B`, `0x0040E84B`, `0x0040E869`, `0x0040E886`, `0x0040E9B7`, `0x0040E9CC`, `0x0040EA19`, `0x0040EA34`, `0x0040EA4F`, `0x0040EB4F`, `0x0040EB6F`, `0x0040EC67`, and `0x0040EC7C`.

The caller loads the VM pointer into `EAX`, pushes an operand dword and then a selector dword, and calls this entry. For example, after `0x0040E82B`, the caller executes `fadd` using `ST(0)`; other call sites store the returned x87 value with `fstp` or continue floating-point arithmetic.

## Observed ABI and behavior

At entry, the relevant state is:

- `EAX` is the ECL VM pointer.
- `[ESP+4]` is the selector dword (the callers push selectors such as 1, 2, and 3).
- `[ESP+8]` is the operand's 32-bit float payload.

The 26-byte body is:

```asm
00412aa0  mov  ecx,[esp+8]       ; save operand bits
00412aa4  mov  eax,[eax+14d8h]   ; VM -> operand context
00412aaa  mov  eax,[eax+4]      ; context -> resolver receiver
00412aad  push ecx              ; resolver's stack float argument
00412aae  mov  ecx,[esp+8]       ; selector is now at +8
00412ab2  call 0044ff80         ; EAX receiver, CL selector, float on stack
00412ab7  ret  8                ; remove the entry's two stack arguments
```

`0x0044FF80` (`ResolveEclFloatValue`) uses `EAX` as its receiver, `CL` as its selector, and the pushed dword as its float input; that callee removes its one stack argument with `ret 4` and returns a floating value in x87 `ST(0)`. `Ecl_ForwardFloat` does not modify the x87 stack after the call, so the resolver's result is passed through to the caller. Thus the wrapper's `ret 8` cleanup and its x87 pass-through are both part of the observable contract.

## Legacy names to preserve

`regions.json` assigns this 26-byte region to `src/game/ecl_forward_float_00412aa0.cpp`, under `asm_Ecl_ForwardFloat_00412aa0` / `_asm_Ecl_ForwardFloat_00412aa0`. `include/asm_symbols.hpp` declares the C-linkage entry and its `VA_asm_Ecl_ForwardFloat_00412aa0` address macro. The manifest also maps both decorated legacy names, `_asm_Ecl_ForwardFloat_00412aa0@8` and `@asm_Ecl_ForwardFloat_00412aa0@8`, to `0x00412AA0`. Keep these aliases at the same address if the implementation or declaration is revisited; the decorated aliases do not make the `EAX` receiver convention representable in C++.

The current tree also has an identical non-static definition in `src/game/recovery_leaves.cpp` at lines 224–240, while the manifest assigns this entry to the dedicated source above. This audit leaves that out-of-scope file untouched; whether it participates in the same link was not checked.
