# Score-record list tick: native LTCG residual at 0x0041C330

2026-09-27. This region remains assembly. A readable C++ model and live Ghidra
evidence are retained in `matching2/build/experiments/score_tick`; the model is
not eligible for promotion because its complete compiler contribution is 272
bytes, whereas retail requires 274 bytes.

## Verified behavior and representation

Live Ghidra `disassemble_function` and `decompile_function` for `th10.exe`
confirm that the function receives its owner in EDI, walks the list at owner
+0x18, saves the successor before invoking callbacks, and returns 1. A node has
a dispatch pointer at +0, predecessor at +4, successor at +8, state at +0x0C,
timer previous/current/elapsed/speed at +0x10/+0x14/+0x18/+0x1C, and an unsigned
retirement byte at +0x50. The owner has a cursor at +0x434 and live count at
+0x438. Dispatch slot +8 is the update callback; slot +0x10 is destruction.

A nonzero retirement byte is incremented with byte wrapping and triggers
retirement when its new value is at least 2. State 1 also retires the node before
update. Otherwise, a nonzero update result retires it. Retirement calls the
destruction callback, decrements the live count, unlinks both neighbors, repairs
the cursor to the predecessor when necessary, and calls `free` at 0x004524A1.
The two retail retirement tails are retained in the source model.

For a surviving node, timer previous receives current. Speed strictly between
the external bounds at 0x00470B68 and 0x00470B64 increments current and adds
1.0f to elapsed. Other speeds accumulate into elapsed and convert the retained
x87 sum through `__ftol2` at 0x00463B2C. The matching fractional load order is
obtained with:

```cpp
double step = *node->speed;
node->current = int(node->elapsed = step + node->elapsed);
```

The double temporary keeps the speed-first x87 evaluation. The assignment
expression stores elapsed with `fst`, retaining the sum for conversion.
Separating the accumulation from conversion would reload a rounded binary32
value. The integral path uses `++current; elapsed += 1.0f` and binds the pooled
1.0f literal to 0x00470AFC through a declared constant alias.

## Bounded experiment and current evidence

The scratch project extends registered
`layout/ltcg/score_records_advance_frame_0041c480.json`: remove its 48-byte
synthetic anchor, select the real tick body at 0x0041C330, declare its source as
an additional source, and replace the former gap with 62 bytes starting at
0x0041C442. The public 0x0041C480 member remains the sole root. The existing
synthetic entry and its 10-byte extent remain unchanged. Shared node/owner
types are in scratch `include/th10/game/score_record_list.hpp`.

Reproduce the preserved model:

```sh
python3 matching2/tools/matching/probe.py \
  --source src/unidentified/FUN_0041c480_0041c480.cpp \
  --project matching2/build/experiments/score_tick/msvc \
  --output matching2/build/experiments/score_tick/reprobe --json
```

The final fresh run is `score_tick/probe_final.json`. It correctly rejects the
tick because the required 274-byte extent exceeds its 272-byte MAP CODE
contribution. `score_tick/best_evidence.json` records direct, unmasked PE-byte
comparison: the existing 91-byte callback at 0x0041C480 is exact with zero
differences; the 274-byte target window at 0x0041C330 differs in 235 bytes,
largely because the control-flow difference shifts later instructions.
`score_tick/disassembly.txt` contains the final native emission, and
`ghidra_disassembly.txt` / `ghidra_decompile.txt` contain the live reference.

The remaining structural mismatch is the early retirement control flow.
Retail emits separate dispatch/ECX setup for the retirement-byte path, jumps
forward to its destruction call, and prepares the same dispatch register after
the state comparison before branching to update. The current compiler combines
the retirement-byte and state checks before dispatch setup. The first unlink
also loads predecessor before successor, opposite retail's first tail; the
post-update tail and timer instruction families are reproduced.

Tested source forms include two tails with a goto, explicit three-tail source,
capturing the successor before the first unlink assignment, a member Tick
instead of a free function, an explicit retirement-byte local, and a compiler
read/write barrier before the state check. These remain 272 bytes. A single
combined retirement/update condition collapses to 206 bytes and is unsuitable.
The independent `score_tick_dispatch` scratch captures a 277-byte alternative
that shares the unlink tail after separate virtual destruction calls; it has
the useful forward block layout, but EAX versus EDX dispatch allocation prevents
the two calls from merging into retail's single early destruction call.

Do not change the maintained manifest or replace the assembly body with these
models. The next useful lever is to preserve the separate early dispatch setup
while merging the first two virtual destruction calls into one forward call
site, retaining the distinct post-update retirement tail and exact caller ABI.

## 2026-10-02 genuine-caller resume

The resumed scratch layout is schema 2: the real 91-byte `AdvanceFrame`
callback is the entry and its two retail calls reach the complete tick model.
The earlier synthetic context has been removed. This reproduces the same
272-byte baseline, with the callback still byte-exact.

Seven new ordinary C++ variants were measured: an inline early-dispatch bool
helper; that helper with predecessor setters taking a pointer by value or
const reference; the baseline with each setter; a nested traversal loop; and
an embedded timer with inline `Advance`. The dispatch and timer variants emit
277 bytes, setters on the baseline emit 272, and the nested loop emits 283.
None reproduces the required complete 274-byte contribution. The maintained
assembly body and its ownership remain unchanged.

Reproducible source, disassembly and unmasked byte evidence are retained in
`matching2/build/experiments/score_tick_resume_20261002/final_evidence.json`.
The register allocation around the two early virtual calls still differs;
these failed candidates receive no recovery credit.
