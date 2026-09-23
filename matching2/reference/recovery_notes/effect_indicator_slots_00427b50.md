# Effect indicator slot allocator: 0x00427B50

## Ghidra evidence

Live analysis of `th10.exe` identifies `FUN_00427b50` at `0x00427B50`, ending
at `0x00427C04` (181 bytes). Its decompiler signature is
`undefined4* __fastcall FUN_00427b50(undefined4, int, undefined4*, undefined4,
undefined4, int, undefined4)`. The register/stack report places the first
argument in ECX, the manager in EDX, then five four-byte arguments on the stack.
The first argument is not read. The body ends in `ret 0x14`, and both return
paths copy the selected slot address, or the one-past-pool address, to EAX.

Ghidra reports exactly two direct references:

| Call instruction | Caller | Observed call setup |
| --- | --- | --- |
| `0x00425CCE` | `FUN_00425730` | EDX is the manager; the stack carries a position pointer, raw words `0x42000000` and `0x41800000`, frame count `30`, and mode `150`. |
| `0x00428863` | `FUN_00428630` | EDX is the manager; the stack carries a position pointer, raw words `0x42000000` and `0x3FB33333`, frame count `13`, and a computed mode. |

The allocator has no callees. Its decompilation and disassembly agree on these
operations:

1. Start at manager offset `+0x350C`; inspect 32 records at `0x6C`-byte
   intervals for a clear bit 0 at record offset `+0x68`.
2. On the first free record, zero all `0x6C` bytes, set record flags to `3`,
   then redundantly zero `0x2C` bytes beginning at `+0x18`.
3. Copy the three position words and the two caller-supplied payload words.
   Callers pass float bit patterns for these payloads, so the source retains
   them as raw 32-bit values.
4. Initialize the embedded timer at `+0x44` when its flags at `+0x54` are
   clear: target `0xFFF0BDC1`, current and previous zero, speed pointer
   `0x00476F78`, then set timer flag bit 0. Store the requested frame count,
   count minus one, and its float conversion at offsets `+0x48`, `+0x44`, and
   `+0x4C`.
5. Store mode, zero counter, limit `999999`, and phase `4` at `+0x58`, `+0x5C`,
   `+0x60`, and `+0x64`, then return the record. If all 32 are occupied, return
   the address immediately after the pool.

## Source model and ABI

`src/game/effect_indicator_slots.cpp` now spells out the complete observed
behavior as ordinary C++. The 32-bit manager/record view and compile-time
layout checks express the `+0x350C` pool offset and `0x6C` record stride. The
function uses C linkage and `__fastcall` with a deliberately unused ECX
parameter, the manager in EDX, five stack arguments, and an `EAX` pointer
result. This matches both direct callers and the callee-cleanup size reported
by Ghidra; no private EAX/ESI/EDI live-in is needed.

The semantic manifest row now binds
`@EffectIndicatorPool_AllocateRetail_00427b50@28` (seven four-byte formal
parameters, including the ECX and EDX values) and preserves the legacy
`_asm_EffectIndicatorPool_AllocateRetail_00427b50` address binding used by the
two existing inline-assembly call instructions. Its `previous_record` retains
the prior assembly row.

## Byte-equivalence limits

This is a semantic C++ recovery, not a measured byte match. No build, probe, or
test was run. In particular, the compiler may remove or reshape the redundant
second clear, choose a different loop/register schedule, or emit the timer's
integer-to-float conversion differently from retail's `FILD`/`FSTP` sequence.
The model preserves the observed field writes, initialization condition,
return values, and external entry contract, but exact 181-byte equivalence
remains unverified.
