# Movement through the complete real player-state caller

The [40-function graph](../semantic_candidates/player_movement_state_004250b0/)
adds the complete movement function at 0x4250B0 and its three complete animation
helpers to the prior 36-function collision/item graph. Movement is now an actual
C++ callee of the full player-state owner. No compiler fixture caller, unused
leading initializer input, register constraint or instruction patch is used.

The genuine call chain produces the private EDI movement receiver. The full
owner shrinks from 3,060 to 3,044 bytes against retail's 3,112. Movement measures
1,640 against 1,656, including both switch tables. Its remaining differences
include animation resource loader registers, reference-return handling, store
ordering and branch/table positions. Both functions remain unselected. The
shared script loader remains 197/203; item spawning remains 823/819. Adding this
caller does not settle those private conventions.

The full source preserves direction precedence, focus gating, special shot age,
slow-animation creation/retirement, facing scripts, integer motion and clamps,
world-position reads, history copies and all four familiar orbits. Checked player
views describe the actual overlapping scheduled-familiar and movement fields;
ordinal 5 shares the transition-age word. Orbit callbacks may alter desired and
current positions, reset flags, age and animation handles before the genuine
update continues.

All 9,270 bounded cases pass, including 2,186 movement cases. The new suite
executes movement 1,923 times, stop-frame 700, position 552, translated position
1,352 and script loading 1,169 times. These counts observe actual body entries;
they do not skip bodies. VM and callback effects remain declared boundaries.

The existing stop-frame 54-byte and position 90-byte helpers now obtain selected
production bytes through this genuine graph. Their original bodies remain
unselected anchors in the old clusters. The translated-position helper has a
whole 111-byte diagnostic match, but its literal references do not match in the
unaltered fixed-address graph. It keeps its previous production ownership.
All remaining selected functions in both old clusters still pass raw verification.
The prior 36-function collision production graph is unchanged.

Thirty complete functions / 3,536 bytes match after diagnostic address rebinding;
independent raw extraction from the fixed native PE verifies 26 functions /
3,033 bytes, including both selected functions. The new layout has no aliases,
masks or instruction edits. The legacy translation-unit include preserves its
original function grouping and introduces no caller.

Both full builds pass. Exact output equals the 487,936-byte retail executable.
Normal output equals the previous normal executable, with differences confined
to the eight existing equivalent owners. The fresh audit verifies 965 layouts,
1,484 selected functions and 4,069 compiler inputs. This is caller-context
replacement and semantic evidence, not new byte recovery: 59 actual assembly
regions / 89,043 bytes and eight equivalent owners remain.
