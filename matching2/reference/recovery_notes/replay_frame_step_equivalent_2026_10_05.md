# Replay frame-step C++ equivalence recovery, 2026-10-05

The 68-byte callback at `0x0042A3E0` is now covered by
`layout/equivalent/replay_frame_step_0042a3e0.json`. The default build uses
`equivalent/game/replay_frame_step_0042a3e0.cpp`; the exact build retains its
assembly owner. This is an equivalent recovery, not a byte-exact promotion.

The C++ follows the model and field evidence in `0042a3e0_wave16.md`. It
returns 6 only when a scene exists, its `+0x58` flag bit 4 is clear, callback
state `+0x10` is 1, global flag `0x100` is set, and signed frame `+0x1C8`
has nonzero remainder modulo 4. All other paths return 1. Offset assertions
cover every object field used by the function. Its ECX receiver is retained
by rooting the member itself as the compiler-only executable entry.

All 22 instructions match. The four previously blocking branch displacements
select different copies of the same one-byte RET: retail goes to `+0x3D`,
the compiler goes to `+0x43`. Both copies immediately return with the same
registers, flags, stack, and memory. The null path still executes its own
`mov eax,1; ret`, and the nonzero-remainder path still executes `mov eax,6;
ret`. No branch skips a required result assignment.

The existing equivalence checker proves these tails reach the same code
automatically. The layout therefore has **no listed differences**, no
base/index allowance, no frame shift, and no unproven branch-target exception.
There was no change to the checker and no copying of oracle instruction bytes
into the C++ output.

Validation: the named equivalence probe reports 22 of 22 instructions
identical and zero recorded differences. Both `make` and `make EXACT=1`
passed after integration with the MIDI tick recovery; the latter verified
all 487936 executable bytes.
