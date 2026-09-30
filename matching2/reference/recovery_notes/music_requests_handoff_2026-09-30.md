# Music request handoff recovery

Claude's interrupted handoff left Music_Load's LTCG extent at 118 while its authoritative region owns 120 bytes. Corrected the extent to 120 and moved the following compiler-layout gap to 0x00420B08 (248 bytes through 0x00420C00). The synthetic driver extent must also track the complete compiler contribution after address-taking roots are added.

Retained native C++ Music_Load (0x00420A90, 120 bytes) and Music_Stop (0x00420C00, 41 bytes). The cluster probe verifies these plus RegisterResource (0x0043E460, 104 bytes) EXACT.

Music_FadeOut (0x00420C30, 84 bytes) remains assembly. Restored its saved original source and translation-unit membership rather than crediting an unmatched C++ implementation. Candidate saved at reference/semantic_candidates/music_requests_fadeout_00420c30.cpp (archive only, not a build input). Tested zero/nonzero branch rearrangement, in-place parameter division, and preloaded local duration with negated greater-than comparison. Retail loads frames on the zero path then jumps to conversion; on the nonzero path it loads frames between FCOMP and FNSTSW, and branches with JE before FDIV. Candidates change either the initial branch placement or the FLD scheduling. Do not promote without an exact probe.

After removing the fade root, the synthetic context is 82 bytes, and the gap after Music_Stop covers 120887 bytes from 0x00420C29 to 0x0043E460. Removed pooled empty-string and float aliases that no longer have compiler definitions.

Verification: root make build completed with 1933/1933 sources, zero failures, and whole executable EXACT across 487936 bytes. Live totals: 1829 ordinary C++ regions / 94516 bytes; 475 assembly regions / 228534 bytes; 320 runtime-library regions / 66347 bytes. This includes pre-existing uncommitted work; it is not all new recovery from this handoff. No commit made.
