# Archive and entry cleanup

2026-09-26. Readable, assembly-free candidates now pass 1,072 retail comparisons
for archive close, reset, and entry deletion. These regions remain assembly
in the exact-build manifest. Earlier wording claiming promotion referred to
an abandoned proposal; its referenced layout header is no longer present.

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

## Remaining work

Live Ghidra access and Wine's compiler tools are now available. Ghidra
confirms Reset's ECX receiver, while Close reads its archive exclusively
through an implicit ESI live-in; Reset, both openers, and shutdown callers
establish ESI before the Close call. The standalone ordinary Reset candidate
became a five-byte tail jump, not retail's ten-byte ESI-preserving call.
Reconstruct a real caller-inclusive native-LTCG context that makes the ESI
receiver visible to MSVC, then require exact region bytes, relocations, and
the whole-executable gate before promotion.
