# Linear camera shake 0x0043C550: byte-exact, 2026-11-01

The 439-byte update task of screen effect mode 1 (`@LinearShakeUpdate@4`) is
now byte-exact C++. The source is `src/core/screen/camera_shake.cpp`. It is
an ordinary translation unit: the regions.json flags (`/O2 /Gz`, no `/GL`), no
LTCG cluster. The old equivalent layout `build_support/layout/equivalent/camera_shake.json`
is gone, and so is the asm owner `build_support/exact/core/screen/shake_update.cpp`.
That layout recorded two `evaluation-order` hunks: the `fidiv dword ptr [esp+8]`
at +0xB6, where retail has it at +0xCE.

## What closed it

The amplitude statement is now two statements. The product is rounded to
float and named before the divide:

```c++
float scaled = (float)((float)delta * self->timer.elapsed);
float amount = scaled / limit + start;
```

The old spelling was `float amount = (float)delta * self->timer.elapsed / limit + start;`.
With the new one, 134/134 instructions and 439/439 bytes are identical to
retail, in the old LTCG equivalence rig and as a plain unit. The fix is plain
C++: no asm, barrier, padding or flag change.

What happens in c2 (from the search agent's tracers, which read c2.dll
13.10.6030 with hardware breakpoints in a real link):

- `fild [limit]` + `fdivp` are merged into one `fidiv` before list
  scheduling. Once merged, the divide has no operand left to wait for, so in the
  old spelling it was ready as soon as the `fmul` was. The scheduler put it at
  +0xB6, right after the second random draw reloads the seed.
- A cast to float, or a named float local, adds a copy (paren) node between the
  product and the divide. One such node is bypassed: its successors get
  the product's edge with zero latency. So a single cast or a single named
  local leaves the divide early.
- Two chained nodes (the cast and the named local) keep a predecessor edge
  into the fidiv. The first node is scheduled on the integer unit at cycle 24,
  after `lea edx,[eax*4]` of the second random draw. So the fidiv comes right
  after it, at +0xCE, as in retail.

Ruled out on the way: the +6 latency for narrow (16-bit) writes applies to
register dependencies only. Memory dependencies (the `[esp+8]` divisor home
and the RNG seed word) have a fixed latency. Block splits do not move the
divide either. The other spellings measured are in
`matching2/build/experiments/goal_2026_11_01/camera_shake/V1.py`..`V9.py`
(winner: `pp_named_cast` in V9.py). The scheduler tracers (`trace8.py`,
`t8show.py`, `lat.py`, `latk.py`, `bp.py`, `gdump.py`) are in the same
directory.

## Build

There is no cluster. The function is a standard `__fastcall` (context in ECX,
`ret` with no stack arguments), so the plain `/Gz` compile emits it as is. The
synthetic caller `CameraShakeEntry` and its volatile callback pointer are
gone. They were the rig's link entry (`_CameraShakeEntry@4`) and are not
needed outside LTCG. The `.text$00camera` code_seg is gone too: the build
selects the function's COMDAT section by symbol.

The externs now use the project's existing names, so the unit links against
the regions.json `symbols` table without new entries:
- `g_screen_effects_frozen` (0x004918A4), formerly `g_shake_cancel`;
- `g_rng` (0x004918B0) through the local `ShakeRngStorage` view, which reads
  the seed as one 32-bit word as retail does;
- `g_screen_shake_x`/`_y` (0x00491E64/68);
- `g_frame_timer_normal_lower`/`_upper` from `th10/math/timer.hpp`
  (0x00470B68/64).

`__real@3f800000` and `__ftol2` were already in the table.

Callers reach the function by its retail address: the selector's cluster
(`native_ascii_factory.json`) binds `@LinearShakeUpdate@4` = 0x0043C550 as an
absolute symbol.

Region record: `semantic_LinearShakeUpdate_0043c550` (previous record
`ScreenShake_Update`, asm).
Promotion dir: `matching2/build/experiments/goal_2026_11_01/promote_camera_shake/`.
