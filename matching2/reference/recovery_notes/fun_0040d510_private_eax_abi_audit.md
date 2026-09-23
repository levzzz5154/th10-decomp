# 0x0040D510 private EAX input audit

## Live Ghidra boundary

The live program is `th10.exe` (`x86:LE:32:default`, image base
`0x00400000`). Ghidra identifies `FUN_0040d510` at `0x0040D510` with body
`0x0040D510..0x0040D52B`, 11 instructions and 28 bytes. The final instruction
is `RET` at `0x0040D52B`. The next function starts at `0x0040D530`; the four
bytes between them (`0x0040D52C..0x0040D52F`) are `INT3` padding. The prior
function returns at `0x0040D502`, followed by 13 bytes of `INT3` padding at
`0x0040D503..0x0040D50F`.

Ghidra's inferred signature is `undefined __stdcall FUN_0040d510(void)`.
Treat that signature as a default, not as the call contract: its decompilation
shows a phantom `in_EAX` input and no parameters. It classifies the routine as
a leaf, reports no callees, and lists one incoming reference, the direct call
at `0x0040A667`.

## Caller and register contract

The call site is in the checked-in naked region `FUN_0040a450` at
`0x0040A450..0x0040A932`. Ghidra does not assign that caller region a function
object, so the xref resolves to the call site but not to a named caller in its
callers list. Immediately before the call, the code loads the pointer stored
at `0x00477704` into `ESI`, copies it to `EAX` at `0x0040A665`, and calls
`0x0040D510` at `0x0040A667`. No argument is pushed for this call. The next
instruction pushes `ESI` for the following call; the result in `EAX` is not
used.

Thus the input is a private register argument in `EAX`. Standard MSVC x86
`__cdecl` and `__stdcall` parameters use the stack, while `__fastcall` and
`__thiscall` use `ECX` (and `EDX` for an additional fastcall argument). None
express this existing EAX handoff. The Ghidra `__stdcall(void)` prototype would
therefore omit a required input if copied into an ordinary C++ declaration.

## Behavior and conversion decision

The body reads the pointers at input offsets `+8` and `+0xC`. For each non-null
pointer, it ORs `2` into the 32-bit value at that pointed-to object's offset
`+4`. It preserves neither the input nor a stable value in `EAX`: when the
second pointer is non-null, it copies that pointer to `EAX` before the final
OR. The observed caller ignores `EAX`.

Although the memory updates are simple to express in ordinary C++, no standard
MSVC x86 function signature can receive the observed input in `EAX` without
changing the caller. Keep the existing naked assembly until a caller can be
changed as part of a coordinated ABI conversion. The source's previous match
record reports the naked body at 28/28 bytes and its tested readable cdecl
candidate at 1/28; no build, probe, or test was run for this audit.

## Link symbol

The manifest owns the 28-byte region at `0x0040D510` under
`_asm_FUN_0040d510_0040d510`. `asm_symbols.hpp` declares that symbol, and the
existing caller invokes it directly. No additional linker alias is needed
while the assembly region and caller remain unchanged. Any later semantic
symbol must preserve `_asm_FUN_0040d510_0040d510` as an alias or wrapper so the
current caller continues to link; the Ghidra name `FUN_0040d510` alone does not
replace that object-file symbol.
