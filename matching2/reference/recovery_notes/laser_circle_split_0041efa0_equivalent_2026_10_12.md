# Circle laser split 0x0041EFA0: equivalent recovery (2026-10-12)

**Status (2026-10-12, later the same day): registered equivalent recovery, 241 of 302 instructions identical.**
The model now has its own source (`equivalent/game/laser_circle_split_0041efa0.cpp`, a member of
a view struct derived from the cluster's `CutLaser`) with the shape of the rectangle split
sibling; the two dummy vectors and the frame shift are gone. Of the 61 remaining instructions,
most follow from one register contest: retail keeps the line-animation resource in EDI across
the creation call and the sample count in its stack slot (EDX between calls); the model keeps
the count in EDI and spills the resource. Declaration order, named locals and a `for` loop do
not change it. Recorded classes: 31 register-choice, 8 evaluation-order, 5 code-shape,
1 stack-slot-order, 1 operand-order, 1 alignment-padding; structural hunks stay under the
12.5% budget. Everything below this paragraph describes the earlier parked draft.

The parked candidate (`layout/ltcg/laser_cut/circle_cut.cpp`) is now a
registered equivalent recovery (`layout/equivalent/laser_circle_split_
0041efa0.json`): 1,108 of 1,108 bytes used, 229 of 302 instructions
identical, 72 instructions in 59 recorded differences, 1 frame-offset.

## What unblocked it from the 2026-10-10 parking

Two dummy `CutVector` locals (`align_a`, `align_b`) declared after
`progress` shift the local symbol ids so `point += step` loads the point
component first, matching retail (the parked note's residual 2).  The same
shift moves every stack frame slot up by 4, which the layout records as
`frame_shift` (deltas [4]).

The float constants the model loads from .rdata are bound to their retail
pool addresses in `bindings` (0.5/6/12/16/18/32/192/224/448/-192 at
0x470AFC..0x470B4C, 0x470BCC, 0x470C0C, 0x470CD8, 0x470D1C, 0x470C00).

## The recorded differences

* 20 pure frame-offset instructions (the +4 slot shift).
* ~24 register-choice hunks: `count` lives in EDI in the model versus EDX in
  retail, `hit_count`/`resource`/`bank` swap EDI/EDX the same way (the
  parked note's residual 1).
* ~15 code-shape hunks: the `point += step` scheduling, the `CreateOffset`
  argument order and the merged-tail stores.

The extent probe in `tools/matching/equivalence.py` no longer mistakes
another function's switch table (TitleOptions' in this link) for this
function's own: a tail-zero region whose retail bytes contain no `ff /24`
table instruction cannot gain one in the model (commit 1ef091c3).

## Remaining

None for the equivalence route.  A byte-exact recovery would additionally
need c2 to reproduce retail's register contest for `count` and the tail
merges; the model keeps the readable semantics either way.

## 2026-10-17: register-contest state reviewed; parked

The 31 register-choice hunks are the note's residual 1 (the `count`
EDX-versus-EDI contest, with `hit_count`/`resource`/`bank` following the same
swap): one ChoosePhysReg tie decision, the same family as
`font_atlas_draw_text`'s substitution table. The note's verdict ("None for
the equivalence route") was reached after the source lever sweep; the
`msvc-c2-what-adds-a-register-candidate` K shapes need the Spillcosts numbers
for this function's blocks before one can be chosen.

Region stays equivalent (407 differing bytes).
