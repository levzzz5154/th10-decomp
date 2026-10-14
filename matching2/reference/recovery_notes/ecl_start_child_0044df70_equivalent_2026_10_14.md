# ECL StartChild 0x0044DF70: accepted as an equivalent recovery (2026-10-14)

Model: `equivalent/script/ecl_start_child_0044df70.cpp` (with SpawnChild and a
synthetic caller as context; the real int/float/script resolver bodies are
context sources). Gate result: 550 of 550 bytes, 144 of 165 instructions
identical, 21 recorded differences (loop scratch-register rotation,
evaluation order, and five code-shape instructions where a compare uses the
zero register instead of `test`/`js`). Earlier history:
`ecl_start_child_0044df70_parked_2026_10_11.md`.

## What moved it from 76 to 21 differences

Measured with the real gate (`equivalence.py --layout`), not the cluster probe.

1. **Loop shape.** Retail computes the destination pointer and the operand
   offset *after* the loop guard: they are strength-reduced induction
   variables, not source variables. Writing the destination as
   `&data[arguments_offset]` inside the loop with `arguments_offset += 4`, and
   the operand as `values[(descriptor + 4) >> 2]` inline, gives retail's
   preheader and flips the descriptor/selector priorities (descriptor EBP,
   selector EBX, as retail).
2. **Keep `index` on the stack.** That loop shape alone made LTCG pass
   `index` in EAX and `child` in ECX. c2's `MdmFlexParams` (0x107ADBE0, now a
   named function in the Ghidra c2.dll program) only turns a parameter into a
   register parameter when its entry-block load is a plain copy of the
   *unsplit* parameter symbol; retail's `index` was split (two loads from its
   slot), so it stays on the stack. Reading it again through
   `*(volatile int*)&index` for the selector reproduces the split, the
   two loads and retail's convention (child in EAX, RET 8).
3. **One read of `source` after the loop.** `source` stays `volatile` (retail
   reloads it per block), but a local copy taken right after the loop is kept
   in EDX through the frame pushes like retail; with EDX taken, the constant 4
   lands in EBX and the two branches' last pushes tail-merge again.
4. **Pop check written as `cursor - 4` into a local, then `>= 0`.** This keeps
   the zero constant's tail piece out of the pop branch.

## Tools added

- `reference/compiler_traces/regalloc/trace_flex_params.py`: logs
  `MdmFlexParams` per function (entry-block tuples it walks, deferred loads
  with their blocked-register sets, `MdmAllocateFlexParam` assignments and
  every parameter's disqualify byte).
- `reference/compiler_traces/symbols/c2_symbols.json`: c2.dll public symbol
  addresses (`@MdmFlexParams@4` 0x107ADBE0, `@CmdIdentifyImmedCandidates@4`
  0x107A5BCF, `@CmdCanEnregImmed@8` 0x107A5A80, `@SpillOrDefer@12`
  0x107B3EDA, ...).

## c2 facts learned (13.10.6030)

- `CmdIdentifyImmedCandidates` makes one register candidate per immediate
  value for the whole function (hash by operand kind and value); float,
  pointer and unsigned zeros all share it.
- `CmdCanEnregImmed` excludes `cmp reg, 0` on a temporary from that candidate,
  but a compare of a register *variable* against 0 is rewritten to use the
  zero register when a zero piece is live.
