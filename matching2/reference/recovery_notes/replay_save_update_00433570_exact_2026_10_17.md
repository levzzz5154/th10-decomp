# Replay save update 0x00433570: byte-exact (2026-10-17)

The complete 1,460-byte handler, including its five-entry phase table, is
selected by `msvc/build_support/layout/ltcg/replay_save_update.json` from
`src/game/title/replay_save_update.cpp`. Its equivalent layout and exclusive
assembly source `build_support/exact/game/title/replay_menu_runtime.cpp` are
removed.

## The last two address encodings

The former model matched 397/399 instructions, differing only in two SIB
bytes in inlined `strcpy` stores. The compiler's temporary symbol numbers
choose the base/index order; the previous experiments correctly identified
the symbol-count window, but had reached it only with unused declarations.

Naming existing menu conditions reaches the window with ordinary used source:
input direction, selection change, cancellation, previous-name trimming, and
grid-cell classification. Each predicate is evaluated at its original point
and used once by the original branch. No member read is cached across a call,
no input is read early, and no runtime instruction is added. Case 1 gains a
scope for its delay predicate so no case label skips an initialization.

| Existing predicates named | Instructions identical | SIB swaps left |
| --- | ---: | ---: |
| 0, 4, 8 | 397/399 | 2 |
| 12 | 398/399 | 1 |
| 16, 20, 26 | 399/399 | 0 |

The maintained version names 16 conditions; descriptive renaming preserves
the result. The separate constant-naming control is not shipped. Every
retained declaration has a source-level purpose and an actual use.

## Native placement

The new cluster preserves the equivalent rig's translation-unit order:
handler, replay deleter, difficulty-select driver, then the donor cluster's
38 dependencies. One-line context wrappers retain those units without taking
ownership of the donor's eight already recovered screens. Those screens
become unselected anchors, as do the replay deleter at 0x004297B0 and the
donor's existing callee bodies. The donor gaps are split around the two newly
compiled functions. The eight-space name literal is bound through a normal
checked data alias at 0x0046E354.

The first native cluster compared all 1,460 bytes equal to retail, including
the embedded table. The public stack receiver, RET 4, and private callee
conventions are derived by native LTCG. No instruction or address bytes are
patched, and no oracle bytes enter the build.

Ignored source experiments and reports:
`build/experiments/easiest_exact_2026_10_17/save_conditions.log` and
`save_cluster/report.json`.

## Validation

- `make`: pass; both promoted complete regions match retail bytes.
- `make EXACT=1`: pass; all 487,936 executable bytes match, SHA-256
  `2f14760b6fbbf57549541583283badb9a19a4222b90f0a146d5aa17f01dc9040`.
- `make behavior-check BEHAVIOR_PYTHON=matching2/build/behavior-venv/bin/python`:
  pass, including the callsite ABI audit, 473/473 shipped-item cases and
  48/48 shipped replay-submenu cases.
- All 129 tool unit tests and `git diff --check`: pass.

The final build output is the normal C++ build (`acafad97f6f90fbb…`), with
31 equivalent regions remaining. Byte-exact C++ is now 249,417/322,064 bytes
(77.4%). These are bounded differential fixtures, not a full replay run.
