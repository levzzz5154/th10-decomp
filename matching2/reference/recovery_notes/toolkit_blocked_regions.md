# Regions blocked by the toolkit, not by the source

2026-09-19. Two classes of residual are now settled to the toolkit, so a future
wave should read this before re-attempting any of them. Each entry names the note
holding the full evidence.

## 1. Register-register argument copy order

Blocked regions: `0x00401110` (330 B, 4 bytes), `0x00405620` (137 B, 4 bytes),
`0x0040D530` (300 B, 4 bytes).

Retail emits a call's register-register argument copies in **ascending**
parameter-home order - the first argument's copy first. This toolkit (cl 13.10.6030,
and the 13.10.3052 toolkit revision) emits them **descending**, and the first
emitted copy always targets the *second* parameter's home. Swapping the two homes
therefore only exchanges the two destination registers, so no assignment of homes
can produce retail's bytes.

Evidence in `argument_copy_order_residual_00401110_00405620_0040d530_wave10.md`:
56 toolkit setups across six translation units (provenance, arity, member and free
conventions, indirect and dllimport calls, callee body in the same TU, pragma
optimize settings, register-pressure ballast, tail and branch shapes); both c2
revisions; and an image census showing 40 direct-call register setups all copying
ECX first with only four EDX-first register pairs anywhere in `.text`, none of them
a direct-call setup. The tie-break is invariant to the destination order rather
than to the source order, which kills every source-shape explanation.

Consequence: `0x00401440` and `0x0040D6B0` are byte-exact inside links that contain
these regions but cannot land while their partners carry four wrong bytes. A
further 22 regions hold the same ECX-before-EDX `Scheduler_Remove` setup, and
`0x0043CD30` holds the immediate-operand form of the tie-break (under
investigation in wave 11).

If a candidate compiler ever appears, `/tmp/MoveOrder/homes.cpp` from that wave is
a one-minute acceptance test: retail's order means the first copy is
`mov %ecx,%esi`, and this toolkit answers `mov %edx,%esi`.

## 2. Mutually exclusive scheduler regions

Blocked region: `0x0040A040` (234 B, 14 bytes).

The residual is an 11-byte clear-block prologue order plus a 3-byte `pop edi`
position. The load/mask register pair comes out as retail's only when the pool
load, the mask materialisation, the `and` and the store share one scheduler region,
while retail's save position requires a region boundary between them. Those two
requirements cannot hold at once, which is why roughly 5,000 shapes - eight barrier
families, ten volatile forms, inlined helper families, two randomized searches -
land on 14 or 15 differing bytes and never lower.

Evidence in `0040a040_wave10.md` and `0040a040_wave9.md`. Its factory `0x0040A3C0`
is byte-exact in the same cluster and lands with it if the region is ever recovered.

## What this document does not cover

These are *toolkit* walls, distinct from the *register-convention* walls, which are
solvable by co-compiling the callee or declaring an anchor. Anything a future wave
finds blocked should say which of the two it is: if a compiled callee body or an
anchor changes the bytes, it was a convention wall; if not, it belongs here.
