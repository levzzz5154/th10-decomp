# Overnight recovery report, 2026-10-17

Queue order per the goal; four regions promoted to byte-exact, two parked with
notes, the rest unchanged. Every shipped change passed `make`, `make EXACT=1`
(SHA-256 `2f14760b6fbbf575…` unchanged throughout), `make abi-check`, the 127
unit tests, `git diff --check`, and a `replay_sync` replay (replay 1, 11,745
gameplay frames; the candidate traces are frame-for-frame identical to
retail's, the only run-to-run difference being the `g+0x64` startup counter
that retail disagrees with itself about).

| Region | Before | After | Status | Key lever |
| --- | ---: | ---: | --- | --- |
| 0x00438AD0 `game_main` | 0 (unpromoted) | 0 | **exact** | LTCG cluster with fourteen real callee bodies as anchors and shaped stand-ins for the three `/EHsc` callees (their stack-receiver conventions need bodies this cluster cannot compile; stand-ins that never read the receiver before a call keep it on the stack) |
| 0x00426F70 `familiar_refresh` | 6 | 0 | **exact** | one value-returning inline accessor at the scaled-row position (`&Rows(player)->carried[...]`) rotates the x-pair loads into retail's order; the tied y-pair stays |
| 0x0043AF30 `midi_tick` | 7 | 0 | **exact** | the track element pointer written as `MidiTrack* track = &table[index];` keeps retail's named-value order at the do-loop's decision |
| 0x0040DC80 `enemy_data_start` | 9 | 0 | **exact** | permuting the `BindName` helper's parameters (record, name) fixes both the result register (ESI) and the argument load order — the callee's parameter order sets the caller's order |
| 0x00433570 `replay_save_update` | 2 | 2 | parked | the inlined `strcpy` base/index order is the temp-id hash wrap at 1024; operand spellings and pointer locals move nothing, and only symbol-count padding (86 no-op inline calls) flips it, which is not source (`msvc-c2-operand-order-mechanism`) |
| 0x0042A3E0 `replay_frame_step` | 4 | 4 | parked | re-confirmed wave 16's negative result on the renamed model: the four `rel8` bytes pick between two identical `ret` copies and ~2,200 compiled variants found no source shape that changes the choice (`0042a3e0_wave16.md`) |
| 0x0041EB00 `laser_rectangle_split` | 14 | 14 | parked | the second-reference forms (`hit_count != 0 && hit_count >= 0`) give retail's EAX `test` but trade it for a tail shuffle (extra `jl` at +0x2B2, missing `lea` padding at +0x2BA) — the documented SpillObvious trade-off |

## Byte-exact share

100.0% of game code remains recovered (322,064 of 322,064 bytes, 2,322 of
2,322 regions). Byte-exact C++ rose from **74.6% to 76.7%** of the game code
bytes (2,289 regions); the equivalent recoveries are down from 37 to 33. The
`Recovered:` line after the last build:

```
Recovered: 100.0% of bytes (322,064 of 322,064), 100.0% of regions (2,322 of 2,322); byte-exact alone 76.7% of bytes, 97.7% counting identical instructions of equivalent regions
```

## What was learned (saved as memories)

- `/EHsc` emits an EH frame only where an unwind obligation exists; `throw()`
  on the stack-`new` constructors makes a function's /EHsc compile match the
  plain no-EH one byte for byte
  (`msvc-ehsc-throw-nothrow-same-codegen`).
- A stand-in whose receiver is first used after a call keeps the stack
  receiver (the flex-params entry scan never sees the load); tail-call
  destructors pass the receiver slot through (`msvc-c2-flex-params-entry-scan`
  addendum).
- Every compile of an /EHsc body emits its complete unwind group; the
  validators only accept it as exported region-owned functions or an
  ordinary (non-/GL) source's generated anchors, so a cluster can never see
  another cluster's EH body with private conventions
  (`th10-eh-functions-one-per-ltcg-cluster` addendum).

## Remaining queue

Re-measure before continuing (shared-context fixes move other regions):
`animation_change_script` (22, the documented 44/42 ESI/EDI priorities),
`camera_shake` (27, x87 RNG order), `front_script_tick` (25, index arithmetic
order), then `result_rows` (44) upward. The register-allocator regions have
working tracers in `matching2/reference/compiler_traces/regalloc/` and the
operand-sort/scheduler tracers; the notes name the exact open question for
each.
