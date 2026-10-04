# LZSS compressor `0x004359B0`

Date: 2026-09-23

Status (2026-09-26): the 1029-byte compressor remains assembly in
`matching2/msvc/src/archive/score_save.cpp`. Its readable, nonmatching model is
archived in `matching2/reference/semantic_candidates/score_save.cpp`.
The insertion helper at `0x00436000` is already byte-exact C++; deletion and
transplantation at `0x00436210` and `0x004362B0` now also match, as documented
in `lzss_delete_node_00436210.md`.

## Live boundary and ABI

Ghidra reports one function at `0x004359B0` with body ending at
`0x00435DB4`; the `RET 0x0C` at `0x00435DB2` makes the byte interval
`[0x004359B0, 0x00435DB5)` 1029 bytes. The manifest retains that retail extent.

The effective ABI is `unsigned char* __stdcall(const unsigned char*, int,
int*)`: three stack arguments, compressed-buffer return in `EAX`, and callee
cleanup. Both direct callers depend on the returned pointer and callee cleanup:

| Caller | Call instruction | Evidence after return |
| --- | --- | --- |
| `FUN_00429B60` | `0x00429E5D` | Reads the returned pointer from `EAX`; there is no `add esp, 0x0C`. |
| `FUN_0042B1E0` | `0x0042B315` | Immediately moves `EAX` to `EDI`; there is no caller cleanup. |

The archived candidate entry is `Lzss_Compress_004359B0`. The maintained
manifest still selects `_asm_FUN_004359b0_004359b0` for this interval.

## Behavior and dependencies

The compressor allocates `input_size * 2` bytes. Allocation failure returns
null before writing `*output_size`; on success, the size is set to zero before
the global dictionary and tree are initialized. The ring dictionary has
`0x2000` bytes and uses an 18-byte lookahead. Its binary match tree consists of
12-byte records rooted at `0x00477858`, with the root at node `0x2000`.

The retail routine emits literal tokens for match lengths below three. Longer matches
write a zero flag, a 13-bit ring position, and a four-bit length-minus-three;
literals write a one flag and one byte. Bits are written most-significant
first. At end of input, a zero flag and zero 13-bit position form the
terminator. Only complete bytes are written, so any final partial byte is
implicit and excluded from the returned size.

For each consumed input position, the compressor removes the node that leaves
the 18-byte window, replenishes that ring slot when input remains, advances the
cursor, and inserts the next position to calculate the next match. The recovered helpers are `Lzss_InsertString_00436000` and
`Lzss_RemoveNode_00436210`; the latter has a semantic fastcall manifest entry
and an explicit ECX input. The compressor's existing assembly call alias
continues to resolve to that same recovered entry address.

The live body compares zero-extended bytes with `0xFFFFFFFF`; those comparisons
cannot match. The candidate correctly does not assign sentinel behavior to `0xFF`.

## Semantic recovery and differential check (2026-09-26)

The candidate is now a self-contained C++ model with a byte-sized bit mask,
32-bit output accumulator, advancing output pointer, bounded input cursor,
and typed tree nodes. It clears all nodes from zero through the root, resets
both initial child links, and inlines the first deletion level. A node with
two children calls the recovered recursive deletion entry before transplanting
its predecessor. The input reader returns an `int`, preserving the observed
end-of-input check without treating byte `0xFF` as a sentinel.

The normal MSVC 13.10 flags compiled this model to 963 bytes. After resolving
all COFF relocations to the verified retail bindings, 185 byte positions agree
with the 1029-byte retail interval. This is **not** an exact match; the
production region still selects its original assembly.

`matching2/tests/lzss_compressor_differential.py` executes the compiled C++
candidate and the hash-checked retail image under Unicorn. Both executions
use the retail insertion and recursive deletion helpers; the candidate's
inline deletion is compiled C++. The test compares every emitted byte, the
reported length, the complete 8193-node tree (including the null sentinel),
and the entire ring dictionary. An independent format decoder checks round
trips. It also checks preserved registers, `RET 12` stack cleanup, allocation
size, unchanged input, and untouched output after the reported end.

All 160 streams passed: zero-filled, `0xFF`, ramp, random and small-alphabet
inputs at 22 boundary lengths from zero through 16421 bytes, plus 50 seeded
random inputs. This includes lookahead boundaries and two dictionary wraps.
Three simulated allocation failures also passed and left the size output and
dictionary/tree state untouched. The allocator shim provides a full mapped
output arena: this is a behavioral comparison, **not** proof that the original
`input_size * 2` allocation is sufficient for every length. Retail writes one
terminator byte even for an empty successful allocation.

Reproduce with Python's `unicorn` package installed, Wine and the normal
toolkit:

```sh
python3 matching2/tests/lzss_compressor_differential.py
```

The current sandbox began denying Wine's local socket bind after the
successful compiler probe. Its Ghidra MCP approval policy also changed to
deny calls. The test was therefore run with the object already compiled:

```sh
matching2/build/lzss-compressor-recovery/venv/bin/python \
  matching2/tests/lzss_compressor_differential.py \
  --object matching2/build/lzss-compressor-recovery/compress.obj
```

The tested source SHA-256 was
`230b99bd008416bf639d42baf6735f1a6b5d713b3493702e84a6acfcd0edd1c3`;
the COFF object SHA-256 was
`52be351fe0b800e27f30329a86d95bc8494ad15bb33e423bf7f4244d08c33370`.
The source did not change after compilation. Build-directory artifacts are
disposable; the default test command recompiles the checked-in candidate.

## Remaining byte recovery

The next compiler experiment should address the differences visible in the
two complete disassemblies saved under
`matching2/build/lzss-compressor-recovery/{candidate,retail}.asm`:

- The model uses a 0x30-byte frame; retail uses 0x2C. Local ordering and input
  pointer induction differ. Retail computes the input count before each
  consumed-token loop and increments it alongside the input pointer.
- Retail reloads the literal byte from the ring for each mask bit and reloads
  the match position in its bit loop. Passing values into `WriteBits` snapshots
  them before the loops. Explicit loops calling `WriteBit` are a source-level
  avenue to reproduce those loads without volatile accesses.
- MSVC merges the candidate's two single-child deletion paths. Retail retains
  both paths, with indexed child loads and a retained pointer for the final
  parent clear. Indexed accesses or the native-LTCG caller context may recover
  that schedule without duplicating machine instructions manually.
- The tree-clear loop's `<= 0x2000` comparison generates a different bound
  from retail's end-exclusive pointer comparison. Initialization behavior is
  now verified, but this control-flow spelling still needs a byte probe.

The stdcall return and real helper call targets are already correct. Do not
promote the model until all 1029 bytes and relocation targets pass the normal
probe and the complete executable gate.

## Resolved 2026-10-04: the whole codec from one natural source

`src/archive/lzss.cpp` now holds the compressor, the decompressor and the seven
tree helpers (0x004359B0..0x00436360) as plain C++, all byte-exact through the
`layout/ltcg/lzss.json` cluster. It replaces the per-helper sources, the
`compression_tree` and `lzss_tree_initialize_root` clusters and the hand-shaped
`Lzss_InsertString_00436000`.

What was actually wrong with every earlier attempt:

- The source is Mark Nelson's LZSS (`InitTree`, `AddString`, `DeleteString`,
  `ContractNode`, `ReplaceNode`, `FindNextNode`, bit output with `rack`/`mask`)
  nearly verbatim; no shaping is needed.
- The compressor cannot be matched by a stand-alone `/O2` compile, nor by an
  LTCG link in which its callees are opaque externs. With the callee *bodies*
  in the same LTCG scope the register assignment (mask in BL, rack in memory)
  and the one-level inline of `DeleteString` come out on their own.
- `DeleteString` is recursive, so LTCG keeps its declared convention; it has to
  be `__fastcall` (node in ECX). The non-recursive helpers get private
  conventions from their real callers.
- `InitTree` and `InitEncoder` have no out-of-line callers in retail (both are
  inlined into the compressor). `InitEncoder` and the decompressor can be
  `/INCLUDE` roots; rooting `InitTree` forces the stack convention, so the
  context calls it directly, which yields retail's EAX argument.
- Definition order in the source equals retail's address order.
