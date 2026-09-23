# Enemy manager factory `0x0040D6B0` semantic recovery

The source expresses the manager factory as ordinary C++ in
`matching2/msvc/src/game/enemy_manager_create_retail_0040d6b0.cpp`. The
95-byte span is now classified as semantic in `matching2/msvc/regions.json`,
with its earlier assembly record preserved. This is a behavior recovery; it
does not claim that the ordinary C++ reproduces the retail bytes.

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

The prior scratch LTCG attempt also produced a 95-byte factory body, but the
`0x0040D530` callee still had four argument-copy mismatches, so that cluster
was not landable. The recorded next lever is to promote `0x0040D530`, its
EAX-receiver callers, this factory, and `0x0040D280` together in a real-caller
LTCG cluster. See
[`recovery_enemy_manager_create_0040d6b0_wave5.md`](recovery_enemy_manager_create_0040d6b0_wave5.md)
for the earlier model and experiment details.

No build, probe, or tests were run for this source edit.
