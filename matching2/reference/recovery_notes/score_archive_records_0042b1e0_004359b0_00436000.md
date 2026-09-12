# Score/archive record cluster: `0x0042B1E0`, `0x004359B0`, `0x00436000`

## Result

`0x00436000` was recovered as readable semantic C++ and independently proved
exact over its authoritative 516-byte live extent. The production source,
native-LTCG layout/context, and primary-integration proposal are retained.
`regions.json` was not edited.

The serializer and compressor failed exact comparison and retain their
original exact assembly. `0x0041A200`, which shares `score_save.cpp`, was not
modified and remains exact assembly.

| Region | Legacy extent | Live extent | Best semantic extent | First mismatch |
| --- | ---: | ---: | ---: | --- |
| `0x0042B1E0` score serializer | 592 | 564 | 537 | `0x0042B1E1`: candidate `06`, retail `03` |
| `0x004359B0` LZSS compressor | 1040 | 1029 | 622 | `0x004359B2`: candidate frame `1C`, retail `2C` |
| `0x00436000` match-tree insert | 528 | 516 | 516 | none; all bytes exact |

The focused production probe with the proposal reports exact for
`0x0041A200` (2247 bytes), retained `0x004359B0` (1029 bytes), and semantic
`0x00436000` (516 bytes). A fresh fixed-address native `/GL` image separately
placed `Lzss_InsertString_00436000` at `0x00436000` as one complete 516-byte
compiler contribution and matched every oracle byte.

## Reconciled behavior and ABI

`0x0042B1E0` receives the score archive owner in `EBX` and returns with a
plain `RET`. It allocates a 2 MiB work image, copies the six-dword header, and
walks seven fixed records of stride `0x437C`. Records tagged `CR` receive their
section index and a checksum over `0xB3E` six-byte units before a complete
record copy. It checksums and appends the trailing `0x448`-byte block, updates
the header lengths, compresses the payload through `0x004359B0`, encrypts it
through `0x0044B220`, and writes header plus packed payload to
`scoreth10.dat` through the shared-file ABI.

The 537-byte candidate modeled those record sizes and file operations, but
its owner remained in `ESI` (`mov eax,[esi]`) instead of retail `EBX`
(`mov eax,[ebx]`), allocated a 16-byte rather than 12-byte frame, and used
different copy/checksum scheduling. Recovering it requires caller slices at
`0x00417C80` and `0x0041FB50` that naturally preserve the owner in `EBX`, plus
the exact shared-file close/write failure path.

`0x004359B0` takes input, byte count, and output-size pointer on the stack,
allocates `2 * input_size`, and returns the packed buffer in `EAX` with
`RET 0x0C`. It clears the global dictionary at `0x0048F868` and interleaved
tree nodes at `0x00477858`, primes an 18-byte lookahead, emits literal or
13-bit-position/4-bit-length tokens through an MSB-first bit accumulator, and
updates the ring through insert `0x00436000` and delete `0x00436210`.

The legacy hook/state API was not the retail ABI. The bounded global-state
candidate recovered the allocation and bitstream roles but compiled to 622
bytes versus 1029, with a 28-byte frame instead of retail 44 bytes. Its next
dependency is exact semantic `0x00436210` and the original source-level bit
writer abstraction: retail repeatedly preserves the accumulator, mask,
output cursor, lookahead, and input cursor in named stack slots, whereas the
flattened candidate folds those states and loses 407 bytes of scheduling.

`0x00436000` receives the old cursor in `ECX` (unused at entry), the new ring
position in `EDX`, and the best-position output pointer on the stack, returning
with `RET 4`. It compares candidate strings six bytes at a time up to length
18. Longer/equal matches update the best position; a full match replaces the
old tree node while repairing parent and child links. Otherwise the signed
comparison selects the left or right child, inserting at the first empty
link. Exact code generation required best-length assignment before the output
store, an explicit nonnegative/right versus negative/left branch, and clearing
the new node's right child before its left child.

## Retained integration files

- `layout/ltcg/score_lzss_insert_00436000.json`
- `layout/ltcg/score_lzss_insert_00436000_context.cpp`
- `layout/ltcg/score_lzss_insert_00436000_proposal.json`

The failed combined candidate, context, and layout were deleted, as were all
temporary native and focused-probe outputs.
