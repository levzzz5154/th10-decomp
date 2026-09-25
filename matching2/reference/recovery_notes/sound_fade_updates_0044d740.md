# DirectSound fade updates at 0x0044D740..0x0044D847

Ghidra identifies four complete functions, with no incoming references at
their entry addresses. Each receives the sound-buffer owner in ECX, checks a
different mode value at offset `+0x1C`, decrements the remaining frame count
at `+0x14`, and clears the mode when that count reaches zero. The duration at
`+0x18` scales the intermediate volume:

| Entry | Mode | Active volume argument | Completion |
| --- | ---: | --- | --- |
| `0x0044D740` | 1 | `remaining * 5000 / duration - 5000` | Stop the first DirectSound buffer; return 1 |
| `0x0044D790` | 2 | `remaining * -5000 / duration` | Return 1 |
| `0x0044D7D0` | 3 | `remaining * -1000 / duration` | Return 1 |
| `0x0044D810` | 4 | `remaining * 1000 / duration - 1000` | Return 1 |

On a mode mismatch or after a nonterminal update, each returns zero. The
active path calls the semantic helper at `0x0044D4E0`, currently named
`SetOperationDeadline`. Its virtual call at offset `+0x3C` is DirectSound
`SetVolume` according to the local Wine `dsound.h` declaration. The
[C++ source](../semantic_candidates/sound_fade_updates_0044d740.cpp)
expresses these state transitions and arithmetic directly; the
[sound-buffer type](../../msvc/include/th10/platform/sound_buffer.hpp) now
names the three fade fields.

The manifest keeps each former assembly body in `previous_record`. The
one-argument fastcall declaration preserves each entry's ECX input, but the
existing volume helper's retail private EAX input still needs a caller-inclusive
LTCG match. No build or byte comparison was run for these four conversions.

**Build status (2026-09-25):** the full byte-verified build showed that this model does not reproduce the retail bytes. The maintained source keeps the exact assembly, and the model is preserved in `reference/semantic_candidates/`.
