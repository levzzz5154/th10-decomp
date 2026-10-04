# ECL StartChild 0x0044DF70: parameter-home controls

Fresh production-path probes confirm the complete 549-byte child-start model,
with 416 differing bytes including its one-byte extent difference against 550
retail bytes. The selected 142-byte SpawnChild remains EXACT in the baseline.

Retail overwrites the incoming index stack slot with the destination pointer.
Explicitly assigning that pointer representation to the integer index parameter
produces the identical complete child-start body, verified by SHA-256, and keeps
SpawnChild exact. It is a diagnostic, not a readable production rewrite.

A typed four-byte union carrying first the input index and then the destination
pointer changes the 549-byte body, but still has 416 differing bytes and grows
SpawnChild from 142 to 146. Its subsequent layout-origin failure is retained;
no helper or caller is truncated to hide the regression.

Reordering the equivalent integer/float operand branches to make the integer
case first also produces the identical 549-byte body and preserves exact SpawnChild.
The compiler canonicalizes that control-flow spelling. These controls are now
exhausted; do not repeat them as untested parameter-home or branch-order ideas.

The independent complete body hashes and native images/maps are archived in
`matching2/build/experiments/ecl_child_home_controls_2026_10_04`.
Scratch project: `/tmp/th10-ecl-child-home/msvc`. No production ownership or
machine implementation changed. The assembly owner's outdated claim of no
byte-measured candidate is corrected to point at the existing native model.
