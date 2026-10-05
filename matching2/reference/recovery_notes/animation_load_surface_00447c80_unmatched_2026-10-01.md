# Surface loader: preserved unmatched C++ candidate

The interrupted Claude session had assigned the 576-byte owner at `0x00447C80` to a C++ implementation before its native cluster passed. That implementation also temporarily returned `-2` when scratch-surface creation failed; the original returns `-1`. The preserved [candidate](../semantic_candidates/FUN_00447c80_00447c80.cpp) corrects that return value.

Under the standard MSVC 13.10.6030 `/O2 /Gz /MT /Gy /G6 /GF /GS /Zl /GL` profile, this corrected candidate emits a complete 577-byte native body. Its initial missing-file exit jumps to a shared `-1` return, whereas the original sets EAX to `-1` locally before jumping to the epilogue. Native error cleanup follows successful cleanup, reversing the original block order and lengthening another branch. The resulting alignment shifts the memory loader and Clear routine by 16 bytes, so the cluster correctly fails its entry-address check.

Equivalent nested conditions, explicit cleanup labels, inline file/cleanup helpers, RAII cleanup, a result variable, caller result consumption, translation-unit placement, the source calling-convention declaration, and the CRT `free` declaration were examined. None established a complete literal match. Size optimization emitted a different 523-byte body and was rejected. No byte masking, instruction patches, forced padding inside the function, or new volatile/barrier tricks were used.

The original assembly owner remains maintained and exact. The existing verified memory-loader cluster is restored. This candidate receives **zero recovered-function or byte credit** in Wave19. Its header additions remain because the separately recovered back-buffer copier uses the real surface/device types.

Local diagnostic artifacts are under `matching2/build/experiments/claude_surface_resume_2026_10_01/`, including full native PE/MAP outputs, original-source snapshots, and the probe failure reports. Continuing this routine requires a complete 576-byte compiler body and an exact cluster proof; changing the declared extent or relaxing the gate would not establish recovery.

## Resolved 2026-10-05

Recovered byte-exact as `matching2/msvc/src/render/animation_load_surface_00447c80.cpp`
in the `resource_surface_loading` cluster (the preserved candidate file was
removed). The only change against the candidate: the five failure checks are
separate `if (...) goto fail;` statements with the `fail:` cleanup written
after the success return, instead of one `||` chain with the cleanup as its
body.

Why it matters: c2 lays blocks out in reverse post-order with the branch
target visited first. A `||` chain branches straight to the failure body from
the first check, so that body is finished first and lands after the success
path. `if (c) goto fail;` is a branch over a jump block: the next check is the
branch target, the jump block is the fallthrough, so `fail` is reached last
from the final check and lands right after it, ahead of the success path. The
jump blocks are then folded into `jne fail`. The `return -1` of the scratch
surface failure is a whole block and merges into the tail of `fail`; the
missing-file `return -1` follows a call cleanup and keeps its own copy.
