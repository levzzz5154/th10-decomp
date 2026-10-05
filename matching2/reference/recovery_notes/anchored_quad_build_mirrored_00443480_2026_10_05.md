# 0x00443480 mirrored anchored quad build (recovered 2026-10-05)

`src/render/anchored_quad_build_mirrored_00443480.cpp` compiles to the retail
505 bytes inside the render batch cluster (`anm_batch_flush_00442f50`).
`make` and `make EXACT=1` pass. Supersedes
`sprite_mirrored_twin_residual_2026-09-28.md`.

* Nothing in the image calls this body, so a root gave it the public stdcall
  entry (524 bytes). The fix is one call from the cluster's synthetic context
  (`RenderBatchContext`); with the real mirrored submit (0x442AD0) in the same
  cluster the pass picks entity in EAX, manager on the stack, RET 4. The
  context grew from 360 to 374 bytes and the gap behind it shrank to match.
* The visibility test is three separate `if (...) return -1;` statements. As
  one `||` condition the `return -1` block is laid out at the end of the
  function; retail has it right after the tests.
* The arithmetic is the stepwise accumulation of the earlier candidate.
