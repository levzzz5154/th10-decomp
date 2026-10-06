# Laser cutter family — shared native graph and earlier compiler evidence

The preceding goal turn made progress by recovering both line trim candidates and proving their full parameter-copy behavior. This follow-up made progress through a coherent four-function native graph, a reproducible execution-address fix, 870 passing shared-graph comparisons, and new read-only traces. It added **zero production recovery bytes**. The full readable, byte-matching, inline-assembly-free C++ objective remains active and incomplete.

## Current shared graph

[`semantic_candidates/laser_cutter_family/`](../semantic_candidates/laser_cutter_family/) contains all four complete owners, one shared vector/animation-ID/parameter/interface header, complete genuine helpers, native measurement and safe-link recipes, the bounded fixture runner, dependency audit and source receipts. Both laser classes expose their real rectangle/circle slots at `18`/`1C`; unused slots remain declarations, without invented bodies or a replacement vtable.

The maintained rebuild preserves the individual cutter bodies: rectangle trim 1269 bytes / 13 differing bytes; circle trim 1237 versus 1238 / 876 differing overlap bytes; rectangle split 1171 / 27; circle split 1108 / 433. The shared graph does not make those bodies exact. The normal gates remain the individual candidates' separate evidence: three pass structural checks and fail raw equality, while the circle trim fails its required extent. No shared normal gate or promotion is claimed.

All 870 maintained-fixture cases pass in the actual shared native PE, with the same four observation hashes as the individual builds. They observe 1155 items, 2644 effects and 170 spawned lasers. Owner, item, pool, manager, heap, complete spawned records, call order, return/RET12, preserved registers and x87 state remain within the documented bounded fixture scopes and scripted API boundaries. This does not establish full game behavior or raw equality.

## Execution-address correction

The initial shared build at the usual `00400000` base ran both trim suites successfully. Its splitter then entered a normal emitted instruction at `00402050`, which collided with the fixture's shared Entity-constructor overflow hook. That was a harness address collision, not evidence of a real overflow or a changed cutter behavior.

The maintained `safe_link.py` replays the real `/LTCG` link at `00100000`. Only `/BASE`, output paths and the ordinary sectionless absolute-symbol COFF metadata differ; the compiler and all source IR objects are unchanged. A second native link supplies diagnostic relocation evidence. All 16 emitted function bodies match the original shared build after address binding. The runner maps the actual PE below retail and retains the original shared boundary addresses. No compiler data, register choice or instruction is modified. The maintained execution PE SHA-256 is `306ba516374e2a4aafc2b9ddac89e261e12387118afb8c31d923a11822278ee1`.

## Rectangle trim scheduling

The real current trim link was observed with four hardware breakpoints only. It completed with 764 events across 34 scheduling graphs, and all 1269 traced native bytes equal the uninstrumented contribution, SHA-256 `9ea81a43037389079bf25f84de838f0da986333c64b1064446350650728bab2e` before diagnostic relocation.

At graph 0 cycle 2, cookie store sequence 3 and EBX-save sequence 4 are both ready at priority 102400. The cookie store wins. The size argument load then has priority 124928 and precedes the still-ready save. Retail instead saves EBX and copies the receiver before the cookie store and size load. This is the same current scheduling choice observed in the rectangle splitter; it is not proof of the original IR or a universal compiler limitation.

The full events and proof are saved in `laser_rectangle_trim_0041d880/evidence/scheduler_*`. The fixed-address candidate SHA remains `2576392a69d9d90863ac400dbea0338a1b4e86924a324d80a42cc80923775db3`.

## Splitter zero reuse precedes late flow

The new [`trace_target_flow_link.py`](../compiler_traces/flowgraph/trace_target_flow_link.py) observes the real current rectangle-splitter link at `Riscify`, two `FgDoLateFlowOpts` entries, `FgCodeMotion` and `MscClean`. It uses four hardware breakpoints and completes normally. All 1171 traced native bytes equal the uninstrumented contribution, SHA-256 `c676de1bc5131cbc175f209b80af257121e3432fc943e3b3b08b1fd3b2a7419e` before diagnostic relocation. No tuple or compiler decision is written.

At `Riscify` entry the hit test already compares the hit-count stack symbol against EAX immediately after `MOV 0,EAX`. Before the first late-flow entry, the hit-count load is split into ECX; before the second entry, `MOV 0,EAX` becomes `XOR EAX,EAX`, while `CMP ECX,EAX` remains. The choice to reuse the cursor zero therefore predates these late-flow passes and scheduling. The responsible earlier pass and the original compiler input are still unknown. Full tuples and the proof are in `laser_rectangle_cut_0041eb00/evidence/late_flow_*`.

## Bounded controls and next work

Thirty-three source/build configurations were measured: nine mask/origin placement forms, five origin-copy forms, five spawn-record storage/copy forms, three memory/arithmetic forms, four target-only option forms, one older-compiler graph, four fully visible typed-creator graphs, and two complete-family builds. The best rectangle trim remains 13 differing bytes. None supplies byte-exact code.

Target-only `/G5` and `/G7` additions leave the body unchanged; every translation unit compiled with `/G7` changes the whole graph substantially, so the target-only observation must not be interpreted as a global CPU-option result. The older Toolkit 2003 emits a 1301-byte rectangle trim with 1200 overlapping differences. Fully visible typed creator bodies retain a real public creator root and complete implementation, correcting the earlier declaration-only link experiment. Their best tested circle trim is still one byte short, with 875 overlap differences; their best split has 437 differences against the retained 433-byte residue. All changed options and source controls are rejected as promotion inputs.

The subsequent [earlier compiler investigation](laser_rectangle_split_early_compiler_2026_10_06.md) identifies immediate-candidate extraction, load insertion and allocation as the current splitter zero-reuse mechanism. It preserves four completed traces with whole-code equality proofs, without improving or promoting the candidate. Genuine upstream caller or fuller source-type evidence and the exact dependency/path construction for the shared prologue choice remain useful directions. Do not re-run the late-flow or exhausted source controls as if they were new, patch emitted instructions, fabricate helper bodies, or credit a size match. These bounded negative controls establish no universal impossibility.

## Visible circle trim variant and diagnostic alias

The fully visible typed circle-trim creator improves one differing overlap byte, to 875, and all 236 unchanged trim fixtures pass with exactly the retained circle observations. It is preserved as a separate complete graph under `laser_cutter_family/variants/circle_trim_visible/`. The shared family keeps its original call/inlining choices, so its circle result remains 876. Neither graph is promotable: both emit 1237 bytes against 1238 required. No helper byte-match or normal fixed-address gate is claimed for the alternate.

A supplemental safe-link check found a separate diagnostic binding collision in the alternate's original default-base build: the native allocator entry was `00401DE0`, the same numeric address as the external `Entity_Init` boundary. The old diagnostic binding update incorrectly pointed the allocator call at `00401DE0` rather than `00449950`. Its normalized body is therefore rejected as proof. A fresh complete native build at `00100000` removes the collision and correctly binds the allocator call. Its corrected residue is still 875 overlapping differences, now 58 groups. The current control reproducer uses that non-overlapping diagnostic base. This was a reference measurement/execution issue; retained candidates' fixed-address proofs and production bytes were unchanged.

## Production audit

A fresh authoritative audit reads only layouts named in the current manifest. The complete 487936-byte production EXE still equals the oracle, SHA-256 `2f14760b6fbbf57549541583283badb9a19a4222b90f0a146d5aa17f01dc9040`. All 1483 selected functions in 963 current native layouts retain oracle-matching hashes; 3968 distinct current compiler input files match current reports. All four cutters remain assembly. Exact ordinary C++ stays at 2254 regions / 199062 bytes (61.9%); 60 actual assembly regions / 89245 bytes remain after excluding equivalent owners. Production source, manifest, flags and verifier were not changed by this follow-up, so the current production build was audited without an unnecessary rebuild.
