# Complete linked-record manager walks through the real player owner

This graph has 42 complete ordinary C++ functions and six genuine roots. It
extends the prior 40-function movement graph with full manager evaluation at
0x41C800 and cleanup at 0x41C850. Both bodies now execute through the actual
player-state caller. Their polymorphic records have retirement in virtual slot
5 and evaluation in slot 7; every walk saves the next record before dispatch.

Executing the real cleanup revealed an omitted argument in the previous external
boundary: state 3/frame 15 passes mode **1**, as the retail `mov ebx,1` immediately
before 0x425D6D confirms. The complete owner now calls `Reset(1)`. The previous
fixture had skipped cleanup, returned zero and cleared the list head. The real
body keeps the head, dispatches eligible records and returns one. Those actual
operations now execute in both comparisons; only the virtual record methods
remain explicit callback boundaries.

| Whole function | Native / retail bytes | Production disposition |
| --- | ---: | --- |
| Manager evaluation, 0x41C800 | 76 / 76 | Raw exact through genuine owner |
| Manager cleanup, 0x41C850 | 44 / 44 | Raw exact through genuine owner |
| Animation stop frame, 0x449210 | 54 / 54 | Raw exact through genuine movement |
| Animation position, 0x4492F0 | 90 / 90 | Raw exact through genuine movement |
| Full player-state owner, 0x425730 | 3,044 / 3,112 | Unselected, complete 20-byte table included |
| Movement, 0x4250B0 | 1,640 / 1,656 | Unselected, both switch tables included |

The four existing selected helpers / 264 bytes now share this genuine production
context. The two synthetic manager contexts are removed from active layout
ownership, and the prior genuine movement context is replaced by this larger
graph. Their files and sealed historical evidence are preserved. The other
legacy contexts remain; no claim is made that all synthetic contexts are gone.
The 36-function collision production graph is unchanged.

All 9,812 bounded comparisons pass. The previous nine suites have 9,270 cases;
542 new manager cases cover empty/single/mixed lists, eligibility, totals, modes,
callback mutations, repeated walks, aliasing the copied vector, floating-point
bit patterns and actual owner transitions. The new suite executes evaluation
293 times and cleanup 234 times. The full 947-case owner suite also passes with
both manager bodies executing. Register preservation, stack cleanup, memory
state, callback arguments/order and x87 balance are compared. These bounded
checks do not establish unrestricted callbacks or full-game integration.

Thirty-two whole functions / 3,656 bytes match after diagnostic address rebinding.
Independent extraction from the fixed native PE verifies 28 whole functions /
3,153 bytes raw exact. The four selected bodies are raw exact without aliases,
masks, instruction edits or reference bytes as build inputs. The complete
translated-position helper remains a diagnostic match only in this graph and
keeps its previous production ownership.

Both full normal and exact builds pass. The exact 487,936-byte executable equals
retail, SHA-256 `2f14760b6fbbf57549541583283badb9a19a4222b90f0a146d5aa17f01dc9040`.
Normal output is unchanged; its 20,828 differing bytes belong solely to the same
eight equivalent owners. The current audit checks 963 layouts, 1,484 selected
functions and 4,064 compiler inputs. No new recovered-byte credit is claimed:
2,255 ordinary C++ regions / 199,264 bytes; 59 actual assembly regions /
89,043 bytes and eight equivalent owners remain under the active strict goal.

```bash
python matching2/reference/semantic_candidates/player_bullet_state_0041c800/measure.py genuine_graph --fresh
python matching2/reference/semantic_candidates/player_bullet_state_0041c800/bullet_differential.py genuine_graph
python matching2/reference/semantic_candidates/player_bullet_state_0041c800/player_differential.py genuine_graph
python matching2/reference/semantic_candidates/player_bullet_state_0041c800/audit_receipt.py
```

The receipt binds current sources, all whole native bodies, complete observed
case results, fixed probes, before/after ownership and both full build outputs.
