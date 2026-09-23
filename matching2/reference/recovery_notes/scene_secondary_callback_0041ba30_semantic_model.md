# `0x0041BA30` secondary scene callback: semantic model

`matching2/msvc/src/unidentified/FUN_0041ba30_0041ba30.cpp` records a readable,
inline-assembly-free model of the 29-byte retail callback. The manifest still
classifies this address as assembly. The source candidate has not been compiled
or probed, and its ordinary C++ call to the fallback is not an ABI bridge.

## Live Ghidra behavior

The disassembly of `0x0041BA30` is:

```text
0041ba30  mov edx,[0x00477810]
0041ba36  test edx,edx
0041ba38  mov eax,ecx
0041ba3a  jz   0x0041ba48
0041ba3c  test byte ptr [edx+0x58],0x04
0041ba40  jz   0x0041ba48
0041ba42  mov eax,1
0041ba47  ret
0041ba48  jmp  0x0041b8e0
```

The scene flag condition is therefore exact: a non-null pointer at
`0x00477810` whose byte at `+0x58` has bit `0x04` set returns `1`. Otherwise,
the original callback context is passed in `EAX` to the fallback. The context
is not a stack argument. The callback entry itself receives the context in
`ECX`, consistent with the scheduler registration at `0x0041AD90`.

The fallback's Ghidra entry disassembly confirms `mov edi,eax`; it then sets
`EDI = context + 0x14`, `ESI = context + 0x34c`, and scans `0x896` (2,198)
records at a `0x3f0` stride. A record is skipped when its dword at
`ESI + 0xa4` is zero. For an active record it:

1. Writes the record-relative floats at `ESI - 4` and `ESI` after adding the
   globals at `0x00470b4c` and `0x00470b48`, then copies the float at `ESI+0x7c`
   to `ESI+4`.
2. Compares `*ESI` with `0x00470bd0`. One branch may write `24.0f`, calculate a
   value using `0x00470bcc`, `0x00470d20`, and `0x00470bf8`, call
   `0x00463b2c` with the value in x87 `ST(0)`, and store the returned low byte
   at `ESI-0x39`. The branches also compare the record's short at `ESI+0x4c`
   with the dword at `ESI+0xac` plus `0x158` or `0x161`; on mismatch they call
   `0x0043e5a0`.
3. Calls `0x004451c0` for the active record.

Those helper calls have their own nonstandard register inputs: `0x0043e5a0`
receives the resource in `ECX`, the object in `EAX`, and the index in `EDX`;
`0x004451c0` receives the manager in `ECX` and object in `EAX`; and
`0x00463b2c` consumes an x87 value and returns an integer in `EAX`. After all
records, the fallback returns `1`. Its prologue saves `EBX`, `EBP`, `ESI`, and
`EDI`, which are restored on the return path.

Ghidra `get_xrefs_to(0x0041B8E0)` reports only the unconditional transfer at
`0x0041BA48`. Thus the EAX receiver convention is private to this callback in
the current database. `0x0041BA30` occupies a separate 29-byte manifest row;
`0x0041B8E0` is a separate 281-byte row.

## Folding and ABI assessment

The fallback's *effects* can be expressed as ordinary C++ using the callback's
`this` pointer, but folding the whole body into this callback is not a viable
conversion while these addresses retain their current region ownership. The
callback is a 29-byte row and the fallback is a separate, noncontiguous
281-byte row (with `0x0041BA00` between them). Folding the body would require a
layout/manifest merge before promotion, and the helper calls would still need
typed semantic replacements or adapters for their register-specific inputs.
The current source therefore models only the callback check and leaves the
fallback call marked as a semantic-only declaration, not as a matching ABI.

Concrete semantic conversion path: keep the externally registered callback as
an `int __thiscall` method, convert `0x0041B8E0` to a typed C++ member method
that takes the same context as `this` in `ECX`, and have the callback call that
method normally. The sole incoming-reference evidence above supports changing
this private edge from EAX/tail-jump to ECX/ordinary call while preserving the
callback's scheduler-facing context and integer result. The fallback body must
also express its `0x0043E5A0`, `0x004451C0`, and `0x00463B2C` operations through
typed semantic implementations or explicit ABI adapters. This preserves the
observable callback behavior; it is not byte-exact and changes the private
entry ABI of `0x0041B8E0`.

If preserving the retail EAX/tail-jump boundary contract is required instead,
retain a small assembly entry shim at `0x0041BA30` to transfer `ECX` to `EAX` and jump,
then put a small EAX-to-typed-call adapter at `0x0041B8E0` in front of the C++
fallback core. A normal `__cdecl` call from the current source cannot substitute
for that edge: it puts the context on the stack and creates a new return
address. This ABI-edge option retains assembly at the boundary; the
semantic-only conversion path above removes that private convention by changing
both C++ signatures consistently.

The sibling callback at `0x0041BA00` checks other bits in the same global scene
flag word. That supports the callback-family interpretation, but it does not
establish byte-exact source shape here.
