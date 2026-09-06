# Player-partition semantic implementation audit — 2026-09-05

This report covers the exact address partition assigned to the player agent: **86 source files, 246 semantic addresses, and 95,131 tracked retail bytes** from `docs/semantic_exhaustive_audit_manifest.json`. It is an address-level static audit; a `grounded` row means the promoted source and all available IDA C, IDA assembly, and raw Ghidra artifacts agree on the reviewed shape. It does not claim live retail execution, compiler/ABI identity, or byte-for-byte equivalence for a callback-based host API.

## Verdict rules

- **grounded**: exact source marker and all three local references were available, and the bounded comparison found no discrepancy in control flow, fields, constants, ownership, or error handling at the reviewed boundary.
- **partial**: a concrete slice is supported, but a material behavior or contract is omitted or contradicted.
- **unresolved**: one or more required local references is unavailable, so no semantic credit is assigned.

## Results

Of 246 addresses, **2 are grounded**, **7 are partial**, and **17 are unresolved**, and **220 remain pending**. Unresolved rows lack required exports; pending rows have references but no completed function-specific evidence row yet.

| Address | Source | Source line | IDA C | IDA asm | Ghidra | Verdict | Boundary / finding |
| --- | --- | ---: | ---: | ---: | --- | --- | --- |
| `0x0041a200` | `src/archive/score_save.cpp` | 256 | 29058 | 36605 | `0041A200_FUN_0041a200.c` | **partial** | Retail writes fixed hint header strings, traverses eight global linked lists with 255-record caps, emits fields at offsets +0x70/+0x60/+0x68/+0x64/+0x7C, and closes the shared handle. The host hook emits a shortened header, delegates records through a different list callback, and does not model the global write/error/critical-section path; text-format and ownership equivalence are not established. |
| `0x0042b1e0` | `src/archive/score_save.cpp` | 211 | 41664 | 60741 | `0042B1E0_FUN_0042b1e0.c` | **partial** | Retail copies the six word header from the score object, serializes exactly seven CR sections at 0x437C-byte strides with the 0x5243 tag and 0xB3E-byte checksum loop, adds the 0x110-byte trailer checksum, compresses, encrypts with key 53/block 16, and writes scoreth10.dat. The host loops caller-supplied sections, computes only a flat payload sum, fabricates SCR0/version fields, and omits the fixed record/trailer layout. |
| `0x004359b0` | `src/archive/score_save.cpp` | 113 | 50773 | 76729 | `004359B0_FUN_004359b0.c` | **grounded** | LZSS control structure agrees: 0x2000 ring, 0x12-byte lookahead, literal flag bits, 13-bit position plus 5-bit (length-3) tokens, tree delete/insert per emitted byte, and final partial flag flush match IDA C 50773-51057, Ghidra 004359B0 lines 10-178, and asm sub_4359B0. Boundary: source makes retail globals, allocation, and output-capacity failure explicit through LzssState/output_capacity. |
| `0x00436000` | `src/archive/score_save.cpp` | 24 | 51229 | 77421 | `00436000_FUN_00436000.c` | **grounded** | Match-tree insertion agrees on the 0x2000+byte roots, 18-byte compare, longest-match update, child-link insertion, and full-match node replacement. IDA C 51229-51324, Ghidra 00436000 lines 10-95, and asm sub_436000 match; source exposes the retail globals as LzssState and returns the match length rather than using the register ABI. |
| `0x0044dbf0` | `src/game/archive_cursor_open.cpp` | 1 | 68932 | 115194 | `0044DBF0_FUN_0044dbf0.c` | **pending** | Source and all three local references are present; exact semantic comparison is pending. |
| `0x0043c2c0` | `src/game/ascii_overlay_callbacks.cpp` | 52 | 55434 | 87451 | `0043C2C0_FUN_0043c2c0.c` | **pending** | Source and all three local references are present; exact semantic comparison is pending. |
| `0x0043c410` | `src/game/ascii_overlay_callbacks.cpp` | 45 | 55506 | 87595 | `0043C410_FUN_0043c410.c` | **pending** | Source and all three local references are present; exact semantic comparison is pending. |
| `0x00447ae0` | `src/game/ascii_overlay_callbacks.cpp` | 23 | 64179 | 104669 | `00447AE0_FUN_00447ae0.c` | **pending** | Source and all three local references are present; exact semantic comparison is pending. |
| `0x0040e5f0` | `src/game/boss_overlays.cpp` | 35 | 22156 | 19622 | `0040E5F0_FUN_0040e5f0.c` | **pending** | Source and all three local references are present; exact semantic comparison is pending. |
| `0x0041d7c0` | `src/game/boss_overlays.cpp` | 4 | 31303 | 41573 | `0041D7C0_FUN_0041d7c0.c` | **pending** | Source and all three local references are present; exact semantic comparison is pending. |
| `0x0040ae70` | `src/game/bullet.cpp` | 6 | 19213 | 14052 | `0040AE70_FUN_0040ae70.c` | **pending** | Source and all three local references are present; exact semantic comparison is pending. |
| `0x0040af00` | `src/game/bullet.cpp` | 5 | 19247 | 14101 | `0040AF00_FUN_0040af00.c` | **pending** | Source and all three local references are present; exact semantic comparison is pending. |
| `0x0040af90` | `src/game/bullet.cpp` | 5 | 19279 | 14156 | `0040AF90_FUN_0040af90.c` | **pending** | Source and all three local references are present; exact semantic comparison is pending. |
| `0x0040b250` | `src/game/bullet.cpp` | 151 | 19455 | 14470 | `0040B250_FUN_0040b250.c` | **pending** | Source and all three local references are present; exact semantic comparison is pending. |
| `0x0040c6e0` | `src/game/bullet.cpp` | 175 | 20553 | 16599 | `0040C6E0_FUN_0040c6e0.c` | **pending** | Source and all three local references are present; exact semantic comparison is pending. |
| `0x0040cc70` | `src/game/bullet.cpp` | 4 | 20793 | 17193 | `0040CC70_FUN_0040cc70.c` | **pending** | Source and all three local references are present; exact semantic comparison is pending. |
| `0x0040cea0` | `src/game/bullet.cpp` | 140 | 20884 | 17422 | `0040CEA0_FUN_0040cea0.c` | **pending** | Source and all three local references are present; exact semantic comparison is pending. |
| `0x0040cf40` | `src/game/bullet.cpp` | 108 | 20925 | 17501 | `0040CF40_FUN_0040cf40.c` | **pending** | Source and all three local references are present; exact semantic comparison is pending. |
| `0x0040cf60` | `src/game/bullet.cpp` | 119 | 20933 | 17518 | `0040CF60_FUN_0040cf60.c` | **pending** | Source and all three local references are present; exact semantic comparison is pending. |
| `0x0040cf90` | `src/game/bullet.cpp` | 128 | 20957 | 17548 | `0040CF90_FUN_0040cf90.c` | **pending** | Source and all three local references are present; exact semantic comparison is pending. |
| `0x0040cfb0` | `src/game/bullet.cpp` | 3 | 20974 | 17572 | `0040CFB0_FUN_0040cfb0.c` | **pending** | Source and all three local references are present; exact semantic comparison is pending. |
| `0x0040d680` | `src/game/bullet.cpp` | 164 | 21364 | 18258 | `0040D680_FUN_0040d680.c` | **pending** | Source and all three local references are present; exact semantic comparison is pending. |
| `0x0040d830` | `src/game/bullet.cpp` | 3 | 21486 | 18470 | `0040D830_FUN_0040d830.c` | **pending** | Source and all three local references are present; exact semantic comparison is pending. |
| `0x0040dc80` | `src/game/bullet.cpp` | 4 | 21733 | 18809 | `0040DC80_FUN_0040dc80.c` | **pending** | Source and all three local references are present; exact semantic comparison is pending. |
| `0x0044bc70` | `src/game/bullet.cpp` | 49 | 67497 | 111799 | `0044BC70_FUN_0044bc70.c` | **pending** | Source and all three local references are present; exact semantic comparison is pending. |
| `0x0044c2a0` | `src/game/bullet.cpp` | 67 | 67730 | 112517 | `0044C2A0_FUN_0044c2a0.c` | **pending** | Source and all three local references are present; exact semantic comparison is pending. |
| `0x0040b3a0` | `src/game/bullet_anim_release.cpp` | 17 | 19470 | 14587 | `0040B3A0_FUN_0040b3a0.c` | **pending** | Source and all three local references are present; exact semantic comparison is pending. |
| `0x00428280` | `src/game/effect_pool_update.cpp` | 3 | 39396 | 56343 | `00428280_FUN_00428280.c` | **pending** | Source and all three local references are present; exact semantic comparison is pending. |
| `0x0040ba90` | `src/game/ending_text.cpp` | 27 | 19872 | 15337 | `0040BA90_FUN_0040ba90.c` | **pending** | Source and all three local references are present; exact semantic comparison is pending. |
| `0x004073e0` | `src/game/enemy_grid_scan.cpp` | 13 | 16354 | 8813 | `004073E0_FUN_004073e0.c` | **pending** | Source and all three local references are present; exact semantic comparison is pending. |
| `0x00407560` | `src/game/enemy_motion_steps.cpp` | 61 | 16428 | 8965 | `00407560_FUN_00407560.c` | **pending** | Source and all three local references are present; exact semantic comparison is pending. |
| `0x00407780` | `src/game/enemy_motion_steps.cpp` | 108 | 16513 | 9123 | `00407780_FUN_00407780.c` | **pending** | Source and all three local references are present; exact semantic comparison is pending. |
| `0x004078e0` | `src/game/enemy_motion_steps.cpp` | 108 | 16577 | 9229 | `004078E0_FUN_004078e0.c` | **pending** | Source and all three local references are present; exact semantic comparison is pending. |
| `0x00407a30` | `src/game/enemy_motion_steps.cpp` | 203 | 16643 | 9334 | `00407A30_FUN_00407a30.c` | **pending** | Source and all three local references are present; exact semantic comparison is pending. |
| `0x00407be0` | `src/game/enemy_motion_steps.cpp` | 155 | 16722 | 9471 | `00407BE0_FUN_00407be0.c` | **pending** | Source and all three local references are present; exact semantic comparison is pending. |
| `0x00407ef0` | `src/game/enemy_motion_steps.cpp` | 81 | 16857 | 9742 | `00407EF0_FUN_00407ef0.c` | **pending** | Source and all three local references are present; exact semantic comparison is pending. |
| `0x00401de0` | `src/game/entity.cpp` | 3 | 12415 | 1227 | `00401DE0_FUN_00401de0.c` | **pending** | Source and all three local references are present; exact semantic comparison is pending. |
| `0x00401ff0` | `src/game/entity.cpp` | 3 | 12535 | 1433 | `00401FF0_FUN_00401ff0.c` | **pending** | Source and all three local references are present; exact semantic comparison is pending. |
| `0x00402050` | `src/game/entity.cpp` | 3 | 12543 | 1472 | `00402050_FUN_00402050.c` | **pending** | Source and all three local references are present; exact semantic comparison is pending. |
| `0x00405d00` | `src/game/entity.cpp` | 27 | 15368 | 6855 | `00405D00_FUN_00405d00.c` | **pending** | Source and all three local references are present; exact semantic comparison is pending. |
| `0x00405de0` | `src/game/entity.cpp` | 86 | 15395 | 6928 | `00405DE0_FUN_00405de0.c` | **pending** | Source and all three local references are present; exact semantic comparison is pending. |
| `0x00406160` | `src/game/entity.cpp` | 47 | 15531 | 7261 | `00406160_FUN_00406160.c` | **pending** | Source and all three local references are present; exact semantic comparison is pending. |
| `0x004061d0` | `src/game/entity.cpp` | 54 | 15549 | 7312 | `004061D0_FUN_004061d0.c` | **pending** | Source and all three local references are present; exact semantic comparison is pending. |
| `0x0041ad60` | `src/game/entity.cpp` | 74 | 29576 | 37757 | `0041AD60_FUN_0041ad60.c` | **pending** | Source and all three local references are present; exact semantic comparison is pending. |
| `0x00438a30` | `src/game/entity.cpp` | 3 | 53203 | 82103 | `00438A30_FUN_00438a30.c` | **pending** | Source and all three local references are present; exact semantic comparison is pending. |
| `0x0042b780` | `src/game/floating_text_draw.cpp` | 34 | 41932 | 61292 | `0042B780_FUN_0042b780.c` | **pending** | Source and all three local references are present; exact semantic comparison is pending. |
| `0x00418c40` | `src/game/game_config_defaults.cpp` | 17 | 27851 | 34428 | `00418C40_FUN_00418c40.c` | **pending** | Source and all three local references are present; exact semantic comparison is pending. |
| `0x004218d0` | `src/game/game_mode_switch.cpp` | 5 | 34105 | 47307 | `004218D0_FUN_004218d0.c` | **pending** | Source and all three local references are present; exact semantic comparison is pending. |
| `0x00401000` | `src/game/game_thread.cpp` | 3 | 11786 | 42 | `00401000_FUN_00401000.c` | **pending** | Source and all three local references are present; exact semantic comparison is pending. |
| `0x00401110` | `src/game/game_thread.cpp` | 3 | 11830 | 113 | `00401110_FUN_00401110.c` | **pending** | Source and all three local references are present; exact semantic comparison is pending. |
| `0x00401260` | `src/game/game_thread.cpp` | 3 | 11896 | 216 | `00401260_FUN_00401260.c` | **pending** | Source and all three local references are present; exact semantic comparison is pending. |
| `0x00401440` | `src/game/game_thread.cpp` | 4 | 11980 | 373 | `00401440_FUN_00401440.c` | **pending** | Source and all three local references are present; exact semantic comparison is pending. |
| `0x00401760` | `src/game/game_thread.cpp` | 118 | 12128 | 698 | `00401760_FUN_00401760.c` | **pending** | Source and all three local references are present; exact semantic comparison is pending. |
| `0x00401a50` | `src/game/game_thread.cpp` | 124 | 12266 | 922 | `00401A50_FUN_00401a50.c` | **pending** | Source and all three local references are present; exact semantic comparison is pending. |
| `0x00447bb0` | `src/game/game_thread_text_draw.cpp` | 59 | 64207 | 104753 | `00447BB0_FUN_00447bb0.c` | **pending** | Source and all three local references are present; exact semantic comparison is pending. |
| `0x004266b0` | `src/game/item_field_contact.cpp` | 13 | 37998 | 53906 | `004266B0_FUN_004266b0.c` | **pending** | Source and all three local references are present; exact semantic comparison is pending. |
| `0x0041bb00` | `src/game/item_spawn.cpp` | 27 | 30131 | 38966 | `0041BB00_FUN_0041bb00.c` | **pending** | Source and all three local references are present; exact semantic comparison is pending. |
| `0x0041d3d0` | `src/game/laser_line.cpp` | 3 | 31150 | 41223 | `0041D3D0_FUN_0041d3d0.c` | **pending** | Source and all three local references are present; exact semantic comparison is pending. |
| `0x0041f400` | `src/game/laser_line.cpp` | 124 | 32574 | 43997 | `0041F400_FUN_0041f400.c` | **pending** | Source and all three local references are present; exact semantic comparison is pending. |
| `0x0042aa50` | `src/game/linked_pool_append.cpp` | 6 | 41300 | 59984 | `0042AA50_FUN_0042aa50.c` | **pending** | Source and all three local references are present; exact semantic comparison is pending. |
| `0x0042ab20` | `src/game/linked_pool_release.cpp` | 1 | 41336 | 60061 | `0042AB20_FUN_0042ab20.c` | **pending** | Source and all three local references are present; exact semantic comparison is pending. |
| `0x00408910` | `src/game/manager_factories.cpp` | 361 | 17267 | 10686 | `00408910_FUN_00408910.c` | **pending** | Source and all three local references are present; exact semantic comparison is pending. |
| `0x00408c90` | `src/game/manager_factories.cpp` | 358 | 17410 | 10965 | `00408C90_FUN_00408c90.c` | **pending** | Source and all three local references are present; exact semantic comparison is pending. |
| `0x0040d6b0` | `src/game/manager_factories.cpp` | 135 | 21379 | 18277 | `0040D6B0_FUN_0040d6b0.c` | **pending** | Source and all three local references are present; exact semantic comparison is pending. |
| `0x00413810` | `src/game/manager_factories.cpp` | 392 | 23156 | 26712 | `00413810_FUN_00413810.c` | **pending** | Source and all three local references are present; exact semantic comparison is pending. |
| `0x00414830` | `src/game/manager_factories.cpp` | 389 | 24081 | 28121 | `00414830_FUN_00414830.c` | **pending** | Source and all three local references are present; exact semantic comparison is pending. |
| `0x0041aed0` | `src/game/manager_factories.cpp` | 444 | 29640 | 37890 | `0041AED0_FUN_0041aed0.c` | **pending** | Source and all three local references are present; exact semantic comparison is pending. |
| `0x0041afd0` | `src/game/manager_factories.cpp` | 17 | 29682 | 38003 | `0041AFD0_FUN_0041afd0.c` | **partial** | The retail item sweep is represented by a host-side model in src/game/gameplay_final_runtime.cpp: states 5/7/8/0xA/0xB, per-type collection effects, ANM updates, and the case-5 countdown spawn remain unmodeled; only the documented motion/collection slice is supported. |
| `0x00429610` | `src/game/manager_factories.cpp` | 420 | 40389 | 58138 | `00429610_FUN_00429610.c` | **pending** | Source and all three local references are present; exact semantic comparison is pending. |
| `0x004296f0` | `src/game/manager_factories.cpp` | 220 | 40419 | 58235 | `004296F0_FUN_004296f0.c` | **pending** | Source and all three local references are present; exact semantic comparison is pending. |
| `0x0042ae60` | `src/game/manager_factories.cpp` | 247 | 41498 | 60380 | `0042AE60_FUN_0042ae60.c` | **pending** | Source and all three local references are present; exact semantic comparison is pending. |
| `0x0042b4d0` | `src/game/manager_factories.cpp` | 295 | 41826 | 61016 | `0042B4D0_FUN_0042b4d0.c` | **pending** | Source and all three local references are present; exact semantic comparison is pending. |
| `0x0043c8b0` | `src/game/manager_factories.cpp` | 161 | 55752 | 88093 | `0043C8B0_FUN_0043c8b0.c` | **pending** | Source and all three local references are present; exact semantic comparison is pending. |
| `0x0043c970` | `src/game/manager_factories.cpp` | 163 | 55771 | 88172 | `0043C970_FUN_0043c970.c` | **pending** | Source and all three local references are present; exact semantic comparison is pending. |
| `0x0044bea0` | `src/game/menu.cpp` | 1 | 67562 | 112019 | `0044BEA0_FUN_0044bea0.c` | **pending** | Source and all three local references are present; exact semantic comparison is pending. |
| `0x004224c0` | `src/game/name_entry.cpp` | 18 | 34760 | 48465 | `004224C0_FUN_004224c0.c` | **pending** | Source and all three local references are present; exact semantic comparison is pending. |
| `0x00423570` | `src/game/name_entry.cpp` | 44 | 35632 | 49870 | `00423570_FUN_00423570.c` | **pending** | Source and all three local references are present; exact semantic comparison is pending. |
| `0x00432cb0` | `src/game/name_entry.cpp` | 97 | 48451 | 72193 | `00432CB0_FUN_00432cb0.c` | **pending** | Source and all three local references are present; exact semantic comparison is pending. |
| `0x004231d0` | `src/game/pause_result_open.cpp` | 76 | 35448 | 49600 | `004231D0_FUN_004231d0.c` | **pending** | Source and all three local references are present; exact semantic comparison is pending. |
| `0x00413bc0` | `src/game/player_front_runtime.cpp` | 164 | 23299 | 27015 | `00413BC0_FUN_00413bc0.c` | **partial** | Retail field/visit order is transcribed, but sprite allocation, task reorder, orbit updates, and manager ownership are omitted by the host API; retain only the reviewed HUD slice. |
| `0x0040678e` | `src/game/player_motion.cpp` | 30 | — | — | `0040678E_FUN_0040678e.c` | **unresolved** | Exact source body is present, but IDA C, IDA asm reference export is unavailable; no semantic verdict is claimed. |
| `0x004074b0` | `src/game/player_motion.cpp` | 92 | 16393 | 8909 | `004074B0_FUN_004074b0.c` | **pending** | Source and all three local references are present; exact semantic comparison is pending. |
| `0x004076a0` | `src/game/player_motion.cpp` | 122 | 16471 | 9053 | `004076A0_FUN_004076a0.c` | **pending** | Source and all three local references are present; exact semantic comparison is pending. |
| `0x00407da0` | `src/game/player_motion.cpp` | 62 | 16773 | 9620 | `00407DA0_FUN_00407da0.c` | **pending** | Source and all three local references are present; exact semantic comparison is pending. |
| `0x00407e40` | `src/game/player_motion.cpp` | 76 | 16816 | 9681 | `00407E40_FUN_00407e40.c` | **pending** | Source and all three local references are present; exact semantic comparison is pending. |
| `0x00430ff0` | `src/game/practice_stage_menu.cpp` | 20 | 47001 | 69709 | `00430FF0_FUN_00430ff0.c` | **pending** | Source and all three local references are present; exact semantic comparison is pending. |
| `0x0042cd50` | `src/game/progress_worker.cpp` | 6 | 43043 | 63303 | `0042CD50_FUN_0042cd50.c` | **pending** | Source and all three local references are present; exact semantic comparison is pending. |
| `0x00431ba0` | `src/game/replay_browser_draw.cpp` | 5 | 47570 | 70688 | `00431BA0_FUN_00431ba0.c` | **pending** | Source and all three local references are present; exact semantic comparison is pending. |
| `0x00428f60` | `src/game/replay_runtime_bootstrap.cpp` | 4 | 40002 | 57559 | `00428F60_FUN_00428f60.c` | **pending** | Source and all three local references are present; exact semantic comparison is pending. |
| `0x004329f0` | `src/game/replay_score_draw.cpp` | 7 | 48338 | 71971 | `004329F0_FUN_004329f0.c` | **pending** | Source and all three local references are present; exact semantic comparison is pending. |
| `0x00433230` | `src/game/replay_stage_name_draw.cpp` | 6 | 48719 | 72669 | `00433230_FUN_00433230.c` | **pending** | Source and all three local references are present; exact semantic comparison is pending. |
| `0x004172e0` | `src/game/result_overlay.cpp` | 12 | 26516 | 31997 | `004172E0_FUN_004172e0.c` | **pending** | Source and all three local references are present; exact semantic comparison is pending. |
| `0x0041fdd0` | `src/game/result_screen_effects.cpp` | 16 | 32986 | 44878 | `0041FDD0_FUN_0041fdd0.c` | **pending** | Source and all three local references are present; exact semantic comparison is pending. |
| `0x00408030` | `src/game/score.cpp` | 506 | 16911 | 9847 | `00408030_FUN_00408030.c` | **pending** | Source and all three local references are present; exact semantic comparison is pending. |
| `0x00408660` | `src/game/score.cpp` | 141 | 17195 | 10413 | `00408660_FUN_00408660.c` | **pending** | Source and all three local references are present; exact semantic comparison is pending. |
| `0x004086b0` | `src/game/score.cpp` | 265 | 17208 | 10450 | `004086B0_FUN_004086b0.c` | **pending** | Source and all three local references are present; exact semantic comparison is pending. |
| `0x00408750` | `src/game/score.cpp` | 415 | 17214 | 10512 | `00408750_FUN_00408750.c` | **pending** | Source and all three local references are present; exact semantic comparison is pending. |
| `0x004088c0` | `src/game/score.cpp` | 354 | 17244 | 10638 | `004088C0_FUN_004088c0.c` | **pending** | Source and all three local references are present; exact semantic comparison is pending. |
| `0x004089c0` | `src/game/score.cpp` | 182 | 17295 | 10749 | `004089C0_FUN_004089c0.c` | **pending** | Source and all three local references are present; exact semantic comparison is pending. |
| `0x00408d60` | `src/game/score.cpp` | 20 | 17433 | 11055 | `00408D60_FUN_00408d60.c` | **partial** | Wrapper maps the score UI state, but metric_a/metric_b are hard-coded to zero and ANM tick/digit/aux/camera callbacks are unset; this cannot establish whole-function equivalence. |
| `0x004091c0` | `src/game/score.cpp` | 125 | 17651 | 11392 | `004091C0_FUN_004091c0.c` | **pending** | Source and all three local references are present; exact semantic comparison is pending. |
| `0x00409230` | `src/game/score.cpp` | 117 | 17683 | 11444 | `00409230_FUN_00409230.c` | **pending** | Source and all three local references are present; exact semantic comparison is pending. |
| `0x00409270` | `src/game/score.cpp` | 123 | 17694 | 11467 | `00409270_FUN_00409270.c` | **pending** | Source and all three local references are present; exact semantic comparison is pending. |
| `0x00409d90` | `src/game/score.cpp` | 569 | 18342 | 12413 | `00409D90_FUN_00409d90.c` | **pending** | Source and all three local references are present; exact semantic comparison is pending. |
| `0x00409e20` | `src/game/score.cpp` | 621 | 18378 | 12492 | `00409E20_FUN_00409e20.c` | **pending** | Source and all three local references are present; exact semantic comparison is pending. |
| `0x0040ac20` | `src/game/score.cpp` | 368 | 19086 | 13790 | `0040AC20_FUN_0040ac20.c` | **pending** | Source and all three local references are present; exact semantic comparison is pending. |
| `0x0040ac90` | `src/game/score.cpp` | 406 | 19129 | 13845 | `0040AC90_FUN_0040ac90.c` | **pending** | Source and all three local references are present; exact semantic comparison is pending. |
| `0x0040ace0` | `src/game/score.cpp` | 275 | 19139 | 13874 | `0040ACE0_FUN_0040ace0.c` | **pending** | Source and all three local references are present; exact semantic comparison is pending. |
| `0x0040ad20` | `src/game/score.cpp` | 389 | 19152 | 13908 | `0040AD20_FUN_0040ad20.c` | **pending** | Source and all three local references are present; exact semantic comparison is pending. |
| `0x0040b9d0` | `src/game/score.cpp` | 132 | 19807 | 15233 | `0040B9D0_FUN_0040b9d0.c` | **pending** | Source and all three local references are present; exact semantic comparison is pending. |
| `0x00412e70` | `src/game/score.cpp` | 577 | 22669 | 25695 | `00412E70_FUN_00412e70.c` | **pending** | Source and all three local references are present; exact semantic comparison is pending. |
| `0x0041be80` | `src/game/score.cpp` | 1 | 30294 | 39257 | `0041BE80_FUN_0041be80.c` | **pending** | Source and all three local references are present; exact semantic comparison is pending. |
| `0x0041beb0` | `src/game/score.cpp` | 421 | 30306 | 39284 | `0041BEB0_FUN_0041beb0.c` | **pending** | Source and all three local references are present; exact semantic comparison is pending. |
| `0x0041c030` | `src/game/score.cpp` | 428 | 30379 | 39433 | `0041C030_FUN_0041c030.c` | **pending** | Source and all three local references are present; exact semantic comparison is pending. |
| `0x0041c1c0` | `src/game/score.cpp` | 484 | 30451 | 39574 | `0041C1C0_FUN_0041c1c0.c` | **pending** | Source and all three local references are present; exact semantic comparison is pending. |
| `0x0041c5b0` | `src/game/score.cpp` | 456 | 30709 | 40030 | `0041C5B0_FUN_0041c5b0.c` | **pending** | Source and all three local references are present; exact semantic comparison is pending. |
| `0x0041c7d0` | `src/game/score.cpp` | 538 | 30805 | 40202 | `0041C7D0_FUN_0041c7d0.c` | **pending** | Source and all three local references are present; exact semantic comparison is pending. |
| `0x0041c800` | `src/game/score.cpp` | 547 | 30826 | 40235 | `0041C800_FUN_0041c800.c` | **pending** | Source and all three local references are present; exact semantic comparison is pending. |
| `0x0041f7a0` | `src/game/score.cpp` | 589 | 32710 | 44299 | `0041F7A0_FUN_0041f7a0.c` | **pending** | Source and all three local references are present; exact semantic comparison is pending. |
| `0x00426610` | `src/game/score.cpp` | 152 | 37970 | 53840 | `00426610_FUN_00426610.c` | **pending** | Source and all three local references are present; exact semantic comparison is pending. |
| `0x00426660` | `src/game/score.cpp` | 161 | 37984 | 53873 | `00426660_FUN_00426660.c` | **pending** | Source and all three local references are present; exact semantic comparison is pending. |
| `0x00428d70` | `src/game/score.cpp` | 589 | 39973 | 57399 | `00428D70_FUN_00428d70.c` | **pending** | Source and all three local references are present; exact semantic comparison is pending. |
| `0x0044a4e0` | `src/game/score.cpp` | 282 | 66302 | 109285 | `0044A4E0_FUN_0044a4e0.c` | **partial** | Source supplies only a button-buffer encoder. Retail also acquires WinMM/DirectInput state and retries input-loss; the exact poll contract is omitted. |
| `0x0044b010` | `src/game/score.cpp` | 297 | 66861 | 110451 | `0044B010_FUN_0044b010.c` | **pending** | Source and all three local references are present; exact semantic comparison is pending. |
| `0x0044b080` | `src/game/score.cpp` | 314 | 66891 | 110504 | `0044B080_FUN_0044b080.c` | **pending** | Source and all three local references are present; exact semantic comparison is pending. |
| `0x0044be20` | `src/game/score.cpp` | 341 | 67528 | 111971 | `0044BE20_FUN_0044be20.c` | **pending** | Source and all three local references are present; exact semantic comparison is pending. |
| `0x0044be70` | `src/game/score.cpp` | 327 | 67545 | 111996 | `0044BE70_FUN_0044be70.c` | **pending** | Source and all three local references are present; exact semantic comparison is pending. |
| `0x00421fa0` | `src/game/score_file.cpp` | 166 | 34453 | 47960 | `00421FA0_FUN_00421fa0.c` | **pending** | Source and all three local references are present; exact semantic comparison is pending. |
| `0x0042acb0` | `src/game/score_file.cpp` | 130 | 41409 | 60238 | `0042ACB0_FUN_0042acb0.c` | **pending** | Source and all three local references are present; exact semantic comparison is pending. |
| `0x0042b030` | `src/game/score_file.cpp` | 72 | 41543 | 60567 | `0042B030_FUN_0042b030.c` | **pending** | Source and all three local references are present; exact semantic comparison is pending. |
| `0x00431410` | `src/game/score_menu_rows.cpp` | 30 | 47223 | 70084 | `00431410_FUN_00431410.c` | **pending** | Source and all three local references are present; exact semantic comparison is pending. |
| `0x0042a6a0` | `src/game/spell_card_dispatch.cpp` | 11 | 41132 | 59653 | `0042A6A0_FUN_0042a6a0.c` | **pending** | Source and all three local references are present; exact semantic comparison is pending. |
| `0x004127a0` | `src/game/spell_timer.cpp` | 34 | 22248 | 25019 | `004127A0_FUN_004127a0.c` | **pending** | Source and all three local references are present; exact semantic comparison is pending. |
| `0x00424480` | `src/game/sprite_descriptor.cpp` | 11 | 36374 | 51216 | `00424480_FUN_00424480.c` | **pending** | Source and all three local references are present; exact semantic comparison is pending. |
| `0x0040a940` | `src/game/sprite_test_overlay.cpp` | 45 | 18964 | 13567 | `0040A940_FUN_0040a940.c` | **pending** | Source and all three local references are present; exact semantic comparison is pending. |
| `0x0042c360` | `src/game/sprite_test_overlay.cpp` | 19 | 42531 | 62422 | `0042C360_FUN_0042c360.c` | **pending** | Source and all three local references are present; exact semantic comparison is pending. |
| `0x0040c3c0` | `src/game/stage_background.cpp` | 17 | 20398 | 16234 | `0040C3C0_FUN_0040c3c0.c` | **pending** | Source and all three local references are present; exact semantic comparison is pending. |
| `0x00427960` | `src/game/stage_background.cpp` | 46 | 38945 | 55416 | `00427960_FUN_00427960.c` | **pending** | Source and all three local references are present; exact semantic comparison is pending. |
| `0x00419650` | `src/game/stage_focus_fade.cpp` | 4 | 28420 | 35342 | `00419650_FUN_00419650.c` | **pending** | Source and all three local references are present; exact semantic comparison is pending. |
| `0x00415b00` | `src/game/stage_slot_state.cpp` | 3 | 25337 | 29848 | `00415B00_FUN_00415b00.c` | **pending** | Source and all three local references are present; exact semantic comparison is pending. |
| `0x004349e0` | `src/game/stage_text.cpp` | 4 | 49872 | 74694 | `004349E0_FUN_004349e0.c` | **pending** | Source and all three local references are present; exact semantic comparison is pending. |
| `0x00434a20` | `src/game/stage_text.cpp` | 18 | 49897 | 74741 | `00434A20_FUN_00434a20.c` | **pending** | Source and all three local references are present; exact semantic comparison is pending. |
| `0x00434a80` | `src/game/stage_text.cpp` | 36 | 49937 | 74807 | `00434A80_FUN_00434a80.c` | **pending** | Source and all three local references are present; exact semantic comparison is pending. |
| `0x00418190` | `src/game/stage_update.cpp` | 64 | 27281 | 33360 | `00418190_FUN_00418190.c` | **pending** | Source and all three local references are present; exact semantic comparison is pending. |
| `0x00413980` | `src/game/task_registration.cpp` | 159 | 23213 | 26819 | `00413980_FUN_00413980.c` | **pending** | Source and all three local references are present; exact semantic comparison is pending. |
| `0x0041c120` | `src/game/task_registration.cpp` | 132 | 30416 | 39523 | `0041C120_FUN_0041c120.c` | **pending** | Source and all three local references are present; exact semantic comparison is pending. |
| `0x0042caa0` | `src/game/task_registration.cpp` | 233 | 42875 | 63052 | `0042CAA0_FUN_0042caa0.c` | **pending** | Source and all three local references are present; exact semantic comparison is pending. |
| `0x0042cdf0` | `src/game/title_menu_runtime.cpp` | 3 | 43074 | 63375 | `0042CDF0_FUN_0042cdf0.c` | **pending** | Source and all three local references are present; exact semantic comparison is pending. |
| `0x00426cf0` | `src/game/trigger_activation.cpp` | 18 | 38294 | 54449 | `00426CF0_FUN_00426cf0.c` | **pending** | Source and all three local references are present; exact semantic comparison is pending. |
| `0x0044bc10` | `src/math/angle.cpp` | 27 | 67466 | 111748 | `0044BC10_FUN_0044bc10.c` | **pending** | Source and all three local references are present; exact semantic comparison is pending. |
| `0x0044b9e0` | `src/math/rng.cpp` | 35 | 67396 | 111526 | `0044B9E0_FUN_0044b9e0.c` | **pending** | Source and all three local references are present; exact semantic comparison is pending. |
| `0x0044ba80` | `src/math/rng.cpp` | 45 | 67410 | 111589 | `0044BA80_FUN_0044ba80.c` | **pending** | Source and all three local references are present; exact semantic comparison is pending. |
| `0x0044bb20` | `src/math/rng.cpp` | 59 | 67434 | 111647 | `0044BB20_FUN_0044bb20.c` | **pending** | Source and all three local references are present; exact semantic comparison is pending. |
| `0x0044bb90` | `src/math/rng.cpp` | 64 | 67450 | 111697 | `0044BB90_FUN_0044bb90.c` | **pending** | Source and all three local references are present; exact semantic comparison is pending. |
| `0x00404ed0` | `src/math/timer.cpp` | 2 | 14708 | 5452 | `00404ED0_FUN_00404ed0.c` | **pending** | Source and all three local references are present; exact semantic comparison is pending. |
| `0x00428dd0` | `src/math/timer.cpp` | 26 | 39979 | 57441 | `00428DD0_FUN_00428dd0.c` | **pending** | Source and all three local references are present; exact semantic comparison is pending. |
| `0x0042c620` | `src/math/timer.cpp` | 44 | 42638 | 62626 | `0042C620_FUN_0042c620.c` | **pending** | Source and all three local references are present; exact semantic comparison is pending. |
| `0x0044bf40` | `src/math/timer.cpp` | 26 | 67619 | 112119 | `0044BF40_FUN_0044bf40.c` | **pending** | Source and all three local references are present; exact semantic comparison is pending. |
| `0x00421b90` | `src/math/vector3_cross.cpp` | 1 | 34232 | 47523 | `00421B90_FUN_00421b90.c` | **pending** | Source and all three local references are present; exact semantic comparison is pending. |
| `0x004054b0` | `src/platform/all_source_runtime.cpp` | 205 | 14919 | 5994 | `004054B0_FUN_004054b0.c` | **pending** | Source and all three local references are present; exact semantic comparison is pending. |
| `0x0044c150` | `src/platform/all_source_runtime.cpp` | 184 | 67689 | 112383 | `0044C150_FUN_0044c150.c` | **pending** | Source and all three local references are present; exact semantic comparison is pending. |
| `0x00437db0` | `src/platform/font_texture_draw.cpp` | 42 | 52492 | 80571 | `00437DB0_FUN_00437db0.c` | **pending** | Source and all three local references are present; exact semantic comparison is pending. |
| `0x00437fe0` | `src/platform/font_texture_draw.cpp` | 50 | 52644 | 80812 | `00437FE0_FUN_00437fe0.c` | **pending** | Source and all three local references are present; exact semantic comparison is pending. |
| `0x00436a30` | `src/platform/gdi_font_cache.cpp` | 7 | 51752 | 78573 | `00436A30_FUN_00436a30.c` | **pending** | Source and all three local references are present; exact semantic comparison is pending. |
| `0x00437d10` | `src/platform/gdi_font_cache.cpp` | 11 | 52471 | 80512 | `00437D10_FUN_00437d10.c` | **pending** | Source and all three local references are present; exact semantic comparison is pending. |
| `0x0044c7e0` | `src/platform/joystick_property.cpp` | 18 | 67903 | 112920 | `0044C7E0_FUN_0044c7e0.c` | **partial** | Source reconstructs the conventional DirectInput property call, while the local retail decompile is explicitly corrupted; exact ABI/vtable and error-path equivalence remains unproven. |
| `0x00436210` | `src/platform/memory_file.cpp` | 79 | 51332 | 77602 | `00436210_FUN_00436210.c` | **pending** | Source and all three local references are present; exact semantic comparison is pending. |
| `0x00436260` | `src/platform/memory_file.cpp` | 41 | 51364 | 77643 | `00436260_FUN_00436260.c` | **pending** | Source and all three local references are present; exact semantic comparison is pending. |
| `0x004362b0` | `src/platform/memory_file.cpp` | 53 | 51382 | 77670 | `004362B0_FUN_004362b0.c` | **pending** | Source and all three local references are present; exact semantic comparison is pending. |
| `0x00436330` | `src/platform/memory_file.cpp` | 67 | 51410 | 77717 | `00436330_FUN_00436330.c` | **pending** | Source and all three local references are present; exact semantic comparison is pending. |
| `0x00436370` | `src/platform/memory_file.cpp` | 162 | 51424 | 77743 | `None` | **unresolved** | Exact source body is present, but Ghidra reference export is unavailable; no semantic verdict is claimed. |
| `0x004363c0` | `src/platform/memory_file.cpp` | 121 | 51439 | 77784 | `004363C0_FUN_004363c0.c` | **pending** | Source and all three local references are present; exact semantic comparison is pending. |
| `0x00436430` | `src/platform/memory_file.cpp` | 135 | 51471 | 77842 | `00436430_FUN_00436430.c` | **pending** | Source and all three local references are present; exact semantic comparison is pending. |
| `0x00436460` | `src/platform/memory_file.cpp` | 146 | 51484 | 77869 | `None` | **unresolved** | Exact source body is present, but Ghidra reference export is unavailable; no semantic verdict is claimed. |
| `0x004364d0` | `src/platform/memory_file.cpp` | 167 | 51513 | 77935 | `None` | **unresolved** | Exact source body is present, but Ghidra reference export is unavailable; no semantic verdict is claimed. |
| `0x004364e0` | `src/platform/memory_file.cpp` | 172 | 51519 | 77946 | `None` | **unresolved** | Exact source body is present, but Ghidra reference export is unavailable; no semantic verdict is claimed. |
| `0x0043d250` | `src/platform/memory_file.cpp` | 4 | 56215 | 89053 | `0043D250_FUN_0043d250.c` | **pending** | Source and all three local references are present; exact semantic comparison is pending. |
| `0x0043d390` | `src/platform/memory_file.cpp` | 209 | 56289 | 89233 | `0043D390_FUN_0043d390.c` | **pending** | Source and all three local references are present; exact semantic comparison is pending. |
| `0x0043a730` | `src/platform/midi_sequencer.cpp` | 32 | 54321 | 84867 | `0043A730_FUN_0043a730.c` | **pending** | Source and all three local references are present; exact semantic comparison is pending. |
| `0x0043aad0` | `src/platform/midi_sequencer.cpp` | 70 | 54431 | 85163 | `0043AAD0_FUN_0043aad0.c` | **pending** | Source and all three local references are present; exact semantic comparison is pending. |
| `0x0043ace0` | `src/platform/midi_sequencer.cpp` | 46 | 54515 | 85357 | `0043ACE0_FUN_0043ace0.c` | **pending** | Source and all three local references are present; exact semantic comparison is pending. |
| `0x0043af30` | `src/platform/midi_sequencer.cpp` | 125 | 54617 | 85589 | `0043AF30_FUN_0043af30.c` | **pending** | Source and all three local references are present; exact semantic comparison is pending. |
| `0x00436570` | `src/platform/process.cpp` | 4 | 51568 | 78032 | `00436570_FUN_00436570.c` | **pending** | Source and all three local references are present; exact semantic comparison is pending. |
| `0x0044bd10` | `src/platform/process.cpp` | 87 | — | — | `0044BD10_FUN_0044bd10.c` | **unresolved** | Exact source body is present, but IDA C, IDA asm reference export is unavailable; no semantic verdict is claimed. |
| `0x0044c100` | `src/platform/process.cpp` | 56 | — | — | `0044C100_FUN_0044c100.c` | **unresolved** | Exact source body is present, but IDA C, IDA asm reference export is unavailable; no semantic verdict is claimed. |
| `0x0044c130` | `src/platform/process.cpp` | 33 | — | — | `0044C130_FUN_0044c130.c` | **unresolved** | Exact source body is present, but IDA C, IDA asm reference export is unavailable; no semantic verdict is claimed. |
| `0x0044d5b0` | `src/platform/process.cpp` | 73 | 68651 | 114481 | `0044D5B0_FUN_0044d5b0.c` | **pending** | Source and all three local references are present; exact semantic comparison is pending. |
| `0x00436680` | `src/platform/resource_file.cpp` | 27 | 51605 | 78144 | `00436680_FUN_00436680.c` | **pending** | Source and all three local references are present; exact semantic comparison is pending. |
| `0x004366c0` | `src/platform/resource_file.cpp` | 33 | 51625 | 78173 | `004366C0_FUN_004366c0.c` | **pending** | Source and all three local references are present; exact semantic comparison is pending. |
| `0x00436ca0` | `src/platform/resource_file.cpp` | 18 | 51857 | 78815 | `00436CA0_FUN_00436ca0.c` | **pending** | Source and all three local references are present; exact semantic comparison is pending. |
| `0x0043a910` | `src/platform/sound_commands.cpp` | 111 | 54337 | 84983 | `0043A910_FUN_0043a910.c` | **pending** | Source and all three local references are present; exact semantic comparison is pending. |
| `0x0043d120` | `src/platform/sound_commands.cpp` | 93 | 56114 | 88915 | `0043D120_FUN_0043d120.c` | **pending** | Source and all three local references are present; exact semantic comparison is pending. |
| `0x0043d7d0` | `src/platform/sound_commands.cpp` | 238 | 56439 | 89673 | `0043D7D0_FUN_0043d7d0.c` | **pending** | Source and all three local references are present; exact semantic comparison is pending. |
| `0x0043d950` | `src/platform/sound_commands.cpp` | 215 | 56485 | 89826 | `0043D950_FUN_0043d950.c` | **pending** | Source and all three local references are present; exact semantic comparison is pending. |
| `0x0043ddf0` | `src/platform/sound_commands.cpp` | 17 | 56698 | 90272 | `0043DDF0_FUN_0043ddf0.c` | **pending** | Source and all three local references are present; exact semantic comparison is pending. |
| `0x0044cbf0` | `src/platform/sound_commands.cpp` | 123 | 68091 | 113340 | `0044CBF0_FUN_0044cbf0.c` | **pending** | Source and all three local references are present; exact semantic comparison is pending. |
| `0x0044cf20` | `src/platform/sound_commands.cpp` | 146 | 68251 | 113684 | `0044CF20_FUN_0044cf20.c` | **pending** | Source and all three local references are present; exact semantic comparison is pending. |
| `0x0044d110` | `src/platform/sound_commands.cpp` | 170 | 68375 | 113918 | `0044D110_FUN_0044d110.c` | **pending** | Source and all three local references are present; exact semantic comparison is pending. |
| `0x0044dad0` | `src/platform/sound_commands.cpp` | 200 | 68877 | 115075 | `0044DAD0_FUN_0044dad0.c` | **pending** | Source and all three local references are present; exact semantic comparison is pending. |
| `0x0043cd30` | `src/platform/sound_device_init.cpp` | 38 | 55942 | 88553 | `0043CD30_FUN_0043cd30.c` | **pending** | Source and all three local references are present; exact semantic comparison is pending. |
| `0x00421e00` | `src/platform/sound_fade.cpp` | 21 | 34344 | 47785 | `00421E00_FUN_00421e00.c` | **pending** | Source and all three local references are present; exact semantic comparison is pending. |
| `0x0044d440` | `src/platform/sound_stream_start.cpp` | 4 | 68566 | 114301 | `0044D440_FUN_0044d440.c` | **pending** | Source and all three local references are present; exact semantic comparison is pending. |
| `0x0043cc40` | `src/platform/sound_worker.cpp` | 4 | 55900 | 88449 | `0043CC40_FUN_0043cc40.c` | **pending** | Source and all three local references are present; exact semantic comparison is pending. |
| `0x0044c1c0` | `src/platform/worker_start.cpp` | 3 | 67716 | 112432 | `0044C1C0_FUN_0044c1c0.c` | **pending** | Source and all three local references are present; exact semantic comparison is pending. |
| `0x004136c0` | `src/render/animation_slot.cpp` | 1 | 23079 | 26574 | `004136C0_FUN_004136c0.c` | **pending** | Source and all three local references are present; exact semantic comparison is pending. |
| `0x004470c0` | `src/render/anm_archive.cpp` | 6 | 63624 | 103570 | `004470C0_FUN_004470c0.c` | **pending** | Source and all three local references are present; exact semantic comparison is pending. |
| `0x004472e0` | `src/render/anm_archive.cpp` | 40 | 63747 | 103793 | `004472E0_FUN_004472e0.c` | **pending** | Source and all three local references are present; exact semantic comparison is pending. |
| `0x00421300` | `src/render/anm_handle_release.cpp` | 29 | 33809 | 46804 | `00421300_FUN_00421300.c` | **pending** | Source and all three local references are present; exact semantic comparison is pending. |
| `0x00409e50` | `src/render/anm_propagate.cpp` | 19 | 18396 | 12517 | `00409E50_FUN_00409e50.c` | **pending** | Source and all three local references are present; exact semantic comparison is pending. |
| `0x0042c770` | `src/render/anm_propagate.cpp` | 30 | 42722 | 62758 | `0042C770_FUN_0042c770.c` | **pending** | Source and all three local references are present; exact semantic comparison is pending. |
| `0x004451c0` | `src/render/anm_vm_draw_dispatch.cpp` | 13 | 61872 | 100662 | `004451C0_FUN_004451c0.c` | **pending** | Source and all three local references are present; exact semantic comparison is pending. |
| `0x0043c1a0` | `src/render/default_viewport.cpp` | 13 | 55386 | 87331 | `0043C1A0_FUN_0043c1a0.c` | **pending** | Source and all three local references are present; exact semantic comparison is pending. |
| `0x00444b10` | `src/render/edge_strips.cpp` | 9 | 61692 | 100003 | `00444B10_FUN_00444b10.c` | **pending** | Source and all three local references are present; exact semantic comparison is pending. |
| `0x00444be0` | `src/render/edge_strips.cpp` | 50 | 61749 | 100099 | `00444BE0_FUN_00444be0.c` | **pending** | Source and all three local references are present; exact semantic comparison is pending. |
| `0x00445620` | `src/render/effect_ring_update.cpp` | 25 | 62018 | 101041 | `00445620_FUN_00445620.c` | **pending** | Source and all three local references are present; exact semantic comparison is pending. |
| `0x00442670` | `src/render/final_quad_pipeline.cpp` | 6 | 60226 | 97070 | `00442670_FUN_00442670.c` | **pending** | Source and all three local references are present; exact semantic comparison is pending. |
| `0x00420cd0` | `src/render/fog_disable.cpp` | 3 | 33586 | 46259 | `00420CD0_FUN_00420cd0.c` | **pending** | Source and all three local references are present; exact semantic comparison is pending. |
| `0x00437160` | `src/render/image_alpha_transform.cpp` | 5 | 52094 | 79308 | `00437160_FUN_00437160.c` | **pending** | Source and all three local references are present; exact semantic comparison is pending. |
| `0x0043bfa0` | `src/render/texture_stage_reset.cpp` | 17 | 55309 | 87148 | `0043BFA0_FUN_0043bfa0.c` | **pending** | Source and all three local references are present; exact semantic comparison is pending. |
| `0x004465b0` | `src/render/transparent_pixel_fill_locked.cpp` | 13 | 63020 | 102405 | `004465B0_FUN_004465b0.c` | **pending** | Source and all three local references are present; exact semantic comparison is pending. |
| `0x00412a00` | `src/script/ecl_vm.cpp` | 215 | 22362 | 25198 | `00412A00_FUN_00412a00.c` | **pending** | Source and all three local references are present; exact semantic comparison is pending. |
| `0x00412a10` | `src/script/ecl_vm.cpp` | 246 | 22372 | 25210 | `00412A10_FUN_00412a10.c` | **pending** | Source and all three local references are present; exact semantic comparison is pending. |
| `0x0044fd10` | `src/script/ecl_vm_children.cpp` | 130 | 70775 | 118005 | `0044FD10_FUN_0044fd10.c` | **pending** | Source and all three local references are present; exact semantic comparison is pending. |
| `0x00450470` | `src/script/final_script_runtime.cpp` | 8 | 71273 | 118900 | `00450470_FUN_00450470.c` | **pending** | Source and all three local references are present; exact semantic comparison is pending. |
| `0x00450700` | `src/script/final_script_runtime.cpp` | 1 | 71389 | 119210 | `00450700_FUN_00450700.c` | **pending** | Source and all three local references are present; exact semantic comparison is pending. |
| `0x00403850` | `src/script/stage_ecl_load.cpp` | 14 | 13503 | 3426 | `00403850_FUN_00403850.c` | **pending** | Source and all three local references are present; exact semantic comparison is pending. |
| `0x00418150` | `src/util/heap.cpp` | 44 | 27271 | 33330 | `00418150_FUN_00418150.c` | **pending** | Source and all three local references are present; exact semantic comparison is pending. |
| `0x0042cdb0` | `src/util/heap.cpp` | 55 | 43064 | 63345 | `0042CDB0_FUN_0042cdb0.c` | **pending** | Source and all three local references are present; exact semantic comparison is pending. |
| `0x00435220` | `src/util/heap.cpp` | 76 | 50354 | 75737 | `00435220_FUN_00435220.c` | **pending** | Source and all three local references are present; exact semantic comparison is pending. |
| `0x00435250` | `src/util/heap.cpp` | 35 | 50365 | 75775 | `00435250_FUN_00435250.c` | **pending** | Source and all three local references are present; exact semantic comparison is pending. |
| `0x004352c0` | `src/util/heap.cpp` | 15 | — | — | `None` | **unresolved** | Exact source body is present, but IDA C, IDA asm, Ghidra reference export is unavailable; no semantic verdict is claimed. |
| `0x004381f0` | `src/util/heap.cpp` | 66 | — | — | `004381F0_FUN_004381f0.c` | **unresolved** | Exact source body is present, but IDA C, IDA asm reference export is unavailable; no semantic verdict is claimed. |
| `0x00438250` | `src/util/heap.cpp` | 226 | 52788 | 81068 | `None` | **unresolved** | Exact source body is present, but Ghidra reference export is unavailable; no semantic verdict is claimed. |
| `0x00438260` | `src/util/heap.cpp` | 151 | 52794 | 81078 | `00438260_FUN_00438260.c` | **pending** | Source and all three local references are present; exact semantic comparison is pending. |
| `0x00438350` | `src/util/heap.cpp` | 90 | 52862 | 81217 | `00438350_FUN_00438350.c` | **pending** | Source and all three local references are present; exact semantic comparison is pending. |
| `0x00438380` | `src/util/heap.cpp` | 232 | 52868 | 81248 | `00438380_FUN_00438380.c` | **pending** | Source and all three local references are present; exact semantic comparison is pending. |
| `0x00438420` | `src/util/heap.cpp` | 102 | 52903 | 81330 | `00438420_FUN_00438420.c` | **pending** | Source and all three local references are present; exact semantic comparison is pending. |
| `0x00438510` | `src/util/heap.cpp` | 197 | 52971 | 81475 | `00438510_FUN_00438510.c` | **pending** | Source and all three local references are present; exact semantic comparison is pending. |
| `0x00438590` | `src/util/heap.cpp` | 215 | 53012 | 81555 | `00438590_FUN_00438590.c` | **pending** | Source and all three local references are present; exact semantic comparison is pending. |
| `0x00438680` | `src/util/heap.cpp` | 269 | — | — | `None` | **unresolved** | Exact source body is present, but IDA C, IDA asm, Ghidra reference export is unavailable; no semantic verdict is claimed. |
| `0x00438690` | `src/util/heap.cpp` | 24 | — | — | `None` | **unresolved** | Exact source body is present, but IDA C, IDA asm, Ghidra reference export is unavailable; no semantic verdict is claimed. |
| `0x004386a0` | `src/util/heap.cpp` | 30 | 53081 | 81699 | `None` | **unresolved** | Exact source body is present, but Ghidra reference export is unavailable; no semantic verdict is claimed. |
| `0x004386b0` | `src/util/heap.cpp` | 285 | 53087 | 81710 | `004386B0_FUN_004386b0.c` | **pending** | Source and all three local references are present; exact semantic comparison is pending. |
| `0x0043874c` | `src/util/heap.cpp` | 287 | — | — | `0043874C_FUN_0043874c.c` | **unresolved** | Exact source body is present, but IDA C, IDA asm reference export is unavailable; no semantic verdict is claimed. |
| `0x00438800` | `src/util/heap.cpp` | 261 | — | — | `None` | **unresolved** | Exact source body is present, but IDA C, IDA asm, Ghidra reference export is unavailable; no semantic verdict is claimed. |
| `0x00438840` | `src/util/heap.cpp` | 19 | — | — | `None` | **unresolved** | Exact source body is present, but IDA C, IDA asm, Ghidra reference export is unavailable; no semantic verdict is claimed. |

## Partial findings

`0x0042B1E0` is materially different in its save layout: retail has seven fixed CR records, per-record/trailer checksums, and a fixed stream header; the host callback loop and flat checksum cannot claim save-file equivalence.

`0x0041AFD0` is a documented partial item-sweep model: state 5 and collection side effects, ANM updates, and the countdown spawn are omitted. Only its motion/collection slice is supported.

`0x00413BC0` (`InitializeFront`) has a well-supported task/ANM visit order, life slots, power digits, and registration ordering. The source explicitly leaves sprite allocation/release, one draw, task-list reorder, and orbit/manager ownership outside its host API.

`0x00408D60` (`PlayerScore_Update`) maps many retail offsets correctly, but its score metrics are forced to zero and animation callbacks are null. It is a useful state adapter, not a whole retail update.

`0x0044A4E0` is represented by a 32-button encoder while the retail entry performs device acquisition and DirectInput/WinMM retry handling. Only the encoding slice is supported.

`0x0044C7E0` is a conventional-ABI reconstruction against a corrupted local retail decompile. Its property block and HRESULT handling are plausible, but the exact retail call ABI remains open.

## Pending evidence inventory

- `0x0044dbf0` `src/game/archive_cursor_open.cpp`: references available at IDA C 68932, IDA asm 115194, and `0044DBF0_FUN_0044dbf0.c`; function-specific comparison still pending; source marker line 1.
- `0x0043c2c0` `src/game/ascii_overlay_callbacks.cpp`: references available at IDA C 55434, IDA asm 87451, and `0043C2C0_FUN_0043c2c0.c`; function-specific comparison still pending; source marker line 52.
- `0x0043c410` `src/game/ascii_overlay_callbacks.cpp`: references available at IDA C 55506, IDA asm 87595, and `0043C410_FUN_0043c410.c`; function-specific comparison still pending; source marker line 45.
- `0x00447ae0` `src/game/ascii_overlay_callbacks.cpp`: references available at IDA C 64179, IDA asm 104669, and `00447AE0_FUN_00447ae0.c`; function-specific comparison still pending; source marker line 23.
- `0x0040e5f0` `src/game/boss_overlays.cpp`: references available at IDA C 22156, IDA asm 19622, and `0040E5F0_FUN_0040e5f0.c`; function-specific comparison still pending; source marker line 35.
- `0x0041d7c0` `src/game/boss_overlays.cpp`: references available at IDA C 31303, IDA asm 41573, and `0041D7C0_FUN_0041d7c0.c`; function-specific comparison still pending; source marker line 4.
- `0x0040ae70` `src/game/bullet.cpp`: references available at IDA C 19213, IDA asm 14052, and `0040AE70_FUN_0040ae70.c`; function-specific comparison still pending; source marker line 6.
- `0x0040af00` `src/game/bullet.cpp`: references available at IDA C 19247, IDA asm 14101, and `0040AF00_FUN_0040af00.c`; function-specific comparison still pending; source marker line 5.
- `0x0040af90` `src/game/bullet.cpp`: references available at IDA C 19279, IDA asm 14156, and `0040AF90_FUN_0040af90.c`; function-specific comparison still pending; source marker line 5.
- `0x0040b250` `src/game/bullet.cpp`: references available at IDA C 19455, IDA asm 14470, and `0040B250_FUN_0040b250.c`; function-specific comparison still pending; source marker line 151.
- `0x0040c6e0` `src/game/bullet.cpp`: references available at IDA C 20553, IDA asm 16599, and `0040C6E0_FUN_0040c6e0.c`; function-specific comparison still pending; source marker line 175.
- `0x0040cc70` `src/game/bullet.cpp`: references available at IDA C 20793, IDA asm 17193, and `0040CC70_FUN_0040cc70.c`; function-specific comparison still pending; source marker line 4.
- `0x0040cea0` `src/game/bullet.cpp`: references available at IDA C 20884, IDA asm 17422, and `0040CEA0_FUN_0040cea0.c`; function-specific comparison still pending; source marker line 140.
- `0x0040cf40` `src/game/bullet.cpp`: references available at IDA C 20925, IDA asm 17501, and `0040CF40_FUN_0040cf40.c`; function-specific comparison still pending; source marker line 108.
- `0x0040cf60` `src/game/bullet.cpp`: references available at IDA C 20933, IDA asm 17518, and `0040CF60_FUN_0040cf60.c`; function-specific comparison still pending; source marker line 119.
- `0x0040cf90` `src/game/bullet.cpp`: references available at IDA C 20957, IDA asm 17548, and `0040CF90_FUN_0040cf90.c`; function-specific comparison still pending; source marker line 128.
- `0x0040cfb0` `src/game/bullet.cpp`: references available at IDA C 20974, IDA asm 17572, and `0040CFB0_FUN_0040cfb0.c`; function-specific comparison still pending; source marker line 3.
- `0x0040d680` `src/game/bullet.cpp`: references available at IDA C 21364, IDA asm 18258, and `0040D680_FUN_0040d680.c`; function-specific comparison still pending; source marker line 164.
- `0x0040d830` `src/game/bullet.cpp`: references available at IDA C 21486, IDA asm 18470, and `0040D830_FUN_0040d830.c`; function-specific comparison still pending; source marker line 3.
- `0x0040dc80` `src/game/bullet.cpp`: references available at IDA C 21733, IDA asm 18809, and `0040DC80_FUN_0040dc80.c`; function-specific comparison still pending; source marker line 4.
- `0x0044bc70` `src/game/bullet.cpp`: references available at IDA C 67497, IDA asm 111799, and `0044BC70_FUN_0044bc70.c`; function-specific comparison still pending; source marker line 49.
- `0x0044c2a0` `src/game/bullet.cpp`: references available at IDA C 67730, IDA asm 112517, and `0044C2A0_FUN_0044c2a0.c`; function-specific comparison still pending; source marker line 67.
- `0x0040b3a0` `src/game/bullet_anim_release.cpp`: references available at IDA C 19470, IDA asm 14587, and `0040B3A0_FUN_0040b3a0.c`; function-specific comparison still pending; source marker line 17.
- `0x00428280` `src/game/effect_pool_update.cpp`: references available at IDA C 39396, IDA asm 56343, and `00428280_FUN_00428280.c`; function-specific comparison still pending; source marker line 3.
- `0x0040ba90` `src/game/ending_text.cpp`: references available at IDA C 19872, IDA asm 15337, and `0040BA90_FUN_0040ba90.c`; function-specific comparison still pending; source marker line 27.
- `0x004073e0` `src/game/enemy_grid_scan.cpp`: references available at IDA C 16354, IDA asm 8813, and `004073E0_FUN_004073e0.c`; function-specific comparison still pending; source marker line 13.
- `0x00407560` `src/game/enemy_motion_steps.cpp`: references available at IDA C 16428, IDA asm 8965, and `00407560_FUN_00407560.c`; function-specific comparison still pending; source marker line 61.
- `0x00407780` `src/game/enemy_motion_steps.cpp`: references available at IDA C 16513, IDA asm 9123, and `00407780_FUN_00407780.c`; function-specific comparison still pending; source marker line 108.
- `0x004078e0` `src/game/enemy_motion_steps.cpp`: references available at IDA C 16577, IDA asm 9229, and `004078E0_FUN_004078e0.c`; function-specific comparison still pending; source marker line 108.
- `0x00407a30` `src/game/enemy_motion_steps.cpp`: references available at IDA C 16643, IDA asm 9334, and `00407A30_FUN_00407a30.c`; function-specific comparison still pending; source marker line 203.
- `0x00407be0` `src/game/enemy_motion_steps.cpp`: references available at IDA C 16722, IDA asm 9471, and `00407BE0_FUN_00407be0.c`; function-specific comparison still pending; source marker line 155.
- `0x00407ef0` `src/game/enemy_motion_steps.cpp`: references available at IDA C 16857, IDA asm 9742, and `00407EF0_FUN_00407ef0.c`; function-specific comparison still pending; source marker line 81.
- `0x00401de0` `src/game/entity.cpp`: references available at IDA C 12415, IDA asm 1227, and `00401DE0_FUN_00401de0.c`; function-specific comparison still pending; source marker line 3.
- `0x00401ff0` `src/game/entity.cpp`: references available at IDA C 12535, IDA asm 1433, and `00401FF0_FUN_00401ff0.c`; function-specific comparison still pending; source marker line 3.
- `0x00402050` `src/game/entity.cpp`: references available at IDA C 12543, IDA asm 1472, and `00402050_FUN_00402050.c`; function-specific comparison still pending; source marker line 3.
- `0x00405d00` `src/game/entity.cpp`: references available at IDA C 15368, IDA asm 6855, and `00405D00_FUN_00405d00.c`; function-specific comparison still pending; source marker line 27.
- `0x00405de0` `src/game/entity.cpp`: references available at IDA C 15395, IDA asm 6928, and `00405DE0_FUN_00405de0.c`; function-specific comparison still pending; source marker line 86.
- `0x00406160` `src/game/entity.cpp`: references available at IDA C 15531, IDA asm 7261, and `00406160_FUN_00406160.c`; function-specific comparison still pending; source marker line 47.
- `0x004061d0` `src/game/entity.cpp`: references available at IDA C 15549, IDA asm 7312, and `004061D0_FUN_004061d0.c`; function-specific comparison still pending; source marker line 54.
- `0x0041ad60` `src/game/entity.cpp`: references available at IDA C 29576, IDA asm 37757, and `0041AD60_FUN_0041ad60.c`; function-specific comparison still pending; source marker line 74.
- `0x00438a30` `src/game/entity.cpp`: references available at IDA C 53203, IDA asm 82103, and `00438A30_FUN_00438a30.c`; function-specific comparison still pending; source marker line 3.
- `0x0042b780` `src/game/floating_text_draw.cpp`: references available at IDA C 41932, IDA asm 61292, and `0042B780_FUN_0042b780.c`; function-specific comparison still pending; source marker line 34.
- `0x00418c40` `src/game/game_config_defaults.cpp`: references available at IDA C 27851, IDA asm 34428, and `00418C40_FUN_00418c40.c`; function-specific comparison still pending; source marker line 17.
- `0x004218d0` `src/game/game_mode_switch.cpp`: references available at IDA C 34105, IDA asm 47307, and `004218D0_FUN_004218d0.c`; function-specific comparison still pending; source marker line 5.
- `0x00401000` `src/game/game_thread.cpp`: references available at IDA C 11786, IDA asm 42, and `00401000_FUN_00401000.c`; function-specific comparison still pending; source marker line 3.
- `0x00401110` `src/game/game_thread.cpp`: references available at IDA C 11830, IDA asm 113, and `00401110_FUN_00401110.c`; function-specific comparison still pending; source marker line 3.
- `0x00401260` `src/game/game_thread.cpp`: references available at IDA C 11896, IDA asm 216, and `00401260_FUN_00401260.c`; function-specific comparison still pending; source marker line 3.
- `0x00401440` `src/game/game_thread.cpp`: references available at IDA C 11980, IDA asm 373, and `00401440_FUN_00401440.c`; function-specific comparison still pending; source marker line 4.
- `0x00401760` `src/game/game_thread.cpp`: references available at IDA C 12128, IDA asm 698, and `00401760_FUN_00401760.c`; function-specific comparison still pending; source marker line 118.
- `0x00401a50` `src/game/game_thread.cpp`: references available at IDA C 12266, IDA asm 922, and `00401A50_FUN_00401a50.c`; function-specific comparison still pending; source marker line 124.
- `0x00447bb0` `src/game/game_thread_text_draw.cpp`: references available at IDA C 64207, IDA asm 104753, and `00447BB0_FUN_00447bb0.c`; function-specific comparison still pending; source marker line 59.
- `0x004266b0` `src/game/item_field_contact.cpp`: references available at IDA C 37998, IDA asm 53906, and `004266B0_FUN_004266b0.c`; function-specific comparison still pending; source marker line 13.
- `0x0041bb00` `src/game/item_spawn.cpp`: references available at IDA C 30131, IDA asm 38966, and `0041BB00_FUN_0041bb00.c`; function-specific comparison still pending; source marker line 27.
- `0x0041d3d0` `src/game/laser_line.cpp`: references available at IDA C 31150, IDA asm 41223, and `0041D3D0_FUN_0041d3d0.c`; function-specific comparison still pending; source marker line 3.
- `0x0041f400` `src/game/laser_line.cpp`: references available at IDA C 32574, IDA asm 43997, and `0041F400_FUN_0041f400.c`; function-specific comparison still pending; source marker line 124.
- `0x0042aa50` `src/game/linked_pool_append.cpp`: references available at IDA C 41300, IDA asm 59984, and `0042AA50_FUN_0042aa50.c`; function-specific comparison still pending; source marker line 6.
- `0x0042ab20` `src/game/linked_pool_release.cpp`: references available at IDA C 41336, IDA asm 60061, and `0042AB20_FUN_0042ab20.c`; function-specific comparison still pending; source marker line 1.
- `0x00408910` `src/game/manager_factories.cpp`: references available at IDA C 17267, IDA asm 10686, and `00408910_FUN_00408910.c`; function-specific comparison still pending; source marker line 361.
- `0x00408c90` `src/game/manager_factories.cpp`: references available at IDA C 17410, IDA asm 10965, and `00408C90_FUN_00408c90.c`; function-specific comparison still pending; source marker line 358.
- `0x0040d6b0` `src/game/manager_factories.cpp`: references available at IDA C 21379, IDA asm 18277, and `0040D6B0_FUN_0040d6b0.c`; function-specific comparison still pending; source marker line 135.
- `0x00413810` `src/game/manager_factories.cpp`: references available at IDA C 23156, IDA asm 26712, and `00413810_FUN_00413810.c`; function-specific comparison still pending; source marker line 392.
- `0x00414830` `src/game/manager_factories.cpp`: references available at IDA C 24081, IDA asm 28121, and `00414830_FUN_00414830.c`; function-specific comparison still pending; source marker line 389.
- `0x0041aed0` `src/game/manager_factories.cpp`: references available at IDA C 29640, IDA asm 37890, and `0041AED0_FUN_0041aed0.c`; function-specific comparison still pending; source marker line 444.
- `0x00429610` `src/game/manager_factories.cpp`: references available at IDA C 40389, IDA asm 58138, and `00429610_FUN_00429610.c`; function-specific comparison still pending; source marker line 420.
- `0x004296f0` `src/game/manager_factories.cpp`: references available at IDA C 40419, IDA asm 58235, and `004296F0_FUN_004296f0.c`; function-specific comparison still pending; source marker line 220.
- `0x0042ae60` `src/game/manager_factories.cpp`: references available at IDA C 41498, IDA asm 60380, and `0042AE60_FUN_0042ae60.c`; function-specific comparison still pending; source marker line 247.
- `0x0042b4d0` `src/game/manager_factories.cpp`: references available at IDA C 41826, IDA asm 61016, and `0042B4D0_FUN_0042b4d0.c`; function-specific comparison still pending; source marker line 295.
- `0x0043c8b0` `src/game/manager_factories.cpp`: references available at IDA C 55752, IDA asm 88093, and `0043C8B0_FUN_0043c8b0.c`; function-specific comparison still pending; source marker line 161.
- `0x0043c970` `src/game/manager_factories.cpp`: references available at IDA C 55771, IDA asm 88172, and `0043C970_FUN_0043c970.c`; function-specific comparison still pending; source marker line 163.
- `0x0044bea0` `src/game/menu.cpp`: references available at IDA C 67562, IDA asm 112019, and `0044BEA0_FUN_0044bea0.c`; function-specific comparison still pending; source marker line 1.
- `0x004224c0` `src/game/name_entry.cpp`: references available at IDA C 34760, IDA asm 48465, and `004224C0_FUN_004224c0.c`; function-specific comparison still pending; source marker line 18.
- `0x00423570` `src/game/name_entry.cpp`: references available at IDA C 35632, IDA asm 49870, and `00423570_FUN_00423570.c`; function-specific comparison still pending; source marker line 44.
- `0x00432cb0` `src/game/name_entry.cpp`: references available at IDA C 48451, IDA asm 72193, and `00432CB0_FUN_00432cb0.c`; function-specific comparison still pending; source marker line 97.
- `0x004231d0` `src/game/pause_result_open.cpp`: references available at IDA C 35448, IDA asm 49600, and `004231D0_FUN_004231d0.c`; function-specific comparison still pending; source marker line 76.
- `0x004074b0` `src/game/player_motion.cpp`: references available at IDA C 16393, IDA asm 8909, and `004074B0_FUN_004074b0.c`; function-specific comparison still pending; source marker line 92.
- `0x004076a0` `src/game/player_motion.cpp`: references available at IDA C 16471, IDA asm 9053, and `004076A0_FUN_004076a0.c`; function-specific comparison still pending; source marker line 122.
- `0x00407da0` `src/game/player_motion.cpp`: references available at IDA C 16773, IDA asm 9620, and `00407DA0_FUN_00407da0.c`; function-specific comparison still pending; source marker line 62.
- `0x00407e40` `src/game/player_motion.cpp`: references available at IDA C 16816, IDA asm 9681, and `00407E40_FUN_00407e40.c`; function-specific comparison still pending; source marker line 76.
- `0x00430ff0` `src/game/practice_stage_menu.cpp`: references available at IDA C 47001, IDA asm 69709, and `00430FF0_FUN_00430ff0.c`; function-specific comparison still pending; source marker line 20.
- `0x0042cd50` `src/game/progress_worker.cpp`: references available at IDA C 43043, IDA asm 63303, and `0042CD50_FUN_0042cd50.c`; function-specific comparison still pending; source marker line 6.
- `0x00431ba0` `src/game/replay_browser_draw.cpp`: references available at IDA C 47570, IDA asm 70688, and `00431BA0_FUN_00431ba0.c`; function-specific comparison still pending; source marker line 5.
- `0x00428f60` `src/game/replay_runtime_bootstrap.cpp`: references available at IDA C 40002, IDA asm 57559, and `00428F60_FUN_00428f60.c`; function-specific comparison still pending; source marker line 4.
- `0x004329f0` `src/game/replay_score_draw.cpp`: references available at IDA C 48338, IDA asm 71971, and `004329F0_FUN_004329f0.c`; function-specific comparison still pending; source marker line 7.
- `0x00433230` `src/game/replay_stage_name_draw.cpp`: references available at IDA C 48719, IDA asm 72669, and `00433230_FUN_00433230.c`; function-specific comparison still pending; source marker line 6.
- `0x004172e0` `src/game/result_overlay.cpp`: references available at IDA C 26516, IDA asm 31997, and `004172E0_FUN_004172e0.c`; function-specific comparison still pending; source marker line 12.
- `0x0041fdd0` `src/game/result_screen_effects.cpp`: references available at IDA C 32986, IDA asm 44878, and `0041FDD0_FUN_0041fdd0.c`; function-specific comparison still pending; source marker line 16.
- `0x00408030` `src/game/score.cpp`: references available at IDA C 16911, IDA asm 9847, and `00408030_FUN_00408030.c`; function-specific comparison still pending; source marker line 506.
- `0x00408660` `src/game/score.cpp`: references available at IDA C 17195, IDA asm 10413, and `00408660_FUN_00408660.c`; function-specific comparison still pending; source marker line 141.
- `0x004086b0` `src/game/score.cpp`: references available at IDA C 17208, IDA asm 10450, and `004086B0_FUN_004086b0.c`; function-specific comparison still pending; source marker line 265.
- `0x00408750` `src/game/score.cpp`: references available at IDA C 17214, IDA asm 10512, and `00408750_FUN_00408750.c`; function-specific comparison still pending; source marker line 415.
- `0x004088c0` `src/game/score.cpp`: references available at IDA C 17244, IDA asm 10638, and `004088C0_FUN_004088c0.c`; function-specific comparison still pending; source marker line 354.
- `0x004089c0` `src/game/score.cpp`: references available at IDA C 17295, IDA asm 10749, and `004089C0_FUN_004089c0.c`; function-specific comparison still pending; source marker line 182.
- `0x004091c0` `src/game/score.cpp`: references available at IDA C 17651, IDA asm 11392, and `004091C0_FUN_004091c0.c`; function-specific comparison still pending; source marker line 125.
- `0x00409230` `src/game/score.cpp`: references available at IDA C 17683, IDA asm 11444, and `00409230_FUN_00409230.c`; function-specific comparison still pending; source marker line 117.
- `0x00409270` `src/game/score.cpp`: references available at IDA C 17694, IDA asm 11467, and `00409270_FUN_00409270.c`; function-specific comparison still pending; source marker line 123.
- `0x00409d90` `src/game/score.cpp`: references available at IDA C 18342, IDA asm 12413, and `00409D90_FUN_00409d90.c`; function-specific comparison still pending; source marker line 569.
- `0x00409e20` `src/game/score.cpp`: references available at IDA C 18378, IDA asm 12492, and `00409E20_FUN_00409e20.c`; function-specific comparison still pending; source marker line 621.
- `0x0040ac20` `src/game/score.cpp`: references available at IDA C 19086, IDA asm 13790, and `0040AC20_FUN_0040ac20.c`; function-specific comparison still pending; source marker line 368.
- `0x0040ac90` `src/game/score.cpp`: references available at IDA C 19129, IDA asm 13845, and `0040AC90_FUN_0040ac90.c`; function-specific comparison still pending; source marker line 406.
- `0x0040ace0` `src/game/score.cpp`: references available at IDA C 19139, IDA asm 13874, and `0040ACE0_FUN_0040ace0.c`; function-specific comparison still pending; source marker line 275.
- `0x0040ad20` `src/game/score.cpp`: references available at IDA C 19152, IDA asm 13908, and `0040AD20_FUN_0040ad20.c`; function-specific comparison still pending; source marker line 389.
- `0x0040b9d0` `src/game/score.cpp`: references available at IDA C 19807, IDA asm 15233, and `0040B9D0_FUN_0040b9d0.c`; function-specific comparison still pending; source marker line 132.
- `0x00412e70` `src/game/score.cpp`: references available at IDA C 22669, IDA asm 25695, and `00412E70_FUN_00412e70.c`; function-specific comparison still pending; source marker line 577.
- `0x0041be80` `src/game/score.cpp`: references available at IDA C 30294, IDA asm 39257, and `0041BE80_FUN_0041be80.c`; function-specific comparison still pending; source marker line 1.
- `0x0041beb0` `src/game/score.cpp`: references available at IDA C 30306, IDA asm 39284, and `0041BEB0_FUN_0041beb0.c`; function-specific comparison still pending; source marker line 421.
- `0x0041c030` `src/game/score.cpp`: references available at IDA C 30379, IDA asm 39433, and `0041C030_FUN_0041c030.c`; function-specific comparison still pending; source marker line 428.
- `0x0041c1c0` `src/game/score.cpp`: references available at IDA C 30451, IDA asm 39574, and `0041C1C0_FUN_0041c1c0.c`; function-specific comparison still pending; source marker line 484.
- `0x0041c5b0` `src/game/score.cpp`: references available at IDA C 30709, IDA asm 40030, and `0041C5B0_FUN_0041c5b0.c`; function-specific comparison still pending; source marker line 456.
- `0x0041c7d0` `src/game/score.cpp`: references available at IDA C 30805, IDA asm 40202, and `0041C7D0_FUN_0041c7d0.c`; function-specific comparison still pending; source marker line 538.
- `0x0041c800` `src/game/score.cpp`: references available at IDA C 30826, IDA asm 40235, and `0041C800_FUN_0041c800.c`; function-specific comparison still pending; source marker line 547.
- `0x0041f7a0` `src/game/score.cpp`: references available at IDA C 32710, IDA asm 44299, and `0041F7A0_FUN_0041f7a0.c`; function-specific comparison still pending; source marker line 589.
- `0x00426610` `src/game/score.cpp`: references available at IDA C 37970, IDA asm 53840, and `00426610_FUN_00426610.c`; function-specific comparison still pending; source marker line 152.
- `0x00426660` `src/game/score.cpp`: references available at IDA C 37984, IDA asm 53873, and `00426660_FUN_00426660.c`; function-specific comparison still pending; source marker line 161.
- `0x00428d70` `src/game/score.cpp`: references available at IDA C 39973, IDA asm 57399, and `00428D70_FUN_00428d70.c`; function-specific comparison still pending; source marker line 589.
- `0x0044b010` `src/game/score.cpp`: references available at IDA C 66861, IDA asm 110451, and `0044B010_FUN_0044b010.c`; function-specific comparison still pending; source marker line 297.
- `0x0044b080` `src/game/score.cpp`: references available at IDA C 66891, IDA asm 110504, and `0044B080_FUN_0044b080.c`; function-specific comparison still pending; source marker line 314.
- `0x0044be20` `src/game/score.cpp`: references available at IDA C 67528, IDA asm 111971, and `0044BE20_FUN_0044be20.c`; function-specific comparison still pending; source marker line 341.
- `0x0044be70` `src/game/score.cpp`: references available at IDA C 67545, IDA asm 111996, and `0044BE70_FUN_0044be70.c`; function-specific comparison still pending; source marker line 327.
- `0x00421fa0` `src/game/score_file.cpp`: references available at IDA C 34453, IDA asm 47960, and `00421FA0_FUN_00421fa0.c`; function-specific comparison still pending; source marker line 166.
- `0x0042acb0` `src/game/score_file.cpp`: references available at IDA C 41409, IDA asm 60238, and `0042ACB0_FUN_0042acb0.c`; function-specific comparison still pending; source marker line 130.
- `0x0042b030` `src/game/score_file.cpp`: references available at IDA C 41543, IDA asm 60567, and `0042B030_FUN_0042b030.c`; function-specific comparison still pending; source marker line 72.
- `0x00431410` `src/game/score_menu_rows.cpp`: references available at IDA C 47223, IDA asm 70084, and `00431410_FUN_00431410.c`; function-specific comparison still pending; source marker line 30.
- `0x0042a6a0` `src/game/spell_card_dispatch.cpp`: references available at IDA C 41132, IDA asm 59653, and `0042A6A0_FUN_0042a6a0.c`; function-specific comparison still pending; source marker line 11.
- `0x004127a0` `src/game/spell_timer.cpp`: references available at IDA C 22248, IDA asm 25019, and `004127A0_FUN_004127a0.c`; function-specific comparison still pending; source marker line 34.
- `0x00424480` `src/game/sprite_descriptor.cpp`: references available at IDA C 36374, IDA asm 51216, and `00424480_FUN_00424480.c`; function-specific comparison still pending; source marker line 11.
- `0x0040a940` `src/game/sprite_test_overlay.cpp`: references available at IDA C 18964, IDA asm 13567, and `0040A940_FUN_0040a940.c`; function-specific comparison still pending; source marker line 45.
- `0x0042c360` `src/game/sprite_test_overlay.cpp`: references available at IDA C 42531, IDA asm 62422, and `0042C360_FUN_0042c360.c`; function-specific comparison still pending; source marker line 19.
- `0x0040c3c0` `src/game/stage_background.cpp`: references available at IDA C 20398, IDA asm 16234, and `0040C3C0_FUN_0040c3c0.c`; function-specific comparison still pending; source marker line 17.
- `0x00427960` `src/game/stage_background.cpp`: references available at IDA C 38945, IDA asm 55416, and `00427960_FUN_00427960.c`; function-specific comparison still pending; source marker line 46.
- `0x00419650` `src/game/stage_focus_fade.cpp`: references available at IDA C 28420, IDA asm 35342, and `00419650_FUN_00419650.c`; function-specific comparison still pending; source marker line 4.
- `0x00415b00` `src/game/stage_slot_state.cpp`: references available at IDA C 25337, IDA asm 29848, and `00415B00_FUN_00415b00.c`; function-specific comparison still pending; source marker line 3.
- `0x004349e0` `src/game/stage_text.cpp`: references available at IDA C 49872, IDA asm 74694, and `004349E0_FUN_004349e0.c`; function-specific comparison still pending; source marker line 4.
- `0x00434a20` `src/game/stage_text.cpp`: references available at IDA C 49897, IDA asm 74741, and `00434A20_FUN_00434a20.c`; function-specific comparison still pending; source marker line 18.
- `0x00434a80` `src/game/stage_text.cpp`: references available at IDA C 49937, IDA asm 74807, and `00434A80_FUN_00434a80.c`; function-specific comparison still pending; source marker line 36.
- `0x00418190` `src/game/stage_update.cpp`: references available at IDA C 27281, IDA asm 33360, and `00418190_FUN_00418190.c`; function-specific comparison still pending; source marker line 64.
- `0x00413980` `src/game/task_registration.cpp`: references available at IDA C 23213, IDA asm 26819, and `00413980_FUN_00413980.c`; function-specific comparison still pending; source marker line 159.
- `0x0041c120` `src/game/task_registration.cpp`: references available at IDA C 30416, IDA asm 39523, and `0041C120_FUN_0041c120.c`; function-specific comparison still pending; source marker line 132.
- `0x0042caa0` `src/game/task_registration.cpp`: references available at IDA C 42875, IDA asm 63052, and `0042CAA0_FUN_0042caa0.c`; function-specific comparison still pending; source marker line 233.
- `0x0042cdf0` `src/game/title_menu_runtime.cpp`: references available at IDA C 43074, IDA asm 63375, and `0042CDF0_FUN_0042cdf0.c`; function-specific comparison still pending; source marker line 3.
- `0x00426cf0` `src/game/trigger_activation.cpp`: references available at IDA C 38294, IDA asm 54449, and `00426CF0_FUN_00426cf0.c`; function-specific comparison still pending; source marker line 18.
- `0x0044bc10` `src/math/angle.cpp`: references available at IDA C 67466, IDA asm 111748, and `0044BC10_FUN_0044bc10.c`; function-specific comparison still pending; source marker line 27.
- `0x0044b9e0` `src/math/rng.cpp`: references available at IDA C 67396, IDA asm 111526, and `0044B9E0_FUN_0044b9e0.c`; function-specific comparison still pending; source marker line 35.
- `0x0044ba80` `src/math/rng.cpp`: references available at IDA C 67410, IDA asm 111589, and `0044BA80_FUN_0044ba80.c`; function-specific comparison still pending; source marker line 45.
- `0x0044bb20` `src/math/rng.cpp`: references available at IDA C 67434, IDA asm 111647, and `0044BB20_FUN_0044bb20.c`; function-specific comparison still pending; source marker line 59.
- `0x0044bb90` `src/math/rng.cpp`: references available at IDA C 67450, IDA asm 111697, and `0044BB90_FUN_0044bb90.c`; function-specific comparison still pending; source marker line 64.
- `0x00404ed0` `src/math/timer.cpp`: references available at IDA C 14708, IDA asm 5452, and `00404ED0_FUN_00404ed0.c`; function-specific comparison still pending; source marker line 2.
- `0x00428dd0` `src/math/timer.cpp`: references available at IDA C 39979, IDA asm 57441, and `00428DD0_FUN_00428dd0.c`; function-specific comparison still pending; source marker line 26.
- `0x0042c620` `src/math/timer.cpp`: references available at IDA C 42638, IDA asm 62626, and `0042C620_FUN_0042c620.c`; function-specific comparison still pending; source marker line 44.
- `0x0044bf40` `src/math/timer.cpp`: references available at IDA C 67619, IDA asm 112119, and `0044BF40_FUN_0044bf40.c`; function-specific comparison still pending; source marker line 26.
- `0x00421b90` `src/math/vector3_cross.cpp`: references available at IDA C 34232, IDA asm 47523, and `00421B90_FUN_00421b90.c`; function-specific comparison still pending; source marker line 1.
- `0x004054b0` `src/platform/all_source_runtime.cpp`: references available at IDA C 14919, IDA asm 5994, and `004054B0_FUN_004054b0.c`; function-specific comparison still pending; source marker line 205.
- `0x0044c150` `src/platform/all_source_runtime.cpp`: references available at IDA C 67689, IDA asm 112383, and `0044C150_FUN_0044c150.c`; function-specific comparison still pending; source marker line 184.
- `0x00437db0` `src/platform/font_texture_draw.cpp`: references available at IDA C 52492, IDA asm 80571, and `00437DB0_FUN_00437db0.c`; function-specific comparison still pending; source marker line 42.
- `0x00437fe0` `src/platform/font_texture_draw.cpp`: references available at IDA C 52644, IDA asm 80812, and `00437FE0_FUN_00437fe0.c`; function-specific comparison still pending; source marker line 50.
- `0x00436a30` `src/platform/gdi_font_cache.cpp`: references available at IDA C 51752, IDA asm 78573, and `00436A30_FUN_00436a30.c`; function-specific comparison still pending; source marker line 7.
- `0x00437d10` `src/platform/gdi_font_cache.cpp`: references available at IDA C 52471, IDA asm 80512, and `00437D10_FUN_00437d10.c`; function-specific comparison still pending; source marker line 11.
- `0x00436210` `src/platform/memory_file.cpp`: references available at IDA C 51332, IDA asm 77602, and `00436210_FUN_00436210.c`; function-specific comparison still pending; source marker line 79.
- `0x00436260` `src/platform/memory_file.cpp`: references available at IDA C 51364, IDA asm 77643, and `00436260_FUN_00436260.c`; function-specific comparison still pending; source marker line 41.
- `0x004362b0` `src/platform/memory_file.cpp`: references available at IDA C 51382, IDA asm 77670, and `004362B0_FUN_004362b0.c`; function-specific comparison still pending; source marker line 53.
- `0x00436330` `src/platform/memory_file.cpp`: references available at IDA C 51410, IDA asm 77717, and `00436330_FUN_00436330.c`; function-specific comparison still pending; source marker line 67.
- `0x004363c0` `src/platform/memory_file.cpp`: references available at IDA C 51439, IDA asm 77784, and `004363C0_FUN_004363c0.c`; function-specific comparison still pending; source marker line 121.
- `0x00436430` `src/platform/memory_file.cpp`: references available at IDA C 51471, IDA asm 77842, and `00436430_FUN_00436430.c`; function-specific comparison still pending; source marker line 135.
- `0x0043d250` `src/platform/memory_file.cpp`: references available at IDA C 56215, IDA asm 89053, and `0043D250_FUN_0043d250.c`; function-specific comparison still pending; source marker line 4.
- `0x0043d390` `src/platform/memory_file.cpp`: references available at IDA C 56289, IDA asm 89233, and `0043D390_FUN_0043d390.c`; function-specific comparison still pending; source marker line 209.
- `0x0043a730` `src/platform/midi_sequencer.cpp`: references available at IDA C 54321, IDA asm 84867, and `0043A730_FUN_0043a730.c`; function-specific comparison still pending; source marker line 32.
- `0x0043aad0` `src/platform/midi_sequencer.cpp`: references available at IDA C 54431, IDA asm 85163, and `0043AAD0_FUN_0043aad0.c`; function-specific comparison still pending; source marker line 70.
- `0x0043ace0` `src/platform/midi_sequencer.cpp`: references available at IDA C 54515, IDA asm 85357, and `0043ACE0_FUN_0043ace0.c`; function-specific comparison still pending; source marker line 46.
- `0x0043af30` `src/platform/midi_sequencer.cpp`: references available at IDA C 54617, IDA asm 85589, and `0043AF30_FUN_0043af30.c`; function-specific comparison still pending; source marker line 125.
- `0x00436570` `src/platform/process.cpp`: references available at IDA C 51568, IDA asm 78032, and `00436570_FUN_00436570.c`; function-specific comparison still pending; source marker line 4.
- `0x0044d5b0` `src/platform/process.cpp`: references available at IDA C 68651, IDA asm 114481, and `0044D5B0_FUN_0044d5b0.c`; function-specific comparison still pending; source marker line 73.
- `0x00436680` `src/platform/resource_file.cpp`: references available at IDA C 51605, IDA asm 78144, and `00436680_FUN_00436680.c`; function-specific comparison still pending; source marker line 27.
- `0x004366c0` `src/platform/resource_file.cpp`: references available at IDA C 51625, IDA asm 78173, and `004366C0_FUN_004366c0.c`; function-specific comparison still pending; source marker line 33.
- `0x00436ca0` `src/platform/resource_file.cpp`: references available at IDA C 51857, IDA asm 78815, and `00436CA0_FUN_00436ca0.c`; function-specific comparison still pending; source marker line 18.
- `0x0043a910` `src/platform/sound_commands.cpp`: references available at IDA C 54337, IDA asm 84983, and `0043A910_FUN_0043a910.c`; function-specific comparison still pending; source marker line 111.
- `0x0043d120` `src/platform/sound_commands.cpp`: references available at IDA C 56114, IDA asm 88915, and `0043D120_FUN_0043d120.c`; function-specific comparison still pending; source marker line 93.
- `0x0043d7d0` `src/platform/sound_commands.cpp`: references available at IDA C 56439, IDA asm 89673, and `0043D7D0_FUN_0043d7d0.c`; function-specific comparison still pending; source marker line 238.
- `0x0043d950` `src/platform/sound_commands.cpp`: references available at IDA C 56485, IDA asm 89826, and `0043D950_FUN_0043d950.c`; function-specific comparison still pending; source marker line 215.
- `0x0043ddf0` `src/platform/sound_commands.cpp`: references available at IDA C 56698, IDA asm 90272, and `0043DDF0_FUN_0043ddf0.c`; function-specific comparison still pending; source marker line 17.
- `0x0044cbf0` `src/platform/sound_commands.cpp`: references available at IDA C 68091, IDA asm 113340, and `0044CBF0_FUN_0044cbf0.c`; function-specific comparison still pending; source marker line 123.
- `0x0044cf20` `src/platform/sound_commands.cpp`: references available at IDA C 68251, IDA asm 113684, and `0044CF20_FUN_0044cf20.c`; function-specific comparison still pending; source marker line 146.
- `0x0044d110` `src/platform/sound_commands.cpp`: references available at IDA C 68375, IDA asm 113918, and `0044D110_FUN_0044d110.c`; function-specific comparison still pending; source marker line 170.
- `0x0044dad0` `src/platform/sound_commands.cpp`: references available at IDA C 68877, IDA asm 115075, and `0044DAD0_FUN_0044dad0.c`; function-specific comparison still pending; source marker line 200.
- `0x0043cd30` `src/platform/sound_device_init.cpp`: references available at IDA C 55942, IDA asm 88553, and `0043CD30_FUN_0043cd30.c`; function-specific comparison still pending; source marker line 38.
- `0x00421e00` `src/platform/sound_fade.cpp`: references available at IDA C 34344, IDA asm 47785, and `00421E00_FUN_00421e00.c`; function-specific comparison still pending; source marker line 21.
- `0x0044d440` `src/platform/sound_stream_start.cpp`: references available at IDA C 68566, IDA asm 114301, and `0044D440_FUN_0044d440.c`; function-specific comparison still pending; source marker line 4.
- `0x0043cc40` `src/platform/sound_worker.cpp`: references available at IDA C 55900, IDA asm 88449, and `0043CC40_FUN_0043cc40.c`; function-specific comparison still pending; source marker line 4.
- `0x0044c1c0` `src/platform/worker_start.cpp`: references available at IDA C 67716, IDA asm 112432, and `0044C1C0_FUN_0044c1c0.c`; function-specific comparison still pending; source marker line 3.
- `0x004136c0` `src/render/animation_slot.cpp`: references available at IDA C 23079, IDA asm 26574, and `004136C0_FUN_004136c0.c`; function-specific comparison still pending; source marker line 1.
- `0x004470c0` `src/render/anm_archive.cpp`: references available at IDA C 63624, IDA asm 103570, and `004470C0_FUN_004470c0.c`; function-specific comparison still pending; source marker line 6.
- `0x004472e0` `src/render/anm_archive.cpp`: references available at IDA C 63747, IDA asm 103793, and `004472E0_FUN_004472e0.c`; function-specific comparison still pending; source marker line 40.
- `0x00421300` `src/render/anm_handle_release.cpp`: references available at IDA C 33809, IDA asm 46804, and `00421300_FUN_00421300.c`; function-specific comparison still pending; source marker line 29.
- `0x00409e50` `src/render/anm_propagate.cpp`: references available at IDA C 18396, IDA asm 12517, and `00409E50_FUN_00409e50.c`; function-specific comparison still pending; source marker line 19.
- `0x0042c770` `src/render/anm_propagate.cpp`: references available at IDA C 42722, IDA asm 62758, and `0042C770_FUN_0042c770.c`; function-specific comparison still pending; source marker line 30.
- `0x004451c0` `src/render/anm_vm_draw_dispatch.cpp`: references available at IDA C 61872, IDA asm 100662, and `004451C0_FUN_004451c0.c`; function-specific comparison still pending; source marker line 13.
- `0x0043c1a0` `src/render/default_viewport.cpp`: references available at IDA C 55386, IDA asm 87331, and `0043C1A0_FUN_0043c1a0.c`; function-specific comparison still pending; source marker line 13.
- `0x00444b10` `src/render/edge_strips.cpp`: references available at IDA C 61692, IDA asm 100003, and `00444B10_FUN_00444b10.c`; function-specific comparison still pending; source marker line 9.
- `0x00444be0` `src/render/edge_strips.cpp`: references available at IDA C 61749, IDA asm 100099, and `00444BE0_FUN_00444be0.c`; function-specific comparison still pending; source marker line 50.
- `0x00445620` `src/render/effect_ring_update.cpp`: references available at IDA C 62018, IDA asm 101041, and `00445620_FUN_00445620.c`; function-specific comparison still pending; source marker line 25.
- `0x00442670` `src/render/final_quad_pipeline.cpp`: references available at IDA C 60226, IDA asm 97070, and `00442670_FUN_00442670.c`; function-specific comparison still pending; source marker line 6.
- `0x00420cd0` `src/render/fog_disable.cpp`: references available at IDA C 33586, IDA asm 46259, and `00420CD0_FUN_00420cd0.c`; function-specific comparison still pending; source marker line 3.
- `0x00437160` `src/render/image_alpha_transform.cpp`: references available at IDA C 52094, IDA asm 79308, and `00437160_FUN_00437160.c`; function-specific comparison still pending; source marker line 5.
- `0x0043bfa0` `src/render/texture_stage_reset.cpp`: references available at IDA C 55309, IDA asm 87148, and `0043BFA0_FUN_0043bfa0.c`; function-specific comparison still pending; source marker line 17.
- `0x004465b0` `src/render/transparent_pixel_fill_locked.cpp`: references available at IDA C 63020, IDA asm 102405, and `004465B0_FUN_004465b0.c`; function-specific comparison still pending; source marker line 13.
- `0x00412a00` `src/script/ecl_vm.cpp`: references available at IDA C 22362, IDA asm 25198, and `00412A00_FUN_00412a00.c`; function-specific comparison still pending; source marker line 215.
- `0x00412a10` `src/script/ecl_vm.cpp`: references available at IDA C 22372, IDA asm 25210, and `00412A10_FUN_00412a10.c`; function-specific comparison still pending; source marker line 246.
- `0x0044fd10` `src/script/ecl_vm_children.cpp`: references available at IDA C 70775, IDA asm 118005, and `0044FD10_FUN_0044fd10.c`; function-specific comparison still pending; source marker line 130.
- `0x00450470` `src/script/final_script_runtime.cpp`: references available at IDA C 71273, IDA asm 118900, and `00450470_FUN_00450470.c`; function-specific comparison still pending; source marker line 8.
- `0x00450700` `src/script/final_script_runtime.cpp`: references available at IDA C 71389, IDA asm 119210, and `00450700_FUN_00450700.c`; function-specific comparison still pending; source marker line 1.
- `0x00403850` `src/script/stage_ecl_load.cpp`: references available at IDA C 13503, IDA asm 3426, and `00403850_FUN_00403850.c`; function-specific comparison still pending; source marker line 14.
- `0x00418150` `src/util/heap.cpp`: references available at IDA C 27271, IDA asm 33330, and `00418150_FUN_00418150.c`; function-specific comparison still pending; source marker line 44.
- `0x0042cdb0` `src/util/heap.cpp`: references available at IDA C 43064, IDA asm 63345, and `0042CDB0_FUN_0042cdb0.c`; function-specific comparison still pending; source marker line 55.
- `0x00435220` `src/util/heap.cpp`: references available at IDA C 50354, IDA asm 75737, and `00435220_FUN_00435220.c`; function-specific comparison still pending; source marker line 76.
- `0x00435250` `src/util/heap.cpp`: references available at IDA C 50365, IDA asm 75775, and `00435250_FUN_00435250.c`; function-specific comparison still pending; source marker line 35.
- `0x00438260` `src/util/heap.cpp`: references available at IDA C 52794, IDA asm 81078, and `00438260_FUN_00438260.c`; function-specific comparison still pending; source marker line 151.
- `0x00438350` `src/util/heap.cpp`: references available at IDA C 52862, IDA asm 81217, and `00438350_FUN_00438350.c`; function-specific comparison still pending; source marker line 90.
- `0x00438380` `src/util/heap.cpp`: references available at IDA C 52868, IDA asm 81248, and `00438380_FUN_00438380.c`; function-specific comparison still pending; source marker line 232.
- `0x00438420` `src/util/heap.cpp`: references available at IDA C 52903, IDA asm 81330, and `00438420_FUN_00438420.c`; function-specific comparison still pending; source marker line 102.
- `0x00438510` `src/util/heap.cpp`: references available at IDA C 52971, IDA asm 81475, and `00438510_FUN_00438510.c`; function-specific comparison still pending; source marker line 197.
- `0x00438590` `src/util/heap.cpp`: references available at IDA C 53012, IDA asm 81555, and `00438590_FUN_00438590.c`; function-specific comparison still pending; source marker line 215.
- `0x004386b0` `src/util/heap.cpp`: references available at IDA C 53087, IDA asm 81710, and `004386B0_FUN_004386b0.c`; function-specific comparison still pending; source marker line 285.

## Unresolved reference inventory

- `0x0040678e` `src/game/player_motion.cpp`: missing IDA C, IDA asm; source marker line 30.
- `0x00436370` `src/platform/memory_file.cpp`: missing Ghidra; source marker line 162.
- `0x00436460` `src/platform/memory_file.cpp`: missing Ghidra; source marker line 146.
- `0x004364d0` `src/platform/memory_file.cpp`: missing Ghidra; source marker line 167.
- `0x004364e0` `src/platform/memory_file.cpp`: missing Ghidra; source marker line 172.
- `0x0044bd10` `src/platform/process.cpp`: missing IDA C, IDA asm; source marker line 87.
- `0x0044c100` `src/platform/process.cpp`: missing IDA C, IDA asm; source marker line 56.
- `0x0044c130` `src/platform/process.cpp`: missing IDA C, IDA asm; source marker line 33.
- `0x004352c0` `src/util/heap.cpp`: missing IDA C, IDA asm, Ghidra; source marker line 15.
- `0x004381f0` `src/util/heap.cpp`: missing IDA C, IDA asm; source marker line 66.
- `0x00438250` `src/util/heap.cpp`: missing Ghidra; source marker line 226.
- `0x00438680` `src/util/heap.cpp`: missing IDA C, IDA asm, Ghidra; source marker line 269.
- `0x00438690` `src/util/heap.cpp`: missing IDA C, IDA asm, Ghidra; source marker line 24.
- `0x004386a0` `src/util/heap.cpp`: missing Ghidra; source marker line 30.
- `0x0043874c` `src/util/heap.cpp`: missing IDA C, IDA asm; source marker line 287.
- `0x00438800` `src/util/heap.cpp`: missing IDA C, IDA asm, Ghidra; source marker line 261.
- `0x00438840` `src/util/heap.cpp`: missing IDA C, IDA asm, Ghidra; source marker line 19.

The generated table intentionally keeps every address in the partition, including rows whose neighbor in the same translation unit may be complete. No production or shared ledger files were changed by this audit.
