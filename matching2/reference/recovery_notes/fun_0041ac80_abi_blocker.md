# `FUN_0041ac80` at `0x0041AC80` — keep the naked body

Date: 2026-09-23

## Decision

Keep `matching2/msvc/src/unidentified/FUN_0041ac80_0041ac80.cpp` as a naked
assembly body. The body writes a two-DWORD result through the incoming EAX
pointer, reads two values from the stack, and removes eight argument bytes
with `RET 8`. Ordinary MSVC x86 C++ signatures do not express this
EAX-result/stack-argument combination. No source body change was needed. No
build, probe, or test was run for this audit.

## Live Ghidra boundary and references

Live Ghidra project `th10`, program `th10.exe`, has no function registered at
`0x0041AC80`; `get_function_by_address` and decompilation therefore return
“No function found.” The disassembly nevertheless reads these complete
instructions at the candidate entry:

| Address | Bytes | Instruction |
| --- | --- | --- |
| `0x0041AC80` | `8B 4C 24 04` | `mov ecx, [esp+4]` |
| `0x0041AC84` | `8B 54 24 08` | `mov edx, [esp+8]` |
| `0x0041AC88` | `89 08` | `mov [eax], ecx` |
| `0x0041AC8A` | `89 50 04` | `mov [eax+4], edx` |
| `0x0041AC8D` | `C2 08 00` | `ret 8` |

The five instructions end exactly at `0x0041AC8F`. The bytes immediately
before the entry, `0x0041AC72..0x0041AC7F`, disassemble as `INT3`; immediately
after the body, `0x0041AC90` is a separate plain `RET`, `0x0041AC91..0x0041AC9F`
are `INT3`, and the next observed code begins at `0x0041ACA0`. Ghidra has no
function registered at these adjacent starts either, so these are instruction
and padding boundaries rather than recovered Ghidra function objects.

`get_xrefs_to` and bulk xref queries returned no references to the entry or
any instruction address in `0x0041AC80..0x0041AC8D`; `get_xrefs_from` returned
none. `get_function_callers` and `get_function_xrefs` cannot enumerate callers
because the target has no Ghidra function object. Thus this audit found no
registered direct callers or call references; it does not establish whether
some unregistered indirect/computed call exists.

## Entry ABI and blocker

On entry, EAX already holds the destination address. The first stack DWORD at
`[ESP+4]` is copied through ECX to result offset zero, and the second at
`[ESP+8]` is copied through EDX to result offset four. EAX is not overwritten,
so the same destination pointer is also the return value. `RET 8` removes the
two explicit stack arguments. The effective contract is therefore a
two-field result factory with a private EAX result pointer, two stack inputs,
and callee cleanup.

A readable function returning a two-DWORD UDT receives the compiler's hidden
result argument according to MSVC's UDT-return ABI; it cannot select EAX as
that hidden result pointer while retaining these two stack argument offsets
and `RET 8`. The pre-existing source audit records a readable factory attempt
that emitted 20 bytes and first diverged at `0x0041AC81`, after matching only
6 of 16 bytes. Readable constructor/member LTCG contexts used ECX/EDX for the
values and returned with plain `RET`, which also misses the retail contract.
An ordinary pointer-returning function would return a pointer supplied as an
ordinary declared argument, which would change the argument layout and
cleanup. The naked body remains the faithful representation of this entry.

## Symbol routing

Ghidra's current program database has no canonical function symbol for this
entry. The local raw source symbol is `asm_FUN_0041ac80_0041ac80`, linked as
`_asm_FUN_0041ac80_0041ac80` at `0x0041AC80`. Existing manifest aliases
`_asm_FUN_0041ac80_0041ac80@8` and `@asm_FUN_0041ac80_0041ac80@8` route to
the same address. No Ghidra rename or shared routing change was made.
