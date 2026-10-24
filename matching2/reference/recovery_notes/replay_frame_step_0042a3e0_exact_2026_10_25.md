# Replay frame-step callback 0x0042A3E0: byte-exact (2026-10-25)

The 68-byte callback (`ReplayFrameStep::Check`, `src/game/replay/replay_frame_step.cpp`)
is now an ordinary translation unit. Its equivalent layout and the asm owner
`build_support/exact/game/replay/replay_manager_on_frame_step.cpp` are removed.

The last four bytes were the rel8 targets of the four failure branches: retail
sends them to the `ret` after `mov eax,6` (+0x3D), every barrier-free shape sends
them to the null path's trailing `ret` (+0x43). The 2026-10-03 addendum of
`replay_frame_step_0042a3e0.md` had already found the construction, and it is
what ships:

```cpp
int result;
if ((scene->flags & 4) != 0) result = 1;
else {
    result = 1;
    if (state == 1 && (g_input_keys_raw & 0x100) != 0 && frame % 4 != 0) result = 6;
}
_ReadWriteBarrier();
return result;
```

with the null path as the trailing `return 1;`. The barrier keeps the value join
alive until the exit jumps are final (see `0042a3e0_wave16.md` for the flow
rule), so the failure branches join `mov eax,6`'s `ret` and the null block owns
the last one. The nested `if` form of the three checks gives the same bytes; a
single `result = 1; if (all four) result = 6;` does not (61 bytes). The barrier
intrinsic is already used by ten shipped byte-exact sources (pause menu reset,
player collision, spell timer, ...); no inline assembly is involved.

Validation: `make` (equivalent regions 19 -> 18), `make EXACT=1` (SHA-256
`2f14760b6fbbf575…`), `callsite_abi.py`, 127 tool unit tests, `git diff --check`.
