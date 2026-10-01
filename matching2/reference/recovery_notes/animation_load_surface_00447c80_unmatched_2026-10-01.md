# Surface loader: preserved unmatched C++ candidate

The interrupted Claude session had assigned the 576-byte owner at `0x00447C80` to a C++ implementation before its native cluster passed. That implementation also temporarily returned `-2` when scratch-surface creation failed; the original returns `-1`. The preserved [candidate](../semantic_candidates/FUN_00447c80_00447c80.cpp) corrects that return value.

Under the standard MSVC 13.10.6030 `/O2 /Gz /MT /Gy /G6 /GF /GS /Zl /GL` profile, this corrected candidate emits a complete 577-byte native body. Its initial missing-file exit jumps to a shared `-1` return, whereas the original sets EAX to `-1` locally before jumping to the epilogue. Native error cleanup follows successful cleanup, reversing the original block order and lengthening another branch. The resulting alignment shifts the memory loader and Clear routine by 16 bytes, so the cluster correctly fails its entry-address check.

Equivalent nested conditions, explicit cleanup labels, inline file/cleanup helpers, RAII cleanup, a result variable, caller result consumption, translation-unit placement, the source calling-convention declaration, and the CRT `free` declaration were examined. None established a complete literal match. Size optimization emitted a different 523-byte body and was rejected. No byte masking, instruction patches, forced padding inside the function, or new volatile/barrier tricks were used.

The original assembly owner remains maintained and exact. The existing verified memory-loader cluster is restored. This candidate receives **zero recovered-function or byte credit** in Wave19. Its header additions remain because the separately recovered back-buffer copier uses the real surface/device types.

Local diagnostic artifacts are under `matching2/build/experiments/claude_surface_resume_2026_10_01/`, including full native PE/MAP outputs, original-source snapshots, and the probe failure reports. Continuing this routine requires a complete 576-byte compiler body and an exact cluster proof; changing the declared extent or relaxing the gate would not establish recovery.
