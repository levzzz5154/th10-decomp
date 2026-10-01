# Music stream restart, segment servicing and notification worker

2026-09-26. New candidates recover the full 213-byte restart at `0x0044DAD0`
and the complete 634-byte servicing function split across `0x0044D850` and
`0x0044D9F0`. They contain no inline assembly. A typed worker candidate at
`0x0043E3A0` clarifies the already-maintained C++ worker and makes the retail
import caching explicit. None of these candidates replaces a manifest body.

| Comparison group | Cases | Matching memory/division faults |
| --- | ---: | ---: |
| Restart/service with scripted dependencies | 435 | 8 |
| Restart/service with executing restore/refill/cursors | 55 | 3 |
| Notification worker with scripted service | 53 | 1 |
| Worker with executing service/refill/cursors | 24 | 2 |

The service groups include three bounded no-progress traces; the worker group
includes one bounded wait trace. These are distinct from the fault counts.
The worker suite executes 43 service calls and includes four restart-then-worker
sequences. An independent PCM assertion verifies intro data followed by two
repetitions starting at the track's loop offset.

## Evidence and shared types

Saved full Ghidra instructions for `0044DAD0`, `0044D850`, and `0043E3A0`, their
callers, the maintained source/manifest, and SHA-256-verified retail bytes are
the evidence. The new live Ghidra request for `0044D850` was denied by the
session approval policy. Its saved high-level output drops reachable refill
blocks and misidentifies several locals; complete instructions were used to
recover those branches.

`SoundStreamingState` extends the known `SoundStream` prefix with previous
play position at `+0x5c`, played-byte total at `+0x60`, write offset at `+0x64`,
end flag at `+0x68`, segment length at `+0x6c`, and servicing flag at `+0x74`.
The cursor's `+0x2c` is the total PCM length used for playback completion.
The existing `0x44DCA0` record selector confirms it copies the selected track's
remaining length into this field. DirectSound GetCurrentPosition is now typed
at vtable byte offset 16; the other established slots retain their offsets.

## Restart at `0x44DAD0`

Retail dereferences the buffer array before testing its first entry. A null
array faults; a null first buffer or reader returns `0x800401f0`. Restart clears
the four fields at `+0x5c..68` before calling RestoreIfLost on the first buffer.
The saved ECX word is a restoration-output local, not an inherited refill flag.
Tests vary ECX separately from the helper's output.

A negative restoration result returns immediately. A nonzero restoration flag
causes full refill with repeat zero, using the current first buffer; a negative
refill also returns. The current reader is then reset in place: memory mode
sets position to base and updates a positive signed end; file mode seeks when
the handle is nonnull, ignores the result, reloads metadata, and sets remaining
length. A missing file handle merely skips this reset's file branch.

Finally restart reloads the current first buffer and calls SetCurrentPosition
with zero, returning that HRESULT unchanged. This is neither Release nor Stop.
Reset/refill failures do not roll back the four cleared fields and do not call
SetCurrentPosition. The candidate uses explicit stdcall rather than retail's
EDI receiver and plain RET. It compiles to 224 Clang bytes versus 213 retail.

## Segment service at `0x44D850` / `0x44D9F0`

The conventional stdcall arguments are stream and repeat, with RET 8. Both
manifest rows are parts of this one function; the second cannot be translated
as an independent entry.

The function guards the buffer array and reader, but not the array's first
buffer. It calls GetCurrentPosition with both outputs and ignores its HRESULT.
The busy check uses the **write cursor**:
`write_offset >= write_cursor - segment_bytes && write_offset < write_cursor`,
with unsigned 32-bit arithmetic and no circular-range correction. The initial
play cursor output is unused. A busy segment returns `0x800401f0`.

RestoreIfLost then runs on the current first buffer. A negative result returns;
a nonzero restoration flag calls full refill with repeat zero and returns its
negative HRESULT or zero. This full-refill branch skips the later segment and
playback accounting.

Otherwise Lock receives the current write offset and segment length. Both
region pointer outputs start at zero; retail reuses the stream argument's
stack slot for the first byte-count output, initially the stream pointer bits.
The candidate explicitly preserves that initial value. A negative Lock or any
nonzero second-region pointer returns without Unlock; the second region's
reported length is irrelevant to that rejection.

If the end flag was already set, service writes silence across the first span.
Otherwise it reads with the current cursor. A negative result leaves the lock
held. A short read with repeat disabled pads the tail, then sets the end flag;
a padding fault leaves the flag unchanged. A short read with repeat enabled
repeatedly rewinds with mode **one** and reads the remaining span. This honors
the positive loop-start offset and enters the repeat loop even after an initial
zero-byte read. It has no zero-progress guard. Full-buffer refill instead uses
mode zero and pads an initial zero read; those behaviors remain separate.

Unlock uses the current first buffer, not necessarily the buffer that was
locked, and ignores its HRESULT. Another GetCurrentPosition uses a distinct
play-position local and a null write-position output. Its negative HRESULT
returns before accounting. Success computes played distance with a single
buffer wrap, adds it to the unsigned total, and stores the new position. If
the end flag is set and total reaches the current reader's total PCM length,
it calls Stop on the current first buffer and ignores that result. Finally it
reloads write offset and buffer size after Stop and stores
`(write_offset + locked_bytes) % buffer_bytes`. Zero buffer size retains the
retail divide fault.

The candidate is 764 Clang bytes versus 634 retail bytes. Its entry convention
matches the retail stack contract, but its helper conventions and native frame
still differ. No native MSVC exactness claim follows from behavioral agreement.

## Notification worker and maintained-source gap

The 189-byte worker is already semantic in `src/platform/midi_worker.cpp`, but
its historical names and comments incorrectly described MIDI stop processing.
The `+0x30` field means playing; `+0x74` brackets segment servicing. Production
comments now identify these roles; its matched body/symbols remain unchanged.

The worker caches PeekMessage and MsgWaitForMultipleObjects once at entry.
Each wait uses one handle at `0x49779c`, wait-all false, infinite timeout and
mask `0xbf`. It checks the active stream at `0x497798` after the wait. A null
stream requests exit, but the current wait result is still processed.

Wait result one drains all queued messages with removal, including messages
after WM_QUIT (`0x12`). Any WM_QUIT requests exit after draining. Wait result
zero services a nonnull, playing stream: set its servicing flag, reload the
global stream for `Service(stream, 1)`, ignore that result, then reload the
global again and clear its servicing flag without checking null. Replacement
can leave the old stream marked servicing and clear the new one instead;
replacement with null faults at address `0x74`. Other wait results, including
failures, retry unless exit was already requested. The unused thread argument
is popped with RET 4, and normal termination returns zero.

The maintained C++ compiles to 165 Clang bytes and passes 76 of the 77 worker
cases. The import-mutation case reproduces a difference: Clang reloads the
IAT pointers on later calls whereas retail retains its cached callbacks.
The new typed 196-byte candidate caches them explicitly and passes that case.
It also calls the now-known two-argument stdcall service directly instead of
casting a cdecl assembly declaration. Native MSVC may already choose retail's
caching for the maintained source; it is retained pending native evidence.
This comparison does not count the maintained-source mismatch as a pass.

## Validation and outstanding native work

```sh
python3 matching2/tests/sound_stream_service_differential.py
python3 matching2/tests/sound_stream_worker_differential.py
```

The available interpreter is
`matching2/build/lzss-compressor-recovery/venv/bin/python`. Tests freshly compile
Windows x86 COFF, check the retail image hash, and compare original instructions
with candidate execution in Unicorn. They inspect return values, ordered calls,
callback-time state, whole fixture memory, faults, stack cleanup and preserved
registers. Integrated cases execute the maintained restoration helper and the
recovered [cursor/refill bodies](music_cursor_and_stream_refill.md).

One diagnostic deliberately leaves the successful final position query's
output unwritten. It exposed the two distinct retail locals during recovery.
After correction, this Clang frame happens to agree with the zero-initialized
fixture stack, but that is excluded from the 490 passing cases: both routines
read uninitialized storage in that scenario, and different frames/stack history
can change the value. Initial position/status outputs on successful external
calls are otherwise supplied by the fixture; general uninitialized stack
equivalence is not established.

DirectSound, file APIs and message/wait APIs are scripted. The tests do not
establish real Windows scheduling, live audio, arbitrary concurrent mutation,
or exception dispatch. Native MSVC helper ABIs, frames, full-region bytes and
whole-executable gates remain pending. No manifest region was promoted and no
byte gate was relaxed.


## Native service promotion (2026-10-02)

`src/platform/sound_stream_service.cpp` now owns the complete 637-byte native
service extent at 0x0044D850 through 0x0044DACC, including the aligned refill
loop formerly split into a 221-byte assembly continuation at 0x0044D9F0.
`layout/ltcg/sound_stream_service.json` compiles readable C++ with the native
fill, restore, rewind and read helpers to recover their private register ABIs.
The selected function is ordinary two-argument stdcall with RET 8.

The short-read branch follows both the read and silence paths, retaining the
retail loop alignment. Standard intrinsic memset supplies the silence fill.
The retired assembly sources and obsolete three-byte padding owner have been
removed. Incremental `make` verified the entire 487,936-byte EXE exactly.
This native result supersedes the service byte/ABI blockers above; the
separate worker behavioral limitations are unchanged.
