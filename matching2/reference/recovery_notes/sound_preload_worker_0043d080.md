# Archived WAVE preload producer

2026-09-26. `semantic_candidates/sound_preload_worker.cpp` recovers the complete
107-byte worker at `0x0043D080` as ordinary C++. Together with the
[single-slot helper](archive_load_cache_slot_0043d640.md), it passes **167 retail
comparisons, including two matching invalid writes**. A separate integration
suite passes **31 scenarios, 687 cached-archive loads, 672 WAVE handoffs, five
direct slot-helper loads and 31 archive cleanup calls**. Production remains
assembly pending the native byte gates.

The [shutdown integration](sound_shutdown_0043d120_0043dab0.md) extends this
path through secondary-buffer release, pending-image frees, MIDI worker stop,
interface aggregation and device-owner cleanup in 28 additional scenarios.

## Evidence and publication

Evidence comes from saved Ghidra C/instructions for `0043D080`, the
[earlier live audit](sound_worker_setup_0043d080_ghidra_audit.md), maintained
retail bodies and verified executable. A fresh Ghidra MCP request was rejected:
`MCP tool call requires approval, but approval policy is never`.

The worker takes no inputs and returns with plain RET. It iterates over 37
filenames at `0x474B40`. Before each load, shutdown state `0x4977B4` equal to
exactly 2 returns immediately. Other nonzero states still permit loading.
Each name goes through `Archive_LoadFile(name, 0, 0)`, selecting the cached DAT
path with no output-size pointer. The result is published at `0x4977C0 + 4*i`,
the global manager's pending-WAVE slot at offset `0x5230`. Null is published
too. Existing pending pointers are overwritten without being freed.

A null result logs format `0x46FDD4` through the object at `0x474F70`, then
returns. The filename is reread after the loader callback; changed shutdown
does not suppress this diagnostic. A successful load is published even if
shutdown became 2 during it; the next iteration observes the state. All 37
successful loads lead to a separate wait: when state is zero, cache the Sleep
import at `0x4660AC` and call Sleep(1) until state is any nonzero value. Changing
the import during the wait does not redirect it. Volatile accesses retain the
observed pending/state reads and writes; they do not establish a portable
C++11 multithreaded memory model for the original x86 program.

## DAT-to-WAVE integration

The integration freshly compiles maintained `Archive_LoadFile` and links it to
the ten recovered [DAT lifecycle candidates](dat_archive_integration.md). The
producer, slot helper, WAVE consumer and maintained chunk walker also compile
from source. Retail comparison executes their original instruction bodies.
Encrypted fixtures use all 37 original resource names, mixed raw/compressed
payloads, varied PCM lengths and 16/18-byte fmt chunks. Archive opening, index
decoding, lookup, payload decryption/decompression, publication, WAVE parsing,
PCM copying and archive closing all execute.

The cached loader increments the byte at `0x49231E` after EnterCriticalSection
and decrements it after Leave; tests include wrapping depth 255. Name processing
retains its unusual rule: search for the last forward slash in the suffix after
the last backslash; when none exists, use the original path. Forward-slash
prefixes and changed casing succeed. Backslash-only prefixes, including a
forward slash before the last backslash, fail for the basename-only index.
The actual CRT searches and comparisons run.

After finding a nonzero size, the cached loader allocates output and ignores
the archive reader's return value. Three cases fail only the compressed
reader's stored-buffer allocation. The cached loader still returns its
untouched output allocation, the producer publishes it and continues loading,
and the WAVE consumer rejects the A5 fixture bytes as non-RIFF and frees the
output exactly once. This preserves an existing failure path.

Other cases cover missing/empty entries, cached output allocation failures,
initial shutdown, cancellation after selected loads, the final wait, and
DirectSound Create/Lock failures. Normal published images must equal the
independently generated payloads before consumption. Unlock must contain the
original PCM with both split-region guards intact; its result is ignored.
Consumed allocations are freed once. Five direct slot-helper loads cover
replacing existing COM buffers and publishing twice to one pending slot: that
overwrite deliberately records one displaced allocation without a free.

## Validation and boundaries

```sh
python3 matching2/tests/sound_preload_worker_differential.py
python3 matching2/tests/sound_archive_preload_integration.py
```

The local interpreter is `matching2/build/lzss-compressor-recovery/venv/bin/python`.
Native Clang emits 121 bytes for the producer and 44 for the slot helper,
compared with retail's 107 and 37. Unit tests compare events, full global/local
memory, table mutations, results, faults, stack cleanup and preserved registers.
Integration compares allocation history and guarded bytes, codec ring,
archive/file state, critical-section depth, manager bytes, PCM output and calls.

Only file I/O, allocation/free, critical-section imports, Sleep, logging and
DirectSound methods are scripted in integration. A test-only calling-convention
adapter connects the maintained loader's name-in-ECX/read-RET-8 call to the
candidate reader's three-argument stdcall interface; it supplies no archive
behavior. The producer/slot helper use the ordinary Archive_LoadFile interface
rather than retail's name-in-EAX convention. Chunk/log ABI differences remain
documented in the WAVE note.

This schedule publishes before consumption; it does not test arbitrary
concurrency. Windows scheduling/exception dispatch, live audio and native
MSVC frame/private-ABI/byte matching remain unverified. Production region and
whole-executable gates remain in place. Existing WAVE and integrated initializer
tests still pass after making the WAVE test compiler's code address configurable.
