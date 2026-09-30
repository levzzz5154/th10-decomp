# Native C++ recoveries, 2026-09-27

Latest checkpoint: see [the addendum](native_recoveries_2026-09-27_addendum.md) for nine more integrated routines and current progress totals.


This batch replaces thirteen complete retail routines, totaling 1,894 bytes,
with readable C++ without inline assembly. All thirteen pass the matching
probe against the retail executable, including every relocation target.
Both full-executable rebuilds passed across all 487,936 bytes. The final
build includes the naming/comment corrections; all 3,851 recorded project
input hashes agree with the current tree. A direct byte comparison of the
built executable and stable retail oracle also passes.

| Address | Bytes | Recovered operation | Compile route |
| --- | ---: | --- | --- |
| `0x004127A0` | 593 | Spell timer slot advance | Native LTCG, public receiver |
| `0x00415E30` | 93 | Guarded script-state timer tick | Native LTCG, private receiver |
| `0x0041E4D0` | 226 | Oriented rectangle contact test | Ordinary C++ |
| `0x0041F670` | 226 | Oriented rectangle contact test twin | Ordinary C++ |
| `0x0041F8D0` | 82 | Front/bullet startup resource loading | Existing logger LTCG cluster |
| `0x00437160` | 157 | Image alpha transform | Ordinary C++ |
| `0x0043DDB0` | 52 | Queue a sound-effect stop | Native LTCG, private registers |
| `0x00448E30` | 73 | Primary-front animation creation | Existing front LTCG cluster |
| `0x00448F60` | 73 | Secondary-back animation creation | Native LTCG |
| `0x00448FB0` | 95 | Positioned secondary-back creation | Native LTCG |
| `0x00449090` | 73 | Secondary-front animation creation | Native LTCG |
| `0x004490E0` | 95 | Positioned secondary-front creation | Native LTCG |
| `0x0044C200` | 56 | Start a worker thread suspended | Existing worker LTCG cluster |

Before the batch the manifest classified 1,607 semantic regions / 70,333
bytes and 1,171 assembly regions / 318,765 bytes. The current manifest
classifies 1,620 semantic regions / 72,227 bytes and 1,158 assembly regions /
316,871 bytes. The embedded data and padding totals are unchanged. Counts
are region classifications. Three existing semantic render bodies also
retain inline assembly: `sprite_quad_submit.cpp`,
`sprite_quad_submit_mirrored.cpp`, and `projection_quads.cpp`. This batch
does not establish completion of the full asm-free decompilation goal.

Live Ghidra MCP decompilation, disassembly, xrefs and bounded memory reads
were used to verify layouts, entry conventions, call sites and complete
retail bodies. Evidence and source experiments are retained under
`matching2/build/experiments/`. Normal probes select complete compiler
contributions without instruction rewrites or masked bytes. Native compiler
contexts and ABI anchors are excluded from recovered-code counts.

The major source changes are the typed spell timer and clock reset, the
float-conversion wrapper controlling the contact test's x87 lifetime, the
packed alpha bitfield with a shared successful return, and reuse of the
existing animation creation/registration contexts. The spell timer's
`_ReadWriteBarrier` controls store scheduling without emitting instructions.
Its globals and default speed are typed symbols rather than raw offsets.

Two fresh near misses remain assembly: the 81-byte player flag clear swaps
ECX/EDX across eleven bytes, and the score-list tick emits 272 bytes instead
of 274. Their current candidates and residuals are documented separately.
Eight resolved entries were removed from the deferred-blocker queue.

Detailed notes: [spell timer](spell_timer_advance_slots_004127a0_native_ltcg.md),
[contact tests](oriented_rect_hit_test_0041e4d0_0041f670_exact.md),
[image alpha](image_alpha_transform_00437160.md),
[startup resources](native_startup_resources_0041f8d0.md),
[sound stop queue](native_stop_queue_0043ddb0.md),
[primary front](native_primary_front_creator_00448e30.md),
[secondary back](native_secondary_back_creators_00448f60_00448fb0.md),
[secondary front](native_secondary_front_creators_00449090_004490e0.md),
[script timer](recovery_tick_state_00415e30.md),
[suspended worker](worker_start_suspended_0044c200.md),
[player flag residual](player_clear_flags_00405500_cluster.md), and
[score-list residual](score_record_list_tick_0041c330.md).

## Final whole-image gate

Command: `make MSVC_ARGS='--jobs 8 --verify matching2/build/oracle/th10.exe'`.
All 2,250 build units succeeded. The build validates every byte of the linked
`.text` and packaged executable, with no masked bytes or instruction rewrites.
The retail image is used only for verification, not as a build input.

- Executable: 487,936 bytes, SHA-256
  `2f14760b6fbbf57549541583283badb9a19a4222b90f0a146d5aa17f01dc9040`.
- `.text`: 412,672 bytes, SHA-256
  `c1acff416da826334c29a19fa89cd7a094626eb36c32afe7950f705a55f56998`.
- Manifest SHA-256: `cbd1f2a7f2d7a2a3da11d8610609a02bca4cf062fb7e8fde28e74ada7cd865cb`.
- Machine audit: `matching2/build/experiments/native_recoveries_2026-09-27_verified.json`.
- Build report: `matching2/build/msvc/port-report.json`.

A separate review checked all thirteen selected sources and their relevant
headers/contexts for inline assembly, naked functions and encoded instruction
data; none were found. Ghidra plate comments were updated and saved for the
nine recovered heads that have function objects in the live program. Four
other heads retain the bounded disassembly/memory evidence used for their
recovery. The full decompilation goal remains active.
