# `GameProgress_UnlockAllStages` at `0x0042C8C0`

## Live Ghidra evidence

The open `th10.exe` program identifies the function at `0x0042C8C0` as
`FUN_0042c8c0`. Its decompiler pseudocode has no formal parameter and names an
implicit `in_EAX` value. The live function signature is reported as
`undefined __stdcall FUN_0042c8c0(void)`, so the signature alone misses the
register input visible in the body and its caller.

The body writes `0x01010101` to four consecutive dwords at offsets `+0x1D882`
through `+0x1D88E`. It then visits six records separated by `0x437C`; in each
record it performs 24 byte stores of `1`, at offsets `+0x4E9`, `+0x4F1`, …,
`+0x5A1`. The Ghidra listing saves and restores ESI and EDI, has no calls, and
places a seven-byte `LEA ESP,[ESP]` alignment NOP after a short jump. The body
spans `0x0042C8C0..0x0042C91C` (93 bytes including that NOP).

Ghidra reports one caller: `FUN_00431ee0`, at the call instruction
`0x00432451`. The instruction immediately before the call is
`0x0043244C: MOV EAX,dword ptr [0x0047783C]`. The caller does not push a
parameter or place a receiver in ECX. The current source for that caller is the
naked assembly body `asm_FUN_00431ee0_00431ee0` in
`matching2/msvc/src/game/replay_large_runtime.cpp`.

## Disposition

Keep the current naked body. The operation is straightforward to describe in
C++, but an ordinary free-function parameter would arrive on the stack and an
ordinary member receiver would arrive in ECX. Neither represents the live
EAX-only call boundary. Native LTCG can select private register conventions in
a compiler context, but the retained synthetic candidate still differs in 25
bytes, and the actual caller is naked assembly rather than a typed C++ call.
A C++ helper behind an assembly shim could describe the stores, but would not
replace this exact body at its current entry.

An existing synthetic native-LTCG candidate is retained under
`matching2/build/waves/throughput-parent/unlock`. Its layout records a
93-byte candidate with an EAX argument, while
`matching2/build/waves/throughput-parent/candidates.json` records 25 differing
bytes. That experiment does not establish an exact ordinary-C++ replacement
for the real naked caller. No build, probe, or test was run for this audit.

## Name aliases

| Role | Name |
| --- | --- |
| Semantic/canonical name | `GameProgress_UnlockAllStages` |
| Raw Ghidra name | `FUN_0042c8c0` |
| Historical decorated alias | `?GameProgress_UnlockAllStages@@` |
| Current exact-body symbol | `asm_GameProgress_UnlockAllStages_0042c8c0` |
| Current COFF symbol | `_asm_GameProgress_UnlockAllStages_0042c8c0` |
| Interior assembly label | `asm_GameProgress_UnlockAllStages_part_0042c900` |
