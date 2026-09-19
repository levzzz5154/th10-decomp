# The four-byte argument-copy residual — **decisive negative**: `0x00401110`, `0x00405620` and `0x0040D530` are toolkit-blocked, not model-blocked

2026-09-19, wave 10, agent `MoveOrder`. Three regions sit four bytes short
because a pair of independent register copies is emitted in the opposite order
to retail at both of its sites. This note settles the question the wave-7 and
wave-9 notes left open: **the order is not reachable from any C++ source shape
with the pinned toolkit**, and the reason is now a measured rule rather than an
impression. All three regions were re-built this wave from their wave-7/wave-9
scratch models and re-measured against the retail image; nothing was landed and
nothing was registered.

| region | declared | emitted | differing bytes | differing offsets (region-relative) |
| --- | ---: | ---: | ---: | --- |
| `0x00401110` loader | 330 | **330** | **4** | `+0x10F +0x111 +0x136 +0x138` |
| `0x00405620` release pair | 137 | **137** | **4** | `+0x2F +0x31 +0x63 +0x65` |
| `0x0040D530` enemy destroy | 300 | **300** | **4** | `+0x2E +0x30 +0x62 +0x64` |

Every other byte of all three bodies, and every other function in each of the
three clusters, is byte-identical to retail (details in §4).

## 1. The rule, both directions (new this wave)

Both compilers emit a register copy for each argument. They differ on exactly
one thing: **the order of two register-to-register argument copies.** Where one
operand is a memory load the toolkit emits the load first (`L1`/`L2` in §3), and
retail's load-source call setups are load-first too (26 `(mem→EDX, reg→ECX)`
setups plus the landed `Scheduler_RemoveLocked` at `0x449F35`), though there the
load-first and second-argument-first orders coincide, so retail's load rule is
not independently pinned. It does not matter here: every site of the three
regions is a register-register pair.

* **retail** emits them in **ascending parameter home** order — the first
  argument's copy first.
* **this toolkit** emits them in **descending home** order — the second (last)
  argument's copy first, i.e. reverse argument order.

Measured on both sides, with two different home pairs:

| site | homes (position order) | retail | toolkit |
| --- | --- | --- | --- |
| `0x40564E`/`0x405682` (`0x449F60`: task→ECX, sched→EDX) | ECX(1), EDX(2) | `8b ce 8b d7` (**ECX first**) | `8b d7 8b ce` (EDX first) |
| `0x40D55D`/`0x40D591` (same callee) | ECX, EDX | `8b ce 8b d3` | `8b d3 8b ce` |
| `0x40121E`/`0x401245` (`0x43E5A0`: object→EAX, resource→ECX, index→EDX) | EAX(0), ECX(1) | `8b c6 8b cf` (**EAX first**) | `8b cf 8b c6` (ECX first) |

The second pair is the mirror image — the toolkit puts ECX(1) before EAX(0)
while retail puts EAX(0) before ECX(1) — which is why the rule is stated as
*ascending home* rather than "ECX before EDX". The index register EDX of the
`0x43E5A0` call is materialised separately (`xor edx,edx` / `mov $0x62,%edx`)
and is byte-identical in both.

### Retail census (whole image, this wave)

Scanning every adjacent `mov r32,%ecx` / `mov r32,%edx` pair in `.text`
(`/tmp/MoveOrder/census.py`): **40** pairs are immediately followed by a direct
call, **all 40 are ECX-first, all 40 call `0x449F60`**, over four different
register pairs — `(ECX←ESI, EDX←EDI)` × 27, `(EDI, EBX)` × 8, `(EDI, EBP)` × 3,
`(ESI, EBX)` × 2. Four EDX-first register pairs exist in the image and **none is
a direct-call setup**: `0x428780` (`mov %ebx,%edx | mov %ebp,%ecx | call *%eax`,
an *indirect* 3-argument call whose pushed argument precedes both), `0x43A5E0`
(followed by `sub %ecx,%edx`), `0x43AB16` (`mov %ah,0xa(%esp)`), `0x4471C9`
(`mov %edx,0x120(%esi)`).

The destination-order invariant also kills every source-order explanation: the
`(EDI,EBX)` group is descending by source register (7 then 3) and the
`(ESI,EDI)` group ascending (6 then 7), so retail is ordering by *home*, not by
source register, not by the value, and not by the callee's identity alone.

## 2. The experiment that settles it: homes do not move the order

`/tmp/MoveOrder/homes.cpp` feeds the same two live values (task in ESI, scheduler
in EDI) to two callees whose parameter homes differ, both `__fastcall` with the
identical two-register ABI:

```text
homesA  call f(task, sched)   ->  8b d7 8b ce   mov %edi,%edx | mov %esi,%ecx   (ECX=task, EDX=sched)
homesB  call f(sched, task)   ->  8b d6 8b cf   mov %esi,%edx | mov %edi,%ecx   (ECX=sched, EDX=task)
```

The toolkit's **first** copy always writes the *second* parameter's home. The
consequence is a proof, not an observation: for the byte sequence retail has
(`8b ce 8b d7` = `mov %ecx,%esi` then `mov %edx,%edi`) the first emitted copy
would have to write **ECX**. No assignment of homes can do that, because the
first copy always targets the *second* home and the second copy targets the
first — swapping the homes only exchanges the two destination registers
(`8b d6 8b cf`), it never produces `8b ce`. Since the homes themselves are
pinned by the exact callee bodies (`0x449F60`: `cmp %edi,%ecx` on the searched
task, `lea 0x14(%edx),%eax` on the scheduler list; `0x43E5A0` cluster anchor),
and since the copy *targets* are therefore not free either, the residual is
unreachable — by any declaration, expression, local, anchor, root, caller or
callee-visibility change.

## 3. Configurations measured (56 toolkit call setups this wave, plus the earlier ~80)

All compiled with the project profile (`/O2 /Gz /MT /Gy /G6 /GF /GS /Zl`) through
`matching2.tools.common.wine.compiler_environment`; each setup below is listed
with the instruction pair the toolkit emitted. **Every register-register pair is
descending** (the later argument's home first); the only ECX-first line in the
whole matrix is `L1`, where the ECX operand is a **memory load** — the load-first
rule both compilers share.

* `/tmp/MoveOrder/m.cpp` (13 setups): value provenance — object field / global /
  caller parameter / `GetTask()` result / both from calls / wrapper struct /
  conversion operator / pointer arithmetic / array / volatile / const / extra
  local copies / two sequential calls / three-argument call / indirect call;
  plus three register-pressure ballast shapes and the two-block retail shape.
* `/tmp/MoveOrder/matrix.cpp` (34 setups, generated by
  `/tmp/MoveOrder/gen.py`; `/tmp/MoveOrder/matrix_main.obj` is an earlier
  32-setup iteration used for the `13.10.3052` cross-check): the above
  plus the second argument as `int`, the first argument as `int`, a dead and a
  live third argument, member `__fastcall`, `#pragma optimize` on/off, an
  8/9/16/32-bit cast pair, a caller-parameter pair (stack sources), loop, tail
  position, `if/else`, volatile pair, and an inlined-helper call.
* `/tmp/MoveOrder/homes.cpp` (3 setups — the fourth function there is a
  `__thiscall` member whose call has no second register argument): the two home
  assignments above and a `__declspec(dllimport)` callee (the IAT call is
  `mov %edi,%edx | mov %esi,%ecx | call *…` — same order, and its `ff 15` call
  could not match retail's `e8` anyway).
* `/tmp/MoveOrder/last.cpp` (2): callee body present in the same translation
  unit (`__declspec(noinline)`, both parameters live), the same reached through
  a variable, and an internal-linkage callee.
* `/tmp/MoveOrder/probe2.cpp` (4): a non-hoistable memory operand for the ECX
  argument (`mov (%eax),%ecx | mov %esi,%edx` — **load first**), the same for the
  EDX argument (`mov (%eax),%edx | mov %esi,%ecx` — **load first**), and
  `#pragma optimize("g"/"t", off)` (the former spills everything to the stack;
  the latter is unchanged). Retail's 28 load-plus-register call setups put the
  load first in every case (`(mem→EDX, reg→ECX)` × 26, `(mem→EDX, mem→ECX)` × 2);
  it has no `(mem→ECX, reg→EDX)` setup to compare, so the toolkit's load-first
  behaviour there cannot make a region differ — the disagreement is confined to
  the register-register pair.

Counting only the setups whose operands are both plain registers: **49 of the
56, all descending**, and the toolkit's first copy targets the later home in
every one of them. The same scan restricted to pairs whose third instruction is a
direct call gives the retail invariant in one line: `(reg,reg)` = **40 ECX-first, 0 EDX-first**;
`(mem,imm)` = 2 ECX-first; `(mem,mem)` = 2 ECX-first + 2 EDX-first;
`(reg,imm)` = 1 ECX-first; `(mem,reg)` = 26 EDX-first (the load);
`(reg,reg)` EDX-first = 1, the indirect 3-argument call above.

Independent of source shape:

* **Two c2 revisions.** `cl.exe 13.10.3052` (the Visual C++ Toolkit 2003 present
  under `~/.wine/drive_c/.../Visual C++ Toolkit 2003`, `c2.dll`
  `52af3d0facd05bc80a21a972b1115dd3`) and the pinned `13.10.6030`
  (`c2.dll 63ccebc6195fe01d86ad953d7db2fd29`) emit the same descending order on
  the whole matrix. The "another MSVC 13.10 build emits param1-first" hope of
  the wave-7 note is therefore falsified for the one other revision on this
  machine.
* **Both codegen paths.** Plain `/O2` objects and the native `/GL` + `/LTCG`
  cluster link (every §4 build) agree.
* **The load-first shapes agree.** The toolkit emits a memory operand's load
  before the remaining register copy (`L1`: `mov (%eax),%ecx | mov %esi,%edx`;
  `L2`: `mov (%eax),%edx | mov %esi,%ecx`), which is what retail's 26
  `(mem→EDX, reg→ECX)` setups and its landed `Scheduler_RemoveLocked`
  (`0x449F35`, load then `mov %esi,%ecx`) show, so the only disagreement the
  image exposes is the register-register pair.

Consistency check: the toolkit's divergence can only show up at a call with two
*register* argument operands, and all 40 such sites in the image (plus the six
`0x401110`/`0x43E5A0` sites) lie in still-`asm` regions — which is exactly why
554 landed regions are unaffected and why no landed region can be used to
cross-check this rule.

## 4. The three residuals, re-measured this wave

**`0x00405620`** — scratch copy `/tmp/ReleasePairRepair/msvc` (wave 7), probe run
this wave into `/tmp/MoveOrder/out_5620`:

```text
python3 matching2/tools/matching/probe.py \
  --source src/game/recovery_release_raw_pair_and_reset_00405620.cpp \
  --project /tmp/ReleasePairRepair/msvc --output /tmp/MoveOrder/out_5620 --show 12
0x00405620     137 bytes  _ReleaseRawPairAndReset_00405620@4  DIFFERENT
  first difference at 0x0040564f
  expected: ce 8b d7 e8 09 49 04 00 ...   0x0040564e: 8b ce  mov ecx,esi
  actual:   d7 8b ce e8 09 49 04 00 ...   0x0040564e: 8b d7  mov edx,edi
```

```text
emitted 0x40564E  8b d7 8b ce e8 09 49 04 00      retail  8b ce 8b d7 e8 09 49 04 00
emitted 0x405682  8b d7 8b ce e8 d5 48 04 00      retail  8b ce 8b d7 e8 d5 48 04 00
```

differing bytes: `0x40564F`, `0x405651`, `0x405683`, `0x405685`. The other 14
registered regions of `bullet_manager_load_scripts_0040ae70.json` are EXACT in
the same link, including the landed `@Scheduler_Remove@8` (114 bytes) and
`_Scheduler_RemoveLocked@8` (52 bytes).

**`0x0040D530`** — `/tmp/EnemyTeardown` (wave 9) copied to
`/tmp/MoveOrder/EnemyTeardown`, rebuilt this wave through its `full.py` lab:

```text
cd /tmp/MoveOrder/EnemyTeardown && python3 full.py variants/idx_nbh_cbar.cpp d530check
0x0040D530 emitted=300 declared=300 diffs=4 first=[46, 48, 98, 100]
0x0040D6B0 emitted=95  declared=95  diffs=0
(the other 24 merged functions: emitted == declared, diffs=0)
```

```text
emitted 0x40D55D  8b d3 8b ce e8 fa c9 03 00 68 74      retail  8b ce 8b d3 e8 fa c9 03 00 68 74
emitted 0x40D591  8b d3 8b ce e8 c6 c9 03 00 68 74      retail  8b ce 8b d3 e8 c6 c9 03 00 68 74
```

differing bytes: `0x40D55E`, `0x40D560`, `0x40D592`, `0x40D594`.

**`0x00401110`** — `/tmp/ThreadChain` (wave 9) copied to
`/tmp/MoveOrder/ThreadChain`, rebuilt this wave (`press10.py aliasonly`, the
shaped model of wave 9 §1 with the six ABI anchors):

```text
RESULT aliasonly   loader 330 diffs 4 [271, 273, 310, 312]   anim 356/6 (anchor, not exported)
```

```text
emitted 0x40121E  8b cf 8b c6 89 be 08 03 00 00      retail  8b c6 8b cf 89 be 08 03 00 00
emitted 0x401245  8b cb 8b c6 89 9e 08 03 00 00      retail  8b c6 8b cb 89 9e 08 03 00 00
```

differing bytes: `0x40121F`, `0x401221`, `0x401246`, `0x401248`. The paired
factory `0x00401440` (69 bytes) is EXACT in this same link — as it was in wave 9
— and stays `asm` only because its cluster cannot be registered while the loader
is four bytes off.

Instruction-level delta, all three regions: **two 2-byte register moves
transposed, twice per region**, `mov %ecx,%esi`/`mov %edx,%edi` against
`mov %edx,%edi`/`mov %ecx,%esi` (and its `EAX`/`ECX` counterpart at
`0x00401110`). No byte count, branch displacement, call displacement, lock
pair, store or `ret` differs.

## 5. Disposition

`0x00401110`, `0x00405620` and `0x0040D530` should be recorded as
**toolkit-blocked** and not re-attempted as source-shape work: each has a model
that reproduces retail's extent, its prologue, its register ownership, its
locks, its stores and all of its callees exactly, and the only residual is a
scheduling tie-break this c2 resolves the other way. The same ruling covers the
20 other regions in the wave-7 list — `0x00405F70`, `0x00408AF0`, `0x0040A1A0`,
`0x0040AF00`, `0x0040B7B0`, `0x00413300`, `0x004133F0`, `0x00413450`,
`0x004145F0`, `0x00417C80`, `0x00418EE0`, `0x0041ADF0`, `0x0041C1C0`,
`0x0041FB50`, `0x00422220`, `0x00424ED0`, `0x0042B570`, `0x0042BC30`,
`0x0042CB60`, `0x0043CB00` — plus `0x0043CD30`, which holds the same tie-break
in its `(reg→ECX, imm→EDX)` form (`mov %esi,%ecx ; mov $0x492590,%edx ;
call 0x43D390`, measured in §3 as `t_second_int`).

**22 regions hold all 40 of the image's ECX-before-EDX `Scheduler_Remove`
setups** — the wave-7 list's 21, which already includes `0x0040D530`, plus
`0x00405620` (measured by mapping every site to its region) — so the residue is
bounded: closing the tie-break wholesale — a toolkit change — would unblock 22
regions plus the factories that ride with them, and no other modelling work can
move any of them. `0x00401110` is the same tie-break at a second callee
(`0x43E5A0`, homes `EAX`/`ECX`); its six sites lie in that one region.

Two regions are *one blocker away* and should be landed in the same change as
their cluster if the pair ever becomes reachable, because their models are
already exact but not separately registrable: `0x00401440` (69 bytes, exact in
the loader link) and `0x0040D6B0` (95 bytes, exact in the enemy-destroy link).

A future change of toolkit is the only lever left, and it is a project-wide
decision: both c2 revisions available here are wrong in the same direction, and
the rule is measured well enough to test a candidate compiler in one minute —
compile `/tmp/MoveOrder/homes.cpp` and look at `homesA`: any build whose first
copy for `f(task, sched)` is `mov %ecx,%esi` is retail's, and would close this
residual and the sibling set of §5 wholesale.

## 6. Integration statement

Nothing was landed or registered: no manifest record, no layout, no source, no
section, no header was changed in the maintained tree, no compiled object is
exported, and no symbol of another agent's region is bound. The maintained tree
changed only by this note. Scratch state: `/tmp/MoveOrder/{msvc,ThreadChain,
EnemyTeardown}`, the probe output `/tmp/MoveOrder/out_5620`, the loader lab
`/tmp/MoveOrder/ThreadChain/ltcg/p10-aliasonly`, and the enemy lab
`/tmp/MoveOrder/EnemyTeardown/ws/d530check` (the last two are the exact builds
whose report JSONs hold the emitted bytes quoted above). `/tmp/ReleasePairRepair`
and the original `/tmp/ThreadChain`, `/tmp/EnemyTeardown` were read only.
