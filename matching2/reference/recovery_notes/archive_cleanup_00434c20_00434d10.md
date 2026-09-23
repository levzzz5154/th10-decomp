# Archive cleanup pair at 0x00434C20 and 0x00434D10

## Semantic candidates

`DatArchive_Reset` forwards the archive object to `DatArchive_Close`. Close frees the filename buffer, walks the allocated entry array backwards using its MSVC array cookie count, releases the entries' owned name buffers, frees the array allocation, deletes the virtual file interface, and clears the archive fields. The entry and archive layout candidates are in `layout/ltcg/archive_cleanup_00434c20_00434d10_types.hpp`.

The promoted manifest entries use these proposed symbols and extents:

| Address | Candidate | Bytes | Proposed symbol |
| --- | --- | ---: | --- |
| `0x00434C20` | `DatArchive_Reset` | 10 | `?DatArchive_Reset@@YIXPAUDatArchiveCleanup_00434c20_00434d10@@@Z` |
| `0x00434D10` | `DatArchive_Close` | 86 | `?DatArchive_Close@@YAXPAUDatArchiveCleanup_00434c20_00434d10@@@Z` |

The prior `_asm_DatArchive_Reset_00434c20` and `_asm_DatArchive_Close_00434d10` aliases stay mapped to their retail addresses because other assembly sources call them by those names.

## Candidate layout

`layout/ltcg/archive_cleanup_00434c20_00434d10.json` compiles Reset and Close together. The context calls Reset in a loop and checks the cleared fields afterward. This is meant to let native LTCG select the private register convention where Reset receives the object in ECX and Close receives it in ESI. The synthetic context size is 64 bytes, a placeholder.

## Evidence status

The retail wrapper sequence and Close's ESI receiver are documented in `dat_archive_reset_00434c20.md`. A previous isolated C++ Reset candidate missed the required size, so the linked pair is a new candidate. No build or byte probe has been run for this pair. The proposed decorated names, receiver convention, context placement, and emitted bytes remain unverified.
