# Pickup sweep geometry, animation types and native frame

This follows the [complete genuine graph checkpoint](player_hit_pickup_genuine_2026_10_06.md).
The maintained ordinary-C++ graph still contains 15 complete genuine bodies,
with the full pickup sweep as its sole public linker root. No synthetic caller,
inline assembly, register prescription, instruction patch or comparison mask
was added. Both collision targets remain assembly-owned; new recovered bytes
are zero.

The maintained sweep is now **1171 / 1170 bytes**, with 1012 unequal overlapping
bytes and 61 instruction-difference groups. The leaf remains 203 / 202, with
144 unequal bytes and seven groups. Nine collaborators remain diagnostic-exact
after address-only rebinding. These results are not a normal fixed-address
selection proof, and a nearly equal length does not establish recovery.

The shared Entity layout identifies the saved +2C field as `rotation.z`, a float,
and +14/+18 as intrusive child next/previous links. The candidate now uses these
types. Its float save/restore compiles to integer bit copies, preserving all
tested angle patterns, including signaling NaNs. MarkForRemoval retains its
object-or-null return contract: a nonnull previous link returns the object;
otherwise traversal leaves the return cursor null.

Retail reserves 64 bytes. After its four register pushes, the observed geometry
storage is:

| Local | Offset | Size | Use |
|---|---:|---:|---|
| Pickup maximum | 20 | 12 | XY edges, later rotated XY point |
| Player maximum | 2C | 12 | XY bounds |
| Player minimum | 38 | 12 | XY bounds |
| Pickup minimum | 44 | 12 | XY edges |

The Z words are not initialized or read. The maintained source uses four
three-float position objects and reuses the pickup maximum as the rotated
point. This produces retail's 64-byte frame without artificial padding or
liveness. Pickup minimum XY and maximum X still round to binary32; maximum Y
stays in x87 precision in the measured native body. The first raw difference
has moved from the frame-size operand to **00428647**, where the candidate
stores the total in a local and retail reuses the manager parameter's storage.
Register choices, loop cursor homes, geometry ordering and creation code also
remain different.

Twenty-three complete source controls were measured, with full native extents
and both image bases preserved. Selected measurements are:

| Control | Sweep bytes | Unequal overlap | Groups |
|---|---:|---:|---:|
| Previous maintained scalar geometry | 1165 | 1056 | 62 |
| Four position objects, early total | 1171 | 1017 | 55 |
| Float half dimensions | 1158 | 991 | 58 |
| Float angle, four position objects | 1171 | 1015 | 66 |
| Float angle, changed corner declaration order | 1171 | 1013 | 67 |
| Reused pickup maximum, retained | 1171 | 1012 | 61 |
| Two-arm generation gate | 1182 | 1045 | 70 |

Float half dimensions pass the tested cases but were not retained merely for
their shorter extent or smaller difference count. The chosen types/storage
follow the shared object layout and retail's actual stack accesses. Three
generation snapshots emit the same code as their baseline; delaying total
initialization and restructuring the generation gate do not fix its stack home.
The archive ledger distinguishes controls that were executed from those only
measured. No behavior equivalence is asserted for unexecuted controls.

Two read-only compiler traces ran with hardware breakpoints and unchanged
MSVC 7.1 `c2.dll`, SHA-256
`7a6f6d8e4da7b518384ff78f2c41028805d3a1d1a40dc2cc857c391ec81763f5`.
The 53-event global-register trace shows the integer saved-field control taking
EBP before the manager, making the manager costly to retain. The corrected
16-event stack trace shows four 12-byte geometry elements. The total's conflict
set includes the manager parameter; the pickup cursor's does not. The resulting
cursor reuse and separate total local explain the measured stack-home
difference. This is an observation of the compiler's graph, not a proof that
ordinary C++ cannot reproduce retail's allocation. No decisions were forced.
All 3072 bytes of each traced code section equal its untraced control. The
initial stack trace decoded the conflict pointer incorrectly; its empty
conflict lists are rejected and are not used in this conclusion.

The retained graph passes **1837** bounded retail/native comparisons: the
previous 1273 cases, 480 subnormal-dimension cases under x87 controls 037F,
027F and 007F, and 84 angle-bit preservation cases with/without script loading.
Observation SHA-256 is
`e3ec8628d013a380737826cd78972c94f3d0779f46b64e20c72c736f5b31c65f`.
Successful allocation, VM effects and descriptor filters are scripted as
documented in the fixture; arbitrary VM behavior and full-game integration
remain outside this bounded test. The original already-recovered constructor
executes in both runs for the tested heap path.

Sources, input snapshots/hashes, complete PE/maps/bodies, commands, source
controls, observations and read-only traces are preserved in
[the candidate archive](../semantic_candidates/player_hit_pickup_004059f0/README.md).
The previous 1165-byte/1273-case checkpoint remains archived as historical
evidence. Current production checks and counts are sealed in the receipt.
