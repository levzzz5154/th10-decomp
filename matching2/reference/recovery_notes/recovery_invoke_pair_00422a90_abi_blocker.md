# 0x00422A90 — callback adapter remains assembly

2026-09-23. Keep `src/game/recovery_invoke_pair_00422a90.cpp` unchanged. The
10-byte region is a register-convention adapter: it receives its context in
ECX, installs that context in ESI for the worker at `0x004223F0`, and forwards
the worker's result. An ordinary C++ call cannot express the worker's ESI
input while preserving the wrapper's exact ABI.

## Boundary and evidence

Read-only Ghidra inspection of `th10.exe` identifies `InvokePairCallback` at
`0x00422A90`, with body `0x00422A90..0x00422A99` (10 bytes). The live manifest
also records a 10-byte `asm` region owned by `0x00422A90`. Its full listing is:

```text
00422a90  push esi
00422a91  mov  esi,ecx
00422a93  call 004223f0
00422a98  pop  esi
00422a99  ret
```

The only xref to the entry is a data/immediate reference at `0x00422152` in
`FUN_00422150`; Ghidra reports no direct call callers. At that site the caller
pushes `0x00422A90` and calls `FUN_00449ED0`, which allocates a callback record.
It stores the returned record under `[EBX+8]` and writes the owner context
(`EBX`) at `[record+0x20]`. This is a registered callback entry, not a helper
that receives a second function-pointer argument.

## ABI and behavior

The entry pointer arrives in ECX. The adapter saves the caller's ESI, copies
ECX to ESI, and calls `FUN_004223F0`; that worker reads and updates the context
through ESI. The adapter restores the caller's ESI and returns without
changing EAX or EDX after the call. The worker's Ghidra decompilation has an
`undefined8` return and its exit paths form `CONCAT44(value, 1)`, so the
callback result is the pair in EDX:EAX, with EAX set to 1 and EDX carrying the
state-dependent high word. The wrapper forwards that pair intact.

The register transfer is part of the contract: `FUN_004223F0` is retained as
a raw `void __cdecl` assembly symbol and consumes the object in ESI, not ECX.
A normal C++ call would pass an argument according to a declared calling
convention; it cannot state “pass this value in ESI” or guarantee the exact
save/call/restore sequence while preserving the opaque worker's EDX:EAX
result. Reproducing this adapter therefore needs naked/inline assembly or a
change to the worker ABI, neither of which is an ordinary C++ conversion.

The older `legacy_semantic` sketch `Recovery_InvokePair(void*, function_ptr)`
does not describe the live call contract: no function-pointer parameter is
present at this entry. No build, probe, or tests were run for this review.
