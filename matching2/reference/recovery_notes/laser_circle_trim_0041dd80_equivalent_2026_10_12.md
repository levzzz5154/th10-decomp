# Circle laser trim 0x0041DD80: equivalent recovery (2026-10-12)

**Status (2026-10-12, later the same day): registered equivalent recovery, 260 of 345 instructions identical.**
The model itself is unchanged (it is the `laser_cut` cluster's context body, which exact
clusters depend on). What changed is the review of its 57 differences hunk by hunk instead of
counting every one as structural: 20 register-choice, 13 evaluation-order, 10 stack-slot-order,
1 operand-order, and 13 structural (11 code-shape, 2 branch-target), which is within the 12.5%
budget. No call, callee or named address differs. This is the weakest of the registered
recoveries and the first candidate for a rewrite in its own source like the circle split.
Everything below this paragraph describes the earlier parked draft.

The in-cluster candidate (`layout/ltcg/laser_cut/circle_trim.cpp`, already an
anchor body of the `laser_cut` cluster) is now a registered equivalent
recovery (`layout/equivalent/laser_circle_trim_0041dd80.json`): 1,238 of
1,238 bytes used, 260 of 345 instructions identical, 85 instructions in 57
recorded differences.

## Recorded differences

* 36 code-shape hunks: evaluation-order and scheduling differences in the
  sample walk, the run-spawn epilogue and the model's handling of the
  playfield bounds (`data_00470b04`, 448, -192, 192).
* 19 register-choice hunks: the hit counter, resource pointer and bank
  pointer live in different registers (the same contest the parked
  rectangle/circle notes describe).
* 2 branch-target hunks: the model merges two identical walk tails that
  retail keeps apart (or vice versa); both destinations run the same code,
  which `listed_branch_targets` records.

## Bindings

The model's float constants are bound to their retail pool addresses
(16.0 at 0x00470B48, 32.0 at 0x00470BCC, -192.0 at 0x00470B40, 192.0 at
0x00470B3C, 448.0 at 0x00470B38, 18.0 at 0x00470C0C, 6.0/12.0/2.0/1.0 at
their pool slots).  The layout reuses the rectangle split's absolute
symbol coverage plus the trim-specific data symbols (`data_00477818`,
`data_0047781c`, `data_00470b04`).

## Procedure notes

The work-directory-keeping variant (`equivalence_keep.py`, env
`EQUIV_KEEP_WORK`) was used to recover the model map for identifying
unbound constant references; the candidate keeps its two alignment locals
from this session's first experiment (they changed nothing measurable for
the trim, but were present during validation).

## 2026-10-17: state reviewed; parked

The 57 hunks are the same three families the parked rectangle/circle notes
describe: the hit-counter/resource/bank register contest (20), the
sample-walk and run-spawn scheduling (34), and the two merged walk tails
(2, recorded via `listed_branch_targets`). No new lever applies: the
register contest needs the Spillcosts/ChoosePhysReg numbers for these
blocks, and the walk-tail merge is the distinct-argument shape the
tail-merge survivor levers do not move (as `recovery_script_executor`
re-confirmed this session).

Region stays equivalent (870 differing bytes).
