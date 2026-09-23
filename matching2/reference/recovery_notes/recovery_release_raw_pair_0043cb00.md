# `Recovery_ReleaseRawPair` at `0x0043CB00`

The readable source for the 127-byte body is in
`matching2/msvc/src/game/recovery_leaves.cpp`. The function has a one-pointer
`__stdcall` ABI: Ghidra reads the pair from `[ESP+4]` and the retail body ends
with `RET 4`. The manifest now binds the semantic row to
`_asm_Recovery_ReleaseRawPair_0043cb00@4` and keeps the former assembly record
in `previous_record`. Byte-exact status is unverified.

The pair contains two scheduler entries at offsets `+8` and `+0xC`. For each
non-null entry, the function enters the critical section at `0x00492274`,
increments the global byte at `0x0049231C`, removes the entry from the scheduler,
leaves the critical section, and decrements the byte. The scheduler pointer is
loaded from `0x00491BE4` for each entry. Ghidra identifies
`FUN_00449F60` as the removal helper, called with the entry in ECX and scheduler
in EDX; the C++ source casts that existing symbol to a matching `__fastcall`
function pointer. The enter/leave callbacks are indirect function pointers at
`0x004660B0` and `0x004660B4`.

Ghidra reports `FUN_0043C870` as a caller. That source already calls this entry
through a one-pointer stdcall callback type. No null check is added for the pair
itself; its known caller gates the object. The function names and concrete types
of the two pair fields remain inferred from their scheduler-removal use. No
build, probe, or test was run for this edit.
