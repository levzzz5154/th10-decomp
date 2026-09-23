# ECL resource slot setter at `0x00412720`

## Recovery status

Keep the retail entry as naked assembly for now. The body is small and its
memory effects are recoverable, but its caller uses two live-in registers that
the selected x86 C++ calling conventions do not expose as named parameters.
Replacing the entry with an ordinary C++ function would change the call ABI.

## Ghidra evidence

Audited in the live `/th10.exe` program (`/home/levzzz/Games/TH10 - Mountain
of Faith/th10.exe`). Ghidra identifies `SetEclResourceSlot` at
`0x00412720`, with body `0x00412720..0x0041274F` inclusive (48 bytes). The
last instruction is `RET 4` at `0x0041274D`; the next instruction bytes begin
at `0x00412750`, outside this function body. The complete body is a leaf with
one call xref and no callees.

Ghidra's nominal signature is
`undefined __fastcall SetEclResourceSlot(int, int, undefined4)`: the first two
values are in `ECX` and `EDX`, and the third is at `[ESP+4]`. Its variable
report also marks `ESI` and `EDI` as unaffiliated live-ins. The entry has no
static outgoing data xrefs because its memory accesses are based on those
register values.

The sole caller is `FUN_0040E770`, at its call instruction `0x00410CC0`. The
retail sequence immediately before it is:

```asm
00410CAC  mov edi,[esp+1Ch]
00410CB0  mov ecx,[esp+10h]
00410CB4  push esi
00410CB5  mov esi,[ebx+14D8h]
00410CBB  add edi,20h
00410CBE  mov edx,eax
00410CC0  call 00412720
```

Thus the setter receives the state/table base in `ESI`, an auxiliary value in
`EDI`, the resource identifier in `ECX`, and the slot index in `EDX`. The
caller pushes its previous `ESI` value as the one stack word consumed by
`RET 4`. This exact call site is the only function xref to the setter.

## Recovered behavior

Let `slot` be the incoming `EDX`, `state` the incoming `ESI`, `resource` the
incoming `ECX`, `aux` the incoming `EDI`, and `stack_word` the dword at
`[ESP+4]` on entry. The instructions perform:

```cpp
uint32_t* record = (uint32_t*)(state + 0x2494 + slot * 0x10);
record[0] = (uint32_t)resource;
if (resource >= 0) {
    record[1] = stack_word;
    record[2] = aux;
    record[3] = aux;
    *(uint32_t*)(state + (slot + 0x24A) * 0x10) = aux;
}
```

The identifier is always replaced. A negative identifier leaves the other
three record words and the auxiliary table entry untouched. There are no
helper calls. The body leaves `EAX` holding the slot-record address, but the
only caller overwrites `EAX` immediately after return; Ghidra therefore does
not establish a meaningful return value.

## C++ blocker and symbols

`__fastcall` can name the `ECX` and `EDX` inputs and represent the consumed
stack word, but it cannot declare the incoming `ESI` and `EDI` values as
additional parameters. Ordinary C++ also cannot reliably read those incoming
registers while preserving them as the callee-saved registers required by the
ABI. A readable helper could express the stores only after assembly glue
marshalled all five values, which would still leave this entry dependent on
inline assembly. A C++-only route needs a larger caller/setter cluster change
that removes the custom register contract; no such route was verified here.

The current raw entry identifier is
`asm_Ecl_SetResourceSlot_00412720` (COFF name
`_asm_Ecl_SetResourceSlot_00412720`). Existing manifest aliases also include
`_asm_Ecl_SetResourceSlot_00412720@4` and
`@asm_Ecl_SetResourceSlot_00412720@4`. There is no new semantic C++ symbol or
alias to integrate while the entry remains assembly.
