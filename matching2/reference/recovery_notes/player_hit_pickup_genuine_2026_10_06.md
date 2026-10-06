# Genuine pickup caller for 004059F0, 2026-10-06

Historical checkpoint: the [complete hit-test recovery](player_hit_test_exact_2026_10_06.md)
now selects all 202 bytes of 004059F0. The sweep remains assembly-owned.

Both 004059F0 (202 bytes) and 00428630 (1170 bytes) remain assembly-owned.
The maintained ordinary-C++ candidate is in
`reference/semantic_candidates/player_hit_pickup_004059f0/`. New recovery
credit is zero. No production selection, mask or byte-patching rule changed.

The previous hit-test rig used a synthetic loop. The current linker root is
the complete real collision sweep, including all 128 pickups and 32 score
regions. Fifteen complete genuine bodies span two translation units. Primary
creation, its allocator, registration, preservation loader and initializers
are visible to LTCG. Neither an entry trampoline nor an invented caller is
compiled. The current compiler derives player in ECX and point in EAX at
the real hit-test call, correcting the old claim that ordinary C++ cannot
produce that convention.

## Field corrections

These offsets were checked directly against the maintained retail assembly.
The legacy semantic structures and earlier pickup note misidentified the
first handle column as the beginning of the record array.

| Manager field | Actual offset and relationship |
| --- | --- |
| Animation resource | 0010 |
| Generation words | 0474, 0478 |
| Pickup records | 049C, 128 records of 005C bytes |
| First handle | 04E0 = first record + 0044 |
| Regions | 350C, 32 records of 006C bytes |

Each pickup starts with its own previous/current frame pair. Its position is
at 0014, state at 0040, handle at 0044, collected/initialized words at
0050/0054, and descriptor at 0058. The transition scale at 001C aliases
position Z. The filter receives the manager and the current record's clock
address, then the center on the stack. The interval call also uses that
record's clock. Both clock and handle columns advance 005C on every iteration.

No null-descriptor guard exists after rejecting states zero and two. A filter
can replace the descriptor before acceptance; descriptor reloads are preserved
around callbacks and animation calls. The saved animation field is at object
002C. Separate typed list nodes and animation records describe lookup and
children. MarkForRemoval returns the object when children are already flagged;
otherwise it returns the child cursor after traversal, which is null.

Regions have radius/speed/angle at 0000/0004/0008, width/height at 0010/0014,
position at 0018, timer at 0044, contribution at 0058, accumulation at 005C,
limit/interval at 0060/0064 and flags at 0068. The circular radius is per
region: both EBP and the timer cursor advance 006C in retail's loop.

## Numerical correction and complete native measurements

Retail stores pickup minimum X, minimum Y and maximum X as binary32 before
their comparisons. Maximum Y stays in x87 precision. Plain float locals in
the initial reconstruction did not force the stores to be reloaded. Twenty
adversarial comparisons spanning five powers of two exposed fifteen failures.
The maintained three volatile float locals encode those observed stores;
maximum Y remains extended. Region checks are ordered by axis to avoid
unnecessary double spills. The rotation stores sine and both local coordinates
as float while retaining cosine and displacement arithmetic.

| Genuine graph checkpoint | Full sweep bytes | Bounded result |
| --- | ---: | --- |
| Creation graph, before edge correction | 1156 / 1170 | 15 failures of 1220 |
| Three rounded edges | 1196 / 1170 | 1220 pass |
| Region tests ordered by axis | 1165 / 1170 | 1267 pass |
| Maintained typed nodes and helper return | 1165 / 1170 | 1273 pass |

The maintained hit-test is 203 / 202 bytes. It has 144 unequal overlapping
bytes and seven diagnostic instruction groups, starting at 00405A25. The
remaining differences are game-pointer hoisting, mode re-testing and memory
flag tests instead of the retail late flag-byte load into CL. The sweep has
1056 unequal overlapping bytes and 62 groups, starting at 00428632.

Nine full collaborators match after address-only rebinding: interval (29),
lookup (73), mark (66), validation (21), retirement (21), indicator (181),
allocator (161), preservation loader (194) and entity initializer (273).
Stop-at-frame is 65 bytes with two differing bytes. Primary creation is
74 / 73, registration 114 / 118, and object initialization 210 / 217.
These are complete native contributions, with no truncation to retail lengths.
Diagnostic equality provides no new fixed-address gate or selected recovery.

## Execution and reproduction limits

All 1273 bounded observations compare unmodified retail and native executable
images, returned values, affected manager/object/list storage, score, callback
order, preserved registers, return-stack cleanup and x87 control/balance.
Cases cover hit/miss/boundary classification; flag/config/mode combinations;
NaNs and infinities; state rejection; first/last pickups and regions; independent
clocks; descriptor replacement; screen limits; circles, axis boxes and rotated
boxes; contribution exhaustion; signed score overflow; script loading and
occupied-pool/heap creation; invalid inputs and signed remainder faults.
Sixty rounding cases use x87 controls 037F, 027F and 007F. Six direct removal
cases independently verify its return and child mutations.

Successful operator new, VM execution and descriptor callbacks are shared
scripted boundaries. The already-recovered constructor runs as retail code in
both heap-fallback executions. Allocation failure, arbitrary script behavior,
unmasked floating-point traps and whole-game execution are not proved.
The null result receiver follows the observed MSVC 7.1 public boundary.

Use the commands in the candidate README. Archived inputs, native paired
images/maps, commands, complete rebased diagnostic bodies and observation
reports are hashed by the receipt. Ghidra's project remains connected, but
function decompilation tools were not exposed in this session; this work used
the retail bytes and maintained assembly rather than fabricated tool results.

Normal fixed-address, full raw equality is still required before either target
can replace assembly. The next useful hit-test work is its late direct-hit
flag load and allocator decision under this real graph. For the sweep, native
frame/field grouping and the genuine creation spills remain measurable.
