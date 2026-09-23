# `Path_DecodeXor` at `0x00417010`

## Decision

Keep [`path_decode_xor_00417010.cpp`](../../msvc/src/platform/path_decode_xor_00417010.cpp) as the retail naked assembly definition. The transform is straightforward to describe in C++, but its input arrives in EAX under a private register ABI. The five retail call sites call the entry directly after preparing EAX; an ordinary MSVC C++ function declaration cannot express an EAX parameter. Replacing only the callee with a typed function would break those call sites, while preserving them requires inline assembly or a broader caller migration.

## Live Ghidra evidence

Inspected the open `th10.exe` program (`x86:LE:32`, image base `0x00400000`). Ghidra reports `FUN_00417010` at `0x00417010`, body `0x00417010..0x00417038` (41 bytes), and the misleading inferred signature `undefined1 * __stdcall FUN_00417010(void)`. The body has 20 instructions, three basic blocks, no calls, and returns with a plain `ret` at `0x00417038`.

The entry immediately saves ESI and EDI, then copies EAX to EDI. Thus EAX is an input, despite Ghidra's zero-parameter signature. The complete direct-call xref list has five sites:

- `0x0040BE6A` and `0x0040BE8F` in `FUN_0040BD80`;
- `0x00415F43`, `0x00416006`, and `0x00416063` in `FUN_00415E90`.

The disassembly at `0x0040BE64..0x0040BE6A` loads `[EBP+0x54]`, adds four, then calls. At `0x0040BE8C..0x0040BE8F`, EAX already holds the selected record address and four is added before the call. Each of the three sites in `FUN_00415E90` loads `[EBP+0x5C]`, adds four, and calls. No stack argument is pushed for this helper. The decompiler omits these EAX inputs because its prototype is wrong. Ghidra reports no callees.

The only data xrefs to the destination `0x00497D40` are from this function: the byte store at `0x00417024` and address materializations at `0x00417018` and `0x00417032`. No other function xrefs to that address appeared in the live database. The actual destination capacity is not established by those xrefs.

## Exact byte-string behavior

The routine reads one byte from the EAX input pointer per iteration and XORs it with an 8-bit key. It writes the result to the fixed output address `0x00497D40`, then advances both pointers. The key starts at `0x77`; its increment starts at `7`. After every byte, including the terminating byte, the key is increased by the current increment and the increment is increased by `0x10`. These are byte-register operations, so both values wrap modulo 256. The loop ends when the decoded byte is zero, writes that NUL to the output, and returns `0x00497D40` in EAX.

This is not a loop that stops on a zero input byte: termination occurs when the input byte equals the current key. There is no explicit length, null check, or output-capacity check. It has no path-separator handling or other path-specific branch; its observed operation is the byte transform above. The `LEA ECX,[ECX]` at `0x0041701D` preserves ECX and has no data effect. ESI and EDI are restored before return; ECX and EDX are used as loop state and are clobbered.

## Integration and codegen status

Keep the current asm manifest binding: `_asm_Path_DecodeXor_00417010` at `0x00417010`, size 41. `asm_symbols.hpp` declares `extern "C" void __cdecl asm_Path_DecodeXor_00417010();`; the declaration names the raw assembly call target and is not the semantic transform's C++ signature. Raw calls remain in `event_script_runtime.cpp` (two sites) and `fun_00415e90_00415e90.cpp` (three sites). No new alias or typed signature should be installed while those sites retain the EAX contract.

The source's existing D3307 record reports a best ordinary-C++ candidate of 21/41 matching bytes, first differing at `0x00417012`, across five native MSVC 13.10 context variants. That historical result was not rerun during this audit. No build, probe, or test was run for this pass.
