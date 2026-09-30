# Complete MarkText and text dispatcher: exact 268-byte handoff

**Maintained integration verified, 2026-09-28.** The seventh checkpoint integrates these complete routines, passes the maintained normal probes, and reproduces all 487,936 retail bytes with all 4,005 current project inputs audited. See [the seventh checkpoint](native_recoveries_2026-09-28_seventh.md) and `matching2/build/experiments/native_recoveries_2026-09-28_seventh_verified.json`. The scratch handoff below is historical; its pending parent gates are now complete. Its pre-integration text is archived under `native_recoveries_2026-09-28_seventh_handoff_notes/`.

The complete text dispatcher at `004479D0` (127 bytes) and MarkText at `00447A50` (141 bytes) now match every original byte in the normal native LTCG gate. `final/probe_final02.json` reports EXACT268, two complete selected contributions, no failures, zero masked bytes, zero instruction changes, zero address-operand changes, and no reference instruction bytes used to build. Parent integration and the combined maintained build remain separate gates. This agent changed no maintained inputs.

Canonical scratch: `matching2/build/experiments/marktext_dispatcher_2026_09_28/final`.

- Final normal probe and resolved proposal: `probe_final02.json` and `proposal_final02.json`.
- Reviewable delta: `promotion_delta.json`, SHA256 `36f545de3c026402f197b2154aa6ee15ef63f423e2166e0af19303c68dc77f75`.
- Input verification: `handoff_verification.json` (PASS; 38/38 native input hashes, all 38 explicit copy hashes, 37 C++/header inputs scanned for asm/naked/_emit). Every destination path is new.
- Selected source: `msvc/src/game/recovery_mark_text_and_dispatcher_004479d0.cpp`, SHA256 `24cde331d358f2d537207fa1272b5a5278667f2f7b2c7e3aad73ffc233b72bf9`.
- Header: `msvc/include/th10/game/recovery_mark_text_and_dispatcher_004479d0.hpp`, SHA256 `c1da04d9d3d4956f0d2091f9a685f57e9f73eee41e0c45123d49fdebbf1f7a39`.
- Layout: `msvc/layout/ltcg/recovery_mark_text_and_dispatcher_004479d0.json`; compiler context: matching `_context.cpp`. Genuine full unselected sources and headers use unique `marktext_dispatcher_context` paths.
- Native report: `probe_final02/clusters/recovery_mark_text_and_dispatcher_004479d0/report.json`, SHA256 `ce14ee298a38f6e30564413be06e8b55647fa7c278afba00a686bb4daec53825`.
- Normal body object: matching `bodies.obj`, SHA256 `538b2b781ef65035bbde14e3aa149590feb99dbe447d94777c4dff18cdd6a5bd`.

| Complete selected routine | Bytes | Differences | Native and retail SHA256 |
| --- | ---: | ---: | --- |
| Dispatcher `004479D0` | 127 | 0 | `ebc74019a72477110c4e2015aa06ca902aa9facc0c978a7739a0d4a7bc2c464a` |
| MarkText `00447A50` | 141 | 0 | `ecc6b27f52517c22cb8f0fe41a22f81e225334f0efaa2537407bbaea52840bc9` |

## Fresh contract and complete semantics

Fresh Ghidra disassembly, xrefs, and boundary bytes are retained in `fresh_evidence`, with independent parameter lifetime analysis in `abi_evidence_text_helpers` and complete draw-result evidence in `draw_result_evidence`. The dispatcher has exactly three actual callers: MarkText `00447A50`, right-aligned formatter `00447AE0`, and centered formatter `00447BB0`. Each supplies resource in EDI, font height in EAX, text in EBX, and texture/horizontal offset/color/mode in four stack homes. The dispatcher returns with RET16. It retains text and resource through the four FP conversions, caches color in EBP, and performs left/top/right/bottom conversions in that order before the chosen real drawing call.

The grounded ordinary C++ parameter tuple is `(resource, texture, horizontal_offset, font_height, color, text, unshadowed)`, following the actual drawing arguments. All three genuine complete caller models pass that tuple coherently. This corrected the previous native text-stack/color-EBX allocation without forced registers, shortened helpers, or instruction edits. The historical source declaration remains unproven; the full measured C++ representation and resulting private ABI are exact.

The dispatcher retains both signed font guards: nonpositive becomes 17; positive 1 through 8 returns. It preserves all four reads/casts and both full six-stack-argument draw calls. Fresh complete draw tails prove RET24 and an unsigned EAX result: zero for a null surface, otherwise the final COM Release count. The final source declares those draw results truthfully and ignores them. All three callers ignore the dispatcher result. The exact native dispatcher also preserves the actual retail EAX outcomes, including the incoming height on the early return; the historical intended return type is not inferred from that incidental retained value.

MarkText retains its 128-byte buffer, font-byte read before formatting, actual input homes represented with `va_list`, every formatting payload passed to real vsprintf, color read from its retained home after formatting, mode/resource/texture loads, complete dispatch, and post-call dirty flag reload/update. The complete music-room caller still supplies the locked-track `index + 1` variadic payload. Mutable format buffers are explicitly passed as `const char*`; the complete indicator caller retains its real manager-global reload after drawing. Independent fresh semantic review of the final source/header hash snapshot passed all guards, conversions, formatting arguments, global reloads, effects, and three caller contracts. Parent artifact/source/ownership review is separate and pending at handoff.

The earlier 125-byte dispatcher label was incorrect. Fresh bytes put the final RET16 at `00447A4C` (`C2 10 00` through `00447A4E`) and padding CC at `00447A4F`. The authoritative maintained ASM record and whole original extent are 127 bytes. The previous full native dispatcher therefore had 127/127 with five argument-home/register differences, not a size residual. No original extent has been truncated.

## Ownership and bounded context

The delta proposes only these two original regions. It preserves the complete original dispatcher record owned by shared `src/game/recovery_leaves.cpp` and the complete original MarkText record owned by `src/game/recovery_mark_log_state_00447a50.cpp` as each new record's `previous_record`. Parent should apply only these reviewed semantic records under the manifest lock before unique cluster registration, preserving every other shared-source selection and alias. The delta lists 38 new source/header/context/layout paths, two symbols, one translation unit, and one unique cluster. It never copies a scratch manifest or overwrites the existing exact148 slot-pair cluster inputs. The already recovered 83+65 pair remains unselected context and is not counted again.

`complete_context_measurements.json` retains all 50 complete selected/anchor contributions and their hashes. Complete selected and major unselected native/retail binaries and disassemblies are retained. Only127+141 are promoted by this proposal; the following original routines remain unmatched full context:

| Complete unselected routine | Original / native bytes | Actual head | Raw overlap differences | Native SHA256 |
| --- | --- | --- | ---: | --- |
| Executor `0040BD80` | 1568 / 1500 | `0040BD80` | 1257 | `4660cd40fd5cc24b13f863e0902b77137a136a4a321b804b3750d754f86c149b` |
| Indicator queue `00419120` | 1317 / 1343 | `00419120` | 1198 | `252d6827fef3593337d79e7b517b50aede1e43f92b9a6469366f7127eeaf3aee` |
| Music room `00433EF0` | 2796 / 2764 | `00433EF0` | 2590 | `f87fc73f2ce0d96310e89fac6ff3540dd61698da9c6ea60b8c9e2b4035a7c139` |

These are full-body raw diagnostics, not completed selected-body comparison claims for those originals. Their original extents remain unchanged. The interpreter still contains all 18 operations, waits/input, worker, reload, global effects, and timer tail; its native1500 contribution remains too short for the original1568 gate.

The separate complete result-bearing dispatcher representation is retained in `result_contract_variant`: native135/original127, full MarkText141 at the shifted native head `00447A60`. Its normal probe rejected the entire dispatcher contribution; `measured_residual.json` records 108 raw dispatcher overlap differences and 24 raw MarkText differences, with normalization incomplete. It is not promoted. Initial orchestration failures in `draw_order_variant/probe01` and `probe02` are also retained distinctly. The successful draw-order representation and final clean gates resolve them without changing scope.

The main executor1568 and whole executable remain the original recovery goal. The exact MarkText/dispatcher now provide proven callee behavior for subsequent complete executor work. Its remaining state/register and by-value handle local-layout differences are the next grounded dependency; the genuine `00419650` indicator caller and full `00415E90` text caller remain additional complete caller leads. All previous experiments and the maintained global Tick signature are preserved.
