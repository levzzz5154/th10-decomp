# THA1 index loader `0x00434F70`

2026-10-02 update: the maintained loader is now complete byte-exact, asm-free C++. The whole EXE gate passes. See [native recovery](dat_archive_load_index_native_00434f70_2026_10_02.md) for the genuine caller graph, alias proof, and verification receipts.

The remaining text records the historical 2026-09-26 candidate and its differential evidence.

2026-09-26. `reference/semantic_candidates/dat_archive_load_index.cpp` is a
typed, assembly-free model of the complete 350-byte loader. It shares archive
and entry layouts with the reader through `dat_archive_types.hpp`. Its 623
retail control-flow comparisons pass. The maintained region remains assembly;
private ABI recovery and MSVC byte matching are outstanding.

## Evidence and interface

Saved Ghidra files `decompiled/ghidra_augmented/functions/00434F70.{c,asm}`
cover `[0x00434F70, 0x004350CE)`. The receiver arrives in ESI, path is the only
stack argument, the boolean result is in AL, and cleanup is `RET 4`. The
candidate exposes both parameters through ordinary stdcall for testing.

Direct calls are at `0x00434C69` in DatArchive_Open and `0x00434CE0` in
DatArchive_OpenResource. The earlier note naming DatArchive_Read as a direct
caller was incorrect. The mode pointer at `0x00474908` points to `"r"` at
`0x0046F2C0` in the verified image.

The decrypted sixteen-byte header consists of four unsigned 32-bit words:

| Offset | Meaning | Decode |
| --- | --- | --- |
| +0 | Signature | Must equal `0x31414854` (`THA1`) |
| +4 | Unpacked entry-list bytes | Subtract 123456789 modulo 2^32 |
| +8 | Stored entry-list bytes | Subtract 987654321 modulo 2^32 |
| +12 | Entry count | Subtract 135792468 modulo 2^32 |

Header decryption uses key/step/block/limit `1B/37/10/10`; index decryption
uses `3E/9B/80/stored_size`. LZSS receives null output and the decoded unpacked
size. BuildIndex receives the unpacked buffer, archive's current count, and
the stored-list start offset.

## State and cleanup

The candidate corrects these assumptions in the legacy model:

- After the initial missing-file check, all failures delete the current file
  through the scalar deleting destructor (vtable +28, flag 1), then clear the
  file pointer.
- Both reads accept any nonzero result; neither requires the requested count.
- Entry count is published after signature validation, before GetSize, Seek,
  allocation or decompression. Later failure does not reset it.
- The seek offset is unsigned `file_size - stored_size`, with no wraparound
  check. The Seek return value is ignored.
- Compressed storage remains live until index parsing finishes. Cleanup frees
  compressed first and unpacked second, then deletes the file on failure.
- Old entries survive failures before parsing. The parser result is assigned
  directly, so parser failure replaces entries with null. No old index is
  destroyed here.

The source preserves observed reload points: stored size is read after
GetSize for the seek calculation, then again after Seek for allocation; the
unpacked size is read at decompression, and entry count at parsing. Decoded
sizes are stored back into the local header words, as in retail. These
behaviors are reproduced rather than repaired.

## Verification

`matching2/tests/dat_archive_load_index_differential.py` compiles the actual
candidate with native Clang targeting x86 Windows COFF and scalar integer
code generation. It verifies the oracle's complete `.text` hash, then runs
original and candidate independently under Unicorn. File, allocator, codecs
and parser are scripted collaborators.

All **623 cases** agree on normalized collaborator calls, header bias writes,
archive state, buffer effects, AL result, preserved registers and each
entry's own stack cleanup. Cases exercise every failure stage, nonzero short
reads, low-byte Open results with nonzero upper bits, zero/wrapped offsets,
zero/large sizes and counts, allocation failure, and callback mutations of
header sizes, file pointer and entry count. Free callbacks can change archive
state; success still returns true and failure deletes the current file.

The scripted header reader fills all sixteen bytes even for its nonzero-short
result cases, isolating the caller's branch condition. This does not test
uninitialized bytes after a real partial header read. Scripted codec calls
also do not constitute an end-to-end DAT decode; their algorithms have
separate differential tests.
The later [DAT integration test](dat_archive_integration.md) also executes the
recovered bodies together through complete synthetic archive loads and
reads; the collaborator-based tests here retain their broader failure cases.

```sh
python3 matching2/tests/dat_archive_load_index_differential.py
```

Requires native `clang++` and Python's `unicorn`. The local run used
`matching2/build/lzss-compressor-recovery/venv/bin/python`. Clang emits 301
bytes with these flags; retail has 350. All 671 archive-reader scenarios were
rerun after the shared-layout refactor and also pass.

## Remaining recovery

Wine's server socket bind and Ghidra MCP calls are still denied by the
session settings. Work used saved Ghidra evidence and verified retail bytes;
no restriction was bypassed. When MSVC is available, recover this body with
the real archive openers and cipher/index helpers under native LTCG. Preserve
the ESI receiver, path stack argument, AL result, decryption's AL key, and
the observed cleanup/short-read behavior. Promotion requires the complete
350-byte region, all relocation targets and the whole-executable byte gate.
