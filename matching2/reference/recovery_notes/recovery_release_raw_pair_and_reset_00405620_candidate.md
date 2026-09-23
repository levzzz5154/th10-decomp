# 0x00405620 — readable raw-pair release candidate

The body in `matching2/msvc/src/game/player.cpp` now expresses the recovered
release/reset behavior as ordinary C++ with no inline assembly. Its source name
retains the existing `asm_` spelling so the established symbol can continue to
bind to the region; `regions.json` and shared aliases were left untouched.

## Recovered behavior and ABI

Ghidra's listing shows a pointer argument at `[ESP+4]` and ends with `RET 4`,
confirming a one-argument stdcall entry. The pair has two task-like pointers at
offsets `+8` and `+0xC`; the preceding eight bytes remain opaque. For each
non-null pointer, the function enters the critical section at `0x00492274`,
increments the byte depth counter at `0x0049231C`, calls the fastcall
`Scheduler_Remove(task, scheduler)`, leaves the critical section, and
decrements the counter. The scheduler pointer is read from `0x00491BE4` for each
pair member. Finally, it clears the dword at `0x004776EC`.

The implementation uses local typed function pointers for the two import slots
at `0x004660B0` and `0x004660B4`, the existing scheduler-removal symbol, and a
small local pair layout with conservative field names. A translation-unit-local
preprocessor rename hides only the stale cdecl/zero-argument declaration in
`asm_symbols.hpp`, allowing this definition to use the observed stdcall
pointer-argument signature without changing that shared header or its aliases.

## Exactness status

The current readable body has not been built or probed. Historical native-LTCG
candidate measurements remain relevant: one 137-byte candidate differed from
retail in exactly four bytes, all in the two `Scheduler_Remove` argument setup
pairs. Retail emits `mov ecx,esi; mov edx,edi` at `0x0040564E` and again at
`0x00405682`; the measured C++ candidate emitted `mov edx,edi; mov ecx,esi` at
each site. The earlier measurements found the rest of the function byte-exact,
including both import calls, depth updates, final global clear, and `ret 4`.
See `entity_player_helpers_00401de0_00405d00_00405620_004059f0.md` and
`recovery_release_raw_pair_and_reset_00405620_wave7.md` for the prior compiler
experiments. This note does not claim that the current source body was measured.


## ABI and manifest integration (2026-09-23)

The shared declaration and C++ helper prototypes now use the observed one-pointer `__stdcall` convention. The region binds `_asm_Recovery_ReleaseRawPairAndReset_00405620@4`; the prior cdecl row remains in `previous_record`, and the old alias remains in the symbol table. The known four-byte Scheduler_Remove argument-order mismatch is unchanged, so exact compiler output remains unverified.
