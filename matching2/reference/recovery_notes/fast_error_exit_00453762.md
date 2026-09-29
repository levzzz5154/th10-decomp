# `_fast_error_exit` at `0x00453762`

The production entry remains a 33-byte assembly region at
`matching2/msvc/src/unidentified/fast_error_exit_00453762.cpp`. A readable
ordinary C++ candidate lives under `matching2/reference/semantic_candidates/`.
Ghidra identifies it as `void __cdecl fast_error_exit(int errorCode)`. It calls
`FF_MSGBANNER` only when `data_0047720c` equals 1, reports the supplied error
code through `0x00458EFD`, then terminates with exit code `0xFF` through
`0x00457547`.

The CRT entry at `0x004537DC` calls this routine with error codes `0x1C` and
`0x10`; both sites push one stack argument, matching the recovered cdecl
boundary. Ghidra's disassembly places the conditional banner call at
`0x0045376B`, the error-report call at `0x00453774`, and the process-exit call
at `0x0045377E`. The model preserves that order and treats the process-exit
helper as non-returning.

The candidate has not been promoted. MSVC 13.10 emits a separate stack load,
push, and caller cleanup around `__NMSG_WRITE`, whereas retail directly pushes
`[ESP+4]` and proceeds to the non-returning process-exit call. The live
`__NMSG_WRITE` body ends in plain `RET`, not `RET 4`; declaring it `__stdcall`
to suppress the cleanup would falsely describe its real ABI. Clang's measured
candidate also changes the prologue and global access. Byte identity and the
callee's actual cdecl contract take precedence over a merely behavioral model.
