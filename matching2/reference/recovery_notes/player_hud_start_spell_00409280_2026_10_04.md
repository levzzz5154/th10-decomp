# HUD spell-card start at 0x00409280 — exact ordinary C++

The complete 2,432-byte region now passes the unmasked retail byte gate and has
ordinary C++ production ownership in `msvc/src/game/player_hud_start_spell_00409280.cpp`.
Its SHA-256 is `0a83aa9fdaa2f24183fe8bbb08caee04a6978631c0afba823a2dfcba7acf493e`.
The gate includes the code, alignment, and all seven entries of the 28-byte
stage-switch table. The native private ABI is panel, index, name, and duration
on the stack, followed by RET 16.

The same cluster selects the complete 118-byte primary-back registrar at
0x004489D0 from its maintained render source. Its unchanged retail SHA-256 is
`39e1aaf20ccc6f0c90ef9a2ae5bac14f89797203148cadca4365fa49502f9c22`.
Both functions belong to `layout/ltcg/player_hud_start_spell_00409280.json`.
Complete native callees and an unselected compiler-context caller provide the
LTCG scope; those context functions are not additional recovered ownership.

The implementation counts capped attempts, copies the spell name, loads the
panel sprites, creates and registers its animations, sets the duration and
bonus, and selects the stage-specific frame, label, and animation scripts.
It uses the established ScoreManager/ScoreRecordSection/ScoreSpellRecord layout,
including the manager prefix and all 110 spell slots.

The final compiler-sensitive arrangement remains ordinary readable C++:

- The first panel-name copy uses explicit local input and output cursors in the
  routine.
- The aggregate-name helper keeps its input pointer values constant and advances
  separate local cursors.
- PanelAppearance carries the render bucket and animation flags, both of which
  are consumed during object setup.
- AnimationRef equality takes its four-byte operand by value. The reference-returning
  prefix increment still reproduces the registrar's nonzero-ID sequence.

Read-only compiler traces identified the former one-byte SIB difference in
FactCanonSort. The complete source arrangement above fixes that difference
without inline assembly, compiler barriers, volatile accesses, artificial
padding, masked comparisons, or compiler-output rewriting.

Verification completed after production promotion:

- The fresh production probe reports EXACT for both complete functions.
- The archived probe repeated against the promoted workspace reports EXACT for
  both functions.
- `make -j2` passes. Direct reads of the normal executable verify both complete
  target contributions against retail.
- `make EXACT=1 -j2` passes. An independent `cmp` verifies all 487,936 executable
  bytes against the retail executable.

Fresh reports and retained normal/EXACT build artifacts are under
`build/experiments/spell_goal_2026_10_04/exact_production_probe`,
`exact_archive_after_promotion`, and `exact_completion`. Current input hashes,
tool hashes, ownership records, and build results are recorded in the companion
`player_hud_start_spell_00409280_2026_10_04_evidence.json`.

The previous assembly owner, equivalent model, and separate registrar cluster
are preserved under `reference/semantic_candidates/player_hud_start_spell_00409280/before_exact_promotion`.
StartSpell no longer has an equivalent-recovery entry or an assembly fallback.
The project's three unrelated equivalent recoveries remain unchanged.
Current coverage is 2,202 exact ordinary C++ regions / 168,711 bytes (52.6% of
application bytes), with 62.3% of bytes and 95.0% of regions recovered including
those three equivalent models. This spell-start recovery goal is complete.
