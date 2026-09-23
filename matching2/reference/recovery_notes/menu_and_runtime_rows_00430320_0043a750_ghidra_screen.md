# Unreviewed rows `0x00430320`–`0x0043A750`: live Ghidra screen

Date: 2026-09-23. Read-only review of the active `th10.exe` program.

## Menu state callbacks: `0x00430320` and `0x004306A0`

Ghidra identifies both as `undefined4 __thiscall FUN(void *this, int param_1)`.
The bodies end at `0x00430680` and `0x00430A47`; the manifest rows also own
the jump tables at `0x00430684` and `0x00430A48` (888 and 956 bytes total).
Their sole direct calls from `FUN_0042CDF0` are at `0x0042D16A` and
`0x0042D172`. Each call pushes `EBX` and calls the handler without setting
`ECX`; backward dataflow reaches a four-way `ECX` merge at `0x0042CE2B`, and
Ghidra reports no callers for `FUN_0042CDF0` itself. This leaves the receiver
contract unproven.

The state-transition pseudocode is readable, but both bodies call register-
sensitive helpers such as `0x0042C670`, `0x0042C6D0`, and `0x0042C770`. Their
live Ghidra signatures are `__stdcall(int)`, `__fastcall(undefined4)`, and
`__fastcall(int)` respectively, while the handlers carry additional values
through `EAX`, `EDI`, and `ESI` around these calls. Without recovered semantic
helper interfaces and a known callback receiver, a standalone ordinary C++
rewrite would not preserve the observed call contract. Keep both exact naked
bodies for now.

## Text-render helper: `0x004372A0`

Ghidra has no function at this entry and reports no incoming xrefs. The
manifest owns 222 bytes ending with `RET 0x14`. The body copies the incoming
`ECX` into `EDI`, initializes a local string through the `0x00436890` helper,
then calls `0x00437380` with `ESI` moved into `EAX`. Ghidra's function at
`0x00437380` has a five-stack-argument `__stdcall` signature, but its
decompilation also exposes `in_EAX` and `unaff_EDI`; this call therefore has
two unmodelled register inputs. The existing audit for `0x00436890` establishes
that helper's ordinary one-pointer `__stdcall` contract, but does not resolve
these hidden inputs or the caller of `0x004372A0`. No standalone standard-ABI
conversion is justified.

## Object initializer: `0x0043A750`

Ghidra has no function at the entry and no incoming xrefs. The 436-byte body
uses `ESI` as its object pointer from the first stores through the final
`MOV EAX,ESI; RET`, and calls the API slot at `0x00466290` after placing an
output buffer at `ESI+8`. The field initialization is visible, but neither the
record type nor a caller that establishes `ESI` is known. Since ordinary x86
C++ cannot designate `ESI` as `this`, retain the exact body pending a recovered
caller/cluster contract.

No source or manifest rows were changed in this screen. No build, probe, or
test was run.
