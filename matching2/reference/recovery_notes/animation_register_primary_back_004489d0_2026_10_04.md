# Primary-back animation registration at 0x004489D0 — exact C++

The complete 118-byte registrar remains ordinary C++ in
`msvc/src/render/animation_manager_register_primary_back_004489d0.cpp`.
Its production cluster is now `msvc/layout/ltcg/player_hud_start_spell_00409280.json`,
which also selects the exact 2,432-byte spell-card start routine.
Both complete native contributions pass the unmasked retail gate.

The private ABI remains manager EDX, entity EBX, hidden handle output EAX,
and RET. Its retail SHA-256 remains
`39e1aaf20ccc6f0c90ef9a2ae5bac14f89797203148cadca4365fa49502f9c22`.
The former assembly symbol remains a static address alias for existing callers.

AnimationRef stores an unsigned 32-bit ID. Its prefix increment returns a
reference; equality takes the other four-byte handle by value. The registrar's
`++next_id; if (next_id == 0) ++next_id;` reproduces the retail increment and
zero-guard sequence without barriers, volatile accesses, assembly, or byte edits.

The fresh production probe and archived replay report EXACT for both functions.
Both normal and EXACT builds pass after the shared-cluster promotion. The normal
executable's full registrar and spell-start contributions equal retail, and an
independent cmp confirms the EXACT executable matches retail in full.
See `player_hud_start_spell_00409280_2026_10_04.md` and its evidence JSON for the
current combined ownership and build proof. The prior separate-cluster note and
evidence are preserved in the spell candidate's `before_exact_promotion` archive.
