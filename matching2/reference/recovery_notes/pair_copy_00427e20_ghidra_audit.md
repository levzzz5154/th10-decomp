# Pair-copy helper at `0x00427E20`: Ghidra ABI audit

## Boundary and references

The live `th10.exe` Ghidra database (`x86:LE:32`, image base `0x00400000`)
does not define a function at `0x00427E20`: function lookup and decompilation
return no containing function, and the data-region view calls the entry
`DAT_00427e20` with zero xrefs. This means there is no Ghidra caller list or
callee list to rely on; direct xref queries to both `0x00427E20` and
`0x00427E36` also return none.

Byte disassembly nevertheless gives a coherent, byte-aligned body from
`0x00427E20` through the plain `ret` at `0x00427E36` (23 bytes). It is
preceded by `INT3` padding at `0x00427E13..0x00427E1F` and followed by
`INT3` padding at `0x00427E37..0x00427E3F`; the neighboring code begins at
`0x00427E40`. This agrees with the owned 23-byte `asm` region and subsequent
padding region in `matching2/msvc/regions.json`. The Ghidra database's lack of
a function object is a coverage gap, not evidence that these bytes are data.

## Register contract and behavior

The entry consumes three pointers already present in registers:

| Register | Observed role |
| --- | --- |
| EAX | Pointer to the result pair |
| EDX | Pointer to the source pair |
| ECX | Pointer to a second destination pair |

It saves ESI, reads the first source dword into ESI, writes it to
`[ECX]`, reads the second source dword and writes it to `[ECX+4]`, then writes
both source dwords to `[EAX]` and `[EAX+4]`. It restores ESI and returns with
plain `ret`; it has no calls or stack arguments. EAX remains the result
pointer. ECX and EDX are changed by the body. The load/store order is visible
in the instruction sequence and should be retained if pointer aliasing is
relevant.

## Recovery decision and symbol

Keep [`FUN_00427e20_00427e20.cpp`](../../msvc/src/unidentified/FUN_00427e20_00427e20.cpp)
as naked assembly. The register tuple (result in EAX, source in EDX,
destination in ECX) is not an ordinary MSVC x86 C++ calling convention, and
no Ghidra caller is available to ground a different source-level contract.
The source records a prior H3101 native-LTCG attempt: a typed free
`Pair27*(result, source, destination)` candidate used stack arguments and
matched 0 of 23 bytes. That probe was not rerun for this audit.

The required region symbol remains `_asm_FUN_00427e20_00427e20`, as listed in
`regions.json`. Keep the definition's existing `extern "C" __cdecl` name so
MSVC emits that x86 symbol; no new typed or semantic alias is supported by
the current reference evidence.

No build, probe, or test was run for this audit.
