# Stream initialization, notification recreation and memory-backed creation

2026-09-26. Four complete C++ candidates now cover 1,216 retail bytes without
inline assembly. The exact manifest continues to use its existing assembly.

| Retail routine | Bytes | Candidate |
| --- | ---: | --- |
| `0x0044CE80`, initialize buffer array | 118 | `sound_stream_initialize.cpp` |
| `0x0044D6A0`, initialize one streaming buffer | 109 | `sound_stream_initialize.cpp` |
| `0x0044CF20`, recreate buffers and notifications | 338 | `sound_stream_recreate.cpp` |
| `0x0044CBF0`, create a stream over memory PCM | 651 | `sound_stream_create_memory.cpp` |

Initializer/recreation tests pass **215 unit comparisons, with 29 faults**, and
**36 integrated comparisons, with five faults**. They include 96 notification
installations, an independent table-content assertion, and eight complete
initialize–recreate–restart sequences. Factory tests pass **91 unit comparisons,
with eleven faults**, and **30 integrated comparisons, with six faults**.
An independent factory assertion checks publication, ownership and PCM padding.
Another **65 registered-state/unwind-action comparisons** pass, including
cleanup after a null stream publication. This totals 437 comparisons.

## Evidence and layout

Saved Ghidra C and full instruction exports for all four addresses, the original
retail image verified against the manifest's SHA-256, current maintained
assembly, and related callers/callees provide the evidence. The new Ghidra MCP
request for `0044CF20` was denied by the current session's approval policy.
The saved high-level output omits reachable notification-release branches;
the complete instructions and differential execution establish those paths.

The shared `SoundStreamingState` now names its 36-byte description at `+0x34`,
device-owner cell at `+0x58`, and notification event at `+0x70`. Its previously
recovered playback fields retain their offsets, and the object size is `0x78`.
`WaveNotificationPosition` is an eight-byte offset/event pair. The notification
interface has Release at vtable byte offset 8 and SetNotificationPositions at
12. The buffer QueryInterface slot is typed for the observed notification IID
at `0x46743c`. Cursor, description, notification and object size assertions are
checked during compilation.

## Initializers

The array initializer takes stream in ESI, source in EAX, count in EDI, and
buffer byte count/reader on the stack, returning with RET 8. It installs the
base vtable `0x4705d8`, allocates `count * 4` with 32-bit wrap, and copies one
pointer at a time. Each iteration loads the source before reloading the
destination array, preserving overlap and aliases with stream fields. There
is no AddRef, allocation check, bounds check, or release of an old array.

It stores byte count, original count and reader, then reads the first array
slot and calls full refill with repeat zero even when count is zero. It ignores
the refill result. It then calls SetCurrentPosition(buffer, 0) for each original
index, reloading the array after callbacks but retaining the incoming count.
Position results are ignored; playing is finally cleared and the stream
returned. Null allocation can fault before any refill. Zero-size allocation
may instead expose its untouched first word as the buffer argument.

The single-buffer initializer takes ESI plus four stack arguments and RET 16.
It installs the base vtable, allocates a four-byte array without a null check,
stores the buffer/reader/byte count/count=1, and invokes full refill. It ignores
that result and reloads the current first buffer for SetCurrentPosition(0),
also ignoring its result. Only after those calls does it clear playing and the
four progress fields, install derived vtable `0x4705d4`, and store the segment
length. Description, owner, notification event, servicing, and unrelated
fields remain untouched. The final COM operation is not Release.

Both candidates use explicit five-argument stdcall interfaces. Their combined
Clang module is 393 bytes including alignment, versus 227 retail bytes.

## Buffer recreation

Recreation takes ESI and returns with plain RET. It clears playing, releases
nonnull buffers, and clears each slot through the current array **after** its
Release callback. Count is reloaded on every iteration. It frees the current
array when nonnull, clears that field after the callback, and allocates a new
`count * 4` array. The fresh array is not zeroed or checked for null.

For each current index it reloads the owner/device and calls CreateSoundBuffer
with the description embedded in the stream and the current output slot.
Negative creation returns `0x80004005`; successful creation is followed by
QueryInterface for the notification IID. Negative QueryInterface returns the
same generic error. Neither branch rolls back prior buffers or allocations.

It allocates 16 notification pairs (`0x80` bytes). Allocation failure returns
`0x8007000e` without releasing the acquired notification interface. Each pair
contains `segment_bytes * (index + 1) - 1`, with 32-bit wrap, and the current
event. The two stream fields are reread for every pair; volatile word stores
preserve that behavior even when the allocated table aliases stream state.

SetNotificationPositions receives count 16. Afterwards the current local
notification output is checked and released, then cleared; callbacks may have
replaced or nulled that escaped output. The table is freed on both success and
failure. Negative Set returns `0x80004005`; otherwise count is reloaded before
the next buffer. A null QueryInterface output on apparent success faults when
used later. The candidate adds no rollback for these partial states and
compiles to 632 Clang bytes versus 338 retail.

## Memory-backed stream factory

Retail receives output in ECX, flags in EDX and eleven stack arguments:
owner, PCM base, PCM byte count, music record, four algorithm words, segment
count, segment length, and notification event. It returns with RET 44. The
candidate exposes all thirteen arguments with stdcall/RET 52.

A null device inside the owner cell returns `0x800401f0` without modifying the
output. A null owner itself faults. The factory allocates a `0x94` cursor and
initializes only its record, methods, total-PCM and buffered fields before
writing record/base/current/extent and buffered=1. A failed cursor allocation
still reaches the record write at address `0x90`. Unspecified cursor bytes
retain allocator contents; the total-PCM field remains zero here.

The description has size 36, flags ORed with `0x18188`, byte length equal to
segment count times segment length with wrap, zero reserved, format pointing
at the cursor's current record plus `0x20`, and the four supplied algorithm
words. It creates a buffer and queries notifications. Negative creation/query
returns generic `0x80004005`, retaining the cursor and any produced objects.

Notification storage is `segment_count * 8`. Null storage returns
`0x8007000e` and retains prior allocations/interfaces. Unlike recreation, this
table uses the supplied count and length. Each pair stores event first and then
offset, beginning at `segment_length - 1` and advancing with wrap. Set's
nonnegative results count as success. The current notification output is
released if nonnull, and the table is freed on either Set result; negative Set
then returns `0x80004005`. Buffer/cursor allocations are not rolled back.

On success it allocates a `0x78` stream, invokes the single-buffer initializer
when nonnull, and publishes the initializer's return value. It copies the
escaped description forward as nine words, preserving callback edits. It then
reloads the output for each owner/event/servicing write. A null stream allocation
publishes null before faulting on the copy at `0x34`; an output alias overwritten
by the descriptor can change later write targets. The initializer's refill and
position errors remain ignored inside this complete path.

## Cleanup scope and compiler evidence

Retail handler `0x46531b` points to FuncInfo `0x471374`. Its one unwind state
invokes action `0x465310`, which frees the raw stream allocation at frame offset
`-0x48`, including null. Earlier cursor/buffer/notification failures have no
active cleanup. During the single-buffer constructor, even a failure after its
internal pointer-array allocation frees only the raw outer stream; the cursor,
buffer and internal array are not separately released by this action.

The C++ candidate models that ownership with a scoped `PendingSoundStream`
guard, disarmed after publication and metadata stores. The fixture uses Clang
`-fasync-exceptions`: with ordinary synchronous C++ exceptions, Clang clears
the registered state before the post-constructor memory stores. That differs
from retail at a null publication fault, where the retail state remains zero
and its action frees null. The unwind suite separately recompiles synchronous
Clang and asserts this state gap (`-1` versus `0`); it is not counted as a pass.
Asynchronous compilation retains the state and passes the 65 action comparisons.
The asynchronous module is 988 bytes including code, cleanup and metadata;
the synchronous diagnostic module is 940 bytes.

The unwind test suspends at allocation, Create, Query, Set, Release, Free,
constructor, refill and position calls. It reads the actual FS frame record,
handler thunk, FuncInfo and unwind-map entry; when active, it executes the
selected action with the suspended frame. Two additional cases inspect the
null-publication fault and execute its action. Frame removal is fixture work.
The test explicitly distinguishes retail FuncInfo version `0x19930520` from
Clang's `0x19930522`; it never substitutes one runtime handler for the other.

`tests/x86_seh.py` installs a separate FS thread block and flat 32-bit code/data
segments in Unicorn. This preserves 32-bit stack addressing, allows the real
FS frame-link instructions, and leaves the null page unmapped. Successful
factory calls must restore the initial exception-list sentinel. The retail
security-cookie instructions also execute normally.

## Commands and remaining boundaries

```sh
python3 matching2/tests/sound_stream_initialize_differential.py
python3 matching2/tests/sound_stream_create_memory_differential.py
python3 matching2/tests/sound_stream_create_memory_unwind.py
```

The local interpreter is
`matching2/build/lzss-compressor-recovery/venv/bin/python`. All suites freshly
compile the candidates and compare original instruction execution against
their behavior. Results include callback-time state, ordered ownership events,
memory, allocation/free ledgers, fault addresses/access widths, stack cleanup,
and preserved registers. Integrated cases execute recovered initializers,
[refill/cursors](music_cursor_and_stream_refill.md), and
[restart/restoration](sound_stream_restart_service_worker.md). Existing WAVE
loader and worker suites pass after the shared-type changes.

Allocators and COM/Win32 methods are scripted boundaries. These tests do not
establish Windows exception dispatch, live audio, general concurrent behavior,
or native MSVC EH/ABI/frame equivalence. In particular, the asynchronous Clang
setting is behavioral evidence, not a replacement for the native compiler
profile. Full-region and whole-executable byte gates still apply; no region
was promoted and no exactness rule was relaxed.
