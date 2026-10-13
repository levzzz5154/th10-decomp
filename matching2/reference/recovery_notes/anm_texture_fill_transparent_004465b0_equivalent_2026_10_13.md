# 0x004465B0 AnmTexture::FillTransparentPixels: equivalent recovery, 2026-10-13

`void AnmTexture::FillTransparentPixels()`, texture holder received in EAX,
called from the upload at 0x00446C70 (`mov eax,edi; call 0x004465B0`) and from
LoadFile/UploadAt/CreateFromMemory/CreateAndUpload. Takes level 0 of the D3D
texture, `GetDesc`, `LockRect(&locked, 0, 0)`, switches on the format (0 and
21: A8R8G8B8, 25: A1R5G5B5, 26: A4R4G4B4; everything else leaves), fills every
transparent pixel with the plain average of its opaque left/right/above/below
neighbours (no halving, unlike the font atlas pass at 0x00436DA0), then
`UnlockRect` and `Release`. The 1,463-byte region is 1,417 bytes of code, three
padding bytes (`lea ecx,[ecx+0x0]`), a four-entry jump table at 0x00446B3C and
the 27-byte index table at 0x00446B4C.

## Why equivalent, not exact

The receiver register (EAX) is a private LTCG convention, and the retail body
keeps its canonical zero in ESI from the prologue on (the `level` argument, the
`surface = 0` store, both null `LockRect` arguments and every `jbe`-guard
compare read that one `xor esi,esi`). Every source shape this attempt tried —
all 720 declaration orders of the seven locals, all 24 zero-initialisation
orders per kernel, mid-block declarations, for-init scoping, a `level` local —
produced the same compiled head with the zero in EBX (or, with `n = 0` first,
no zero register at all and immediate pushes). The prologue save follows the
zero: retail `push esi` / model `push ebx`. That single allocator decision
reschedules the whole function, so an exact probe was not reached; the
equivalence gate is.

## Model

`equivalent/render/anm_texture_fill_transparent_pixels_004465b0.cpp`, compiled
against a stand-in-free copy of the `anm_texture_upload_00446c70` cluster
context (the layout's `context_cluster` points at
`layout/ltcg/anm_texture_fill_transparent_004465b0.json`, a copy of that
manifest whose driver drops the 13-byte `FillTransparentPixels` stand-in so the
model's own definition is the only one). The co-compiled retail-exact callers
give the pass the EAX receiver, the vtable slots and the whole call graph.

Verdict (`verify_recovery` non-record, i.e. what `make` enforces):
1,451 of 1,463 bytes used, 365 of 499 instructions identical, 0 base/index
swaps, 10 frame-offset instructions, 124 instructions in 80 recorded
differences (total 149 of 499, budget 166; structural 52, budget 62).

Load-bearing source shapes (any deviation loses the match):

- The interleaved declaration order `i, surface, j, locked, sum, n, desc` puts
  each local in retail's frame slot (surface +0, i +4, j +8, locked +0xC,
  sum +0x14, desc +0x20). The loop counters are additionally declared in each
  `for` statement; the shadowed outer declarations exist to hold the slots.
- The zero-initialisation order inside each pixel branch (`n` first, then the
  sums, `sum[1]` last) is what the scheduler reproduces.
- The `tex` local and `default: break;` both change the allocation and are
  kept.

## Recorded differences, by class

- `register-choice`: the zero register story (retail materialises `xor
  esi,esi` in the prologue and compares against it; the model pushes immediates
  and uses `test`), the pointer register of the 16-bit kernels (retail EBP,
  model EDI), the neighbour count (retail EDI, model EBP) and the sums that
  travel in other registers.
- `evaluation-order`: pure reorderings — the `b`/`g` zero stores, `add
  ecx,0x4` at the 8888 latch, the reloaded `j` around the 16-bit stores.
- `code-shape`: the loop-alignment filler of another shape (`mov edi,edi`
  against `jmp L+X / lea ecx,[ecx+0x0]`, retail's single `nop` before the 4444
  inner head) and the latch blocks the model merges differently.
- `frame_shift: {deltas: [4], count: 10}`: the model has no prologue register
  save (the zero is not a register), so every head/exit `[esp+X]` sits one slot
  lower; the ten affected instructions are counted as frame-offset.

`code_bytes` is 1420, not 1417: the three padding bytes before the jump table
count as code so the model's shorter tail compares table-to-table (the padding
decodes as one `lea ecx,[ecx+0x0]` and is recorded as an alignment-padding
difference). `compare_tail` then checks both pointer tables through the
instruction mapping and the 27 index bytes byte-for-byte; they are identical
because the case structure is.

## What is identical

Head through the dispatch (`sub esp,0x40` … the indexed jump), all three
kernels' neighbour tests, extraction shifts/masks, division chains and pixel
stores, the `UnlockRect`/`Release` exit and both tables. The differences are
register homes, operand scheduling, alignment filler and the merged latch
tails listed in the layout.

Scratch tools: the cluster probe (`probe.py --project scratch/4465b0/msvc`)
for per-variant byte diffs and an instruction-stream differ over
`find_differences` for classification. See also
`anm_texture_fill_transparent_004465b0_2026_10_10.md` (the earlier LTCG rig
state) and `font_atlas_convert_00436da0_regalloc_2026_10_10.md`.
