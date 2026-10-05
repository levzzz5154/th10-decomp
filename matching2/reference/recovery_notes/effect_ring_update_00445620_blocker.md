# Effect ring update at 0x00445620: complete source model, one allocation fact missing

2026-09-13 follow-up to
[`effect_particle_advance_00445620_reconnaissance.md`](effect_particle_advance_00445620_reconnaissance.md).
The full model now exists and compiles to **554 of 598 bytes**. What is fixed
and what is left:

## The layout (confirmed by matching instruction for instruction)

```c
struct Particle {            // 0x1C bytes, array base = state + 0
    float x, y, z;           // +0x00   world placement, accumulated each step
    float angle;             // +0x0C
    unsigned int color;      // +0x10
    float countdown_a;       // +0x14
    float countdown_b;       // +0x18
};
struct State {
    Particle particles[33];  // +0x000, record 0 carries the accumulated level
    char     gap[4];         // +0x39C
    float    radii_a[33];    // +0x3A0
    float    radii_b[32];    // +0x424
    float    rate;           // +0x4A4
};
```

The guard loops walk `particles[0..2]` with a `0x54` stride (three records per
step), which is exactly what a *nested* `for (triple) for (slot)` loop
compiles to: the inner three-iteration loop is unrolled and the outer
eleven-iteration loop is not. Writing the three additions unrolled instead
makes MSVC unroll the outer loop too and grows the region to 2240 bytes; the
nested form reproduces retail's loop bytes exactly.

The body is: `particles[0].xyz = base + position`; `angle = -PI`; the two
guarded eleven-triple sweeps over `countdown_a` and `countdown_b`;
then 31 iterations over `particles[1..31]`, each accumulating the rate into its
two countdowns, running the same eleven-triple sweep when a countdown is
negative, taking the entity colour with its alpha byte cleared, summing
`radii_a[i] += radii_b[i]`, calling `Vector2_SetPolar` (`0x004458B0`:
`x = cos(a)*r`, `y = sin(a)*r`) with the running angle and the radius, adding
the placement to x/y/z and stepping the angle by the pooled `0x470B6C`
(0.202683404f = 2*pi/31); finally `particles[32] = particles[1]` (the
seven-dword `rep movsd`), `return 0`.

## The 44-byte residual

Retail keeps `this` in **EDX** across the whole function, including across the
`Vector2_SetPolar` call, and spills the ring pointer (`var_10`) for the tail
copy, which is why its frame is `0x18` with four pushed registers. The candidate
keeps `this` in EBP (callee-saved) and the ring pointer in EDI, with a `0x10`
frame. The difference is not a source shape: `Vector2_SetPolar` is a leaf that
only touches EAX, ECX and the x87 stack, so EDX provably survives it — but that
body lives in the *asm* region at `0x004458B0`, outside the unit, so the
compiler must assume EDX is clobbered and promotes `this`. It cannot be brought
into scope: the function uses `fsincos`, which this toolkit does not emit from
any C++ spelling, and a second definition would collide with its region.

This is the same class as the animation-pool note: retail's build lets a caller
rely on a callee's preserved registers, the maintained build cannot express the
fact once the callee stays assembly. The model is preserved at
`matching2/build/recovery-lab/effect-ring/` and is worth re-running the moment
either `0x004458B0` becomes expressible or the batch machinery grows a way to
record a callee's preserved set.

## Resolved 2026-10-05

Recovered byte-exact; see `effect_ring_update_00445620_2026_10_05.md`.
