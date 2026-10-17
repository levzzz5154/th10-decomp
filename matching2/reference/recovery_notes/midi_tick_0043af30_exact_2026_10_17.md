# Midi tick 0x0043AF30: byte-exact (2026-10-17)

Follows `midi_tick_equivalent_2026_10_05.md`. The last recorded `code-shape`
hunk is gone: the 473-byte tick callback is selected by the LTCG cluster
`msvc/build_support/layout/ltcg/midi_tick_0043af30.json` from
`src/core/midilib/midi_tick.cpp`, and the assembly region and the equivalent
layout are removed.

## The last residual (143 -> 146 of 146)

Retail keeps the track element pointer as a named value
(`mov eax,[edi+0x138]; lea ecx,[eax+ebp]; mov eax,[ecx+4]`); the model folded
the field load into `[ecx+ebp+4]` and materialised the pointer after it.
Writing the element pointer at the use as `T* p = &arr[i]` reproduces retail's
order:

```cpp
MidiTrack* table = reinterpret_cast<MidiTrack* volatile&>(sequencer.tracks);
MidiTrack* track = &table[index];
```

applied only to the do-loop's track decision; the helper's other two uses
(the `active` checks) keep the forwarded form. Changing the shared
`CurrentTrack` helper instead moves all three uses and loses four other
instructions. All 146 instructions and all 473 bytes are exact.

## Promotion

The cluster compiles the tick with its reset and channel-volume bodies as
anchors at their retail addresses and the method-pointer context as the link
entry. The escaping `MidiTickEntry` method pointer is what keeps Tick's public
ECX receiver boundary, so the context block moved from the source into the
driver; the pointer is read-only after construction and lives in `.rdata`
through `#pragma data_seg`, which the cluster's section check accepts (only
`.text` and `.rdata` contributions are allowed). `make EXACT=1` is unchanged.
