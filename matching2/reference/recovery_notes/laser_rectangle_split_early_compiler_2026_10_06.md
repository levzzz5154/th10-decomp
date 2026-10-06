# Rectangle splitter — immediate candidate and allocation evidence

This continuation made diagnostic progress: it identified the compiler mechanism behind the rectangle splitter's remaining zero-register reuse. It recovered **zero production bytes**. The complete readable, byte-matching, inline-assembly-free C++ objective remains active and incomplete.

## What the trace establishes

The retained complete `0041EB00` candidate still emits 1171 bytes, with 27 differing bytes in four groups. Thirteen differences concern the shared cookie/save prologue schedule. The other fourteen concern the hit-count test and cursor initialization: retail tests the loaded hit count against itself and initializes the cursor afterward; the candidate initializes EAX first and compares the hit count against that register.

Four ordinary `/LTCG` link replays observed earlier lowering, global allocation, immediate extraction and register decisions. Each used four hardware breakpoints, completed normally and made no compiler-data writes, instruction patches or forced allocation decisions. All **4096 emitted code-section bytes**, including all 1171 selected-function bytes, equal the unobserved native build. The selected native-body SHA-256 remains `c676de1bc5131cbc175f209b80af257121e3432fc943e3b3b08b1fd3b2a7419e`.

At `dop2_Codegen`, before lowering, the hit comparison has a literal zero. The lowered comparison still has that literal at `dop2_GlobalRegAlloc` entry. `CmdIdentifyImmedCandidates` then replaces its zero, the cursor-initialization zero and subsequent comparison zeros with one virtual constant symbol. `Enterloads` inserts a pseudo load for that symbol near function entry. Allocation and spilling split/rematerialize its lifetime; the final observed `ChoosePhysReg` decision for the shared zero selects physical EAX. At `Riscify` entry, `MOV 0,EAX` immediately precedes the hit-count comparison, and its result supplies the cursor initialization. Previously observed late-flow passes turn that move into XOR and retain the register comparison.

The evidence therefore identifies the current constant extraction/allocation mechanism. It does **not** establish the original source, original IR or a universal inability to compile matching code. Virtual register numbers before `Riscify` are recorded with their symbol pointers and must not be mistaken for physical register assignments.

## Symbols and reproducibility

Microsoft's matching public PDB has GUID `{5360F7BD-AFB5-4288-A53F-1FBE04D63911}`, age 2. The compiler is independently fingerprinted as `7a6f6d8e4da7b518384ff78f2c41028805d3a1d1a40dc2cc857c391ec81763f5`. [`map_c2_publics.py`](../compiler_traces/symbols/map_c2_publics.py) verifies the PDB identity and applies OMAP stream 10 to the original section addresses. Direct public-symbol offsets are unsuitable for this optimized compiler image. The downloaded PDB and complete symbol map remain ignored build inputs; their origin, hashes and relevant mapped addresses are preserved in the evidence.

[`evidence/early_compiler/`](../semantic_candidates/laser_rectangle_cut_0041eb00/evidence/early_compiler/) contains all events, commands, complete-code equality proofs, a summary of the relevant tuples, symbol provenance and a hash receipt. Reproduce from the repository root after rebuilding the retained candidate:

```sh
python3 matching2/reference/semantic_candidates/laser_rectangle_cut_0041eb00/measure.py rectangle_current
python3 matching2/reference/compiler_traces/flowgraph/trace_target_early_link.py matching2/build/experiments/laser_circle_cut_native_2026_10_06/rectangle_current/commands.json matching2/build/experiments/laser_circle_cut_native_2026_10_06/rectangle_current_immediate_trace CutRectangle immediate
python3 matching2/reference/compiler_traces/verify_target_trace.py matching2/build/experiments/laser_circle_cut_native_2026_10_06/rectangle_current matching2/build/experiments/laser_circle_cut_native_2026_10_06/rectangle_current_immediate_trace matching2/reference/semantic_candidates/laser_rectangle_cut_0041eb00/layout.json matching2/build/experiments/laser_circle_cut_native_2026_10_06/rectangle_current_immediate_trace/proof.json
```

Use the `early` and `global` profiles for the other tuple snapshots. [`trace_target_globals_link.py`](../compiler_traces/regalloc/trace_target_globals_link.py) takes the same first three arguments and observes allocation decisions. The `ChoosePhysReg` breakpoint is 180 bytes after its entry, at the established chosen-register observation site; it is not a replacement implementation. `CmdSpillImmedBytes` has a different state layout, so its records preserve raw state rather than interpreting it as a normal allocation candidate.

## Four rejected controls

The [control recipe](../semantic_candidates/laser_rectangle_cut_0041eb00/evidence/rectangle_immediate_controls.py) copies the complete genuine graph to ignored build storage and measures it at `00100000`, avoiding the known diagnostic address-alias issue. Returning `hit_count` early at the no-hit branch produces 1187 bytes / 477 differing overlap bytes; doing so at both early exits produces 1187 / 479. These match the already rejected literal-return results and provide no improvement.

Target-only size optimization produces a 956-byte contribution and an unbound new floating constant. Disabling global optimization produces 1265 bytes and a separately emitted, unbound vector constructor. Both complete native links succeed, but diagnostic relocation correctly rejects the new references; no overlapping-byte score or normal-gate success is claimed. The controls are evidence only. The retained source, production flags, ownership manifest and verifier remain unchanged.

The next useful investigation is the genuine upstream source graph or the constant lifetime/spill decisions that cause the zero load to remain before the hit test. Repeating late scheduling or these rejected controls does not address that remaining uncertainty. The separate prologue residue still has the documented scheduler dependency/priority evidence.
