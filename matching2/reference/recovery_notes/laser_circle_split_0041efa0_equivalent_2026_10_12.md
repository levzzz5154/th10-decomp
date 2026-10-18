# Circle laser split 0x0041EFA0: equivalent recovery (2026-10-12)

**Status (2026-10-12, later the same day): registered equivalent recovery, 241 of 302 instructions identical.**
The model now has its own source (`equivalent/game/laser_circle_split_0041efa0.cpp`, a member of
a view struct derived from the cluster's `CutLaser`) with the shape of the rectangle split
sibling; the two dummy vectors and the frame shift are gone. Of the 61 remaining instructions,
most follow from one register contest: retail keeps the line-animation resource in EDI across
the creation call and the sample count in its stack slot (EDX between calls); the model keeps
the count in EDI and spills the resource. Declaration order, named locals and a `for` loop do
not change it. Recorded classes: 31 register-choice, 8 evaluation-order, 5 code-shape,
1 stack-slot-order, 1 operand-order, 1 alignment-padding; structural hunks stay under the
12.5% budget. Everything below this paragraph describes the earlier parked draft.

The parked candidate (`layout/ltcg/laser_cut/circle_cut.cpp`) is now a
registered equivalent recovery (`layout/equivalent/laser_circle_split_
0041efa0.json`): 1,108 of 1,108 bytes used, 229 of 302 instructions
identical, 72 instructions in 59 recorded differences, 1 frame-offset.

## What unblocked it from the 2026-10-10 parking

Two dummy `CutVector` locals (`align_a`, `align_b`) declared after
`progress` shift the local symbol ids so `point += step` loads the point
component first, matching retail (the parked note's residual 2).  The same
shift moves every stack frame slot up by 4, which the layout records as
`frame_shift` (deltas [4]).

The float constants the model loads from .rdata are bound to their retail
pool addresses in `bindings` (0.5/6/12/16/18/32/192/224/448/-192 at
0x470AFC..0x470B4C, 0x470BCC, 0x470C0C, 0x470CD8, 0x470D1C, 0x470C00).

## The recorded differences

* 20 pure frame-offset instructions (the +4 slot shift).
* ~24 register-choice hunks: `count` lives in EDI in the model versus EDX in
  retail, `hit_count`/`resource`/`bank` swap EDI/EDX the same way (the
  parked note's residual 1).
* ~15 code-shape hunks: the `point += step` scheduling, the `CreateOffset`
  argument order and the merged-tail stores.

The extent probe in `tools/matching/equivalence.py` no longer mistakes
another function's switch table (TitleOptions' in this link) for this
function's own: a tail-zero region whose retail bytes contain no `ff /24`
table instruction cannot gain one in the model (commit 1ef091c3).

## Remaining

None for the equivalence route.  A byte-exact recovery would additionally
need c2 to reproduce retail's register contest for `count` and the tail
merges; the model keeps the readable semantics either way.

## 2026-10-17: register-contest state reviewed; parked

The 31 register-choice hunks are the note's residual 1 (the `count`
EDX-versus-EDI contest, with `hit_count`/`resource`/`bank` following the same
swap): one ChoosePhysReg tie decision, the same family as
`font_atlas_draw_text`'s substitution table. The note's verdict ("None for
the equivalence route") was reached after the source lever sweep; the
`msvc-c2-what-adds-a-register-candidate` K shapes need the Spillcosts numbers
for this function's blocks before one can be chosen.

Region stays equivalent (407 differing bytes).

## 2026-10-17: the x87 storage lever tested; it needs a frame gap

`volatile double dx` closed `item_update`'s frame gap and improved that model
by 214 differing bytes, so the same lever was applied here, whose residual
also carries x87 hunks (`fadd`, `fstp`, `fld`). Six spellings, measured with
the byte script against the baseline 241/302, 47 hunks, 407 differing bytes:

| variant | identical | hunks | differing bytes |
| --- | --- | ---: | ---: |
| baseline | 241/302 | 47 | 407 |
| `named-dxdy` (squared distance named) | 241/302 | 47 | 407 |
| `volatile-progress` | 240/302 | 47 | 387 |
| `volatile-dy` | 219/302 | 57 | 576 |
| `volatile-dxdy`, `volatile-both`, `volatile-distance` | — | — | a branch retargets |

Nothing improves. The reason is now clear from the frame survey: this region
has **no frame gap** (`code_bytes` equals the region size), whereas
`item_update` was 8 bytes short and the `volatile double` worked by supplying
that missing home. Forcing values to memory where retail already agrees on the
frame only disturbs the schedule.

So the x87 lever is conditional on a frame gap, not general to x87 residuals.

## 2026-10-18: Spillcosts/ChoosePhysReg traced; first byte movement (407 -> 402)

The overnight question ("the count EDX/EDI tie needs the Spillcosts K numbers")
was answered with the c2 tracers (sandbox copies of
`compiler_traces/regalloc/trace_spillcosts.py` + a block-pointer probe; the
model's LTCG link captured via a one-entry commands.json). Count semantics were
verified against Ghidra 0x0041EFA0 first: `count` is the 0-based sample index
(def at entry, `cut[count]` store, `++count` at loop end, bound of every tail
scan), `hit_count` is returned; the model matches retail control flow.

Measured allocation (final Spillcosts priorities -> ChoosePhysReg registers):
_object 252 -> ESI, _cursor 227 -> EBX, **_count 73 -> EDI**, unnamed 60 -> EBX,
_index 56 -> EBX, unnamed 44 -> ESI, _run 28/14, _this 24, _center 8;
**_resource (g_laser_manager->line_animation) is single-block (refs 4 x K 7 x w
2 = 56) and loses: it is spilled to [esp+0x2c]**. Retail is the exact mirror:
resource sits in EDI across the Allocate call (`mov edi,[ecx+0x458]` ->
`mov ecx,edi`), count lives in memory with EDX pieces (`xor edx,edx` feeds both
count and hit_count homes; `mov edx,[esp+0x2c]` reloads per use). Mechanism:
count's live range crosses the CreateOffset block where the Allocate result
(18 refs) forces pressure; retail splits count at the calls, the model hands
count the third callee-saved register and pushes resource out. The retail-like
sibling laser_rectangle_split (2 residual hunks, same tail source) confirms:
its _count converges to **-45 (spilled)** where ours converges to **+73**;
pass-1 totals are identical (83) and the divergence happens in the later
Spillcosts fixpoint passes (its count re-splits and re-walks with refs
scattered over 2 blocks; ours stabilises at 73). The function has 44 blocks
walked in ~5 passes (block pointer at [esp+8] of the 0x107A98EE frame); EBP is
unavailable throughout (frame pointer after `and esp,-8`), so live-across-call
values only contest ESI/EDI/EBX.

The 8 evaluation-order hunks are the `msvc-c2-operand-order-mechanism` x87
`fld/fadd` sort: the point+=step pairs load the operand with the larger
OptHashNode class first (measured: 0x12008 vs 0x14008 = classes 1 and 2; the
z pair is flipped in the raw bytes too). Classes are `(local number & 7) << 13`
bases, numbered at first use, so the flip needs +/-2 on one side.

**Lever that moved bytes: folding the named `index` and `resource` locals into
the CreateOffset call expression** (one statement,
`reinterpret_cast<...>(...->line_animation)->CreateOffset(script*2+17,&point)`):
407 -> 402 differing bytes, 241 -> 243 identical, 47 -> 46 hunks. It fixed the
@0x39e x87 pair (the `origin+step*start` operands) by reordering the IR nodes of
the inlined body vs the this-computation: retail emits the hit-body loads as
[bank, g_sprt, resource] (g_sprt is the inlined CreateOffset body's first
statement, a rematerialized load exactly like the anchor 0x448db0), the model
with named locals emitted [bank, resource, g_sprt].

Ruled out (all measured flat at 407 or worse, ~35 shapes): named locals at call
arguments (SetPolar angle/length, Spawn this/args, IsPartiallyOutside bounds,
bank pointer, script), expression-twice hit tests, field-wise origin/point
copies (991/972 bytes!), dead-branch second uses (`if (x!=x) goto done` folds
before Spillcosts), kept-count copies for the whole tail, counter/type/order
spellings, sample_position variants, compound-vs-simple scalar assignments,
accessors at every use position, statement moves between `step` and `point`'s
first uses (417-423). The v12 probe `CutVector* polar_result=step.SetPolar(...);
step=*polar_result;` jumped to **256/302 identical** (the class shift works!)
but its copy adds code (1009 bytes) - the clean shape needs a first-use local at
the SetPolar statement that survives folding; copies and dead uses fold away and
do not move the numbering.

Next step: find the surviving local/first-use shape at the SetPolar statement
(the only statement between `step`'s and `point`'s first uses) that shifts the
pair classes +2 without adding code, then chase the count/resource EDI contest
with the same K lever once the x87 pairs are aligned.

### 2026-10-18 later: lever stacking reaches 394 bytes

The x87 fld/fadd class mechanism (msvc-c2-operand-order-mechanism) gives two
working shift levers that stack with the node-order lever:

1. `both-inline` (named index/resource folded into the CreateOffset call
   expression) - IR node order, fixes the @0x39e pair.
2. The operand-sort class shift at the `point=step+position` statement: a
   first-use pointer local pair there (`CutVector* sp=&step; CutVector* pp=
   &position; point=*sp+*pp;`) shifts the temp-id classes and flips the
   point+=step pairs back to retail's order (verified in the diff: @0x234/0x245
   fully match). Non-const pointers are required (const forwards and folds
   away); the cost is the register-indirect load form (~24 bytes, hunks @0x74-
   0xba). A call-result local with a live self-copy at SetPolar
   (`CutVector* pr=step.SetPolar(...); step.x=pr->x; step.y=pr->y;`) reaches
   262/302 identical (the same +2 class shift, different cost profile).
3. The double accessor use in the CreateOffset index argument
   (`int index=GetScript()+GetScript()+17;`, accessor added to CutLaser) drops
   the byte count further (402 -> 394).

Best by the bytes gate: **394 bytes** (236/302 identical, 47 hunks, tail 0) =
`int index=GetScript()+GetScript()+17;` + the sp/pp pointer locals at the add +
the `GetScript` accessor in types.hpp. Best by identical instructions: 262/302
(426 bytes, 39 hunks) = the y-copy-xy call-result shape. The remaining
families: the count/resource EDI contest (~16 hunks; the Spillcosts K lever
needed), the entry origin-copy scheduling (@0x25-0x6b), the CreateOffset body
rotation (@0x1b3-0x1f6), the padding lea registers (@0xeb/@0x299).

Ruled out on the new parity: kept-total tail copies, dead-branch second uses,
bank/sample_position locals (all flat at 394).
