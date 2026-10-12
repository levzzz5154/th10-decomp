# Title dispatcher 0x0042CDF0: equivalent recovery (2026-10-12)

The readable candidate that already lived in the title cluster context
(`layout/ltcg/ending_screen_dependencies/title_dispatcher.cpp`, compiled
in-cluster by `difficulty_select_update_dependencies/title_dispatcher.cpp`)
is now a registered equivalent recovery
(`layout/equivalent/title_dispatcher_0042cdf0.json`): 1,088 of 1,128 bytes
used, 187 of 291 instructions identical, 104 instructions in 54 recorded
differences.

## Recorded differences

* 30 code-shape hunks: evaluation-order and scheduling differences through
  the demo path, the phase dispatch and the mode-call sequences.
* 14 register-choice hunks: counter and pointer homes differ (the same
  contest family as the other equivalent recoveries).
* 10 branch-target hunks: the model merges or splits the phase-table
  branches; `listed_branch_targets` records them with both destinations.

## Structure notes

* `code_bytes` = 1060: the retail region contains its phase jump table at
  offset +0x424 (`ff 24` at +0x147 targeting 0x42D214), so the code extent
  excludes the table; the tail comparison covers the table.
* The model calls `TitleOptions` and other in-context functions; each
  context-defined callee is bound in `bindings` to its retail address so
  `relocate()` can rewrite the call displacements.
* The demo path string `bgm/th10_02.wav` (0x0046F018) is bound the same way.

## Remaining

None for the equivalence route.  A byte-exact recovery would additionally
need c2 to reproduce the retail scheduling; the model keeps the readable
semantics either way.
