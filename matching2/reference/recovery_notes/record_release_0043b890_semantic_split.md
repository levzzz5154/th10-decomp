# Record release at `0x0043B890`

## Live binary evidence

The open Ghidra program is `th10.exe` at image base `0x00400000`. Ghidra has no
function defined at `0x0043B890`, and its xref queries report no references to
or from that address. Reading and disassembling the retail bytes directly gives
this 33-byte sequence:

```text
0043B890  mov eax,[esi+4]
0043B893  test eax,eax
0043B895  jz   0043B89E
0043B897  push eax
0043B898  call dword ptr [00466288]
0043B89E  mov eax,[esi+8]
0043B8A1  push eax
0043B8A2  call dword ptr [00466274]
0043B8A8  mov dword ptr [esi+4],0
0043B8AF  ret
0043B8B0  ret
```

The body uses its record pointer in ESI. It releases the handle at offset `+4`
only when nonzero, always releases the pointer at offset `+8`, then clears the
handle slot. The final two bytes are consecutive `RET` instructions. The
second has no discovered inbound references and is not part of the state
release behavior.

## C++ representation and layout contract

`src/unidentified/unassigned_0043b890.cpp` now expresses the release method's
own return with ordinary C++. The following byte is represented by a separate
empty `__stdcall` C++ function in `.text$02adjacentret`; this preserves the
second retail `RET` as compiler-emitted code instead of `_emit` or other inline
assembly.

The native-LTCG context in `layout/ltcg/release_0043b890_context.cpp` still
supplies a caller that lets LTCG select ESI for the record receiver. The
cluster's ordered sections can retain `Release` at `0x0043B890`, the adjacent
return stub at `0x0043B8B0`, and the synthetic context at `0x0043B8C0`. The
existing zero-filled gap from `0x0043B8B1` through `0x0043B8BF` remains 15
bytes.

## Manifest and cluster integration

`regions.json` now records the 32-byte release body at `0x0043B890` and the
one-byte `Empty_0043b8b0` function separately. The LTCG layout selects the
stub in `.text$02adjacentret` at `0x0043B8B0`, roots its symbol so `/OPT:REF`
retains the otherwise-unreferenced COMDAT, and preserves the gap from
`0x0043B8B1` through `0x0043B8BF` plus the synthetic context at `0x0043B8C0`.
The stub's return is a layout carrier, not an additional record-release
action.

The source, manifest, and layout have not been compiled together, so address
placement and the ESI receiver lowering remain unverified. No build, probe, or
test was run.
