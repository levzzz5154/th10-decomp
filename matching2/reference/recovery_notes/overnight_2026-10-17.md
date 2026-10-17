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
| 0x0043E8B0 `animation_change_script` | 22 | 14 | **improved** | `(flags \| 8) & ~0x200u` removes the shared 0x200 register candidate (script 44 vs flags 32): every register now matches retail; 64 of 66 instructions, the two recorded differences are the `and`/`xor` opcode and the update's position around the `fmul` |
| 0x0043C550 `camera_shake` | 27 | 27 | parked | the `fidiv`-versus-RNG pick order survives the conversion-local, temp-class and RNG-advance-placement levers (each adds the x87 operand-order hunk or shifts registers); needs the scheduler priority trace |
| 0x00415E90 `front_script_tick` | 25 | 25 | parked | named difficulty/stage locals at the clear count disturb the register allocation (9 and 36 hunks vs 3); the residual is the ChoosePhysReg -1 ESI preference the trace identified |
| 0x00422660 `result_rows` | 44 | 44 | parked | the pointer-store edge lever leaves the counter loads above the color store: their +32 load priority outranks a one-point store edge; needs the scheduler trace |
| 0x0044E1A0 `ecl_core_interpreter` | 116 | 116 | parked | the stack-slot pair traced (colour k = frame 0x1c+k*4; the top slots are inlined-helper params whose LTCG identities the plain-cl traces cannot pin); next: weight-probe one helper parameter at a time |
| 0x0044A190 `joystick_poll` | 157 | 157 | parked | named-local and goto-loop levers canonicalize; frame lever needs a struct whose colour lands below `info` |
| 0x0042CDF0 `title_dispatcher` | 167 | 167 | parked |
| 0x00417C80 `manager_teardown` | 179 | 179 | parked |
| 0x00406D90 `projectile_command_runtime` | 184 | 184 | parked |
| 0x004247F0 `player_reset_block_initialize` | 217 | 217 | parked |
| 0x004084A0 `projectile_point_count` | 281 | 281 | parked |
| 0x0044DF70 `ecl_start_child` | 285 | 285 | parked |
| 0x00437FE0 `font_atlas_draw_text` | 328 | 328 | parked |
| 0x00450220 `ecl_name_table` | 366 | 366 | parked |
| 0x0041EFA0 `laser_circle_split` | 407 | 407 | parked |
| 0x0040BD80 `recovery_script_executor` | 505 | 505 | parked |
| 0x00428F60 `replay_runtime_bootstrap` | 507 | 507 | parked | the two short store encodings shift the whole tail (3 instruction hunks but 507 bytes); pointer/flat-index spellings all keep them | case-order and goto-advance survivor levers inert (distinct-argument merge, not the duplicate-block shape) | the `count` EDX/EDI ChoosePhysReg tie (31 hunks) needs the Spillcosts K numbers; source sweep already exhausted | single-count copy block confirms the note's trade (40 hunks); head candidates need the measured Spillcosts K | one function-wide register substitution across the fifteen branches; needs the SpillCosts/ChoosePhysReg trace | temporary-compare form overshoots (26 hunks); zero-register compare + Riscify scratch rotation need the pre-Riscify dump | declared-then-assigned y leaves the x87 asymmetry (y memory, x on stack) untouched; shared with 0x00408210 | multiply operand order canonicalizes (memory-operand products); retail's per-statement reload is the CSE decision | the pointer-store edge on the timer-flags store overshoots (18 hunks); residual is the link-phase scheduling from addendum 14/15 | the branchless ternary rewritten as an if/else tail-merged call clears the instruction hunks but the region's differing bytes stay 179 (the byte gate, not the instruction verdict); reverted | x87 operand swap is register-register only; pointer-store edge leaves the schedule unchanged |

## Byte-exact share

100.0% of game code remains recovered (322,064 of 322,064 bytes, 2,322 of
2,322 regions). Byte-exact C++ rose from **74.6% to 76.7%** of the game code
bytes (2,289 regions); the equivalent recoveries are down from 37 to 33, and
the identical-instructions share rose to 97.8%. The
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
`ecl_core_interpreter` (116) upward. The register-allocator regions carry
their tracers:
`animation_change_script` needs the xor form worth three more priority points,
`camera_shake` the scheduler trace for the fidiv/RNG pick, `front_script_tick`
the ChoosePhysReg owner of the -1 ESI preference, `laser_rectangle_split` the
SpillObvious trace for the +0x2BA piece. The register-allocator regions have
working tracers in `matching2/reference/compiler_traces/regalloc/` and the
operand-sort/scheduler tracers; the notes name the exact open question for
each.
