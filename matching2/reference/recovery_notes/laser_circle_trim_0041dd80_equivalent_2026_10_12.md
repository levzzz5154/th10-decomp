# Circle laser trim 0x0041DD80: equivalent recovery (2026-10-12)

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
