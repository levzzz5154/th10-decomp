# `0x00454C08` exception-handler region screen

The region currently stored in
[`unassigned_00454c08.cpp`](../../msvc/src/unidentified/unassigned_00454c08.cpp)
is not a single code body. Ghidra's data-region analysis identifies
`0x00454C08..0x00454C0F` as the eight-byte string `VC20XC00`. The function body
starts at `0x00454C10` and ends at the plain `RET` at `0x00454CF5`.

## ABI blocker

The source at `0x00454BBC` is `__SEH_prolog`; it pushes the address
`0x00454C10` as an exception-handler callback. Ghidra also reports an incoming
data xref from `0x00471070`. It does not currently define a function at
`0x00454C10`, so the callback ABI is not captured by a decompiler signature.

The body reads three stack values (`[EBP+8]`, `[EBP+0xC]`, and `[EBP+0x10]`),
then calls filter and termination funclets through addresses loaded from the
exception metadata. Before these indirect calls it sets `EBP` to the frame
record at `EBX+0x10` and clears `EBX`, `ECX`, `EDX`, `ESI`, and `EDI`. The
funclets therefore run under the compiler's exception-frame/register
convention; an ordinary C++ function pointer call cannot establish that EBP
frame while preserving its own normal stack frame. The `__SEH_prolog` entry
and this callback body need to be recovered as a coordinated ABI cluster before
removing the handler's inline assembly.

Keep `0x00454C08..0x00454C0F` classified as data and retain the naked handler
body at `0x00454C10..0x00454CF5` for now. No source or manifest change was made
for this candidate.
