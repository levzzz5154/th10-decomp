# Player animation advance and field contact

The subsequent [runtime and helper checkpoint](runtime_and_helpers_2026-10-01.md) additionally recovers the complete 885-byte caller and the 306-byte homing helper. Counts and residual statuses below describe this earlier two-function checkpoint.

Two complete functions, totaling 480 bytes, now compile as readable C++ without inline assembly. The final maintained build matches all 487,936 bytes of the retail executable. Recovery is 1,854 semantic regions / 97,973 bytes, with 444 assembly regions / 224,925 bytes remaining. Five semantic functions still contain inline x87; excluding their complete extents leaves 1,849 fully assembly-free semantic regions / 93,522 bytes. The full decompilation goal remains incomplete.

| Function | Address | Complete bytes | Actual native convention |
| --- | --- | ---: | --- |
| `PlayerAnimationState_004074B0::AdvanceAnimationFrame` | `0x004074B0` | 164 | Receiver ESI; plain RET |
| `FieldContact004266B0` | `0x004266B0` | 316 | Position ECX, target EDX, size EAX; result EAX; plain RET |

## Player animation advance

`matching2/msvc/src/game/player_animation_advance_frame_004074b0.cpp` updates the trail velocity while the animation frame at `+0x618` is at most 16. Its speed is the base value at `0x00470C68`, minus elapsed time times `0.3125f`, plus the player's scalar at `+0x3D8`. It passes that speed and heading `+0x3E4` to the genuine polar setter at `0x00408750`, with the velocity member at `+0x3C0` in ECX and two stack floats. After the cutoff it toggles flag bit zero instead.

The function then copies the timer's current frame to its previous field. For the pointed speed strictly between the two original thresholds, it increments the integer frame and adds one to elapsed time. Otherwise it adds the pointed speed to elapsed time and converts the result to the new frame using the genuine `__ftol2` entry at `0x00463B2C`. The C++ uses an ordinary cast; the compiler provides the x87 conversion call and original instruction order.

The shared header uses the maintained `FrameTimer` layout and checks its offset `+0x614`. A compiler-only array walker selects the private ESI receiver without an assembly bridge. The polar setter remains a genuine external callee, with its real ECX receiver and RET 8 contract; this recovery introduces no alternate setter body. The literal `0.3125f` is bound to the existing readonly value at `0x00470C6C`, and the unit increment to `0x00470AFC`. All 164 bytes, including branches, calls, and timer writes, match.

## Field contact

`matching2/msvc/src/game/field_contact_004266b0.cpp` forms typed two-coordinate inner bounds from the supplied position and half-size. Four strict separation predicates determine whether it misses the field's bounds at `+0x404/+0x408` and `+0x410/+0x414`. If it misses, it tests a separate outer rectangle extending 24 units around the position and returns two for overlap, zero otherwise.

For inner overlap, an active dialogue object at `+0x9EB8` of the manager referenced by `0x0047770C` suppresses contact. So do field modes two, four, and three at `+0x458`. Otherwise it calls the genuine activation entry at `0x00426CF0` when the countdown at `+0x4310` is nonpositive, then returns one. Activation takes the target pointer on the stack and returns with RET 4. Its complete 627-byte function remains assembly and is not claimed as recovered here.

All eight separation comparisons accept unordered floating-point values. The C++ expresses ordered strict separation as rejection, preserving the x87 status-word branches. In particular, Ghidra's simplified outer `<=` predicates would reject NaN and do not preserve those original branches. Typed inner minimum/maximum vectors and a distinct outer maximum vector reproduce the complete original x87 evaluation, spills, and comparison order without volatile fields or compiler barriers. Compiler literals `0.5f` and `24.0f` bind to the existing values at `0x00470B0C` and `0x00470BE8`.

The native compiler derives the original three-register entry from the ordinary source declaration and an unselected pointer-array caller. Both real callers, at `0x0040649C` and `0x0040E2DF`, retain their original retail call sequences. The old `_asm_FUN_004266b0_004266b0` alias is preserved, and the obsolete sole-owner assembly source `src/game/item_field_contact.cpp` is removed. The animation entry's old `_asm_PlayerAnimation_AdvanceFrame_004074b0` alias and original region record are also preserved.

## Verification and remaining work

Both maintained source probes are exact across their complete extents. The [checkpoint evidence](player_motion_and_field_contact_2026-10-01.evidence.json) independently compares each selected native PE function with the final game image, decodes all three genuine call targets, verifies the readonly constants, checks current project hashes and 3,011 native input-hash records, and verifies the contiguous 412,672-byte `.text` partition and source coverage. No retail bytes enter native compilation, no bytes are masked, and extraction changes neither instruction bytes nor address operands. Fresh Ghidra evidence and both agents' frozen production proofs are linked by hash.

The final command was:

```sh
make MSVC_ARGS='--jobs 32 --verify matching2/build/oracle/th10.exe'
```

All 1,912 build units succeeded. The final EXE SHA-256 is `2f14760b6fbbf57549541583283badb9a19a4222b90f0a146d5aa17f01dc9040`; `.text` is `c1acff416da826334c29a19fa89cd7a094626eb36c32afe7950f705a55f56998`. The final manifest label is included in the build's current input snapshot. Full logs and the evidence-generation script are retained under `matching2/build/experiments/player_motion_and_field_contact_2026_10_01`.

DeathShrink remains assembly: its separately measured complete 209-byte C++ candidate has eight differing bytes caused by an independent heading load and fall-rate multiplication exchanging order. The larger 885-byte player caller and the wrap helpers also remain unpromoted; genuine callee visibility has improved their native register allocation but has not established complete byte identity. Trigger activation is under a separate complete-function investigation.

The [pool cursor follow-up](replay_pool_cursor_scheduling_2026-10-01.md) additionally rules out volatile cursor fields/stores as a useful scheduling lever for the complete 139-byte replay allocator. All five new native comparisons retain its six-byte instruction-order mismatch, so that function remains assembly.
