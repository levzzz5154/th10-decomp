# ECL entity integer resolver wrapper: live Ghidra ABI audit

The 2026-09-23 audit below established the live register ABI; the later
ordinary C++ conversion was checked with a focused byte-for-byte probe.

## Region and call evidence

The manifest entry is now `semantic_ECL_ResolveIntFromEntity_00412a00`,
source `src/script/ecl_resolve_int_from_entity_00412a00.cpp`, at `0x00412A00`,
size 16. Ghidra identifies the body as `0x00412A00` through `0x00412A0F`
inclusive (the next entry is `0x00412A10`). Its retail instructions are:

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

The pinned Clang i386 COFF profile represents both public live-ins using
`regparm(3)`: the entity arrives in EAX, the unused middle input in EDX,
and the selector in ECX. The resolver declaration uses `regparm(2)` plus
`stdcall`: the derived frame stays in EAX, its interpreter goes to EDX,
and the selector is pushed as its single callee-cleaned stack argument.
The compiled wrapper exactly matches all 16 retail bytes, including the
call relocation and unchanged integer return in EAX. The COFF decorator
`_asm_ECL_ResolveIntOperand_0044fdb0@12` is bound to the resolver's existing
`0x0044FDB0` address; the machine-level stack cleanup remains `RET 4`.

The wrapper retains its `_asm_ECL_ResolveIntFromEntity_00412a00` symbol for
existing assembly callers. Its previous assembly manifest row remains as
`previous_record`; no source-level assembly is needed at this entry.
