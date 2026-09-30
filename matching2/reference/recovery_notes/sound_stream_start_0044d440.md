# Sound-stream start and buffer selection

2026-09-26. `semantic_candidates/sound_stream_start.cpp` recovers the complete
145-byte start routine at `0x0044D440`. The 44-byte command wrapper is in
`unassigned_0043da80.cpp`. They pass **222 individual comparisons with one
matching fault** and **73 integrated comparisons with two matching faults**.
Production remains assembly. A separately tested selector candidate at
`sound_stream_select.cpp` explicitly sequences a callback-sensitive reload
that the maintained source leaves dependent on compiler evaluation order.

## Evidence and corrected meaning

Saved Ghidra C and full instruction listings for `0044D440`, `0044D300` and
`0044D370`, maintained helper source and verified retail bytes establish the
behavior. The fresh Ghidra MCP request was rejected by the session's approval
policy. Ghidra's high-level output and earlier notes misinterpret the incoming
ECX as an interface context: the initial PUSH ECX allocates a local word. The
restore helper receives its address in EBX, writes zero before querying the
nonnull selected buffer, and writes one after restoration. The start routine
tests that output, not an inherited context. Tests vary initial ECX independently
of status/restoration and preserve the resulting behavior.

The receiver is a DirectSound music-stream object, not a MIDI output interface.
The shared candidate types now use `SoundStream`, music thread/stream names and
`Sound_StopMusicWorker_0043dab0`; legacy filenames/production symbols retain
their historical names. The known stream prefix describes buffer array at
4, buffer byte count at 8, reader at 12, count at 16, fade fields at 20/24/28,
priority/flags at 32/36, an unclassified field at 44, and playing at 48.

Two maintained helpers also had generic names obscuring their operations:
`Query` at `0x44D600` calls SetCurrentPosition(buffer, 0) on every buffer and ORs
the HRESULTs. `SetOperationDeadline` at `0x44D4E0` calls SetVolume on the first
buffer, using the global volume curve or -10000 when that global is zero.
Their source comments now identify the actual COM operations without changing
the matched source symbols or bodies.

## Start behavior

An absent buffer array returns `0x800401F0`. Selection returning null yields
`0x80004005`. Otherwise the chosen buffer is cached across every later callback.
The restoration helper's negative HRESULT returns immediately. A nonzero
restored output causes a full refill with loop argument zero; refill failure
also returns immediately. After a successful refill, every buffer is rewound;
that helper's result is ignored. Without restoration, refill and rewind are
skipped even when initial ECX was nonzero.

Start then zeros fade mode/remaining/duration and calls volume setup with zero.
Its return value is ignored. After that callback it writes playing=1, the
supplied priority/flags, and zero to the field at `0x2c`. Finally it invokes
the cached buffer's current Play method with `(buffer, 0, priority, flags)` and
returns its HRESULT. Negative Play does not undo the playing flag or stored
parameters. Replaced arrays affect rewind and volume targets; the Play receiver
remains the selected buffer. A callback can also replace that buffer's vtable.

The [command wrapper](sound_stream_start_status_0043da80.md) calls start with
priority 0 and flags 1, maps missing stream/negative status to -1, and publishes
its full 32-bit command only after nonnegative status. No inherited ECX argument
or function-pointer ABI cast is needed by its semantic contract.

## Selection and sequencing gap

The selector walks current array/count state, skipping null entries. Each
nonnull entry gets a zero-initialized GetStatus output; its HRESULT is ignored.
The first status without playing flag `0x1` selects that slot. The return rereads the array,
so changes during status callbacks can affect the returned pointer.

When no idle entry exists, retail calls rand, then reloads count for unsigned
modulo and reloads the array for selection. The maintained expression
`entries_004[(unsigned int)asm_rand_0045371b() % count_010]` permits Clang to
cache the array before the call. A test changes the array in the rand callback:
retail selects from the new array; this Clang build of the maintained source
selects from the old array. Final stream fields agree but Run and Play target
different buffers.

The new typed candidate stores rand's result in a separate statement before
the count/array reads. It passes that callback case. The test also separately
compiles the maintained selector and reproduces the specific gap; it does not
silently treat its differing trace as a successful retail comparison. Native
MSVC may choose the matched retail evaluation order for the existing source,
so the production body is retained until native evidence supports a change.

Zero count retains retail's divide-by-zero fault after rand. Null selected
fallback entries return the missing-buffer HRESULT. Volume always targets
the current first array element; a valid selected later element does not guard
against a null first element, which faults during volume setup.

## Validation and native boundaries

```sh
python3 matching2/tests/sound_stream_start_differential.py
```

The local interpreter is `matching2/build/lzss-compressor-recovery/venv/bin/python`.
Fresh native Clang modules are executed in Unicorn against original bytes.
The start and command candidates occupy 160 and 54 bytes, compared with 145
and 44 in retail. Their explicit stdcall entries differ from the original
EAX stream plus two stack arguments/RET 8 and ESI manager plus command/RET 4.
The selector's candidate receiver is ECX; retail uses EDI.

Integrated cases run the new selector and freshly compiled maintained Restore,
Rewind and Volume bodies. Bindings account for member helper ABIs; retail's
Run uses ESI buffer/EBX output, Rewind uses EDI and Volume uses EAX. They are
not claimed recovered by the fixture's ordinary thiscall interfaces. The
test-only COFF loader now supports code_seg `.text$` sections and their long
section names, retaining constant data and relocations for these helpers.
The maintained Run source intentionally checks null this; the fixture disables
null-check deletion, and the tested start path calls it only after selecting
a nonnull buffer.

Coverage includes early returns, HRESULT signs, raw priority/flags/commands,
restored versus existing data, callback mutations, Play failures, idle versus
random selection, null slots, empty arrays, and varied global volume settings.
Restoration cases preserve two Restore calls per loop, Sleep(10) on the first
call's `0x88780096`, and the cached Sleep import after a callback changes it.
Comparisons inspect full stream/manager/object memory, ordered calls and
callback-time state, results, memory/division faults, stack cleanup and
preserved registers. The actual retail floating-to-integer helper executes
for compiled volume calculations.

Refill at `0x44D110` remains scripted in this original suite. The separate
`sound_stream_start_integration.py` now executes its recovered body and both
music cursors: 67 comparisons, 55 cursor reads and 57 Play calls, with three
matching faults and an independent PCM padding assertion. See
[cursor/refill recovery](music_cursor_and_stream_refill.md). DirectSound, rand
and Sleep remain boundary collaborators; this is not live audio validation.
Native MSVC private ABI/frame/bytes, general concurrency and Windows
exception dispatch remain unverified. Existing initialization, WAVE, cache,
shutdown and archive-to-shutdown tests validate the shared-type changes;
the parser regression checks the extended COFF loader. No production region
or whole-executable gate was relaxed.
