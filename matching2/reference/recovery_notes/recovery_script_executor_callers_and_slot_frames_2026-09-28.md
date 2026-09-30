# Full executor callers and exact animation slot frames

Maintained integration is complete after independent review and exact normal probes. The sixth checkpoint matches all 487,936 retail executable bytes using all 3,964 current project inputs. Five existing Ghidra Function annotations were saved and read back. Proof: `matching2/build/experiments/native_recoveries_2026-09-28_sixth_verified.json` and `native_recoveries_2026-09-28_sixth_ghidra_verified.json`.

The isolated experiment recovered two complete routines as readable C++: ClearAnimationSlot at `0042C6D0` (83 bytes) and SetSlotFrame at `0042C770` (65 bytes). The final renamed normal native LTCG probe is **EXACT for all 148 original bytes**, with no comparison masks, instruction changes, address-operand changes, or reference instruction bytes used to build. The scratch phase changed no maintained inputs; parent integration, independent review and the combined maintained build subsequently passed.

Canonical package: `matching2/build/experiments/recovery_script_executor_callers_2026_09_28/animation_slot_gate`.

- Final normal report: `probe_final.json`; selected proposal: `proposal_final.json`.
- Reviewable ownership and copy delta: `promotion_delta.json`, SHA256 `e80d9107ce9fd37f89d9380d565b232e9c8ecf85f88f9c5f55c509682c0466c8`.
- Input and copy verification: `handoff_verification.json` (PASS; 37/37 native inputs and all 28 explicit copy-file hashes verified; 36 C++/header inputs scanned for asm/naked/_emit).
- Selected source: `msvc/src/game/recovery_animation_slot_frames_0042c6d0.cpp`, SHA256 `752abccd40b03e52a310422802c8d4ff2391096f35711e2884159ba0d970995a`.
- Final layout: `msvc/layout/ltcg/recovery_animation_slot_frames_0042c6d0.json`; compiler context: matching `_context.cpp`.
- Native report: `probe_final/clusters/recovery_animation_slot_frames_0042c6d0/report.json`, SHA256 `f9b1b196a5a73104eb924727fedf17226d26651b2cf94302a09b26e08fade9b1`.
- Normal body object: matching `bodies.obj`, SHA256 `b7b526d7d9246662adfbd169b01462c93be0126196384b7a68ac28d44a720db4`.

| Whole selected routine | Bytes | Differences | Native and retail body SHA256 |
| --- | ---: | ---: | --- |
| ClearAnimationSlot `0042C6D0` | 83 | 0 | `0d6e3e8759d10d2da14b9ca78364f3e54d701d8395a3969daac7d78be4caa1ab` |
| SetSlotFrame `0042C770` | 65 | 0 | `33528c282e0bc1d2a97126db07dd28db662ec38b56c50dabb1414d8e70695b7a` |

Clear looks up the stored animation handle, sets the found object's stop frame to 1, and updates every child when `children_flagged == 0`. It clears the stored slot even when lookup returns null. Set performs the same conditional object/child frame updates with the supplied unsigned 16-bit frame and leaves the handle stored. The full genuine 73-byte lookup model remains co-visible; its body independently matches SHA256 `fc3dd480f30c27aa9dcf4168de57e19933d0125f22f6df88a09cc2d792ad69e9`. The two selected routines retain all null, child-list, frame-width, and slot effects.

Independent source/ABI review by `validate_return_correction` passed against fresh Ghidra disassembly and whole native/retail bodies for 83, 65, and lookup73. That review covered the first exact gate. The final rename and explanatory comment changes were recompiled and passed the final exact gate above. The separate parent-assigned final artifact/ownership/source review passed.

The ownership delta preserves each complete original maintained record as `new_record.previous_record`. The original 83-byte owner is `src/game/recovery_clear_animation_slot_0042c6d0.cpp`; the original 65-byte owner is `src/render/fun_0042c770_0042c770.cpp`. Both new selected records use `src/game/recovery_animation_slot_frames_0042c6d0.cpp`. Parent must apply only those reviewed semantic records under the manifest lock before registering the unique new cluster, retaining original previous records, aliases, and old unselected input files. The delta supplies only the intended 28 source/layout/context/header copies, two symbols, one translation unit, and one cluster; it is not a scratch-manifest replacement.

The compiler context contains complete executor and caller models, including their actual native extents, plus genuine full dependencies. They remain unselected and contribute zero promoted bytes. The synthetic typed context is also unselected and contributes zero promoted bytes. All three large models were independently reviewed for their complete semantics: all 18 interpreter slots and tails, all indicator queue effects, and all music-room phases, parser, row, input, BGM, and exit effects.

## Complete caller and executor measurements

The canonical baseline retains the original whole selected extents in `msvc/layout/ltcg/recovery_script_executor_0040bd80.json`. Fresh Ghidra evidence and complete sources are retained in `caller_419120_evidence`, `caller_433ef0_evidence`, `companion_anchor_evidence`, and `text_sibling_evidence`. Both complete callers and all new full helper models passed independent semantic review. The baseline has 47 genuine full helper anchors; none is counted as recovered merely because its length equals retail.

The final baseline `probe_final.json` rejects the entire original 1568-byte executor extent because its actual MAP CODE contribution is 1500 bytes. Normalization did not complete for this baseline. `measured_residual.json`, `final_anchor_hashes.json`, `final_layout_calibration.json`, and the complete native/retail binary and disassembly files retain the diagnostic results. The layout calibration records actual ancillary contribution sizes rather than extending their metadata to original sizes. Raw overlap differences include shifted addresses and private ABI allocation and are not a completed production comparison.

| Complete routine | Original bytes | Native bytes | Requested / actual head | Raw overlap differences |
| --- | ---: | ---: | --- | ---: |
| Executor `0040BD80` | 1568 | 1500 | `0040BD80` / `0040BD80` | 1300 |
| Indicator queue `00419120` | 1317 | 1340 | `00419120` / `004190E0` | 1202 |
| Music room `00433EF0` | 2796 | 2748 | `00433EF0` / `00433ED0` | 2579 |

The corresponding complete native hashes are executor `787bb4b12cf23704c560e4e389dff1ac29be6b0ab4c225716eb34c6412764dde`, indicator `53d98f7595e9f38a16145d21cdc51deec0b1a6c7e35770cc64d88057b70ae6c5`, and music room `e20f2abba221ac5052e4d3ad40379786af238eefae10b94450edc71f8592b1f9`. Each first raw difference is at offset 2. These are complete bounded models, not shortened stand-ins.

The final exact pair package uses the complete variadic caller models as unselected context with measured native lengths executor1500, indicator1343, and music2764. Its successful 148-byte gate does not promote those unmatched original extents.

## Whole helper gates and variadic model

`helper_gate/probe_final03.json` completed the normal selected-body gate at the intended heads for the four complete helper bodies. Existing maintained movement `0041AB70` is still exact for 136 bytes; player animation creation `00448DB0` measures 44 differences over 118 bytes; right-aligned text `00447AE0` measures 115 over 204 bytes; centered text `00447BB0` measures 104 over 194 bytes. These probes used zero instruction/address changes. No new helper is promoted from that gate.

The genuine member variadic MarkText model represents the three fixed stack arguments seen at retail calls and retains the music-room call's extra `index + 1` payload. Formatting, font defaulting, all dispatcher arguments and effects, and the dirty flag remain complete. Mutable format-buffer arguments are explicitly converted to `const char*` in the final copied context so their variadic type matches the model. No missing argument, opcode, or side effect is used to obtain a shorter body.

`marktext_gate/probe_final.json` completed the normal gate for the whole original 141-byte MarkText routine: 21 differing bytes, first at `00447A8F`, native SHA256 `617865b3b629b9769d1a6a91cc68d3136ac5329db4ed403e6bb0397d0cd7db42`. Instruction and address changes are zero. Its residual and complete native body are in `marktext_gate/measured_residual.json` and `native_marktext_final.bin`. This is a semantic source representation to measure, not proof of the original declaration.

The 21-byte residual follows the full text dispatcher's private ABI allocation: native uses colour in EBX and text on the stack; retail uses text in EBX and colour on the stack. The complete typed resource-member dispatcher variant retains every signed guard, conversion, full six-stack-argument draw call, and side effect. `dispatch_member_variant/probe02.json` completed the MarkText gate but retained the same 141/21 result; the full dispatcher is native127/original125 and remains unselected. All baseline and bounded variants are preserved, including explicit compile or gate failures; no exact result is claimed for the dispatcher, MarkText, executor, or callers.

## Next concrete evidence

The fresh sole indicator caller at `00419650` is a genuine 571-byte routine that can provide the actual EAX receiver context for `00419120`. The remaining large real MarkText caller `00415E90` is 4480 bytes and supplies additional diverse real text calls. A future attempt should recover these complete callers or a lawful complete dispatcher ABI representation, rather than source spelling sweeps or fake abbreviated context. The executor's by-value animation handle temporaries also warrant checking against the actual 12-byte retail versus 16-byte native local layout. None of these leads changes the bounded results above.

The old executor1500/1568 experiment, emitter111 residual experiment, and maintained global Tick signature remain untouched. The independently exact `00449450` pointer-return correction is already owned by the parent and is not part of this 148-byte delta.
