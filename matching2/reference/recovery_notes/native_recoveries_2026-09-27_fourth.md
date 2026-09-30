# C++ recovery checkpoint, 2026-09-27, fourth checkpoint

Twelve more complete routines, totaling **5,898 bytes**, are integrated as
readable C++ without inline assembly, naked bodies, or encoded instructions.
Across the preceding three checkpoints and this checkpoint, **43 routines /
10,366 bytes** have been recovered. Every new routine passes its normal
maintained-project probe at the original address and full retail extent.

| Entry | Bytes | Recovered operation | Detail |
| --- | ---: | --- | --- |
| 0x00402230 | 522 | Initialize game state, camera, callbacks and timer | [Recovery note](initialize_game_state_00402230_2026-09-27.md) |
| 0x0040D830 | 673 | Initialize enemy script record and bind its first instruction | [Recovery note](enemy_script_bind_0040d830_native_2026-09-27.md) |
| 0x00413980 | 147 | Load item front and register its update/render tasks | [Recovery note](item_front_initialize_00413980_native_ltcg_2026-09-27.md) |
| 0x00415800 | 724 | Draw game overlay animation banks and progress rectangles | [Recovery note](native_game_state_overlay_draw_00415800_2026-09-27.md) |
| 0x004180E0 | 107 | Allocate and publish UI, then start its worker | [Recovery note](game_ui_create_004180e0_2026-09-27.md) |
| 0x0041FAC0 | 140 | Register title tasks and start the embedded worker | [Recovery note](title_worker_start_0041fac0_2026-09-27.md) |
| 0x004216F0 | 465 | Initialize both camera defaults using typed vector assignments | [Recovery note](camera_defaults_004216f0_2026-09-27.md) |
| 0x0042F8B0 | 2452 | Refresh all twenty key-binding digit labels | [Recovery note](key_config_refresh_0042f8b0_2026-09-27.md) |
| 0x00441520 | 97 | Apply entity state when an animation resource is loaded | [Recovery note](entity_state_apply_00441520_2026-09-27.md) |
| 0x00444B10 | 201 | Fill horizontal edge-strip vertex attributes | [Recovery note](edge_strip_fillers_00444b10_00444be0_2026-09-27.md) |
| 0x00444BE0 | 201 | Fill vertical edge-strip vertex attributes | [Recovery note](edge_strip_fillers_00444b10_00444be0_2026-09-27.md) |
| 0x00447EC0 | 169 | Load indexed animation memory from the archive | [Recovery note](animation_resource_surface_memory_loaders_00447c80_00447ec0_native_2026-09-27.md) |

Camera defaults compile through ordinary MSVC C++. The other eleven routines
are selected from ten native-LTCG units. The edge pair shares one unit; UI
creation, item initialization and overlay drawing extend existing clusters.
Their previously selected contributions remain exact. Compiler contexts,
layout gaps and dependency anchors are excluded from recovered output and
add no recovered bytes. Seven new clusters bring the registered total to 683.

The key-label routine preserves all repeated Find calls, embedded child-link
traversals, signed digit arithmetic and final Configure tail call. A full
compiler-visible Configure body expressed as an ordinary free function gives
the retail register allocation. The enemy binder uses typed script-table and
timer layouts; its legal opaque Clear dependency preserves the ignored incoming
ECX while passing its owner in EDX. Its full resolver anchor remains unselected.
UI creation preserves configuration initialization before the complete wipe,
the device's stdcall COM slot, and the retail worker-entry cast. The memory
loader preserves the 260-byte path buffer required by the retail GS frame.

Whole-executable verification **passed**. All **2,242 maintained build units**
completed without failure. The complete **487,936-byte executable equals the
stable retail oracle byte for byte**, with SHA-256:
`2f14760b6fbbf57549541583283badb9a19a4222b90f0a146d5aa17f01dc9040`.
The `.text` SHA-256 remains
`c1acff416da826334c29a19fa89cd7a094626eb36c32afe7950f705a55f56998`.

The manifest and full hash gates passed. The audit compares all **3,909 current
project input files**, including the complete added/deleted file set, against
the build report. It checks all twelve new selected sources for assembly and
all ten affected native units for zero masking, zero instruction changes,
zero address-operand changes, and no oracle instructions used for building.
Independent source reviews found no material issues in the new routines,
ABIs, offsets, compiler inputs or ownership. Ghidra plate comments were saved
and read back for all eleven available Function heads. The memory loader at
0x00447EC0 remains a raw fragment with retained bounded evidence; no Function
object was invented for it.

Proof artifacts are under `matching2/build/experiments/`:

- `native_recoveries_2026-09-27_fourth_build.log`
- `native_recoveries_2026-09-27_fourth_audit.py`
- `native_recoveries_2026-09-27_fourth_verified.json`
- `native_recoveries_2026-09-27_fourth_port_report.json` (full build report snapshot)
- `native_recoveries_2026-09-27_fourth_reviews.json`
- `native_recoveries_2026-09-27_fourth_ghidra_before.json`
- `native_recoveries_2026-09-27_fourth_ghidra_verified.json`
- `native_recoveries_2026-09-27_fourth_partial_semantic_audit.json` and `.md`
- `native_recoveries_2026-09-27_fourth_next_leads.json` and `.md`

Current raw manifest totals are **1,650 semantic regions / 80,699 bytes** and
**1,128 assembly regions / 308,399 bytes**. A broader selected-body audit
corrects the previous incomplete three-function partial-semantic list:
**six semantic regions / 4,525 bytes** still contain assembly. These are the
two sprite submissions at 0x00442670 and 0x00442AD0 (1,111 bytes each), the two
rotated quad builders at 0x004436C0 and 0x00443910 (591 bytes each), projection
quads at 0x00443B60 (1,047 bytes), and scheduler callback creation at
0x00449ED0 (74 bytes). The other 29 file-scan hits have clean selected bodies
and helpers; their files also own separate assembly functions. Thus there are
**1,644 fully C++ semantic regions / 76,174 bytes**, and **1,134 regions /
312,924 bytes** still containing assembly across both classifications. The
full decompilation goal remains active.

Three additional candidates measured in this checkpoint remain unpromoted:

- **0x004246C0, player reset:** the full 244-byte body differs only in six
  register bytes across two animation flag stores. Attempts 02 and 05 emit
  the same body; attempts 03 and 04 are compile failures, not measurements.
  [Residual note](player_reset_004246c0_native_residual_2026-09-27.md).
- **0x00447C80, surface loader:** nearest complete model emits 575 of 576
  required bytes, with 326 differing bytes in the overlap. Pointer staging,
  register allocation and cleanup placement remain unresolved. The exact
  169-byte memory loader was integrated independently.
  [Residual note](animation_resource_surface_memory_loaders_00447c80_00447ec0_native_2026-09-27.md).
- **0x0043C710, camera shake:** the nearest model emits 344 of 349 required
  bytes, with 249 overlap differences. ESI/EBX save placement and duplicated
  branch tails remain unresolved; its timer and RNG anchors are independently
  exact. [Residual note](camera_shake_0043c710_2026-09-27.md).

Earlier measured residuals remain in scratch and remain assembly in the
maintained project. This checkpoint preserves them and the previous verified
checkpoints; it does not treat diagnostic alignments or semantic-only models
as byte-matching recoveries.
