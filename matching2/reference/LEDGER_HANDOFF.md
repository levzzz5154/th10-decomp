# Non-semantic ledger handoff

This directory contains an unfinished ledger snapshot produced during the
recovery session ending at commit `bd115ee`. It is committed as work in
progress for continuation in ChatGPT Web, not as the current authoritative
accounting.

## Authoritative checkpoint

- Manifest: `matching2/msvc/regions.json`
- Manifest SHA-256: `20b26bdbcafb1aa22bf4054a3ea66515fb228999133ea3d2ccb74d3932b2895d`
- Whole executable: exact across 487,936 bytes
- Semantic C++: 429 regions / 22,150 bytes
- Assembly: 2,156 regions / 366,832 bytes
- Embedded `.text` data: 25 regions / 8,157 bytes
- Padding: 1,817 regions / 15,533 bytes
- Total non-semantic: 3,998 regions / 390,522 bytes

The current `non_semantic_regions.json` and `non_semantic_regions.md` still
describe the immediately preceding manifest snapshot, whose SHA-256 begins
`0bc6c4e5`. They therefore include the now-semantic regions at `0x0043D790`
and `0x0044D4E0` and report totals that are high by two regions and 161 bytes.

## Continuation task

Refresh both ledger files from the current manifest while preserving their
evidence-backed categories. Remove `0x0043D790` and `0x0044D4E0` from the
recoverable-assembly inventory, update the snapshot hash and accounting, and
reference `recovery_notes/platform_tail_cluster_0043d790_0044d6a0.md` as the
promotion evidence. Do not classify failed semantic candidates as irreducible
assembly merely because their current compiler probes differ.

After refreshing, validate that every current `kind != semantic` manifest
region appears exactly once and that category totals equal 3,998 regions and
390,522 bytes.

## Measured 2026-09-15: four `semantic` regions still hold naked assembly

Scanning the current manifest against the maintained sources (every
`__declspec(naked)` definition whose name matches a region symbol) finds four
regions that are classified `semantic` while their unit still defines the
naked body, so `make progress` counts them as ordinary C++:

| region | bytes | source | symbol |
| --- | ---: | --- | --- |
| `0x00407560` | 305 | `src/game/enemy_motion_steps.cpp` | `_asm_FUN_00407560_00407560` |
| `0x004127A0` | 593 | `src/game/spell_timer.cpp` | `_asm_FUN_004127a0_004127a0` |
| `0x00418D40` | 237 | `src/game/stage_tip_manager.cpp` | `_asm_StageTipManager_Construct_00418d40` |
| `0x0042ACB0` | 274 | `src/game/score_file.cpp` | `_asm_ScoreFile_InitializeDefaultsRetail_0042acb0` |

Each entry carries an `asm` record in `previous_record`, i.e. the semantic
classification was written without the source following it (the `_retail`
suffix on the last one shows the body is deliberately still assembly). Either
the sources get their C++ back or the four entries should be reverted to
`previous_record` with `matching2/tools/waves/repair_units.py`. Either way the
ledger refresh must not assume `kind == semantic` implies a C++ definition:
1,409 bytes of the reported ordinary C++ are inline assembly today.
