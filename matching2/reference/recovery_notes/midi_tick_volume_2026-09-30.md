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


## Native channel-volume promotion (2026-10-02)

`src/platform/midi_channel_volumes.cpp` reproduces all 140 bytes at
0x0043B7A0 under the `midi_channel_volume` native LTCG cluster. The compiler
chooses the retail EDI receiver and stack adjustment, emits the same x87
FILD/FMUL sequence and float-to-64-bit helper call at 0x00463B2C, and retains
the sixteen-channel loop and signed clamp. The status is computed before the
conversion, preserving the retail temporary and instruction schedule.

The three-byte message is left with an uninitialized fourth byte. Native MSVC
reuses the incoming adjustment slot for this local, exactly preserving that
argument's high byte in the emitted instructions. Explicitly addressing the
argument instead caused MSVC to pass the receiver on the stack and failed
the byte gate; it was rejected. Layout assertions cover the channel stride,
output handle, channel array, fade scale and suppression flag.

Incremental `make` verified the entire 487,936-byte EXE exactly after promotion:
2,046 ordinary C++ regions / 125,749 bytes; 274 assembly regions / 197,382 bytes.
The obsolete assembly owner was removed. Tick remains a separate recovery
task; this result supersedes only the channel-volume blockers above.


## Native tick follow-up (2026-10-02)

The snapshot in `semantic_candidates/midi_tick_native/` mirrors the MSVC
source/layout tree and reproduces a 473-byte tick with 466 matching bytes.
All bytes outside 0x0043B031..0x0043B03B match, including the public ECX
receiver, fade calculation and conversion sequence, runtime arithmetic calls,
callback-time track-table reloads, loop alignment, and both return paths.
The companion volume helper still matches all 140 bytes in this cluster.
Native evidence is under `matching2/build/probes/midi_tick/`.

The remaining block is twelve bytes long in both images. Retail uses:
`mov eax,[edi+138h]; lea ecx,[eax+ebp]; mov eax,[ecx+4]`.
The candidate uses:
`mov ecx,[edi+138h]; mov eax,[ecx+ebp+4]; add ecx,ebp`.
Seven bytes differ within those equivalent address/load sequences.
Pointer/reference forms, volatile next-event reads, explicit unsigned address
arithmetic, and a reference spelling of the event-parser argument did not
resolve the difference. Production retains its verified assembly tick owner.

Initializing the active-track flag before event-time calculation recovered
the retail early zero register and local lifetime. Inverting the fade-duration
condition recovered the out-of-line completed-fade return. Reading the track
table through a volatile pointer view at each decision recovered the 473-byte
extent and retail reload/loop structure; a per-iteration track pointer is shared
by the time comparison and event-parser call. No instruction rewriting, inline
assembly, relocation masking, or oracle-byte inclusion was used.


A further native retry on 2026-10-02 moved the due-event comparison/call into
a force-inlined helper; it retained the same seven-byte mismatch. Rewriting
the inner do/while as a while loop changed the extent/layout and failed the
native gate. The existing 466/473-byte snapshot remains the preferred candidate.
