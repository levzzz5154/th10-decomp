# Archive entry reader `0x00434DD0`

2026-09-26. `reference/semantic_candidates/dat_archive_read.cpp` now contains a
self-contained typed C++ model of the complete 281-byte reader. It compiles
with native Clang and passes 671 differential scenarios. The maintained
assembly region is unchanged; private entry and helper ABIs are not recovered
by this test.

## Evidence and layout

The saved Ghidra decompilation and disassembly at
`decompiled/ghidra_augmented/functions/00434DD0.{c,asm}` cover the body through
the final `RET 8` at `0x00434EE6`. The full retail interval includes the three
alignment bytes preceding the string loop at `0x00434E60`.

The entry takes requested name in ECX and archive/output as two stack
arguments. The candidate instead exposes all three as ordinary stdcall
arguments. The layouts now shared through `dat_archive_types.hpp` are:

| Structure | Layout |
| --- | --- |
| `DatArchiveEntry` | Name +0, stored offset +4, unpacked size +8, metadata +12; 16 bytes |
| `DatArchive` | Entries +0, count +4, filename +8, `FileInterface*` +12 |
| `DatCryptParameters` | Key +0, step +1, block size +4, byte limit +8; 12 bytes |

The file interface comes from the maintained `th10/platform/file.hpp`, using
its `Read` slot at +8 and `Seek` slot at +24. The eight cipher parameter rows
at `0x00474BD8` are read from the actual retail image during testing.

## Behavior

Missing file or missing lookup result returns null. The stored byte count is
`entry[1].offset - entry->offset`, so the final entry requires a sentinel
record. The stored count and unpacked size are captured before allocation and
file I/O. An output buffer is reused only when it is nonnull and the two sizes
are equal; otherwise a stored-size temporary is allocated.

The reader seeks to the entry offset and accepts **any nonzero Read result**.
It does not require the returned byte count to equal the request. `Seek`
success is its low byte, matching the declared `BYTE` result; `Read` tests all
32 bits. After a successful read, the cipher row is selected from the unsigned
byte sum of the **stored entry name**, modulo eight, not the name supplied to
the lookup. The cipher's returned pointer is ignored.

If stored and unpacked sizes differ, the decoder receives the temporary,
stored size, original output pointer, and cached unpacked size. Otherwise the
result is the decrypted input pointer.

Two ownership paths differ from assumptions in the older legacy model:

- At `0x00434E3E`-`0x00434E48`, failed seek/read releases the encrypted buffer
  even when it is the caller's supplied output buffer.
- At `0x00434ECB`-`0x00434EE1`, the raw-data path first chooses encrypted as its
  result, then frees it whenever it differs from the original output pointer.
  Thus an uncompressed read with output null frees its new allocation and
  returns that same address. The older model suppressed this free when the
  sizes matched. The new candidate preserves the actual branch and pointer
  comparison.

Both paths were checked in the saved Ghidra disassembly, directly disassembled
from the hash-checked retail image, and exercised in emulation. The test's
allocator records releases without unmapping memory, so observing a returned
freed address does not conceal a later dereference or claim it is valid to use.

## Differential validation

`matching2/tests/dat_archive_read_differential.py` executes original and
candidate entry points in separate x86 emulators. Lookup, allocation, file
operations, cipher and decompressor are scripted collaborators. Every call is
recorded with its normalized arguments; callbacks produce the same memory
effects in both runs. Their own algorithms are outside this test's scope.
The separate LZSS and DAT cipher differential tests cover those algorithms.

All **671 scenarios** agree on complete collaborator call order, output and
temporary contents, return pointer, frees, archive/entry mutations, preserved
registers and each entry's own stack cleanup. Cases include:

- Empty, raw and compressed records; supplied or allocated destination;
  absent file or entry; allocation failure.
- Seek low-byte success/failure with nonzero upper bits; zero, short, ordinary
  and high-bit Read results; decompressor failure.
- Empty and high-bit entry names and names selecting all eight cipher rows.
- Callbacks that change the entry offset after allocation, change the file
  object during Seek, or change the entry name and unpacked size during Read.
  These establish that the entry's current offset is read for Seek after allocation,
  the file pointer is reloaded for Read, the name is read after I/O, and the
  earlier unpacked-size value remains in use.
- An allocation whose returned address equals the supplied output address,
  checking that cleanup depends on pointer equality rather than an invented
  ownership flag.

Reproduce with native `clang++` and Python's `unicorn` package:

```sh
python3 matching2/tests/dat_archive_read_differential.py
```

The local test uses the interpreter at
`matching2/build/lzss-compressor-recovery/venv/bin/python`. A fresh Clang
compilation emits 281 bytes, coincidentally the same length as retail. The
instructions and call conventions differ; this is **not** an exact byte match.

## Remaining matching work

Native MSVC compilation remains unavailable because the sandbox denies Wine's
server socket bind. Ghidra MCP calls remain denied by the approval policy.
No access restriction was bypassed; analysis used the saved Ghidra artifacts
and verified local retail bytes.

Recover this caller with the real `DatArchive_FindEntry` and cipher sources
under native LTCG. The original call edges require archive in EAX/name in EBX
for FindEntry, key in AL plus five stack arguments/RET 20 for decryption, and
four stack arguments/RET 16 for decompression. The reader itself requires name
in ECX plus archive/output on the stack/RET 8. Preserve the observed cleanup
and short-read behavior while recovering those conventions. Promotion still
requires every byte and relocation target of the complete region, followed by
the whole-executable gate.
