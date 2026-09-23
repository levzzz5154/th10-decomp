# MIDI event parser recovery at `0x0043B110`

## Result

`matching2/msvc/src/platform/midi_event_runtime.cpp` now contains a readable
stdcall C++ implementation named `ProcessMidiEvent_0043B110`. The body has no
inline assembly. It parses
running-status channel messages, applies note
and controller state, emits short messages, sends system-exclusive buffers,
updates tempo timing, handles end-of-track, and advances the track by its
next variable-length delta.

The function uses the existing `MidiSequencer` and `MidiTrack` layouts.  The
MIDI header's 0x40-byte Win32 layout is defined locally because the shared
header intentionally keeps that type opaque.  Header ownership cleanup is
implemented in the body rather than calling `0x0043AEB0`, whose retail entry
uses a private ESI/EDX ABI.  Variable-length reads are also local rather than
calling `0x0043A730`, which receives its cursor in ESI.

## Live Ghidra evidence

The live Ghidra project `th10` / `th10.exe` reports `0x0043B110..0x0043B63A`
as `FUN_0043b110`, with a stack `__stdcall` signature taking two pointers and
an epilogue `ret 8`.  Its only caller is `FUN_0043af30`; the caller pushes the
track first and the sequencer second, then calls this entry.  That caller's
sequencer and track offsets agree with the checked `MidiSequencer` and
`MidiTrack` layout assertions.

The live decompilation and disassembly show:

* A status byte below `0x80` reuses the track's byte at `+0x0c`; otherwise the
  parser consumes a new status byte.  Channel voice messages consume one or
  two data bytes according to status.
* `0x90` and `0x80` update the per-channel note bitmap at
  `sequencer+0x154+channel*0x17`, applying the signed transpose byte at
  `+0x2c4`.  Controller messages update channel bytes and controller 2/4
  save and restore the track cursors, pending times, and five-word clock
  snapshot.
* Controller 7 multiplies its value by the float at `+0x2c8`, converts to an
  integer, clamps it to MIDI's 0..127 range, stores it at channel offset
  `+0x16a`, and replaces the outgoing value with the clamped result.
* `0xF0` allocates a 0x40-byte `MIDIHDR` plus a length-prefixed payload and
  submits it through the import slots at `0x004662A0` and `0x0046629C`.
  `0xFF 0x2F` clears the track's active field and returns early.  Meta `Q`
  advances the event tick base using the old tempo, clears elapsed ticks, and
  accumulates the new tempo bytes with the observed `0x101` multiplier.
* Other processed channel messages are packed as status/data1/data2 and sent
  through `0x00466298`.  The parser stores running status and adds the next
  variable-length delta to `track+0x04`.

The private helper behavior was checked directly: `0x0043AEB0` scans all 32
header slots, calls the unprepare import at `0x00466284`, and frees the payload
and header; `0x0043A730` reads a MIDI variable-length integer from the ESI
cursor.  The C++ body reproduces those operations through ordinary typed
code.  Its tick multiplication calls the already typed `Allmul_00456640`;
its local limb division avoids a new compiler-private `__aulldiv` dependency.

## Region integration

The source entry signature at `0x0043B110` is:

```cpp
extern "C" void __stdcall ProcessMidiEvent_0043B110(
    MidiSequencer* sequencer, MidiTrack* track);
```

On Win32 MSVC, this emits `_ProcessMidiEvent_0043B110@8`. The shared
declaration records the two pointer arguments and stdcall cleanup, and the
assembly caller now names that entry. The manifest binds the decorated symbol
at `0x0043B110`, promotes all 1323 bytes to a semantic region, and retains the
prior assembly record. The body was not built, probed, or tested, so exact-code
equivalence is not claimed.
