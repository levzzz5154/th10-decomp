# TH10 readability handoff — 2026-10-16 (final)

Steps 1–6 of the readability plan are complete and verified. HEAD `3595801d`
on `main`, tree clean.

## What this batch does

- Names every remaining `data_` global — the 0x491C00 application block,
  .data, bss and the .rdata constants — by its owner or content:
  - app block: `g_main_mode_request` (0x491C00), `g_main_state` (0x491FB8),
    `g_app_flags` (0x491FF4), `g_direct3d` (0x491C2C), `g_key_bindings`
    (0x491D4C), `g_music_volume`/`g_effect_volume` (0x491D68/69), the two
    render-stage cameras `g_back_camera` (0x491D7C, five more floats) and
    `g_front_camera` (0x491E94), `g_screen_shake_x/y` (0x491E64/68),
    `g_projection_world/view/matrix` (0x491DC8/E08/E48),
    `g_thread_sync` (0x492274) with its `g_scheduler/file/text_log/timer_lock_depth`
    bytes, `g_main_window` (0x4924F0), `g_qpc_frequency` (0x492508) …
  - .data: `g_stage_routes` (0x474788), `g_title_demo_paths` (0x476FF8),
    `g_title_idle_frames` (0x474CA4), `g_input_keys_raw/edge/held`
    (0x474E30/E34/E36), `g_key_bindings_current` (0x474E88),
    `g_bullet_script_first` (0x474170) …
  - bss: `g_midi_worker_state` (0x497798), `g_keyboard_state` (0x497AA8),
    `g_recovery_script_path` (0x497C38), the CRT block (`g_crt_locale_data`,
    `g_crt_tls_index`, `g_crt_lock_table`, `g_crt_heap_handle`, …),
    `g_font_height_32..60` (0x4918A0..0x491868, named by their CreateFontA
    heights).
  - .rdata by content: `g_dinput_keyboard/joystick_format`,
    `g_guid_syskeyboard`, `g_spell_seq_codes`, `g_resource_dat_suffix`,
    `g_texture_formats_a/b`, `g_enemy_vtable_live/released`,
    `g_beam/line_laser_vtable`, `g_title_vtable`, …
- Drops the address suffix from 1,317 single-variant identifiers and the
  highest-use helpers (`crt_free`, `crt_free_startup`, `AnimationBank`,
  `AnimationResourceFile`, `RecoveryLookupContext`, `IntArg`, `HintVm`,
  `RecoveryTextVm`, `SchedulerTask_Create`, `AnimationManager_Find`, …),
  including the mangled forms inside the JSON symbol maps.
- Renames 2,781 `*_00XXXXXX` files and 54 dependency/context directories to
  readable names, with all `#include` lines, cluster manifests, regions.json
  and the translation-unit list updated. The two data aliases that follow
  renamed types (`??_7ScriptParser@@6B@`, `??KCellPairDivide@@QBE?AU0@ABU0@@Z`)
  follow as well.

## Deliberate leftovers (documented skips)

- The two identity-colliding replay clusters keep their addresses:
  `replay_manager_create_00429610` and `replay_manager_create_004296f0`
  (two distinct entry points, one stem), likewise the two
  `recovery_script_executor_caller` views (0x00419120 → `…caller.cpp`,
  0x00433EF0 → `…caller_00433ef0.cpp`).
- `fun_*`, `FUN_*`, `unassigned_*`, `Unassigned*`, `thunk_*`, `dtor_*`,
  `set_*`, `Slot_*` scratch names in `src/unreferenced/` and
  `src/crt/` (≈870 files): their identity is the address until someone
  identifies the function.
- `asm_*` (1,246 uses), `ObjectAccessor_*` (560 distinct accessor sites),
  `semantic_import_thunk_*` (96) and `reserved_00000000`/`unknown_00000000`
  byte-run placeholders: build machinery and padding markers, not game names.
- Data globals the evidence conflicts on or nothing writes:
  0x474C98 was resolved as `g_rank`; the handoff-earlier skips
  0x474C98/0x477848 etc. are now named or absorbed into
  `g_stage_routes`/`g_stage_route_current`. No `data_00XXXXXX` identifier
  remains in src/, include/ or build_support.

## Fixed at the end

The bulk rename first rewrote path strings inside `#include` lines and JSON
manifests, producing wrong candidates (e.g. `replay_manager_create_00429610.cpp`
pulled into the 004296f0 cluster). Every path was restored from git and
re-pointed at the renamed files; the compiler-includes log of each affected
cluster was checked. `familiar_refresh`/`laser_script_run`/
`player_initialize` dependency directories are renamed with their manifests.
The f0 cluster manifest pointed at the 610 driver after the move — fixed.

## Verification

- `make`: SHA-256 `19efafbd58a4e4c0…`
- `make EXACT=1`: SHA-256 `2f14760b6fbbf575…`
- Recovered: 100.0% of bytes (322,064 of 322,064), 100.0% of regions
  (2,322 of 2,322); byte-exact alone 72.7%.
- `callsite_abi.py` passes (run through `.venv`).
- All 129 unit tests pass; `git diff --check` clean.

## Next

Nothing outstanding for the readability plan. If the scratch names in
`src/unreferenced/` are ever identified, rename them then; the build must
still report the two hashes above.
