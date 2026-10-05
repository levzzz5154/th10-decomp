# Stage score-display constructor 0x00415B00: byte-exact recovery

The complete 683-byte constructor is recovered in
`msvc/src/game/stage_score_display_00415b00.cpp`, with its typed layout in
`msvc/include/th10/game/stage_score_display_00415b00.hpp`. The native cluster
is `msvc/layout/ltcg/stage_score_display_00415b00.json`. The old assembly owner
`src/game/stage_slot_state.cpp` was removed and its manifest row promoted to
ordinary semantic C++; no equivalence exception was added.

The object is the 0x90-byte display allocated by the already recovered
`ItemManager_00415db0::CreateScoreDisplay` at 0x00415DB0. Native LTCG places the
constructor's receiver and script pointer on the stack and returns its receiver
in EAX, with RET 8. An ordinary C++ constructor and placement-construction
caller derive that convention without an ABI shim.

## Source facts that determine the match

- Three timer member constructors clear their initialized bits before the
  constructor body calls memset. Their inline Set(0) operations preserve the
  observed initialization and reset sequences after the clear.
- The pool allocator, primary-list registration, lookup and collision activation
  are complete genuine compiler-context bodies. They derive the private ESI,
  EBX/EDX/EAX and EDX conventions at the selected call sites. Only the display
  constructor is selected; dependency extents describe their full native output,
  not truncated retail-sized prefixes.
- The animation resource initializer is an external public member call, with
  resource in ECX and object/index on the stack. Compiling an unrooted local
  version allowed LTCG to change that ABI and broke the constructor's calls.
- The four handle lookups pass the stored script ID by value. Constructing a
  fresh ID from its integer value changed temporary-register preferences and
  all later register choices. Copying the existing four-byte ID matches retail.
- The region vector assignment follows the four field/color initializations.
  MSVC schedules its first components earlier but stores its final component
  after those four stores. Assigning the vector before those fields differs
  only in that final store's position.

The legacy semantic model was not a faithful oracle: retail initializes the
second vector with **24.0f**, not 25.0f. A failed animation lookup clears its
stored handle and then the subsequent layer-byte write still faults through the
null result; the old model skipped that write. The new source reproduces the
retail bytes, including those paths. The final loops activate applicable entries
in the 2000-record pool, invoke effect-list virtual slot 5 where kind is not 1,
and sweep enemy deaths.

## Verification

The strict native probe passes all **683 bytes EXACT** with zero differences,
zero instruction/address-operand rewriting and no retail bytes used to build.
Compile-time checks cover the 0x90-byte display and every accessed display
member, plus collision-record stride and state offset.

```sh
python3 matching2/tools/matching/probe.py \
  --source src/game/stage_score_display_00415b00.cpp \
  --output /tmp/stage-score-display-probe
```

The initial shared-tree `make` failed in the unrelated stage-tip parser cluster:
concurrent edits moved `_ReadLine@16` from 0x00419F40 to 0x00419F50. The parser
source/layout files changed after this recovery's isolated project was copied.
Those concurrent changes were left intact. An isolated full build against the
copied, previously passing project plus this recovery used
`/tmp/codex-stage-slot/msvc`. Build output is on the workspace filesystem at
`matching2/build/experiments/stage_score_display_00415b00_2026_10_05/full-build`
(the scratch full-build path links there).

Exploratory models, strict-probe evidence and logs are in
`/tmp/codex-stage-slot`. Current ownership after this promotion is 71 assembly
regions / 100,642 bytes; ordinary C++ totals 186,981 bytes and the existing
9 equivalent recoveries still total 33,860 bytes.

User-requested handoff: the isolated build was terminated after 1100/1677
sources with one unresolved failure. Neither full gate for this recovery is
claimed passing. See `codex_handoff_2026_10_05.md` for commands and build paths.
