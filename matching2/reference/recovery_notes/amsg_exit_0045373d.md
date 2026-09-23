# `__amsg_exit` at `0x0045373D`

The entry now has an ordinary C++ model in
`matching2/msvc/src/unidentified/amsg_exit_0045373d.cpp`. Ghidra identifies
`void __cdecl __amsg_exit(int errorCode)`. It calls `FF_MSGBANNER` when
`data_0047720c` equals 1, reports the supplied CRT message code through
`0x00458EFD`, then calls the `__exit` function pointer at `0x00473070` with
`0xFF`.

Ghidra lists callers in `__lock`, `__getptd`, `entry`, `copy_environ`,
`__endthread`, and `__endthreadex`, among others. Their cdecl call sites pass
the message code on the stack. Ghidra identifies the terminal call as
`PTR___exit_00473070`; the source declares that slot as a pointer to a
one-argument cdecl function and models the path as non-returning.

The manifest now classifies the 34-byte entry as semantic and retains its
previous assembly row. The source contains no inline assembly. Its emitted
bytes and placement have not been checked with a build or probe, so this is a
behavioral model rather than a byte-identity claim.
