# Front HUD 0x00414900: semantic bugs found in the equivalent model (2026-10-14)

Re-reading the retail disassembly (0x414900..0x4157DD) against
`equivalent/game/front_hud_update_00414900.cpp` turned up model errors that
are not register allocation. Fix these first (see
`th10-parked-models-may-be-semantically-wrong`):

1. **Notice-slot loop (0x414F33).** For i in 0..9: if `i < count`, create the
   object only when the slot is empty and do nothing else. Otherwise, if the
   slot is live, call FlagStopFrame1 and clear it. The model flags every live
   slot, freshly created ones included.
2. **Boss-id loops.** Re-read `boss_id_count_9e90` on every iteration; retail
   does not cache it.
3. **Finished path (0x4151A5).** Re-read `front->sequence_9eb8` and null-check
   it before flagging slots +0x40..+0x54 and freeing it (an inlined delete).
   `sequence_9eb8 = 0` is stored either way.
4. **Position and difficulty sections are independent.**
   - The position block (pos >= 0, body, no sequence) is skipped as a whole.
   - Then `seq = data_00477704` is re-read and `body = seq->field_10` is
     checked again.
   - The difficulty gate and boss bank run whatever the position checks gave.
     The model nests them inside the position checks.
5. **Lane logic.**
   - `unsigned flags = front->flags_9eb4` is loaded once; lane = (flags>>1)&3.
     The stores use `(flags & ~4) | 2`, and so on, on that same value.
   - Lane 3 is an explicit `else if (lane == 3)` (retail has the compare).
6. The ConfigureObject digits re-read `script_pos_9ec0` for each call.
7. Frame-timer ramps emit `fld [speed]; fadd [elapsed]`, the same idiom the
   0x40BD80 recovery recorded.

The projectile Tick draft layout now links: duplicate context sources
removed, code_bytes 1456 (code + 2 padding bytes), listed_branch_targets.
Measured with the approved 1604 extent (eqm WIDEN), it is 65/337, because
of the receiver-EBX cascade.
