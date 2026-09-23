# `__commit` at `0x004614A9`

The primary 157-byte region is now represented by ordinary C++ in
`src/unidentified/commit_004614a9.cpp`. The adjacent 20-byte region at
`0x00461551` remains its original assembly entry and SEH/error tail.

Live Ghidra analysis identifies the entry as `int __cdecl(uint fd)`. Its caller
at `0x0045FC71` pushes the descriptor, removes the argument after the call, and
uses the result in EAX. The function validates the descriptor against the CRT
handle count, checks the per-entry open flag at offset `+4`, locks the
descriptor, obtains its OS handle, and calls `FlushFileBuffers`. When that call
fails, it stores `GetLastError()` through `_doserrno`; invalid or closed
descriptors and flush failures set errno to 9 and return `-1`.

The retail body registers an SEH frame so the descriptor lock is released if
control unwinds after locking. The C++ body models that cleanup with
`__try/__finally` and calls the existing typed unlock helper. The separate
`0x00461551` tail is retained for its own error/SEH entry. The normal C++ body
and exception path have not been checked against compiler output; no build,
probe, or test was run.
