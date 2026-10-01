# Resource loading, size query, and overlay: native integration checkpoint

Readable C++ now owns the complete resource loader at `00435800` (214 bytes),
size query at `004358E0` (190 bytes), and overlay draw callback at `0043C500`
(74 bytes), plus their four native compiler-generated exception contributions
(36 bytes). All **seven complete contributions / 514 selected bytes** match
the oracle in retained ordinary native probes. The compiled input files
map byte-for-byte to their integrated main paths. No compiler ran during
the final retained-artifact audit, and no fresh whole build is claimed.

The size query selects an archive by path and strips through the first
slash before calling the genuine archive size lookup. Its disk branch uses
a 12-byte file object with the original vtable, invalid-handle initialization,
GetFileSize import, normal destruction, and exception destruction. Complete
unselected size lookup (51 bytes) and file destructor (46 bytes) match.
The generated cleanup at `00465380` and handler at `00465388` occupy one
18-byte native `.text$x` contribution. Their complete unwind map and FuncInfo
at `00471464` match all 36 metadata bytes.

The loader uses the same archive/path selection, with the optional output
buffer passed to the archive reader. Its disk branch opens the temporary
file, obtains its size, reads the file, and destroys the object through genuine
C++ lifetime semantics. A complete real BufferFile caller allows LTCG to
recover the path-in-ECX, output-on-stack, RET4 convention from the source
declaration. The unselected file destructor and BufferFile caller each match
all 46 bytes; their main owners are unchanged. Generated cleanup `004653A0`
and handler `004653A8` share a complete 18-byte `.text$x` contribution, with
all 36 unwind map and FuncInfo bytes exact at `00471488`.

The overlay callback builds its fixed rectangle and ARGB color and calls
the genuine quad drawing helper. Complete unselected drawing (483 bytes)
and flush (133 bytes) anchors match, preserving their existing owners.
Its receiver fields and ECX/EDI/EBX call behavior are verified by the
retained native body, rather than an expanded approximation of those helpers.

Each selected region retains its complete original record and original alias.
The two generated exception handlers were historically attributed to toolkit
library entries: those two full library records remain in `previous_record`.
Thus the 514 semantic bytes comprise **494 former assembly bytes and 20
former library bytes**. Neither full anchors nor exception metadata are
counted as newly recovered code. The obsolete loader assembly was removed
from the shared resource manager source while preserving the finder body;
the two sole-owner assembly cleanup files were removed.

Current manifest totals are C++ **1,868 regions / 100,461 bytes**, assembly
**432 / 222,457**, library **323 / 66,480**, embedded data **7 / 7,779**, and
padding **1,770 / 15,495**. The unchanged five C++ regions containing six x87
assembly blocks account for 4,451 bytes, leaving **1,863 regions / 96,010
bytes fully assembly-free**. The project partition, source ownership, native
cluster declarations, and compiler profiles validate.

The last whole build remains literally exact at **487,936 bytes**, SHA256
`2f14760b6fbbf57549541583283badb9a19a4222b90f0a146d5aa17f01dc9040`,
but its source snapshot predates these integrations. That build recorded
1,861 C++ regions / 99,947 bytes. The current report is deliberately treated
as historical: it has not been rewritten to certify current inputs. A fresh
MSVC rebuild is pending because Wine reports `wineserver: bind: Operation
not permitted` under the current sandbox. Fresh Ghidra calls also require
approval while the approval policy is never; successful pre-change Ghidra
analyses of the loader, size query, and generated handlers are retained.

The repeatable current integration audit is
`matching2/build/experiments/resource_load_and_overlay_2026_10_01/verify_checkpoint.py`.
Its passing output and native provenance are recorded in
[the evidence JSON](resource_load_size_and_overlay_2026-10-01.evidence.json).
Independent loader and overlay integration audits are retained in their
experiment directories. The audit never executes Wine or packages a new EXE.

The separate ArchiveCursor_Read candidate has a complete retained native
202-byte match but remains assembly in main. Its ordinary production probe
is pending a context-bound correction from 100 to the actual 90 bytes. The
frozen handoff is under
`matching2/build/experiments/subagent_archive_cursor_read_2026_10_01/frozen_production`.
It is excluded from this checkpoint's recovered-byte counts.

A separate ordinary-probe project is now prepared under
`matching2/build/experiments/archive_cursor_production_ready_2026_10_01`.
It preserves the frozen source, header, and driver bytes, changes only the
context size metadata to 90, and validates against the current full project
partition and cluster rules. `readiness.json` records those input hashes and
the exact resume command; `run_probe.sh` runs it when Wine is available.
No probe was executed and no main archive-read ownership was changed.
