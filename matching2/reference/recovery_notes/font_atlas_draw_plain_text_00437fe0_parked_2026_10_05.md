# 0x00437FE0 plain atlas text draw (parked 2026-10-05)

Not recovered; the region is still `asm_FUN_00437fe0_00437fe0`. The work in
progress is in `build/experiments/font_atlas_437fe0_claude/` (source, header,
cluster JSON and context; `font_atlas_draw_text_00437fe0.cpp` is the natural
model, `last_tried.cpp` the last experiment).

## What the function is

`void __stdcall (const RECT* destination, int x, int size, COLORREF color,
const char* text, IDirect3DTexture9* texture)`, the unshadowed sibling of
0x00437DB0: pick one of the fifteen fonts at 0x00491868..0x004918A0 by size,
clamp the size to 17, fill the atlas (0x00474CB0) with the colour
(0x00436CA0), select the font, `InvertAlpha(size*2+6)`, `SetBkMode`,
`SetTextColor`, `TextOutA(dc, x*2, 0, text, strlen(text))`, restore, invert
again, convert (0x00436DA0), restore again, then copy
`{0, 0, min((right-left)*2+22, 1024), size*2+2}` to the texture's level-0
surface with D3DXLoadSurfaceFromMemory and release the surface.

## What is solved

* **Frame of 0x14 and the surface in the dead `color` slot.** c2's stack
  packing gives every parameter a colour and lets a local share it when their
  lifetimes do not conflict. A plain address-taken local conflicts with
  everything that is live at a call, so it never shares. A local of an
  *inlined helper* has a lifetime bounded by the helper and does share. The
  surface lookup, the upload and the release therefore belong in one inlined
  helper (`CopyAtlasToTexture`); that also gives retail's two reloads of the
  surface. A shared local goes to the heaviest (most referenced) parameter
  slot that does not conflict. The sibling's `&size` hack in
  `src/platform/font_texture_draw.cpp` is the same thing and can be redone
  this way.
* With that helper the model is 509 bytes and differs only in register
  allocation.

## What is not solved

Retail: `size` in EBP for the whole function, the SelectObject pointer in
EBX, the previously selected object spilled (into the dead `size` slot).
Model: the previous object in EBX, the pointer in EBP, `size` spilled.

Measured with the regalloc tracers (K = candidates referenced in a block; a
reference adds 2*K, living through a block costs K):

| candidate | big block 1 (K1=11) | big block 2 (K2=16) | total |
| --- | --- | --- | --- |
| dc | | | 187 |
| row count | | | 101 |
| SelectObject pointer | 1 ref | 2 refs | 79 |
| previous object | 1 ref | 2 refs | 79 |
| size | 1 ref (+19 from the ladder) | 1 ref | 70 |

So `size = 16 + 2*K1 + 2*K2`, the other two `2*K1 + 4*K2 - 7`; `size` needs
about ten more points (one more counted reference in either big block would
do). Each ladder rung is worth only +2 -1 because the compare and the
assignment blocks reference one candidate each.

With the previous object forced into memory (`volatile`, experiment only) the
result is retail except EBX/EBP swapped. `ChoosePhysReg` takes the register
with the lowest cost, and EBX carries a cost of 100 from the start: the
shared zero immediate is a candidate whose only available register is EBX,
and a candidate limited to one register adds 100 * weight to that register
for its neighbours. Retail's assignment (pointer in EBX, size in EBP) follows
if either `size` is chosen before the pointer or that reservation is absent.

Tried without effect (same code as the natural model): array or separate
globals for the fonts, ternary chain, helper returning the font, `size*2`
spelled other ways, no `row_count` variable, `dc` not cached, rectangle as an
initializer, pointer/reference/struct/union/array forms of the previous
object, reusing `font` for it.

Tracer additions made for this: `stackpack/trace_stackcolors_cl.py` lists
every stack element with its conflict set; `regalloc/trace_choose_physreg.py`
prints the available registers, the cost table and the single-register
candidates at every choice.

## Later the same day

* Both remaining differences follow from one fact: if `size` scored above 79
  it would be chosen third (EBP, because EBX carries the zero's cost), the
  SelectObject pointer fourth (EBX, the only register left) and the previous
  object would get nothing and be spilled into the dead `size` slot. No
  `volatile` is needed for that.
* Sanity check: a real extra use of `size` in the second big block does give
  `size` a register for the whole function.
* Immediate candidates in this function are limited to byte registers
  (EAX/ECX/EDX/EBX), which is why the zero can only take EBX across calls.
* `build/experiments/font_atlas_437fe0_claude/promote437.py on|off` (run from
  `matching2/`) switches the region between the asm record and the model so
  the cluster can be probed again.
