# Sprite quad submit pipelines at 0x00442670 and 0x00442AD0

2026-09-13. The last two direct `SyncRenderState` callers are now ordinary C++.
Both 1,111-byte sprite pipelines, and the 25-byte colour helper they call, are
byte-exact in the existing native-LTCG render batch. That is 2,247 bytes: the
largest single-step recovery since the render cluster was created.

## What the two pipelines do

The sprite VM has already written the four corners of one sprite into the
shared quad buffer at `0x004978C0`. Each pipeline then

1. adds the manager's screen origin (`manager+0x5C`/`+0x60`) to all four
   corners,
2. when bit 0 of the mode argument is set, snaps the shared left, right, top
   and bottom edges to whole pixels and pulls each back by a half pixel,
3. maps the sprite's texture coordinates onto those edges — the two functions
   differ only here: `0x00442670` puts the sprite's `u0` on the left edge and
   `u1` on the right, `0x00442AD0` mirrors that pair,
4. computes the quad's bounding box,
5. culls it against the render target's D3D viewport (`data_00491FAC+0xCC`),
6. closes the open batch when the sprite's texture or the pipeline id changed,
7. modulates the selected entity colour by the manager's fade bytes through
   `0x004423C0`, and stores it into all four corners unless bit 1 of the mode
   argument is set,
8. calls `SyncRenderState` and then `AppendQuad` on the same manager.

Retail sources are separate translation units: the two `.rdata` half-pixel
constants below sit in the regular data of two different objects and the two
functions are the only users of the *mirror* of the shared `0.5f` pool copy at
`0x470B0C` (which every other function in the image uses).

## The private conventions the batch reproduces

| address | function | ABI retail selected |
| --- | --- | --- |
| 0x00442670 | `SubmitSpriteQuad` | entity in EAX, manager in ECX, mode on the stack, `RET 4` |
| 0x00442AD0 | `SubmitSpriteQuadMirrored` | same |
| 0x004423C0 | `AnimationColor_MultiplyChannel` | value in AL, scale in CL, result in EAX |

The source keeps ordinary member/`/Gz` declarations. Only the compiler scope
makes these conventions expressible: the pipelines call `SyncRenderState`
(EAX manager / EDI entity), `Flush` (ESI manager) and `AppendQuad` (EAX manager
/ EDX vertices), and `AnimationColor_MultiplyChannel` is called four times per
pipeline with the channel in AL and the fade byte in CL. Adding the helper as a
fourth source of the same `/GL` link is what reproduces those call sites; as a
standalone unit the same body compiles to a `movzx`-from-stack prologue instead.

## Source-shape evidence

- The cull and the minimum-tracking guards must be spelled with `<`:
  `max_x < (float)target->x`, `min_x = a < b ? a : b`. MSVC 13.10 emits
  `test ah,5` / `jp` for an ordered `<` and `test ah,1` for the negation of
  `>=`; retail uses the former at every one of those sites. The `>` guards on
  the maxima and the `(float)unsigned > max_y` test already matched with mask
  `0x41`.
- The colour channels are read back through the byte array
  (`channels[0..3]`), not through shifts of the live value: retail loads a byte
  from the spill slot for green, blue and alpha, and only the first (red)
  channel is taken from the register with `shr eax,16`.
- The four uv stores are chained assignments in the order
  `quad[0].u = quad[2].u = u0`, `quad[1].u = quad[3].u = u1`, `quad[0].v =
  quad[1].v = v0`, `quad[2].v = quad[3].v = v1`; right-to-left evaluation then
  reproduces retail's store sequence exactly.
- The two half-pixel constants are bound as `_data_00470e8` and
  `_data_00470ec` (`extern "C" float`) instead of being written as `0.5f`
  literals. The compiler pools one `__real@3f000000` per link, so a single
  literal can only ever reference one address; retail's two pipelines each read
  their own preserved `.rdata` slot.
- The pixel snap cannot be expressed in C++98 on this toolkit. The image
  contains a bare `frndint` only in these two functions, in the CRT's
  hand-written `__frnd` (`0x0045EBBA`) and in the `_exp` tail (`0x00464F00`).
  `floor`, `floorf`, `ceilf`, `rint`-style spellings and every integer-cast
  round trip emit CRT calls or `fistp` sequences instead (26 spellings probed
  against `cl 13.10.6030` with the retail flags). The snap block is therefore
  kept as the original source's own `__asm` block, assembled unmodified, while
  everything around it is C++. It is the only inline assembly inside recovered
  game code.

## Validation

`python3 matching2/tools/matching/probe.py --source src/render/sprite_quad_submit.cpp`
reports all 17 batch functions EXACT. `make MSVC_ARGS='--jobs 32'` passes: the
whole 487,936-byte executable is exact and its SHA-256 is unchanged
(`2f14760b6fbbf57549541583283badb9a19a4222b90f0a146d5aa17f01dc9040`).
Progress: 462 ordinary-C++ regions / 30,826 bytes; 2,123 assembly regions /
358,156 bytes.

The layout keeps every declared function at its retail address; the three new
contributions are the complete compiler output of the sources above, with no
instruction, operand, or byte rewriting. The synthetic context grew by 39 bytes
to 294 to call both pipelines and establish their entry registers; it remains
unselected and contributes zero recovered bytes.

| Address | Function | Bytes | Native body SHA-256 |
| --- | --- | ---: | --- |
| 0x004423C0 | AnimationColor_MultiplyChannel | 25 | `fa7ac58a0ae354361698ddf16f6f43a7f51dc065a39de4ecae1b4aa6becf0e3a` |
| 0x00442670 | SubmitSpriteQuad | 1111 | `56f49f7565812af6e2a1839bf818f67475fb72acb84d6c461d01e129a603a858` |
| 0x00442AD0 | SubmitSpriteQuadMirrored | 1111 | `fb3841d5757c4e9f82ab8c476ad74208cda96a1621367ffc433ab4965c6b2693` |

The focused report is retained at
`matching2/build/probe_pipeline/clusters/anm_batch_flush_00442f50/report.json`.

## Iteration harness

`matching2/build/pipeline-lab/lab.py` compiles the batch's `/GL` inputs, links
one native `/LTCG` scope with every function pinned to its retail address (the
filler gaps absorb extent differences so the following functions keep their
addresses), and prints an address-aligned instruction diff against retail. It
was the fast loop for the cull/minimum/comparison-mask and channel-extraction
questions; the maintained probe and build remain the gate.
