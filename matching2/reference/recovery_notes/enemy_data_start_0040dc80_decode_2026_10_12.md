# The enemy tick 0x0040DC80 as an equivalent C++ recovery (2026-10-12)

Region: 0x0040DC80..0x0040E5EB, 2412 bytes, 671 instructions. The model is
`msvc/equivalent/game/enemy_data_start_0040dc80.cpp` with the view
`msvc/include/th10/game/enemy_data_start_0040dc80.hpp`, its link context
`msvc/equivalent/game/enemy_data_start_0040dc80_context.{hpp,cpp}`, and the
layout `msvc/layout/equivalent/enemy_data_start_0040dc80.json`.

Result: 2,412 of 2,412 bytes, 668 of 671 instructions identical. The three
recorded differences are one register choice: the spell-slot entry name
returned by 0x004127A0 at 0x0040E1C2 lives in EDI where retail holds it in
ESI (and reuses ESI for the record once the name has moved to ECX). Five
spellings of that block left the choice unchanged.

The name is historical: the function is the per-frame tick of an enemy, not
a "start". It returns 0 to keep the enemy, 1 when it died, -1 when it left
the field or its script ended.

## What the function does (in retail order)

1. 0x0040DC80: return 0 if `flags & 0x400` (already ticked this frame), else
   set it. `previous = final` (the 0x2C-byte motion record at +0x2C copied to
   +0x00).
2. 0x0040DCA9: four `Interpolator<TrajectoryVec2>` (0x00412AC0, receiver ESI,
   result through EDI), each run only while its `duration` is nonzero:
   +0x1D4 → relative angle (normalised, 0x0044BC70) and speed; +0x24C →
   relative radius and radius step; +0x210 and +0x288 the same for the
   absolute motion.
3. 0x0040DD69: for the relative motion (+0x58) and then the absolute one
   (+0x84): while its `Interpolator<Vec3>` path (+0x13C, +0x188; 0x00404610,
   receiver EAX, result through EDI) runs, `velocity = path.Step() -
   position`; otherwise the inlined `PolarMotion::Update`.
4. 0x0040DE87: `relative.Advance()` (0x0044C2A0, receiver ESI); with
   `flags & 0x40000` the scroll vector at 0x00491E6C is added to the absolute
   position; `absolute.Advance()`; `final.velocity = relative.position +
   absolute.position - final.position`; `final.Advance()`.
5. 0x0040DF13: with `flags & 0x200` the final position is clamped into
   `limit_center ± limit_size / 2` (+0x13AC.., +0x13B4..) and the relative
   position recomputed as `final - absolute`.
6. 0x0040DFDA: the visibility box (`visible_size / 2` around the position)
   against the field (-192..192, 0..448). Outside: return -1 if the enemy
   was seen (`flags & 0x100`) and may be removed (`!(flags & 4)`). Inside:
   set 0x100.
7. 0x0040E050: with `flags & 0x100000`, the animation script follows the
   stage flag at [0x004776EC]+0x28: set and not yet swapped → script +0x1448,
   flags |= 0x200001; clear and swapped → script +0x144C, flags &= ~0x200001.
   The flag is read through an inline accessor twice; that is what keeps
   retail's redundant `test eax,eax` at 0x0040E0B4.
8. 0x0040E0E9: `EclVm_TickChildren(record, *clock.speed)` (0x0044FD10, owner
   EDI); nonzero returns -1.
9. 0x0040E107: `flags &= ~0x2000`. Unless `flags & 0x11`: the player's shots
   (0x00428630, null receiver) give the damage, divided by 5 in shot modes 0
   and 2 and again for a boss (`flags & 0x8000`) while the game flag bit 0 is
   set, at least 1; health (+0x13C0) drops unless `flags & 8` or the
   invulnerable timer runs; a spell slot that came due (0x004127A0) restarts
   the script (0x0040C6E0, 0x0040C730, 0x00450700) and ticks it again; at
   `health <= 0` without `flags & 0x40` the bonus (+0x13BC) is scored and
   0x0040E5F0 may end the enemy (return 1); `flags |= 0x2000`. The marker at
   0x00474C50 is set whenever the enemy was open to shots.
10. 0x0040E275: the same spell-slot restart without the extra tick, the name
    lookup (0x00450470, table in EAX) expanded in place.
11. 0x0040E2BD: contact with the player (0x004266B0: position ECX, player
    EDX, size EAX) unless `flags & 0x12` or the contact timer runs.
12. 0x0040E2E4: with `flags & 0x1000`, the facing (-1/0/1 from the final
    x velocity against ±0.1) selects one of four turning scripts when it
    changes.
13. 0x0040E379: the eight animations are placed at the final position
    (0x00449350, or 0x004492F0 with `flags & 0x40000`; manager EDX, position
    ESI, handle on the stack).
14. 0x0040E3DB: unless `flags & 0x11` or `flags & 0xC0000`, the enemy is
    offered as the homing target ([0x00477834]+0x3504/+0x3508).
15. 0x0040E43E: the hit flash: while `flash_frames` (+0x1414) runs it is
    counted down and the flash bit cleared; otherwise a hit (`flags &
    0x2000`) starts four frames of it and queues sound 0x23 or 0x13
    (0x0043DD10: id EBX, queue ESI, pan on the stack).
16. 0x0040E53E: the invulnerable and contact timers step back by one
    (0x0044BF40, receiver ESI) and the enemy's clock ticks (expanded in
    place).

## How it was recovered, and what the earlier draft got wrong

The first draft of this model was grown toward the region's byte count
(2,144 of 2,412 bytes) and its note concluded that all content was present
and the rest was block placement. That was wrong: the draft tested the
0x400 latch backwards, replaced the three `Advance` calls by inline sums,
ran the clamp and the off-screen test on the wrong fields, misplaced the
death check, and called every helper with the standard conventions, so no
call site could match. Byte count is not a measure of progress; the
instruction diff is (`equivalence.py --layout <layout>` prints it for a
model that is not registered).

The present model was written block by block from the disassembly with the
project's own types (`PolarMotion`, `Interpolator<T>`, `FrameTimer`), and the
context file carries the recovered bodies of the fourteen helpers whose
private register conventions the call sites depend on. Its first measurement
was 559 of 671 instructions identical at exactly 2,412 bytes. The levers that
closed the rest:

- the orbit results copied field by field from a named local (retail reads
  the stack temporary, not the returned pointer);
- `Vec3`'s constructor-style operators for the final velocity, with the
  relative position as the left operand;
- the stage flag through an inline accessor called in both conditions;
- `flash_frames == 0` as the first branch, so the countdown block is placed
  last;
- the animation finder as a member that ignores its receiver, and the two
  position setters declared `(manager, position, id)`: the callee's
  parameter order sets the caller's load order;
- the sound queue from its real header, which gives the id in EBX;
- the player passed to the sweep straight from the global, no named local.
