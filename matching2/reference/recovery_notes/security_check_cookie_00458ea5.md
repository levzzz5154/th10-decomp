# `__security_check_cookie` at `0x00458EA5`

Live Ghidra analysis identifies `void __fastcall __security_check_cookie(uintptr_t)` with its sole argument in ECX. The function compares that value against the four-byte global security cookie at `0x00473660`; equality returns immediately, while inequality transfers to `report_failure` at `0x00458E74`. Ghidra reports 100 xrefs to this helper.

The source now models the check as ordinary C++ using a 32-bit `unsigned int` fastcall parameter and global. The shared declaration for `data_00473660` was corrected from a byte to a dword because the function and its many inline-assembly callers read or write it as a dword. `asm_report_failure_00458e74` is marked non-returning to express the failure path's process termination.

The semantic manifest symbol is `@asm_security_check_cookie_00458ea5@4`, matching the x86 MSVC fastcall decoration. The prior naked record is retained under `previous_record`. No build or code-generation probe was run, so emitted instruction bytes and exact region size remain unverified.
