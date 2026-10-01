# ECL child spawn at `0x004500D0`

Updated 2026-10-01: the complete 142-byte SpawnChild is now maintained exact C++ in `src/script/ecl_child_pair.cpp`. Native LTCG derives the private EDI parent convention from the genuine complete callee scope. The whole EXE remains exact. See [current recovery and verification](resource_cleanup_and_ecl_spawn_2026-10-01.md); the original standalone audit below is retained as history.

## Live Ghidra evidence

Audited `th10.exe` function `FUN_004500d0` with decompilation, instruction
listing, xrefs, and the callers/callee in the same open program. The function
occupies `0x004500D0..0x0045015D` inclusive (142 bytes). It saves EBX and ESI,
returns with `RET 8`, and its two stack slots are at entry `[ESP+4]` and
`[ESP+8]`. EDI is read as an implicit parent pointer and is left unchanged.
The final call's EAX result is also left unchanged through the return.

Ghidra reports two direct callers, both in `FUN_0044e1a0`:

| Call site | Register and stack setup |
| --- | --- |
| `0x0044E268` | `EDI = [ESI+0x1014]`; pushes `EBP`, then `-1`. At callee entry, arg1 is `-1`, arg2 is `EBP`. |
| `0x0044E2A2` | `EDI = [ESI+0x1014]`; pushes the resolved value from EAX. The preceding `0x0044FF00` helper returns with `RET 8`, leaving its earlier pushed `1` as arg2. Thus arg1 is the resolved value and arg2 is `1`. |

At both sites ESI is the parent VM and `[ESI+0x1014]` supplies EDI. EDI is
therefore a real hidden input, not an incidental register value.

## State changes and callee contract

`0x004500D0` allocates a `0x1024`-byte child VM. When non-null, it clears
`child+0x1008` and `child+0x100C`. It then allocates a `0xC`-byte intrusive
node and stores:

- `child+0x1010 = arg1`
- `child+0x1014 = EDI` (parent)
- `child+0x101C = byte [ [EDI+4] + 0x101C ]` (copied script mask)
- `child+0` and `child+4` are cleared

The node fields are `{child, next, previous}`. The list anchor is at
`EDI+0x1030`; its `+4` link points to the first node. The new node is inserted
at the head, updating the old first node's back link when present.

At `0x00450154` the routine calls `FUN_0044df70`, passing the newly allocated
VM in EAX and two stack values: `[EDI+4]` and the original arg2. The callee's
listing starts by consuming the VM from EAX and returns with `RET 8`; it is
another private-register routine. Its result remains in EAX when SpawnChild
returns, although the two dispatcher call sites do not consume that result.

There is no SEH path in this function's listing. The primary blocker is ABI:
ordinary MSVC x86 C++ can model SpawnChild's two stack slots and cleanup, but
cannot express its third input in EDI. It also cannot make the nested call with
the child pointer in EAX through an ordinary function prototype. Leaving this
body as a wrapper is therefore still necessary for exact behavior at the
current standalone boundary.

## Conversion status

Keep the exact wrapper in
`matching2/msvc/src/script/ecl_vm_spawn_child_004500d0.cpp`. Its existing
historical native-LTCG record says a semantic candidate was 147 bytes versus
the 142-byte retail body and that a synthetic caller did not select the EDI
convention. No build, probe, or test was run for this audit. The source note's
next useful boundary is the actual dispatcher `0x0044E1A0` together with the
child start routine `0x0044DF70`; a standalone SpawnChild translation cannot
remove the private-register dependency.
