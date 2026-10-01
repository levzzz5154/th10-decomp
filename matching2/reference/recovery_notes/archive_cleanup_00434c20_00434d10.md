# Archive and entry cleanup

2026-09-30. Readable, assembly-free archive cleanup now includes exact native
MSVC LTCG implementations for Reset, Close, and the global shutdown callback.
The entry deleting destructor was also promoted after the 2026-10-02 native
verification documented below.

## Sources and interfaces

Saved Ghidra files under `decompiled/ghidra_augmented/functions` cover all
three complete bodies. The shared `reference/semantic_candidates/dat_archive_types.hpp`
defines the same sixteen-byte archive and entry layouts used by the tested
parser and reader, plus the typed constructor/destructor helper contracts.

| Address | Candidate source in `reference/semantic_candidates` | Retail bytes | Retail interface |
| --- | --- | ---: | --- |
| `0x00434C20` | `dat_archive_reset_00434c20.cpp` | 10 | ECX receiver; no stack arguments |
| `0x00434D10` | `dat_archive_close_00434d10.cpp` | 86 | ESI receiver; no stack arguments |
| `0x00434D70` | `dat_archive_entry_delete.cpp` | 93 | ESI receiver; flags on stack; `RET 4` |

Reset preserves its ECX entry contract. Close exposes the receiver as an
ordinary stdcall parameter; entry deletion exposes both receiver and flags
as stdcall parameters. These conventional interfaces support behavioral
testing, not direct substitution for the private retail entries.

## Archive cleanup

Close releases the filename through `0x00452422`, clears it, then snapshots
the current entries pointer. For an existing array, it reads the cookie at
`entries - 4` and calls the real vector destructor helper at `0x004525FF` with
entry size 16 and callback `0x00435250`. The helper visits entries in reverse
order, including the sentinel. The cookie count controls destruction;
`archive->entry_count` does not. The raw allocation, including the cookie,
is then released through the separate free entry at `0x004524A1`.

Next, Close snapshots the current file pointer, clears entries, calls the
file's virtual scalar deleting destructor with flag 1 if present, then clears
file and count. It does not clear filename again after array destruction.
Callback mutations verify these reload/store boundaries: changes made by
filename release can select another array; changes made by entry or array
release can select another file; changes made by file deletion to entries or
filename survive the final file/count clears. Ordinary allocator callbacks
do not perform these mutations, but they distinguish the observed sequence.

The old candidate manually walked names and referred to a missing type
header. It now uses the actual helper, retaining the helper's own exception
machinery rather than replacing it with a loop that lacks that behavior.

## Entry deleting destructor

Only the low flags byte is read. Bit 1 selects array mode: destroy the cookie
count in reverse order and return the cookie address. Bit 0 independently
selects deallocation through `0x004524A1`. Without bit 1, release and clear
only the first entry's name, optionally deallocate that entry, and return the
original entry address. Higher flags bits do not affect these operations.
Array mode returns the cookie address even when deallocation is disabled.

## Verification

```sh
python3 matching2/tests/dat_archive_cleanup_differential.py
```

Native Clang emits COFF code for the actual candidates. The test verifies the
retail `.text` hash and executes both versions under Unicorn. Only free calls
and the virtual file destructor are scripted; the retail vector helper and
entry-release callback execute in both runs, including normal SEH frame
registration and restoration.

All **256 Close, 256 Reset, and 560 entry-deletion cases** agree on ordered
helper/free/delete events, state visible during callbacks, complete array
storage, final archive fields, deletion return pointers, preserved registers,
stack cleanup and normal-path FS:[0] restoration. Cases include missing
resources, null names, mismatched archive/cookie counts, zero and selected
negative cookie counts, callback mutations, all 256 low flags bytes, and
nonzero ignored upper argument bytes. Mutating the cookie during name release
also confirms that the helper has already captured its count.

The [DAT integration test](dat_archive_integration.md) includes Close, Reset
and both openers among ten executing candidates. All 168 archive scenarios
and 19 allocation-failure scenarios pass 355 cleanup calls, including repeated
cleanup of already closed objects and a loaded array containing a null name.

Clang body sizes are 102/7/88 bytes for Close/Reset/entry deletion; retail is
86/10/93. Throwing destructors are not injected, and no exception behavior or
native MSVC byte match is claimed. The local tests require `clang++` and
Python's `unicorn`; they used `matching2/build/lzss-compressor-recovery/venv/bin/python`.

## Exact native-LTCG promotion

`msvc/layout/ltcg/dat_archive_close_shutdown.json` builds the real Reset and
global shutdown callers together with Close. This caller-inclusive context
lets MSVC 13.10.6030 generate the retail private ESI receiver convention from
ordinary C++ member calls. The selected bodies match all 109 retail bytes:

| Address | Body | Bytes | SHA-256 |
| --- | --- | ---: | --- |
| `0x00434C20` | `DatArchive::Reset` | 10 | `9b7525ae89285115cea7416e385513c326bcee313902b996646bb915359dad9f` |
| `0x00434D10` | `DatArchive::Close` | 86 | `da50b83421f2a16f917a656ad4f6154bb966f0f2511a8bf745ae1143d601375e` |
| `0x00465A60` | global archive shutdown callback | 13 | `ef9e3ee15ec8eead44d8d51e375942e2b30955349640a55fcb657cf413d60846` |

The production focused probe reported exact bytes for every body, zero byte
masks, no relocation rewrites, and no failures. Its normalized object retained
both internal calls to Close at their retail addresses. The callback pointer
for `HeapBuffer_Release` is bound as an absolute address so its `DIR32`
relocation also matches the retail operand exactly. The atexit-registration
caller now names the semantic callback and independently matches all 12 bytes,
including the callback-address relocation. The full build compiled all 1,945
maintained sources and produced the exact 487,936-byte executable with SHA-256
`2f14760b6fbbf57549541583283badb9a19a4222b90f0a146d5aa17f01dc9040`.
Focused reports are under `matching2/build/probe_dat_archive_close_shutdown`
and `matching2/build/probe_archive_shutdown_registration`.

The manifest now marks Reset, Close, and the shutdown callback as semantic C++
regions. Entry deletion at `0x00434D70` remains assembly and is the next
assembly body in this cleanup family.


## Native entry deletion promotion (2026-10-02)

`matching2/msvc/src/archive/dat_archive_entry_delete.cpp` now owns the complete
93-byte entry at 0x00434D70. The `archive_entry_delete` native LTCG cluster
selects its ESI receiver, one four-byte flags stack slot, BL snapshot, both
return paths and RET 4 exactly. The entry layout is asserted as sixteen bytes.
The retired inline-assembly source has been removed from the manifest and tree.

A one-byte `EntryDeletionFlags` value record preserves the argument's stack
allocation under MSVC's aggregate parameter rules; only its low byte is used,
and the stack slot is rounded to four bytes. This is ordinary C++ parameter
modelling, not an instruction or register adapter. A primitive byte argument
was instead passed privately in BL, producing an 82-byte body; volatile reads
and caller accumulation did not restore the required stack boundary. The
record form reproduces all 93 bytes directly from native compiler output.

The callback remains bound at 0x00435250, and the real vector destructor helper
at 0x004525FF performs reverse-order destruction and its exception handling.
Scalar mode retains name release/clear before optional object deallocation.
Array mode retains the cookie address as its return value, including when
flag bit zero disables deallocation. No helper code was replaced or copied
from the oracle; no byte masks, output rewriting or inline assembly are used.
The synthetic repeated caller is not selected as game code.

The focused probe reported EXACT. Native region SHA-256:
`6bfd35aca859347fde485897b0994d0c19232d657c86ca40a2b0d329af4fbeb5`.
Incremental `make` verified the entire 487,936-byte executable exactly, reusing
1,645 unchanged units and compiling three. Current game-source progress is
2,047 C++ regions / 125,842 bytes (88.23% of regions, 38.94% of bytes), with
273 assembly regions / 197,289 bytes remaining. The earlier entry-deletion
native blocker above is superseded by this verification.
