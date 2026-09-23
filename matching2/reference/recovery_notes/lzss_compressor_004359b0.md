# LZSS compressor `0x004359B0`

Date: 2026-09-23

Status: semantic C++ implementation integrated in source, header, and manifest.
It preserves the observed three-argument `__stdcall` entry and uses typed
LZSS tree helpers. No build, probe, or test was run; byte-for-byte codegen and
symbol placement remain unverified.

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

The typed entry is `Lzss_Compress_004359B0` in the shared header. The manifest
records its decorated stdcall symbol and keeps the previous asm record for
history.

## Behavior and dependencies

The compressor allocates `input_size * 2` bytes. Allocation failure returns
null before writing `*output_size`; on success, the size is set to zero before
the global dictionary and tree are initialized. The ring dictionary has
`0x2000` bytes and uses an 18-byte lookahead. Its binary match tree consists of
12-byte records rooted at `0x00477858`, with the root at node `0x2000`.

The routine emits literal tokens for match lengths below three. Longer matches
write a zero flag, a 13-bit ring position, and a four-bit length-minus-three;
literals write a one flag and one byte. Bits are written most-significant
first. At end of input, a zero flag and zero 13-bit position form the
terminator. Only complete bytes are written, so any final partial byte is
implicit and excluded from the returned size.

For each consumed input position, the compressor removes the node that leaves
the 18-byte window, replenishes that ring slot when input remains, advances the
cursor, and inserts the next position to calculate the next match. The typed
helpers are `Lzss_InsertString_00436000` and `Lzss_RemoveNode_00436210`; the
latter now has a semantic fastcall manifest entry and an explicit ECX input.
The stale `MemoryFile_RemoveNode` label has been removed from the call edge.

The live body compares zero-extended bytes with `0xFFFFFFFF`; those comparisons
cannot match. The implementation does not assign sentinel behavior to `0xFF`.

## Verification limit

The compressor source now models the live sliding-window and bitstream logic,
and its public ABI is represented by a typed `__stdcall` function. The manifest
still describes the 1029-byte retail interval; the generated function length,
exact bytes, and final link placement are unverified because no build or probe
was run.
