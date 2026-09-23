# `_fast_error_exit` at `0x00453762`

The entry now has an ordinary C++ model in
`matching2/msvc/src/unidentified/fast_error_exit_00453762.cpp`. Ghidra
identifies it as `void __cdecl fast_error_exit(int errorCode)`. It calls
`FF_MSGBANNER` only when `data_0047720c` equals 1, reports the supplied error
code through `0x00458EFD`, then terminates with exit code `0xFF` through
`0x00457547`.

The CRT entry at `0x004537DC` calls this routine with error codes `0x1C` and
`0x10`; both sites push one stack argument, matching the recovered cdecl
boundary. Ghidra's disassembly places the conditional banner call at
`0x0045376B`, the error-report call at `0x00453774`, and the process-exit call
at `0x0045377E`. The model preserves that order and treats the process-exit
helper as non-returning.

The manifest now classifies the 33-byte entry as semantic and retains the
previous assembly row. The source contains no inline assembly. Its emitted
bytes and placement have not been checked with a build or probe, so this is a
behavioral model rather than a byte-identity claim.
