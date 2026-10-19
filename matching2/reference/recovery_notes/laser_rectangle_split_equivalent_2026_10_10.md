# Rectangle split 0x0041EB00: equivalent recovery

The C++ in `msvc/equivalent/game/laser_rectangle_split_0041eb00.cpp` compiles,
in the `laser_cut` cluster context, to the 1,171 retail bytes except for one
place: the test of the hit count after the sampling loop.

| | retail | C++ |
| --- | --- | --- |
| 0x2A2 | `mov eax,[esp+30h]` / `test eax,eax` | `mov ecx,[esp+30h]` / `xor eax,eax` / `cmp ecx,eax` |
| 0x2B2 | `xor eax,eax` | (the zero is already in EAX) |

Both builds compare the hit count with zero, branch the same way and leave
zero in EAX for the run search that follows; only the moment EAX is cleared
differs, so the two are the same length and behave identically.

## Cause

The function uses the constant zero often enough for c2 to keep it in a
register. The hit count lives on the stack; after the first allocation round
its live range is cut into pieces, and the piece that holds the lone
`if (hit_count)` has one referencing instruction and no benefit count (a
compare against zero adds none), so `SpillObvious` (c2 0x107A9D71) spills it.
The test is then `cmp [mem],zero`, which puts that block inside the zero
register's piece, and the compare is later split into a load into ECX. In
retail the hit count held EAX in that block, the test was `test eax,eax`, and
the zero piece starts one block later.

For that the hit-count piece needs a second reference that survives to
register allocation. None of these change the bytes: `!x`, `x != 0`, `switch`,
`goto done`, unsigned type, `register`, a copy local, a guarded do-while, the
run counter or cursor declared earlier, swapped counter declarations.
`x < 0 || x > 0` gives the EAX test but the zero register is then lost for the
run search; an early `return hit_count` gives it too but duplicates the
epilogue. The sibling circle split at 0x0041EFA0 has the same retail idiom.

The equivalence build links the cluster's sources in cluster order and keeps
the other cutters as link roots (`roots` in the layout), so the item spawn and
the other shared callees get the same private conventions as in the cluster.

## 2026-10-17: the second-reference lever and its trade-off

The queue's `test`/`je` versus `xor`/`cmp` residual was re-attacked through the
SpillObvious rule in `msvc-c2-immediate-register-candidates`: the hit-count
piece is spilled because the `if` is its only reference and a compare adds no
benefit count. Since `hit_count` only ever increments, a redundant second test
(`hit_count != 0 && hit_count >= 0`, or `!= -1`) is semantically identical and
does give the piece its second reference: the EAX `test` form appears. But
every such form then loses the tail: the model gains an extra `jl` at +0x2B2
and drops retail's `lea ebx,[ebx+0x0]` at +0x2BA (two instructions, 4 bytes).
`count >= hit_count` as the second reference adds a third hunk; the self-def
forms move nothing. This is the documented trade-off ("shows the EAX form but
loses the later zero piece"); closing it needs the SpillObvious trace to see
which piece takes EAX at +0x2BA. Region stays equivalent.

## 2026-10-17: three lever classes tested negative

Measured with the byte script (`diff_dump.py`/`variant.py`), 14 differing bytes
in both hunks throughout:

- **Symbol count** (the lever that closes `replay_save_update`'s base/index
  swaps): 18 variants — 8/16/24/32/48/64 initialiser locals and the function's
  magic numbers named — all identical at 313/316. `OptCmpHashVal` reaches the
  base/index tie-break only, not `ChoosePhysReg`; register-choice does not move
  with the symbol count.
- **Second reference** on the hit count: 14 spellings. `hit_count != 0 &&
  hit_count >= 0` and the `!= -1` guard both reach 315/316 — the EAX `test`
  form does appear — but the 14 differing bytes are unchanged, exactly the
  trade-off above. A saturation guard in the loop (`if (hit_count < 0)
  hit_count = 0;`) and a copy local lose badly (25 and 33 hunks).
- **Cluster context**: 11 drafts varying the `/INCLUDE` roots and dropping the
  `laser_cut` context cluster. The full root set is the best (313/316); dropping
  `SetPolar@ItemPolarVelocity2` costs 317 differing bytes, and any other
  removed root loses a bound symbol and cannot link. Context is not the lever
  here.

The residual stays the two recorded `register-choice` hunks: retail
`mov eax,[esp+0x30]; test eax,eax`, model `mov ecx,[esp+0x30]; xor eax,eax;
cmp ecx,eax`, with retail's trailing `xor eax,eax` at +0x2B2. Region stays
equivalent.

The regalloc trace (`compiler_traces/regalloc/trace_choose_physreg.py` on the
commands `prepare.py` regenerates) confirms the mechanism: the hit-count piece
is `SPILL num=4 prio=0`, spilled at zero priority because the `if` is its only
reference. Eight early-return spellings were tried to give it that reference
without changing the branch form — `if (hit_count == 0) return hit_count;`
and its variants all retarget a branch (+0x198 reaches +0x478 against +0x2B0)
or cost 23–25 hunks. `test-and-chain` is the only form that earns retail's
`mov eax,[esp+0x30]; test eax,eax`, but it then emits a near `jl` where retail
has a short `je`, leaving the same 14 differing bytes. The two requirements —
EAX for the piece, and a short `je` — have not been satisfied together.

## 2026-10-17: the documented K levers do not move it

`msvc-c2-what-adds-a-register-candidate` names the shapes that change `K`
(candidates referenced per block) without changing the code. Six were applied
here against the baseline 313/316, 2 hunks, 14 differing bytes:

| variant | shape | result |
| --- | --- | --- |
| `written-twice` (`hit_count = hit_count;`) | expression twice, merged late | 313/316 — identical |
| `immediate-twice` (`+= 0`, `!= zero_a`) | immediate used twice, one type | 313/316 — identical |
| `fewer-live` (`seen_run` beside the run counter) | fewer live values in the block | 313/316 — identical |
| `named-to-call` | named local passed to a real call | unbound symbol |
| `single-assign-copy` | single-assignment local copied later | a branch retargets |
| `two-loads-same-member` | two locals from the same member | a branch retargets |

The three that compile fold back to the baseline byte for byte, so `K` is not
what decides this contest; the other three change control flow before the
compare is reached. Combined with the earlier second-reference and
symbol-pressure sweeps, this region's EAX/ESI decision is not reachable from
the source shapes catalogued so far. Region stays equivalent.

# laser_rectangle_split 0x0041EB00 — 2026-10-18: the test-form compare recovered (chain-ge0), tail 14 bytes

The equivalent model now compiles retail's hit-test sequence byte-for-byte.
`variant.py` reports `chain-ge0 315/316 0 2 14 0` and `equivalence.py` reports
`"not_equivalent": []`, `base_index_order 0`, `frame_offset 0`, `listed_differences: 2`.
The shipped spelling replaces `if (hit_count)` with

```cpp
if (hit_count != 0 && hit_count >= 0) {
```

semantically identical (hit_count only increments from 0, so `>= 0` is free).
It earns retail's `mov eax,[esp+0x30]; test eax,eax` + `mov [esp+0x2c],esi` +
`je 0x41ef78` exactly, and moves the zero def (`xor eax,eax`) into the run
search like retail; the stream realigns at 0x2c0. The recorded differences are
the remaining tail: `code-shape` at 0x2b2 (the second chain condition's `jl
0x41ef78`, 6 bytes, where retail has `xor eax,eax`) and `alignment-padding` at
0x2ba (retail's `lea ebx,[ebx+0x0]` filler absorbed by that branch). Net 14
differing bytes at 0x2b2–0x2bf.

## Mechanism (traced, c2.dll 13.10.6030 + live traces of model and sibling)

- The shared immediate 0 becomes a global register candidate
  (`CmdIdentifyImmedCandidates` → `GrgRewriteImmedAsReg`). The baseline hit-test
  compare referenced it, pulling the zero piece into the if-block (def at 0x2a6,
  `mov ecx,[esp+30]; xor eax,eax; cmp ecx,eax`).
- Retail and `laser_circle_split` (identical `if (hit_count)` source) emit
  `mov eax,[mem]; test eax,eax` with the zero def *after* the test. Traces
  (`trace_choose_physreg.py`, `trace_target_early_link.py immediate profile`):
  the circle's zero if-piece is spilled (`ColMakeSplitPointOne` →
  `CmdSpillImmedBytes` SPILLIMM ×4 vs the rect's ×1; `SpillOrDefer` spill of the
  zero piece, avail=[8] contested by count-in-EDI) and `Spill` reverts
  globreg-born uses (use-record +0x18 record kind 0xd) to immediates →
  `cmp [mem],0` → riscify `mov eax,[mem]` + `test eax,eax`.
- `SpillObvious` (0x107A9D71) spills a piece iff refs(+0x24)<2 AND (f40(+0x40)<1
  OR (def!=NULL AND def.opcode!=0x26a)). A second reference to hit_count
  (refs≥2) defeats the spill; the piece then keeps EAX and the compare is the
  register `test` form, and the zero piece starts at the run search. The chain
  spelling supplies that second reference; its `>= 0` compare reuses the first
  test's flags (one `test eax,eax` + two branches), so the only emitted cost is
  the second branch.

## Oracle findings (diagnostic patches only; no production change)

- Heap addresses are deterministic across identical link replays: the hit-count
  symbol is 0x37ea624 (candidate n=3), the zero globreg 0x38635e4, the hit-test
  tuple 0x382a054 (verified in the immediate-phase trace).
- Patching `CmdCanEnregImmed` (entry 0x107a5a83 → return-0 tail 0x107a5bb2) for
  exactly that tuple suppresses the Identify-time `GrgRewriteImmedAsReg` for the
  hit-test zero use (recon log: the other 7 zero uses rewritten, ours skipped) —
  yet the emitted body is unchanged (`xor eax,eax; cmp ecx,eax`). The zero
  register at the compare is therefore materialised by a later step (the driver's
  globreg application or the /G6 `cmp [mem],imm` riscify split reusing the live
  zero register), not by the compare's own use. The `CmdCanEnregImmed` case-0x2f
  gate (cmp-vs-immediate-0 not enregistered when the value operand's register
  record is already assigned — call results keep `test r,r`, e.g. the
  `IsPartiallyOutside` test at 0x41ed11) is real but not sufficient on its own.
- The genuinely free knob is the zero-piece cut point: model 0x2a6 vs
  retail/chain-ge0 0x2b2. chain-ge0 moves it with refs≥2.

## Ruled out (~130 variants; all fold back to 313/316 or worse)

- Compare spellings: `!x`, `x!=0`, `0!=x`, `'\0'` literals, bool copies/casts,
  ternaries (`x?1:0`, `x?x:0`, `x?x:x`), ref-bind, pointer load, struct member,
  view-struct + `__declspec(noinline)` (the circle wrapper shape), u-decl
  relations (`>0` signed/unsigned keep the cmp-form and change the branch to
  jle/jbe).
- Types: `(unsigned char)/(char)` reach 314/316 with 2 width bytes (`8b→8a`,
  `85→84`, `mov al`/`test al,al`) but the low-byte test truncates at
  hit_count≡0 mod 256 (reachable at 256 hits when length>3072) — not
  behavior-preserving; `(un)short` 25B; `volatile` counters retarget +0x198.
- Second-reference family (SpillObvious refs≥2 without a second branch): chains
  (`&& ≥0`, `&& !=-1`, `&& count>=hit_count` — third hunk), `&`/`*` of compares
  (frame shift from the setcc temp), `||1`/`?1:1`/comma operators, condition
  self-assignments (`(x=x)!=0`, `+=0`, `|=0`, `*=1`), copy-after-use K-rule
  shapes, `x&0`-style dead inits, `&hit_count`-address compares — all fold in
  global opts before regalloc or add a branch.
- Double-read family (the animation_change_script late-merge shape, this pass):
  anonymous-union views (`hit_count || hit_count2`, `!=0 && !=0`, mixed int/
  unsigned compares), `int hits=hit_count; if (hits != 0 && hit_count >= 0)` and
  `if (hits || hit_count)` — the `&&` forms reduce to chain-ge0 (the jl remains),
  the `||`/skip forms CSE early to baseline or shift the frame. The late merge
  that gave animation_change_script its K point does not translate: the union/
  copy reads of one local merge before Spillcosts.
- Oracle-side: byte-type revert path (`CmdSpillImmedBytes`, type&0xFFF==1) is
  the only reverter that fires for this compare and it narrows the test.

## What remains

One `jl 0x41ef78` (6 bytes) at 0x2b2 where retail has `xor eax,eax` +
alignment filler; 14 differing bytes 0x2b2–0x2bf. Closing it needs the
SpillObvious second reference to hit_count without emitting a second branch
(all ~40 shapes tried fold or branch), or a shift of the zero-piece cut point
that keeps the compare immediate without the chain. Region stays equivalent;
staged for integration: the chain-ge0 model and the layout differences
(`code-shape` 0x2b2, `alignment-padding` 0x2ba).

### 2026-10-19 (round 2): 14 bytes -> 1

`variant.py` `315/316 instructions, 1 differing byte at 0x2ad`; the layout
records one `code-shape` difference at 0x2ac (`je L+0x478` against
`jle L+0x478`).

The closing shape is a nested guard on the same counter,

    if (hit_count) {
     if (hit_count > 0) {
      int cursor=0;
      ...

A single `if (hit_count)`, `if (hit_count != 0)`, `if (hit_count > 0)`,
`if (hit_count >= 1)` or any `!= 0 && >= 0` conjunction regresses to the
14-byte form: with one condition the front end enregisters the zero for both
the guard compare and the loop-entry compare (`mov ecx,[esp+0x30];
xor eax,eax; cmp ecx,eax`), while retail's guard is `mov eax,[esp+0x30];
test eax,eax` with the zero materialised after the branch. The second
(nested) condition keeps the counter in EAX for the guard, which reproduces
retail's `test eax,eax`; c2 then merges the two conditions into one compare
whose failure set is `<= 0`, i.e. `jle` — the single remaining byte.

The residual is `msvc-c2-immediate-register-candidates`: the zero is
enregistered because the guard compare and the loop compare share it, and no
honest spelling measured (nested duplicates, copies, pointer reloads,
unsigned/`>=1` forms, cursor placement, `for` loops, do/while, ternaries)
keeps `test eax,eax` with a `je` failure set.

### 2026-10-19: 47 more guard spellings, no change

The psearch sweep crossed 5 outer guards (`hit_count`, `!= 0`, `(unsigned)`, `(unsigned) > 0u`, `< 0 || > 0`) with 8 inner ones (unsigned `> 0u`/`>= 1u`/`!= 0u`, `!= 0`, the two `||` orders, `!(== 0)`, `>= 0 || < 0`), plus single-guard and goto/early-return forms.
- The best result is still 1 byte at 0x2ad. The merged compare takes the inner relation: an unsigned inner gives `jbe` instead of `je`.
- An inner `!= 0` is folded as redundant, which brings back the 14-byte form.
- `if (hit_count == 0) goto done;` and its unsigned variant also give the 14-byte form.
- `return 0` / `return hit_count` early exits give 466 bytes.
- Also 2026-10-19: switch forms of the guard all give the 14-byte form, as do a ternary goto and a named `bool any`. The switch forms tried were `switch (hit_count) { case 0: goto done; }`, a `case 0: break; default:` body, and a switch nested in the `if`.
