# ASCII manager factory candidate — 0x0043C8B0

`src/game/ascii_manager_create_retail_0043c8b0.cpp` now records a readable
semantic candidate for the 82-byte factory. Ghidra marks the function from
`0x0043C8B0` through `0x0043C901`; its call xrefs show nine direct callers.
The entry uses five ordinary stack arguments, returns the allocated pointer in
EAX, and ends with `ret 0x14`.

## Observed behavior

The factory allocates `0x44` bytes and returns null if allocation fails. It
clears all `0x44` bytes, sets bit 1 in the leading flags word, invokes
`0x0043C970` with the five input values, then returns the manager pointer.
Before the full zero fill, retail clears bit zero at offset `0x40`; the fill
overwrites that store, so the semantic source leaves out this dead write.

The typed call in the source represents the five stack values accepted by
`0x0043C970`. It does not express the full retail call context. At the call,
the new manager is live in ESI, and the caller's EBX value selects a secondary
registration path inside `0x0043C970`. Neither register is a declared factory
parameter. Preserving those values through ordinary C++ register allocation is
unresolved, so this source is semantic and is not asserted to reproduce the
retail bytes.

## Exactness history

[`allocator_binding_new_and_delete.md`](allocator_binding_new_and_delete.md)
records the earlier 77-byte emission against the 82-byte retail body. That
attempt lost the dead pre-zero field clear and changed the public cleanup from
`ret 0x14` to `ret 0x0C` after two parameters moved to registers. Keep those
findings as historical measurement; this candidate does not claim a byte
match. The broader caller-context note
[`stage_update_00418190.md`](stage_update_00418190.md) also identifies EBX as
live at this factory's call boundary.
