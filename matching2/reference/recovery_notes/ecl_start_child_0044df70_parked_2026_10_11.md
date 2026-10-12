# ECL StartChild 0x0044DF70: parked, about 82 of 165 instructions differ (2026-10-11)

The anchor in `src/script/ecl_child_pair.cpp` was rewritten with inline
`PushWord`/`PopWord` helpers that take pointers, a `while` argument loop and a
saved-base local. It emits 557 bytes against retail's 550. SpawnChild stays
exact. The function is still assembly-owned.

## What retail's shape says

- `edi = source + 4` is computed once at entry and every `*pc` goes through it.
  `source` itself has no register: it is reloaded from its parameter home
  (`[esp+24h]`) in each block that needs it and stays in EDX across the tail.
- `index` is read from its home twice (EDX at entry, EBX before the loop) and
  its home is then reused for the destination pointer, so it is a plain
  parameter whose whole-range allocation failed and was split into pieces.
- Zero lives in EDX from the `saved = 0` store to the first push, and the
  `cursor + 4` temporary of that push is in EBX.

## Why the model differs

1. **`T** pc = &param->field` is forwarded.** c2 rewrites every `*pc` as
   `[source+4]` when `pc` has one assignment, so `source` inherits all its
   uses and takes ESI. Standalone rig results (`cl /O2`, 30 spellings): member
   of `this`, reference, local struct member, iterator object, inline helper
   parameter, pointer arithmetic, casts, a `do`/`for` wrapper all forward.
   Only a second assignment (`if (x) pc = other;`) or an assignment inside a
   `goto` loop (hoisted as a loop invariant) keeps `add reg,4` and leaves the
   parameter in memory with per-block loads, which is retail's shape.
   A second `pc = &source->instruction;` inside the argument loop is not
   removed (it emits the load and add again, as retail's interpreter does at
   0x0044FB7E); before the loop it is merged and forwarding returns.
   Address-taking through inline helpers and same-size type punning are
   cleaned up and change nothing.
2. `volatile` on `source` reproduces item 1's effect but reloads `source` in
   the tail where retail keeps EDX. It is a stand-in, not the answer.
3. With `pc` separate, descriptor and selector are swapped (EBX/EBP). The
   ChoosePhysReg trace gives selector+index 113 and descriptor 111; a zero
   immediate limited to EBX puts cost 300 on EBX, so the first of the two takes
   EBP. Retail needs descriptor first; then index/selector fails over its
   whole range (EBX is used by the push temporary) and is split, which gives
   the two loads of `index`, and zero gets EDX.
4. The integer resolver stand-in is an exported `__fastcall` with a dummy
   first parameter, so the model has `xor ecx,ecx` before the call. Retail has
   none: the callee needs its natural convention in this cluster.

## Next steps

- Find a zero-code source reason for `pc` to have two assignments or to be a
  hoisted loop invariant (item 1). Everything else follows from it.
- Then close the 2-point priority gap of item 3 and remove the export of item 4.

Tools: `reference/compiler_traces/scheduler/capture_link.py` plus
`regalloc/trace_choose_physreg.py` on the cluster link; StartChild is the
function with 30 blocks whose first choices are ESI 188 and EDI 158.


## Second-assignment experiments (2026-10-12)

Measured with the real cluster build (the anchor sizes are hard constraints:
SpawnChild must stay at its retail address, so StartChild must be exactly 550
bytes):

* second `instruction = &source->instruction;` at the top of the argument
  loop: 582 bytes (+32) — the reload form is longer, not shorter.
* the same assignment at the end of the loop body: 566 bytes (+16).
* shrinking the `.text$06layout` filler by the growth lets the cluster link,
  but the function itself still overshoots its retail extent, and the anchor
  mechanism pins it at 0x44DF70 — the overlap is fatal.

The two-assignment shape is longer in this context, contradicting the
standalone-rig expectations of item 1; the per-block source reloads add more
than the forwarded-pointer form saves.  The register contest (item 3) and
the exported resolver (item 4) remain the open levers.


## Why the dummy resolver argument cannot be dropped (2026-10-12)

The `xor ecx,ecx` before the resolver call costs 3 of the 7 excess bytes.
The dummy first parameter is dead in the callee body, but it cannot be
removed:

* The 4-argument `__fastcall` ABI is what places `frame` in EDX; a 3-arg
  form would place `frame` in ECX, contradicting the retail body (which
  reads the frame from `[edx+4]`).
* The semantic region 0x0044FF00 is exact at 124 bytes with the same 4-arg
  body; changing its signature would break it.
* c2's IPCG does not drop the dead first argument across the `code_seg`
  pragma boundary that pins the anchor body to 0x0044FF00.

With the zero-store variant (557→553) and the mandatory 3-byte xor, the
model lands at exactly 553 — 3 bytes over the 550-byte retail extent.  The
equivalence machinery compares code at equal extent, so the region stays
assembly until a source shape makes the model 3 bytes shorter (or the
register contest of item 3 shifts the scheduling enough to close the gap).
