# Entity batch copy ABI review at `0x004415C0`

## Disposition

The 57-byte region remains assembly in `regions.json`, owned by
`src/unidentified/FUN_004415c0_004415c0.cpp`. The readable source model at
`src/unidentified/unassigned_004415c0.cpp` is retained as a semantic reference
only; it is not the manifest-owned body, a build/cluster input, or an ABI
bridge. The region is not proposed for conversion in the current pass.

## Retail behavior

The Ghidra body is `0x004415C0..0x004415F8`. If the count is zero, it returns
without calling the helper. Otherwise, each iteration:

1. Calls `0x00404F30` with the item pointer advanced by one byte, the state
   record advanced by `0x3AC` bytes, the full 32-bit entry count, and the
   entry's stack argument.
2. Copies the 16-bit value at state offset `+0x384` to `+0x388`.

The item base's one-byte stride and the state array's larger stride are both
visible in the retail instructions; this note does not assign a stronger
semantic type to the item bytes.

## Entry ABI and call graph

Retail inputs are private-register based:

| Input | Location at entry |
|---|---|
| Count | `EAX` |
| One-byte-stride item base | `ECX` |
| State-record base | `EDX` |
| Forwarded helper argument | `[ESP+4]` |

The function saves the full `EAX` entry count into `EBX`, `ECX` into `EDI`,
`EDX` into `ESI`, and the stack argument into `EBP`. For each helper call, it
places the current item pointer in `EAX`, retains the current state pointer in
`ESI`, forwards the full count in `EBX`, and pushes the saved argument. It
advances `EDI` by one and `ESI` by `0x3AC` before the next iteration. The region
returns with `ret 4`; the helper return value is unused.

Ghidra reports **no direct callers** for `0x004415C0`. Its direct callee is
`0x00404F30`. That callee also uses private registers and remains assembly, so
an ordinary C++ declaration of `0x004415C0` or `0x00404F30` is not an ABI
bridge. A future conversion needs a caller-shaped compiler context or another
proven bridge; the current review leaves the retail body unchanged.
The Ghidra function is named `CopyUpdatedStateShortsForBatch`; its plate comment
records the full retail register tuple and the source model's ABI limitation.

No manifest, shared header, build, probe, or test was changed or run for this
review. The retained source model spells out the loop and the per-item copy in
ordinary C++, while explicitly marking both the entry signature and the
0x00404F30 stand-in as behavioral abstractions rather than callable ABI
declarations.
