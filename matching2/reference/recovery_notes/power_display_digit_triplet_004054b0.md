# Power display digit triplet (`0x004054B0`)

## Current status

The maintained region is still the exact 79-byte naked body in
`matching2/msvc/src/platform/all_source_runtime.cpp`; its manifest row is
`kind: asm`. This note records the live function contract and the ABI blocker.
No build, probe, or test was run for this recovery pass.

## Live Ghidra evidence

In `th10.exe`, Ghidra reports `FUN_004054b0` at `0x004054B0`, with body
`0x004054B0..0x004054FE` (79 bytes). Its inferred signature is
`void __fastcall FUN_004054b0(undefined4 param_1, int param_2, int param_3)`;
the disassembly ends in `ret 4`.

The body overwrites ECX before using its incoming value. Its live inputs are:

| Input | Meaning |
| --- | --- |
| ESI | Owner object; all direct callers load `dword [0x0047770C]` into ESI. |
| EDX | First animation index before the helper adds 8. |
| `[entry ESP+4]` | Signed value split into quotient and remainder by 10. |

It makes three calls to `FUN_0043E5A0`, ignoring each return value:

1. `resource = *(ESI + 0x9EC8)`, target `ESI + 0x6A8C`, index `EDX + 8`.
2. The same resource, target `ESI + 0x71E4`, index `value / 10 + 8`.
3. The same resource, target `ESI + 0x7590`, index `value % 10 + 8`.

The division is signed `idiv 10`, so C++ recovery must retain truncation toward
zero and the matching signed remainder. The resource lookup occurs again for
each call. The helper does not check the resource or owner for null.

Ghidra confirms the callee at `0x0043E5A0` uses the unusual call shape
`ECX=resource`, `EAX=target object`, `EDX=record index`; it returns in EAX and
uses a plain `ret`. Its semantic implementation is maintained in
`src/game/animation_object_configure_from_resource_0043e5a0.cpp`; its exact
native-LTCG recovery constraints are recorded in
`animation_object_configure_0043e5a0_unlock.md`.

## Direct callers

Live xrefs identify six calls from three functions. Each site sets ESI from
`[0x0047770C]` and passes the remaining values in EDX plus one stack slot.

| Caller | Call sites | Owner load |
| --- | --- | --- |
| `FUN_0041afd0` (`0x0041AFD0`) | `0x0041B410`, `0x0041B66A` | `0x0041B3F1`, `0x0041B64B` |
| `FUN_00425730` (`0x00425730`) | `0x00425A10`, `0x00425AF7`, `0x00425C7F` | `0x004259F1`, `0x00425AD8`, `0x00425C60` |
| `InitializePlayer` (`0x00405860`) | `0x00405975` | `0x00405956` |

At each site the caller computes the decimal input, pushes it, then copies the
first display index into EDX. The register owner is not declared as a formal
parameter in the current caller interfaces.

## Why the maintained body remains assembly

The current declaration in `asm_symbols.hpp` and manifest symbol are a
zero-argument `extern "C" __cdecl` entry used by inline-assembly callers. A
typed `__fastcall` C++ definition could describe EDX and the one stack input,
but would use a different decorated symbol and cannot be substituted through
the current declaration alone. It would also need to recover the hidden owner
and make each `0x0043E5A0` call with its resource/object/index register shape.
Existing exact evidence for that callee depends on native-LTCG compilation;
the prior standalone stdcall candidates for this region emitted 82 and 84
bytes instead of 79.

This is a cluster blocker, not evidence that the behavior is irreducible. The
next meaningful recovery is to give all six callers typed interfaces, recover
this helper with the shared `0x0043E5A0` callee in a native-LTCG schema-2
cluster, then compare the resulting call contracts and bytes. Until then, the
current retail assembly preserves the live register and stack contract.

## Update 2026-10-01

Recovered as `PowerDisplayOwner_004054b0::SetPowerDigits` in
`msvc/src/game/power_display_set_digits_004054b0.cpp` (cluster
`layout/ltcg/power_display_set_digits_004054b0.json`), probe EXACT.
