# Sound cleanup and MIDI worker shutdown

2026-09-26. `semantic_candidates/sound_cleanup.cpp` and `sound_midi_stop.cpp`
recover the complete 301-byte cleanup at `0x0043D120` and 176-byte MIDI stop
at `0x0043DAB0` as ordinary C++. Tests pass **187 individual comparisons with
25 matching faults**, plus **106 integrated comparisons with 24 matching
faults**. Integrated calls execute the maintained interface aggregator at
`0x0044D550`. A separate archive-to-shutdown suite passes **28 scenarios,
874 published buffers, 321 WAVE consumptions, 553 unconsumed pending frees and
56 sound-cleanup calls**. Production remains the exact assembly.

The subsequent [stream-start recovery](sound_stream_start_0044d440.md) clarifies
that the object and thread at `0x5208`/`0x0618` implement streamed music over
DirectSound. The shared types now call these `SoundStream`, `music_stream`,
`music_thread`, `music_thread_id` and `music_worker_event`; the candidate stop
entry is `Sound_StopMusicWorker_0043dab0`. Historical MIDI file/test names and
production symbols remain. The existing shutdown suites pass after renaming.

## Evidence and shared layout

Saved Ghidra C/instruction listings, maintained retail bodies and hash-verified
retail bytes establish the contracts. The current Ghidra decompilation request
for `0043D120` was rejected with `MCP tool call requires approval, but approval
policy is never`. Native MSVC execution is also still unavailable under the
Wine socket restriction; no native or whole-executable match is claimed.

`semantic_candidates/sound_wave_types.hpp` now names the additional fields:

| Offset | Observed use |
| --- | --- |
| `0x0614` | MIDI worker thread ID |
| `0x0618` | stream cursor / MIDI worker handle union |
| `0x1ec0` | 16 cached music allocation pointers |
| `0x1f84` | loaded music image |
| `0x5208` | MIDI output object, first vtable slot is deleting destructor |
| `0x520c` | companion handle |

The existing secondary-buffer method table now names Stop at byte offset 72.
The later [music-cache recovery](sound_music_cache_0043d7d0.md) identifies the
formerly auxiliary allocations as cached music data; the shared field is now
`cached_music_data`. The cleanup body retains the same operations and passes
its existing individual and integrated comparisons after that rename.
Compile-time offset assertions protect the recovered manager fields and that
COM slot. Existing initializer, WAVE-loader and preload-worker tests still pass
with the expanded shared layout. The union retains both observed uses of the
same four-byte field instead of describing two independent members.

## Cleanup ordering and ownership

The music image is freed and its field cleared first. Cleanup then visits 128
pairs of secondary slots: `128, 0, 129, 1, ... 255, 127`. For each nonnull
pointer it calls Release and clears that slot after the callback. The 37
pending WAVE pointers are then freed and cleared in ascending order. None of
this requires a device-owner cell. Changes to future slots during callbacks
affect their later reads, while changes to the just-released slot are cleared.

The remaining operations run only if `device_owner` is nonnull at the branch
after pending cleanup. They proceed in this order:

1. KillTimer(window, 1), ignoring its result, then the actual MIDI-stop helper.
2. Capture the current stream pointer, clear the raw device field and call
   stream Stop unconditionally. A null stream faults after the device clear.
3. Reload the stream pointer; release and clear it if nonnull. A Stop callback
   can change which interface is released. The Release return value is ignored.
4. Reload the MIDI output; invoke its deleting destructor with ECX receiver
   and stack flag 1 when present, then clear the field. This can clean an object
   published after MIDI stop, including one installed by the stream callbacks.
5. Reload the owner cell. Release its current device, clear the cached cell,
   free that cell via `0x4524A1`, then clear the manager's owner field. A Release
   callback replacing the manager's owner does not replace the cached cell.
6. Free and clear all 16 auxiliary allocation slots.

Entering the outer owner branch is sufficient to reach auxiliary cleanup:
callbacks may clear the owner field later without cancelling the branch.
An absent owner at the initial branch skips timer/MIDI/stream/owner/auxiliary
cleanup entirely. Every normal return is zero. No fault or exception path
gains an invented scope guard or successful-return fallback.

## MIDI shutdown

An initially null MIDI output makes the entire helper a no-op, even with a
nonnull thread handle. Otherwise, the output is passed to the interface
aggregator, whose result is ignored. The aggregator stops and queries each
configured interface and clears its operation/active fields. The integrated
fixture covers missing/empty lists, negative results, changed lists, changed
counts and an output pointer replaced during those callbacks.

After aggregation, a currently nonnull thread handle starts shutdown polling:

- Capture PostThreadMessageA, post `(current_thread_id, 0x12, 0, 0)`.
- Only after that first Post returns, capture WaitForSingleObject and call it
  with the current handle and 256 milliseconds.
- Repeat Post and Wait using those cached imports until Wait returns exactly
  zero. Timeout, abandoned, failure and other nonzero values all repeat.
- Capture CloseHandle after the successful wait. Close the current thread
  handle, then the current companion handle, including null. Clear the thread
  field after both calls. The companion field itself is not cleared.

The final output is reread and destroyed with flag 1 if nonnull, then its
field is cleared. It can differ from the object passed to aggregation. Callback
tests distinguish import capture timing, current IDs/handles, cached Close,
and clearing after callbacks. The historical injected model allowed absent
callbacks and lacked the proper destructor receiver; it is now explicitly
marked as an approximation.

## Validation and remaining native work

```sh
python3 matching2/tests/sound_shutdown_differential.py
python3 matching2/tests/sound_archive_shutdown_integration.py
```

The local interpreter is `matching2/build/lzss-compressor-recovery/venv/bin/python`.
Individual and integrated shutdown tests compare full manager/object/data
memory, ordered calls and callback-time state, import mutations, return values,
memory faults, stack cleanup and preserved registers. Independent assertions
check bank ordering, skip behavior, mandatory stream Stop, wait sequences,
cached imports and both close calls. Fixtures include sparse/full/random
tables, missing fields and callbacks replacing current/future owned slots.

The archive lifecycle suite freshly compiles the recovered DAT closure,
producer, WAVE loader, cleanup, MIDI stop and maintained cached loader/chunk
walker/aggregator. A sequential schedule consumes selected published images
and leaves the rest pending. Shutdown must free every published image exactly
once, release consumed secondary buffers, run the optional MIDI path and clear
owned state. A repeated cleanup call must change nothing. Partial production
and an absent owner at cleanup are also compared before archive closing.

Native Clang emits 783 bytes for cleanup and 161 for MIDI stop; the maintained
aggregator's Clang body is 97 bytes. These are behavioral fixtures. Retail
cleanup takes its manager in EAX and MIDI stop takes it in ESI, both with plain
RET. The candidates use an explicit stdcall manager argument and RET 4.
The aggregator takes its object in EDI in retail; the candidate's one-pointer
fastcall declaration binds to the compiled maintained thiscall method, both
using ECX and no stack arguments in the fixture. These bindings do not recover
retail's private native conventions.

OS imports, COM methods, allocation/free and file I/O remain scripted.
Arbitrary concurrent schedules, real Windows handles/audio, exception dispatch,
native private ABIs and full frame/byte matching remain unverified. Complete
region and whole-executable gates are still required before any promotion.
