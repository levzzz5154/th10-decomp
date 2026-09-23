# Process launch helper at `0x00436570`

The live source now contains a readable C++ candidate for this 201-byte
function. The current `regions.json` entry remains `kind: asm` with the old
`_asm_Platform_LaunchProcess_00436570` symbol; that mapping has not been
changed in this pass. The candidate is named
`Platform_LaunchProcess_00436570` in C linkage, so its expected 32-bit MSVC
fastcall symbol for integration is `@Platform_LaunchProcess_00436570@16`.

## Behavior

The function fills a `STARTUPINFOA` record with `cb = 0x44`, `dwX`, `dwY`,
`dwXSize`, and `dwYSize` set to `0x80000000`, `dwXCountChars = 80`,
`dwYCountChars = 25`, and `wShowWindow = 10`; the other fields are zero. It
calls `CreateProcessA(application_name, command_line, NULL, NULL, FALSE,
0x20, NULL, NULL, &startup_info, &process_info)`.

- If `CreateProcessA` fails, it returns `-1`.
- If creation succeeds and `wait_for_exit` is zero, it returns `0`.
- Otherwise it initializes the exit code to `STILL_ACTIVE` (`0x103`) and
  repeatedly calls `GetExitCodeProcess` until the code changes, then returns
  that code. The API result is ignored and the loop has no sleep or yield.

The body does not call `CloseHandle` for either returned process handle. It
only reads `process_info.hProcess` while polling; ownership and cleanup outside
this body are unknown.

## ABI and references

Ghidra's live prototype is `int __fastcall FUN_00436570(void *ignored,
char *command_line, const char *application_name, int wait_for_exit)`. The
retail code confirms the storage directly: `ECX` is never read, `EDX` is pushed
as the mutable command line, `[ESP+4]` at entry is the application name, and
`[ESP+8]` is the wait flag. The body returns with `ret 8`, cleaning those two
stack arguments. Thus the private-looking register inputs are covered by an
ordinary x86 `__fastcall` declaration; there is no additional hidden register
argument.

`analyze_function_complete` reported no direct callers and no incoming xrefs
for this address. Its only direct callees are the imported APIs
`CreateProcessA` and `GetExitCodeProcess` (retail IAT slots `0x004660E0` and
`0x004660E4`). Absence of direct references does not rule out an indirect or
external entry path.

## Exactness status

This is a semantic replacement candidate, not an exact-output claim. No build
or byte probe was run. The 201-byte retail extent, API-call argument setup,
stack-local layout, and `ret 8` must still be checked against the MSVC 13.10
output before changing the manifest. The available legacy semantic overlay
supports the behavior, but it used a plain C signature and does not establish
the register/stack ABI or exact code generation.
