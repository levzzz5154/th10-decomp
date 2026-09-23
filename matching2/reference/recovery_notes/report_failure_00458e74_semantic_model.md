# `report_failure` semantic model at `0x00458E74`

The 48-byte region now has an ordinary C++ body and is marked `semantic` in
the manifest. The previous ASM record and linker symbol remain preserved.

## Ghidra evidence

The function calls `FUN_0045F259` with stack arguments `1` and `0`, then calls
the imported `ExitProcess` entry at `0x0046614C` with exit code `3`. The helper
reads its two inputs from `[EBP+8]` and `[EBP+0xC]`; the report-failure
callsite pushes `0` followed by `1`, matching `(mode, flags) == (1, 0)` under
the cdecl right-to-left argument order. The call site is a direct caller of
`security_check_cookie` at `0x00458EA5`.

## Recovered behavior

The semantic body preserves the helper call and process exit order. It uses a
typed stdcall function-pointer view of the ExitProcess IAT slot, then retains
a nonreturning sink if the imported routine unexpectedly returns.

## Limits

This models the observed behavior without reproducing the original SEH frame
bytes. No build, probe, or test was run.
