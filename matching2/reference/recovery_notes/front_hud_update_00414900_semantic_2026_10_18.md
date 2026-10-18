# Front HUD update 0x00414900: equivalent -> semantic, byte-exact (2026-10-18)

Region 0x00414900 (3,836 bytes: 3,808 code plus the 28-byte switch table the
compiler emits inside the same contribution) is now a `semantic` region,
`semantic_FrontHudUpdate_00414900`, from `src/game/front/front_hud_update.cpp`
via the native-LTCG cluster `layout/ltcg/front_hud_update_00414900.json`.
The equivalent layout `layout/equivalent/front_hud_update.json` and the
`equivalent_recoveries` entry are gone; the region's `previous_record` keeps
`asm_FUN_00414900_00414900`.

## What closed the last 16 bytes

The equivalent model stood at 2 recorded hunks / 16 differing bytes, both
`fadd` operand orders (`fld [mem]; fadd ds:const` against the reverse). The
model named the constants through `flt_0_025` / `flt_224` bindings, which the
compiler pooled at addresses of its own choosing. Writing the literals directly
(`+ 0.025f`, `+ 224.0f`) makes the compiler emit its own pooled `__real@`
symbols; `constant_aliases` then rebinds `__real@3ccccccd` to 0x00470CF8 and
`__real@43600000` to 0x00470B4C, and the two `fld`/`fadd` pairs come out in
retail's order with zero recorded differences. `__real@3f800000` (0x00470AFC)
is rebound the same way because the selected body references it.

## Cluster shape

- `functions`: `?FrontHudUpdate@@YGHPAUFrontUpdateView@@@Z`, 0x00414900,
  3,836 bytes; whole contribution, `roots` keeps its public stdcall ABI.
- `context`: the 0x00415AE0 trampoline, compiled from
  `build_support/contexts/legacy/game/front_hud_update_00414900_context_source.cpp`
  (the 0x00415E90 cluster's context, whose source belongs to that cluster, with
  the trampoline renamed to `?Callback@front_hud_context@@YIHPAX@Z` so LINK does
  not decorate the `/ENTRY:` name).
- 37 `anchors`: every other compiled body of the equivalent model's link, the
  dispatcher `_ResultDispatcher2@4` at 0x00415E90 (4,428 bytes) among them.
  The `front_script_tick_00415e90` cluster and its context files are untouched.
- Inputs: the driver (model) first, the context source second, in the order the
  equivalent layout measured; the compiler's register choices depend on it.

## Gates

Full sandbox build: `.text` sha256
`c1acff416da826334c29a19fa89cd7a094626eb36c32afe7950f705a55f56998` (retail);
`--exact` executable sha256
`2f14760b6fbbf57549541583283badb9a19a4222b90f0a146d5aa17f01dc9040` (retail);
0x414900 byte-identical in the default build; progress 2,300 semantic /
22 equivalent; `probe.py` on the unit reports EXACT.
