# MIDI event parser retail audit, 2026-09-30

The native compilation follow-up is recorded in
`midi_event_parser_native_2026_10_06.md`. It preserves exact helper bodies
and all three dispatch byte tables, but the parser remains nonexact. The
no-rebuild restriction and progress counts below describe this older audit.

Reworked the archived ordinary-C++ candidate at
`reference/semantic_candidates/midi_event_runtime.cpp` against fresh Ghidra
disassembly and all three retail dispatch tables. The complete target body is
1323 bytes at 0x0043B110..0x0043B63A. It remains assembly in the live manifest;
the candidate is not a production input or a byte-matching recovery.

Raw retail evidence is retained in
`midi_event_parser_followup_2026-09-30.evidence.json`. Ghidra targets `th10.exe`,
whose backing executable and the local oracle were confirmed in the preceding
tick/volume audit to share SHA-256
`2f14760b6fbbf57549541583283badb9a19a4222b90f0a146d5aa17f01dc9040`.

## Corrections in the candidate

- Note-on and note-off transpose the outgoing note as well as the bitmap index.
  Retail ADD DL at 0x0043B3C3/0x0043B3EE feeds the later packed message at
  0x0043B5EA. Previously the candidate changed only its bitmap calculation.
- The SysEx slot increments with **signed** remainder by 32. Retail's AND
  0x8000001F and negative-result adjustment at 0x0043B267..0x0043B274 implement
  `(index + 1) % 32`, including wrap of the 32-bit increment. They are not an
  unconditional unsigned `& 31` operation.
- The output handle is reloaded between midiOutPrepareHeader and midiOutLongMsg
  (0x0043B219), and the header index is reloaded after external calls. Removed
  cached local values that erased those accesses.
- The parser calls the maintained CompleteMidiHeader and ReadMidiVariableLength
  implementations for SysEx/meta parsing. Removed the large inlined cleanup
  copy and retained the inline variable-length loop only for the final delta,
  where retail also inlines it. Native LTCG must still prove manager EDX /
  header ESI and cursor-address ESI at those boundaries.
- Removed calls to the undeclared `Allmul_00456640` and the replacement 32-step
  limb division. Natural unsigned 64-bit operators express retail's actual
  runtime-helper edges. Both ticks-per-quarter and tempo are sign-extended from
  signed 32-bit values before unsigned arithmetic, as retail CDQ requires.
- Tempo accumulation retains the observed 0x101 multiplier, with unsigned
  arithmetic to preserve retail IMUL/ADD wrap instead of signed overflow.
- Controller 7 converts through signed 64 bits before taking the low word,
  reflecting the EDX:EAX result from 0x00463B2C. No invented float-argument
  prototype is supplied for that x87 helper.
- Packed short messages preserve byte 3 of retail's temporary stack slot.
  Normally this is the high byte of the incoming track pointer at ESP+0x24.
  Controller 7 first overwrites that slot with its zero-extended input at
  0x0043B46E, so its high byte is zero. Retail writes only bytes 1, 0, 2 when
  packing at 0x0043B5EA..0x0043B5F6. The previous candidate always zeroed byte 3.
- The five-word saved loop clock is represented by a named 20-byte layout at
  +0x2EC, with tempo, elapsed ticks, and event base. DWORD packing is required:
  its two 64-bit members begin at relative +4 and +12, not +8 and +16.
- The full local header view is named MidiEventHeader, keeping the canonical
  opaque midihdr_tag and maintained completion helper declaration consistent
  across translation units. A second conflicting midihdr_tag definition is
  not introduced.

Retail dispatch-table decoding confirms two data bytes for 80/90/A0/B0/E0,
one for C0/D0, and the system branch for F0. State updates dispatch 80 to
note-off, 90 to note-on, B0 to controller handling, C0 to program state, and A0
to no state update. Controller destinations are:

| Controller | Retail destination | Operation |
| --- | --- | --- |
| 0 | 0x0043B44B | Bank byte at channel +0x11 |
| 2 | 0x0043B502 | Save tracks and loop clock |
| 4 | 0x0043B56E | Restore tracks and loop clock |
| 7 | 0x0043B461 | Scale/clamp volume, channel +0x15/+0x16 |
| 10 | 0x0043B4EC | Channel +0x12 |
| 91 | 0x0043B4C0 | Channel +0x13 |
| 93 | 0x0043B4D6 | Channel +0x14 |

## Verification and remaining gates

Both this parser candidate and the preceding joint tick/volume candidate pass
Clang's i686 Windows syntax/layout checks with `-Wall -Wextra -fsyntax-only`
and no diagnostics. This emits no object or executable. The original parser
candidate failed that check because Allmul_00456640 had no declaration.

No build or native probe was run, respecting the no-rebuild constraint.
The manifest and production sources were untouched by this audit. Progress
therefore remains 1840 C++ regions / 95847 bytes and 464 assembly regions /
227203 bytes.

Next: co-compile the real tick, parser, volume candidate and canonical helpers
under MSVC native LTCG, preserving each existing production owner and retail
import/runtime address. Measure the entire parser contribution, its three
switch-table outputs, all private ABI handoffs, packing/stack-slot selection,
and x87 scheduling. Syntax checks and semantic repairs do not establish an
exact match; manifest promotion still requires complete byte equality and
whole-executable validation when rebuilding is authorized.
