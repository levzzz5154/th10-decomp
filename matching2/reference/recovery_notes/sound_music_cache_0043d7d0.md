# Music slot caching

2026-09-26. `semantic_candidates/sound_music_cache.cpp` recovers all 369 bytes
at `0x0043D7D0` as ordinary C++. Together with the 32-byte
[music-table wrapper](archive_load_cache_slot_0043d670.md), it passes **282
retail comparisons, including 79 actual maintained basename lookups and six
matching faults**. Production remains assembly pending native byte gates.

## Evidence and layout

The saved Ghidra `0043D7D0` and `0043D2A0` C/instruction listings, maintained
instruction bodies and verified retail executable establish the behavior.
The live Ghidra request for `0043D7D0` was again rejected by the session's
approval policy. No restricted access was bypassed.

The shared sound manager now has these typed fields:

| Offset | Field |
| --- | --- |
| `0x1e80` | 16 selected music-record pointers |
| `0x1ec0` | 16 owned cached music buffers |
| `0x1f00` | 16 music read cursors |
| `0x1f40` | 16 remaining-byte counts |
| `0x1f80` | selected music slot |
| `0x1f84` | loaded metadata image |
| `0x4108` | 16 cached names of 256 bytes each |
| `0x5108` | 256-byte current container path |

`MusicTrackRecord` is 52 bytes: a 16-byte name, file offset at `0x10`, data
length at `0x14`, two still-unknown dwords, then the packed 18-byte format at
`0x20` and tail padding. Compile-time assertions cover the record size and
manager offsets. The cleanup candidate now calls its formerly auxiliary
allocations `cached_music_data`; its operation order is unchanged.

## Cache and name behavior

An existing slot buffer plus an exact, case-sensitive match against the supplied
manager's cached name returns zero immediately. Otherwise, the requested name
is copied into the **global manager's** name slot, even when the receiver is
another manager. The copy is forward, byte-by-byte, includes the terminator,
and is unbounded. Only after this write does the routine test global flag
`0x491D78 & 0x10` and the receiver's device-owner cell. An inactive mode or
absent owner returns zero with the new global name already written.

Tests cover local/global receivers, unchanged/different names, slot -1 and 16,
32-bit multiplication wrap, names longer than 256 bytes and overlapping source
and destination. A forward overlap that propagates the leading byte eventually
faults at the mapped-memory boundary in both bodies; no bounded-copy behavior
was substituted. Byte accesses are volatile to retain their width/order.

Repeated loads make the receiver distinction observable. A global receiver
hits its newly written cache name on subsequent calls. A separate receiver
keeps its original local name and reloads the same requested file on each call.
That global cache hit still happens when the original ReadFile returned false
and supplied zero bytes, because the pointer was published regardless.

## File path and metadata timing

The old slot allocation is freed and the slot cleared before opening the
receiver's current container path. A free callback changing the slot is still
overwritten by that clear. Clearing the device-owner field during free does
not cancel the already-entered loading path.

CreateFile receives access `0x80000000`, share 1, disposition 3 and flags
`0x08000080`; only handle -1 is rejected. A successful open calls the maintained
basename helper at `0x43D2A0` with the requested track name and receiver. That
helper searches for the last forward slash first, using a backslash search
only when there is no forward slash anywhere. It compares record names
case-sensitively and selects record zero if no record matches, including an
empty table. It does not report missing tracks as failure.

The selected index becomes a wrapping 32-bit byte offset `index * 52`. The
metadata-image pointer and relevant fields are reread at each boundary:

1. Read the record's file offset after lookup; call SetFilePointer.
2. Reload the image/record length after Seek; allocate that length.
3. Reload the length again after allocation; pass it to ReadFile.
4. Call CloseHandle, then reload the image to publish the selected record,
   allocated buffer, initial cursor and current record length.

Thus a changed record length can make the read request differ from the
allocation request, and a Close callback can change the final record/count.
Neither Seek's result, ReadFile's BOOL, actual bytes read nor Close's result
determines success. A nonnull allocation is published with return zero even
after a failed/short read. A failed allocation closes the file and returns -1;
an invalid open returns -1 without Close. Faults gain no invented cleanup.

## Validation and remaining work

```sh
python3 matching2/tests/sound_music_cache_differential.py
```

The local interpreter is `matching2/build/lzss-compressor-recovery/venv/bin/python`.
Native Clang emits 381 bytes for music caching and 37 for table publication,
versus retail's 369 and 32. The cache candidate uses three stdcall arguments
and RET 12. Retail uses name in EAX, manager in ESI and one stack index/RET 4.
The table wrapper has its own EAX/stack split, documented separately.

Unit cases script the basename result to probe file/control behavior and
callback changes. Seventy-nine integrated cases compile maintained `path.cpp`
and execute its helper with the matching ECX path/stack-owner convention.
The actual retail strrchr/strcmp bodies run. Clang emits a strcpy library call
where MSVC inlined the copy; a separately compiled ordinary C++ byte-copy
fixture supplies that contract. Integrated basename strings fit the 128-byte
local; no stack-overflow or native stack-cookie-frame equivalence is claimed.

Comparisons include full local/global mapped state, data/guards, call order,
callback-time metadata/slot values, file positions, results, faults, preserved
registers and each entry's stack cleanup. Separate assertions cover mixed
separator precedence, missing-name fallback, copies/guards, ignored read
failures and different repeated-load behavior for local/global managers.

The initializer, shutdown and complete archive-to-shutdown suites also still
pass after expanding the shared layout. Native MSVC private ABI/frame/byte
matching, live filesystem behavior and general concurrency remain unverified.
The exact region and whole-executable gates remain required before promotion.
