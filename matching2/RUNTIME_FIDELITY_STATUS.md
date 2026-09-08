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
establish repeatability only. Historical counts, captures and audit packets remain in Git history; they are
not measurements of the current checkout.

For each new claim record the source revision/worktree changes, command, inputs,
comparison fields, trace window, and remaining divergence. Run build, host tests,
headless smoke, and live graphics checks separately. A smoke run with zero title
sprite draws must not be described as rendering validation.

The static readiness generator deliberately does not certify fresh build or smoke
results. See [README.md](README.md) for the current scope and validation commands.
