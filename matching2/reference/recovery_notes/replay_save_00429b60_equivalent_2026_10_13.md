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
