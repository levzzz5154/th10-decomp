Resolved update: all four animation registrars now have complete exact ordinary C++ implementations. Primary-front and secondary-front each passed their 112-byte native gates after initialization through the entity link array view; their synthetic single-object contexts establish EBX for the entity. Both complete executable builds pass, and the EXACT executable equals retail. Historical failed controls below remain diagnostic evidence only. See the individual registrar recovery notes and evidence JSON files.

Production update: secondary-back was integrated on 2026-10-04 using a separate 97-byte synthetic creation loop. Both builds pass and the complete EXACT executable equals retail. The historical altered-spell-card experiment below was superseded; that modified game body was never promoted. See `animation_register_secondary_back_00448ac0_2026_10_04.md` and its evidence JSON.

# Animation registrar sibling experiments, 2026-10-04

The typed `AnimationRef` increment/equality used by the exact primary-back registrar also reproduces the secondary-back registrar at `0x00448AC0`: all 118 native PE bytes compare directly equal to retail, with zero masks. This is an isolated candidate, not a production promotion.

Evidence: `matching2/build/experiments/registrar_siblings_2026_10_04/secondary_back/standalone_probe/clusters/player_hud_start_spell_00409280/report.json` and `secondary_back/raw_region_proof.json` under the same experiment directory. The disposable project and complete compiler outputs are preserved there.

The experiment changes the spell-card routine to call the secondary list solely to obtain compiler context. That altered body is an unselected anchor in the passing isolated probe; it is not recovered game code and must not replace the exact production spell-card routine. Integration should use a separate explicitly synthetic context or a real secondary-list caller, then reverify both ordinary and EXACT builds.

Primary-front currently compiles to 94 bytes rather than 112: the compiler removes the branch testing the newly cleared node link, and places the entity in EDI rather than EBX. Its ID-increment sequence otherwise matches retail. `front/probe7` preserves that native output. No production source, header, manifest, or build artifact was changed by these experiments.
