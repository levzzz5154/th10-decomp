# Replay save 0x00429B60 — equivalent-path draft (not yet accepted)

Date: 2026-10-13
Owner region: `asm_FUN_00429b60_00429b60` (1681 bytes, still `asm` in
regions.json — nothing was registered).

## What this pass recovered

The prior BLOCKED state was `closest_byte_count=0/1681` with no viable
source shape. This pass produced a complete readable C++ model that
compiles under the real MSVC 13.10.6030 `/GL /LTCG` toolchain to a body
that is structurally retail's: 404 of 535 instructions identical in the
`equivalence.py --record` measurement, with the entry ABI, security-cookie
prologue/epilogue, name copy, stage scan, serialization loops, cipher
call shape and file-write section all present. The remaining differences
are register/slot/scheduling ties plus one optimizer fold (below).

## Files (all new, exclusively this task's)

- `include/th10/game/replay_save_00429b60.hpp` — view types
  (`ReplaySaveHeader/Summary/Manager`, `ReplayUserChunk`) and the member
  declaration.
- `src/game/replay_save_00429b60.cpp` — the model body, as a member
  function `int __fastcall ReplaySaveManager_00429b60::Save(const char*
  file_name, const char* name)`.
- `layout/ltcg/replay_save_00429b60.json` — schema-1 native-LTCG cluster
  manifest (source + synthetic context + the cipher anchor).
- `layout/ltcg/replay_save_00429b60_context.cpp` — cluster driver; roots
  the link and calls `Save` through a volatile function pointer.
- `layout/ltcg/replay_save_00429b60/encrypt.cpp` — the `Dat_Encrypt` body
  as an ABI anchor (`#pragma code_seg(".text$rsave03")`).
- `equivalent/game/replay_save_00429b60_stub.cpp` +
  `layout/equivalent/replay_save_00429b60.json` — the equivalent-path
  draft (`context_cluster` points at the cluster manifest).

`matching2/msvc/regions.json` was never edited (scratch copy only, under
`scratch/replay_save/`).

## Non-obvious levers found (verified by probes)

1. **The routine is a member function.** Retail's entry is
   `__fastcall` with `this` in ECX, first argument in EDX and the player
   name on the stack (`ret 4`). A free `__fastcall` function compiles the
   prologue with the parameters in different registers; declaring `Save`
   as a **member** `__fastcall` function reproduces retail's prologue
   exactly (`mov edi,ecx; xor ebp,ebp; mov esi,edx; mov edx,[edi+0x18]`,
   byte-for-byte, including the copy loop's `bl` scratch).
2. **The cipher call needs the cluster.** `Dat_Encrypt`'s key travels in
   AL; that convention only exists under native /LTCG co-compilation, so
   the model links with the cipher body (anchor) in the same link.
3. **The volatile function-pointer context idiom**
   (already used by `scheduler_tasks_context.cpp`) holds the declared
   ECX/EDX/stack ABI against the whole-program register reassignment.
4. **`data_00477708` must be a pointer, and its block is packed.** The
   two doubles live at +0x24/+0x2C (4 mod 8), so the model reuses
   `FrameRateCounter_004134b0` (`#pragma pack(4)`) through a pointer;
   an object-valued declaration folds the loads into absolute addresses
   and the model then names addresses retail does not.
5. **The slow-rate expression must keep retail's x87 order.** `C - M/B*C`
   is reassociated by /GL into `C - (C/B)*M`. Declaring the scale global
   `const volatile float data_00470b44` blocks the reassociation and
   reproduces retail's exact sequence
   (`fld [M]; fdiv [B]; fmul [C]; fsubr [C]; fstp`).
6. **The per-node statements must re-read `link->pool`.** Caching
   `pool` in a local lets the optimizer common the `input_cursor - pool`
   subexpression across the `total`, `data_size` and `input_count`
   updates; spelling `link->pool->...` in each statement forces the
   retail recompute pattern (`imul 0x2AAAAAAB` twice plus the
   `[esi]` reload). Retail's *emitted* store order is `data_size` then
   `input_count`; spelling `input_count` first in the source produces
   that emission with the recompute pattern (the source order of these
   two independent field updates is a free choice).

## Current measurements

**Draft status: within the equivalence budgets.** With the classified
hunks (36 `register-choice`, 21 `alignment-padding`, 12
`evaluation-order`, 10 `stack-slot-order`, 0 structural) the gate math
is: structural weight 0/535 (budget 12.5%), total weight 138/535 =
25.8% (budget 33.3%), zero call-set mismatches, zero flow changes, the
recomputed hunks match the recorded list exactly, 17 frame-offset
instructions as recorded, 0 base/index swaps. The remaining draft
verdict in `--record` mode is only the record-mode gate classing every
hunk `code-shape`; formal acceptance runs through the orchestrator's
`make` (`verify_all`).

- Cluster probe (`probe.py --project scratch/replay_save/msvc`): the
  cluster builds and places `Save` at 0x00429B60 and the cipher anchor at
  0x0044B220. With the loop-1 statements ordered
  `total, input_count, data_size` the inner loop reproduces retail's
  recompute pattern and the extent is 1720 bytes; with the fields in
  retail's emitted order (`total, data_size, input_count`) the optimizer
  folds the two `input_cursor - pool` subexpressions and the extent is
  1660. 1440 differing bytes, dominated by the stack-slot layout
  (frame `0x12C` vs retail `0x124` in the equivalence build) and by
  loop 2, where retail keeps the page-list head in EAX across the node
  loop while the model re-reads it from its spill slot.
- `equivalence.py --layout ... --record`: 404/535 instructions identical,
  79 hunks / 117 instructions listed. Hard gate failures:
  `retail calls what the model does not: 0x44b220` (the model's cipher
  call target falls inside the declared `code_bytes` window, so it is
  not resolved through the map/binding — needs the model extent to reach
  exactly 1681 or the cipher to land past it), one hunk at +0x431 that
  pairs retail's `sprintf` with the model's `localtime` (the Version
  line's argument pushes are hoisted above the `out` update), and the
  structural weight (measured with everything classed `code-shape`;
  after classification only the loop-fold and call-shift hunks remain
  structural).

## Residual difference classes

- `stack-slot-order`: the frame holds two slots more than retail
  (`0x12C` vs `0x124`); `manager`/`first` occupy retail's slots, `last`
  and the chunk-write counter do not.
- `register-choice`: `packed` in ESI (retail EDI), the WriteFile pointer
  in EDI (retail EBX), the compress size in EAX (retail ESI), `link` in
  ECX (retail ESI).
- `evaluation-order`: the Version line's argument push is hoisted above
  the `out` update; the localtime/Name-sprintf block shifts as a result.
- `code-shape` (structural): the loop-1 fold (above) and the write-region
  reloads of `manager->header->packed_size` (retail keeps the compress
  size in ESI across the first WriteFile; the model re-reads the header
  field).

## Model-window mechanics (equivalence path)

Solved this pass: the cluster driver now defines a real never-executed
pad function (`ReplaySaveModelPad_00429b60`, `.text$rsave02`, ~26 bytes)
called through a volatile function pointer from the synthetic context,
and the layout roots the context (`roots`). /GL eliminates any pad whose
only caller is a direct call (noinline is not honored by the
whole-program inliner), but the volatile-pointer call keeps it, pushes
`Dat_Encrypt` to +0x6A0 (past the 1681-byte window) and the cipher call
resolves through the layout's `bindings`
(`?Dat_Encrypt@@... -> 0x0044B220`).

The equivalence build links the stub plus the cluster driver; the cipher
body lands four bytes after `Save` (`Save` 0x68C bytes, int3 pad,
`Dat_Encrypt` at +0x690). The comparison window is the region extent
(1681), so the cipher call target falls inside the window and is spelled
`call L+0x690`, which the gate cannot bind to 0x0044B220. Padding
sections/functions between them are eliminated by the /GL whole-program
pass (a `#pragma code_seg` noinline pad function with a volatile store
contributed zero bytes even with a live call from the context and a
`/INCLUDE` pragma), so the honest fix is the extent itself: when `Save`
compiles to exactly 1681 bytes the cipher lands beyond the window and
the call resolves through the binding.

## Next levers (in order)

1. Recover the two stack-slot shares. Retail's slot map is
   `pool walker | count/buffer | written | last/chunk-written | i/link |
   first | manager | stage walker` with `path[0x100]` directly below the
   cookie. The declared-local order that makes MSVC 7.1 pack the pairs
   is the missing input; try declaring the locals in retail's slot order
   and/or splitting `link` per loop with the loop-2 name.
2. Keep the compress size register-resident: retail holds it in ESI from
   the Lzss_Compress return to the second WriteFile. Once the frame is
   right this should follow; otherwise spell the second write's size via
   a dedicated `int sent = written;` copy.
3. The Version-line push order: try spelling the line so the argument is
   not a plain global (or re-examine whether the original used a pooled
   literal), which is what makes the model hoist `push 0x46e5c8`.
4. With the frame and those three shapes converged the cluster build
   should reach the 1681 extent; then re-run the cluster probe for EXACT,
   or re-classify the equivalence hunks (`register-choice`,
   `stack-slot-order`, `evaluation-order`, `code-shape`) and re-measure
   the draft against the 12.5%/33% budgets.

## 2026-10-17: next lever 1 probed both ways; parked

The declared-local order lever was tried exactly as written: the locals
declared in retail's slot-map order (`link | count | total | written | last |
user_written | remainder | first | manager | stage | path`) gives 79 hunks,
one worse than the shipped 78; adding the loop split (`link` for the counting
loop, `link2` for the two write loops, per the map's `i/link` pair) is also
79. The two stack-slot shares are therefore not recoverable by declaration
order alone — consistent with the `msvc-c2-stack-slot-order-by-reference-weight`
finding that declaration order does not drive the colour allocation.

Region stays equivalent (1471 differing bytes).

## 2026-10-17: the frame is 8 bytes too large; sharing closes half of it

A frame-size survey across all 33 layouts found four regions whose prologue
disagrees by whole slots. This one is the only one where the **model is too
large**: `retail sub esp,0x124` (292) against `model sub esp,0x12c` (300), so
retail packs a 4-byte pair the model keeps apart.

`written` is live only through the write calls; `user_written` and `remainder`
appear only from the tail block (which itself appears twice). Their ranges are
disjoint, so the slots can legitimately be shared. Measured against the
baseline 408/535, 78 hunks, 1,471 differing bytes, 8 tail bytes:

| variant | identical | hunks | differing bytes | tail |
| --- | --- | ---: | ---: | ---: |
| baseline | 408/535 | 78 | 1,471 | 8 |
| `share-written` (fold `user_written` into `written`) | 407/535 | 73 | 1,456 | 16 |
| `fold-user-written` | 407/535 | 73 | 1,456 | 16 |
| `share-remainder` (reuse `count`) | 408/535 | 78 | 1,455 | 16 |
| `share-remainder-first` (reuse `first`) | 408/535 | 78 | 1,455 | 16 |
| `share-both` | 407/535 | 73 | 1,456 | 16 |

With both shares the prologue becomes `sub esp,0x128` (296) — half the gap
closed — and the hunks drop 78 -> 73 with 15 fewer differing bytes, though the
tail grows 8 -> 16. One further 4-byte share is still needed to reach retail's
292. Region stays equivalent.

# Replay save 0x00429B60 — 2026-10-18 session addendum

(Append this section to `matching2/reference/recovery_notes/replay_save_00429b60_equivalent_2026_10_13.md`;
written from the /tmp/campaign/replay_save sandbox, main tree read-only.)

## 2026-10-18: frame gap closed (0x12c -> 0x124 exact); 433/535, 1,418 differing bytes

Four measured levers on top of the 2026-10-17 state (byte gate; the variant.py
line is `scas-pack-written-uw-last-sent 433/535 0 55 1418 16 drafts`; baseline was
408/535, 78 hunks, 1,471 differing bytes):

1. **`sent-early`** — `int sent = written;` moved to immediately after
   `Lzss_Compress`, and `sent` used for both `Dat_Encrypt` argument lists and
   `header->packed_size` (the tail's `int sent = written;` removed). This is the
   "keep the compress size register-resident" lever from the previous note's
   next-lever list, spelled so every post-compress read comes from one copy.
   408 -> 430 identical instructions alone (1,471 -> 1,425 differing bytes incl.
   tail in the previous accounting).
2. **`pack-written`** — the pack loop's counter IS `written`:
   `for (stage = 0, written = 8; written != 0; stage++, written--)`. c2 then keeps
   the generated countdown in `written`'s slot instead of a fresh element, which
   is exactly retail's `X=0x08 = written + countdown` sharing. **Mechanism
   (verified by traces): the counter folds only into an address-taken variable** —
   `written`'s `&written` at Lzss_Compress prevents c2 from renaming the counter
   to a fresh temp; the same counter on `count` or `remainder` (not address-taken)
   is replaced by a separate unnamed w3 element and the frame stays 0x128.
   This is the lever that closes the last 4 bytes of the frame: 0x128 -> 0x124.
3. **`fold-uw-last`** — the two chunk writes' out-parameter is `last`
   (`imp_WriteFile(..., (unsigned int*)&last, 0)`, check `!= (unsigned int)last`);
   `user_written` is removed. `last`'s live range ends before the chunk writes,
   so this merges retail's `last/chunk-written` shared slot.
4. **`scas`** (summary block order) — the slow-rate section spelled
   `double scaled = ...; summary->slow_rate = 100 - scaled; summary->score = ...;
   summary->stage_count = count;` (all 24 permutations of the four statements
   swept; this is the unique best). 1,423 -> 1,418 bytes. Compare-operand swaps
   (`sent != written`, `0x24 != written`) give +1 identical instruction at the
   same byte count; `sent` declared after `asm_free` gives 436/51 but 1,426 bytes.

With these the model frame is exactly retail's `sub esp,0x124` and the colour
structure is retail's: 8 slot colours + `path[0x100]` + cookie. Every per-role
emitted reference count now equals retail's (pool-walker 9, count/buffer 7,
written+countdown 9, last+chunk 7, stage/link 7, first 5, manager 3,
stage-walker 3).

## Retail slot map (from the retail listing, ground truth)

`X=0x00 pool-walker | X=0x04 {count,buffer} | X=0x08 {written,countdown} |
X=0x0c {last,chunk-written} | X=0x10 {i,link} | X=0x14 first | X=0x18 manager |
X=0x1c stage-walker`, `path[0x100]` at X=0x20..0x120, cookie at 0x120.
The model's pairings all match; the top three slots (first/manager/stage-walker)
land at the right offsets; the bottom five are permuted:
model `[B, W, T, S, L]` vs retail `[T, B, W, L, S]`.

## c2's colour sort — decoded (new rule candidate: *c2 colour-table sort is a
## middle-pivot Lomuto quicksort; ties return 0*)

Disassembled c2.dll 13.10.6030 (pinned sha256 7a6f6d8e...) around the stackpack
breakpoints and validated the reconstruction against three independent traces
(the 2026-10-17 replay_save trace, the 2026-10-18 win trace, and
core_sort_2026_10_17's home_map two-element reversal; note that
core_sort's "model_swap" runs swapped table records *in gdb* — the sort is
deterministic):

- Sort entry 0x1078cb20, body 0x1078e32c: records [lo..hi] (lo = first
  non-param colour, hi = count-1; the param colour(s) at index 0 are pinned and
  the big-size record sorts last through its tiny ratio).
- Pivot = the **middle element** swapped to lo (not median-of-3). Lomuto
  partition: `compare(pivot, e) == -1` selects e (strictly greater ratio) into
  the left run; **ties (compare == 0) are not selected** and rotate through the
  swaps. Pivot swapped to the boundary j; recurse [lo..j-1] (call) then iterate
  [j+1..hi].
- Comparator 0x1078e2d9: class bytes (record+0x18) compared first (bigger class
  sorts last); else ratio = weight*1000/size (signed idiv); equal ratio returns
  **0** (0x1079008d `xor eax,eax; ret`).
- Record weight = sum of member weights (colour joins add weights).
- Colours are then allocated top-down in table order: record 1 = lowest frame
  offset. The sort input (table order) = the colour **creation order** = the
  processing order of each record's first member; elements are processed by
  weight descending, ties by element **list index**, and a later element joins
  the newest non-interfering colour.
- Declaration order and variable names do NOT move the element list (both
  tested: reversed declarations and pure renames leave the indices fixed).
- Simulator: reproduces all observed tables exactly.

## Remaining gap and what is ruled out

Remaining: 55 hunks / 1,423 differing bytes. Two independent causes:

1. Bottom-five slot permutation. With the model's colour keys
   ({buffer,count}=9, written+counter=9, {walkers}=9, {link,stage}=7, last=7,
   first=5, manager=4, stage-walker=3) and its creation order
   `[W, L, B, T, F, S, M, X, P]`, the sort yields `[B, W, T, S, L, ...]`;
   retail's layout needs `[T, B, W, L, S, ...]`. Exhaustive search: no index
   permutation of the tied element groups produces it (all 12 achievable
   creation orders checked); 30,240 input orders do, but every pairing-safe one
   needs weight changes. **Cheapest target: the {pool-walker1, pool-walker2}
   record weight 9 -> 10** (one extra IR reference on the loop-2 walker) maps
   the current creation order to retail's layout exactly; alternatives are
   written-1 & {buffer,count}-1 together.
   Ruled out this session: declaration order (79 hunks previously, re-confirmed
   inert), loop split (previously 79), `user_written` folded into `written`/
   `count` instead of `last` (frames 0x128 or worse, 1424-1457 bytes), pack
   counter on `count`/`remainder` (counter stays a separate element), walker
   pointer-walk spellings (equivalence flow error), comma/`?:0` extra-reference
   probes (folded away, byte-identical), `this->` direct / `file_name` copy /
   `manager` double copy / `total` copy / `count` copy / `while` loop forms
   (all byte-identical), statement-order shuffles in loop 1 (worse), pure
   renames (indices unchanged).
2. ESI/EDI register contest: retail `mov edi,ecx` (this->EDI) / `mov esi,edx`
   (file_name->ESI), model swapped; this also moves the loop-1 node register
   (retail ESI, model ECX) and the WriteFile pointer (retail EBX, model EDI).
   physreg trace: this-piece num=27 prio=76 avail=[2,7,8] costs 7:0 8:0 takes
   ESI on the class-order tie; file_name num=29 prio=48. Retail's this took EDI
   => its ESI cost was non-zero (an ESI-limited neighbour adds 100*weight) or
   the priority order flipped; the this-variable also splits into two candidate
   pieces (num=5 prio=90 limited to EBX/EBP, num=27). Per
   msvc-c2-spillcosts-priority the fix is a K/priority lever in a specific
   block; not found this session.

Best rows measured (bytes = differing code bytes in the code window):
`scas+pack-written+fold-uw-last+sent-early` 433/535, 55 hunks, **1418 bytes**, frame 0x124;
`scas+chk-swaps` (same bytes, 433/54); `scas+sent-late` 436/51/1426;
`stage-count-last` 436/53/1422; `win` (before scas) 433/55/1423.

# Replay save 0x00429B60 — 2026-10-18 session addendum

(Append this section to `matching2/reference/recovery_notes/replay_save_00429b60_equivalent_2026_10_13.md`;
written from the /tmp/campaign/replay_save sandbox, main tree read-only.)

## 2026-10-18: frame gap closed (0x12c -> 0x124 exact); 433/535, 1,418 differing bytes

Four measured levers on top of the 2026-10-17 state (byte gate; the variant.py
line is `scas-pack-written-uw-last-sent 433/535 0 55 1418 16 drafts`; baseline was
408/535, 78 hunks, 1,471 differing bytes):

1. **`sent-early`** — `int sent = written;` moved to immediately after
   `Lzss_Compress`, and `sent` used for both `Dat_Encrypt` argument lists and
   `header->packed_size` (the tail's `int sent = written;` removed). This is the
   "keep the compress size register-resident" lever from the previous note's
   next-lever list, spelled so every post-compress read comes from one copy.
   408 -> 430 identical instructions alone (1,471 -> 1,425 differing bytes incl.
   tail in the previous accounting).
2. **`pack-written`** — the pack loop's counter IS `written`:
   `for (stage = 0, written = 8; written != 0; stage++, written--)`. c2 then keeps
   the generated countdown in `written`'s slot instead of a fresh element, which
   is exactly retail's `X=0x08 = written + countdown` sharing. **Mechanism
   (verified by traces): the counter folds only into an address-taken variable** —
   `written`'s `&written` at Lzss_Compress prevents c2 from renaming the counter
   to a fresh temp; the same counter on `count` or `remainder` (not address-taken)
   is replaced by a separate unnamed w3 element and the frame stays 0x128.
   This is the lever that closes the last 4 bytes of the frame: 0x128 -> 0x124.
3. **`fold-uw-last`** — the two chunk writes' out-parameter is `last`
   (`imp_WriteFile(..., (unsigned int*)&last, 0)`, check `!= (unsigned int)last`);
   `user_written` is removed. `last`'s live range ends before the chunk writes,
   so this merges retail's `last/chunk-written` shared slot.
4. **`scas`** (summary block order) — the slow-rate section spelled
   `double scaled = ...; summary->slow_rate = 100 - scaled; summary->score = ...;
   summary->stage_count = count;` (all 24 permutations of the four statements
   swept; this is the unique best). 1,423 -> 1,418 bytes. Compare-operand swaps
   (`sent != written`, `0x24 != written`) give +1 identical instruction at the
   same byte count; `sent` declared after `asm_free` gives 436/51 but 1,426 bytes.

With these the model frame is exactly retail's `sub esp,0x124` and the colour
structure is retail's: 8 slot colours + `path[0x100]` + cookie. Every per-role
emitted reference count now equals retail's (pool-walker 9, count/buffer 7,
written+countdown 9, last+chunk 7, stage/link 7, first 5, manager 3,
stage-walker 3).

## Retail slot map (from the retail listing, ground truth)

`X=0x00 pool-walker | X=0x04 {count,buffer} | X=0x08 {written,countdown} |
X=0x0c {last,chunk-written} | X=0x10 {i,link} | X=0x14 first | X=0x18 manager |
X=0x1c stage-walker`, `path[0x100]` at X=0x20..0x120, cookie at 0x120.
The model's pairings all match; the top three slots (first/manager/stage-walker)
land at the right offsets; the bottom five are permuted:
model `[B, W, T, S, L]` vs retail `[T, B, W, L, S]`.

## c2's colour sort — decoded (new rule candidate: *c2 colour-table sort is a
## middle-pivot Lomuto quicksort; ties return 0*)

Disassembled c2.dll 13.10.6030 (pinned sha256 7a6f6d8e...) around the stackpack
breakpoints and validated the reconstruction against three independent traces
(the 2026-10-17 replay_save trace, the 2026-10-18 win trace, and
core_sort_2026_10_17's home_map two-element reversal; note that
core_sort's "model_swap" runs swapped table records *in gdb* — the sort is
deterministic):

- Sort entry 0x1078cb20, body 0x1078e32c: records [lo..hi] (lo = first
  non-param colour, hi = count-1; the param colour(s) at index 0 are pinned and
  the big-size record sorts last through its tiny ratio).
- Pivot = the **middle element** swapped to lo (not median-of-3). Lomuto
  partition: `compare(pivot, e) == -1` selects e (strictly greater ratio) into
  the left run; **ties (compare == 0) are not selected** and rotate through the
  swaps. Pivot swapped to the boundary j; recurse [lo..j-1] (call) then iterate
  [j+1..hi].
- Comparator 0x1078e2d9: class bytes (record+0x18) compared first (bigger class
  sorts last); else ratio = weight*1000/size (signed idiv); equal ratio returns
  **0** (0x1079008d `xor eax,eax; ret`).
- Record weight = sum of member weights (colour joins add weights).
- Colours are then allocated top-down in table order: record 1 = lowest frame
  offset. The sort input (table order) = the colour **creation order** = the
  processing order of each record's first member; elements are processed by
  weight descending, ties by element **list index**, and a later element joins
  the newest non-interfering colour.
- Declaration order and variable names do NOT move the element list (both
  tested: reversed declarations and pure renames leave the indices fixed).
- Simulator: reproduces all observed tables exactly.

## Remaining gap and what is ruled out

Remaining: 55 hunks / 1,423 differing bytes. Two independent causes:

1. Bottom-five slot permutation. With the model's colour keys
   ({buffer,count}=9, written+counter=9, {walkers}=9, {link,stage}=7, last=7,
   first=5, manager=4, stage-walker=3) and its creation order
   `[W, L, B, T, F, S, M, X, P]`, the sort yields `[B, W, T, S, L, ...]`;
   retail's layout needs `[T, B, W, L, S, ...]`. Exhaustive search: no index
   permutation of the tied element groups produces it (all 12 achievable
   creation orders checked); 30,240 input orders do, but every pairing-safe one
   needs weight changes. **Cheapest target: the {pool-walker1, pool-walker2}
   record weight 9 -> 10** (one extra IR reference on the loop-2 walker) maps
   the current creation order to retail's layout exactly; alternatives are
   written-1 & {buffer,count}-1 together.
   Ruled out this session: declaration order (79 hunks previously, re-confirmed
   inert), loop split (previously 79), `user_written` folded into `written`/
   `count` instead of `last` (frames 0x128 or worse, 1424-1457 bytes), pack
   counter on `count`/`remainder` (counter stays a separate element), walker
   pointer-walk spellings (equivalence flow error), comma/`?:0` extra-reference
   probes (folded away, byte-identical), `this->` direct / `file_name` copy /
   `manager` double copy / `total` copy / `count` copy / `while` loop forms
   (all byte-identical), statement-order shuffles in loop 1 (worse), pure
   renames (indices unchanged).
2. ESI/EDI register contest: retail `mov edi,ecx` (this->EDI) / `mov esi,edx`
   (file_name->ESI), model swapped; this also moves the loop-1 node register
   (retail ESI, model ECX) and the WriteFile pointer (retail EBX, model EDI).
   physreg trace: this-piece num=27 prio=76 avail=[2,7,8] costs 7:0 8:0 takes
   ESI on the class-order tie; file_name num=29 prio=48. Retail's this took EDI
   => its ESI cost was non-zero (an ESI-limited neighbour adds 100*weight) or
   the priority order flipped; the this-variable also splits into two candidate
   pieces (num=5 prio=90 limited to EBX/EBP, num=27). Per
   msvc-c2-spillcosts-priority the fix is a K/priority lever in a specific
   block; not found this session.

Best rows measured (bytes = differing code bytes in the code window):
`scas+pack-written+fold-uw-last+sent-early` 433/535, 55 hunks, **1418 bytes**, frame 0x124;
`scas+chk-swaps` (same bytes, 433/54); `scas+sent-late` 436/51/1426;
`stage-count-last` 436/53/1422; `win` (before scas) 433/55/1423.

## 2026-10-18 (second pass): gate-passing state staged

The staged state is `scas + pack-written + fold-uw-last + sent-early`
(model `build_support/contexts/legacy/game/replay_save.cpp`, layout
`build_support/layout/equivalent/replay_save.json` regenerated):

- variant.py: `scas-pack-written-uw-last-sent 433/535 0 55 1418 16 drafts`.
- The layout's `differences` are regenerated (43 hunks) with reviewed classes:
  26 register-choice, 63 evaluation-order, 16 alignment-padding, 1 operand-order,
  **0 structural**. Checked gate (`equivalence.py --name replay_save2`, the path
  `make` runs): `replay_save2: 1,664 of 1,681 bytes used, 433 of 535 instructions
  identical, 0 base/index swaps, 31 frame-offset, 71 instructions in 43 recorded
  differences` — the gate's reason list is empty. Total weight 106/535 = 19.8%
  (budget 33.3%); structural 0/535 (budget 12.5%).
- `frame_shift` is regenerated as `{'deltas': [-8, -4, 4], 'count': 31}`: the model
  frame is exactly retail's, and the eight slots are permuted (pool-walkers -8,
  count/buffer +4, written +4, last -4, link/stage +4, path -4 in "retail minus
  model" terms). Those 31 instructions are recorded as frame offsets; fixing the
  permutation (the residuals below) takes `frame_offset` to 0 and the field away.
- Class convention kept from the 2026-10-13 review: statement/argument reorders
  are `evaluation-order` (its Version-line push hoist was classed so), one-sided
  consequence instructions are `alignment-padding`. The `scas` summary-block
  reorder hunks (4 statements reordered in the slow-rate section, 14 instructions)
  were conservatively cross-checked as `block-order` too: 2.6% structural —
  within the 12.5% budget under that reading as well; even holding the ENTIRE
  reorder cluster (63 instructions) structural gives 11.8% <= 12.5%. The
  record-mode `--layout` view always classes unreviewed hunks `code-shape`
  ("unclassified hunks are held to the structural budget") and therefore prints
  19.8% for any draft; the reviewed verdict is the checked mode above.

### scas permutation sweep (24 orders of the summary block)

All 24 permutations of `stage_count / score / scaled / slow_rate` were measured
(bytes, then gate): 9 fail to compile (the slow_rate store before its `scaled`
definition), 14 give 1,422-1,423 bytes, and **`scaled -> slow_rate -> score ->
stage_count` is byte-best at 1,418**. Its reorder weight (14 instructions if held
`block-order`, 2.6%) is inside the structural budget, so it is kept; there is no
byte-best-but-over-budget permutation to record.

## 2026-10-18 (later): the walker +1-ref lever — proven unreachable, parked at 1,418 bytes

The pool-walker weight 9→10 target (the unique cost-1 fix mapping the colour
creation order to retail's slot layout) needs one surviving forwarded IR ref
with zero temp/index side-effect. Proven unreachable: in the loop-2 walks the
shallow `link->pool` reload CSEs to the register-resident `pool` (the memcpy
touches only ECX/ESI/EDI), so every compare/copy form folds with its operand
refs (0 ref reaches the walker); forcing the reload fresh makes the compare
real but the arithmetic select arm lowers to a branch (equivalence break) and
the new heavy temp shifts the element indices, which moves the sort to a worse
permutation. The ecl_name_table sweet spot needs a reload c2 CANNOT CSE (a
deep re-deref through a call-clobberable pointer) forwarding into a named copy
with a non-copy use; the pointer walker has no such shape. 45+ measurements,
all fold or perturb. Residual: the bottom-five slot permutation (31
frame-offset instructions) + the ESI/EDI this-piece swap. Unblocked path: the
c2 regalloc/ChoosePhysReg tracer for the this-piece K/priority (the winedbg
hardware-breakpoint attach is the missing fine signal).
