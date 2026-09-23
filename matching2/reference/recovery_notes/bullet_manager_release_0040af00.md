# Bullet manager release at `0x0040AF00`

The readable C++ implementation is in `matching2/msvc/src/game/bullet.cpp`.
The live manifest classifies this 137-byte region as semantic and preserves
the original assembly record and shared address alias.

## Ghidra evidence

Ghidra identifies `0x0040AF00..0x0040AF88` as a 137-byte function and reports
`undefined __stdcall FUN_0040af00(int param_1)`. The prologue reads the single
pointer argument from `[ESP+4]`, and the function ends in `ret 4`, confirming a
one-argument callee-cleanup ABI. The manager state fields at `+0x08` and
`+0x0C` are each tested as pointers.

For each non-null field, the function calls the import slots at `0x004660B0`
and `0x004660B4` with the critical-section object at `0x00492274`, increments
and then decrements the byte at `0x0049231C`, and calls `0x00449F60` with the
field value in ECX and the current value at `0x00491BE4` in EDX. Ghidra
identifies `0x00449F60` as a two-argument `__fastcall` scheduler removal
routine. After both slots, the function clears the global at `0x004776FC`.

Ghidra lists callers at `0x0040AF90` and `0x00417C80`. The `0x0040AF90` caller
uses Release while unwinding a failed script load. At `0x00417FBC`, the caller
pushes the manager pointer, calls Release, then pushes that same pointer to
`free` it. The padded bytes begin at `0x0040AF89`, after this function body.

## Candidate and limits

The candidate uses `void __stdcall asm_BulletManager_Release_0040af00(...)` and
a small local state view. The two unestablished words are named `unknown_00`
and `unknown_04`; the pointers are named by their observed offsets and use.
Critical-section imports are called through their existing IAT slots, while
`Scheduler_Remove` is declared with its observed fastcall ABI.

`asm_symbols.hpp` has a stale no-argument cdecl declaration for this function.
`bullet.cpp` locally renames only that declaration while including the header,
then defines the observed stdcall symbol. No shared declaration or address
alias was changed.

No native build or byte probe was run, so emitted bytes and exactness remain
unverified. The candidate preserves the observed operation order at source
level, but compiler register allocation, global loads, and call scheduling may
still differ from retail.


## ABI and manifest integration (2026-09-23)

The shared declaration and C++ helper prototypes now use the observed one-pointer `__stdcall` convention. The region binds `_asm_BulletManager_Release_0040af00@4`; the old cdecl row remains in `previous_record` and the historical alias remains in the symbol table. Exact compiler output remains unverified.
