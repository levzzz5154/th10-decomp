# Music cursor and DirectSound buffer refill

2026-09-26. Complete C++ candidates now cover the 194-byte cursor rewind at
`0x0044DD40`, 202-byte cursor read at `0x0044DE10`, and 483-byte refill at
`0x0044D110`. These candidates contain no inline assembly. They remain outside
the exact-build manifest; the production bodies still preserve retail bytes.

| Candidate | Differential comparisons | Matching memory faults |
| --- | ---: | ---: |
| `music_cursor.cpp` | 473 | 33 |
| `sound_stream_fill.cpp`, scripted cursor results | 177 | 7 |
| Refill with executing cursor bodies | 94 | 2 |
| Complete start/command through PCM refill and Play | 67 | 3 |

The two refill groups also include one bounded no-progress trace each. Those
are deliberately stopped after 16 rewinds and are counted separately from
memory faults. The startup integration executes 55 cursor reads and reaches
57 Play calls. An independent byte assertion checks a 29-byte 8-bit sample,
two bytes of `0x80` silence, and untouched output guards.

## Evidence and layout

The saved Ghidra C and full instruction exports in
`decompiled/ghidra_augmented/functions/0044DD40.*`, `0044DE10.*`, and
`0044D110.*` were checked against the SHA-256-verified original executable.
The fresh Ghidra MCP request was denied by the current approval policy.
This recovery uses the saved exports and executes the original instructions;
it does not claim a successful live Ghidra update.

The refill decompilation omits the restoration loop as unreachable. Its
complete instruction listing contains the GetStatus/Restore/Sleep path.
The earlier description of an incoming byte count or ESI stream argument was
incorrect: EAX holds the stream; the two stack arguments are the DirectSound
buffer and repeat flag. The first stack argument is reused as locked byte
count storage after the buffer pointer is cached.

`sound_wave_types.hpp` now describes the cursor's remaining byte count at
`+8`, buffered flag at `+0x7c`, base/position/relative end at `+0x80/84/88`,
file handle at `+0x8c`, and music record pointer at `+0x90`. The music record
names signed loop start/end offsets at `+0x18/1c`, with WAVEFORMAT at `+0x20`.
The shared stream's reader pointer is typed. Offset/size assertions retain
the previously established manager and record layouts.

## Cursor rewind

Any nonzero buffered flag selects memory mode. Rewind caches the buffer base
and record, resets position to base, and updates relative end only when the
record's signed end is positive. A nonzero low byte of the mode argument and
positive signed loop start move position to base plus start, with 32-bit wrap.
Nonpositive ends retain the prior memory limit.

File mode rejects a null handle before reading metadata. It seeks to file
offset plus the global base (`0x4977a4`), adding loop start only for a nonzero
low mode byte and positive start. SetFilePointer's result is ignored. After
the callback it reloads the current record: remaining bytes become end minus
start for a loop-start seek, or end otherwise. Seek callback mutations to the
record therefore affect remaining length but not the offset already passed.

## Cursor read

Memory mode rejects a null position before touching the optional count output.
It clears that output, then reloads the end/base/position fields; the output
can alias any of them. The clamp uses unsigned, wrapping addresses:
`position + requested > base + relative_end`. Copies run forward in 32-bit
words followed by individual bytes. Afterwards the count is added to the
current stored position, which the copy itself can overwrite. The optional
output is finally assigned the copied length. A zero-length copy does not
validate its destination.

`sound_memory_words.hpp` uses packed volatile words to preserve each x86
transfer's width and order, including unaligned addresses, overlap and
partially completed faults. It intentionally does not substitute memmove or
assume nonoverlapping buffers. These are target-specific 32-bit candidates,
not portable host pointer arithmetic.

File mode first rejects a null handle (`0x800401f0`), then requires both
destination and output count (`0x80070057`). It clamps requested bytes to the
unsigned remaining count and subtracts the request **before** ReadFile.
ReadFile's BOOL and actual short count do not repair that subtraction. The
retail code reuses the destination argument's stack slot as the API's count
output: if the API leaves it unwritten, destination pointer bits become the
returned count. The candidate explicitly initializes that temporary to the
pointer value. Metadata/remaining-count mutations made during the API call
are retained unless the caller's count output subsequently overwrites them.

## Buffer refill

A null buffer returns `0x800401f0` before dereferencing the stream. Negative
GetStatus returns immediately. Lost flag `2` caches Sleep once, then repeats
two Restore calls per iteration: the first result `0x88780096` causes
Sleep(10), and the second must return exactly zero to end the loop.

Lock receives offset zero, current stream buffer size, initialized destination
and byte-count outputs, null second-region outputs, and zero flags. Negative
Lock returns immediately. The original buffer pointer remains cached across
all callbacks, while each subsequent COM operation reloads its vtable.

The initial cursor reset is inlined. Memory mode restores the base position
and positive end; file mode seeks and reloads metadata as above, but a missing
handle skips this initial seek instead of returning early. The following
cursor read supplies that error. The stream's reader is reloaded before
reading, including after a seek callback changes it.

After the first successful read:

- Zero bytes pad the entire locked span, regardless of repeat flag.
- A count at least as large as the locked span proceeds to Unlock.
- A positive short read with repeat disabled pads the tail.
- A positive short read with repeat enabled repeatedly rewinds with mode zero
  and reads the remaining span. Both operations reload the current reader.

Silence is `0x80` only for exactly 8 bits per sample, otherwise zero. Format is
read from the current reader/record at padding time. Stores use forward words
then tail bytes. Negative read/rewind returns leave the buffer locked; retail
has no added cleanup. A zero-progress repeated read has no termination guard.
Success invokes Unlock with the original buffer, destination and locked byte
count, null second region, and returns zero regardless of Unlock's HRESULT.

## Validation and limits

```sh
python3 matching2/tests/music_cursor_differential.py
python3 matching2/tests/sound_stream_fill_differential.py
python3 matching2/tests/sound_stream_start_integration.py
```

The available interpreter is
`matching2/build/lzss-compressor-recovery/venv/bin/python`. Each script checks
the oracle hash and freshly compiles x86 Windows COFF with Clang. Comparisons
include callback-time cursor/stream state, ordered API calls, whole fixture
memory, return values, fault location/access width/value, stack cleanup, and
callee-preserved registers. The integration runs selection, restoration,
rewind, volume, refill and both cursor bodies, optionally through the command
wrapper. It retains real retail floating conversion instructions. Win32,
DirectSound and rand remain scripted external boundaries; there is no claim
of live audio, concurrent mutation safety, or Windows exception handling.

The cursor module occupies 516 Clang bytes including both functions and
alignment; refill occupies 797, versus 396 and 483 retail bytes. Rewind's
candidate uses two stdcall arguments rather than ESI/AL and plain RET. Read
uses four stdcall arguments rather than EAX/EDX plus two stack arguments and
RET 8. Refill uses three stdcall arguments rather than EAX plus two arguments
and RET 8. Native MSVC private ABI, frame, region and whole-executable byte
checks remain pending. No exactness gate or production region was changed.
