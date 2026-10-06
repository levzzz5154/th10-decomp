# WAVE loader 0x0043D390: byte-exact C++ promotion

The complete 684-byte WAVE loader now comes from
`msvc/src/platform/sound_wave_load_0043d390.cpp` under the native
`layout/ltcg/sound_wave_load.json` cluster. The assembly owner and its equivalent
source, header and layout were removed. The former equivalent recovery is now
ordinary byte-exact C++ in both build modes.

The two-byte residual was the encoding of the RIFF length adjustment:
retail uses `ADD EBP,-12`, while modifying the local with `chunk_bytes -= 12`
made MSVC emit `SUB EBP,12`. Keeping the stored length unchanged and passing
`chunk_bytes - 12` to both `FindWaveChunk` calls gives the retail encoding.
This preserves unsigned wraparound and the retail's full-header subtraction,
including malformed lengths. No volatile read, barrier, assembly, compiler
flag change, byte rewriting or relaxed comparison was added.

The cluster retains the complete chunk walker and text-log implementations as
compiler context at their retail addresses. Only the loader is selected. Its
public fastcall boundary remains index ECX, manager EDX, filename on the stack,
and `RET 4`. The raw native function and normalized contribution both match
retail, including all calls and absolute references. The new header is the
prior loader type model, moved into the maintained include tree.

Validation on 2026-10-06:

- Strict scratch native probe: all 684 bytes EXACT.
- Strict maintained-source probe after making the length local const: EXACT.
- `sound_wave_load_differential.py --native`: 396 comparisons passed, including
  eight matching faults. The fixture now builds the strict native cluster and
  requires full byte equality before executing its loader with the real retail
  chunk walker and CRT helpers. DirectSound, Sleep, logging and free remain
  scripted; this is not a live audio test. The old `--native-equivalent` spelling
  is accepted as an alias for the byte-exact native mode.
- `make EXACT=1`: all 487,936 executable bytes exact.
- `make`: whole-image gate passed; eight other equivalent regions remain.
- `git diff --check`: passed.

Measurement sources and compiler images are retained under
`matching2/build/experiments/sound_wave_exact_2026_10_06/`. The early arithmetic
spelling controls still differed in the original two bytes; pointer-distance
forms changed other instructions. `helper_offset.cpp` is the first fully equal
relocated candidate; the integrated strict probe is stronger fixed-address and
complete-contribution evidence.

Progress after this promotion: 2,244 ordinary C++ regions / 189,163 bytes;
8 equivalent regions / 33,176 bytes; 70 remaining assembly regions / 99,144 bytes.
The full readable, byte-exact, assembly-free objective remains incomplete.
