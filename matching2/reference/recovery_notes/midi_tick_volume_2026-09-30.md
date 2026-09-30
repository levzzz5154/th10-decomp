# MIDI tick and channel-volume candidate, 2026-09-30

Prepared joint readable C++ for the complete 473-byte tick at 0x0043AF30 and
140-byte volume helper at 0x0043B7A0 in
`reference/semantic_candidates/midi_tick_volume_0043af30.cpp`. This is an
unverified candidate, outside production translation units and the manifest.
No byte-matching credit, build, native probe, or game execution in this step.

## Retail evidence and corrected interpretation

Live Ghidra MCP inspection targeted the open `th10.exe` program. Its backing
executable and `matching2/build/oracle/th10.exe` both have SHA-256
`2f14760b6fbbf57549541583283badb9a19a4222b90f0a146d5aa17f01dc9040`.
Disassembly of tick, volume helper, and float conversion helper plus raw
constant reads are retained in `midi_tick_volume_2026-09-30.evidence.json`.

- 0x00470AFC contains `00 00 80 3F`: 1.0f.
- 0x00470BF4 contains `00 00 00 43`: **128.0f**. The older tick blocker note
  incorrectly reported 0.01f and has been corrected. The fade step is a
  quantized level scaled by 128.
- Tick calls volume at 0x0043AFDE with receiver EDI and stack adjustment zero;
  volume returns with RET 4. Ghidra reports tick as its only direct caller.
- The volume helper walks requested volumes at +0x169, stride 0x17, for 16
  channels. +0x2D4 suppresses the entire operation; +0x13C holds the output
  handle. Its scaled integer plus adjustment is clamped to [0,127].
- The helper reuses its incoming argument's stack slot for the message, writing
  bytes 0, 2, then 1, and preserving byte 3. A simple zero-initialized packed
  message would lose that behavior for nonzero high-byte adjustments. It does
  not update each channel's saved applied-volume field.
- Both divisions in tick sign-extend ticks-per-quarter and tempo with CDQ
  before unsigned 64-bit operations. Track next-event time is also sign-extended
  before an unsigned comparison with the computed event time.
- Retail uses FST, not FSTP, for the first fade-level store. The first conversion
  uses the retained x87 result; after the conditional volume call the second
  conversion reloads the stored float. It must not be collapsed into one
  cached integer conversion.
- ProcessMidiEvent at 0x0043B110 takes sequencer and track on the stack and
  returns with RET 8, as also documented by the existing
  `reference/semantic_candidates/midi_event_runtime.cpp` candidate. The older
  tick note's cdecl description has been corrected.

The private conversion helper at 0x00463B2C consumes x87 ST(0) and returns
EDX:EAX. The candidate uses a compiler float-to-__int64 conversion and then
takes its low word. It does not invent a conventional float-argument prototype
for this helper. The eventual native probe must prove that the compiler selects
the actual helper and retains the retail x87 evaluation and rounding behavior.

## Layout and verification

Candidate overlays document the additional volume and fade fields without
altering the maintained sequencer type. The canonical type ends its last field
at +0x2E4 but is padded to +0x2E8 for its 64-bit members. A composition that
appended fade fields failed the initial layout assertions; the retained overlay
places duration at +0x2E4 and position at +0x2E8.

Syntax and 32-bit Windows layout assertions pass with:

```
clang++ --target=i686-pc-windows-msvc -fms-extensions -fsyntax-only \
  -I matching2/msvc/include \
  matching2/reference/semantic_candidates/midi_tick_volume_0043af30.cpp
```

This check generates no object or executable and proves no MSVC byte match.
`git diff --check` passes. Manifest progress remains 1840 C++ regions / 95847
bytes and 464 assembly regions / 227203 bytes.

## Next acceptance gates

Probe both real bodies jointly under native MSVC /GL and /LTCG, with tick rooted
through its public ECX receiver boundary and volume private so the compiler can
derive the EDI receiver / stack adjustment / RET 4 boundary. Bind the typed
`IatTickMidiOutShortMsg` at 0x00466298; bind compiler-generated runtime multiply,
unsigned divide, and float-conversion calls to their canonical existing owners.
Retain ProcessMidiEvent's actual stack ABI and the canonical ResetTracks body
as a separately owned dependency. Compiler-only contexts receive zero credit.

Measure complete extents, loop alignment, calls, and all bytes; especially the
volume argument-slot reuse, clamp branch shape, x87 scheduling, and the tick's
live track-table reloads after ProcessMidiEvent. Only after both regions are
exact may their complete manifest records be promoted. Whole-image validation
remains required for a production landing when rebuilding is authorized.
