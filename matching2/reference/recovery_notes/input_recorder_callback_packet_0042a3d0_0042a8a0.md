# InputRecorder callback 0x0042A3D0 and ordinary packet append 0x0042A8A0

The actual 10-byte InputRecorder scheduler callback is reproduced by ordinary C++ with the complete real InputRecorder update graph. The existing 85-byte packet append owner is reproduced by typed record stores and a normal moving cursor, removing its volatile cursor/stores and synthetic array context. This adds 10 semantic bytes; the packet's 85 bytes were already selected and add no recovery credit.

## Real boundaries and behavior

The scheduler registration function at 0x00428F60 stores 0x0042A3D0 in task callback fields at 0x00429154 and 0x00429390. The callback receives the genuine recorder context in ECX, forwards `recorder->Update()`, and returns its result. Native LTCG emits the literal complete callback `57 8b f9 e8 f8 f3 ff ff 5f c3`: it saves EDI, transfers ECX to EDI, calls 0x004297D0, restores EDI, and returns. The compiler derives the update's private EDI receiver from this real call graph.

The complete update handles live input, the rapid-shot threshold, key-repeat update, one sampled analog byte every 30 frames, input packet append/page rollover, and indexed playback with real input/sample cursors and per-stage consumed counts. It returns 1 on each path. The shared key state uses the actual 16-bit held/previous/press/release fields, including the true four-byte held/previous union used by the packet call. The replay input record is six bytes, containing three 16-bit fields. The pool cursor at +0x5460 advances by one whole record after writing the three fields; the helper reports whether the resulting record count reaches 3600. Native LTCG derives the original packet boundary from the real update call: receiver EAX, first word DX, two stack words, EAX result, RET 8.

The independent complete six-byte AppPresent scheduler callback at 0x004200C0 is the schema 1 linker entry. It receives the real task context and returns 1. It makes no call into the recorder graph. The actual address-escaped recorder callback is a selected public root, keeping its ECX callback boundary. The graph has no synthetic caller, argument, register-pressure variable, volatile access, inline assembly, barrier, byte patch, or mask.

## Ownership and strict proof

Selected source owners are only:

- `src/unidentified/FUN_0042a3d0_0042a3d0.cpp`: complete callback10 at 0x0042A3D0.
- `src/game/recovery_append_packet_0042a8a0.cpp`: complete ordinary append85 at 0x0042A8A0, preserving its existing semantic extent/credit.

The maintained ASM update owner596 at 0x004297D0 is unchanged. Its complete ordinary 596-byte model is an unselected ABI anchor. KeyRepeat109 at 0x0040AC20 and AppendPage139 at 0x0042AA50 are complete unselected graph helpers; their existing independently selected owners are unchanged. AppPresent6 is unselected. No context, dependency, anchor, literal, padding, or gap receives recovery credit.

The new layout replaces `layout/ltcg/recovery_append_packet_0042a8a0.json`, whose old standalone driver explicitly described a synthetic array caller. The replacement schema 1 layout uses the real graph and independent actual callback entry. Constants used only by the unselected update are pooled naturally; no float address aliases or recovered data are exported.

Fresh split-TU production-path proof is `matching2/build/experiments/input_recorder_2026_10_02/package_final_probe.json`. Both selected source probes report EXACT, with complete literal extents callback10 and packet85, zero masks, zero instruction/address-operand edits, and `reference_bytes_used_for_build: false`. `frozen_evidence.json` independently compares each full native contribution with the oracle: KeyRepeat109, AppPresent6, callback10, packet85, and AppendPage139 are literal exact. The callback's unmodified native call target is 0x004297D0. Native MAP contributions validate each complete function's original address and size.

## Bounded main-update investigation

The first complete genuine graph emitted Update582. Grounded analog saturation (`rounded >= 256`, else byte conversion) and positive-stage fallthrough controls produced592. Direct held-key assignment produced the complete596, with47 differing bytes confined to 0x004297F1..0x00429832; every byte from the KeyRepeat call through the rest of the complete function matched. A raw-key snapshot ordering control and an ordinary byte-input rapid-shot inline member both retained the same596/47 result. The investigation stopped there.

The remaining live-prefix difference is the compiler's natural register/scheduling choice: native raw input EAX and settings ECX versus retail raw input ECX and settings EAX, with associated byte/word instructions. The final unselected context has53 differences because six naturally pooled float-address bytes also differ. The update is neither selected nor truncated, and receives zero semantic credit. Complete-case geometry, hashes, native artifact paths, and the narrow region proposal are frozen in `frozen_evidence.json` and `integration_proposal.json` under the same lab.

## Maintained whole-EXE verification

Fresh maintained probing and the incremental whole-EXE gate both pass. The rebuilt executable is literally identical across all 487,936 bytes, SHA256 `2f14760b6fbbf57549541583283badb9a19a4222b90f0a146d5aa17f01dc9040`. This batch adds 392 asm-free bytes: initializer382 and callback10; Packet85 cleanup adds zero credit. Verified asm-free totals are 2,108 selected regions / 139,352 bytes (43.1255% of 323,131 project-owned bytes). Six mixed semantic bodies still contain 4,525 assembly bytes and are excluded from that total. The build reused 1,605 units, compiled four, and extracted 150 library members. Full current input hashes and complete native contributions are independently checked in `whole_verification.json` in both experiment directories.

The final one-source maintained probe is `matching2/build/experiments/input_recorder_2026_10_02/maintained_probe.json`; it checks both selected bodies and avoids the earlier two-source report-path overwrite. Its native artifacts and all current input hashes match the independent full-contribution comparison.

## Update at 0x004297D0 resolved 2026-10-05

`InputRecorder_004297D0::Update` is byte-exact (596 bytes), lives in
`src/game/input_recorder_update_004297d0.cpp` and is selected in this cluster;
`make` and `make EXACT=1` pass. The earlier candidate had the masked key word
in EAX and the configuration flags in ECX (retail: ECX and EAX). The hold
counter is incremented through a named local
(`unsigned short frames = held_frames + 1; held_frames = frames; if (frames >= 8)`),
which makes the counter a register candidate that outranks the key word and
takes EAX. The two float literals are bound to 0x00470B0C and 0x00470C34.
