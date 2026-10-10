# Main task mode switch 0x004218D0 - exact (2026-10-10)

`MainTaskStateWave18::UpdateMode` in `msvc/src/app/main_task_update_mode.cpp`,
666 bytes (572 of code, the rest switch tables), selected in the
`sound_fade_real_tasks` cluster. Parked on 2026-10-05 with the unlock-and-return
block at the wrong place; this note records what placed it.

## The exit block sits in the middle of the function

Retail has `current_mode = next_mode; LeaveCriticalSection; --depth; return 1`
directly after case 4's create call, and every later case jumps *backwards* to
it. Inner case 14 of case 4 and the tail of case 15 jump backwards to that
create call.

There is one exit block in the source, after the switch. Evidence: the
temporary register cursor (`RegAssign`, EAX -> ECX -> EDX per temporary, see
`compiler_traces/regalloc/trace_temporary_cursor.py`) gives retail's exit load
the fourth pick; a second copy would have taken the fifth and a different
register, and the two could not have merged.

The block is moved late, by `FgCodeMotion` (c2 0x107b016b): the function's
exit chain is lifted behind the first block that ends in an unconditional jump
to it, **but only when no block falls through into it**. Reverse post-order puts
the exit last, so the block laid out before it decides:

- last case in the source ends in `break` -> it falls into the exit, nothing
  moves, every case keeps `jmp exit` (the parked model, 694 bytes);
- last case in the source returns -> the exit is moved up behind case 4, whose
  create call is the first block jumping to it. The duplicated
  `create; jmp exit` tails of inner case 14 and of case 15 then merge into that
  copy (the common tail now includes the whole exit, well over 20 bytes).

So `case 3:` (release, `LeaveSlot(5)`, `return 4`) is the *last* case in the
source. Case 0, which continues into it when the shared state cannot be
created, is first and reaches it with `goto quit`; the same pass lifts the
case 3 block behind case 0, which is where retail has it.

## Other points

- Case 10 stores `ui_mode`/`next_mode` before loading the stage shown last:
  the game counters at 0x00474C40 are one struct whose address is taken
  (`GameState()` accessor), so the load cannot be hoisted above the stores.
- Tracing: `compiler_traces/flowgraph/trace_lateflow_cl.py` on the function
  compiled alone (`cl /O2` reproduces the cluster's block order); the tuple
  dump at `FgCodeMotion` against the one at `MscClean` shows the move.
- A second explicit exit copy inside the switch gives the right position too,
  but its head (`mov reg,[next]; mov [current],reg`) stays behind in every
  case, with a different register.
