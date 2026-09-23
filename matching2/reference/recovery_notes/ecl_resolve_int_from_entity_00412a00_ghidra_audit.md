# ECL entity integer resolver wrapper: live Ghidra ABI audit

Audited the live Ghidra program `th10.exe` on 2026-09-23. This was a static
review only; no build, probe, or test was run.

## Region and call evidence

The manifest entry is `asm_ECL_ResolveIntFromEntity_00412a00`, source
`src/script/ecl_resolve_int_from_entity_00412a00.cpp`, at `0x00412A00`, size
16, kind `asm`. Ghidra identifies the function body as `0x00412A00` through
`0x00412A0F` inclusive (the next entry is `0x00412A10`). The body is:

```asm
00412A00  mov eax,[eax+0x14D8]
00412A06  mov edx,[eax+4]
00412A09  push ecx
00412A0A  call 0x0044FDB0
00412A0F  ret
```

There is one direct caller, `FUN_0040e770`, with 30 direct call sites:
`0x0041135F`, `0x00411370`, `0x004114AF`, `0x004114C3`, `0x0041151C`,
`0x0041152F`, `0x00411542`, `0x00411555`, `0x0041157F`, `0x004115C8`,
`0x00411651`, `0x004116D0`, `0x0041171C`, `0x00411768`, `0x004117B4`,
`0x00411893`, `0x00411A20`, `0x00411ACA`, `0x00411A5C`, `0x00411A93`,
`0x00411B05`, `0x00411B2A`, `0x00411B38`, `0x00411B88`, `0x00411BD5`,
`0x00411BFB`, `0x00411CB3`, `0x00411CCB`, `0x00411CE6`, and `0x00411CFA`.

Caller context confirms that EAX carries the entity pointer (commonly loaded
from EBX immediately before the call), while ECX carries the operand selector.
Selectors include zero and small indices such as 1 through 11. The caller
consumes the wrapper result from EAX/AX, including storing AX at
`0x00411364` and `0x00411375`, and storing full EAX at sites such as
`0x00411521` and `0x00411534`.

## Resolver bridge and disposition

The callee `ResolveEclIntOperand` at `0x0044FDB0` reads its selector from
`[ESP+4]`, uses the ECL frame in EDX, returns its integer in EAX, and ends
every return path with `RET 4`. The wrapper therefore obtains the entity's
ECL state through `[entity+0x14D8]`, obtains its frame/cursor through
`[state+4]`, pushes the ECX selector, and lets the callee consume that one
stack argument. The wrapper then returns with the result still in EAX.

Keep the current naked body. A faithful ordinary C++ prototype cannot express
both wrapper inputs: the entity arrives in EAX, and the selector arrives in
ECX. Under the supported 32-bit Microsoft C++ conventions, cdecl/stdcall pass
arguments on the stack, thiscall uses ECX for `this`, and fastcall uses ECX
then EDX; none accepts this EAX/ECX pair. The callee also requires the wrapper
to move the derived frame into EDX and push the selector for its callee-cleaned
stack ABI. Making those values ordinary C++ parameters would require changing
the caller ABI or retaining assembly to capture EAX, so the existing assembly
is the faithful representation at this boundary.

Keep the existing call alias `asm_ECL_ResolveIntFromEntity_00412a00`, declared
in `include/asm_symbols.hpp` and mapped to `0x00412A00` by the manifest. No new
alias is needed while the routine remains assembly.
