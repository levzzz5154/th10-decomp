# Effect ring construction 0x004452F0 (803 bytes) - recovered 2026-10-05

Source: `matching2/msvc/src/render/effect_ring.cpp`
Cluster: `matching2/msvc/layout/ltcg/effect_ring_build_004452f0.json`
Supersedes the ring section of `render_effect_cluster_00442050_00442f50_004452f0.md`.

## What decided each part

- **Entity in EDI, particle in ESI, radius pointer in EDX.** The particle
  pointer starts at record 0, record 0 is filled through it, and it is then
  incremented (`++particle`) before the loop. Starting it at `&particles[1]`
  gives entity in ESI and merges the block pointer with the radius pointer.
- **Three RNG calls, two inline draws.** The values before the loop call
  `Rng_NextFloatSigned` (0x0044BB90); the two inside the loop are the inline
  shared-generator form (32-bit seed read, last word in both halves). The
  context carries real bodies for the RNG leaf and the polar setter.
- **`mov eax,[drift]` ahead of `fmul 2^-31`.** The inline signed draw converts
  in its own statement: `float roll = (float)NextU32(); return roll * k - 1.0f;`.
  With the conversion inside the product expression the multiply is scheduled
  first. Same shape as the item scatter at 0x0040C9D0.
- **x87 operand order of the vector sums.** Hash-class tuning as in
  `effect_ring_update_00445620_2026_10_05.md`: the named locals `step` and
  `radius` in the loop put the loop sum and the record 0 sum in their classes.
- Callbacks at +0x398/+0x39C are bound as absolute `data` symbols so the
  stored addresses get the image base.

## Scheduler facts learned (c2 13.10.6030, P6 model)

`SchSelectInstrs` walks the ready list in priority order and takes at most one
instruction per functional unit per cycle (unit 0 integer, unit 2 x87); the
unit table is cleared at the start of every block. A candidate whose earliest
time is later than the current cycle is skipped. With equal graphs the emitted
order is fully determined by static priority, so a swap of an integer load and
an x87 operation means the dependency graph differs, not a tie-break.
Selection tracer used: scratch variant of `trace_scheduler.py` with breakpoints
at 0x107B055F (unit result), 0x107B0861 (AGI result), 0x107B08A9 (time check).
