# Effect manager cleanup at `0x0042B570`

## Current disposition

Keep `src/game/effect_manager_destroy.cpp` as the retail assembly overlay for
now. The source comment records the last readable standalone attempt at 81
bytes against this function's 232-byte retail extent, with the remaining gap
attributed to the SEH frame/handler, the scheduler-removal call ABI, and the
cleanup member layout. A caller-inclusive schema2 link was also attempted but
did not retain the decorated entry symbol. No new exact-output experiment was
run in this review.

## Ghidra behavior and boundaries

Live `th10.exe` analysis identifies `FUN_0042b570` from `0x0042B570` through
`0x0042B657`; the final `ret 4` ends at `0x0042B658`, so the body occupies 232
bytes. Its entry takes one pointer from the stack and callee-pops that pointer.
The four direct call references are at `0x0040A2DC`, `0x00417ED4`,
`0x0042B691`, and `0x0042B6B1`. The last is the cleanup call in the scalar
deleting-destructor sequence at `0x0042B6B0`.

The decompilation and disassembly show this order:

1. Install the function's SEH registration record, whose handler address is
   `0x0046523B`, and initialize its state field.
2. Read the task pointer at manager offset `+0x08`. If non-null, enter the
   critical section at `0x00492274` through the function pointer at
   `0x004660B0`, increment byte `0x0049231C`, call
   `FUN_00449F60(task, *(void**)0x00491BE4)`, leave through
   `0x004660B4`, and decrement the byte.
3. Repeat for the manager task pointer at `+0x0C`, reloading the scheduler
   global from `0x00491BE4`.
4. Clear global pointer `0x00477840` unconditionally. If manager offset
   `+0x370` is non-null, pass it to the free entry at `0x00452422` and then
   store zero at `+0x370`. The null path also stores zero.
5. Restore the previous SEH chain head and return with `ret 4`.

`FUN_00449F60` is decompiled as `__fastcall(task, scheduler)`, matching the
caller's ECX/EDX setup. The wrapper imports at `0x004660B0` and `0x004660B4`
are called as one-argument stdcall functions. These conventions and the
function's two cleanup exits must be preserved by any replacement. The
disassembly is available from Ghidra's `disassemble_function(0x0042B570)`;
the direct references come from `get_function_xrefs(0x0042B570)`.

## Next useful evidence

A replacement is not supported by the current record. Revisit after a
caller-inclusive LTCG layout can retain a correctly decorated one-argument
`__stdcall` entry and preserve the scheduler's `__fastcall` call plus the SEH
cleanup shape. Then compare the whole 232-byte contribution before removing
this overlay or changing its manifest classification.
