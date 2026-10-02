# Line-laser bounce `0x0041CFD0`: native recovery

2026-10-02. Maintained promotion verified.

The complete 410-byte routine is readable, inline-assembly-free C++ in
`matching2/msvc/src/game/projectile_bounce.cpp`. The maintained native probe
reports zero differing bytes, with selected-body SHA-256
`9be793018926bde16b0e725a6ccab3da97d461af2c129e67ac0aa32a131dded7`.
Only this body receives new recovery credit.

The real line-laser vtable at `0x0046DA60` supplies the public thiscall
boundary: slot 15 at `0x0046DA9C` contains this entry. The constructor installs
the table at `0x0041C5B9`; the updater sets ECX to the receiver at
`0x0041D45D` and calls `[vtable+0x3C]` at `0x0041D45F`. There are no stack
arguments, and the routine returns with plain RET. These literal retail bytes
are pinned in the lab's `final_receipt.json`.

The source tests the next position before reflecting. Its inclusive outer
bounds permit a sound when merely touching a lower boundary; horizontal
reflection uses the strict lower bound and inclusive upper bound. Vertical
reflection is suppressed by `0x08000000`; crossing the upper y boundary also
requires flag `0x400`. Reflection copies the next position and width into the
actual parameters at `+0x424`, uses normalized `-angle-pi` horizontally or
`-angle` vertically, and spawns kind zero. Either reflection clears
`0x08000C00`. Compile-time checks preserve the `0x1DC` parameter size,
`0xD58` object size, and position, flag, and parameter offsets.

Native LTCG compiles the complete genuine Base initializer, SpawnIn, line and
beam constructors, and SoundQueue alongside Bounce. The local Base model has
one real object input. It does not use the inherited unused leading formal
slot. Base emits 100 bytes versus retail's 98; the 202-byte line and 219-byte
beam constructors each differ by one register byte at their Base call.
SpawnIn153 and SoundQueue123 are exact. Every dependency remains unselected
and receives zero new credit; its maintained owner is unchanged.

An integer 0/1 reflection flag and passing the angle expression directly to
the genuine normalizer produce the complete retail body without an extra
float stack word. No synthetic caller, dummy input, added volatile, assembly
bridge, byte mask, or instruction/address rewrite is used.

Evidence is retained in
`matching2/build/experiments/projectile_bounce_real_graph_20261002`:
`maintained_probe.json`, its native cluster report,
`single_parameter_final_measure.json`, `final_receipt.json`, and
`whole_verification.json`. The whole-image receipt covers the combined
410-byte Bounce and 397-byte InitializePlayer promotion. The rebuilt
487,936-byte EXE matches retail literally, SHA-256
`2f14760b6fbbf57549541583283badb9a19a4222b90f0a146d5aa17f01dc9040`.
