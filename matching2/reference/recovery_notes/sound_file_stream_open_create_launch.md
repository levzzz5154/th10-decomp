# File-backed music cursor, stream factory and worker launch

2026-09-26. Three readable C++ candidates cover **1,116 retail bytes**, without
inline assembly. They remain outside the exact-build manifest.

| Retail routine | Bytes | Candidate |
| --- | ---: | --- |
| `0x0044DBF0`, open a music cursor | 173 | `music_cursor_open.cpp` |
| `0x0044C8F0` and continuation `0x0044CAD0`, create file stream | 702 | `sound_stream_create_file.cpp` |
| `0x0043D690`, replace worker and launch file stream | 241 | `sound_stream_launch.cpp` |

The opener passes **133 comparisons, including four faults**. The factory
passes **103 unit comparisons, including eight faults**, and **47 integrated
comparisons, including seven faults**. A further **81 registered-state and
table-selected unwind-action comparisons** pass. Launch passes **203 unit
comparisons, including 41 faults**, and **53 integrated comparisons, including
seven faults**. These total **620 comparisons**. Independent checks also cover
failed-open ownership, launch arguments, successful publication and retained
handles after failure.

## Evidence and shared types

Evidence is the saved Ghidra C/full-instruction exports for these addresses,
the maintained assembly, and the retail image checked against the manifest's
SHA-256. The new Ghidra MCP decompile request for `0044DBF0` was rejected:
`MCP tool call requires approval, but approval policy is never`. No permission
workaround was attempted. The saved exports remain available locally.

`MusicReadCursor` now names `open_mode` at `+0x78`; the object remains `0x94`
bytes and all existing fields retain their offsets. The factory shares the
scoped `PendingSoundStream` guard with the memory-backed factory through
`pending_sound_stream.hpp`. Following that extraction and the fixture
generalization, all 121 memory-factory comparisons and 65 unwind comparisons
still pass. These regression checks are separate from the 620 above.

## Opening the cursor

Retail receives cursor in ESI, mode in EAX, filename in ECX and record in EDX,
then returns with plain RET. The candidate uses explicit stdcall/RET 16.
It stores the full mode, clears buffered mode, and returns zero when mode is
anything other than exactly one. Those paths do not inspect the filename.
Mode one with a null filename returns `0x80070057` while retaining the old file
and record fields.

CreateFile receives access `0x80000000`, sharing 1, creation disposition 3,
flags `0x08000080`, and null security/template arguments. Its result is stored
in the cursor; only `0xffffffff` is rejected, returning `0x80004005`. A null
handle is accepted. The function rereads buffered mode after CreateFile and
then stores the original record argument, overwriting a callback replacement.

If buffered mode became nonzero, position is reset to the current buffer base
and a strictly positive signed loop end replaces the relative memory extent.
Otherwise a nonnull file is positioned at `record.file_offset + global
0x4977a4`, with 32-bit wrap. Seek failure is ignored. The record is reloaded
after Seek to obtain remaining bytes. A null file skips that update. Finally,
total PCM bytes is copied from file-remaining even on the buffered branch.

The test covers mode values with identical low bytes, null pointers, invalid
and null handles, offset wrapping, callback edits, and open followed by actual
cursor reads. Clang produces 200 bytes versus 173 retail bytes.

## File stream creation and ownership

Retail takes output in ECX, flags in EDX and ten stack arguments: owner,
filename, four algorithm words, segment count, segment length, event and
record. RET 40 removes those arguments. The candidate exposes twelve stdcall
arguments/RET 48. Both retail body ranges are included; padding between them
is not counted as recovered code.

A null device inside the owner cell returns `0x800401f0`, leaving output
untouched. A null owner faults. The factory allocates a `0x94` cursor and, when
nonnull, initializes only its record, methods, total PCM and buffered fields.
It invokes the opener with mode one even when allocation returned null.

**Every nonzero opener result is failure**, including a positive value. A
nonnull cursor whose current open mode is one has its current file passed to
CloseHandle; afterwards the file field becomes `0xffffffff`. The raw cursor
is then freed and generic `0x80004005` returned. This closes an invalid handle
after CreateFile failure. A null filename leaves the allocation's old file
word intact, so the cleanup closes that untouched word. The deterministic
allocator test independently checks closing `0xa5a5a5a5`, freeing the cursor,
and preserving the caller's output. CloseHandle results are ignored.

On success the 36-byte description has flags ORed with `0x18188`, byte count
`segment_count * segment_bytes` with wrap, format pointing at the cursor's
current record plus `0x20`, and the four supplied algorithm words. Negative
CreateSoundBuffer or QueryInterface results return `0x80004005` without rolling
back the cursor/file or any produced interfaces.

Notification storage is `segment_count * 8`; null returns `0x8007000e` without
releasing earlier resources. Each entry stores offset **before** event, unlike
the memory factory. Offsets begin at `segment_bytes - 1` and advance with wrap.
SetNotificationPositions receives the supplied count. Its nonnegative results
count as success. Afterwards the current escaped notification output is
released if nonnull, cleared, and the table freed. A negative Set result then
returns `0x80004005`.

The remaining creation/publication path agrees with the memory factory: a
`0x78` raw stream allocation, the actual single-buffer constructor when
nonnull, publication of its returned pointer, a forward nine-word copy of the
possibly callback-edited description, then owner/event/servicing writes through
the reloaded published pointer. Constructor refill/position errors are ignored.
Null allocation publishes zero before faulting at `0x34`.

## Registered cleanup

Retail handler `0x46533b` loads FuncInfo `0x471398`. Its one active state uses
action `0x465330` to free the raw stream allocation at frame offset `-0x48`,
including null. Earlier failures have no registered cleanup. Constructor-time
failure frees only that outer allocation; cursor, buffer and constructor's
internal pointer array are not released by the action.

The suite suspends at open/CreateFile/Seek/Close and each allocation, COM or
constructor boundary, reads the actual FS frame, handler, FuncInfo and unwind
map, and executes the selected action. It also inspects a real null-publication
fault. Frame removal is modeled by the fixture; Windows dispatch is not run.
The raw allocation guard remains armed through publication and metadata stores.

As with the memory factory, the behavioral profile needs Clang
`-fasync-exceptions` to preserve state zero at post-constructor memory faults.
A separately compiled synchronous profile reproduces state `-1` where retail
has state zero. That diagnostic is not counted as a matching comparison.
The asynchronous file-factory module is 1,020 bytes including EH metadata.

## Worker launch

Retail takes manager in EAX and filename on the stack, returning with RET 4.
The candidate exposes two stdcall arguments/RET 8. It copies filename bytes
forward, including the terminator, into manager `+0x5108` **before** checking
the device-owner pointer or device. Copying has no bounds/overlap protection.
A missing owner/device returns `-1`. The owner cell itself is not dereferenced
by these initial checks.

After stopping the prior worker, it loads the record at manager `+0x1f84`,
caches its block alignment and sample rate, and calculates segment length as
`((sample_rate * alignment) << 2) >> 4`, with unsigned 32-bit wrapping at both
operations. This is not an unbounded product divided by four. It calls
CreateEvent with four zeros and stores the result at `+0x520c`. It calls
CreateThread with the worker entry `0x43e3a0`, the current global argument at
`0x491c70`, zero creation flags and the ID output at manager `+0x614`.

After CreateThread, it reloads the event, publishes the returned thread at
`+0x618`, then subtracts `segment_length % cached_alignment`. A zero alignment
therefore divides by zero after both handle publications. Callback changes to
the format do not repair or alter the cached divisor/product.

The factory receives output `manager + 0x5208`, flags `0x10100`, the current
owner pointer, the **original filename pointer**, four current algorithm words
from `0x46a67c`, count 16, rounded length, reloaded event and cached record.
Only a negative factory HRESULT becomes `-1`; all nonnegative results become
zero. Event/thread creation failure is not checked, and a failed factory leaves
the new handles in the manager. Tests independently assert that retained state.

Integrated tests execute the actual stop candidate, maintained interface
aggregator, file factory, opener, single-buffer constructor, refill and cursors.
They cover existing or missing streams/threads, repeated shutdown waits,
callback changes, allocator/COM failures, short reads, silence padding, invalid
handles and missing format data. The deleting destructor remains scripted.
CreateThread records its actual entry and argument but does not run a concurrent
worker. The launch candidate compiles to 237 Clang bytes versus 241 retail.

## Reproduction and limits

```sh
python3 matching2/tests/music_cursor_open_differential.py
python3 matching2/tests/sound_stream_create_file_differential.py
python3 matching2/tests/sound_stream_create_file_unwind.py
python3 matching2/tests/sound_stream_launch_differential.py
```

The local interpreter is
`matching2/build/lzss-compressor-recovery/venv/bin/python`. Tests freshly compile
the candidates and compare ordered callback traces, state visible at calls,
memory, returned values, allocation/free ledgers, fault addresses/access widths,
stack cleanup and preserved registers. Zero division is compared as x86
interrupt zero. Successful calls restore the initial FS exception list.

Win32, COM and allocators are scripted boundaries. These results do not prove
live audio, asynchronous thread scheduling, Windows exception dispatch, or native
MSVC ABI/frame/byte equivalence. The session also prevents Wine socket startup,
so the native compiler could not be exercised. Full-region and whole-executable
byte gates remain required. No region was promoted or exactness rule relaxed.


## Native attempt, parked (2026-10-02)

`reference/semantic_candidates/sound_stream_create_file_native/` holds a
native-LTCG candidate for the launch (0x0043D690) and the file factory
(0x0044C8F0) with its unwind funclets (0x00465330 / 0x0046533B), plus the
adopt spec. Neither is exact; nothing in the manifest changed.

Established:

* The factory keeps declared `__fastcall` (output ECX, flags EDX, RET 40)
  only when it is listed in `roots`. Unrooted, LTCG passes flags in ECX and
  the name in EDX instead.
* The launch's failure-return layout needs
  `if (!device_owner) return -1; if (!device) return -1;` and
  `if (Create(...) < 0) return -1; return 0;`.
* The read cursor is `new`ed with an inline constructor (record, methods,
  total, buffered cleared in that order) and discarded with an inline
  destructor that closes the file handle; `SAFE_DELETE` shape.
* The body follows the SDK `CreateStreaming` order; the rooted candidate has
  the retail frame (0x50) and the same slots, 210 instructions against 214.
* The handler region at 0x0046533B is 10 bytes plus one INT3; adopting it
  needs the padding region moved to 0x00465345.

Open (same symptom in the memory factory 0x0044CBF0 model):

* Retail loads the segment count into EBP at entry and keeps it there, so the
  zero constant stays in ECX and the cursor stays in its stack slot. The
  candidate loads the count only after the cursor open. Declaring the count
  with any pointer type reproduces the entry load (`unsigned int`, `int`,
  `unsigned long`, `size_t` and a one-field struct do not), but then the
  track pointer loses its register to the zero constant.
* Launch: retail stores the event before loading the worker argument and
  loads the owner after the name (EDX), leaving ECX for the result test.
