# Music command queue 0x0043DDF0 (1,452 bytes) — exact ordinary C++

Source: `msvc/src/platform/sound_music_commands.cpp` (`WaveSoundManager::ProcessCommands`).
Cluster: `msvc/layout/ltcg/sound_music_commands_0043ddf0.json`, with the real bodies of every
routine the handler drives as unselected anchors (wrappers in `sound_music_commands_dependencies/`).

What decided the bytes:

- 0x497798 / 0x497858 are fields of the global sound manager (`music_stream`, `volume_b`) and
  0x491D64 is `g_supervisor.effect_mode`. As lone externs they were hoisted as constants.
- Case order in source is 8, 1, 2, 4, 3, 5, 6, 7. The natural order changes block layout and the
  scratch-register rotation.
- The outer loop is a `goto top` loop. Only that form gives the `jmp` + padded aligned label;
  `do/while`, `for(;;)` and `while` do not.
- `advance:` is one shared label. A per-site `++step; goto done` changes the whole function.
- Case 2 writes the streamed half first; each `if (SoundStreamFill(...) >= 0) goto advance;` is
  followed by its own `break;`, which keeps the fill tail in the cached half.
- The cached half's step 7 jumps to the streamed half's step-4 start (`goto start_stream`). Two
  textual copies of the call are tail-merged, and c2 then keeps the cached-half copy, which sits
  in the wrong place. One block with two entries is the only form found that places it after the
  record select.
- The pending-effects loop divides by the memory count (`total / pending_pan_count[i]`) and then
  clears it; the early `if (!g_supervisor.effect_mode) return first->kind;` precedes it.
- SoundStreamStart needs FindAvailable (0x44D370), Run (0x44D300) and Query (0x44D600) as real
  bodies, and SoundStreamFill needs ArchiveRewind/ArchiveRead, or the anchors come out at the
  wrong size and shift everything after them.

Cluster technique: a wrapper TU moves a maintained source into another section without copying
it: `#define code_seg(name) code_seg(".text$a03f")` before the `#include` (MSVC macro-expands the
pragma). Sources that nest further sources with their own section names are included unrenamed and
the other names are fitted around them.

Tail-merge rule seen in c2 (`FgTryCommonTailMerge` / `FgDoCommonTailMerge`): of two identical
blocks jumping to one label, the one whose jump is earlier in the label's branch list survives;
the list is prepend-ordered and re-filled when earlier merges retarget jumps, so source order of
the copies does not pick the survivor.

Verified 2026-10-04: `make -j2` and `make EXACT=1 -j2` both pass. Ordinary C++ 2,198 regions /
165,094 bytes; assembly 120 regions / 124,494 bytes; recovered 61.2% of bytes, 94.8% of regions;
byte-exact alone 51.4%.
