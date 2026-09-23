# `0x0041C1C0` ScoreExtendedObject destructor: semantic model

2026-09-23. `ScoreExtendedObject_DestroyRetail` is now expressed as ordinary
C++ in `matching2/msvc/src/game/score.cpp`, and the 195-byte region is
classified as semantic in `regions.json` with the earlier assembly record
preserved. This records the understood behavior and does not claim byte
identity.

## Established behavior

The entry receives a manager/object pointer. It removes the task pointers at
`+0x08` and `+0x0C` when present. Each removal calls the critical-section
callbacks stored at `0x004660B0` and `0x004660B4` with the first section in
`g_thread_synchronization` (`0x00492274`), increments the scheduler lock-depth
byte at `0x0049231C`, calls `Scheduler_Remove(task, *0x00491BE4)`, then leaves
the section and decrements the depth byte.

It then walks the resource list whose head is at `+0x18`. Each node saves its
iteration next pointer from `+0x08`, calls the node's vtable slot at `+0x10`
on the node, unlinks through the node's current previous pointer at `+0x04`
and next pointer, and frees the node through `0x004524A1`. Iteration follows
the next pointer saved before the virtual call. Finally, it clears the global
manager pointer at `0x0047781C`.

## ABI and callers

The retail entry takes one 32-bit stack pointer, preserves the callee-saved
registers, and ends in `RET 4`. The source therefore uses a `void __stdcall`
signature with one object pointer. `object_factories.cpp` declares and calls
the entry as `__stdcall` when score-display task registration fails. The
assembly caller in `manager_teardown.cpp` pushes the global manager pointer
immediately before calling it and relies on the callee to remove that stack
argument.

`asm_symbols.hpp` now declares the one-pointer stdcall interface, matching the
promoted `_asm_ScoreExtendedObject_DestroyRetail_0041c1c0@4` symbol. The source
wrappers at `0x0041C2F0` and `0x0041C310` use the same cleanup convention; the
raw assembly caller at `0x00417EA4` continues to push the pointer and rely on
`RET 4`. The older undecorated name remains mapped to the address for existing
assembly references.

## Exactness limit

The current D2601 record is `closest_byte_count=195`,
`first_diff=unmeasured`, `residual_class=abi`. The 195-byte extent is known,
but this semantic candidate has not been compiled or compared. The remaining
exactness question is the compiler's callback and virtual-call schedule and
its EBX/EBP/ESI/EDI allocation around the scheduler and list operations. A
native-LTCG comparison with the scheduler remove/free bindings and the owning
layout is still needed before claiming byte identity.
