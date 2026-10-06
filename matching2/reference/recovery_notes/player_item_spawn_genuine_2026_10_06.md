# Genuine item-spawn closure and production collision context, 2026-10-06

The [previous 33-function collision graph](player_collision_state_00425730_2026_10_06.md)
left Item Spawn external. Its 262/260 collision check differed only at that
call: native used ECX for the manager and pushed the point, while retail used
EAX/ECX. The [new complete graph](../semantic_candidates/player_item_spawn_0041bb00/)
includes genuine Item Spawn, animation script startup and the actual ordinary
item-polar method. The existing full player-state owner and collision loop
naturally establish Item Spawn's EAX manager / ECX point / four stack words /
RET16 contract. Check now equals all 260 retail bytes, without accepted
register substitutions, masks, instruction edits or fake compiler callers.

The record size, position, Entity animation, timer, state, kind/display kind,
normal/special pool starts and ring cursor are explicit checked C++ fields.
Item Spawn preserves the entire 150-slot normal search, clamp, timer seed/reset,
signed power remapping, previous kind-3 animation retirement, animation startup,
identifier writes, 2,048-slot ring, signed remainders and occupied-slot count
increments. It retains the previously measured nontrivial resource-bank snapshot
and timer barriers. They are source hypotheses, not claims about the original
source classes. No barrier instruction is emitted and no dummy parameter is
used. Script startup calls the actual complete one-pointer Entity_Init and
installs zeroed position/base/render vectors, layer bytes and script index.
The script loader source now returns the observed animation-manager pointer or
null; this correction changes no native bytes in the current ignored-result
call graph. No dead leading initializer argument was reintroduced.

## Whole native graph and remaining work

There are 36 complete genuine functions and six actual roots. Twenty-seven
functions / 3,281 bytes are exact after address-only diagnostic rebinding.
Twenty-four / 2,889 bytes are raw-exact in the fixed-address graph. As before,
Motion, Tick and SoundQueue account for three pooled-literal-address differences.
Among the previous 33 complete bodies, only Check and the outer player owner
change; the other 31 complete bodies, including the loader and activation, are
unchanged after address rebinding.

| Full function | Native / retail bytes | Remaining diagnostic groups |
| --- | ---: | ---: |
| Collision check | **260 / 260 exact** | 0 |
| Record activation | **199 / 199 exact** | 0 |
| Player-state owner | 3060 / 3112 | 124 |
| Item Spawn | 823 / 819 | 6 |
| Script startup | 200 / 202 | 11 |
| Script loading | 197 / 203 | 12 |
| Offset animation creation | 116 / 118 | 4 |
| Item polar helper | 30 / 30 | 3 |

Item Spawn's native and retail table material are both 23 bytes. The source
still requires two additional `mov edx,esi` entity handoffs to the native
script-start ABI and uses ECX instead of EAX for the first identifier copy.
The shifted table-reference groups also appear in the full comparison; none
is masked. Script startup keeps its object in EDX through the visible complete
initializer/loader graph, while retail uses ESI and passes EDX to Entity_Init.
The source must earn the retail convention through genuine collaborators or a
faithful representation; adding synthetic liveness or changing compiler choices
is not a solution. The previously measured older line graph's 819-byte / two-byte
residual belongs to a different complete helper graph and is not the result of
this new player-state closure.

The read-only compiler trace completes with 24 allocation events. All 36 full
native bodies and the entire 11,264-byte .text section remain unchanged; its
SHA-256 is `0da283c94c2107c7e7cc54630abdf715219bedb2788b0ba36af41a51e171e419`.
No compiler code/program data, physical register or allocation choice was changed.

## Behavior and production integration

All 7,084 bounded cases pass: the previous 5,510 plus 1,574 new full item cases.
The latter execute Item Spawn 1,642 times, script startup 864, script loading
1,404, offset creation 540 and item polar 1,228 times. The collision suite now
executes 54 actual special-item spawns. The complete death-state owner creates
its seven-item fan through the same real callee. Tests cover pools, occupancy,
first/last slots, clamp/unordered positions, signed power, remapping, previous
kind-3 effects, loaded/empty scripts, signed cursor/count thresholds, timer
flags, repeat calls and three x87 controls. Full player/item/collision/animation
memory, selected globals, normalized external calls and helper counts, results,
private-input preservation, cleanup and x87 balance are compared. The emulator's
private input registers are test fixtures only; no compiler test caller exists.
VM effects, successful allocation and bottom player collaborators remain bounded
external boundaries. The unselected ordinary polar method uses FCOS/FSIN and
is tested only over finite gameplay angles.

Both complete collision bodies pass the unchanged normal fixed-address probe:

- Activation, 199 bytes: `104d9d3111629b8e843a524b4be11b5d826e0b6c5e10cd08b773d07e30f9f89f`.
- Check, 260 bytes: `f099f1395e6458b13b4d35cbede812f4003e2be1a24600f8f238172139fe61bc`.

Production selects them from
`msvc/src/game/player_collision_00408030_00408100.cpp` through
`msvc/layout/ltcg/player_state_collision_genuine_00408030_00408100.json` and the
complete source graph in `player_state_collision_runtime/`. The driver is the
actual full player state owner; it has no pointer-array or fabricated context.
Both original selected regions remain ordinary C++ with their original sizes
and previous assembly provenance. Their former definitions remain complete
unselected anchors in `update_player.json`, which still selects six player/drop/
enemy bodies. That remaining legacy compiler context has not been falsely
claimed as genuine or removed. Its six selected bodies remain raw-exact.

The full normal build passes with changes confined to the eight already recorded
equivalent regions; all other executable/section bytes and both collision bodies
match retail. The full exact build passes and its 487,936 bytes equal retail:
`2f14760b6fbbf57549541583283badb9a19a4222b90f0a146d5aa17f01dc9040`.
The current audit verifies 964 layouts, 1,484 selected functions and 4,030 current
compiler inputs. Counts stay at 2,255 ordinary C++ regions / 199,264 bytes,
eight equivalent owners, and 59 actual assembly regions / 89,043 bytes.
No new region or byte recovery credit is claimed; the contribution is replacing
two selected bodies' synthetic compiler context with their actual complete
call graph. The full byte-matching, inline-asm-free goal remains incomplete.

Before/after manifests and compiler results are archived separately. The native
candidate and historical-control input hashes are checked against the exact
production-manifest snapshot used when they were measured. Current production
inputs are checked against the fresh compiled reports. Earlier sealed candidate
receipts that require the former live manifest are historical prerequisites;
they are not silently resealed or presented as current-state audits.
