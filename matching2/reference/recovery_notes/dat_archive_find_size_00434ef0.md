# DatArchive_FindSize at 0x00434EF0

The 2026-09-23 measurements below are historical results from the live Ghidra
`th10.exe` program and an MSVC 13.10 native LTCG probe. The source and region
manifest now contain a readable C++ candidate; its current ABI and bytes have
not been built or measured.

Ghidra decompiles a lookup over 16-byte archive records. The archive index
arrives in EAX and the requested name in EBX. It checks the entry pointer,
then scans `entry_count` records, compares names with `__stricmp`, and returns
the matching record's dword at offset 8 (uncompressed size), or zero. Ghidra
reports `Resource_GetFileSizeRetail` at `0x004358E0` as its caller. The caller
puts the archive in EAX and the name in EBX before the call.

The adjacent `DatArchive_FindEntry` at `0x00434F30` already compiles exactly
from C++ through `archive_find_entry_followup.json`. Reusing its record layout,
case-insensitive compare adapter, and synthetic array-walking LTCG caller
produced a 51-byte `FindSize` body, matching the retail extent and control-flow
shape. The closest result differed in 12 bytes. Retail begins
`56 57 8b 38 85 ff 74 20 8b 70 04`; the compiled body begins
`56 8b 30 85 f6 57 74 20 8b 78 04`. MSVC keeps the record pointer in ESI
and the count in EDI, while retail keeps the pointer in EDI and count in ESI.
The compare call and loop layout stayed aligned. At the time, no candidate was
promoted because the full byte comparison was not exact.

The current source candidate in `src/archive/dat_archive_find_size_00434ef0.cpp`
models the entry scan and returns the matched record's uncompressed size. It
uses ordinary C++ parameters for clarity, while retail callers pass the archive
index in EAX and the requested name in EBX. The source declaration therefore
does not establish the actual calling convention, and the candidate is not
claimed to match retail bytes.

Source forms measured under the same compiler setup included an early null
return, count-first `do` loop, `for` loop, indexed loop, local return value,
raw dword access, copied index, reordered decrement, const pointer, `goto`
on match, `break` on match, `register` locals, volatile count, and a separate
boolean for the compare. Most retained the 12-byte register swap; some changed
the function extent and did not reach byte comparison.

A future compiler investigation could compile the real `0x004358E0` caller
with this function in a schema-2 LTCG batch, retaining its SEH and archive
selection behavior. It may supply the context that made retail select EDI for
the record pointer. Another bounded option is to vary the synthetic caller's
use of the returned size while retaining the 51-byte callee extent. The
existing single-function probe alone does not establish that readable C++ is
impossible.
