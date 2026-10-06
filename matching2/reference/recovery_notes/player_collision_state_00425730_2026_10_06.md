# Complete player-state collision graph, 2026-10-06

The previous [complete 28-function player-state graph](player_state_genuine_00425730_2026_10_06.md)
left collision check and record activation as external, scripted boundaries.
The new [33-function candidate](../semantic_candidates/player_collision_state_00425730/)
adds their actual complete C++ bodies and the playfield/animation collaborators
required by activation. All five original real roots remain; no compiler test
caller, partial callee, parameter-liveness trick or register annotation was added.

CollisionRecord describes the complete 0x7F0 record: animation state +0x30C,
position +0x3B4, diameter +0x3F0, timer +0x3F8, animation index +0x438 and state
+0x446. The manager owns 2,000 records at +0x60 and its animation resource at
+0x3E0B50. Layout assertions cover the actual accesses. Check preserves the
three-component displacement construction and the existing production source's
_ReadWriteBarrier before the shared radius-scale read. It has no emitted
barrier instruction. Activation uses the measured production branch shape,
restarting the timer only on the inside path and marking outside records for
removal. The animation resource's CreateOffset returns the same recovered
four-byte AnimationRef that creation, registration and lookup already share.
Its hidden result slot is a consequence of ordinary C++ class-return semantics.
LoadScript invokes the actual one-pointer Entity_Init, with no dead leading
script parameter, installs the resource/index/script, resets the embedded
clock, clears the active bit, executes the VM and increments the script counter.

## Complete functions and genuine-context controls

Every measurement uses native MSVC 13.10 /GL and ordinary /LTCG links at two
bases, records the complete emitted extent and rebinds address operands for
diagnostics. Historical controls are compiler evidence only; all passing
behavior claims refer to the final genuine_graph snapshot.

| Whole-function source control | Activation | Check | CreateOffset | LoadScript | Player owner |
| --- | ---: | ---: | ---: | ---: | ---: |
| initial global class-return creator | 198/199 | 262/260 | 116/118 | 197/203 | 3060/3112 |
| resource member creator, shared Vector3 and flag-value controls | **199 exact** | 262/260 | 116/118 | 197/203 | 3060/3112 |
| resource member script loader; final genuine graph | **199 exact** | 262/260 | 116/118 | 197/203 | 3060/3112 |

The member creator correctly places the genuine resource before the hidden
result pointer. Reusing Vector3 and the already-recovered flag-value view does
not otherwise change output. The flag-value control was not retained; the
final creator uses the simpler unsigned flag snapshot. The member loader does
not change complete bytes after address rebinding. All controls contain full
functions, without fake callers, forced registers or artificial liveness.

The final 33-function graph has 26 diagnostic-exact functions / 3,021 bytes.
The original 27 helper/caller bodies are unchanged; only the outer player
owner changes among the prior 28. Bounds contributes a complete new 91-byte
match and activation contributes its complete 199-byte match. The owner is
3,060/3,112, with equal 20-byte switch tables, 2,852 differing overlapping
bytes and 124 instruction groups. It is still unmatched and assembly-owned.
Sweep, effect update and scheduled creation retain their prior differences.

Check differs in only two instruction groups: its external Item Spawn call
uses native ECX for the manager instead of retail EAX, and pushes the position
instead of retaining it in retail ECX. Its own engine/point convention is
already EAX/EBX through the genuine owner. This is the next concrete dependency
to replace with a whole genuine C++ callee; an external prototype cannot earn
retail's private convention.

CreateOffset differs in four groups, including its entity/index homes and the
order of flag/bucket stores and x87 position reads. LoadScript differs in 12
groups. The read-only native register trace observes object priority 184 and
EDX home, resource priority 48 and ESI home, index priority 30 and EDI home,
and shared zero priority 8 and EBX home. Retail uses an EAX object input with
an EDI body home, an ECX resource input copied to ESI, EBX index and EBP zero.
The trace explains the current native choices; it does not establish a source
fix. No compiler choice or memory was changed. Generic verification confirms
all 33 complete bodies and the full 9,728-byte .text section are identical to
the baseline; the section SHA-256 is
`33296b55d7085b8cc25a741a8285de24d571869b5e30d75c1b3c3e2435d1f5ff`.

## Behavior and fixed-address proof

All 5,510 bounded cases pass. The additional 1,557 cases execute activation
5,118 times, check 694, bounds 6,855, offset creation 386 and script loading
386 times. The former 947 whole-owner cases now execute collision and activation
rather than script them. State, manager/pool/object/global memory, normalized
external calls and order, helper invocation counts, results, preserved registers,
stack cleanup, x87 balance and control word are compared between retail and
native execution. Private-input registers are emulator fixture inputs only;
no compiler test caller was added.

The unchanged normal fixed-address probe passes all 199 activation bytes,
SHA-256 `104d9d3111629b8e843a524b4be11b5d826e0b6c5e10cd08b773d07e30f9f89f`.
The real owner and collision loop naturally establish the ESI receiver. The
isolated manifest owns all 33 actual complete native extents; its gap sections
contain only ordinary layout padding. It uses no constant aliases, reference
instructions, masked bytes or instruction/address edits. Independent extraction
finds 23 raw-exact bodies / 2,629 bytes, including the previously proven 174-byte
sequence updater. Motion, Tick and SoundQueue account for the three remaining
pooled-literal differences between raw and diagnostic counts.

The production manifest/source graph is unchanged and still audits to the
487,936-byte retail executable, SHA-256
`2f14760b6fbbf57549541583283badb9a19a4222b90f0a146d5aa17f01dc9040`.
It contains 2,255 ordinary C++ regions / 199,264 bytes and still has 59 actual
assembly regions / 89,043 bytes. Activation was already selected C++ in its
older context; this candidate adds no production selection or recovered-byte
credit. Bottom player collaborators, Item Spawn, VM effects and successful
allocation remain explicitly bounded external fixtures.
