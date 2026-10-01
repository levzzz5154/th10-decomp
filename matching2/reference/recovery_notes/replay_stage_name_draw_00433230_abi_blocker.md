# Replay stage and name-entry draw (`0x00433230`)

## Audit result

The 826-byte manifest region remains exact assembly. Live Ghidra analysis of
`th10.exe` identifies `FUN_00433230` as
`undefined4 __stdcall FUN_00433230(int param_1)`, with one 4-byte stack
parameter, a return value of `1`, and one caller at `0x0042D28F`. The retail
epilogue is `RET 4`. The manifest still maps the extent
`0x00433230..0x00433569` to `_asm_FUN_00433230_00433230` as `kind=asm`.

The behavior is recoverable, but this entry cannot be replaced safely by an
ordinary C++ body under the current alias and helper declarations. The caller
at `0x0042D28F` pushes the menu object and expects this routine to remove that
argument. The current `asm_symbols.hpp` declaration for the mapped entry is
an undecorated cdecl/no-argument symbol. An ordinary one-argument `__stdcall`
definition would use a different decorated x86 symbol and would not satisfy
the existing fixed-address alias.

There is a second private ABI at the text append boundary. Live Ghidra
decompilation/disassembly of `0x00401630` shows it formats the varargs and
then calls `0x00401530`. `0x00401530` receives the `GameThread` in `ECX` and
formatted text in `EAX`, and reads the position vector from `EBX[0..2]`.
Every append from this function sets `EBX` to a stack-resident x/y/z vector
before calling `0x00401630`. A normal C++ varargs declaration for the
formatter does not carry that vector. A semantic replacement therefore
needs both an entry thunk that preserves the fixed alias and `RET 4` behavior,
and a call bridge that establishes the hidden `EBX` vector. The shared header,
manifest, layout, and caller were outside this audit's edit scope, so those
contracts have not been changed.

The existing exact naked body is retained. Its earlier recorded MSVC 13.10
readable-stub probe produced only 5 of 826 bytes; no new build, probe, or test
was run for this audit.

## Recovered behavior

- Draw only when the object state at `param_1 + 0x20` is `2`; always return
  `1`. The function sets `g_pGameThread + 0x8988` to `1` before drawing.
- Visit ten rows. The row slice begins at
  `data_0047783c + (3 * data_00474c68 + data_00474c6c) * 0x437C +
  data_00474c74 * 0xF0`, then advances by `0x18` per row. The live accesses
  use row-relative fields at `+0x18` (score), `+0x1C` (difficulty), `+0x1D`
  (stage), `+0x1E` (inline name), `+0x28` (timestamp), and `+0x2C` (clear
  percentage). These offsets describe the observed accesses; they are not
  asserted as a standalone C++ record type.
- Use x/y/z values `48.0f`, `160.0f`, and `0.0f` for the first row, advance
  y by `18.0f`, and set the row color to the selection color or a descending
  fade color. A nonzero flag at `param_1 + 0x58EC` selects the fade path.
- A zero timestamp selects the placeholder date/time format. A nonzero
  timestamp goes through the CRT `_localtime` helper at `0x00452BAA`; the
  function formats year (`tm_year + 1900`), one-based month, day, hour,
  minute, the difficulty-label pointer from `0x0047471C`, and clear
  percentage.
- With the fade flag clear, draw the editable name at `param_1 + 0x58DC`,
  draw its cursor using `param_1 + 0x58E8`, and draw the charset from the
  string pointer at `0x004746D8`. The charset cursor is at `param_1 + 0x58F4`;
  the last three displayed characters are emitted as byte values `0x81`,
  `0x7F`, and `0x80`.

The older callback-style reference at
`matching2/reference/legacy_semantic/src/game/replay_stage_name_draw.cpp`
captures the broad UI purpose, but its abstractions do not model the hidden
`EBX` vector or the retail entry ABI. It also uses an initial x coordinate of
`40.0f`, whereas the live instruction stream initializes it to `48.0f`; the
live listing is authoritative for this region.

## Integration requirements for a later semantic promotion

1. Keep `_asm_FUN_00433230_00433230` as the fixed region symbol, or update the
   alias and its address mapping together with the callers. A semantic
   one-argument entry has stdcall stack cleanup and x86 name decoration; a
   small undecorated entry thunk can preserve the current external symbol.
2. Declare an append bridge that takes the three-word position vector and
   establishes it in `EBX` before reaching `0x00401530` (directly or through
   `0x00401630`). Ordinary varargs alone are insufficient.
3. Keep `_localtime` as the retail helper for timestamp conversion unless a
   replacement also preserves its CRT date semantics. Byte-offset views can
   describe the page and archive data without introducing an unverified
   shared record layout.


Superseded 2026-10-02: recovered natively, see title_practice_rows_00431410.md.
