# Process exit wrapper at `0x00453B60`

The source at `matching2/msvc/src/unidentified/FUN_00453b60_00453b60.cpp`
models the known behavior as an ordinary C++ call to
`asm_crtExitProcess_00457547(0xff)`. The callee is declared non-returning, so
the wrapper is marked non-returning as well. This is a behavioral model; no
byte-identity claim is made.

## Ghidra evidence

In `th10.exe`, Ghidra's byte disassembly of `0x00453B60` through
`0x00453B69` contains exactly two instructions: `push 0xff` at `0x00453B60`
and `call 0x00457547` at `0x00453B65`. These account for the manifest's
10-byte region. The target is identified as `___crtExitProcess` with
`void __cdecl ___crtExitProcess(int param_1)`. Its decompilation passes that
argument to `CorExitProcess` when available and then to `ExitProcess`; Ghidra
marks the latter path non-returning. The cross-reference list to
`0x00457547` includes the call at `0x00453B65`.

Ghidra has no function object at `0x00453B60`, and reports no xrefs to that
entry. It therefore provides no recovered entry signature or callers. The
current source's no-argument `__cdecl` declaration is retained to preserve its
existing symbol, but that incoming ABI is not independently confirmed. The
call's outgoing cdecl argument and non-returning behavior are supported by
the callee signature and decompilation.

## Manifest and limits

The 10-byte manifest row is now marked `semantic`, with its prior ASM record
preserved in `previous_record`. Ghidra confirms the outgoing call and status
value but not a function object or incoming references at this entry, so the
no-argument cdecl boundary remains an informed model. No build, probe, or test
was run.
