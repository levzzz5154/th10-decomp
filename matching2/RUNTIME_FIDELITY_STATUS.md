# Runtime fidelity status

The project has a runnable C++ integration target, not demonstrated full-game
parity. The generated inventory currently classifies 722 addresses as 710
semantic, 4 partial, 3 researched, and 5 unrecovered. These are source-evidence
categories, not gameplay completion percentages.

## Known boundaries

| Area | Evidence and remaining work |
| --- | --- |
| Extended ECL (`0x0040E770`) | Partial. Known unimplemented random-movement, sound-command, manager-cleanup, and state-mixer cases now terminate with an opcode diagnostic. Unclassified default cases still advance and need auditing against retail. |
| Ending script (`0x0040BD80`) | Partial. Wait countdowns, float timekeeping, and named-stream loading now have focused static regressions; retail text/ANM/timer globals and the complete stream owner remain outside the host API. |
| Player update (`0x004250B0`) | Partial. The typed movement/control slice has focused regressions, but separate retail cardinal/diagonal speeds, gated slow-age updates, and orbit/trail/sprite ownership remain unresolved. |
| Final input (`0x0044A5F0`) | Partial. The state tail and statically recovered keyboard/DirectInput masks have callback-backed regressions; retail global ownership, joystick dispatch, and per-player publication remain outside the host API. |
| Player update (`0x00425730`) | Researched. Collision/respawn, bullet-clear, death effects, and several manager hooks remain incomplete. |
| Attached effects (`0x00426F70`) | Researched. Formation-table/layout tests exist; persisted callback addresses do not establish host callback execution. |
| Music room (`0x00433EF0`) | Researched. Playback/menu models have tests; the host does not reproduce retail Shift-JIS glyph rendering and text layout. |
| Five legacy inventory addresses | No current implementation annotation establishes these entries. Historical overlay membership no longer promotes them to semantic. Consult `coverage.json` for the addresses; audit source provenance before changing their status. |
| Retail data | The all-source target embeds retail `.rdata`/`.data` and requires `th10.exe` during the build. It uses game archives at runtime. |

The source ledger is annotation-driven and may contain further overstatements.
Passing placeholder/fidelity scans means their configured checks passed, not that
all missing behavior has been detected.

## Runtime evidence

The existing retail probe and reconstruction trace tools compare bounded scenarios.
VM clock/PC/rank agreement does not establish enemy position, lifetime, collision,
audio, or pixel equivalence. Deterministic reconstruction-to-reconstruction traces
establish repeatability only. Earlier counts and captures are retained in
[historical runtime notes](docs/runtime_fidelity_history.md), not asserted as
measurements of the current checkout.

For each new claim record the source revision/worktree changes, command, inputs,
comparison fields, trace window, and remaining divergence. Run build, host tests,
headless smoke, and live graphics checks separately. A smoke run with zero title
sprite draws must not be described as rendering validation.

The static readiness generator deliberately does not certify fresh build or smoke
results. See [README.md](README.md) for the current scope and validation commands.

## Cleanup validation — 2026-09-05

Validated the cleanup working tree based on `554cfff`, including the pre-existing
`standalone/host_stage.cpp` enemy-dump instrumentation. This is a dated observation,
not a gate that the source report automatically carries forward:

- `./test.sh`: passed, including 17 unsupported-opcode termination cases and three
  progress-evidence regressions.
- `./build_all_pe32.sh`: passed; 281 production translation units and zero
  unresolved project edges. The build still imported 220 retail data symbols.
- `./run_all_pe32.sh --smoke --ecl 3600`: `SMOKE_PASS` and `STAGE_BRIDGE_PASS`;
  3,600 update/draw ticks, final stage frame 3,570, clean shutdown. Used the default
  retail assets, with no input script or retail trace comparison. The smoke reported
  zero title sprite draws; no visual parity claim follows from this run.

No fresh retail-vs-reconstruction trace comparison or live graphics validation
was performed in this cleanup.
