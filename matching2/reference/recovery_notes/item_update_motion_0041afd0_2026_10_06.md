# Typed item motion and rectangle controls, 2026-10-06

The complete item-update candidate now separates its animation and motion
subobjects and emits **2,232 native / 2,320 retail bytes**, including all 64
switch-table bytes. All **473 bounded retail/native comparisons** pass with the
same observation hash as the preceding initializer graph. Update remains
unselected: **2,105 unequal overlapping bytes and 133 diagnostic instruction
groups** remain. A shorter body does not establish byte equality.

The same genuine graph still supplies production's complete conversion,
power-add and life-add recoveries, raw-exact across **472 bytes**. The independent
four-function gate also proves the complete **161-byte allocator**. Selection,
manifest ownership and matching tools are unchanged; no new recovered bytes
are credited.

## Source and full controls

`SpawnItem_0041bb00` contains its actual 0x3AC-byte animation followed by an
`ItemMotion_0041bb00` subobject holding position, three-component velocity,
motion counter, timer, state, kind, display kind, magnet speed and variant.
Existing offset/size checks now describe those nested fields. The contiguous
2,198-record array, 0x3F0 stride and every retail offset are unchanged. Spawn
and conversion use the same coherent type; no overlapping replacement array
or compiler-only field is introduced.

The update walks the item and motion pointers together. Its conversion flag
is an integer, matching retail's dword storage. Rectangle rejection spells the
lower-bound tests as `minimum.x > point.x` and `minimum.y > point.y`, preserving
unordered-coordinate behavior while producing retail's x87 operand order and
`test ah,0x41` form. The proved extended planar products, binary32 Z displacement
store and stored-Y screen test remain intact.

The original flat graph emitted 2,436 bytes. The complete control ledger is
`evidence/motion_precision_control_ledger.json`:

| Complete ordinary-source control | Native update bytes |
| --- | --- |
| Nested motion, pointer derived each iteration | 2,220 |
| Nested motion, motion pointer retained through loop | 2,220 |
| Integer conversion flag | 2,224 |
| Retail lower-bound operand order; maintained | 2,232 |
| Y reference / position reference / independent cursors | 2,232 each |
| Two-component predicate arguments by value | 2,420 |
| Three-component predicate arguments by value | 2,380 |
| Two-component comparison operators | 2,580 |
| Two coordinate snapshots / value-plus-snapshot | 2,380 each |
| Additional complete real stage caller | 2,232 |

Every control passes all 473 item comparisons with the same observations.
The stage control contains 33 complete bodies; the others contain 32. The
fixture executes item update, not the additional stage routine. Copies and
operator wrappers add stack spills and do not reproduce retail's two snapshots.
The position-reference body is identical to the baseline. The Y-reference
body differs at 22 bytes while retaining its size and retail-difference count.
The actual stage caller leaves the 200-byte script-start helper and its private
ABI unchanged. These results constrain the next investigation; none proves
an unavoidable compiler limitation or the original source.

Thirteen controls preserve full sources, layouts, two native link bases, maps,
complete normalized/retail bodies, comparisons, execution reports and coverage.
No caller, live argument, register assignment, instruction patch or comparison
mask is fabricated. The maintained form keeps the direct rectangle predicate.

## Proof and remaining scope

The normal fixed-address gates pass for the three production selections and
the independent allocator proof. The complete 2,232-byte update is an unselected
compiler context; the production layout retains each actual native contribution
extent. Spawn remains unselected at **823 / 819 bytes**, with 425 unequal
overlapping bytes. The previous 2,436-byte source, receipt, PE/MAP and actual
production inputs are independently preserved in `evidence/initializer_graph/`.

The fixture retains 38 initializer cases and 16 heap-fallback/constructor cases,
valid/loading item scripts, manager ring wraparound, all earlier precision
cases, full memory observations, callback traces, return/stack checks and x87
state. Successful allocation, VM callbacks, power-change and terminal conversion
remain scripted; the constructor executes retail's already-recovered body in
both runs. This remains bounded evidence, not complete game integration.

`make` and `make EXACT=1` pass. Exact mode remains raw-identical to the
487,936-byte oracle, SHA-256
`2f14760b6fbbf57549541583283badb9a19a4222b90f0a146d5aa17f01dc9040`.
The current audit verifies 963 layouts, 1,483 selected functions and 3,986
current compiler inputs. Counts remain 2,254 ordinary C++ regions / 199,062
bytes and **60 actual assembly regions / 89,245 bytes**. The full goal remains
active.

Commands and current hashes are in
[`item_update_0041afd0/`](../semantic_candidates/item_update_0041afd0/).
