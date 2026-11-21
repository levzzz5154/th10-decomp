# Sprite quad submit pipelines at 0x00442670 and 0x00442AD0

The maintained [regular](../../msvc/src/core/sprtfunc/sprite_quad_submit.cpp)
and [mirrored](../../msvc/src/core/sprtfunc/sprite_quad_submit_mirrored.cpp)
pipelines byte-match retail and still use inline `FRNDINT` for pixel snapping.
In the pinned MSVC 7.1 compiler, declaring `rint` or `nearbyint` and marking
it intrinsic still emits an external call, not the retail instruction (`C4163` under `/Oi`). The backend does emit
`FRNDINT` *inside* its `exp` expansion, between `FLD` and `FXCH`; that is
not a pixel-rounding intrinsic. GCC emitted all four `FRNDINT` instructions in 24 full builds of each pipeline;
none produced the retail 1,111-byte function. See the
[byte-matched checkpoint](native_recoveries_2026-09-27_third.md).

Calling the original CRT rounding routine (`_frnd`, `0x0045EBBA`) from C++
produces four calls in each native MSVC body and expands each from 1,111 to
1,189 bytes. The linked routine performs `FRNDINT`; calling it does not
reproduce the inline instruction sequence. The native `exp` expansion rounds
`x * log2(e)` for its own range reduction; C++ cannot read that intermediate
as a rounding result. A full MSVC build with signed binary32 arithmetic in
place of the snap block emitted 1,475 bytes and no `FRNDINT`.

With GCC 16.2, `__builtin_rintl` emits all four rounding instructions,
but even the 889-byte size-optimized submitters take the manager in EDX,
not ECX. Compiling the real callers alongside them instead puts the entity
on the stack and emits `ret 8`. Neither is callable with retail's contract.
Clang's register calling convention can keep both incoming registers, but
emits a plain `ret` and calls an external rounding routine.
GCC 16.2 rejects combining `thiscall` and `regparm(1)`. Clang 23 accepts the
combination but still receives the entity on the stack and emits `ret 8`.

Open Watcom can express the entry directly (entity in EAX, manager in ECX,
`ret 4`). In complete builds of both submitters, `rint` and `nearbyint`
still emitted four library calls each, even with `#pragma intrinsic`. None
emitted the four inline rounding instructions.

Digital Mars C++ 8.57.0n emitted all four `FRNDINT`s and all eight corner
stores in the regular submitter. It spilled three rounded coordinates,
expected the entity on the stack and ended in `ret 8`. Its complete body
was 1,047 bytes, not 1,111.

Both versions share the [screen-origin adjustment, viewport culling and batch staging](../../msvc/include/th10/render/sprite_quad.hpp).
Their U coordinates and half-pixel constant bindings remain distinct.

Historical snapshot, 2026-09-13: the last two direct `SyncRenderState` callers
were converted to ordinary C++. Both 1,111-byte sprite pipelines and the
25-byte colour helper they call matched the retail image while the snap path
still used inline x87 assembly.

Historical semantic-only experiment, 2026-09-23: both `FRNDINT` blocks were replaced
with ordinary C++ calls to `rint`, followed by the same half-pixel adjustment
and duplicated corner writes. Microsoft documents `rint` as following the
active floating-point rounding mode and raising `FE_INEXACT` when rounding
changes the value, matching the x87 operation's normal rounding and inexact
behavior ([Microsoft CRT `rint` documentation](https://learn.microsoft.com/en-us/cpp/c-runtime-library/reference/rint-rintf-rintl?view=msvc-170)).
That version was not compared with retail and is not the maintained source.

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
- Each snap reads one edge, rounds it according to the x87 control word,
  subtracts the pipeline's half-pixel constant, and writes the paired corners.
  Changing the rounding to a truncating integer cast is not equivalent.

## Historical validation before the source update

The following measurements describe the 2026-09-13 version with inline x87.
They are not measurements of the later `rint` experiment.

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
