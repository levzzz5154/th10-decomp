# IDA Pro cross-check and recovery priorities

Generated from `th10.exe.asm`, `th10.exe.c`, and the matching2 function registry. IDA output is treated as independent evidence, not compilable source.

## Applied correction

- Corrected `EffectRing_Update` at `0x00445620` to use `0.2026834f`, the retail float at `_DAT_00470B6C` and `float32(2*pi/31)`.
- Updated the batch-22 test so vertices 9 and 31 are checked against the retail step; the previous quarter-turn assertion encoded the incorrect `2*pi/32` assumption.
- The focused batch-22 test passes after the correction.

## Batch-22 cross-check

| Address | Ghidra span | IDA signature | Semantic name | Result |
|---|---:|---|---|---|
| `0x0040BA90` | 656 bytes | `int *__stdcall sub_40BA90(int *a1, int a2)` | `EndingText_Construct` | 0xEC-byte clear; 5 iterations; scripts 0x42..0x46; layer 15; flags 0x40000000/2; three timer initializations; final color 0x00FFFFFF. |
| `0x0044D850` | 640 bytes | `int __stdcall sub_44D850(unsigned int a1, int a2)` | `Streamer_RefillSegment` | Entry and end at the same tracked boundary; DirectSound Lock/Unlock offsets; 0x800401F0 busy and 0x8000FFFF unexpected-region results; cursor wrap and write-offset modulo behavior agree. |
| `0x00445620` | 656 bytes | `int __thiscall sub_445620(int this)` | `EffectRing_Update` | 31 rim iterations; 11 groups of 3 vertices for 33-entry U/V wrap; 0x1C-byte closing-vertex copy; thiscall receiver. IDA data decodes _DAT_00470B6C as 0.2026834f = float32(2*pi/31). |

### Calling-convention interpretation

- IDA labels `0x0040BA90` and `0x0044D850` as `__stdcall`, and `0x00445620` as `__thiscall`. The cleaned C++ uses explicit state/environment parameters, so these are ABI evidence for bridge code rather than signatures that must be copied literally.
- No batch-22 function boundary disagreement was found between the IDA procedure starts and the Ghidra registry.
- The null-handle guards in `EndingText_Construct` remain an intentional semantic safety adaptation: retail immediately dereferences after a registration path expected to succeed.

## Corpus and boundary findings

- IDA assembly contains **1233** named `sub_*` procedures; **684** overlap the **703** Ghidra registry starts.
- **19** Ghidra starts have no matching IDA `proc near` label: `0x0040678E`, `0x0040E770`, `0x00427D80`, `0x0042B6F0`, `0x00434CA0`, `0x004381F0`, `0x00438723`, `0x0043874C`, `0x004387C2`, `0x00438AD0`, `0x0043D790`, `0x00447FD0`, `0x00448900`, `0x00449A90`, `0x0044BD10`, `0x0044C100`, `0x0044C130`, `0x0044CF00`, `0x0044D710`.
- IDA adds **454** procedure starts in the game-code range. Approximate next-start gaps: <=16: 218, <=32: 57, <=128: 61, <=64: 55, >128: 63. Most are tiny wrappers, thunks, or alternate entries; do not bulk-import them as independent semantic functions.
- For function recovery, preserve the Ghidra registry as the primary inventory and use IDA-only starts as review candidates. Confirm each against callers, stack cleanup, and fall-through behavior.

## Continued recovery checkpoints

### `0x00427E90` — effect watch spawner

- Promoted as `EffectWatch_SpawnFromDescriptor` in `src/game/effect_indicator_slots.cpp`.
- Recovered the 128-slot scan, mode-3 source suppression, timer setup, relative origin calculation, polar/carry path, animation creation, callback, and sound paths.

### `0x00401760` — queued text renderer

- Promoted as `GameThread_DrawQueuedText` in `src/game/game_thread_queue.cpp`.
- Recovered per-record view switching, fixed/proportional advances, newline and space handling, 2x98 glyph-bank selection, half-alpha shadows at +2/+2, main-glyph drawing, and final restoration to view 0.
- Focused tests cover view transitions, glyph indices, shadows, newline advancement (including retail's extra horizontal advance), fixed-width mode, and the empty queue.

### `0x0043D390` — pending RIFF/WAVE sound-buffer loader

- Promoted as `SoundWave_LoadPending` in `src/platform/memory_file.cpp`.
- Recovered the disabled-bank exit, existing-buffer release, 10 ms asynchronous wait/cancellation loop, pending-slot consume, RIFF/WAVE and `fmt `/`data` parsing, 18-byte format copy, DirectSound flags `0x80C8`, create/lock/two-region copy/unlock sequence, diagnostics, and owned-image release.
- Focused tests cover a split lock region, exact PCM bytes and format fields, malformed input, disabled-bank ownership, and the retail buffer flags.

### `0x004269D0` — spell/attack timeout transition

- Promoted as `SpellTimeout_EnterTransition` in `src/game/spell_timeout.cpp`.
- Recovered bonus decay toward 5000, countdown publication, two timer resets, sound stop, four animation-pair retirements, optional `Caution!` tip, frame-60 player/option flag clearing, and transition-gauge clamp to `[-1024, 1024]`.
- Focused tests cover timer images, all eight animation handles, warning suppression, player-frame gating, countdown behavior, bonus decay, and both gauge clamps.

### `0x0043CD30` — sound worker-thread initializer (batch 24)

- Promoted as `SoundDevice_InitializeWorker` in `src/platform/sound_device_init.cpp`.
- Evidence: the thread entry `StartAddress` (`0x0043CCF0`) passes the device context (`Parameter`, `0x00492590`) and window `dword_4977B8`; the helpers `0x0044C7E0` (primary-format setter), `0x0044B810` (logger), and `0x0043D390` (`SoundWave_LoadPending`) are all recovered; `aDirectsound`/`aDirectsound_0` are the identical string `"DirectSound "` and `aErrorSound` is `"error : Sound "`.
- Recovered the 128-handle/12-music-slot reset, DirectSoundCreate8 + SetCooperativeLevel(2) with logged teardown, the ignored primary-format request (16-bit/stereo/44100), the 0x8000-byte looping stream buffer (create/lock/zero/unlock/play), the 250 ms window timer, and the 37-file WAV preload gated on the shutdown word `dword_4977B4`.

### `0x00417870` — stage-entry orchestrator (batch 25)

- Promoted as `StageContext_Enter` in `src/game/stage_entry.cpp`, together with its task callbacks `0x004187C0` (`StageTask_UpdateThunk`, the `push ecx; call sub_418190` adapter — the stage tick `0x00418190` is still unrecovered and stays injected) and `0x004187D0` (`StageTask_ClearCameraOnIdle`). The two callbacks are not among the 722 tracked exports, so the ledgers move by one function.
- Hex-Rays' "possibly undefined" `v1`/`v17` at the `0x00421300`/`0x00421070` call sites are phantom `ecx` reads; the assembly pushes `offset dword_491C28` as the single stack argument for both calls.
- Every other callee was already recovered, so the orchestrator binds to documented hooks: sync-pair wait with the UI abort bit `0x80`, fresh-run score/lives/power seeding from the 17276-byte score-file records (stage practice forces difficulty 4; play count capped at 99999 and skipped for replays), update/draw task registration at priorities 10/4, the 52-byte stage-descriptor copy, the replay short path (`0x0042A6A0`/`0x00413A20`/`0x00402640`) vs. the nine-step construction chain, the spell-practice (`0x00417800`) vs. enemy-manager (`0x0040D6B0`) branch, the optional music pair, camera-shake reset, player-spawn arm, loader wait, pending-ANM release, and the shared failure exit that marks both task nodes and leaves the entry bit set.

### `0x00422660` — result replay/ranking renderer (batch 26)

- Promoted as `ResultMenu_DrawReplayAndRanking` in `src/game/result_menu_draw.cpp`.
- Recovered paired states 10/17, 11/18, and 12/19: the 25 replay rows with selection colors and timestamps, the ten-frame name-grid tween, the score-ranking title and optional cursor, and ten 24-byte score rows selected from the 17276-byte character/stage record at the 240-byte difficulty offset.
- Assembly confirms the score row fields at +24 score, +28 stage byte, +29 power byte, +30 ten-byte name, and +40 timestamp, plus the renderer busy/color words at game-thread offsets 0x8988/0x8974.

### `0x00433B30` — replay-manager renderer (batch 27)

- Promoted as `ReplayManager_Draw` in `src/game/replay_menu_draw.cpp`.
- Recovered state 2's 25 replay rows (date/time, character/shot, difficulty, stage, clear percentage), state 3's animated selected row, the delayed entered-name/underscore display, and the 13-column charset grid.
- The final three charset positions preserve the retail special glyph remap 129/127/128; name cursor position 8 preserves the one-cell x correction.

### `0x00428630` — player collectible/score-field collision sweep (batch 28)

- Promoted as `Player_CollectAndScoreFields` in `src/game/player_pickup_sweep.cpp`.
- Recovered the 128-slot pickup sweep, descriptor AABBs and type-specific zero-line gate, optional descriptor callback, one-time collection animation stop, type-3 four-frame value gate, ordinary pickup animation replacement, type-2 indicator spawn, and player hit-test contribution.
- Recovered all 32 score regions: interval suppression, axis-aligned and rotated rectangle overlap, circular overlap, value accumulation/expiry, raw-value return, score conversion `(value / 10 + 10) / 10`, and the 999,999,999 cap.

### `0x004172E0` — result-overlay mode constructor (batch 29)

- Promoted as `ResultOverlay_SetMode` in `src/game/result_overlay.cpp`.
- Recovered scripts 71–76 for modes 0–4/6 and mode 0's eight registered digit VMs (scripts 39–46, layer 15, flag 0x40000000).
- The decimal splitter preserves the 10,000,000-to-1 divisor walk, sprite index `digit + 8`, and retail leading-zero visibility behavior (zero hides all eight positions).

### `0x0041BB00` — item-manager spawn allocator (batch 30)

- Promoted as `ItemManager_Spawn` in `src/game/item_spawn.cpp`.
- Recovered the first-free scan over 150 normal slots, x clamp to [-192, 192], motion/timer reset, bomb-fragment kind remapping, previous-kind-3 cleanup, display-kind/script special cases for kinds 10/11, and identifier publication.
- Kind 8 uses the separate 2048-slot ring, increments its lifetime spawn count even on an occupied slot, advances with wrap, and selects the four density bands (`cursor % 4`, `% 8 + 4`, `% 16 + 8`, `% 32 + 16`).

Coverage is now **604 semantic functions**, with **77 unrecovered**.

## Hex-Rays coverage of the recovery backlog

- **37 of 87** unrecovered Ghidra functions have a Hex-Rays body.
- The two recovered bodies removed one `__fastcall` and one `__stdcall` candidate from the IDA-backed backlog.
- `ida_unrecovered_priorities.tsv` contains all candidates with repository score, size, dependencies, test proximity, IDA signature, and simple complexity indicators.

## Recommended first recovery set

| Tier | Score | Address | Bytes | Deps | Tests | Subsystem | IDA convention | Body lines |
|---|---:|---|---:|---:|---|---|---|---:|
| A | 8 | `0x0041D3D0` | 1008 | 0 | yes | `game_systems` | `__thiscall` | 145 |
| A | 7 | `0x0041F400` | 928 | 1 | yes | `score` | `__thiscall` | 93 |
| A | 7 | `0x00428280` | 944 | 1 | yes | `recovery_leaves` | `__stdcall` | 232 |
| A | 7 | `0x0043CD30` | 1008 | 1 | yes | `sound_device_init` (recovered: `SoundDevice_InitializeWorker`) | `__thiscall` | 141 |
| B | 7 | `0x00417870` | 1040 | 0 | yes | `stage_entry` (recovered: `StageContext_Enter`) | `__stdcall` | 169 |
| B | 7 | `0x00422660` | 1072 | 0 | yes | `result_menu_draw` (recovered: `ResultMenu_DrawReplayAndRanking`) | `__stdcall` | 164 |
| B | 7 | `0x00428630` | 1520 | 0 | yes | `recovery_leaves` | `__thiscall` | 212 |
| B | 6 | `0x00433B30` | 960 | 0 | yes | `replay_menu_draw` (recovered: `ReplayManager_Draw`) | `__stdcall` | 153 |
| B | 6 | `0x0041EFA0` | 1120 | 1 | yes | `score` | `__thiscall` | 183 |
| B | 6 | `0x0041EB00` | 1184 | 1 | yes | `spell_timeout` | `__thiscall` | 206 |
| B | 6 | `0x0040BD80` | 1600 | 1 | yes | `recovery_leaves` | `__stdcall` | 275 |
| B | 6 | `0x0043AF30` | 480 | 2 | no | `window` | `__thiscall` | 51 |
| C | 7 | `0x00406D90` | 1616 | 0 | yes | `manager_factories` | `__thiscall` | 293 |

### Triage rules

- **Tier A:** high repository score and at most 1024 bytes; start here.
- **Tier B:** useful Hex-Rays body with moderate size/score; recover after the Tier A neighborhood.
- **Tier C:** large, dependency-heavy, or lower-confidence bodies; use IDA mainly for constants, call targets, and control-flow confirmation.
- Before promoting any body, reconcile register parameters and `__usercall` callers against the assembly. Hex-Rays bodies with ordinary signatures are easier starting points, but their types are still guesses.


## Resolved roadblock: `0x0041D3D0` -> `LaserLine_Update` (batch 23)

The previous stop at `0x0041D3D0` was declared for missing type evidence: 11 virtual dispatches with "no constructor or caller identifying the concrete subclass or vtable." That evidence exists in the IDA export and in the repository itself:

- `0x0041D3D0` is slot `+0x08` of the 19-slot vtable `off_46DA60` in `.rdata`, one of three sibling vtables (`off_46DA10`, `off_46DA60`, `off_46DAB0`) sitting next to the allocation-site strings `.\src\game\laser.cpp:227 LaserLineInf` and `laser.cpp:236 LaserInfiniteInf`, which identify the family as the laser pool.
- The constructor `0x0041C5B0` installs `off_46DA60`; it was **already recovered** in `src/game/score.cpp` as `ScoreExtendedObject_Initialize` (the historical name predates the laser evidence; the symbol is kept, the doc note records the correction).
- The factory `0x0041C510` proves the dynamic type: selector 0 allocates 0xD58 bytes and calls `0x0041C5B0` (`off_46DA60`, the line laser); selector 1 allocates 0xD74 bytes and calls `0x0041C680` (`off_46DA10`, the infinite-laser variant). The bounce handler `0x0041CFD0` (recovered, batch 14) re-enters the same factory with selector 0.
- Every "unresolved" virtual slot has a concrete binding: `+0x00 -> 0x0041CA80` (command stream), `+0x18 -> 0x0041D880` (player-hit callback), `+0x28 -> 0x0041D2C0` (recovered, batch 10), `+0x30 -> 0x0041D170` (turn step), `+0x3C -> 0x0041CFD0` (recovered, batch 14), and seven nullsubs (`+0x24/+0x2C/+0x34/+0x38/+0x40/+0x44/+0x48`).

The function is promoted as `LaserLine_Update` in `src/game/laser_line.cpp` with the resolved dispatch table modeled as documented hooks (`include/th10/game/laser_line.hpp`) and covered by `tests/laser_line_test.cpp` (flag dispatch order and live flag re-reads, flash/hold timer countdowns, growth vs. tail-consumption phases, total-length retirement, off-screen culling, hit/graze classification incl. both half-width branches and the every-5th-frame graze gate, and animation-VM rescale/tick rules).

## Validation

- Focused batch-28 collision, batch-29 overlay, and batch-30 item-spawn tests: pass.
- Full `bash test.sh`: pass, including batches 9-30 and standalone startup-to-title `SMOKE_PASS`.
- Coverage: 604 semantic functions, 77 unrecovered, 637/722 readable implementations (88.2%).
- Standalone readiness remains 179/179 source-ready, 70,320/70,320 bytes, zero blockers, and 144/144 indirect calls audited.


## Recovery batches 31–42

- **Batch 31, `0x0040C9D0` — `ItemDrop_ScatterGroups`:** recovered the eleven item-kind groups, elliptical randomized placement, angle progression/normalization, retail spawn constants, and clearing of all twelve count words.
- **Batch 32, `0x00444CE0` — `Renderer_DrawTexturedEdgeStrip`:** recovered validation, pending flush, texture/FVF caches, stage-state writes, and the indexed edge-strip draw parameters.
- **Batch 33, `0x0043B8D0` — `Input_InitializeDevices`:** recovered DirectInput/keyboard setup, exact cooperative flags, failure cleanup, acquire, and optional joystick configuration.
- **Batch 34, `0x0044C8F0` — `SoundStream_CreateSegmented`:** recovered segmented buffer construction, notification offsets, event publication, and HRESULT-style failures.
- **Batch 35, `0x00444760` — `Renderer_DrawTransformedQuad`:** recovered matrix dirty-state rebuild, XYZ rotations, anchor modes, world/texture transforms, texture cache, vertex mode 2, and `DrawPrimitive(5,0,2)`.
- **Batch 36, `0x00402CA0` — `CompositeEffect_Draw`:** recovered the two staged passes, optional four-quad pass, render-state cache transitions, overlay colors, and fade completion.
- **Batch 37, `0x0041E260` — `LineEffect_SweepIntoItems`:** recovered the 12-unit line walk, script selection, display offsets, playfield gate, and optional kind-8 item drops.
- **Batch 38, `0x00412AC0` — `Trajectory_Evaluate2D`:** recovered embedded timer advancement, completion snap, linear/accelerated modes, cubic Hermite evaluation, and eased interpolation.
- **Batch 39, `0x0040A940` — `SpriteView_DrawDebugOverlay`:** recovered all four debugger display modes, colors, coordinates, numeric formatting, cursor placement, and gizmo draw.
- **Batch 40, `0x0042B780` — `TextBatch_DrawReverseGlyphs`:** recovered the 723-record scan, centered spacing, distance alpha, reverse character order, and three glyph banks.
- **Batch 41, `0x00431410` — `ScoreMenu_DrawRows`:** recovered state/timer gates, six ranking rows, unavailable formatting, selection colors, and confirmation blink.
- **Batch 42, `0x0041E700` — `Laser_UpdateState`:** recovered target-length growth, normalized angle/position motion, player attachment, states 3/4/2/5, width growth/shrink, hit/graze classification, VM scale synchronization, and retirement.

Each recovery set has a focused test under `tests/`; all groups are wired into `test.sh`.

## Batch-42 checkpoint validation

- Full `bash test.sh`: pass through batches 9–42.
- Standalone startup-to-title: `SMOKE_PASS` with clean shutdown.
- Coverage: 616 semantic functions, 65 unrecovered, 649/722 readable implementations (89.9%).
- Standalone readiness: 179/179 source-ready, 70,320/70,320 bytes, zero retail blockers, and 144/144 indirect calls audited.
