# `EnemySlot_CreateAndInitRetail` at `0x0041FD00`

Audit performed 2026-09-23 against the live Ghidra program `th10.exe`. The
existing naked source in `msvc/src/game/enemy_slot_create_and_init_retail_0041fd00.cpp`
should remain in place. Its body is short, but two callees require private
register arguments that ordinary MSVC x86 C++ cannot declare.

## Entry, caller, and result

Ghidra reports `void * __stdcall FUN_0041fd00(void)` at `0x0041FD00..0x0041FD44`.
There is one code caller: `FUN_004218d0`, at `0x00421935`. The call has no stack
arguments. The caller tests the returned EAX and stores it at `[EDI+0x768]`.
The factory preserves EBX and ESI and returns its state pointer in EAX. With no
stack arguments, the observed `ret` has the same stack effect under cdecl and
stdcall; the current source and symbol binding use cdecl.

The caller itself keeps its manager pointer in EDI. It does not pass that
pointer to this factory. Its EAX live-in belongs to `FUN_004218d0`'s own entry
ABI, not to `FUN_0041fd00`.

## Exact factory flow

1. Allocate `0x3F0` bytes using `operator_new` (`0x00452493`) with one cdecl
   stack argument. Test the returned pointer.
2. If non-null, put the allocation in ESI and call `FUN_0041f850`. That callee
   reads the state pointer from ESI and returns the same pointer in EAX. Save
   that result in EBX. If allocation returned null, set EBX to null.
3. Call `FUN_0041fac0` unconditionally with the state pointer in EBX, including
   the allocation-null path. Its current body returns zero in EAX.
4. If the worker helper returns nonzero and EBX is non-null, call
   `FUN_0041fb50` with EBX as one stdcall stack argument, then free EBX through
   cdecl `_free` (`0x004524A1`). Return null. Otherwise return EBX in EAX.

The nonzero-result cleanup branch remains part of the retail body even though
the presently disassembled `FUN_0041fac0` ends with `xor eax,eax; ret`.

## Direct and transitive dependencies

| Address | Ghidra function / current role | ABI evidence and relevant behavior |
| --- | --- | --- |
| `0x00452493` | `operator_new` | cdecl, one 32-bit size on stack; the size is `0x3F0`. |
| `0x0041F850` | state-table initializer | No stack argument. The receiver arrives privately in ESI; it writes through ESI, publishes that pointer to `DAT_00477820`, and returns ESI in EAX. It has no other code caller in Ghidra. |
| `0x0041FAC0` | worker starter | No stack argument. The worker/state receiver arrives privately in EBX; it writes fields at EBX offsets `+8`, `+0xC`, and `+0x10` onward, registers two callbacks, starts the thread, and returns zero in EAX. It has no other code caller in Ghidra. Its transitive calls include callback creation at `0x00449ED0` twice, registration at `0x00449AE0` and `0x00449B70`, the private-ESI stop helper at `0x0044C150`, and `__beginthreadex` at `0x00453683`. The registration helpers use ESI for the callback, EDI for its priority, and one stack argument for the scheduler manager; their epilogues use `ret 4`. `FUN_0044C150` uses ESI for the worker thread subobject. The thread start address is `FUN_0041F990` (`0x0041F990`). |
| `0x0041FB50` | state/thread cleanup | One pointer is passed on the stack and the function ends in `ret 4`, so this is a one-argument stdcall. It tears down state and thread globals before the factory frees the allocation. Ghidra also finds calls from global-state teardown (`FUN_004203F0`) and two deleting-destructor entries (`0x0041FD51`, `0x0041FD75`). |
| `0x004524A1` | `_free` | cdecl, one pointer on the stack; the factory caller removes four stack bytes after the call. |

The private ESI and EBX conventions are the decisive barrier: MSVC x86 C++ has
no standard function convention that passes a formal parameter in either
register. Declaring either helper as cdecl, stdcall, thiscall, or fastcall would
change the call setup (fastcall/thiscall use ECX/EDX). A typed caller would need
an adapter that itself establishes ESI/EBX, which is outside this function's
ordinary typed-C++ body. The previous candidate recorded in the source also
emitted 63 bytes against the 69-byte retail extent; that historical probe was
not rerun for this audit.

## Symbol and alias integration

The existing source defines the C-linkage symbol
`asm_EnemySlot_CreateAndInitRetail_0041fd00`. `include/asm_symbols.hpp` declares
it as `extern "C" void __cdecl` and defines
`VA_asm_EnemySlot_CreateAndInitRetail_0041fd00` as `0x0041fd00`. The region
binding is `_asm_EnemySlot_CreateAndInitRetail_0041fd00` at `0x0041FD00`, and
`game_mode_switch.cpp` calls that alias directly.

The live Ghidra result gives the routine a pointer return, unlike the current
void alias declaration. If a later conversion keeps the current binding, define
the semantic body under the same C-linkage identifier with return type `void *`
and `__cdecl`; its COFF symbol remains
`_asm_EnemySlot_CreateAndInitRetail_0041fd00`, so the VA macro, region binding,
and caller name need not change. The declaration in `asm_symbols.hpp` would need
the matching return correction so the caller's EAX result is typed as a pointer.
The observed no-argument stack behavior is compatible with that cdecl alias.

The other direct aliases already present in `asm_symbols.hpp` are
`asm_operator_new_00452493` / `VA_asm_operator_new_00452493`,
`asm_Recovery_InitializeStateTable_0041f850` /
`VA_asm_Recovery_InitializeStateTable_0041f850`,
`asm_Recovery_StartWorker_0041fac0` / `VA_asm_Recovery_StartWorker_0041fac0`,
`asm_FUN_0041fb50_0041fb50` / `VA_asm_FUN_0041fb50_0041fb50`, and
`asm_free_004524a1` / `VA_asm_free_004524a1`. The initializer and worker alias
prototypes omit their actual ESI and EBX inputs; the cleanup alias is declared
as no-argument cdecl although the code requires one stdcall pointer (`ret 4`).
A typed C++ caller must describe the observed conventions rather than assume
those legacy declarations encode them.

No source body, header, caller, region binding, or build metadata was changed
for this audit. No build, probe, or test was run.
