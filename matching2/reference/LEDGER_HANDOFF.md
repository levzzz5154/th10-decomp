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
