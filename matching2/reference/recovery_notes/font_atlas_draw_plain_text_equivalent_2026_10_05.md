# Plain atlas text drawing C++ equivalence recovery, 2026-10-05

The complete 509-byte routine at `0x00437FE0` now has a C++ implementation
selected by `layout/equivalent/font_atlas_draw_text_00437fe0.json`. The default
build uses it; `make EXACT=1` retains the original assembly. The model is the
natural source from `font_atlas_draw_plain_text_00437fe0_parked_2026_10_05.md`,
with its real surface-fill dependency compiled in the same native LTCG scope.
The draw function itself is rooted to preserve its public six-argument stdcall
entry and RET 24. The fill call is rebound to the existing owner at 0x00436CA0.

The comparison reports 166 instructions, 117 identical, and 44 recorded hunks.
Most hunks repeat the same size/font register substitution across the fifteen
font-selection branches. No unproven branch targets, frame shifts, or
base/index differences are admitted. The full function remains 509 bytes.

## Allocation and instruction review

After all four callee-saved pushes, both bodies have the same frame and public
argument addresses. Every saved register is restored on both surface-release
paths, and the same 24 argument bytes are removed on return.

| Value | Retail | C++ |
| --- | --- | --- |
| font size during selection | EBP | EDI |
| selected font | EDI | EBX |
| device context | ESI | ESI |
| SelectObject import pointer | EBX | EBP |
| drawn row count | EDI | EDI |
| previous selected object | dead size-argument slot | EBX |
| size after the first SelectObject | EBP | size-argument slot |
| temporary surface output | dead color-argument slot | dead size-argument slot |

At `+0xD6`, the C++ clamps the size in its argument home and reloads it instead
of keeping it solely in EBP. That home is private to this call, its updated
value is used for the source rectangle height, and it is reused as the
surface output only after the final size use. The inline upload helper bounds
that output local's lifetime. The three recorded surface-slot offsets refer
to the same value across GetSurfaceLevel, upload and conditional release;
the temporary's address itself does not escape that call's output contract.

All fifteen font pointers, size thresholds and comparison signedness agree.
The moved initial size load accounts for the intervening pushes in its ESP
offset. The previous-object value is preserved across calls in either a saved
register or an unused argument slot. Both restore that first SelectObject
result twice, regardless of the later SelectObject return values.

The width calculation loads `destination.left` into EDX before loading the
right edge, rather than subtracting the left-edge memory operand directly.
The rectangle is unchanged during this calculation, no call or memory write
intervenes, and both compute `(right - left) * 2 + 22` with the same 32-bit
arithmetic and signed 1024 clamp. The reloaded size computes the same bottom
edge. A four-byte LEA alignment filler disappears; it has no flag, stack or
memory effect. External-call ordering and all other operations agree.

## Differential execution

`matching2/tests/font_atlas_draw_plain_text_differential.py` compiles the
maintained C++ through the **strict** equivalence gate, then executes that
native body and retail under Unicorn. It compares every external call's
arguments and source/destination rectangle contents, including the private
fill ABI, and poisons EAX/ECX/EDX at each call to exercise preserved values.
Only private output-slot addresses are normalized to the value written.

All **3528 cases pass**: every font threshold, negative and extreme sizes,
four x coordinates including a wrap boundary, widths below/at/above the
1024 clamp, empty/ASCII/multibyte text, and valid/null surface outputs. Each
case also checks callee-saved registers, stack cleanup, unmodified destination,
one text call, two restores of the first object, and conditional release.
The helpers and Windows/COM calls are stubs: this validates the routine's
boundary behavior, not GDI rasterization or Direct3D output pixels.

Reproduce using Python with Unicorn installed:

```sh
python3 matching2/tests/font_atlas_draw_plain_text_differential.py
```

The local run used
`matching2/build/lzss-compressor-recovery/venv/bin/python`. The full normal
and exact image gates are run after integration.

## 2026-10-17: register-family state reviewed; parked

The 37 register-choice hunks are the substitution table above (size EBP/EDI,
import pointer EBX/EBP, previous object slot/EBX) repeated across the fifteen
font-selection branches: one function-wide register-assignment difference,
not fifteen independent ones. The documented route is the SpillCosts /
ChoosePhysReg trace (`msvc-c2-spillcosts-priority` traces the address from a
failing region), which needs its own tracing session; no source spelling was
tried this pass to avoid disturbing the four reviewed non-register hunks.

Region stays equivalent (328 differing bytes).

## 2026-10-18: byte-exact — the link context was the register contest

All 509 bytes match; `equivalence.py` reports `differences: []`,
`not_equivalent: []`, `base_index_order: 0`, `frame_offset: 0`. The model
source is unchanged from 2026-10-05. The lever is the build context.

`msvc-ltcg-direct-caller-changes-codegen` records that a function measured as
the rig's `entry_symbol` is compiled as if reached only by address, that an
internal function with a direct caller loads its stack parameters in the entry
block, and that "priorities shift by a few points when the context changes, so
re-check register contests after the switch". A Spillcosts/ChoosePhysReg trace
of the parked model put `size` at priority 66 and the `SelectObject` import
pointer at 73. The import pointer is therefore placed first and takes EBP: the
shared zero immediate is a single-register rival on EBX (its early piece is the
strlen loop's byte compare) and repels that register with 100*f40. `size` is
then forced to EBX and the whole substitution table in the 2026-10-17 section
follows. Retail's layout is the opposite placement: `size` first, taking EBP,
the import pointer forced to EBX, `previous` finding no register and landing in
the dead size-argument slot, and the surface output moving to the dead colour
slot. Forcing the import pointer to EBX at its ChoosePhysReg decision
(diagnostic only, never selected by the build) reproduced retail's layout for
the entire function, which named the target exactly.

The fix is `build_support/contexts/equivalent/font_atlas_draw_text_context.cpp`,
a forwarding stub that calls `FontAtlas_DrawPlainText` directly, listed in the
layout's `context_sources` with `entry_symbol` `_FontAtlasDrawTextContext@24`
(the checker locates the region through `function`, so the link entry is free
to be the context, as in the midi tick cluster). With a direct caller the body
compiles as an internal function and the priorities move as the rule predicts.

Ruled out, byte-gated on the 328-byte baseline and the 28-byte intermediate
that the volatile probe produced:

- `void* volatile previous`, `*(void**)&size` slot aliasing and address-taken
  `previous`: forcing `previous` to memory clears 300 of 328 bytes and leaves
  only the size/import-pointer pair swapped; the qualifier is not needed once
  the context is right.
- Clamp spellings (ternary, separate clamped local, `<= 16`, `< 18`, the
  sibling's volatile reload, a `__forceinline` clamp helper): 318/328/329
  differing bytes or no movement; the compare/def form is canonical.
- The expression-written-twice and named-local families (`size + size`, hoisted
  `size * 2`, counts restated at the call sites, named colour/x/length locals,
  two locals read from the same member): each folds back to the same IR.
- Zero-immediate type splits (`(char)0`, `0L`, `0u` at the TextOutA y, at the
  source-rect stores and at the D3DX arguments): constants canonicalise.
- `__forceinline` helper wraps around the restores, the SelectObject trio and
  the size arithmetic, in both parameter orders: pure-computation helpers fold
  away and the SelectObject wrappers regress to 153 differing bytes.
- Address-taken size/font/length, `CopyAtlasToTexture` parameter reordering,
  row_count/bottom hoisting and the ternary font chain: no movement.

# 2026-10-18: promoted to an exact recovery (LTCG cluster)

The equivalent recovery is replaced by the native-LTCG cluster
`build_support/layout/ltcg/font_atlas_draw_text_00437fe0.json`. The model
source is unchanged; the cluster keeps the direct-caller context edge that
closed the register contest (the 2026-10-18 section above), now as the
cluster's compiler context: `build_support/layout/ltcg/font_atlas_draw_text_00437fe0_context.cpp`
includes the model source and calls `FontAtlas_DrawPlainText` directly from
`_FontAtlasDrawTextContext@24` in `.text$03context`, so the native /LTCG link
compiles the body as an internal function with a direct caller and the
Spillcosts priorities stay where retail's are.

Cluster facts (measured from the native `cluster.map`, `native-*` run):

| contribution | section | address | bytes |
| --- | --- | --- | --- |
| `FillRgb444` (anchor, compiled through the model's `resource_file.cpp` include) | `.text$01accessor` | 0x00436CA0 | 72 |
| `FontAtlas_DrawPlainText` (selected) | `.text$02text` | 0x00437FE0 | 509 |
| `_FontAtlasDrawTextContext@24` (compiler context, not selected) | `.text$03context` | 0x004381E0 | 42 |

Zero-filled gaps `.text$00before` (0x35CA0), `.text$01accessorz` (0x12F8) and
`.text$02textz` (3) absorb the space and the COMDAT alignment slack; the
context's first declared size (48) was corrected to its measured 42. The
`FillRgb444` anchor exists so the modelled call bakes the retail displacement;
its established unit `src/core/main/resource_file.cpp` stays intact
(`included_sources`). The absolute symbols bind the import thunks, the atlas
globals, `InvertAlpha`, `FontAtlas_Convert` and `D3DXLoadSurfaceFromMemory` at
their retail addresses, as in the equivalent layout.

regions.json cutover: the region record becomes
`semantic_FontAtlas_DrawPlainText_00437fe0` (previous_record kept), the model
source joins `translation_units`, the asm owner
`build_support/exact/core/main/fun.cpp` is deleted (it owned only this
region), the equivalent_recoveries entry and the equivalent layout are gone,
and the cluster is registered in `ltcg_clusters`.

Gates: `probe.py --source src/core/main/font_atlas_draw_text.cpp` reports
EXACT for the 509-byte body; `test_ltcg_cluster.py` (60) and
`test_equivalence.py` (27) pass; the full `build_msvc.py` run requires the
linked `.text` to match retail's SHA-256.
