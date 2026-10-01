# `Ecl_ForwardFloat` audit at `0x00412AA0`

Current 2026-09-30: the dedicated source now contains exact C++ without inline
assembly. A native-LTCG batch compiles this real caller with the complete value
resolver at `0x0044FF80`. A named operand-slot local and integer selector yield
all 26 retail bytes; the callee remains exact at 171 bytes. The decisions below
predate that recovery. See [the source and byte evidence](ecl_float_values_and_forward_2026-09-30.md).

## Decision

Keep the entry as retail assembly. The decompiler's `__stdcall` signature
omits its EAX VM input, its two stack inputs, the resolver's ECX selector,
and the x87 result in `ST(0)`. Clang `regparm` can express those inputs, but
the measured ordinary C++ candidate does not reproduce the exact retail
register schedule and 26-byte body; see the probe comparison below.

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

`regions.json` assigns this 26-byte region to
`src/game/ecl_forward_float_00412aa0.cpp`. The manifest's undecorated and
`@8` call aliases still resolve to `0x00412AA0`. The redundant, unselected
assembly clone in `src/game/recovery_leaves.cpp` was removed; the dedicated
source still owns the exact assembly region.

The original audit only considered Microsoft calling conventions. A pinned
Clang i386 `regparm(2)`/`stdcall` source can represent the EAX VM input,
two stack arguments, and `RET 8`, but does not byte-match: forwarding the
operand as raw float bits emits 25 bytes and loads the selector first, whereas
retail first loads the operand into ECX. A float-typed parameter also adds
unwanted x87 load/store instructions. Keep the dedicated region as assembly
until a compiler-generated 26-byte version matches the complete sequence.
