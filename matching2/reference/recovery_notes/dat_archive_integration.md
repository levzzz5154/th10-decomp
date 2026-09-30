# DAT candidate integration

2026-09-26. Ten assembly-free candidates execute together against the retail
archive path: disk/resource opening, filename copying, index loading,
packed-index parsing, content reading, decryption, LZSS decompression, Close,
and Reset. The integration test passes **168 complete scenarios over 56
synthetic archives, 1,236 entry reads, 19 allocation-failure paths, and 355
cleanup calls**. This extends the individual collaborator-based tests without
promoting any region.

## Test scope

`matching2/tests/dat_archive_integration_differential.py` compiles the
actual candidate files with native Clang for x86 Windows COFF and relocates
each to a separate emulated address. Candidate-to-candidate calls execute
directly. The parser includes its compiler-generated C++ exception frame,
cleanup actions and metadata. A second execution uses the original retail bodies. Both start
from the verified retail `.text` and the same seeded dictionary and heap.

The fixtures contain a complete encrypted THA1 header, file payloads, and an
encrypted LZSS packed index. A separate Python encoder constructs their
ciphertext and token streams; expected names, metadata and payloads are also
checked independently of the differential comparison. The eight content
cipher parameter records come from `0x00474BD8` in the verified image.

File I/O is an in-memory implementation of the maintained FileInterface
slots. Heap allocation is deterministic and frees are recorded without
reusing or poisoning storage. The real vector-constructor/destructor helpers,
entry constructors and releases, lookup, CRT stricmp ASCII path, and memcpy
execute in both runs.
Both file constructors retain their retail vtable addresses; the test replaces
only the tables' virtual I/O slots with the in-memory collaborator. Each
fixture runs through direct LoadIndex, disk Open and resource Open, including
actual filename copying and disk Open's second virtual Open call.
A scripted CRT thread-data lookup supplies a C-locale record. The candidate
reader's lookup call uses an emulator adapter solely to supply the original
EAX/EBX arguments and restore the ordinary stdcall contract on return.

The comparison covers ordered allocation/free and file-operation events,
archive fields, all allocated bytes and surrounding guards, the complete
LZSS dictionary, file position, return pointers, preserved registers, stack
cleanup, and normal-path FS:[0] restoration. Loaded indexes are checked for
their array cookie, every name and metadata word, and the terminal sentinel.
Reads are checked against the fixture payload with both allocated and supplied
output buffers, including case-insensitive queries and missing names.

## Cases and observed behavior

- Every content-cipher bucket is exercised just below/at/above its block size
  and beyond its byte limit, alongside a file using overlapping LZSS matches.
- A match at the start of one file references bytes left by index decoding,
  confirming dictionary persistence across loader and reader calls.
- A large literal stream wraps the dictionary twice. Empty raw and compressed
  files, duplicate case-insensitive names, and seeded random multi-file
  indexes exercise the surrounding archive behavior.
- Duplicate names return the first match. The reader treats a zero-byte raw
  read as failure, while a compressed empty stream can succeed.
- An uncompressed read without supplied output still returns its already
  freed allocation, as previously measured. Retaining bytes after free lets
  the test inspect this result; it does not establish safe pointer ownership.
- The five injected direct-loader allocation failures target header cipher scratch,
  stored-index storage, decoded-index storage, entry-array storage, and the
  first name. Name allocation failure can leave a successfully loaded index
  containing a null name. The test does not then perform name lookup on it.
  Each opener also tests these stages plus file-object and owned-filename
  allocation failure, bringing the total to nineteen failure scenarios.
- Close or Reset releases each loaded archive; the other entry is then called
  on the empty object. Loader failures also undergo cleanup, including the
  successfully loaded array with a null name. These 355 calls compare all
  name, array and file releases as well as the cleared archive fields.

## Reproduction and limits

```sh
python3 matching2/tests/dat_archive_integration_differential.py
```

Requires native `clang++`, the project's MSVC headers for the cipher's memcpy
declaration, and Python's `unicorn`. The local run used
`matching2/build/lzss-compressor-recovery/venv/bin/python`. No precompiled
candidate objects are required. The shared COFF loader now accepts a code
address, retaining its previous default for the individual routine tests.

The test does not execute Windows file handles, TLS setup, a full game process,
non-C locales, or constructor exceptions. Its fixture streams are generated
for testing rather than extracted from a shipping archive. The parser's
allocation guard has separate registered-state/unwind-action tests, but
Windows exception dispatch remains unverified. Several candidates still expose
ordinary calling conventions for behavioral validation. Native MSVC region
matching and the whole-executable byte gate remain required for promotion.

Related notes:

- [Index loading](dat_archive_load_index_00434f70.md)
- [Packed-index parsing](dat_archive_parser_004350d0.md)
- [Content reading](dat_archive_read_00434dd0.md)
- [DAT cipher](dat_crypt_0044b0d0_0044b220.md)
- [LZSS decoding](lzss_decoder_00435dc0.md)
- [Archive and entry cleanup](archive_cleanup_00434c20_00434d10.md)
- [Opening and filename ownership](dat_archive_open_00434c30_00434ca0.md)
- [Public resource and multiple-archive integration](resource_archive_integration.md)
