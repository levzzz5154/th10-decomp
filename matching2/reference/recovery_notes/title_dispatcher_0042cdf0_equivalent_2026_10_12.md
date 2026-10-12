# Title dispatcher 0x0042CDF0: equivalent recovery (2026-10-12)

**Status (2026-10-12, later the same day): registered equivalent recovery, 279 of 291 instructions identical.**
What changed since the parked draft:

- the key configuration handler 0x0042F540 and its leaves are linked from their real sources
  (`context_sources`), so the call passes the room in EBX with no push, as retail does;
- the idle test is `switch (mode) { case 1: case 2:`; with `mode == 1 || mode == 2` the compiler
  keeps the constant 2 in EBP (retail never touches EBP) and the body is 4 bytes too long. The
  switch costs three instructions at the top (`test/jle/cmp/jg` for retail's `cmp 1/je/cmp 2/jne`),
  recorded as code-shape; the natural spelling that keeps 2 out of EBP is still unknown;
- the timer tick uses float literals.

The other recorded differences: the demo block schedules the stage-record store and the
difficulty load in another order (4 hunks), one alignment filler, one x87 operand order.
Everything below this paragraph describes the earlier parked draft.

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
