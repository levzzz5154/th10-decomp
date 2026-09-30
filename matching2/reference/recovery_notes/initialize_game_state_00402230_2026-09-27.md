# InitializeGameState 0x00402230: EXACT 522/522

> Integration status (2026-09-27): the exact routine(s) described here are now integrated in the maintained project. The combined 487,936-byte executable matches retail byte for byte. See [the fourth checkpoint](native_recoveries_2026-09-27_fourth.md) for current proof and remaining work. Scratch-only and promotion instructions below describe the original recovery handoff. Unmatched candidates remain in scratch.

2026-09-27. The complete compiler contribution at 0x00402230..0x00402439 is
recovered as typed readable C++ with a normal native-LTCG probe. Maintained
files were not edited. Only the 522-byte initializer is selected as game code.

Live Ghidra evidence is retained in ghidra_evidence.json. Retail receives state
in EAX, stage-file name in ECX, and state id in one stack dword; it returns an
integer and RET4. The real creation caller at 0x00402693 confirms these homes.
The old D3806 ownership probe was rejected before native compilation.

The model publishes the proper global state pointer, loads the stage resource,
logs failure, copies all 0x118 camera bytes, initializes four vector members,
creates and registers all three scheduler callbacks, resets the frame timer,
sets the active bit, and clears the two state fields. There are no added null
checks or reduced final-state-only substitutions.

The actual recovered StageEclLoader::Load, TextLog::AppendLine and both
scheduler registration bodies serve as compiler-only ABI anchors. Their
complete contributions are 308, 201, 131 and 131 bytes respectively and remain
at their retail addresses. The outer forwarding context is 21 bytes, never
selected as recovered code. The source, driver, and anchor files contain no
inline assembly, naked functions or emitted bytes.

The first full native body had the correct 522-byte extent and exact first
333 bytes, including the private entry, both load/log boundaries, REP MOVSD
camera copy and every CameraVector temporary. It differed in 61 bytes because
of callback store ordering and timer-tail scheduling. Putting context before
the first and third callback flag writes reduced the difference to 36 bytes.
Using ordinary timer stores with compiler memory barriers at the callback/timer
boundary, between lazy defaults and the final reset, and before active-state
publication gave exact 522/522. The barriers preserve all observed preliminary
writes and emit no machine instructions.

Final normal gate: probe_final.json, exact=true, failures=[], different_bytes=0,
relocations=[], instruction_bytes_changed=0, address_operands_changed=0,
masked_bytes=0, reference_bytes_used_for_build=false. Native and retail body
SHA-256: b1046bb3e73ae16e093ab36086f6bbc146a4556df9fa09fc3dd1079e0a5fc191.
The final source has compile-time checks for the timer, frame-limit field,
active flags, after-draw callback, camera position, and complete camera extent.

Copy these six scratch artifacts to their corresponding maintained paths:

- msvc/src/game/initialize_game_state_00402230.cpp
- msvc/layout/ltcg/initialize_game_state_00402230.json
- msvc/layout/ltcg/initialize_game_state_00402230_context.cpp
- msvc/layout/ltcg/stage_anchor_00402230.cpp
- msvc/layout/ltcg/log_anchor_00402230.cpp
- msvc/layout/ltcg/scheduler_anchor_00402230.cpp

Then register the unique layout through the normal register_cluster.py helper.
Selected symbol: _InitializeGameState_00402230@12. Existing manifest symbols
already bind _asm_InitializeGameState_00402230 and its legacy decorated names
to 0x00402230, preserving the assembly caller's fixed-address resolution.
Do not copy the entire scratch regions.json over the live manifest; the parent
must integrate against its current checkpoint. A read-only scratch registration
preview accepts the proposed layout.

Reproduction:

    python3 matching2/tools/matching/probe.py --source src/game/initialize_game_state_00402230.cpp --project matching2/build/experiments/initialize_game_state_00402230_2026_09_27/msvc --output <fresh-output> --json

Baseline and intermediate source/probe snapshots remain beside the final gate.
The ranking accepted before this task is retained separately in
fresh_ranking_evidence.md; no prior verified checkpoint was replaced.
