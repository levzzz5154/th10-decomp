# Circle laser split 0x0041EFA0: equivalent recovery (2026-10-12)

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
