# `FUN_0042c7c0` private register ABI blocker

Audited read-only against the connected Ghidra program `th10.exe` on
2026-09-23. The assembly owner remains
`matching2/msvc/src/unidentified/FUN_0042c7c0_0042c7c0.cpp`.

## Boundary and references

Ghidra has no function object at `0x0042C7C0`; function lookup, decompilation,
and function-caller lookup therefore return no function. Address-level
disassembly shows the 25-byte body from `0x0042C7C0` through the final byte of
`RET 4` at `0x0042C7D8`. The preceding Ghidra function `FUN_0042c770` ends at
`0x0042C7B0`; the intervening bytes `0x0042C7B1..0x0042C7BF` are `INT3`. The
target is followed by seven `INT3` bytes at `0x0042C7D9..0x0042C7DF`, then
separate code begins at `0x0042C7E0`. The current source manifest likewise
assigns this entry 25 bytes and the following seven bytes to padding.

No caller is identified in the current Ghidra database. `get_xrefs_to` reports
no references to the entry, `get_xrefs_from` reports no references from it,
and a program-wide instruction search of 124,648 decoded instructions found
no operand referring to `0x0042C7C0`. A byte-pattern search for the absolute
little-endian address `c0 c7 42 00` also found no match. This rules out a
currently visible direct call or absolute pointer reference; it does not
identify any possible computed or runtime-only invocation.

## Behavior and ABI

The body saves ESI and EDI, reads one stack dword into EDI from the original
`[ESP+4]`, and computes `ESI = EAX + ECX*4 + 0x2C4`. It calls
`FUN_004497d0` without changing EBX. That helper uses ESI as the address of a
slot, EBX as the script ID, and EDI as the address where it writes its result.
It resolves the slot through `AnimationManager_Find`, scans the returned child
list for an object whose signed 16-bit field at `+0x38A` equals EBX, then
writes the matching object pointer or null to `[EDI]`. On return, the wrapper
sets EAX to EDI, restores EDI and ESI, and executes `RET 4`, cleaning the one
stack dword.

The observed entry therefore consumes a table/base in EAX, a slot index in
ECX, a script ID in EBX, and a stack output pointer. It also returns that
output pointer in EAX and has callee cleanup for the stack word. Ghidra does
not provide a formal signature for this entry. The ABI facts above come from
the entry disassembly and the disassembly/decompilation of its direct callee
at `0x004497D0`.

## Disposition

Keep the existing naked assembly. An ordinary MSVC x86 C++ function cannot
declare the required EAX and EBX inputs while also expressing this ECX input,
stack output pointer, EAX return, and `RET 4` cleanup. A `__fastcall` or
`__thiscall` spelling does not provide the required private EAX/EBX register
contract. Reproducing it as standard C++ would need an assembly entry/shim,
which would leave this exact entry as assembly.

No build, probe, or test was run for this audit.

## Integration symbols

| Role | Symbol / address |
| --- | --- |
| Source entry symbol | `asm_FUN_0042c7c0_0042c7c0` |
| Manifest COFF symbol | `_asm_FUN_0042c7c0_0042c7c0` |
| Manifest decorated address aliases | `_asm_FUN_0042c7c0_0042c7c0@4`, `@asm_FUN_0042c7c0_0042c7c0@4` -> `0x0042C7C0` |
| Direct callee symbol | `asm_AnimationManager_FindChildByScriptIndex_004497d0` at `0x004497D0` |
| Callee's nested manager lookup | `asm_AnimationManager_Find_004491c0` at `0x004491C0` |

The aliases above are read from `matching2/msvc/regions.json`; this audit did
not build the source or verify emitted linker symbols.
