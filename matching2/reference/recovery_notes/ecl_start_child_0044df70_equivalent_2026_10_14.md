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

## 2026-10-17: the zero-register compare lever probed; parked

The five code-shape hunks are the note's own c2 fact: a compare of a
register *variable* against 0 is rewritten to the zero register, a temporary
keeps `test`. Moving the pop check's `cursor` compare onto a temporary
(`if (stack->cursor - 4 >= 0)` with the local assigned inside) overshoots to
26 hunks: the split loads and the loop scratch rotation change with it. The
eight register-choice hunks are the `msvc-c2-riscify-scratch-registers`
rotation (round-robin scratch assignment scanned backwards), which needs the
pre-Riscify dump before a source lever can be chosen.

Also recorded: the gate's structural-differences budget already rejects this
model at 18.2% coverage (budget 12.5%), so every future variant must clear
that gate too.

Region stays equivalent (285 differing bytes).

# ADDENDUM for reference/recovery_notes/ecl_start_child_0044df70_equivalent_2026_10_14.md
# (staged; append verbatim below the existing 2026-10-17 section)

## 2026-10-18: zero-register compare mechanism decoded; zero-cost levers negative

The five code-shape hunks are now a closed-form mechanism (c2 13.10.6030, asm
verified). `CmdCanEnregImmed` (0x107A5A80) case `cmp` (0x2f): the `cmp reg,0`
immediate use is EXCLUDED from the shared-zero candidate iff the compared
operand is kind-1 with a register symbol other than the shared temp class
(symbol byte@+4 != 2; the temp class is 108ab2ec, byte@+4 == 2). Excluded ->
the immediate stays -> `test reg,reg`; included -> `cmp reg,zero-reg`. The
`mov reg,0` case is symmetric (dest symbol byte@+4 == 2 -> rewritten).

Measured piece structure (trace_spillcosts / trace_choose_physreg, oracle/):
model zero candidate pieces = {saved_frame-def, cmp#1} -> EDX,
{cmp#2, else-push x2} -> ECX materialized at 0x124, {time=0}, {*instruction=0}
revert to immediates. Retail = cmp pieces spill (1-ref, f40=0 -> SpillObvious)
to `test`; the else piece starts at 0x189 (`xor ecx,ecx`).

Diagnostic proofs (measured, each with side effects):
- `saved_frame = *(volatile int*)&index - *(volatile int*)&index` removes the
  immediate-0 def; the cmp#1 piece becomes 1-ref and @0x25 flips to
  `test eax,eax` (33 hunks total: volatile loads perturb the prologue).
- `-original_cursor == 0` / `!= 0` makes the compare's zero use vanish (flags
  fuse): 21/26 hunks but +73/+9 bytes (neg + scheduling shifts).

Ruled out this pass (byte-gated, all measured):
- Zero-cost removal of `saved_frame = 0`'s immediate use: `original_cursor -
  original_cursor`, `^ self`, `arguments_offset - arguments_offset`, `!= self`,
  `& ~self`, `index - index` (non-volatile) — all FE-fold back to the immediate
  0 (285-294 bytes, @0x25 unchanged).
- Non-temp compare operand at zero cost: `original_cursor + 8 == 8`,
  `0 == original_cursor`, `!x`, `x|x==0`, `x*1`, `x/1`, `x<<0`, `x^0`, `x&x`,
  `x+x==0`, `-x==0` (costs), `x-x*2==0`, `0-x==0`, `x*-1==0`, field-address
  volatile read (kind-6 compare is not excluded -> riscified `cmp ebx,edx`),
  stack-pointer LEA base (folds), argument-offset compare (387 bytes).
- Distinct constant kind for the @0x131 pop check (`add ecx,0xfffffffc` vs
  `sub ecx,ebx`): `4u`, `sizeof(int)`, `enum` constant, `const unsigned`,
  `const int`, `(short)4`, `~3`, `0xFFFFFFFC`, `(int)0xFFFFFFFCu`, `-(-4)`,
  `(-1<<2)`, `+ -4` — the FE canonicalizes every spelling to the shared signed
  int-4 candidate (all 285, `sub ecx,ebx`); the -4 must arrive as a distinct
  operand kind (hash is kind+value) or the use must be excluded (case 0x2d/0x32
  only excludes ESP/EBP destinations).

Best remaining hypothesis: the compare operand must be a k2-symbol copy
(parameter read, as `*(volatile int*)&index` produces; note those copies carry
physical/pseudo register symbols at IdentifyImmedCandidates) or a call return.
`original_cursor` derives from `child->stack.cursor` (a memory load whose base
chain roots at the temp-class `child`), so its node is temp-class at identify
time in every spelling tested. A construction that routes the compared value
through a parameter-symbol copy at zero instruction cost is the open problem.

## 2026-10-18 addendum: the inlined-helper k2 carrier — negative, parked for good

The last documented carrier (rule msvc-c2-choosephysreg-cost-score:
inlined-helper params as copy-defined candidates) tested as `__forceinline`
helpers wrapping the compares (by value and by `const int&`, at cmp#1 / cmp#2
/ both / inverted): all 6 variants byte-identical to baseline (285 differing
bytes). c2 inlines the helper before CmdIdentifyImmedCandidates, so the
parameter copy-def never exists at identify time and the compared node stays
the temp-class `child->stack.cursor` load. With the FE folding every
zero-cost spelling back before identify time, the region stays at 285
differing bytes / 21 hunks and is parked for good. Full variant ledger and
reusable oracle traces under /tmp/campaign/ecl_start/.
