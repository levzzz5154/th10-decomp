# Adjacent record geometry and retained precision, 2026-09-28

Neither selected function is exact or promoted. The final complete native adjacent sweep is **578 bytes against original 585**, and the point sweep remains the identical old **368 bytes against original 370**. Both original addresses and extents remain selected. The calibrated normal probe rejects `EffectRecordAdjacentSweep` because its declared 585-byte extent is outside the actual MAP CODE contribution; it does not reach a successful point-sweep gate. All measurements here are unpromoted diagnostic evidence.

The isolated experiment is `matching2/build/experiments/effect_record_adjacent_context_2026_09_28/`. No maintained source, manifest, tool, or previous experiment was edited. Final inputs are frozen in `probe11_palette_calibrated_inputs/`; `sha256.json` identifies every declared source/header/driver/layout input. The final adjacent source SHA-256 is `3f078b336b95eed6b51f92e5258cd57e596d4104e52982483f84a27b15c3057b`; header SHA-256 is `3723c9b97ba0651b0ddc53cb86eaa2f61c619c9d9ab9f1633e879970e1fa6ec6`.

## Fresh original evidence and genuine boundaries

Fresh connected Ghidra MCP reads and bounded full-byte disassembly cover all 585 bytes at `00408210` (149 instructions) and all 370 bytes at `004084A0` (126 instructions), without truncation. `fresh_full_body_comparison.json` verifies the five full memory reads against the oracle, including 819-byte allocator `0041BB00`, 118-byte creator `00448DB0`, and 73-byte lookup `004491C0`. Original adjacent SHA-256 is `db89521d8d41ed987a728bfa2b80ff10e772c908a085a5347b6a8964de1d8559`; original point SHA-256 is `5aa3899c37e8865763cde5c7cb04970e5c3d2dea1445d1d4879ee4a0aa04e39c`. Oracle SHA-256 is `2f14760b6fbbf57549541583283badb9a19a4222b90f0a146d5aa17f01dc9040` (487,936 bytes).

The adjacent routine now has a valid Ghidra function head. The point routine's decompile response still says `No function found`; its whole bounded instruction/memory evidence remains usable. Actual adjacent callers are the ECL dispatch branches at `00410D19` and `00410DE8`, inside the **14,416-byte** routine `0040E770`. They load owner global `004776F0` into EBX and push the flag 1/0, discarding the result. No shortened dispatcher stand-in was compiled. No direct maintained point-sweep caller was found; that does not prove absence of an indirect caller.

The retail adjacent ABI is owner EBX, one stack flag, integer EAX return zero, `RET 4`. The point ABI is owner ECX, point EDI, radius on the stack, integer EAX return, `RET 4`. The full creator uses position EDI, three stack arguments and `RET 0Ch`; lookup uses context EDX, stack ID and `RET 4`, with an unused member receiver. Native compiler artifacts, rather than source declarations alone, determine actual emitted ABI.

Record layout remains stride `7F0`, owner array at `60` with 2,000 records, position at `3B4`, width/height at `3F0/3F4`, resource at `39C`, state at `446`, timer at `450`, signed palette index at `7EC`, and owner animation resource at `3E0B50`. Owner center/dimensions are real three-component values at `44/50`.

## Representation changes and complete results

The genuine copied graph includes complete allocator, all-segment/bounded line callers, animation creation/allocation/registration/loading/configuration, and lookup bodies. Its synthetic context publishes the complete line-method addresses and invokes the complete bounded caller plus both geometry methods. The context is explicitly synthetic and is not recovered ECL code. The polar dependency uses ordinary C++ cosine/sine, not an inline-assembly FSINCOS stand-in. No function was shortened to its selected extent.

Owner bounds use complete three-component constructor temporaries and legal copies, retaining otherwise dead Z arithmetic. The final per-record model uses initialized 12-byte lower/upper objects, with volatile lower X/Y, upper Y, and shared half-height to express the observed binary32 stores. The four negated rectangle exclusions accept unordered values. Ordered descriptor thresholds choose the small/medium/large palette with NaNs reaching the final palette. The main call boundary now passes an actual canonical `Vector3` to shared typed `Spawn`, and an actual `AnimationScriptId` through the opaque output interface.

| Native trial | Adjacent full extent / 585 | Point full extent / 370 | Adjacent literal overlap differences | Status |
|---|---:|---:|---:|---|
| probe04 | 576 | 368 | 313 | Pre-review type/lifetime issues; diagnostic only |
| probe05 | 576 | 368 | 313 | Byte-reading creator experiment; context entry rejected |
| probe06 | 656 | 368 | 349 | Full aggregate per-record copies; context entry rejected |
| probe07 | 582 | 368 | 339 | Selective scalar homes; half-height still extended |
| probe08 | 592 | 368 | 92 | Typed selective-rounding objects; context entry rejected |
| probe09_calibrated | 592 | 368 | 92 | Original adjacent full contribution rejected |
| probe10_palette_shared | 578 | 368 | 110 | One shared signed-index lifetime change; context entry rejected |
| probe11_palette_calibrated | 578 | 368 | 110 | Same source, synthetic entry only calibrated; original full extent rejected |

The first three setup probes failed before yielding a valid complete native result. Their JSON failures are retained. The table's differences are unmasked literal overlaps from whole contributions, not normalized exact gates. `measured_adjacent_graph.json`, `measured_palette_shared_trial.json`, and `measured_palette_calibrated_trial.json` retain image/MAP/probe/body hashes and complete per-function extents. Every native body is in its matching `*_complete_sections/` directory with a full disassembly.

Final calibrated native dependencies, all at their original addresses, are configuration 204/original202, loading 203/203, registration 114/118, creator 111/118, allocation 165/161, polar 30/30, allocator 823/819, all-segments 601/609, bounded-segments 623/623, lookup 73/73, and synthetic context 129 bytes at `00449A20`. Loading, bounded-segments, and lookup have literal whole-body diagnostic equality in this context. They have no new selected normal-gate or promotion claim. Final adjacent body SHA-256 is `49820fc7aa9be53ac6c059f1f274fb5060deefa3ae043e8bc54575f415c8bd73`; final point body SHA-256 is `5734a467b22d25adb93d490640c33e1fadf3913df9ce920b8b3cf59874566b9a`, unchanged from the old 368-byte body.

## Measured remaining differences

The typed selective-rounding model reproduces the original `3Ch` frame and owner-bound temporary/copy schedule. Across the bounded per-record interval, **25 of 27 complete FP/LEA instructions match at unchanged addresses**. The two failures occupy one ten-byte region: retail `00408324 FLD [ESI+3B8]` then `0040832A FSUB [ESP+8]`; native `00408324 FLD [ESP+8]` then `00408328 FSUBR [ESI+3B8]`. `final_geometry_and_palette_comparison.json` retains both actual byte sequences and `all_equal: false`. Equivalent finite arithmetic is insufficient to establish matching FP exception/NaN behavior or bytes.

The previous 592-byte source loaded the signed palette index independently in all three arms. Retail loads it in the small arm at `004083F3` and once before the medium/large branch at `00408411`. The single authorized new source change shared the index in the second-threshold path. Native LTCG instead hoisted **one** load at `004083E6` into EDX before the first threshold, reused it in all three arms, kept the animation result in EDI, and shortened the full body by 14 bytes to 578. The presumed seven-byte residual was therefore not removed in isolation: that source lifetime affected register allocation and hoisting across the first threshold as well.

The handle/lookup schedule also differs: retail loads the returned ID into EDX and pushes it before loading lookup context; native loads ID into EAX, loads context EDX, then pushes EAX. The next source lever for the adjacent sweep must account for this actual animation-result and palette-index lifetime/register relationship, while retaining the second-threshold-only shared index and position-Y-first subtraction. A further constructor spelling or generic aggregate sweep is not supported by this result.

## Finite point-sweep precision counterexample

The unchanged 368-byte point model pops and reloads the rounded left-top Y before adding height. Retail at `004084F2` stores left-top Y without popping, then adds height to the still-live extended value. This is a real value boundary, not merely a register naming difference.

`finite_rounding_witness.py`/`.json` derive a finite input using exact rationals under round-to-nearest-even. With position Y `42A003D1`, height `3F000959`, position X zero, width two, point X minus one, point Y `42A083DA`, and radius zero, retail left-bottom Y is `42A083DA`; rounded reload yields `42A083DB`, one binary32 ULP higher. One active state-1 record with descriptor value eight and 1,999 inactive records yields **retail count 1 versus old model count 0**. This is instruction-derived arithmetic, not runtime execution of the game. Independent read-only review recomputed every reported corner/distance and found a maximum exact significand requirement of 37 bits, so the decisive witness arithmetic fits x87's stated 64-bit significand precision.

The next point-sweep representation must distinguish a retained working extended Y from its stored binary32 corner copy. Merely reloading the corner or substituting a mathematically simplified expression demonstrably changes the decision. All four genuine 12-byte corners and the complete distance/control contribution remain required; no extent, mask, shortened helper, inline assembly, uninitialized Z, or byte patch is authorized by this evidence.

## Independent review and handoff limits

`independent_review.json` records the independent read-only review and source hashes. The three corrected adjacent boundary/lifetime issues and initialized temporary components passed review, together with the ordered/unordered threshold semantics and finite witness. The copied graph is **not globally certified as portable C++**: unrelated `LineSweepStep`/`LinePolarVelocity` views remain in the all-segment and bounded callers; `SpawnItem` is viewed as `ItemConfiguredEntity` in the allocator; and the bounded caller indexes a float pointer obtained from `Entity.position.x` beyond that individual subobject. Exact copied file/line locations are retained in the review. These inherited contexts must be resolved before any lawful full-graph promotion claim.

All compiler sessions are terminal. Final source and explicit inputs are frozen; complete original selectors remain 585 and 370. There is no maintained change, whole-image gain, new exact geometry function, or promotion candidate in this handoff.
