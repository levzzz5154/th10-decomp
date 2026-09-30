# Runtime library sections linked from the toolkit, 2026-09-28

**Result:** 320 runtime-library functions (66,092 bytes) that were inline-assembly
transcriptions are now linked from the toolkit's own library objects. The whole
487,936-byte executable stays exact. Assembly fell from 1,106 regions /
305,284 bytes to 650 / 239,713; 20 small regions (197 bytes) that earlier
sessions had rewritten as C++ runtime helpers were absorbed into the library
sections that contain them. Six regions of pure INT3 fill (41 bytes) that were
classified as assembly are now padding.

## Why this is the source

`remaining_work_split_2026_09_19.md` measured that the CRT block from
`0x00452493` is byte-identical, outside relocation fields, to members of the
libraries shipped with the project's MSVC 13.10.6030 toolkit, and left open
whether to rebuild those regions from library code. The retail linker copied
each of these functions from one `/Gy` section of one library member. Linking
that same section at the same address is what the original build did; a
hand-written imitation of `memcpy` or `_setlocale` would be neither more
readable nor more faithful.

## Mechanism

* `regions.json` region kind `library`, with translation unit
  `lib/<library>/<member>` (for example
  `lib/libcmt.lib/build/intel/mt_obj/xtoa.obj`). `library_section_number` and
  `library_entry` record which section and which defining symbol.
* `build_msvc.py` extracts the member from `<toolkit>/lib/<library>` in place of
  compiling, then normalizes it exactly as a compiled unit. No byte is changed.
* Relocation targets are bound through the existing `symbols` table. Statics the
  section reaches in a section that is not linked, and runtime names the
  manifest had already bound to another address (for example a signature-matched
  name on a sibling copy), are aliased per unit through `coff_aliases` to a
  unique `_crt_<library>_<member>_<name>` spelling.
* `coff_regions.py` now ignores `.bf`/`.ef` line-number symbols, accepts `.bss`
  sections without file data, and resolves a region symbol through the unit's
  aliases.

## Adoption rules (`tools/waves/adopt_crt_library.py`)

A section is adopted only when it equals retail outside its relocation fields,
exactly covers consecutive manifest regions including at least one assembly
region, every relocation target it implies agrees with the manifest and with
every other adopted section, it is placed at most once, and any static it reaches
in another section of the same member is that section's placement. Identical
bodies are disambiguated by the other sections' relocations: `memmove.obj` is at
`0x00453280` and `memcpy.obj` at `0x0045BFC0`, and `a_cmp.obj`'s private
`strncnt` is the copy at `0x00461ADD`, not `a_map.obj`'s. The tool reads the
retail executable only to derive these addresses; the build does not.

## What is left in the runtime block

About 3.8 KB of runtime assembly remains. Those functions either start inside a
library section whose other functions the manifest splits differently, or do not
occur in these libraries at all. The 107 `.text$x` unwind funclets at
`0x00465xxx` belong to game functions and are recovered with them.

## Entryless-section follow-up

`libcmt.lib/build/intel/mt_obj/exsup3.obj` supplies one 265-byte `.text`
section at `0x00454C08`: an eight-byte prefix, `__except_handler3` at +8,
and `__seh_longjmp_unwind@4` at +238. The 241 bytes outside its six REL32
fields match retail; every relocation resolves to the retail runtime target.
The original scanner found this overlay but skipped it because no function
symbol starts at section offset zero. The manifest selects the COFF static
`.text` symbol through a section-base alias instead, with no emitted code
rewritten. A focused probe verified the complete section; the full `make`
verified all 487,936 executable bytes. Current totals after this adoption
and the separate global-draw adapter conversion are 321 library regions /
66,357 bytes and 528 remaining inline-assembly regions / 232,292 bytes.
