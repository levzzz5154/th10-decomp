# Trigger-region classifier recovery note

The archived semantic model and the IDA/Ghidra evidence agree on the behavior
at `0x004267F0`: rotate the region's position by `-angle`, test the inner
horizontal/vertical band, reject suppressed or ineligible modes/cooldowns,
call `0x00426CF0` on activation, and return `0`, `1`, or `2` for rejection,
activation, or the outer transition band.  Retail fields used are the
position at `+0x3C0/+0x3C4/+0x3C8`, half extents at `+0x41C/+0x420/+0x424`,
mode at `+0x458`, and cooldown at `+0x4310`; global suppression is read from
`[0x0047770C]+0x9EB8`.

A focused native-LTCG candidate was probed and rejected.  Its semantic source
reproduced the retail 36-byte x87 scratch layout and all observed absolute
bindings, but the compiler emitted a 483-byte body rather than the required
471 bytes and scheduled the scratch copies differently beginning at
`0x0042680C` (`8B 54 24 10` versus the candidate's `FLD [ECX+3C8]`).  Because
the probe was not exact, production `src/game/trigger_region.cpp` and its
region/cluster manifest entries were restored to the legacy assembly form.

Checkpoint result: `0x004267F0`, size 471, is **NON-EXACT** and is not
integrated.  No trigger-region LTCG manifest, context source, or probe output
remains.  The next dependency is a compiler/layout mechanism that can preserve
the retail x87 temporary-stack aliasing and instruction schedule at
`0x0042680C` while retaining the observed call ABI; another ordinary semantic
LTCG spelling is not accepted without a focused EXACT probe.
