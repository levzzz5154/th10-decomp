# Exhaustive semantic implementation audit manifest

Generated from `coverage.json` on 2026-09-05. The ledger currently has **710 semantic addresses**; **708 remain in this pass** after 5 exact-address reviews (2 were still semantic in the current ledger). The unit of completion is an address, not a translation unit: a checked function does not clear its neighbors. See the [consolidated audit status](semantic_audit_summary.md) and [deduplicated address ledger](semantic_audit_summary.json) for the current bounded-pass results.

## Evidence criteria

- Inspect the exact address in local IDA pseudocode and disassembly.
- Inspect the matching raw Ghidra export; record corruption or missing data.
- Inspect the promoted source body and its host contract/callbacks.
- Compare control flow, field offsets, constants, ownership, and error paths.
- Run an existing focused test when it exercises the exact address; do not treat a self-authored test as retail proof.
- Classify only the reviewed address; neighboring functions in the same file remain unchecked.

## Previously checked exact addresses

| Address | Evidence |
| --- | --- |
| `0x0040BD80` | docs/semantic_spot_audit.md: EndingScript_Update |
| `0x00412AC0` | docs/semantic_spot_audit.md: Trajectory_Evaluate2D |
| `0x004250B0` | docs/semantic_spot_audit.md: player_front::UpdatePlayer |
| `0x0042B9C0` | docs/semantic_spot_audit.md: ScorePopup_Enqueue |
| `0x0044A5F0` | docs/semantic_spot_audit.md: input_final::Poll |

## Nonsemantic statuses excluded from this pass

Partial, researched, and unrecovered entries remain visible in the ledger but are excluded from the semantic implementation inventory. Their blockers are not silently converted into green audit results.

## Nonoverlapping agent partitions

Whole source files belong to one group only. Reports must preserve the address list below and add one verdict/evidence row per address.

### coordinator

81 files, 237 addresses, 99351 tracked retail bytes.

- `src/app/frame_clock.cpp` (2): `0x00439540`, `0x00439D20`
- `src/app/game_state_init.cpp` (1): `0x00445900`
- `src/app/main_tasks.cpp` (5): `0x0041FF80`, `0x00420270`, `0x00420470`, `0x00420670`, `0x00420870`
- `src/archive/crypt.cpp` (2): `0x0044B0D0`, `0x0044B220`
- `src/archive/lzss.cpp` (1): `0x00435DC0`
- `src/archive/resource_manager.cpp` (3): `0x004356F0`, `0x00435800`, `0x004358E0`
- `src/game/archive_cursor.cpp` (1): `0x0044DD40`
- `src/game/archive_cursor_read.cpp` (1): `0x0044DE10`
- `src/game/asset_buffer.cpp` (1): `0x0040B480`
- `src/game/bullet_manager.cpp` (9): `0x00402720`, `0x00404450`, `0x00404F30`, `0x00405300`, `0x00405E20`, `0x00405ED0`, `0x00406060`, `0x004065C0`, `0x0040C730`
- `src/game/bullet_runtime_update.cpp` (1): `0x00406240`
- `src/game/effect_indicator_queue.cpp` (1): `0x00419120`
- `src/game/effect_indicator_slots.cpp` (6): `0x004050D0`, `0x00427B50`, `0x00427D80`, `0x00427E90`, `0x00428160`, `0x0042A930`
- `src/game/enemy_projectile_spawn.cpp` (1): `0x004067D0`
- `src/game/frame_counter.cpp` (1): `0x00427C70`
- `src/game/game_thread_queue.cpp` (3): `0x00401530`, `0x00401630`, `0x00401690`
- `src/game/game_ui_create.cpp` (1): `0x004180E0`
- `src/game/input_recorder.cpp` (1): `0x004297D0`
- `src/game/key_config.cpp` (1): `0x00430250`
- `src/game/laser_segment_cut.cpp` (4): `0x0041D880`, `0x0041DD80`, `0x0041EB00`, `0x0041EFA0`
- `src/game/line_effect_sweep.cpp` (1): `0x0041E260`
- `src/game/main_menu_dispatch.cpp` (6): `0x00422150`, `0x004223F0`, `0x00422660`, `0x00422AB0`, `0x00422C80`, `0x004236F0`
- `src/game/manager_teardown.cpp` (15): `0x00405F70`, `0x00408AF0`, `0x00409F90`, `0x0040B7B0`, `0x0040D530`, `0x00414370`, `0x004145F0`, `0x00417C80`, `0x00418EE0`, `0x0041ADF0`, `0x0041FB50`, `0x00422220`, `0x00424ED0`, `0x004294A0`, `0x0042CB60`
- `src/game/menu_flow_updates.cpp` (3): `0x0042F540`, `0x00430320`, `0x004306A0`
- `src/game/message_manager_init.cpp` (1): `0x0040B560`
- `src/game/object_factories.cpp` (2): `0x0041C290`, `0x0041FD00`
- `src/game/pause_menu_reset.cpp` (1): `0x00424D90`
- `src/game/player.cpp` (11): `0x00404530`, `0x004045B0`, `0x00405410`, `0x00405500`, `0x004055C0`, `0x00405620`, `0x00405750`, `0x00405860`, `0x004059F0`, `0x00405AC0`, `0x00405B60`
- `src/game/player_scheduler.cpp` (1): `0x00405BE0`
- `src/game/pool_constructors.cpp` (3): `0x0042B430`, `0x0042C920`, `0x0043E5A0`
- `src/game/projectile_bounce.cpp` (1): `0x0041CFD0`
- `src/game/projectile_command_runtime.cpp` (1): `0x00406D90`
- `src/game/recovery_leaves.cpp` (78): `0x00401520`, `0x00404DA0`, `0x00405040`, `0x004056B0`, `0x0040B940`, `0x0040B9F0`, `0x0040BD20`, `0x0040C9A0`, `0x0040CC50`, `0x00412720`, `0x00412AA0`, `0x00412DB0`, `0x00412ED0`, `0x00413170`, `0x00413200`, `0x00413270`, `0x00413450`, `0x00413790`, `0x00414570`, `0x00417770`, `0x00417800`, `0x00418810`, `0x004188A0`, `0x00418A00`, `0x00419040`, `0x00419090`, `0x004198A0`, `0x004198C0`, `0x0041A050`, `0x0041A0A0`, `0x0041AB10`, `0x0041AD90`, `0x0041F850`, `0x0041F8D0`, `0x0041F930`, `0x0041FAC0`, `0x004203F0`, `0x00420A90`, `0x00421F00`, `0x004220E0`, `0x00422360`, `0x00422A90`, `0x00423510`, `0x004243F0`, `0x00425020`, `0x00427950`, `0x00427AE0`, `0x004281D0`, `0x004297B0`, `0x0042A8A0`, `0x0042ADD0`, `0x0042B660`, `0x0042C670`, `0x0042C6D0`, `0x0043BC40`, `0x0043C870`, `0x0043CB00`, `0x0043D790`, `0x00441EF0`, `0x00441F50`, `0x00442220`, `0x00442300`, `0x00446EB0`, `0x00447280`, `0x004479D0`, `0x00447A50`, `0x0044CE80`, `0x0044CF00`, `0x0044D080`, `0x0044D300`, `0x0044D370`, `0x0044D4E0`, `0x0044D550`, `0x0044D5D0`, `0x0044D600`, `0x0044D6A0`, `0x0044D710`, `0x0044DCA0`
- `src/game/replay_spell_list.cpp` (1): `0x00432690`
- `src/game/score_hud_update.cpp` (1): `0x00417040`
- `src/game/score_view_ctor.cpp` (1): `0x0041C680`
- `src/game/slot_snapshot.cpp` (1): `0x0042A450`
- `src/game/spell_card_end.cpp` (1): `0x00409C00`
- `src/game/spell_timeout.cpp` (1): `0x004269D0`
- `src/game/stage_entry.cpp` (1): `0x00417870`
- `src/game/stage_tip_manager.cpp` (4): `0x00418D40`, `0x00418E30`, `0x0041A120`, `0x00424650`
- `src/game/stats_task.cpp` (1): `0x00413350`
- `src/game/title_main_menu.cpp` (1): `0x0042D420`
- `src/game/trajectory_evaluate.cpp` (2): `0x00404610`, `0x0044C350`
- `src/game/trigger_region.cpp` (1): `0x004267F0`
- `src/math/interpolators.cpp` (3): `0x00441600`, `0x00441950`, `0x00441AD0`
- `src/math/random_vector.cpp` (1): `0x00441E50`
- `src/math/vector.cpp` (2): `0x0041F800`, `0x004458B0`
- `src/platform/font_cache_init.cpp` (1): `0x00437A00`
- `src/platform/gdi_surface.cpp` (1): `0x00436AF0`
- `src/platform/joystick_probe.cpp` (1): `0x0044A0C0`
- `src/platform/midi_event_runtime.cpp` (1): `0x0043B110`
- `src/platform/midi_worker.cpp` (2): `0x0043B7A0`, `0x0043E3A0`
- `src/platform/midi_worker_stop.cpp` (1): `0x0043DAB0`
- `src/platform/pack_file_loader.cpp` (2): `0x0043A1C0`, `0x0044B360`
- `src/platform/sound_dummy.cpp` (1): `0x00420B10`
- `src/platform/sound_effect_buffers.cpp` (1): `0x0043DB60`
- `src/platform/sound_event_queue.cpp` (1): `0x0043DD10`
- `src/platform/sound_float_forward.cpp` (1): `0x00427C50`
- `src/platform/sound_leaves.cpp` (2): `0x00420C30`, `0x0044D730`
- `src/platform/sound_stream_thread.cpp` (1): `0x0043D690`
- `src/platform/win32_timer.cpp` (1): `0x004203C0`
- `src/render/anchored_quad_draw.cpp` (1): `0x00443290`
- `src/render/anm_batch_flush.cpp` (1): `0x00442F50`
- `src/render/anm_blend_state.cpp` (1): `0x004423E0`
- `src/render/anm_clip_quad.cpp` (1): `0x004462F0`
- `src/render/anm_distance_color.cpp` (1): `0x00443FB0`
- `src/render/camera_defaults.cpp` (1): `0x004216F0`
- `src/render/camera_setup.cpp` (4): `0x00421480`, `0x0043BCD0`, `0x00448270`, `0x00448450`
- `src/render/d3d_resource_manager.cpp` (4): `0x00438880`, `0x00449A90`, `0x00449AA0`, `0x00449E50`
- `src/render/edge_strip_draw.cpp` (1): `0x00444CE0`
- `src/render/faded_quad_draw.cpp` (1): `0x004445C0`
- `src/render/quad_build_anchored.cpp` (1): `0x00443080`
- `src/render/quad_vertex_append.cpp` (1): `0x00442FE0`
- `src/render/queued_anm_cleanup.cpp` (1): `0x00421070`
- `src/render/render_state_sync.cpp` (1): `0x004425A0`
- `src/render/transparent_pixel_fill.cpp` (1): `0x00436DA0`
- `src/script/anm_vm_tick.cpp` (2): `0x0043EAC0`, `0x0043EE30`
- `src/script/ecl_name_table.cpp` (2): `0x0040CD20`, `0x00450220`
- `src/script/prng.cpp` (1): `0x0043CB80`
- `src/util/legacy_string_funclets.cpp` (2): `0x00438723`, `0x004387C2`

### ending

81 files, 225 addresses, 104398 tracked retail bytes.

- `src/app/fps_counter.cpp` (2): `0x004134B0`, `0x004135D0`
- `src/app/version_marker.cpp` (1): `0x00420100`
- `src/archive/dat.cpp` (8): `0x00434C20`, `0x00434C30`, `0x00434D10`, `0x00434DD0`, `0x00434EF0`, `0x00434F30`, `0x00434F70`, `0x004350D0`
- `src/archive/dat_file.cpp` (1): `0x00434CA0`
- `src/game/animation_resource_lazy_fetch.cpp` (1): `0x0040C540`
- `src/game/boss_gauge.cpp` (2): `0x00428C20`, `0x00428E10`
- `src/game/effect_accel.cpp` (1): `0x0041D2C0`
- `src/game/effect_manager_destroy.cpp` (1): `0x0042B570`
- `src/game/ending_screen.cpp` (1): `0x0042D300`
- `src/game/enemy_drop_sweep.cpp` (1): `0x0041BA50`
- `src/game/enemy_lifecycle.cpp` (6): `0x004066E0`, `0x00408100`, `0x0040B110`, `0x0040D750`, `0x0040DAE0`, `0x0040E6A0`
- `src/game/entity_color_slot.cpp` (1): `0x00442050`
- `src/game/entity_movement_slot.cpp` (1): `0x0041AB70`
- `src/game/entity_region_sweep.cpp` (1): `0x00408210`
- `src/game/event_script_runtime.cpp` (1): `0x00403C80`
- `src/game/faith_gauge.cpp` (1): `0x00418930`
- `src/game/game_state.cpp` (6): `0x00402160`, `0x00402230`, `0x00402440`, `0x00402640`, `0x00402850`, `0x00402CA0`
- `src/game/game_state_overlay_draw.cpp` (1): `0x00415800`
- `src/game/item_scatter.cpp` (1): `0x0040C9D0`
- `src/game/laser_grow_update.cpp` (1): `0x0041E700`
- `src/game/message_host_init.cpp` (1): `0x0040D280`
- `src/game/music_room.cpp` (1): `0x00426520`
- `src/game/particle_seed.cpp` (1): `0x00404E10`
- `src/game/player_pickup_sweep.cpp` (1): `0x00428630`
- `src/game/player_reset.cpp` (1): `0x004246C0`
- `src/game/player_runtime_init.cpp` (2): `0x004247F0`, `0x00426360`
- `src/game/progress.cpp` (2): `0x0042C850`, `0x0042C8C0`
- `src/game/rank_level.cpp` (1): `0x004175E0`
- `src/game/replay_file_load.cpp` (1): `0x0042A200`
- `src/game/replay_large_runtime.cpp` (2): `0x00429B60`, `0x00431EE0`
- `src/game/replay_menu_draw.cpp` (1): `0x00433B30`
- `src/game/replay_menu_runtime.cpp` (2): `0x004315C0`, `0x00433570`
- `src/game/replay_progress.cpp` (2): `0x00412FF0`, `0x00415DB0`
- `src/game/result_menu_open.cpp` (1): `0x00423370`
- `src/game/scheduler.cpp` (13): `0x00420C00`, `0x00421F60`, `0x00422C30`, `0x0042C730`, `0x0042C750`, `0x00449AE0`, `0x00449B70`, `0x00449C00`, `0x00449D40`, `0x00449ED0`, `0x00449F60`, `0x0044A000`, `0x0044A030`
- `src/game/score_cleanup.cpp` (1): `0x0041C850`
- `src/game/score_queue.cpp` (1): `0x0041C510`
- `src/game/score_tasks.cpp` (3): `0x00413A20`, `0x0041C330`, `0x0042AF20`
- `src/game/score_timer_leaves.cpp` (3): `0x00418A90`, `0x00418B80`, `0x0042C5C0`
- `src/game/shot_practice_menu.cpp` (1): `0x00430A60`
- `src/game/slot_lock_leaves.cpp` (2): `0x00421C50`, `0x00421D20`
- `src/game/stage_tip_parser.cpp` (1): `0x00419960`
- `src/game/stage_tips.cpp` (1): `0x00418D00`
- `src/game/thread_spawn.cpp` (1): `0x00420EA0`
- `src/game/title_assets.cpp` (1): `0x0041F990`
- `src/game/title_options_menu.cpp` (1): `0x0042D920`
- `src/game/ui_final_runtime.cpp` (5): `0x00409280`, `0x00414900`, `0x00415E90`, `0x0042E5A0`, `0x0042F8B0`
- `src/game/version_list.cpp` (1): `0x00420DD0`
- `src/game/weather_pool.cpp` (1): `0x0042B6F0`
- `src/math/math_utils.cpp` (2): `0x004049A0`, `0x00404D40`
- `src/math/oriented_rect.cpp` (1): `0x0041E4D0`
- `src/math/vector2_polar.cpp` (1): `0x0044C5D0`
- `src/platform/bgm_streamer_refill.cpp` (1): `0x0044D850`
- `src/platform/dinput_device_setup.cpp` (1): `0x0043B8D0`
- `src/platform/file.cpp` (17): `0x00435340`, `0x00435370`, `0x00435460`, `0x00435490`, `0x004354D0`, `0x00435510`, `0x00435530`, `0x00435550`, `0x00435580`, `0x00435610`, `0x0044B4D0`, `0x0044B540`, `0x0044B620`, `0x0044B6B0`, `0x0044B740`, `0x0044B790`, `0x0044B7E0`
- `src/platform/font_surface_blend.cpp` (1): `0x00437750`
- `src/platform/joystick_poll.cpp` (1): `0x0044A190`
- `src/platform/path.cpp` (2): `0x00417010`, `0x0043D2A0`
- `src/platform/sound_stream_create.cpp` (1): `0x0044C8F0`
- `src/platform/text_log.cpp` (2): `0x0044B810`, `0x0044B8E0`
- `src/platform/window.cpp` (10): `0x00438AD0`, `0x004390E0`, `0x004392E0`, `0x00439390`, `0x00439730`, `0x00439FF0`, `0x0043A290`, `0x0043AA60`, `0x0043AE20`, `0x0043AEB0`
- `src/render/animation_manager.cpp` (49): `0x0040C480`, `0x0040C4D0`, `0x0043DC90`, `0x0043E460`, `0x0043E710`, `0x0043E7E0`, `0x0043E8B0`, `0x0043EC70`, `0x0043ED00`, `0x0043EDA0`, `0x004423C0`, `0x00446220`, `0x00447050`, `0x004477D0`, `0x00447810`, `0x00447940`, `0x00447F70`, `0x00448860`, `0x00448900`, `0x00448980`, `0x004489D0`, `0x00448A50`, `0x00448AC0`, `0x00448B40`, `0x00448BB0`, `0x00448D00`, `0x00448D50`, `0x00448DB0`, `0x00448E30`, `0x00448F60`, `0x00449090`, `0x004491C0`, `0x00449210`, `0x00449250`, `0x004492A0`, `0x004492F0`, `0x00449350`, `0x004493E0`, `0x00449450`, `0x00449470`, `0x00449590`, `0x004495E0`, `0x00449630`, `0x00449670`, `0x004496A0`, `0x004496D0`, `0x004497D0`, `0x00449870`, `0x00449950`
- `src/render/anm_entry_load.cpp` (1): `0x00447470`
- `src/render/anm_pending_service.cpp` (1): `0x00447700`
- `src/render/anm_record_walk.cpp` (1): `0x00403A30`
- `src/render/anm_script_table_sweep.cpp` (1): `0x00403990`
- `src/render/anm_surface_restore.cpp` (3): `0x00446D70`, `0x00447FD0`, `0x00448120`
- `src/render/anm_texture_upload.cpp` (3): `0x00446C70`, `0x00446F40`, `0x004473C0`
- `src/render/camera_apply.cpp` (1): `0x004215A0`
- `src/render/d3d_init.cpp` (1): `0x00439890`
- `src/render/device_reset.cpp` (1): `0x004391F0`
- `src/render/effect_ring.cpp` (1): `0x004452F0`
- `src/render/game_render_targets.cpp` (3): `0x00438A60`, `0x00443F80`, `0x00444580`
- `src/render/projection_quads.cpp` (3): `0x00403090`, `0x00443B60`, `0x00444240`
- `src/render/quad_transform_draw.cpp` (1): `0x00444760`
- `src/render/rect_fan_draw.cpp` (1): `0x004450E0`
- `src/render/render_stage_select.cpp` (1): `0x00401D20`
- `src/render/special_quad.cpp` (2): `0x0043BDA0`, `0x0043C500`
- `src/script/ecl_core_interpreter.cpp` (15): `0x0044DF70`, `0x0044E1A0`, `0x0044FDB0`, `0x0044FE40`, `0x0044FF00`, `0x0044FF80`, `0x00450030`, `0x00450070`, `0x004500D0`, `0x00450160`, `0x00450190`, `0x004501B0`, `0x004505B0`, `0x00450690`, `0x004506D0`
- `src/script/script_text_reader.cpp` (1): `0x00419F40`
- `src/util/runtime_pool.cpp` (1): `0x004388F0`

### player

86 files, 246 addresses, 95131 tracked retail bytes.

- `src/archive/score_save.cpp` (4): `0x0041A200`, `0x0042B1E0`, `0x004359B0`, `0x00436000`
- `src/game/archive_cursor_open.cpp` (1): `0x0044DBF0`
- `src/game/ascii_overlay_callbacks.cpp` (3): `0x0043C2C0`, `0x0043C410`, `0x00447AE0`
- `src/game/boss_overlays.cpp` (2): `0x0040E5F0`, `0x0041D7C0`
- `src/game/bullet.cpp` (16): `0x0040AE70`, `0x0040AF00`, `0x0040AF90`, `0x0040B250`, `0x0040C6E0`, `0x0040CC70`, `0x0040CEA0`, `0x0040CF40`, `0x0040CF60`, `0x0040CF90`, `0x0040CFB0`, `0x0040D680`, `0x0040D830`, `0x0040DC80`, `0x0044BC70`, `0x0044C2A0`
- `src/game/bullet_anim_release.cpp` (1): `0x0040B3A0`
- `src/game/effect_pool_update.cpp` (1): `0x00428280`
- `src/game/ending_text.cpp` (1): `0x0040BA90`
- `src/game/enemy_grid_scan.cpp` (1): `0x004073E0`
- `src/game/enemy_motion_steps.cpp` (6): `0x00407560`, `0x00407780`, `0x004078E0`, `0x00407A30`, `0x00407BE0`, `0x00407EF0`
- `src/game/entity.cpp` (9): `0x00401DE0`, `0x00401FF0`, `0x00402050`, `0x00405D00`, `0x00405DE0`, `0x00406160`, `0x004061D0`, `0x0041AD60`, `0x00438A30`
- `src/game/floating_text_draw.cpp` (1): `0x0042B780`
- `src/game/game_config_defaults.cpp` (1): `0x00418C40`
- `src/game/game_mode_switch.cpp` (1): `0x004218D0`
- `src/game/game_thread.cpp` (6): `0x00401000`, `0x00401110`, `0x00401260`, `0x00401440`, `0x00401760`, `0x00401A50`
- `src/game/game_thread_text_draw.cpp` (1): `0x00447BB0`
- `src/game/item_field_contact.cpp` (1): `0x004266B0`
- `src/game/item_spawn.cpp` (1): `0x0041BB00`
- `src/game/laser_line.cpp` (2): `0x0041D3D0`, `0x0041F400`
- `src/game/linked_pool_append.cpp` (1): `0x0042AA50`
- `src/game/linked_pool_release.cpp` (1): `0x0042AB20`
- `src/game/manager_factories.cpp` (13): `0x00408910`, `0x00408C90`, `0x0040D6B0`, `0x00413810`, `0x00414830`, `0x0041AED0`, `0x0041AFD0`, `0x00429610`, `0x004296F0`, `0x0042AE60`, `0x0042B4D0`, `0x0043C8B0`, `0x0043C970`
- `src/game/menu.cpp` (1): `0x0044BEA0`
- `src/game/name_entry.cpp` (3): `0x004224C0`, `0x00423570`, `0x00432CB0`
- `src/game/pause_result_open.cpp` (1): `0x004231D0`
- `src/game/player_front_runtime.cpp` (1): `0x00413BC0`
- `src/game/player_motion.cpp` (5): `0x0040678E`, `0x004074B0`, `0x004076A0`, `0x00407DA0`, `0x00407E40`
- `src/game/practice_stage_menu.cpp` (1): `0x00430FF0`
- `src/game/progress_worker.cpp` (1): `0x0042CD50`
- `src/game/replay_browser_draw.cpp` (1): `0x00431BA0`
- `src/game/replay_runtime_bootstrap.cpp` (1): `0x00428F60`
- `src/game/replay_score_draw.cpp` (1): `0x004329F0`
- `src/game/replay_stage_name_draw.cpp` (1): `0x00433230`
- `src/game/result_overlay.cpp` (1): `0x004172E0`
- `src/game/result_screen_effects.cpp` (1): `0x0041FDD0`
- `src/game/score.cpp` (34): `0x00408030`, `0x00408660`, `0x004086B0`, `0x00408750`, `0x004088C0`, `0x004089C0`, `0x00408D60`, `0x004091C0`, `0x00409230`, `0x00409270`, `0x00409D90`, `0x00409E20`, `0x0040AC20`, `0x0040AC90`, `0x0040ACE0`, `0x0040AD20`, `0x0040B9D0`, `0x00412E70`, `0x0041BE80`, `0x0041BEB0`, `0x0041C030`, `0x0041C1C0`, `0x0041C5B0`, `0x0041C7D0`, `0x0041C800`, `0x0041F7A0`, `0x00426610`, `0x00426660`, `0x00428D70`, `0x0044A4E0`, `0x0044B010`, `0x0044B080`, `0x0044BE20`, `0x0044BE70`
- `src/game/score_file.cpp` (3): `0x00421FA0`, `0x0042ACB0`, `0x0042B030`
- `src/game/score_menu_rows.cpp` (1): `0x00431410`
- `src/game/spell_card_dispatch.cpp` (1): `0x0042A6A0`
- `src/game/spell_timer.cpp` (1): `0x004127A0`
- `src/game/sprite_descriptor.cpp` (1): `0x00424480`
- `src/game/sprite_test_overlay.cpp` (2): `0x0040A940`, `0x0042C360`
- `src/game/stage_background.cpp` (2): `0x0040C3C0`, `0x00427960`
- `src/game/stage_focus_fade.cpp` (1): `0x00419650`
- `src/game/stage_slot_state.cpp` (1): `0x00415B00`
- `src/game/stage_text.cpp` (3): `0x004349E0`, `0x00434A20`, `0x00434A80`
- `src/game/stage_update.cpp` (1): `0x00418190`
- `src/game/task_registration.cpp` (3): `0x00413980`, `0x0041C120`, `0x0042CAA0`
- `src/game/title_menu_runtime.cpp` (1): `0x0042CDF0`
- `src/game/trigger_activation.cpp` (1): `0x00426CF0`
- `src/math/angle.cpp` (1): `0x0044BC10`
- `src/math/rng.cpp` (4): `0x0044B9E0`, `0x0044BA80`, `0x0044BB20`, `0x0044BB90`
- `src/math/timer.cpp` (4): `0x00404ED0`, `0x00428DD0`, `0x0042C620`, `0x0044BF40`
- `src/math/vector3_cross.cpp` (1): `0x00421B90`
- `src/platform/all_source_runtime.cpp` (2): `0x004054B0`, `0x0044C150`
- `src/platform/font_texture_draw.cpp` (2): `0x00437DB0`, `0x00437FE0`
- `src/platform/gdi_font_cache.cpp` (2): `0x00436A30`, `0x00437D10`
- `src/platform/joystick_property.cpp` (1): `0x0044C7E0`
- `src/platform/memory_file.cpp` (12): `0x00436210`, `0x00436260`, `0x004362B0`, `0x00436330`, `0x00436370`, `0x004363C0`, `0x00436430`, `0x00436460`, `0x004364D0`, `0x004364E0`, `0x0043D250`, `0x0043D390`
- `src/platform/midi_sequencer.cpp` (4): `0x0043A730`, `0x0043AAD0`, `0x0043ACE0`, `0x0043AF30`
- `src/platform/process.cpp` (5): `0x00436570`, `0x0044BD10`, `0x0044C100`, `0x0044C130`, `0x0044D5B0`
- `src/platform/resource_file.cpp` (3): `0x00436680`, `0x004366C0`, `0x00436CA0`
- `src/platform/sound_commands.cpp` (9): `0x0043A910`, `0x0043D120`, `0x0043D7D0`, `0x0043D950`, `0x0043DDF0`, `0x0044CBF0`, `0x0044CF20`, `0x0044D110`, `0x0044DAD0`
- `src/platform/sound_device_init.cpp` (1): `0x0043CD30`
- `src/platform/sound_fade.cpp` (1): `0x00421E00`
- `src/platform/sound_stream_start.cpp` (1): `0x0044D440`
- `src/platform/sound_worker.cpp` (1): `0x0043CC40`
- `src/platform/worker_start.cpp` (1): `0x0044C1C0`
- `src/render/animation_slot.cpp` (1): `0x004136C0`
- `src/render/anm_archive.cpp` (2): `0x004470C0`, `0x004472E0`
- `src/render/anm_handle_release.cpp` (1): `0x00421300`
- `src/render/anm_propagate.cpp` (2): `0x00409E50`, `0x0042C770`
- `src/render/anm_vm_draw_dispatch.cpp` (1): `0x004451C0`
- `src/render/default_viewport.cpp` (1): `0x0043C1A0`
- `src/render/edge_strips.cpp` (2): `0x00444B10`, `0x00444BE0`
- `src/render/effect_ring_update.cpp` (1): `0x00445620`
- `src/render/final_quad_pipeline.cpp` (1): `0x00442670`
- `src/render/fog_disable.cpp` (1): `0x00420CD0`
- `src/render/image_alpha_transform.cpp` (1): `0x00437160`
- `src/render/texture_stage_reset.cpp` (1): `0x0043BFA0`
- `src/render/transparent_pixel_fill_locked.cpp` (1): `0x004465B0`
- `src/script/ecl_vm.cpp` (2): `0x00412A00`, `0x00412A10`
- `src/script/ecl_vm_children.cpp` (1): `0x0044FD10`
- `src/script/final_script_runtime.cpp` (2): `0x00450470`, `0x00450700`
- `src/script/stage_ecl_load.cpp` (1): `0x00403850`
- `src/util/heap.cpp` (20): `0x00418150`, `0x0042CDB0`, `0x00435220`, `0x00435250`, `0x004352C0`, `0x004381F0`, `0x00438250`, `0x00438260`, `0x00438350`, `0x00438380`, `0x00438420`, `0x00438510`, `0x00438590`, `0x00438680`, `0x00438690`, `0x004386A0`, `0x004386B0`, `0x0043874C`, `0x00438800`, `0x00438840`
