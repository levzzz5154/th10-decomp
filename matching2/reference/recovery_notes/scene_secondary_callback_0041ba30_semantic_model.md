# `0x0041BA30` secondary scene callback: semantic model

The source pair
`matching2/msvc/src/unidentified/FUN_0041ba30_0041ba30.cpp` and
`matching2/msvc/src/unidentified/FUN_0041b8e0_0041b8e0.cpp` now models the
callback and its update routine as ordinary C++ `__thiscall` methods on the
same context. The manifest rows remain unchanged and still classify both
addresses as assembly. These source candidates have not been compiled or
probed.

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

The retail fallback's Ghidra entry disassembly confirms `mov edi,eax`; it then sets
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

In the retail binary, those helper calls have their own nonstandard register inputs: `0x0043e5a0`
receives the resource in `ECX`, the object in `EAX`, and the index in `EDX`;
`0x004451c0` receives the manager in `ECX` and object in `EAX`; and
`0x00463b2c` consumes an x87 value and returns an integer in `EAX`. After all
records, the fallback returns `1`. Its prologue saves `EBX`, `EBP`, `ESI`, and
`EDI`, which are restored on the return path.

Ghidra `get_xrefs_to(0x0041B8E0)` reports only the unconditional transfer at
`0x0041BA48`. Thus the EAX receiver convention is private to this callback in
the current database. `0x0041BA30` occupies a separate 29-byte manifest row;
`0x0041B8E0` is a separate 281-byte row.

## C++ recovery and ABI changes

The callback's method keeps its scheduler-facing context in the ordinary
`__thiscall` receiver and delegates to `UpdateSceneSecondaryRecords()`. The
fallback is now a same-class method that receives the same context in `ECX`.
This removes the private EAX/tail-jump edge by changing both C++ signatures
consistently; it preserves the callback's context and result semantics but does
not reproduce the internal retail control flow or byte layout.

The source inlines the observed `0x0043E5A0` configuration effects. Ghidra shows
the resource validity checks, record selection at `resource+0x118 + index*0x44`,
the object fields at `+0x308`, `+0x384`, and `+0x394`, dimensions at `+0x4c` and
`+0x50`, and the three 4x4 matrices at `+0x23c`, `+0x27c`, and `+0x2bc`. The
source initializes and scales those matrices in ordinary C++ rather than
calling the helper with its retail `(resource in ECX, object in EAX, index in
EDX)` convention.

Ghidra memory reads confirm the position offsets are `224.0f` and `16.0f`; the
branch limit is `8.0f`, transition range is `32.0f`, scale is `0.03125f`, and
byte maximum is `255.0f`. The inlined configuration helper uses scale
`0.00390625f` from `0x00470B7C`.

The source also models the observed `0x00463B2C` conversion without passing a
value through x87 `ST(0)`. Ghidra shows a signed 64-bit conversion truncated
toward zero with only the low byte consumed here. The C++ helper returns that
low byte for finite in-range values and maps the x87 invalid-conversion case to
zero. It computes with `double`; the retail x87 intermediates retain extended
precision, so byte-for-byte rounding at threshold boundaries is unverified.
The first x87 compare branches to the high path for greater/equal and unordered
values (`TEST AH,5; JP`); the C++ predicate is therefore written as not-less
than. The second compare sends less-than and unordered values through the byte
conversion (`TEST AH,1; JNZ`), represented by not-greater-or-equal.

For `0x004451C0`, the fallback calls the existing semantic C++ dispatcher with
its explicit `(manager, entity)` parameters. This C++ source edge is consistent
with the dispatcher declaration and avoids fabricating an EAX/ECX register
call. Retail itself passes manager in `ECX` and entity in `EAX`; Ghidra also
reports multiple other callers to this dispatcher. Its case-target register
adapters and those existing call edges remain outside this two-source recovery.
Reconcile them before promoting the dispatcher and fallback together. No
register adapter or inline assembly remains in these two source files.

No manifest or shared-header changes were made. Before promotion, integration
must change both manifest symbols to the new decorated member-method symbols
and reconcile the dispatcher ABI with its other call sites. The semantic
callback and loop behavior are represented; the x87 precision details and
build-level symbol/address integration remain unverified.

The sibling callback at `0x0041BA00` checks other bits in the same global scene
flag word. That supports the callback-family interpretation, but it does not
establish byte-exact source shape here.
