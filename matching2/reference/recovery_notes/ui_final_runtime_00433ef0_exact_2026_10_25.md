# Music room 0x00433EF0: byte-exact (2026-10-25)

The 2,796-byte music room (`TitleMusicRoom`, `src/game/title/ui_final_runtime.cpp`)
is selected by `build_support/layout/ltcg/title_music_room.json`. Its
equivalent layout, the asm owner `build_support/exact/game/title/ui_final_runtime.cpp`
and the equivalent-only context `ui_final_stage_text.cpp` are removed.

## The last byte

The one remaining difference was the base/index order of
`recovery_music_player[0x1D892 + room->displayed_track]` in the confirm path
(retail `[ecx+edx+0x1d892]`, model `[edx+ecx+0x1d892]`). Traced with a
SymAlloc/`HshInsertEntry` tracer on the model link:

- the late `OptCmpHashVal` sort compares the load `[t+0x690]` (hash
  `8 + ((t & 3) << 14)`, `t` the address temporary) with the global pointer
  leaf `recovery_music_player` (`36 << 5 = 0x480`);
- `t` is the global optimizer's hash variable for `room + 0x690`
  (`SymMakeHashVar` from `HshInsertEntry`, called from `TupMakeHshSym`). The
  pass numbers one hash variable per new expression while it walks case 0's
  first-frame block in source order; `&room->displayed_track` is first met at
  the `room->displayed_track = 0` store and got id 880 (class 0), so the load
  sorted after the global.

Any equivalent spelling earlier in that walk that changes the number of new
expressions by a non-multiple of four flips it. Assigning the loaded comment
file to the room first and reading the cursor back from it does:

```cpp
room->file_buffer = Archive_LoadFile(recovery_music_comment_file, &remaining, 0);
char* text = room->file_buffer;
if (text == 0)
    goto leave_room;
```

(`if (room->file_buffer == 0)` with the old order also closes it.) Neither
unused padding (1–96 dead `const` declarations), nor 18 named predicates and
locals, nor seven spellings of the inlined cursor clamp moved the id: they fold
before this pass. Reordering the three first-frame stores flips the id too but
moves the stores.

## The cluster

`title_music_room.json` keeps the exact input order of the equivalence
measurement: the music room source (driver), the stage-text extract/skip
sources, the AnimationManager9 register body, the stand-ins
(`title_music_room_dependencies/03_stand_ins.cpp`: `UiFinalExtractLine`,
`UiFinalFind`, `UiFinalTransition`, now with their retail sections), then the
difficulty-select cluster's driver and dependencies as wrappers. The donor
bodies that sit at the addresses the music room calls (the old music-room
draft, the skip/extract line readers, the transition setup, the resource queue
registrar, the lookup Find/Validate) stay in the link but are parked at
0x00401000+ through new `TH10_MUSIC_*_SECTION` / `TH10_LOOKUP_*_SECTION`
macros in the two shared anchor files (defaults unchanged). The four float
literals the body reads are bound at retail's pool addresses (three
`constant_aliases`, one double as a data alias).

Generator and helpers: `build/experiments/goal_2026_10_25/promote_ui_final.py`,
`build_cluster_fix.py` (fills `headers`/`included_sources` from the compiler
log), `promote_regions.py` (textual regions.json cutover).

## Validation

`make` (byte-exact C++ 83.8% -> 84.7%), `make EXACT=1` (SHA-256
`2f14760b6fbbf575…`), `callsite_abi.py` (0 failures), 127 tool unit tests,
`git diff --check`.

The LLVM/Clang 23 upgrade of 2026-10-21 had invalidated the tool pins of the
three GNU/Clang compiler profiles (`layout/compiler/*.json`); the pins now name
the installed binaries and every region they compile still matches retail.
