# Recovery script executor 0040BD80: complete native residual

Status: complete readable model, measured residual, **do not promote**. The entire retail contribution remains selected at 1,568 bytes. The final ordinary MSVC 13.10 LTCG build emits a complete 1,500-byte contribution at the correct address, `0040BD80`, including the 18-entry switch table. The normal production probe rejects the requested retail extent because it exceeds that actual MAP CODE contribution. This is a bounded result, not recovered bytes.

All work is isolated under [recovery_script_executor_0040bd80_2026_09_28](../../build/experiments/recovery_script_executor_0040bd80_2026_09_28/). This task made no maintained source, manifest, or full-build changes. The parent retained responsibility for integration and the maintained checkpoint.

## Fresh evidence and complete model

Fresh reads used `th10.exe` in Ghidra through `/run/user/1000/ghidra-mcp/ghidra-2136235.sock`. [Decompiler](../../build/experiments/recovery_script_executor_0040bd80_2026_09_28/ghidra_decompile.txt), [disassembly](../../build/experiments/recovery_script_executor_0040bd80_2026_09_28/ghidra_disassembly.txt), and [caller xrefs](../../build/experiments/recovery_script_executor_0040bd80_2026_09_28/ghidra_xrefs.txt) are retained. The actual caller is `TickRecoveryState_0040bd20`, calling at `0040BD21`; the executor takes an ordinary stack state pointer and returns with `RET 4`.

The [source](../../build/experiments/recovery_script_executor_0040bd80_2026_09_28/msvc/src/game/recovery_script_executor_0040bd80.cpp) and [header](../../build/experiments/recovery_script_executor_0040bd80_2026_09_28/msvc/include/th10/game/recovery_script_executor_0040bd80.hpp) model the full interpreter. The state is `0xEC` bytes, with command pointer at `+0x54`, flags at `+0x74`, secondary animation handles at `+0x90`, and worker at `+0xD0`. Compile-time assertions check these offsets. Command arguments cover all three accessed words; command advancement uses the stored argument-byte count plus four, not the C++ command size.

The complete model preserves:

- The busy flag guard and input-dependent command-time adjustment.
- All opcode slots 0 through 17, including fallthrough advancement for 1, 2, and unknown opcodes.
- Text decoding, all five ring slots, the null-handle stores, text drawing and wrapping, and stop-frame changes.
- Both wait paths, the negative-duration special case, input and owner gates, modulo-six behavior, sound queueing, ring reset, and the global reset.
- Resource initialization and retirement, all animation creation paths, worker start and early return, and the command cursor advanced before that return.
- Color, music selection, random voice playback, and flag changes.
- Script reload, failure return, full-state clearing, cursor initialization, three timer resets, and continuation without advancing the newly loaded command.
- Both ASCII creation modes, the three game-mode conditions, and the timer update tail.

Two independent semantic reviews passed: the text-helper worker's full-main review and the parent's separate review. They found no missing opcode, guard, wait/input behavior, worker effect, reload effect, global effect, timer-tail behavior, or bad ABI call. These reviews do not establish instruction or byte equality.

## Genuine dependency model

The isolated LTCG cluster includes 31 genuine full helper contributions across 14 anchor translation units. These cover timers; handle lookup, validation, flags, and removal; text decode, formatting, and dispatch; ASCII creation, registration, schedulers, and factories; asset/archive loading; resource clearing, release, and creation; sound queueing; and worker start/stop. The ASCII registration contribution includes its complete switch table. Real leaf edges retain their observed signatures and address bindings.

No placeholder forwarding helper replaces a game callee. No opcode or side effect was removed to force an extent. The unselected synthetic entry context precedes the selected executor at `0040BD70`; its placement allows the real target to remain at `0040BD80`. The gap layout uses actual dependency contribution lengths, while the selected executor retains its original 1,568-byte extent.

[final_anchor_hashes.json](../../build/experiments/recovery_script_executor_0040bd80_2026_09_28/final_anchor_hashes.json) records each of the 31 complete native helper contributions, its actual MAP address and extent, desired retail address, prior retail extent, and SHA-256. Addresses after the shorter executor drift. The file explicitly makes no helper exactness claim.

## Final normal probe and diagnostic

[probe_final02.json](../../build/experiments/recovery_script_executor_0040bd80_2026_09_28/probe_final02.json) is the final canonical measurement. Native compilation and linking completed. The target begins at `0040BD80`, but the normal gate rejects it with:

> function RecoveryScript_Execute extent is outside a MAP CODE contribution

The report has no resolved production units or regions and `exact: false`. Normalization did not complete. The earlier [attempt02.json](../../build/experiments/recovery_script_executor_0040bd80_2026_09_28/attempt02.json) image-base/entry rejection is retained separately; it is not the final result.

| Measurement | Result |
| --- | --- |
| Retail whole contribution | 1,568 bytes |
| Final native whole contribution | 1,500 bytes |
| Extent difference | -68 bytes |
| Raw differing bytes in the 1,500-byte overlap | 1,300 |
| First raw difference | `0040BD82` |
| Native switch table | `0040C314`, included in the 1,500 bytes |
| Retail body SHA-256 | `78414f9d448a6af0d2c2076eefa6f7e6d1c3e8711cbc655a747e6f1b00bb6dda` |
| Native body SHA-256 | `28805d53f85d2db77607f21e9f770088d96674905afffc6d29491e028438c3f6` |
| Native PE SHA-256 | `729db193c191755e52fea1093750a0b2bcbaba18d3926afce1967c2fd737b949` |

The raw overlap metric is diagnostic. It includes differing private parameter/register allocation, shifted call targets, and shifted switch-table entries. It is not a normalized production comparison or a claim that the remaining 200 overlapping bytes are recovered. [measured_residual.json](../../build/experiments/recovery_script_executor_0040bd80_2026_09_28/measured_residual.json) records offsets, source/dependency hashes, gate status, and review status. The complete [native body](../../build/experiments/recovery_script_executor_0040bd80_2026_09_28/native_executor_final.bin), [retail body](../../build/experiments/recovery_script_executor_0040bd80_2026_09_28/retail_executor.bin), and [native disassembly](../../build/experiments/recovery_script_executor_0040bd80_2026_09_28/native_executor_final_disassembly.txt) are retained.

The build uses readable C++ and ordinary native LTCG. It uses no inline assembly, naked function, emitted oracle instruction bytes, fake register anchor, instruction rewrite, address-operand rewrite, or comparison mask. These are build/comparison-method facts; they do not imply a completed normalizer report.

## Separate validated ABI correction

Fresh executor evidence exposed the real `00449450` return contract: `EAX` carries the animation object or null, and the instruction at `0040BEAC` moves that result into `ESI` for the text call at `0040BEAE`. The previous maintained validation source and layout described a void return. A complete truthful helper model was independently probed and reviewed with an explicit `__cdecl` pointer-return member, preserving its plain `RET` ABI. Its entire 21-byte contribution remained exact; default member calling convention instead produced a wrong `RET 4` shape.

The correction evidence, five-file proposal, and final exact normal probe are retained in [validate_return_correction](../../build/experiments/recovery_script_executor_0040bd80_2026_09_28/validate_return_correction/), with the separate [correction note](animation_validate_handle_return_correction_00449450_2026-09-28.md). The parent independently reviewed and integrated that correction, then reported the combined maintained full build still exact at 487,936 recovered bytes. This is a source/ABI correction to an already recovered 21-byte body; it adds no executor recovery bytes.

## Concrete next leads

The strongest next lead is genuine variadic caller topology for `MarkText_00447A50`. In this reduced cluster LTCG promotes color to `EBX` and drops the unused manager argument, leaving only the format on the stack and spilling the executor loop counter. Retail pushes all three fixed arguments and retains the loop count in `EBX`. [Fresh xrefs](../../build/experiments/recovery_script_executor_0040bd80_2026_09_28/ghidra_mark_text_xrefs.txt) contain 13 calls: three in this executor and ten in genuine callers `00415E90`, `00419120`, and `00433EF0`. Co-compiling those authentic complete callers could constrain the real variadic ABI; no substitute caller or fake anchor has been attempted.

The other lead is the actual by-value animation-handle return and temporary lifetime model. Native uses 16 bytes of local slots; retail uses 12 and reuses the incoming argument slot for the opcode-eight output record. The current explicit output-pointer helper model has authentic complete callee semantics. Fresh evidence and complete caller validation are needed to determine whether a real return-record representation explains the lifetime and frame difference.

The earlier emitter decision remains a separate 111-byte residual. The requested shared-full-Tick-type variant was tested in the old scratch's isolated `shared_type_variant2`; it left decision 111 bytes/48 differences, wrapper 10 bytes exact, and Tick 93 bytes exact. The old canonical scratch and note were preserved. That lever is now measured, not pending.
