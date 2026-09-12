# Player/front runtime pair: `0x00413BC0` and `0x004250B0`

## Result

Neither region passed the independent exact extent-and-byte gate. The live
assembly in `src/game/player_front_runtime.cpp` was therefore retained, no
proposal was emitted, and `regions.json` was not edited. The temporary paired
semantic candidate, native-LTCG context, and layout were removed after the
failed probes.

| Region | Live manifest extent | Legacy extent | Best native candidate | First mismatch |
| --- | ---: | ---: | ---: | --- |
| `0x00413BC0` | 1965 | 1968 | 1728 | `0x00413BC0`: candidate `53`, retail `51` |
| `0x004250B0` | 1656 | 1664 | 1312 | `0x004250B0`: candidate `A1`, retail `83` |

The focused maintained-source baseline is exact for both live extents.

## Retail ABI and caller evidence

Both functions receive their owning runtime in `EDI` and return with a plain
`RET`; `0x004250B0` additionally returns zero in `EAX`.

- The front initializer is called at `0x0040A678`, `0x004182A4`, and
  `0x004184A4`. Each caller loads the front singleton from `0x0047770C`
  directly into `EDI` before the call.
- The movement update is called at `0x00425A8C` by `0x00425730`, which executes
  `mov edi,ebp` immediately before the call.
- Public-member and TU-local native-LTCG candidates both retained a source ABI
  that fetched the object from the stack. The initializer began
  `53 8B 5C 24 08 ...` instead of retail `51 8B 47 08 ...`; the movement body
  began `A1 5C 4E 47 00 83 EC 1C ...` instead of retail
  `83 EC 18 A0 5C 4E 47 00 ...`. Linkage/noinline changes did not alter those
  entries.

The animation calls are a coupled register cluster, not ordinary external
calls. In particular, the create/configure/register sequence carries the
configured object and manager across `0x00449870` into `0x004489D0` using
live `ECX`/`EAX`/`EDX` values. `0x0043E710` consumes object, bank, and script
index in `EAX`, `ECX`, and `EBX`. The position helpers at `0x004492F0` and
`0x00449350` similarly consume manager/position state in registers while only
the handle is on the stack. Ordinary declarations changed every call shape
and prevented an exact caller body even when the surrounding behavior was
represented.

## Recovered front-initializer behavior

`0x00413BC0` marks the update/draw tasks at `+0x08/+0x0C` for removal; creates
and registers the two persistent front animation objects at `+0x9E58/+0x9E5C`;
loads 42 animation slots in the retail interleaved order; sets/clears nine life
icon flags from `0x00474C70`; and configures the three power digits from the
word at `0x00474C48`.

It then creates the mutually exclusive `0/1` or `0x71` front animations,
conditionally registers `0x4F` and difficulty-relative `0x66`, always
registers difficulty-relative `0x6B`, assigns the generated IDs at
`+0x9E50/+0x9E54`, and moves the corresponding task trees to layer 3 before
clearing `+0x9E90`. The repeated manager-list insertion is inlined in retail.

Ghidra identifies four aligned body ranges totaling 1940 instruction bytes;
the live 1965-byte manifest region also owns the internal compiler alignment
bytes. The legacy 1968-byte boundary includes three additional trailing bytes
and is not the live promotion extent.

## Recovered movement behavior

`0x004250B0` decodes the eight direction combinations from `0x00474E5C`,
applies the playable/slow gate, maintains the slow-transition age, creates or
releases the slow animation, selects separate cardinal/diagonal normal/slow
speed fields, and changes the facing animation when the signed primary axis
crosses zero.

It scales both integer movement components by the frame multiplier at
`0x00476F78` through `__ftol2`, updates and clamps the two positions to
`[-18400,18400]` and `[3200,43200]`, writes float positions using
`0x00470B00`, positions the slow animation, updates the 32-entry trail/ring,
and updates four orbit records. Each orbit can invoke the dynamic callback at
record `+0x90`, interpolates toward its normal/slow target after the age gate,
and translates two animation handles.

Ghidra identifies two aligned instruction ranges totaling 1588 bytes. The
live 1656-byte region additionally owns the compiler switch table at
`0x00425708..0x00425727` and intervening alignment/padding; the legacy
1664-byte boundary includes eight trailing bytes. A future exact semantic
layout must account for this in-text jump table as part of the same promoted
extent.

## Next dependency

Retry only as a bounded multi-source native-LTCG cluster containing a
caller-faithful slice of `0x00425730` and one front caller plus semantic forms
of the directly coupled animation helpers (`0x00449870`, `0x004489D0`,
`0x0043E710`, `0x0043E5A0`, `0x004492F0`, and `0x00449350`). That cluster must
prove the `EDI` incoming-object convention and preserve the helper register
edges before source-level tuning. The `0x004250B0` layout also needs a verified
carve/placement for the compiler-generated switch table inside the live
manifest extent.
