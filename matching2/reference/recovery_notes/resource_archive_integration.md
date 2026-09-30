# Resource-to-DAT integration

2026-09-26. Fourteen assembly-free candidates now execute together from public
resource registration, loading and size queries through the DAT lifecycle.
The new test passes **57 single-archive scenarios, one three-archive scenario,
73 registration attempts, 456 resource loads, 228 size queries, seven
allocation-failure paths and 130 cleanup calls**. No region was promoted.

## Executed path

`matching2/tests/resource_archive_integration.py` extends the existing DAT
integration harness. It freshly compiles the ten DAT lifecycle candidates and
four resource candidates with native Clang for x86 Windows. Resource calls
link directly to the recovered archive opener, reader and size lookup. The
retail archive selector, first-slash search, CRT C-locale comparison, vector
helpers and entry constructors/releases execute from the verified image.

The comparison run executes the original retail functions. Only allocation,
file I/O and CRT thread-data retrieval are scripted. Each virtual file object
has its own immutable fixture bytes and current position; reopening the same
filename does not replace the bytes belonging to another open object.

The tests use all 56 DAT fixtures from the original integration suite plus an
archive containing nested, repeated-slash and trailing-slash entry names.
These are complete encrypted headers, contents and indexes constructed by the
independent Python format encoder. Registration starts with zeroed global
archive records, performs actual index loading and filename copying, and
increments the real global count. Tests check the constructed index cookie,
names, offsets, sizes, metadata and sentinel before public resource queries.

## Assertions

- Public loads preserve first-slash routing and case-insensitive entry lookup,
  including missing entries, duplicate entry names, all eight cipher buckets,
  dictionary carry-over, ring wrap, and empty raw/compressed streams. Each load
  runs with both null and caller-supplied output buffers.
- Public size queries return the unpacked size of the first matching entry.
  They leave archive records, heap bytes, the dictionary, file positions and
  recorded collaborator calls unchanged.
- Three simultaneously registered archives use independent file objects.
  Two have the same registered name and different payloads; alternating loads
  resolve the duplicate name to the first record. Closing the middle record
  preserves both neighboring open files.
- Registration failures cover file-object, header-scratch, stored-index,
  decoded-index, entry-array, entry-name and filename allocations. A failed
  registration leaves the count unchanged, and a subsequent successful call
  reuses that slot. Name allocation failure can still register an index with
  a null name; that case is inspected and closed without lookup through NULL.
- Close and Reset clear each chosen record and release its owned storage.
  They do not decrement the resource registry's global count. Tests make no
  subsequent resource lookup through the resulting cleared registry entries.

Every call checks its entry convention, stack cleanup, preserved registers
and normal FS:[0] restoration. Comparisons cover the complete registry table,
allocation/free and file-operation order, all allocated bytes and guards,
file contexts, LZSS dictionary, results and caller output. Payload and size
assertions also use the independent fixture expectations.

## Reproduction and limits

```sh
python3 matching2/tests/resource_archive_integration.py
```

Requires native `clang++`, the project's MSVC headers and Python `unicorn`.
The local run used `matching2/build/lzss-compressor-recovery/venv/bin/python`.
The shared harness now accepts an archive-record address and multiple code
arenas; the resource compiler helper accepts a relocation base and explicit
collaborator bindings. Their original defaults are retained. The original
168-scenario DAT integration suite and all 518 resource comparisons pass
after these changes.

Loose-file fallback is outside this test; a [separate integration suite](resource_loose_file_integration.md)
now executes FileHandle Open/ReadWhole together with scripted Windows imports.
Files are synthetic and file I/O
is scripted. As in the DAT integration test, freed bytes remain inspectable
to characterize the retail raw-reader return of a freed pointer; that pointer
does not become valid ownership. C++ exception dispatch and native MSVC
region/whole-executable matching remain unverified.

Related notes: [DAT integration](dat_archive_integration.md),
[resource dispatch](resource_paths_004357d0_0043599d.md).
