# Shared player layout and animation value interfaces

This follows the [20-function shared caller checkpoint](player_effect_pickup_shared_2026_10_06.md).
The previous turn was progress. This turn replaces the two player-record views
with one verified layout and retains two complete additional diagnostic-exact
helpers. All three remaining assembly targets remain unselected; new recovered
bytes are zero.

Both real callers now use one 4478-byte PlayerState, one 5C-byte record, one
descriptor, one motion type and one full FrameTimer. The player state timer
begins at 474, with previous/current at 474/478. These were incorrectly named
generation_begin/end in the narrower sweep view. The existing maintained
player declaration at
`msvc/include/th10/game/pause_result_open_004231d0/player/player_state.hpp`
independently establishes this timer and the other player offsets. The record
clock occupies 00..13; Motion begins at 14, with position at 14 and speed at 2C.
The sweep's transition scale is position.z, and its velocity_scale is motion.speed.
The shared descriptor includes ordinal/type at 1C/1D, the effect callback at 28
and sweep filter at 30. Static checks cover these fields, both handle slots,
both arrays and the complete player extent.

State and handle storage now use the observed volatile accesses consistently
across the two callers. Each initial-state guard takes one snapshot. Lookup
arguments are ordinary four-byte ID snapshots, distinct from handle storage.
This preserves retail's reloads and repeated retirement stores without retaining
unrelated pointer variables to those words. The complete StopAtFrame2 body
becomes diagnostic-exact at 65 bytes. The first common-layout control used
local volatile references; it retained their addresses in live registers and
regressed effect update to 879 bytes / 60 groups. All its bounded comparisons
pass, but that spelling is not maintained.

The registrar now uses the already-recovered member/value interface, grounded
in `msvc/src/render/animation_manager_register_primary_back_004489d0.cpp` and
`msvc/include/th10/game/player_hud_animations.hpp`. Its full ordinary body
reproduces all 118 bytes after diagnostic address rebinding. The earlier free
function spelling emitted 114 bytes and omitted the actual tail-next reload;
it also lowered the counter update differently. The retained member reloads
tail->next after storing node->next, increments the actual AnimationRef,
preserves the nonzero-ID rule and returns that reference by value.

The genuine creator also returns AnimationRef by value. The C++ compiler
derives its hidden result pointer; no register convention, caller stub, extra
work or opcode is supplied. Keeping the old explicit output pointer while
calling the value-return registrar grew the creator to 84/73 bytes. The
retained value-return creator restores 74/73 with five instruction groups.
Its caller's creation block and padding differ from the pointer-interface
checkpoint, so the sweep's overlapping inequality count increases by one.
This is recorded as an unresolved byte difference, not accepted or masked.

| Retained complete body | Native / retail | Unequal overlap | Groups |
|---|---:|---:|---:|
| Hit-test | 203 / 202 | 144 | 7 |
| Sweep | 1171 / 1170 | 1013 | 62 |
| Effect update | 874 / 876 | 205 | 3 |
| Creator | 74 / 73 | 56 | 5 |
| Object initializer | 210 / 217 | 187 | 9 |

The other **15 complete bodies / 1594 bytes** are diagnostic-exact. Those
helpers already have recovered production owners, so this is improved genuine
caller-graph fidelity, not new byte recovery credit. All 20 unique functions
are maintained in full; the two actual owners are the only public roots.
No normal fixed-address selection proof is claimed.

The retained module passes **2412** bounded retail/native comparisons: 1869
pickup checks, 215 effect checks and 328 real caller sequences. The 32 added
creation cases cover initial counters 0, 7, FFFFFFFE and FFFFFFFF, a nonempty
tail-next link, loaded/unloaded scripts and descriptor types 0/2. They execute
the complete creation/registration chain and compare complete memory states.
Pickup observation SHA-256:
`2c8a71f39b43150bff34149eff3271b13fdc7abb771d6b7b4797194a09ad36a3`.
The sequence observations remain identical to the previous checkpoint, with
410 calls to each real owner. Allocation, descriptor callbacks and animation
VM effects retain their documented scripted boundaries; full-game behavior
and arbitrary VM effects are not established.

Four full source controls, their native images/maps, complete bodies,
compiler commands and input hashes are archived. Common-layout and value-return
controls were executed with all 2380 prior cases; the intermediate explicit
output-pointer registration control was only measured and has no asserted
behavior equivalence. The interim common-player canonical checkpoint remains
archived alongside the original shared-lookup/module checkpoints.

The production comment now refers to 2412 checks. Production selection and
instruction bytes are unchanged. The final receipt seals the fresh compiler
inputs, complete native bodies and observations and current production audit.
The full executable decompilation remains open on all remaining assembly
regions and the three target owners' byte differences.

The [public initializer follow-up](animation_resource_initialize_object_genuine_2026_10_06.md) retains its authentic public ABI as a third real root. Creator and initializer now match their complete 73/217-byte bodies, bringing the diagnostic supporting total to 17 functions / 1884 bytes. All 2460 comparisons pass, including 48 direct initializer cases. The already selected initializer also passes its normal fixed-address proof using this genuine graph in place of the former synthetic driver; the three unresolved target owners remain assembly. The 15-body, 2412-case checkpoint above is preserved as historical evidence.

The [shared reference follow-up](player_effect_pickup_reference_2026_10_06.md) removes the duplicate lookup ID type, preserves all 20 complete native bodies and passes 2508 bounded comparisons, including 48 direct zero/high-bit ID checks. It also refreshes the normal initializer proof under the updated shared interface. The prior checkpoint above remains archived.
