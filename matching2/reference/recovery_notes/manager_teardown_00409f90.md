# Manager teardown recovery: `0x00409F90`

## Status

The live target remains unpromoted. Production
`matching2/msvc/src/game/fun_00409f90_00409f90.cpp` is still the original
naked assembly, and its manifest row remains
`_asm_FUN_00409f90_00409f90`, address `0x00409F90`, size `118`, kind `asm`.
The post-promotion target pass was not exact, so no target semantic source,
target cluster layout, or target cluster registration was retained.

The directly coupled helper at `0x004493E0` is now promoted. Its verified live
source is
`matching2/msvc/src/render/animation_manager_mark_resource_for_removal_004493e0.cpp`;
the registered native-LTCG layout and compiler context are
`layout/ltcg/animation_manager_mark_resource_for_removal_004493e0.json` and
`layout/ltcg/animation_manager_mark_resource_for_removal_004493e0_context.cpp`.
The helper manifest row is semantic with its decorated member symbol, and its
focused production probe reproduced `92/92` bytes exactly. The helper's
assembly-to-semantic transition is recorded by its `previous_record` in
`regions.json`.

The archived semantic registry is not an authoritative live extent here. It
maps `FUN_00409f90` to `src/game/manager_teardown.cpp` with size `2480`
(`0x00409F90..0x0040A93F`, exclusive end `0x0040A940`). That span crosses
separately owned live regions beginning at `0x0040A010`, `0x0040A040`,
`0x0040A130`, `0x0040A1A0`, `0x0040A340`, `0x0040A450`, and `0x0040A940`.
Taking that extent would violate the requested ownership boundary. The live
118-byte partition (`0x00409F90..0x0040A005`) was therefore the only target
extent eligible for this attempt.

## Recovered behavior

The archived semantic draft, IDA/Ghidra output, callers, and exact retail
disassembly agree on the behavior of the live target partition:

1. Load the animation manager pointer from `0x00491C10`. Walk its four
   retired-resource slots at `manager + 0x3AD090`, calling the directly coupled
   resource-marking routine once per slot.
2. Walk the manager list at `manager_argument + 0x58`. Each node contains the
   object at offset `0` and the next node at offset `4`; for each non-null
   object, invoke vtable slot `+0x14` with reason `1`.
3. Clear manager fields `+0x64` and `+0x10`. If the scheduler-node pointers at
   `+8` and `+0xC` are non-null, clear bit `0x2` in each node's flags at `+4`.
   The function is one-argument stdcall and returns with `ret 4`.

The promoted helper marks each animation object whose resource pointer at
object offset `+0x308` equals the retired resource, setting bit
`0x04000000` in its flags at `+0x35C`. It performs the two manager list walks
at manager offsets `0x72DAD4` and `0x72DADC` and preserves the retail internal
ABI: manager in `EAX`, resource in `EDX`, plain `ret`.

## Exact helper proof

The focused production probe was:

```text
PYTHONPATH=. python3 matching2/tools/matching/probe.py \
  --source src/render/animation_manager_mark_resource_for_removal_004493e0.cpp \
  --project matching2/msvc --oracle matching2/build/oracle/th10.exe \
  --output matching2/build/probe-4493e0-promoted-1 --json
```

Result: `EXACT`. The helper body at `0x004493E0` is `92/92` bytes with SHA-256
`a9a42d5ac94f0eaabfbcf277f043db7d1c183a3da6d472ec14488ca3a1960ad1`, matching
the retail body. Its production cluster also retained the declared helper
extent and context address `0x00449480`.

## One bounded post-promotion target pass

The target source was reconstructed in a fresh task-local copy with the
promoted helper as an additional native-LTCG source. The pass used the
semantic manager/global/list/release behavior above and a C++ member-call
dependency declaration. It was compiled once only. The first validator link
reported the task-local manifest's omitted absolute binding for
`_data_00491c10`; the already compiled objects were then linked diagnostically
with that known retail data binding, without another compiler pass. The shared
validator and Python tooling were not changed.

The resulting native MAP proved the requested focused extents and origins:

```text
target  .text$01manager_teardown  0x00409F90  0x76 (118)  cluster.obj
helper  .text$20helper            0x004493E0  0x5c (92)   source_000.obj
context .text$30context           0x00449500  0x3c (60)   cluster.obj
```

The helper was still exact. The target body SHA-256 was
`e91da7ddc5058a220d4f35e56348721003a78b21d64b1dce3c23829ce704577a`; retail
was `782b365517d27258ab001548805f6dfbf8e6fc2795a0c2784681812d306be0f3`.
Exactly these 16 target bytes differed:

```text
0x00409F91  0x00409F92  0x00409F93  0x00409F94
0x00409F95  0x00409F96  0x00409F97  0x00409F99
0x00409F9A  0x00409F9B  0x00409F9C  0x00409F9D
0x00409F9F  0x00409FA4  0x00409FB3  0x00409FBC
```

Retail begins:

```text
push ebx; mov ebx,[0x00491C10]; push ebp; mov ebp,[esp+0x0C];
push esi; push edi; lea esi,[ebx+0x3AD090]; mov edi,4
```

The bounded native body begins:

```text
push ebx; push ebp; mov ebp,[esp+0x0C]; push esi; push edi;
mov edi,[0x00491C10]; lea esi,[edi+0x3AD090]; mov ebx,4
```

The remaining loop, tail, release call, field clears, and `ret 4` match. This
is a compiler register-allocation/prologue mismatch, not a semantic or extent
failure, so the target stays assembly.

The normal cluster validator also rejects the native MAP's zero-length
`.text` contribution on line 8 (`invalid MAP contribution on line 8`). This is
existing shared-tool behavior; no shared tooling was edited. The production
target's focused assembly probe remains an independent `EXACT` at `118/118`.

## Next dependency checkpoint

The helper dependency is resolved and promoted. The remaining target blocker
is a compiler-visible native-LTCG declaration/context that simultaneously
preserves the external stdcall stack argument in `EBP`, assigns the global
animation manager load to `EBX`, and assigns the four-slot loop count to
`EDI`. Do not promote `0x00409F90` until a fresh bounded proof eliminates all
16 listed byte differences while retaining the live 118-byte ownership
boundary. Any future use of the archived `2480`-byte semantic file still
requires a new partition/ownership audit before changing `regions.json`.

All failed target-pass artifacts were removed after this note update. The
promoted helper files and its manifest registration remain; unrelated
concurrent source/layout changes and shared Python tooling were preserved.
