# Cached music launch and existing-file track selection

2026-09-26. `sound_stream_launch_cached.cpp` recovers the complete 298-byte
routine at `0x0043D950` as readable C++ without inline assembly. Its Clang
behavioral build is 297 bytes; native MSVC ABI/byte matching remains pending,
and the exact manifest retains the assembly entry.

The new suite passes **282 unit comparisons, including 39 faults**, and **91
integrated comparisons, including nine faults**. Integrated memory-mode cases
execute the memory factory, single-buffer constructor, refill and cursor code.
File-mode cases execute the maintained name selector, basename lookup and cursor
record selector. Independent assertions check arguments, selected-slot updates,
failure ownership and an actual name-to-record selection.

## Entry and mode routing

Evidence is the saved Ghidra C/full-instruction export, current maintained
assembly/callees and the retail image verified against the manifest SHA-256.
The live MCP and native compiler restrictions are recorded in
[the file launch recovery](sound_file_stream_open_create_launch.md). No further
tool approval or permission workaround was attempted.

Retail receives manager in ESI and slot index in EAX, with plain RET. The
candidate exposes two stdcall arguments/RET 8. It returns `-1` when the manager's
owner pointer is null, global byte `0x491d63` is zero, or the manager's device is
null, in that order. The owner cell is not dereferenced at this stage. Any
nonzero enable byte is accepted.

When bit `0x10` of global byte `0x491d78` is clear, it delegates to the maintained
`0x43d790` with the slot name at `manager + 0x4108 + index * 256`. That helper's
result is returned unchanged. There is no event/thread creation or selected-slot
write on this branch. Index calculations are unchecked and wrap at 32 bits;
the candidate uses integer address calculations to preserve this behavior.

## Memory-mode creation

With mode bit `0x10` set, a null cached allocation at `+0x1ec0 + index * 4`
returns `-1`. The routine then reads the record pointer at `+0x1e80 + index * 4`
and caches its sample rate and block alignment. Segment size is
`((sample_rate * alignment) << 2) >> 4` using unsigned 32-bit wrapping, then
rounded downward to a multiple of the cached alignment.

As in the file launcher, CreateEvent receives four zeros and its result is
published at manager `+0x520c`. CreateThread receives worker `0x43e3a0`, the
current global argument at `0x491c70`, zero flags and thread-ID output `+0x614`.
After that call, the current event is loaded, the returned thread is published
at `+0x618`, and the alignment modulus occurs. Zero alignment therefore faults
after both handles are stored. Event/thread results are not checked.

This path **does not stop or delete an existing worker/stream** before creating
the new ones. It does not reread the cached-allocation guard after callbacks.
The memory factory receives output at `+0x5208`, flags `0x10100`, the current
owner pointer, current PCM cursor from `+0x1f00 + index * 4`, current remaining
length from `+0x1f40 + index * 4`, and the current record pointer from
`+0x1e80 + index * 4`. Thus callback edits can change the supplied record or PCM
range while segment sizing still uses the earlier format values. The four
algorithm words at `0x46a67c` are also read after thread creation. Count is 16;
the event is the value reloaded immediately before thread publication.

A negative factory HRESULT returns `-1` without updating selected slot
`+0x1f80`. All nonnegative results store the original slot index and return zero.
A failed factory retains the new handles and any previous output pointer it
did not replace. Successful creation overwrites the old stream pointer without
cleanup by this caller. Independent assertions verify the absence of stop,
destroy, PostThreadMessage and CloseHandle events.

## Existing-file track selection

Three already-maintained C++ bodies execute on this integrated branch:

- `0x43d790`, `PathName_0043d2a0::SelectArchiveEntry`, 55 retail bytes;
- `0x43d2a0`, `PathName_0043d2a0::FindBasenameSlot_0043d2a0`, 227 bytes;
- `0x44dca0`, `PlatformStreamState_0044DCA0::Select`, 78 bytes.

The first helper returns `-1` when manager stream `+0x5208` is null. Otherwise
it looks up the name, forms the 52-byte record address from the current table
at manager `+0x1f84`, reloads the current stream and its reader, and asks that
reader to select the record. It ignores the selection HRESULT and returns zero.

The name lookup searches the basename after the last slash, or the last
backslash only if no slash exists. It walks the null-name-terminated record
table and falls back to index zero when no match exists. As in the earlier
music-cache fixture, integrated tests execute retail `strrchr` and `strcmp`;
the Clang build's non-inlined `strcpy` uses a compiled byte-copy fixture. Names
here fit the helper's 128-byte local. Stack-cookie overflow behavior is not
claimed.

The cursor selector rejects nonzero buffered mode or file handle `0xffffffff`
with `0x80004005`, before changing its record. Otherwise it stores the supplied
record. A nonnull handle is sought to record file offset plus global `0x4977a4`,
ignoring Seek's result. After the callback it reloads the cursor's record and
sets remaining bytes from its loop end. A null handle skips Seek and that
update. Total PCM bytes then receives the current remaining-byte value.

Tests cover valid/missing names, slash forms, null/invalid file handles,
buffered-mode rejection, callback replacement of the table/reader/record,
missing streams, null pointers and unchecked arithmetic. All three maintained
bodies agree with retail under these tests; no edits or additional promoted
regions are attributed to them.

## Reproduction and remaining boundaries

```sh
python3 matching2/tests/sound_stream_launch_cached_differential.py
```

The available local interpreter is
`matching2/build/lzss-compressor-recovery/venv/bin/python`. The suite freshly
compiles every tested C++ body. `LaunchHarness` shares Win32 event/thread
fixtures and state/ABI checks with the file launcher; the latter's 256
comparisons still pass after that refactor. Memory comparisons include full
manager/cursor/PCM arenas, ordered callback-time state, ownership ledgers,
fault access/address/width, zero-division interrupts, return values, stack
cleanup and preserved registers. Successful returns restore the FS exception
list after the integrated memory factory.

This is behavioral evidence with scripted Win32/COM/allocator boundaries.
CreateThread does not schedule a live concurrent worker. Native MSVC private
ABIs, EH/frame layout, exact bytes and whole-executable gates remain outstanding.
The 373 comparisons are additional to the 620 file-open/create/launch checks,
bringing this batch to **993 comparisons over four new candidate routines
covering 1,414 retail bytes**. Regressions are counted separately.
