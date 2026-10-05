# Codex handoff — 2026-10-05, user-requested pause

The full-decomp goal is paused. Claude resumed work in this shared tree around
19:30. No commits were made; preserve the existing uncommitted work. User's
latest matching preference: **prioritize byte-exact C++; use equivalence only
when absolutely necessary**.

## Byte-exact recoveries added after that preference

1. `0x00411FC0`, ECL integer resolver:
   `msvc/src/script/ecl_integer_value_00411fc0.cpp` and matching native layout.
   Strict probe: 820 bytes EXACT (616 code + 204 generated switch table).
   Both full `make` and `make EXACT=1` passed after integration.
2. `0x00412350`, ECL float resolver:
   `msvc/src/script/ecl_float_value_00412350.cpp` and matching native layout.
   Strict probe: 884 bytes EXACT (679 code + 1 alignment + 204 generated table).
   Both full gates passed after integration. This is the last fully gated
   checkpoint: 72 asm regions / 101,325 bytes remaining.
3. `0x00415B00`, stage score-display constructor:
   `msvc/src/game/stage_score_display_00415b00.cpp`, its header, context, layout
   and manifest ownership are integrated. Strict native probe: 683 bytes EXACT.
   **Full gates remain outstanding.** Shared-tree make failed in the concurrently
   edited parser cluster (`_ReadLine@16` shifted to 0x419F50). Those parser edits
   were not reverted. An isolated full build was stopped on the user's handoff
   request after reporting 1100/1677 sources and **one unresolved failure**;
   it must not be described as passing. All my build processes were terminated.

Current manifest reports 71 asm regions / 100,642 bytes, but the constructor's
full-image integration is not yet fully gated. No new equivalence registrations
were added for these three recoveries. The ECL tables were merged into their
complete compiler contributions, so reported semantic-byte totals/denominators
also incorporate the old table/alignment bytes.

Detailed notes:
- `ecl_value_dispatchers_00411fc0_00412750.md`
- `stage_score_display_00415b00_2026_10_05.md`

## Resume constructor validation

Strict scratch project: `/tmp/codex-stage-slot/msvc`.
Probe artifacts: `/tmp/codex-stage-slot/probe` (EXACT).
Shared build failure: `/tmp/codex-stage-slot/make.log`.
Interrupted isolated build: `/tmp/codex-stage-slot/make-isolated.log`.
Output/cache: `matching2/build/experiments/stage_score_display_00415b00_2026_10_05/full-build`.
`/tmp/codex-stage-slot/full-build` is a symlink to that workspace directory.
It was moved because /tmp is almost full; preserve other processes' scratch.

Resume the isolated build if useful:

```sh
make MSVC_ARGS='--project /tmp/codex-stage-slot/msvc --output /tmp/codex-stage-slot/full-build'
make EXACT=1 MSVC_ARGS='--project /tmp/codex-stage-slot/msvc --output /tmp/codex-stage-slot/full-build --exact'
```

Once the shared parser is restored or recovered, run both full gates in the
shared tree. Last known exact EXE SHA-256 (after both ECL recoveries):
`2f14760b6fbbf57549541583283badb9a19a4222b90f0a146d5aa17f01dc9040`, 487,936 bytes.

Constructor matching facts: normal C++ ctor (no calling-convention annotation
needed); three timer constructors clear flag bits before memset; public external
InitializeObject member ABI; full genuine private helper bodies as context;
copy script IDs by value for lookup rather than reconstructing them; region
vector assignment after the field/color initializations. Region extent is 24,
not legacy model's 25. Null lookup still leads to retail's subsequent faulting
layer write. The caller's older separate cluster still uses its previous
stand-in constructor; replacing that context with this complete body is future
cleanup, not something already validated here.

## Earlier work retained

Before the user tightened equivalence preference, six equivalent recoveries
were integrated and fully gated: MIDI tick 43AF30, replay frame step 42A3E0,
camera shake 43C550, animation change script 43E8B0, font atlas text 437FE0,
and WAVE loading 43D390. Existing equivalences now total 9 / 33,860 bytes.
Each has a `*_equivalent_2026_10_05.md` review note. Differential checks passed
for font rendering (3528 cases) and native WAVE loading (396 comparisons).

The pending hit-test equivalence promotion was explicitly stopped. The unused
verifier extent extension and tests were removed from the worktree and parked
at `/tmp/codex-hit-equivalence-parked`. Production equivalence.py is unchanged
from HEAD. Hit-test exact probes and findings are in `/tmp/codex-hittest` and
`player_hit_test_004059f0_2026_10_05.md`.

Claude's earlier parser checkpoint was preserved at
`reference/semantic_candidates/stage_tip_parser_00419960/`, including an isolated
strict reproduction. This is historical evidence, not a replacement for Claude's
new edits. It has a 1498-byte parser with 571 differing bytes and an exact reader.
