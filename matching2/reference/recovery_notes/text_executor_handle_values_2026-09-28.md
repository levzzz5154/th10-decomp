# Text executor handle values: bounded full native measurement

Status: **residual, no promotion**. The complete executor at `0040BD80` remains selected at its original 1,568-byte extent. The final ordinary MSVC 13.10.6030 LTCG build emits 1,540 bytes, including all 18 switch slots and their table. Compilation and linking complete, but the normal selected-body gate rejects the original extent because it extends outside the actual MAP CODE contribution. No production regions resolve and normalization does not complete.

This continuation owns only [text_executor_handle_values_2026_09_28](../../build/experiments/text_executor_handle_values_2026_09_28/) and this new note. It changes no maintained source, layout, manifest, tool, or previous experiment. The maintained seventh text pair (127 + 141 bytes) and sixth animation-slot pair (83 + 65 bytes) remain preserved and are not counted again.

## Fresh evidence and structural representation

Fresh full [executor disassembly](../../build/experiments/text_executor_handle_values_2026_09_28/fresh_evidence/executor_disassembly.txt), [decompilation](../../build/experiments/text_executor_handle_values_2026_09_28/fresh_evidence/executor_decompilation.txt), and [xrefs](../../build/experiments/text_executor_handle_values_2026_09_28/fresh_evidence/executor_xrefs.txt) came from `th10.exe` in Ghidra instance 2136235 through `/run/user/1000/ghidra-mcp/ghidra-2136235.sock`. The genuine Tick caller at `0040BD21` passes one ordinary state pointer; the executor ends with `RET 4`.

[Handle evidence](../../build/experiments/text_executor_handle_values_2026_09_28/handle_value_evidence/README.md) and [stack-slot calculations](../../build/experiments/text_executor_handle_values_2026_09_28/handle_value_evidence/stack_slots.json) establish that handles and script IDs are four-byte integer records. Registration at `004489D0` writes an ID to the output slot and returns that slot's address. The typed graph therefore retains explicit four-byte output slots; it does not invent a hidden structure return, padding, constructor, or destructor.

With `S` denoting entry ESP, retail creation outputs use `S+4` (case 8, the incoming state-argument slot), `S-12` (case 15), `S-8` (case 16), and `S-4` (case 17). The native models use `S-16` for case 8 and the same other three slots. Retail reserves 12 local bytes; all measured native variants reserve 16. In case 3, retail retains the cursor in EDI and loop count in EBX. Native retains an additional initial handle-array base in EBX, uses EDI as the cursor, and spills the loop count to `S+4`. These allocations are observed; the claim that the counter spill causes the extra local remains an inference because their lifetimes are disjoint.

The complete output graph types all sixteen animation handles as the same four-byte record and adapts genuine registration, primary and positioned creation, lazy resource creation, player creation, indicator, and music callers. Handle-owned Resolve removes an unused lookup-manager receiver. Context-owned SetFlag passes its actual lookup context with one by-value ID. Complete helper bodies and every caller operation remain present. The executor retains all 18 opcode slots, guards, waits and input behavior, text operations, worker effects, reload/global effects, and timer/FP tail.

## Four bounded normal probes

Every terminal probe selects the full original executor extent of 1,568 bytes. The initial baseline layout precheck rejection is retained separately as `baseline/probe01.json`; moving the following gap to the original executor end made the normal baseline reach the genuine contribution gate. No requested function extent was shortened.

| Complete model | Terminal normal report | Native extent | Raw overlap differences |
| --- | --- | ---: | ---: |
| Current seventh baseline | [baseline/probe02.json](../../build/experiments/text_executor_handle_values_2026_09_28/baseline/probe02.json) | 1,500 | 1,261 |
| Handle-owned Resolve and record ID | [handle_member_id_variant/probe01.json](../../build/experiments/text_executor_handle_values_2026_09_28/handle_member_id_variant/probe01.json) | 1,500 | 1,271 |
| Complete typed explicit-output graph | [typed_outputs_variant/probe01.json](../../build/experiments/text_executor_handle_values_2026_09_28/typed_outputs_variant/probe01.json) | 1,540 | 1,287 |
| Context-owned SetFlag, final | [context_owned_flag_variant/probe01.json](../../build/experiments/text_executor_handle_values_2026_09_28/context_owned_flag_variant/probe01.json) | 1,540 | 1,295 |

All four reports reject with `function RecoveryScript_Execute extent is outside a MAP CODE contribution`. The 40-byte native size change is a measured structural effect, not evidence of closer byte equality. Raw metrics include shifted helper calls and switch-table addresses from the different layout geometry. They are diagnostics only and are not directly comparable as normalized progress.

The second variant's full SetFlag has two genuine ABI differences: ID at `ESP+8` rather than `ESP+4`, and `RET 8` rather than `RET 4`, because an unused receiver remained. Those were not call-address differences. The final context-owned representation resolves both and emits all 66 bytes identically, SHA-256 `9668434bd5037d2784407a0c27a697d5ca2ff03d8dff1d8cfe112ae02b584e36`. SetFlag is already maintained semantic code in `src/render/animation_manager.cpp`; this result is context evidence, not a new recovery or ownership proposal. Full Resolve also has zero raw differences across its 21 bytes and preserves the maintained pointer-return correction; it likewise adds no recovered bytes.

## Canonical final artifacts

[handoff_residual.json](../../build/experiments/text_executor_handle_values_2026_09_28/handoff_residual.json) identifies the final source, header, gate, diagnostic, and unmeasured caller. [measured_residual.json](../../build/experiments/text_executor_handle_values_2026_09_28/context_owned_flag_variant/measured_residual.json) records actual native extents and heads, original extents, hashes, and all exclusions. The complete [native executor](../../build/experiments/text_executor_handle_values_2026_09_28/context_owned_flag_variant/native_0040bd80.bin), [retail executor](../../build/experiments/text_executor_handle_values_2026_09_28/context_owned_flag_variant/retail_0040bd80.bin), and [native disassembly](../../build/experiments/text_executor_handle_values_2026_09_28/context_owned_flag_variant/native_0040bd80.disassembly.txt) are retained.

| Artifact | SHA-256 |
| --- | --- |
| Final complete executor source | `e717e6b763f5739478ac66068f7ed752ebd5717fe1d9abdabeed4d249b14df0e` |
| Final context header | `6f6ca9097649cf941d3e281262ff1c2c34a1031242371bc37011ebf086c213d6` |
| Native executor, 1,540 bytes | `51f3a12f2fe61c1ff7d5b3ca6e6995cef7f9d73517c88f94351df3c543827ba1` |
| Retail executor, 1,568 bytes | `78414f9d448a6af0d2c2076eefa6f7e6d1c3e8711cbc655a747e6f1b00bb6dda` |
| Final normal report | `62abe1d065713f259720db76443264e4b7cf8fc3c43025169e40bee3862abb80` |
| Final diagnostic JSON | `d95b632549c2e9273409cf5c25784f63523eec9e46d592d15e14601c38e29541` |

The final native contribution starts at `0040BD80`; its first raw difference is offset 2, the frame allocation. The complete unselected indicator Drain context emits 1,343 bytes against original 1,317, and the complete music context emits 2,748 against original 2,796. Neither is promoted. Unselected dispatcher and MarkText retain their full 127/141-byte extents; raw differences in this residual PE reflect shifted heads and call operands, not a replacement for their maintained exact normal probes.

The frozen executor source inherits an earlier first-line comment saying it has not been compiled. That comment is stale: this continuation compiled the complete source in all terminal native probes. The actual reports and artifacts above establish its measured status; the source is left frozen to preserve its recorded hash.

The final independent [read-only audit](../../build/experiments/text_executor_handle_values_2026_09_28/final_semantic_review.json) passed the complete-body, SetFlag ABI, contribution-gate, and residual claims. It confirmed all 18 opcode outcomes, both final SetFlag call changes, and the 38 post-probe input hashes. It made no edits or probes and retained the address-drift and stale-comment caveats.

Compiler and linker logs, PE, MAP, and objects remain under `context_owned_flag_variant/probe01/clusters/text_executor_handle_values_0040bd80/native-aaeizhqr/`. The diagnostic retains a **post-probe** snapshot of 38 declared input hashes and an assembly-free scan of 37 source/header files. Because the contribution gate stops resolution, these are not a completed normal-report input stamp. Builds use no inline assembly, naked function, fake register anchor, emitted oracle instructions, instruction rewrite, address-operand rewrite, or comparison mask. No helper is selected or promoted based only on a raw diagnostic.

## Complete genuine 571-byte next caller

A new full [indicator update source](../../build/experiments/text_executor_handle_values_2026_09_28/caller_00419650_model/source.cpp), [header](../../build/experiments/text_executor_handle_values_2026_09_28/caller_00419650_model/header.hpp), and [evidence handoff](../../build/experiments/text_executor_handle_values_2026_09_28/caller_00419650_model/evidence/handoff.json) model the entire original 571-byte function at `00419650`. Its current maintained ASM owner is `src/game/stage_focus_fade.cpp`. A separate logical semantic review passed for queue selection and release, owner reset, all ten lookups, invalid-ID clearing, opacity-lock guard, three ordered fade regions, signed wrapped coefficient, alpha stores, counters, and return 1. **No native probe has been run for this caller**, so its private receiver allocation, x87 materialization, extent, and byte equality remain unverified.

Fresh retail evidence shows its state in EBX, queue-head receiver in EAX at the real `0041967C` call to complete Drain `00419120`, stack arguments state/release, and plain RET/EAX=1. Player coordinates plus 224/16 remain live in x87, with observed float32 spill points for absolute Y difference, half width, and half width plus 32. The complete ordinary source is a concrete next experiment, not proof of those allocations.

Next action: co-compile this genuine 571-byte caller with the complete original 1,317-byte Drain and corrected text tuple, preserving both original selected extents. Trace the real EBX state/EAX queue head and x87 spills. The current 1,343-byte Drain would overlap the retail caller head by 15 bytes if both heads were forced to their original addresses; retain any truthful layout or whole-contribution rejection rather than truncate either body. Separately investigate case 3's extra initial-base lifetime and state-argument-slot reuse. Do not infer hidden structure return or pad the handle from the 16-byte frame.

Recovered-byte delta for this continuation: **0**. Full executor recovery and the whole-image goal remain open.
