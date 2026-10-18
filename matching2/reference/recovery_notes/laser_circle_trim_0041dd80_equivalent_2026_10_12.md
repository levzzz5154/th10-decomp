# Circle laser trim 0x0041DD80: equivalent recovery (2026-10-12)

**Status (2026-10-12, later the same day): registered equivalent recovery, 260 of 345 instructions identical.**
The model itself is unchanged (it is the `laser_cut` cluster's context body, which exact
clusters depend on). What changed is the review of its 57 differences hunk by hunk instead of
counting every one as structural: 20 register-choice, 13 evaluation-order, 10 stack-slot-order,
1 operand-order, and 13 structural (11 code-shape, 2 branch-target), which is within the 12.5%
budget. No call, callee or named address differs. This is the weakest of the registered
recoveries and the first candidate for a rewrite in its own source like the circle split.
Everything below this paragraph describes the earlier parked draft.

The in-cluster candidate (`layout/ltcg/laser_cut/circle_trim.cpp`, already an
anchor body of the `laser_cut` cluster) is now a registered equivalent
recovery (`layout/equivalent/laser_circle_trim_0041dd80.json`): 1,238 of
1,238 bytes used, 260 of 345 instructions identical, 85 instructions in 57
recorded differences.

## Recorded differences

* 36 code-shape hunks: evaluation-order and scheduling differences in the
  sample walk, the run-spawn epilogue and the model's handling of the
  playfield bounds (`data_00470b04`, 448, -192, 192).
* 19 register-choice hunks: the hit counter, resource pointer and bank
  pointer live in different registers (the same contest the parked
  rectangle/circle notes describe).
* 2 branch-target hunks: the model merges two identical walk tails that
  retail keeps apart (or vice versa); both destinations run the same code,
  which `listed_branch_targets` records.

## Bindings

The model's float constants are bound to their retail pool addresses
(16.0 at 0x00470B48, 32.0 at 0x00470BCC, -192.0 at 0x00470B40, 192.0 at
0x00470B3C, 448.0 at 0x00470B38, 18.0 at 0x00470C0C, 6.0/12.0/2.0/1.0 at
their pool slots).  The layout reuses the rectangle split's absolute
symbol coverage plus the trim-specific data symbols (`data_00477818`,
`data_0047781c`, `data_00470b04`).

## Procedure notes

The work-directory-keeping variant (`equivalence_keep.py`, env
`EQUIV_KEEP_WORK`) was used to recover the model map for identifying
unbound constant references; the candidate keeps its two alignment locals
from this session's first experiment (they changed nothing measurable for
the trim, but were present during validation).

## 2026-10-17: state reviewed; parked

The 57 hunks are the same three families the parked rectangle/circle notes
describe: the hit-counter/resource/bank register contest (20), the
sample-walk and run-spawn scheduling (34), and the two merged walk tails
(2, recorded via `listed_branch_targets`). No new lever applies: the
register contest needs the Spillcosts/ChoosePhysReg numbers for these
blocks, and the walk-tail merge is the distinct-argument shape the
tail-merge survivor levers do not move (as `recovery_script_executor`
re-confirmed this session).

Region stays equivalent (870 differing bytes).

# Addendum for `reference/recovery_notes/laser_circle_trim_0041dd80_equivalent_2026_10_12.md`

## 2026-10-18: the `return hit_count` spelling closes 4 hunks; differences regenerated and the gate passes

The trimmed-early tail in the run walk (`if (length>18.0f) {...} else {...}`) was
spelled `else {retired=1;goto done;}`; the byte-exact sibling
`src/game/laser/laser_rectangle_trim.cpp` (TrimRectangle 0x0041D880, semantic
region) spells it `else {retired=1;return hit_count;}`. Adopting the sibling
spelling alone raises the model to **274 of 345 instructions identical, 865
differing code bytes** (from 260/345, 870) and closes 4 recorded hunks.

The recorded `differences` in the layout were regenerated from the current
build (53 hunks) with reviewed classes: 25 `register-choice`, 11 `code-shape`
(0xef's alignment filler is `jmp`+`lea` where retail has a one-byte `nop`, so
it is structural, not `alignment-padding`), 5 `branch-target` (the
`listed_branch_targets` pairings), 5 `stack-slot-order`, 5 `evaluation-order`
(the object-field store block and the two moved `fadd`s), 1 `operand-order`
(0x249), 1 `alignment-padding` (0x4d3's `int3`). With those classes the strict
`equivalence.py --name laser_circle_trim_0041dd80` check now passes: 1,238 of
1,238 bytes used, 0 base/index swaps, 0 frame-offset, 71 instructions in 53
recorded differences. Previously the region failed the structural budget
(111 of 345 instructions in structural hunks, 32.2% against 12.5%).

Verified unchanged by this edit: `probe.py --source
src/game/laser/laser_rectangle_trim.cpp` reports TrimRectangle 0x0041D880
EXACT, and the sibling recoveries `laser_rectangle_split_0041eb00`
(313/316) and `laser_circle_split_0041efa0` (241/302) still pass their strict
checks, so the shared `laser_cut` cluster context is not disturbed.

## What was ruled out (2026-10-18)

All measured with `variant.py` on the layout (bytes are the differing code
bytes; the pre-change baseline is 274/345 at 865):

* **Test-vs-cmp spelling sweep** (9 forms of the two `while (cursor<count &&
  !cut[cursor])` tests): `==0`, `=='\0'`, `0==`, `(unsigned char)x==0`,
  `unsigned char cut[]`+`==0`, `<=0`, `!(x!=0)` all compile to the model's
  `mov dl,[..]; test dl,dl`; `<1` and `!=1` compile to `cmp [mem],1` (865 →
  644 bytes but 2 fewer identical instructions — alignment noise, and `1` is
  not retail's immediate). None produces retail's `cmp BYTE PTR [mem],0`.
* **Hit-body shapes**: the `create.cpp` store order (render_bucket before
  flags, x,y,z), `CutVector* sample_position=&point` for the spawn, a
  `__forceinline` `CreateOffsetInline` helper in the create.cpp shape, typed
  `AnimationResourceFile*` resource, a named `CutAnimationBank* bank` local —
  all identical bytes to the baseline or worse.
* **Statement orders**: resource-first (879), index-last (946).
* **Register-contest levers**: `int end=count` copies for the tail walks
  (propagated away, no change), `count=count` self-assignment (no change),
  `hit_count` second reference (`!x || x<0` / `x!=0 && x>=0` chains: 919),
  `unsigned count` (868), swap of `cut[count]=1`/`++hit_count` (876),
  `origin` copied through a pointer or a `CopyVector` helper (1128/1130).
* **Counter types**: `short`/`unsigned short`/`char`/`unsigned char count`
  and `short run` all reach 288/345 with 40 hunks (the best identity seen) but
  943 differing bytes and 6 tail bytes: the narrowed counter is widened
  (`movsx edx,di`) at each use, and those widening instructions are not in
  retail. `short hit_count` (285), `short first_run` (273), `short cursor`
  (248) are worse. This variant family is a dead end for exactness but proves
  the mechanism below.

## Mechanism of the remaining 53 hunks (2026-10-18, for the next session)

The residual is one register contest with downstream consequences:

* Retail: `count` lives in **EDX** (spilled at `[esp+0x44]`, reloaded after the
  hit body's calls, `inc edx` at the walk back edge, `cmp ebx,edx` in the tail),
  the bank pointer (`g_laser_manager->line_animation`) lives in **EDI** across
  the Allocate call, `object` in ESI, `this`/`cursor`/`index` in EBX.
  The model: `count` takes EDI, the bank pointer is spilled to `[esp+0x3c]`.
* With count in EDX all four byte registers (AL/BL/CL/DL) are live at the
  `cut[cursor]` tests, so c2's Riscify leaves `cmp BYTE PTR [mem],0` (retail's
  form). With EDX free the test splits to `mov dl,[..]; test dl,dl` (the model,
  and the byte-exact sibling's form for the same source). The two
  `cmp [mem],0` hunks (0x359, 0x400) are therefore downstream of the contest,
  as are the count home-store/reload at the walk back edge (0x22c, 0x28d), the
  4-byte prologue shift, the `jmp`+`lea` alignment filler at 0xef and the
  branch-displacement hunks (0x116, 0x36e, 0x3ae, 0x3b4, 0x442).
* Spillcosts/ChoosePhysReg traces of the model link
  (`/tmp/campaign/laser_trim/trace/spillcosts.txt`, `choose.txt`; TrimCircle is
  the 48-block function whose marker experiment (`if (count==39917)`)
  identified it) give the bank pointer `refs 4 x K 7 x weight 2 = 56` priority
  and `count` 71; count is allocated first and takes the last callee-saved
  (EDI), so the bank pointer fails SpillObvious and is spilled. Retail's bank
  pointer clearly outranks count (it holds EDI as one piece across the
  Allocate call and count falls out of the callee-saved set and is split into
  EDX pieces around the calls). The lever to hunt is therefore +16 priority on
  `resource` or -15 on `count`: e.g. one more def/use pair of `resource`, or
  two more candidate references (a twice-used immediate) in the hit-body block
  (K 7 -> 9 gives 4 x 9 x 2 = 72 > 71). The K/refs spellings tried this session
  (second references, named helper parameters, statement orders) all folded
  away before Spillcosts.
