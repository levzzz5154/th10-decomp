# GCC/Clang regions moved back to the retail toolchain

Historical port checkpoint: the polar setters have since returned to the pinned
GCC path to satisfy the no-inline-assembly objective. Their current C++ bodies
match all eight 30-byte regions. Other ports below remain in place. See
[the later checkpoint](ecl_int_operand_and_polar_2026-09-30.md).

2026-09-30. Ten sources were built by the pinned GCC or Clang profiles under
`source_compilers`. Nine of them are now either toolkit library sections or
MSVC 13.10 C++; each converted unit probes EXACT and the complete executable
still passes the 487,936-byte hash gate. Only `0x00412A60` keeps its Clang
profile.

| Region(s) | Was | Now |
| --- | --- | --- |
| `0x00453762` (36), `0x00453786` (86) | Clang C++ + assembly | `libcmt.lib` `wincrt0.obj` `_fast_error_exit`, `_check_managed_app` |
| `0x00454EB8`, `0x00454EC1`, `0x00454ECD` (9/12/10) | GCC + Clang C++ | `libcmt.lib` `output.obj` `_get_int_arg`, `_get_int64_arg`, `_get_short_arg` |
| Eight polar setters (30 bytes each) | GCC + custom RTL plugin | MSVC, `src/math/x87_polar_setters.cpp` |
| `0x0043A6F0` (14) | GCC | MSVC LTCG, `swap_low_word_bytes_0043a6f0.json` |
| `0x00449440` (11) | GCC | MSVC LTCG, `draw_global_animation_00449440.json` |
| `0x0040C650`, `0x0040C680`, `0x00412A00` (8/8/16) | Clang | MSVC LTCG, `ecl_operand_thunks.json` |
| `0x00412A60` (14) | Clang | unchanged |

## Runtime library sections

The five CRT functions equal whole `/Gy` sections of the toolkit's
`libcmt.lib`. They were never adopted because `adopt_crt_library.py` only
replaced sections that retire assembly, and these had already been recovered
as foreign-compiler C++. The tool now also replaces C++ whose source is listed
under `source_compilers`.

`_fast_error_exit` is 36 bytes: retail keeps the dead `pop ecx; pop ecx; ret`
cleanup after the non-returning `__crtExitProcess` call. The old 33-byte region
had left those three bytes at the head of the `0x00453783` assembly region,
so that region was first split at `_check_managed_app` (`0x00453786`).
Adoption chose byte-identical copies from `crt0.obj` and `cprintf.obj`; the
regions now name `wincrt0.obj` and `output.obj`, the members whose neighbours
retail links (`__amsg_exit`, `__output`).

`output.obj` is an ordinary (non-`/GL`) library object, yet its static
`get_int_arg` takes its argument in EAX. MSVC 7.1 gives internal functions a
private register convention inside one translation unit, not only under LTCG.

## Polar setters: the original used inline assembly

`push ecx; mov [esp],ecx; mov eax,[esp]` is what MSVC 7.1 emits when an
inline `__asm` block reads `this`: the receiver is homed in a frame slot for
the block. With `fld angle; fsincos; fmul radius; fstp [eax].x; fmul radius;
fstp [eax].y` and no C++ return statement (EAX already holds `this`), MSVC
emits all 30 retail bytes of every setter, including the elliptic variant's
`[esp+10h]` and `RET 12`. No C++ spelling makes MSVC fuse `sin`/`cos`, so this
is source-level assembly inside ordinary C++, like the `frndint` snap in
`sprite_quad_pipelines_00442670_00442ad0.md`. The GCC version needed a
compiler plugin to reproduce the receiver spill that MSVC emits by itself.

## Private-convention thunks

`0x0043A6F0`, `0x00449440`, `0x0040C650`, `0x0040C680` and `0x00412A60` have
no references in retail. They are out-of-line copies that kept their
whole-program register conventions. Each schema-1 layout supplies a synthetic
array-walking context that earns the entry registers, and ABI anchors stand
in for callees that are still assembly or that live in another cluster.

* `0x0043A6F0` needs no volatile: plain MSVC already emits retail's
  `mov [esp],ah; mov [esp+1],al; mov ax,[esp]` shape, and LTCG puts the word
  in AX.
* `0x00449440`'s anchor for `0x004451C0` must dispatch through the manager's
  vtable. A stand-in that only reads both objects assigns them (EAX manager,
  ECX entity) whichever order they are declared in.
* `0x0040C680` enters with the selector in ECX, the slot in EDX and the float
  on the stack: a public `__fastcall`. It tail-jumps only when the
  `0x0044FF80` declaration is `__stdcall`, so both pop the same four bytes
  (retail's `RET 4`). Its binding `_asm_ECL_ResolveFloatValue_0044ff80@12` is
  in `symbols`.
* `0x00412A00` passes its selector as the ignored ECX argument of the
  `__fastcall` `0x0044FDB0` binding, so ECX needs no move.

## Residual: `0x00412A60`

MSVC reproduces the extent, the entry registers and the tail jump, but loads
the intermediate slot into EDX (`mov edx,[eax+14D8h]; mov eax,[edx+4]`)
where retail reuses EAX. Unchanged under: named temporaries, reusing the
parameter, a forced-inline slot helper, a member-function resolver, `/O1`,
`/O1 /Oy-` and `/Os`, and resolver stand-ins that do not touch EDX. An
ignored third resolver parameter was placed on the stack, not in EDX.
