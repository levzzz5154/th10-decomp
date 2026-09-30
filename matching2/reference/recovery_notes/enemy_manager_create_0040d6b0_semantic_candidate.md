# Enemy manager factory `0x0040D6B0` semantic candidate

The active `regions.json` still classifies this 95-byte span as assembly, and
`matching2/msvc/src/game/enemy_manager_create_retail_0040d6b0.cpp` still emits
the retail naked body. The readable factory model is kept in
`matching2/reference/semantic_candidates/enemy_manager_create_retail_0040d6b0.cpp`;
it is not integrated as recovered code.

## Observed behavior

Ghidra recognizes `0x0040D6B0..0x0040D70E` as
`uint *__stdcall FUN_0040d6b0(undefined4 param_1)`. The listing and decompile
show the following sequence:

1. Allocate `0x68` bytes with `operator new` at `0x00452493`.
2. If allocation succeeds, clear bit 0 at offset `+0x50`, zero `0x1A`
   dwords, set bit 1 in the word at `+0x00`, and publish the pointer in global
   `0x00477704`.
3. Call `0x0040D280` with the factory's script-name argument.
4. If initialization reports failure, call teardown `0x0040D530` and
   `free` at `0x004524A1` when an allocation exists, then return null.
   Otherwise return the allocated pointer (which is null if allocation failed).

The `+0x50` bit clear occurs before the full zero fill, so the zero fill
overwrites it. It is retained in the source model because it is an observed
store in the retail body. Field names remain limited to the two observed flag
words.

## Entry ABI and callers

The entry takes one 32-bit stack argument, returns the manager pointer in EAX,
and uses `ret 4`. Ghidra reports callers `FUN_0040A350` and `FUN_00417870`;
their calls are at `0x0040A377` and `0x00417B33`. Both push the argument and
consume the EAX result. This is an ordinary `__stdcall` entry shape.

## Exactness blocker D3802

The prior standalone readable candidate emitted the full 95-byte extent but
differed in nine register-identity bytes. Retail keeps the new manager in EBX
for `0x0040D280`, then passes it in EAX to `0x0040D530`. The standalone model
homes it in ESI and passes teardown's pointer in ECX. Those private callee
conventions are not expressible through the ordinary C++ declarations used by
the model.

The earlier scratch LTCG attempt produced a 95-byte factory body, but the
`0x0040D530` callee still had four argument-copy mismatches, so that cluster
was not registered. A later wave-9 note records the factory itself as exact in
a wider merged native-LTCG link while `0x0040D530` retained those four
mismatches; that historical probe did not land a reusable layout. See
[`recovery_enemy_manager_create_0040d6b0_wave5.md`](recovery_enemy_manager_create_0040d6b0_wave5.md)
and [`0040d530_wave9.md`](0040d530_wave9.md) for the experiment history.

The reference candidate now uses the same 0x68-byte manager type as the timer
sweep candidate. Ghidra shows that the factory passes this object to
`FUN_0040d280`, which installs the callback records at `+0x08/+0x0C`, the frame
timer at `+0x40`, and the parser at `+0x54`; the sweep and teardown use the
enemy-list fields beginning at `+0x58`. The shared candidate layout and its
offset checks are in
[`enemy_timer_sweep_0040d750.hpp`](../semantic_candidates/enemy_timer_sweep_0040d750.hpp).

The shared candidate source was compiled with Clang's 32-bit MSVC target to
check syntax and layout. This is not an MSVC byte-match test. A current native
probe remains unavailable because Wine cannot bind its local socket in the
sandbox.
