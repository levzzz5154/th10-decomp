# Anchored sprite quad builder at 0x00443290: reconnaissance, not yet exact

2026-09-13. The 486-byte `BuildAnchoredQuad` is the keystone of the remaining
sprite family: 0x004436C0 and 0x00443910 both call it (`push ecx; mov eax, edx;
call 0x00443290`) before submitting to the already recovered pipeline
`0x00442670`. A first source model compiles to 350-391 bytes instead of 486, so
this note records what the disassembly pins down and where the model still
diverges, to avoid re-deriving it.

## What the disassembly fixes

| item | evidence |
| --- | --- |
| entry ABI | `EAX` sprite, manager on the stack, `RET 4`; both callers pass it that way |
| placement | `x = [eax+0x334] + [eax+0x340] + [eax+0x34C]`, `y = [eax+0x338] + [eax+0x344] + [eax+0x350]`, `z = [eax+0x33C] + [eax+0x348] + [eax+0x354]` (three `Vector3` at 0x334, 0x340, 0x34C) |
| sizes | `w = [eax+0x4C] * [eax+0x3C]`, `h = [eax+0x50] * [eax+0x40]` |
| anchors | two independent `switch ((flags >> 18) & 3)` / `switch ((flags >> 20) & 3)` with cases 0, 1, 2 and an empty default; `flags` is at **0x35C** (`0x358` is the resource pointer) |
| roundings | horizontal case 0 multiplies by the pooled `0.5f` at `0x470B0C`; vertical case 0 subtracts a spilled `h * 0.5f`, and vertical cases 1/2 add/subtract a spilled `h` |
| stores | x: `quad[0].x = quad[2].x = left`, `quad[1].x = quad[3].x = right`; y: `quad[0].y = quad[1].y = top`, `quad[2].y = quad[3].y = bottom`; z: all four from `base_z + position_z + offset_z`; all inside the axis switches |
| per-case right/top edges | case 0 uses `left + w` (retail re-reads the stored left), case 1 uses `x + w` with a fresh placement sum, case 2 uses the bare placement sum |

Retail's x87 discipline is the part a first model misses: `w` stays in a
register across the horizontal switch (`fsubrp st(1),st`), while `h` and
`h * 0.5f` are both computed early and spilled to the frame (`fst [esp]`,
`fmul 0.5f`, `fstp [esp+4]`), which is why the retail frame is only 8 bytes.
The compiled candidates spill `w` instead and use a 0x10 frame.

Two further build facts this function needs:

- the pooled `0.5f` literal must be rebound to `0x470B0C`; the cluster's own
  pool currently starts at `0x470B98` for `__real@4f800000`, so `0.5f` lands at
  `0x470B9C`. A `constant_alias` for `__real@3f000000` at `0x470B0C` is the
  existing mechanism for that.
- the cluster layout has to split `.text$06alayout` around 0x00443290 (and the
  section names must sort the function between the 0x00443080 gap and the
  0x00443476 gap; `06a2anchor` sorted before `06a2layout` and put the body at
  the wrong address in the first attempt).

## 0x00443080, the rounded sibling (measured 2026-09-13)

A model of the 515-byte rounded builder was written and compiled: it reaches
421 bytes, 94 short. Its reconnaissance is now complete as well.

| item | evidence |
| --- | --- |
| entry ABI | `ESI` sprite, manager on the stack, `RET 4`; submits through `0x00442670` with mode **1** (the snap bit) |
| rounding | the centre anchors call the CRT: `sub esp,8` / `fstp [esp+14h+X]` / `call _floor` at `0x00452FF0` (the SSE2/x87 dispatcher), result stored back with `fstp` as a float |
| why width spills | the `_floor` call clobbers the x87 registers, so `w` is spilled (`fstp [esp+0Ch+var_C]`) before the height is computed; `h` and `h*0.5f` follow into `var_8`/`var_4` (frame 0xC, plus the per-call 8-byte argument area) |
| case expressions | case 0 right = `left + w`; case 1 right = `base + position + w + offset` (the width is added *before* the offset in the emitted order); case 2 right = `base + position + offset`, with both placement sums recomputed |
| constant | the centre rounding multiplies by the pooled `0.5f` at `0x470B0C`, the same rebinding the sibling needs |

The 94-byte shortfall is structural, not a single site: with fewer live x87
values than retail, the compiler common-subexpressions the placement sums
across cases and merges case tails, where retail recomputes them. Reproducing
this family's sizes needs the same *live-range pressure*, which is what makes
these two bodies resistant to a first source model while the pipeline pair at
0x00442670/0x00442AD0 matched quickly.

Both attempts are preserved: `matching2/build/recovery-lab/anchored1/`.

## Related family status

| address | bytes | state |
| ---: | ---: | --- |
| 0x00443290 | 486 | this note; source model started, not exact |
| 0x00443080 | 515 | calls only `_floor` (x2, bound at 0x00452FF0) and the pipeline; model at 421/515, see above |
| 0x004436C0 | 591 | contains `fsincos`; unreachable from C++ on this toolkit |
| 0x00443910 | 591 | contains `fsincos`; unreachable from C++ on this toolkit |
| 0x00443F80 | 33 | calls 0x00443B60 and the pipeline |
| 0x00443FB0 | 643 | calls 0x00443B60, `__ftol2` (x7) and the pipeline |
| 0x00444240 | 818 | calls D3DXMatrix*/Vec3Project only |
| 0x00444580 | 60 | calls 0x00444240 and the pipeline |
| 0x004445C0 | 402 | calls 0x00444240, D3DXVec3Transform, `__ftol2` (x3) and the pipeline |
| 0x00444760 | 929 | calls Flush (recovered), D3DXMatrix* and 0x004423E0 |
| 0x00444B10 | 201 | no calls at all; a good next candidate |

Everything except the two `fsincos` functions has expressible callees, so the
family is a cluster-sized batch once the first body's x87 discipline is
reproduced.

The experiment copy is at `matching2/build/recovery-lab/anchored1/`; iteration
uses `matching2/build/pipeline-lab/lab.py --names BuildAnchoredQuad` against the
render batch manifest after re-applying the header and manifest changes listed
above.
