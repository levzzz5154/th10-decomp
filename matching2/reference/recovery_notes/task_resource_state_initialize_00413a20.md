# Task resource state initializer at `0x00413A20`

## Current source recovery

`matching2/msvc/src/game/score_tasks.cpp` now expresses this entry as a
readable C++ state update. It loads the cached resource selected by the stage
asset table, consumes the optional preloaded archive buffer or loads the
selected path through `Archive_LoadFile`, initializes the observed fields, and
logs either load failure. The receiver layout is intentionally limited to the
offsets touched by this body; the field meanings remain open.

The existing C-linkage entry spelling is retained for assembly callers. The
shared declaration now uses `int __stdcall asm_FUN_00413a20_00413a20(void*)`,
and the semantic manifest row uses its emitted `_asm_FUN_00413a20_00413a20@4`
symbol. The direct callers are `0x00413980` (call at `0x004139B6`) and
`0x00417870` (call at `0x00417B07`); both pass the state pointer on the stack
and inspect the integer result in EAX.

## Live Ghidra evidence

The open program was `th10.exe`, x86 little-endian, 32-bit. Ghidra reports
`undefined4 __stdcall FUN_00413a20(int param_1)`, entry `0x00413A20`, body
`0x00413A20..0x00413B40`. `disassemble_bytes` returned 289 bytes and 81
instructions across that inclusive range. The direct call xrefs are the two
call sites listed above.

The first dependency is `0x00447280`, decompiled as
`int* __fastcall FUN_00447280(int, int, char*)`. At `0x00413A34..0x00413A3A`,
the entry pushes the stage asset's `+0x20` string, sets ECX to `0x1C`, and calls
it with the resource-owner pointer already in EDX. Its source-level semantic
implementation is `Recovery_LoadCachedResource` in
`matching2/msvc/src/game/recovery_leaves.cpp`.

When no preloaded buffer exists, the body clears `0x00497C38`, copies the
string at `stageAssetTable + 0x18 + 4 * data_00474C68`, and calls `0x0044B360`
at `0x00413B12`. Ghidra decompiles that helper as an archive-or-disk file load
and identifies the filename as an incoming EAX value. The call site sets EAX
to `0x00497C38` and pushes two zero arguments. The shared
`th10/platform/archive_file.hpp` declaration documents this native-LTCG
register convention and says callers must share the loader's optimization
scope. The converted C++ uses that semantic API; exact emitted call shape has
not been verified.

The failure logger at `0x0044B810` is decompiled as a `__thiscall` variadic
append method and has a semantic implementation in
`matching2/msvc/src/platform/text_log.cpp`. The conversion calls the method
with the same log object and format-string addresses used by the retail body.

After successful loading, the retail instructions initialize fields at
`+0x9E60`, `+0x9E64`, `+0x9E68`, `+0x9E6C`, `+0x9E70`, `+0x9E78`, `+0x9EC0`, and
`+0x9EC4`; the archive and cached-resource pointers are stored at `+0x9EBC`
and `+0x9E80`. The C++ source preserves these offsets and the conditional flag
behavior without assigning unverified field names.

The previous source comment recorded a 13/289-byte candidate match with its
first difference at `0x00413A26`, attributed to the private cached-resource /
string-copy call shape and local layout. The source now uses the recovered
semantic helper declarations, but the archive loader retains a native-LTCG
register convention. No build, probe, or test was run for this conversion, so
the semantic entry and exact emitted call shape remain unverified against the
retail bytes.
