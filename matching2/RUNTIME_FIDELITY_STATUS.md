# Runtime Fidelity Status

This note records the boundary for the three researched functions. The
function ledger remains at 397 exact overlays, 322 semantic functions, and 3
researched functions until the remaining external behavior is represented.

## 0x00425730 Player Update

Implemented and regression-tested:

- Raw timer initialization ownership and conditional frame-delta pointer
  publication.
- Indicator velocity-Z clearing.
- Player-present, focus-object, hold-config, and game-over gates from the raw
  manager blocks.
- The `0x4250B0` focus latch at `+0x4474`, including its auxiliary-timer
  threshold and packed character/shot branch.

Still partial: collision/respawn, bullet-clear, death-fan, hold-update,
power-HUD, stage-transition, and animation-manager calls remain null hooks in
the standalone binding. Their retail owners are manager objects or callbacks
whose host object layouts and dispatch/trampoline contracts are not exposed by
the current standalone API. The tested null-hook path is intentional and is
not promoted as a semantic implementation.

## 0x00426F70 Attached Effects

Implemented and regression-tested:

- Retail `pl00/pl01` `*.sht` formation tables are populated into the PE32
  player-object allocation at `+0x20` and `+0x98`.
- The raw bridge reads the independent player-position array at `+0x43AC`,
  preserves focused alias ordering, accepts valid all-zero tables, and writes
  callback words at familiar `+0x90`.
- The i386 regression follows the `+0x45C` table pointer, verifies pair-B
  scaling, and verifies callback `0x00427950` persistence.

Still partial: raw callback words are persisted but no host trampoline invokes
those retail function addresses. Manager-owned animation operations are
represented through the existing adapter where available; unsupported manager
edges remain explicit partial state.

## 0x00433EF0 Music Room

Implemented and regression-tested: live sound-ID translation, played-table
callbacks, title-aware playback, BGM restoration, exact retail preview bytes,
and shared frame-speed timer advancement including paused/fractional frames.

Still partial: the host animation text surface preserves the Shift-JIS bytes
but renders through fixed-scale ASCII ANM lookup. Retail GDI/text layout and
high-byte glyph rendering require a font/text callback and layout surface that
the current standalone host API does not expose, so this behavior is not
claimed as semantic parity.

The title-to-Music-Room-to-main-menu route is covered by the 10-step menu
smoke. It shows no duplicate transition or shutdown behavior, but the smoke
does not prove retail pixel identity for title/music-manager ownership, so that
ownership is not promoted beyond the observed host behavior.

## Deterministic Reconstruction Trace

The standalone accepts `--trace PATH`; the option is disabled by default and
opens a JSONL stream only when explicitly requested. The schema is
`th10-recon-jsonl-v1`: resource events carry stable sizes and FNV-1a hashes,
VM events use monotonic IDs and script-relative program-counter offsets, VM
creation/destruction and input events are recorded, object events expose stable
manager handles, draw events carry script/resource/sprite metadata, and frame
events include canonical RGB pre-Present checksums when a D3D9 surface is
available. The emitter excludes pointers and wall-clock data. Repeated
`--trace ... --smoke` runs produce byte-identical streams.

`tools/compare_runtime_trace.py` compares two streams semantically, rejects
unstable pointer/address/timestamp fields, and requires every stable VM, ECL VM,
object, and entity identity to have exactly one teardown event.
`tests/runtime_trace_compare_test.py` covers matching, mismatch, and lifecycle
failures. `ecl_core_edges_test` also asserts the optional opcode observer
callback and instruction identity.

A retail-side machine-readable trace is still unavailable because the untouched
`th10.exe` has no injector or embedded probe. The bounded Wine debugger check
reaches retail `WinMain` but remains in the startup/modal/input barrier before
the frame and ANM anchors. The exact probe workflow and anchor list are recorded
in `matching2/docs/retail_trace_probe.md`. The reconstruction trace therefore
proves its own determinism and execution coverage but is not yet a retail
comparison.

## Deterministic Stage Trace

The ECL extended-dispatch bridge now gives each root/child VM a separate
retail-sized entity record and wires the shipped 0x100/0x101/0x104/0x105/0x10e
spawn family into `BulletEntity_Spawn`. The adapter marshals the dynamic
operand block, position, flags, and the entity +0xFC payload into the existing
0x68-byte enemy manager's intrusive list; `stage_spawn` records expose the
stable entity id, opcode, manager count, serial, and resolved position.
`tests/bullet_manager_test.cpp` covers the 0x2518-byte spawn layout and list
head/tail/count contract.

The leaf dispatcher also now matches retail descriptor ownership for `0x190`
(full 0x210-byte per-slot reset/default writes) and `0x191` (per-slot position
materialization plus an explicit launch callback into the existing 2,000-slot
bullet pool). The PE32 stage host owns that callback and initializes the retail
pool active word, row, position, and timer records; `ecl_vm_test` covers the
raw defaults, adjacent-slot isolation, position math, and callback contract.
The enemy manager now schedules each linked `BulletEntity` from its retail
priority-0x12 update callback. The embedded root record at entity+0x08 is
resolved from the spawn label, ticked with the entity frame scale, and retired
with balanced VM/entity lifecycle events. Core external-variable reads use a
short-lived resolver-vtable swap and restore the retail entity vtable before
returning; the extended dispatcher uses a private operand frame and restores
entity+0x2514 to self. Child VMs now tick through their owning entity only:
the stage walk retires root-owned children while the enemy-manager callback
ticks each enemy's own child list, matching `EclVm_TickChildren` (0x0044FD10).
Previously the stage loop ticked every live child, double-advancing enemy
children (a 180-frame child finished in 90 frames); the per-frame tick rate is
now one tick per stage frame for every VM. The bounded trace reaches real
enemy script calls, movement/flag leaves, and the 0x190/0x191 leaf family:
85 0x190 executions and 178 0x191 executions activate 178 pool slots (row 0)
through the launched callback (0x191 runs across stage frames 672..3542).
Launched slots now bind a real per-slot ANM VM from `bullet.anm` (raw bytes
mounted from the archive at pool init; script id = `dword_474170[type] + sub`
from the launch record's words, type 0 in this checkout), mirroring retail
sub_4067D0. The pool sweep's per-bullet hook (retail sub_406240) ticks that VM
every frame and, when `AnmVm_Tick` reports script end or the slot self-
destruct flag (bit 3 of +0x00) is set, retires the slot through the shared
`BulletPool_RetireSlot` leaf (retail sub_405BE0: clears +0x446 and rewinds
both clock pairs), which the sweep then drops from the relink lists. In this
checkout every launched slot's script is a looping bullet sprite, so none
reaches its end inside the stage_frame-3570 window and all 178 stay active at
the cut — the retirement edge is wired and regression-covered
(`bullet_pool_update_test` asserts the leaf layout and the sweep drop); the
remaining boundary is reaching scripts whose sprites terminate plus the
full collision/offscreen retire paths (tracked with the ANM slice).

The same trace stream now covers the real `stage01.std`/`stage01.ecl` bridge:
stage resource hashes, stage-entry phases, scheduler primary/ECL/secondary/timeline
ordering, root and child ECL VM lifecycle, async IDs, rank masks,
script-relative PCs, entity lifecycle, bullet-pool slot lifecycle and active
summaries, stage draw records, ECL spawn records, and stage termination.
`--trace PATH --smoke --ecl 3600` produces a deterministic 249,449-event
stream in this checkout, including 217,130 ECL ticks, 8,542 opcode records
(57 distinct opcodes, 0x190/0x191 family included), a real async child VM,
107 `stage_spawn` records across opcodes 0x101/0x105, 158 ECL VM
creates/destroys and 158 entity live transitions with balanced teardown; two
runs compare byte-identically and through the semantic comparison tool. Live
D3D traces also
carry `stage_draw` records at stage and player draw sites, alongside
pre-Present RGB checksums.

## Title ANM Manager Boundary

Title-tree handoff now retires every replaced VM and manager object through the
retail removal path; menu-smoke tracing currently reports 171 VM creates/171
destroys and 176 object creates/176 destroys.

The all-source PE32 runtime now mounts `title.anm`, `title_v.anm`, and
`sig.anm` through the retail-layout resource manager, publishes the live D3D9
device to the descriptor runtime, configures pooled `AnimationObject` records,
and synchronizes each live VM's transform, colour, flags, and sprite before the
manager bucket calls `AnimationObject_Render`. The manager script executor is
kept paused while the canonical host VM remains the script owner, preventing a
duplicate tick. Deterministic traces identify these records as manager-owned
draws; failed title bindings no longer install `HostDrawAnmVm` as a callback.

`build_pe32.sh` now delegates to the same 280-TU all-source image, so both PE32
runners use one descriptor/manager ownership model. If a visible title VM still
cannot resolve a descriptor or texture, the host records an error and terminates
instead of silently promoting the raw callback. The i386
`title_anm_manager_bridge_test` now covers descriptor binding and pooled-object
reuse; stage/front/player VMs now mount descriptor-owned resources and render
through the manager bucket path. The remaining live-gate limitation is D3D9
HAL/device availability, documented in `matching2/docs/anm_vertical_slice_bridge_blockers.md`.

## Validation

The current implementation passes `./test.sh`, `./build_all_pe32.sh`,
`./build_pe32.sh`, and two independent 3,600-frame traced stage runs; the
semantic comparer reports `TRACE_COMPARE_PASS events=249449`. The PE32 build
reports 280 production translation units, zero unresolved project edges, zero
placeholders, and zero new or worsened fidelity findings. The published
`run_pe32.sh --resource-smoke` also passes against real archive resources.

With a nonzero nested X11 display (`gamescope -W 1280 -H 720 -w 640 -h 480
-- sleep ...`), the canonical `run_all_pe32.sh --menu-smoke` and
`--boot-real 360` both pass with `device=yes`; `--stage-live 120` also passes
with 16,173 manager-owned `stage_draw` records and 179 Present checksums, and
two independent live traces compare semantically. The host's direct `:0` display
currently advertises `0x0`, so direct invocations fail before game-state
construction with Wine's Direct3D9 HAL error; this is an environment gate, not
a headless-runtime pass.
