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

## Validation

The current implementation passes `./test.sh`, `./build_all_pe32.sh`,
`./run_all_pe32.sh --menu-smoke`, and `./run_all_pe32.sh --boot-real 360`.
The PE32 build reports 280 production translation units, zero unresolved
project edges, zero placeholders, and zero new or worsened fidelity findings.
