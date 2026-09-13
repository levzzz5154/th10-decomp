# Bullet motion through the sound-queue cluster

2026-09-13. Three complete motion routines are recovered as C++98:

| Address | Bytes | Behavior |
| --- | ---: | --- |
| `0x00407780` | 338 | Repeated fixed-angle turns with deceleration between speed resets |
| `0x00407A30` | 431 | Repeated player-aimed direction changes with deceleration |
| `0x00407BE0` | 446 | Reflection at enabled playfield edges, speed override, and bounce limit |

Net new recovery is 1,215 bytes. The existing 329-byte projectile callback and
123-byte sound queue remain exact in the same cluster.

The bullet methods need an ESI receiver, so `sound_queue.json` now uses a
schema-1 pointer-array context that reaches all three. Each additional real
source is separately `/GL` compiled into the same native `/LTCG` invocation.
`ProjectileDeceleration::Update` remains the sole extra root, retaining its
public ECX entry. Neither the bullet methods nor `SoundQueue::Queue` is rooted.
Only the five complete maintained contributions enter the executable; the
context and zero-filled layout gaps count as zero recovered bytes.

The turn-step source follows the proven projectile deceleration shape with
the bullet layout at `+0x3B4` through `+0x6E0`. It matched immediately once the
native context selected ESI. The aimed variant computes two double-precision
local coordinate differences, handles a coincident target explicitly, and
calls `atan2`; MSVC itself emits the retail `fpatan`. The existing standard
`Angle_NormalizeSum` and polar-vector entries remain external bindings.
The aimed timer addition retains the elapsed load before the scale load,
whereas the turn-step variant retains the opposite order. A local volatile
elapsed reference expresses that one access without changing timer reset
stores or the deceleration expression. Marking the entire elapsed field
volatile changed those other operations and was rejected.

The bounce candidate initially used `>=` ternaries for choosing the reflected
position. Instruction-aligned comparison exposed different x87 condition
masks: retail uses strict `<` tests followed by the complementary branch,
including its unordered-value behavior. Those explicit strict tests reproduce
the comparisons. This routine also passes the stored binary32 speed directly
to the polar helper through a nonvolatile reference view. Sending it through
an x87 load/store added three bytes. The final caller, its private sound edge,
and all four other cluster contributions pass without byte rewriting.

Focused proof:

```
python3 matching2/tools/matching/probe.py \
  --source src/game/fun_00407780_00407780.cpp \
  --output matching2/build/probe_sound_motion_final
```

Body SHA-256 values for the new functions:

```
00407780  338  838a91548451f57f0ab7e623f0afc4c831c1cc2f3a99344818381a25ae5f9c30
00407A30  431  3eeb848d059ad247431957cf55e366c57af5f6c237e44833a8b7939af70f67ec
00407BE0  446  6dbebd1b36dc9c0f37c7d8252d0a516ce040b574efaea38174a316c3ee7465f8
```

`make verify MSVC_ARGS='--jobs 32'` passes: 487,936 bytes, whole-image SHA-256
`2f14760b6fbbf57549541583283badb9a19a4222b90f0a146d5aa17f01dc9040`.
Progress is 443 C++ regions / 24,757 bytes; 2,142 assembly regions /
364,225 bytes. No LTCG infrastructure changed.

## Fixed-angle sibling remains blocked

The 335-byte `0x004078E0` sibling remains production assembly. Its own ESI
entry, sound edge, complete extent, branch structure, and floating-point
operations were reproduced. The natural direct-angle-copy spelling differed
only in the two stores at `0x0040793E` and `0x00407944`: the compiler stored the
angle before speed, while retail stores speed first.

Capturing the angle as binary32 bits with two intrinsic `memcpy` operations
fixes that order. The resulting complete 335-byte body differs in only four
bytes at `0x004079B4`, `0x004079B7`, `0x004079BC`, and `0x004079BD`:

```
retail:     mov ecx,[esp]; mov edx,[esi+3E4h]; push ecx; push edx
candidate:  mov eax,[esp]; mov ecx,[esi+3E4h]; push eax; push ecx
```

Changing the external polar declaration from member to an equivalent
fastcall free function did not alter these choices. A float temporary uses
x87 for the angle copy; a union temporary expands the frame and function.
The closest candidate and native diagnostics remain under
`matching2/build/recovery-lab/fixed_angle_memcpy.cpp`, `sound_motion10`, and
`sound_motion11`. Further work should target source scheduling/register
allocation at the final argument preparation, not re-solve sound ABI or
literal placement. This is not an irreducibility claim.
