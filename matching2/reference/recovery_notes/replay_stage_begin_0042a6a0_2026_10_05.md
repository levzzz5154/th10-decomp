# 0x0042A6A0 replay stage start (recovered 2026-10-05)

`src/game/replay_stage_begin_0042a6a0.cpp` compiles to the retail 356 bytes in
its own cluster; `make` and `make EXACT=1` pass.

The first standalone-rig model had the right size and instructions; only the
store order differed. Both residuals were aliasing facts, fixed in the context
rather than the source: the generator at 0x004918B0 and the configuration word
at 0x00491FC4 are parts of objects the program reaches through pointers, so
the synthetic caller lets their addresses escape (with the game state at
0x00474C40). The stores to the generator then order against the loads through
the stage pointer as in retail.

The record's `rep stos` with a null test is `new ReplayStage` with a zeroing
constructor; the `xor/and 1/xor` on +0x1C0 is a one-bit bit-field assignment;
the lazily initialised block at 0x00474C54 is `FrameTimer::Set`.
Rig: `build/experiments/replay_stage_42a6a0_claude`.
