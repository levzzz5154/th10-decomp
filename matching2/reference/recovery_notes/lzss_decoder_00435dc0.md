# LZSS decoder `0x00435DC0`

2026-09-26. `reference/semantic_candidates/lzss.cpp` now has a compiled,
retail-tested semantic implementation. The maintained 475-byte region in
`msvc/src/archive/lzss.cpp` remains assembly: no new MSVC byte match has been
established.

## Evidence and contract

The saved Ghidra decompilation/disassembly at
`decompiled/ghidra_augmented/functions/00435DC0.{c,asm}` covers the complete
`[0x00435DC0, 0x00435F9B)` body. The maintained assembly and hash-checked retail
image agree on its four stack parameters and final `RET 0x10`:

```cpp
unsigned char* __stdcall DecompressDatLzss_00435dc0(
    const unsigned char* source, int sourceLength,
    unsigned char* output, unsigned int outputCapacity);
```

The result is the original output pointer, not the final cursor. A null output
causes one `malloc(outputCapacity)` call; failure returns null before touching
input or the dictionary. A nonnull output bypasses allocation. Capacity does
not bound the decode loop; it is solely an allocation argument.

The shared ring at `0x0048F868` has 8192 bytes and starts each decode at index
one. Unlike the compressor, the decoder does **not** clear this dictionary.
Matches may refer to existing ring contents or to bytes written earlier during
the same overlapping match copy. Both source and destination indices wrap
with `0x1FFF`.

The stream consists of a one-bit flag followed by either an eight-bit literal
(flag one), or a thirteen-bit position and four-bit length-minus-three (flag
zero). Position zero terminates without reading a match length. Bits are
most-significant first. The candidate now expresses each bit group with a
descending mask, matching the loops visible in the original, rather than
shifting an accumulating value.

At every new input byte, retail loads `*cursor` **before** checking whether
`cursor - source < sourceLength`. At exhaustion it discards that load, supplies
zero bits, and leaves the input cursor in place. This means a logically empty
or truncated buffer can still fault if its cursor is inaccessible. The model
retains a volatile read at this one observed access; dictionary accesses are
ordinary typed C++. The former fixed-address dictionary cast and input-pointer
conversion through a 32-bit integer have been removed.

## Differential validation

`matching2/tests/lzss_decoder_differential.py` compiles the actual candidate
with native Clang targeting 32-bit Windows COFF. The candidate is then executed
under Unicorn beside the original retail entry. The test resolves symbols
using the project manifest and verifies the oracle's complete `.text` hash.
It compares:

- Every output byte and all 8192 dictionary bytes.
- The ordered input-read addresses and widths, including repeated reads at
  exhaustion.
- Invalid-memory access type, address and width for inputs ending at an
  unmapped page.
- Allocation arguments, failure behavior, result pointer, preserved registers
  and stdcall stack cleanup.

All **203 cases** pass. The set covers all match lengths (3 through 18),
positions 1/8190/8191, stale dictionary contents, overlapping match expansion,
all literal values, output spanning two dictionary wraps, allocated and supplied
buffers, small allocation-capacity arguments, 65 deterministic random byte
streams, every truncation of a mixed token stream, negative/zero source lengths,
five guard-page faults, five allocation failures, and three overlapping
source/output placements. Explicit token streams also have independently
constructed expected output.

Reproduce with Python's `unicorn` package and `clang++` installed:

```sh
python3 matching2/tests/lzss_decoder_differential.py
```

The run in this workspace used the interpreter in
`matching2/build/lzss-compressor-recovery/venv/bin/python`. The test defaults
to compiling a fresh object; `--object` permits an explicitly supplied COFF
object for additional compiler comparisons.

## Remaining matching work

Clang emits a 1233-byte body with the test flags. Its optimizer unrolls the bit
groups differently from retail; this measurement is behavioral evidence only.
The native Clang path was used because the session sandbox currently rejects
Wine's local server socket bind. Ghidra MCP calls also require approval that
the current policy forbids. Neither restriction was bypassed.

When MSVC is available, compile this revised source with the project's actual
flags and compare its complete extent and relocations. The current model has
the correct pointer cursor, 32-bit input-byte accumulator and eight-bit mask,
but register lifetimes and stack placement remain unmeasured under MSVC. The
saved retail epilogue consumes the remaining mask bits without additional
reads; that local-only state is not exported by the C++ interface. Do not add
artificial volatile state or instruction fragments to reproduce it. Promotion
still requires the complete 475-byte gate and whole-executable verification.
