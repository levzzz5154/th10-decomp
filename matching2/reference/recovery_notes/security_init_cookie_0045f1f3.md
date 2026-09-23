# `___security_init_cookie` at `0x0045F1F3`

This 102-byte CRT routine now has a typed C++ implementation in
`src/unidentified/security_init_cookie_0045f1f3.cpp`. The existing C-linkage
entry name and address remain stable for the CRT initializer table.

## Ghidra evidence

Live Ghidra identifies `___security_init_cookie` as a standard
`void __cdecl(void)` function spanning `0x0045F1F3..0x0045F258`, followed by
the next region at `0x0045F259`. It has one computed call reference from
`__cinit` at `0x0045761B` and a data reference from the initializer table at
`0x00473004`. The entry takes no arguments and has no hidden register inputs.

The body leaves an existing cookie unchanged unless it is zero or
`0xBB40E64E`. In those cases it calls, in order, `GetSystemTimeAsFileTime`,
`GetCurrentProcessId`, `GetCurrentThreadId`, `GetTickCount`, and
`QueryPerformanceCounter`. It XORs the two FILETIME words, all three scalar
results, and the two performance-counter words, then stores that value at
`0x00473660`. If the result is zero, it stores `0xBB40E64E` instead. Ghidra's
listing shows these calls through the fixed import slots declared in
`asm_symbols.hpp`; the C++ uses typed views of those slots.

The retail routine ignores `QueryPerformanceCounter`'s Boolean result and
reads both output words. The C++ implementation zero-initializes that output
before the call so a failed counter query has defined behavior; in that rare
failure case it uses zero counter words where retail would consume whatever
was already on its stack. No other return value from the imports affects the
control flow.

No build, probe, or test was run, so the C++ code has not been compared with
the retail bytes.
