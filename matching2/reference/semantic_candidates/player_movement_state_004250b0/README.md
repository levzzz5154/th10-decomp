# Complete movement in the genuine player graph

This graph contains 40 complete, ordinary C++ functions and six real roots. The
complete `PlayerState::Move` body replaces the former external movement edge of
the complete player-state owner. No synthetic caller or extra register input is
present. Private EDI movement and SI/ESI animation-helper inputs arise through
actual callers under MSVC 7.1 LTCG.

All 9,270 bounded retail/native cases pass: the previous eight suites contain
7,084 cases and the new movement suite contains 2,186. Movement tests cover all
direction combinations, focus gating, shot-dependent transition age, movement
speeds, fixed-position clamps, history, four familiar orbits, callback mutations,
animation handles, child propagation and three x87 precision controls. The
movement and animation bodies execute intact; VM, allocation and orbit callbacks
remain explicit fixture boundaries. These tests do not establish full-game
integration or unrestricted floating-point equivalence.

The checked movement view uses the same 0x4478-byte player object. Familiar
positions and reset flags overlap the existing scheduled-familiar view; the
transition-age field overlaps scheduler ordinal 5. Static offset checks describe
these actual retail relationships. The volatile input snapshot and position
reads preserve the observed accesses without altering the shared owner type.

| Whole function | Native / retail bytes | Status |
| --- | ---: | --- |
| Movement, 0x4250B0 | 1,640 / 1,656 | Unselected; both 32-byte switch tables included |
| Player-state owner, 0x425730 | 3,044 / 3,112 | Unselected; complete 20-byte switch table included |
| Stop frame, 0x449210 | 54 / 54 | Selected through this genuine graph, raw exact |
| Position, 0x4492F0 | 90 / 90 | Selected through this genuine graph, raw exact |
| Translated position, 0x449350 | 111 / 111 | Diagnostic exact after address rebinding; remains in its previous production context |

Only the existing 54-byte and 90-byte selected helpers move to this production
context. Their original complete bodies remain unselected anchors in the two
legacy clusters, whose remaining selected functions also pass. A one-include
translation unit preserves the legacy translated-position compilation when its
primary source changes. It defines no caller and adds no executable code.
The remaining synthetic legacy contexts are still present; no claim is made
that all of their ownership has been replaced.

Thirty whole functions / 3,536 bytes are exact in the diagnostic address-rebound
comparison. Independent extraction from the production fixed-address native PE
finds 26 whole raw-exact functions / 3,033 bytes. The translated-position literal
addresses account for its narrower diagnostic result; it is not promoted by
this graph. Only the two selected whole functions / 144 bytes are selected here.
The new manifest uses no constant/data aliases, masks, instruction edits or
retail bytes as compiler inputs. Relative-call metadata in the build supplies
real external addresses.

Both full normal and exact builds pass. The exact 487,936-byte executable equals
retail, SHA-256 `2f14760b6fbbf57549541583283badb9a19a4222b90f0a146d5aa17f01dc9040`.
The normal executable is unchanged from the prior checkpoint; its 20,828 unequal
bytes all belong to the same eight existing equivalent owners. Current audit:
965 native layouts, 1,484 selected functions and 4,069 verified compiler inputs.
No new recovered-byte credit: 2,255 ordinary C++ regions / 199,264 bytes;
59 actual assembly regions / 89,043 bytes remain, plus eight equivalent owners.

Reproduce from the repository root:

```bash
python matching2/reference/semantic_candidates/player_movement_state_004250b0/measure.py genuine_graph --fresh
python matching2/reference/semantic_candidates/player_movement_state_004250b0/movement_differential.py genuine_graph
python matching2/reference/semantic_candidates/player_movement_state_004250b0/player_differential.py genuine_graph
python matching2/reference/semantic_candidates/player_movement_state_004250b0/audit_receipt.py
```

The sealed inputs and executable establish the checkpoint independently of later
changes to the live project. The receipt also records the current production
ownership and its exact verification. The prior 36-function archive is preserved.
