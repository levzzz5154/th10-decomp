# Music-command dispatch and sound-effect queue

2026-09-26. Complete readable C++ candidates now cover three retail regions,
with no inline assembly. They remain outside the exact-build manifest.

| Entry | Retail region | Candidate |
| --- | ---: | --- |
| `0x0043DDF0`, process music commands and effects | 1,452 bytes | `sound_commands.cpp` |
| `0x0043DD10`, queue a scaled pan sample | 149 bytes | `sound_effect_queue.cpp` |
| `0x0043DDB0`, queue a stop request | 52 bytes | `sound_effect_queue.cpp` |

The dispatcher region includes its eight-entry jump table and interior
alignment. Its instruction bodies are `0043ddf0–0043de24` and
`0043de30–0043e37a`; the entire manifest interval ends at `0043e39c` exclusive.
The new candidates cover **1,653 retail-region bytes** in total.

Dispatcher tests pass **757 unit comparisons, including 17 faults**, and **83
integrated comparisons, including three faults**. Producer tests pass **444
comparisons, including four faults**, and **28 producer-to-dispatcher
comparisons, including two faults**. This totals **1,312 comparisons**.
Independent assertions check queue compaction, pan averaging, volume values,
fade wrapping, busy-state retention, failed sample counts, handle lifetime,
producer aliases, and a full create–play–shutdown sequence.

## Evidence and shared layout

Evidence is the saved Ghidra C/full instruction exports for `0043DDF0` and
`0043DD10`, the complete maintained 52-byte `0043DDB0` body, related C++
callees, and the retail executable verified against the manifest SHA-256.
A live Ghidra decompile request for `0043DDF0` was rejected with
`MCP tool call requires approval, but approval policy is never`. Saved exports
and original instruction execution provided the available evidence; no
permission workaround was attempted.

`WaveSoundManager` now names twelve pending effect IDs at `+0x620`, twelve
signed sample counts at `+0x650`, and twelve arrays of 128 pan samples at
`+0x680`. The historical `music_handles` name remains a union alias for the
IDs, preserving initialization code. The pan arrays end at `+0x1e80`.
Thirty-two music commands start at `+0x1f88`; each `0x10c`-byte record holds
kind, signed argument, step, and a 256-byte name. These end at cached names
`+0x4108`. Assertions check the layouts; all prior fields retain their offsets.
The DirectSound SetPan slot is now typed at vtable byte offset `0x40`.

After these changes, the 354 initializer comparisons and 30 startup scenarios
with 709 actual WAVE preloads still pass. All 373 cached-launch comparisons
also pass. These regressions are separate from the 1,312 new comparisons.

## Dispatcher boundary and queue removal

The dispatcher has a normal one-manager stdcall boundary, RET 4. It returns
zero immediately when the device-owner pointer at manager `+0x610` is null;
it does not inspect the queued effects in that case. Otherwise its return is
the current first music-command kind. Unknown kinds, including zero, leave
the music queue in place and still allow effect processing.

Completing a command shifts `0x43` words per record, forward, until the next
original zero-kind record or 31 copies. It does not clear the final record of
a completely full queue. Crucially, its traversal pointer advances with this
copy. Command 1 requests another dispatch using that **advanced pointer**, not
the queue head. With two pending commands, it normally reaches the zero-kind
tail and leaves the newly shifted head for the next call. With all 32 slots
occupied, it can dispatch the original last record and then shift outside the
nominal queue. Tests compare the resulting memory, including the adjacent
manager fields; the candidate does not add a bounds guard or repair the tail.

Volatile word copies preserve transfer width, ordering and partial fault state.
Arguments and steps are reread after callbacks where the original does so.
Unsigned step updates wrap, while the stage bounds in command 2 are signed.

## Music commands

| Kind | Behavior |
| ---: | --- |
| 1 | Cache a named track. In cached mode, nonzero step only advances; step zero first stops the worker. Other mode calls cache directly. Cache result is ignored, the record is removed, and dispatch resumes at the advanced tail pointer. |
| 2 | Start/select a track through the staged paths below. |
| 3 | With a stream, step zero stops/rewinds buffers and advances, step one removes the record, other steps advance. Without a stream, remove it. |
| 4 | Staged worker shutdown, described below. |
| 5 | Set fade mode and duration on global stream pointer `0x497798`, if present. Duration is signed argument times float `60.0`, converted to signed 64 bits with the low word retained. Store it to both `+0x14` and `+0x18`, set mode `+0x1c` to one, then remove the record. |
| 6 | When enable byte `0x491d63` equals exactly one, wait for servicing to clear, then stop the first buffer. Remove the record afterward. |
| 7 | Same enable/servicing rule as 6, then resume the first buffer with its saved priority/flags. Remove afterward. |
| 8 | Set stream volume from manager `+0x52c4`, if a stream exists, then remove. |

Commands 6 and 7 read stream `+0x74` before their later null check. A null
stream therefore faults at `0x74` when the enable byte is exactly one.
Nonzero servicing retains the command without advancing it. Other enable
values remove it without invoking the operation.

For command 2, cached mode means bit `0x10` at `0x491d78` is set **and** the
current command argument is nonnegative:

| Step | Cached-mode action |
| ---: | --- |
| 0 | Call cached launch with the argument as slot. Advance only when its result is exactly zero; otherwise remove. |
| 2 | Restart a nonnull stream; a negative result removes the command. A missing stream simply advances. |
| 5 | Cache the first buffer if its array/count permit it, derive repeat from the reader record's nonzero loop end, overwrite the command argument with 0/1, and refill the current stream using that cached buffer. Negative refill removes the command. |
| 7 | Start playback with priority zero/flags one; ignore the result and advance. |
| Other | Advance while signed step is below 20; otherwise remove. |

In file mode, or with a negative argument, a missing stream removes command 2.
Step zero stops/rewinds all buffers. Step one waits while servicing is nonzero;
otherwise it recreates buffers and advances regardless of that result. Step
two resolves either the inline name (negative argument) or indexed cached name,
reloads the metadata table and current reader, and selects the resulting
52-byte record. Selection errors are ignored.

Step three caches the first buffer, calls restart and ignores its result,
reloads the current reader/record, writes repeat 0/1 into the command argument,
and refills the current stream using the cached buffer. Negative refill removes
the record. Step four starts playback, ignoring its result. Other signed steps
below seven advance; the remainder remove the record. Because argument is
overwritten, an originally negative argument can switch routing on the next
call when the cached-mode flag is set. An integrated sequence covers that case.

## Staged shutdown

Command 4 removes itself immediately when no stream exists. Otherwise:

- Step zero stops/rewinds buffers and advances.
- Step one posts message `0x12` to the current thread ID and advances when a
  thread exists; with no thread, it removes the command.
- Step two waits 256 ms. Exactly zero clears the current manager thread field.
  Any other result posts the quit message again and decrements the current
  command step; the common increment then applies, normally leaving step two.
- Step three captures CloseHandle once, closes the current thread and then
  the reloaded event through that same function pointer, caches the current
  stream, clears the thread, invokes its deleting destructor with flag one if
  nonnull, and clears the stream. The final clear also occurs when it was null.
- Step ten removes the command; all other steps advance.

The successful wait has already replaced the thread handle with zero before
step three. The fixture independently asserts **CloseHandle(0)** followed by
the event close. It does not silently restore the original handle. After the
destructor clears the stream, the next dispatch normally removes the command
through the missing-stream check. Callback replacements and changes to the
CloseHandle import are covered.

## Consuming pending effects

Effects run only when byte `0x491d64` is nonzero. Processing stops at the first
negative ID or after twelve entries. An entry's ID is set to `-1` before any
COM call. Its buffer is at manager `+0x208 + id * 4`, the second half of the
shared secondary-buffer array. Lookup is unchecked and uses 32-bit addresses.

A negative sample count requests Stop on a nonnull buffer and clears the
current count **after** that callback. A nonnegative count sums the specified
pan samples with 32-bit wrap, interprets the sum as signed, and divides by the
cached signed count. Division occurs even if the eventual buffer is null;
count zero raises x86 interrupt zero after the ID was consumed. An initially
ordinary local let Clang move this division under the buffer check. A volatile
pan result now keeps the evaluation unconditional in the tested profile.

After successful averaging the count is cleared before buffer lookup. A
nonnull buffer receives Stop, SetCurrentPosition(0), SetPan(average), SetVolume
and Play(0,0,0), with the current buffer reloaded between operations. Their
results are ignored. Global effect-volume zero selects `-10000`. Otherwise
the signed base volume is read from the eight-byte setting table at `0x4749c8`,
and the volume is the low-word/truncated form of:

`(1 - (1 - effect_volume * float32(0.01))^3) * (base_volume + 5000) - 5000`.

The setting's base volume is a signed 16-bit value. The vtable is cached before
the conversion while the receiver is reloaded afterward. Unlike the music
volume helper, this curve is cubic. The literal `0.01` is the retail binary32
value, not exact decimal arithmetic: effect volume 70/base `-1000` yields
`-1109` in the tested extended-precision mode. Pan sum `-7` over three samples
yields `-2`, truncating toward zero.

## Pan and stop producers

The pan producer at `0x43dd10` takes manager in ESI, sound ID in EBX, and a
float stack argument, RET 4. Its explicit candidate uses three stdcall
arguments/RET 12. It loads a signed 16-bit priority from settings `+6`, scales
the float by the binary32 value at `0x470b20` (`5.208333492279053`), converts it
to signed 64 bits and keeps the low word. Input 192 produces sample 1000.

It scans twelve pending IDs, stopping at a match or the first negative ID.
For a match, counts below signed 128 append the sample and increment the
reloaded count; counts at least 128 leave the queue unchanged. Negative counts
are accepted as array indices. Integer address calculations and volatile stores
preserve their aliases: count `-12` in slot zero writes sample 1000 into its
own count field, then reloads/increments it to 1001.

For a free slot, it stores the requested ID, writes its priority at manager
`+0x408 + id * 4`, stores the first sample, and increments the existing count.
It does not reset a stale count. A full queue with no matching ID is unchanged.
The function is void in the saved signature; tests do not treat its incidental,
branch-dependent EAX as an API result.

The stop producer at `0x43ddb0` takes manager in ESI and ID in EDI, plain RET.
The candidate exposes two stdcall arguments/RET 8. It uses the same scan,
inserts the ID only into a free slot, and sets the matching count to `-1`.
Its observed EAX is the chosen slot, or twelve when full; the candidate returns
that value. The paired field is therefore a sample count/stop sentinel, which
resolves the earlier generic key/flag interpretation.

Producer-to-consumer checks include multiple samples per effect, all twelve
slots, stops, disabled effects, missing buffers, infinities and NaNs. A stop
followed by a play for the same pending ID increments count `-1` to zero;
the dispatcher then divides by zero. That retail behavior is retained.

## Floating-point profile and validation boundaries

`sound_effect_support.hpp` shares the setting layout and low-word conversion.
Masked x87 invalid conversions yield integer-indefinite with low word zero;
the C++ helper handles nonfinite/out-of-range values before casting, avoiding
an undefined out-of-range C++ conversion.

The behavioral build uses Clang `-mlong-double-80`. Tests compare 24-, 53- and
64-bit x87 precision and all four rounding directions at 64-bit precision,
including extreme volumes, low-word wrap, subnormals, NaNs and infinities.
The control word is preserved and normal calls leave an empty balanced FPU
stack. They do not claim equality of floating status flags or the partially
live FPU stack at a faulting settings read. Native MSVC evaluation and code
generation still require measurement.

Integrated dispatcher paths execute recovered cached launch, memory factory,
initialization, recreation, restart, refill, music cursors, stream start and
worker stop, plus maintained basename/record selection, aggregation, restoration,
rewinding, first-buffer stop, configured resume and volume helpers. The named
music-cache operation remains scripted at the dispatcher boundary. DirectSound,
Win32, allocators and the deleting destructor are scripted; thread creation
does not schedule concurrent execution. The tests make no live-audio or Windows
exception-dispatch claim.

```sh
python3 matching2/tests/sound_commands_differential.py
python3 matching2/tests/sound_effect_queue_differential.py
```

The local interpreter is
`matching2/build/lzss-compressor-recovery/venv/bin/python`. Both suites freshly
compile their C++ bodies and compare return/control flow, ordered callback
state, memory, allocation/free ledgers, fault address/access width, stack cleanup
and preserved registers. The dispatcher module is 1,840 Clang bytes; the two
producer bodies share a 788-byte module. These are behavioral measurements,
not byte matches. Full-region and whole-executable gates remain required, and
no region was promoted or exactness rule relaxed.
