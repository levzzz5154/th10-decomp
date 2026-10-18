# 0x004465B0 AnmTexture::FillTransparentPixels: equivalent recovery, 2026-10-13

`void AnmTexture::FillTransparentPixels()`, texture holder received in EAX,
called from the upload at 0x00446C70 (`mov eax,edi; call 0x004465B0`) and from
LoadFile/UploadAt/CreateFromMemory/CreateAndUpload. Takes level 0 of the D3D
texture, `GetDesc`, `LockRect(&locked, 0, 0)`, switches on the format (0 and
21: A8R8G8B8, 25: A1R5G5B5, 26: A4R4G4B4; everything else leaves), fills every
transparent pixel with the plain average of its opaque left/right/above/below
neighbours (no halving, unlike the font atlas pass at 0x00436DA0), then
`UnlockRect` and `Release`. The 1,463-byte region is 1,417 bytes of code, three
padding bytes (`lea ecx,[ecx+0x0]`), a four-entry jump table at 0x00446B3C and
the 27-byte index table at 0x00446B4C.

## Why equivalent, not exact

The receiver register (EAX) is a private LTCG convention, and the retail body
keeps its canonical zero in ESI from the prologue on (the `level` argument, the
`surface = 0` store, both null `LockRect` arguments and every `jbe`-guard
compare read that one `xor esi,esi`). Every source shape this attempt tried —
all 720 declaration orders of the seven locals, all 24 zero-initialisation
orders per kernel, mid-block declarations, for-init scoping, a `level` local —
produced the same compiled head with the zero in EBX (or, with `n = 0` first,
no zero register at all and immediate pushes). The prologue save follows the
zero: retail `push esi` / model `push ebx`. That single allocator decision
reschedules the whole function, so an exact probe was not reached; the
equivalence gate is.

## Model

`equivalent/render/anm_texture_fill_transparent_pixels_004465b0.cpp`, compiled
against a stand-in-free copy of the `anm_texture_upload_00446c70` cluster
context (the layout's `context_cluster` points at
`layout/ltcg/anm_texture_fill_transparent_004465b0.json`, a copy of that
manifest whose driver drops the 13-byte `FillTransparentPixels` stand-in so the
model's own definition is the only one). The co-compiled retail-exact callers
give the pass the EAX receiver, the vtable slots and the whole call graph.

Verdict (`verify_recovery` non-record, i.e. what `make` enforces):
1,451 of 1,463 bytes used, 365 of 499 instructions identical, 0 base/index
swaps, 10 frame-offset instructions, 124 instructions in 80 recorded
differences (total 149 of 499, budget 166; structural 52, budget 62).

Load-bearing source shapes (any deviation loses the match):

- The interleaved declaration order `i, surface, j, locked, sum, n, desc` puts
  each local in retail's frame slot (surface +0, i +4, j +8, locked +0xC,
  sum +0x14, desc +0x20). The loop counters are additionally declared in each
  `for` statement; the shadowed outer declarations exist to hold the slots.
- The zero-initialisation order inside each pixel branch (`n` first, then the
  sums, `sum[1]` last) is what the scheduler reproduces.
- The `tex` local and `default: break;` both change the allocation and are
  kept.

## Recorded differences, by class

- `register-choice`: the zero register story (retail materialises `xor
  esi,esi` in the prologue and compares against it; the model pushes immediates
  and uses `test`), the pointer register of the 16-bit kernels (retail EBP,
  model EDI), the neighbour count (retail EDI, model EBP) and the sums that
  travel in other registers.
- `evaluation-order`: pure reorderings — the `b`/`g` zero stores, `add
  ecx,0x4` at the 8888 latch, the reloaded `j` around the 16-bit stores.
- `code-shape`: the loop-alignment filler of another shape (`mov edi,edi`
  against `jmp L+X / lea ecx,[ecx+0x0]`, retail's single `nop` before the 4444
  inner head) and the latch blocks the model merges differently.
- `frame_shift: {deltas: [4], count: 10}`: the model has no prologue register
  save (the zero is not a register), so every head/exit `[esp+X]` sits one slot
  lower; the ten affected instructions are counted as frame-offset.

`code_bytes` is 1420, not 1417: the three padding bytes before the jump table
count as code so the model's shorter tail compares table-to-table (the padding
decodes as one `lea ecx,[ecx+0x0]` and is recorded as an alignment-padding
difference). `compare_tail` then checks both pointer tables through the
instruction mapping and the 27 index bytes byte-for-byte; they are identical
because the case structure is.

## What is identical

Head through the dispatch (`sub esp,0x40` … the indexed jump), all three
kernels' neighbour tests, extraction shifts/masks, division chains and pixel
stores, the `UnlockRect`/`Release` exit and both tables. The differences are
register homes, operand scheduling, alignment filler and the merged latch
tails listed in the layout.

Scratch tools: the cluster probe (`probe.py --project scratch/4465b0/msvc`)
for per-variant byte diffs and an instruction-stream differ over
`find_differences` for classification. See also
`anm_texture_fill_transparent_004465b0_2026_10_10.md` (the earlier LTCG rig
state) and `font_atlas_convert_00436da0_regalloc_2026_10_10.md`.

## 2026-10-17: register-contest route named; parked

The 68 register-choice hunks are the shared-zero candidate contest the
`msvc-c2-immediate-register-candidates` memory describes: retail keeps the
zero in ESI (`xor esi,esi; push esi` / `cmp eax,esi`) where the model emits
the immediate (`push 0x0` / `test eax,eax`). The memory's rule applies from
the other side — adding zero stores does not fix it (the EBP cost/benefit
step turns them back into immediates); the route is to find why the other
candidates cannot take ESI. The documented 0x405750 lever (callee parameter
order) does not transfer directly here: the callees are COM methods with
ABI-fixed parameters.

Region stays equivalent (1245 differing bytes).

## 2026-10-17: zero-materialisation forms probed; all negative

Six spellings aimed at making zero a value c2 cannot fold to an immediate,
measured with the byte script against the baseline 365/499, 80 hunks, 1,233
differing bytes:

| variant | identical | hunks | differing bytes |
| --- | --- | ---: | ---: |
| baseline | 365/499 | 80 | 1,233 |
| `named-zero` (`unsigned int zero = 0;` through the stores and tests) | 365/499 | 80 | 1,233 |
| `address-taken-zero` (`unsigned int* zero_ref = &zero`) | 365/499 | 80 | 1,233 |
| `zero-struct` (`struct Zero { unsigned int v; }`) | 365/499 | 80 | 1,233 |
| `derived-zero` (`zero = (desc.width == 0xffffffffu)`) | 274/499 | 156 | 1,409 |
| `push-zero`, `named-zero-wide` | — | — | compile error (`LockRect` takes `const void*`) |

The three plain forms fold straight back to the immediates — byte-identical to
baseline — which is exactly the EBP cost/benefit behaviour the memory records.
Deriving the zero from a comparison breaks the match outright. So nothing in
this function can force a zero into ESI; the contest is decided before the
source is consulted. Region stays equivalent.

## 2026-10-18: zero-init order lever; 1233 -> 954 differing bytes

The lever that moved this region: the per-pixel zero-initialisation order is
`sum[0] = 0; sum[2] = 0; sum[1] = 0; n = 0;` (the sums in the old order, `n`
LAST), in all three kernels. Measured with `variant.py`: 365/499 identical,
77 hunks, **954 differing code bytes** (was 1,233), tail 12. The 24-order
sweep shows a 954-byte plateau for every order with `sum[2]` before `sum[1]`
and `n` not first (`021n`, `02n1`, `0n21`, `201n`, `20n1`); `210n`/`21n0`
(1283-1289) and `n`-first orders (1233-1240) are worse. The 16-bit kernels'
order is irrelevant to the byte count; the 8888 kernel's order carries the
whole effect (`nlast-8888-only` = 956).

What it fixed: the A8R8G8B8 kernel's zero stores now come from a zero
register (`mov [esp+0x2c],esi` / `mov [esp+0x28],esi`) and the neighbour
alpha tests keep the immediate byte form (`cmp BYTE PTR [ecx+0x1],0x0`),
exactly as retail; `mov esi,0x1` / `inc esi` give n=ESI as retail. The
remaining 8888 differences are the xor/store schedule (`xor esi,esi;
xor ebx,ebx; test eax,eax` against retail's `xor ebx,ebx; xor esi,esi;
test eax,eax` with the stores first), the `lea ecx,[edi-0x2]` placement
around `cmp ebp,esi`/`test ebp,ebp`, and the alignment filler.

### Ruled out (all measured against the 954 baseline unless noted)

- All 24 zero-init orders per kernel and 12 per-kernel mixes: plateau at 954
  for the orders above; nothing below 954.
- Dropping the `(unsigned char)` casts on the sum stores (the
  `font_atlas` 0x436DA0 lever): 1266 - the casts ARE the source form here,
  matching the note's earlier claim (retail masks the sums in place with
  `and cl,0x1f; movzx cx,cl`).
- `!= '\0'`, truth tests (`if (c[1])`), named `const unsigned int zero`,
  `0u`-typed zeros, `j != 0`: byte-identical to their baselines.
- Named `width`/`height` locals (per-kernel or hoisted): 1341/1351 - worse.
- All 7 declaration orders (adjacent swaps, reversed, rotations), `tex`
  removed, `level` local, `surface` initialised late, the LockRect NULLs via
  named locals: inert (954). `j > 1` diagnostic (semantics changed): 404/499
  identical but 1257 bytes - the zero compares matter for the register
  cascade but the compare immediates themselves cost the bytes.

### The remaining 954 bytes and the c2 mechanism

Residual classes: the head zero piece (retail `xor esi,esi; push esi` /
`mov [esp+0xc],esi` and `cmp eax,esi` guard tests, model `push 0x0` /
`mov [esp+0x8],0x0` / `test`), the 16-bit kernels' register permutation
(retail temp=ESI, n=EDI, p=EBP, j=EAX against model temp=EAX, n=EBP,
p=EDI, j=ESI), the merged latch tails, and 12 tail bytes (one jump-table
entry). The permutation cascades from ESI being free for j: retail's zero
candidate holds ESI from the prologue (hence the prologue `push esi` and
the frame_shift), which forces j to EAX.

c2 decision logic recovered from the loaded c2.dll 13.10.6030 (Ghidra
`/compiler_reference/c2.dll`), matching the traces:

- `CmdIdentifyImmedCandidates` (0x107a5bcf) rewrites eligible immediate
  operands into one register candidate per (operand kind, value) per
  function via `CmdCanEnregImmed` (0x107a5a80) + `GrgRewriteImmedAsReg`
  (0x107a6065). `cmp reg, 0` on a temporary stays out of the candidate; the
  compare of a register variable against 0 is rewritten when a zero piece is
  live (the ecl_start_child rule).
- The re-queue verdict is `FUN_10741d94` (0x10741d94) -> `FUN_10741992`
  (0x10741992): keep iff `sum(src-occurrence costs) <= k * dst-occurrences +
  threshold`, where `k` is 2/3/6 by the operand's addressing shape and the
  threshold is `FUN_107a99bf(symbol) + 6`: for an immediate symbol with
  value 0 it is 2+6=8 (value -1 gives 3, other values 3 or 5). Hard vetoes:
  a first tuple naming an unallocated byte-flagged (0x80 at +5) operand, or
  more than one unallocated operand; and `FUN_10741c25` rejects a 2nd
  occurrence whose opcode is a PUSH (0x254) under some conditions.
  `CmdSpillImmedBytes` (0x1076a4b0) then restores immediate bytes.
- Hypothesis for the head piece failing while the 8888 behaviour survives:
  the zero family's piece spanning head -> 8888 body includes the 8888 byte
  compares (`cmp byte [ecx+1],0`), which byte-flag the piece (the flag is
  visible on all three SPILLIMM'd pieces: `flags=00028c02`); retail splits
  the family at the `n = 0` def (`xor esi,esi`, which redefines ESI)
  *before* the byte compares, so its head piece is unflagged and keeps
  `push esi` while the flagged tail piece reverts to `cmp byte,0`. In our
  schedule `n = 0` is emitted before the stores so no such split occurs.
  Diagnostics support this: deleting the byte compares entirely does not
  rescue the head (the height/width zero-trip compares remain in the range).

Traces for this build: `scratch/anm_tex/trace/{spill,choose,choose2}.txt`
(sandbox `/tmp/campaign/anm_tex/trace/`). Region remains an equivalent
recovery (365/499 identical, 77 recorded differences, gate passes:
structural 51 of 499, total 149).

## 2026-10-18 (later): piece-boundary pass negative; parked at 954 bytes

The piece-boundary hypothesis from the earlier section (zero family split at
the `n = 0` def; unflagged head piece in ESI) was tested directly and is NOT
supported. Bounded sweep of 24 shapes this session (plus 27 K/edge shapes
earlier the same day):

- Forcing the `n = 0` def after the zero stores via memory edges (volatile
  reloads of `sum[k]` for n, volatile stores, a named volatile array pointer,
  byte reload): 8 shapes, 1159-1349 bytes - the reload costs land and no head
  piece appears (`push esi` / `xor esi,esi` never materialise in the head in
  ANY shape).
- `n = sum[k]` copies (the post-store-value edge): folded back to `n = 0`,
  byte-identical to baseline (954).
- Byte compares rewritten to compare against constant 1 (`c[1] >= 1` etc.,
  exact unsigned equivalence): 1201-1324.
- Same-size constant swaps moving a reference between immediate families
  (`if (n > 1)` -> `if (n >= 2)`, identical encoding): inert (954-956).
- Named pointer to the sum array (the font_atlas note's shape: elements become
  ordinary candidates): 381/499 identical (the cascade moves again) but 1256.

Trace evidence (sandbox `/tmp/campaign/anm_tex/trace/choose2.txt`, 954 build):
the zero family's pieces are ALL reverted - three `CmdSpillImmedBytes` events
(`SPILLIMM num=1 prio=-787`, `num=12/num=7 prio=-178`) with the byte flag set
in every piece (`flags=00028c02`, 0x80 at byte +5). The 8888 zero stores'
ESI is the `n = 0` def's register (the n candidate is `CHOOSE reg=7 num=68/64
prio=336`), not a kept family piece. This is consistent with the
`FUN_10741d94` first-tuple hard-reject (`if (src-operand candidate has no
register and flags & 0x80: return false`): the family is rejected BY FLAG,
independent of its occurrence counts - which is why every count/edge shape
fails identically. The flag comes from the byte-sized zero uses (the 8888
`cmp byte [ecx+1], 0` family); retail's split story (byte uses reverting to
`cmp byte,0` while the unflagged dword family keeps ESI) requires the two
immediate kinds to stay separate candidates in c2's hash, which the model's
IR does not currently produce.

### Productive lead left open (do not lose this)

A repeated-immediate lever flips the whole register cascade toward retail
WITHOUT touching the zero family: spelling the left-neighbour guard as
`if (j >= 1 && ...)` (exact unsigned equivalence with `j > 0`) adds a second
immediate family (constant 1) to the guard blocks and moves K/priorities:

| variant | identical | hunks | bytes |
| --- | ---: | ---: | ---: |
| baseline | 365/499 | 77 | 954 |
| `j >= 1` all kernels | 402/499 | 52 | 1314 |
| `j >= 1` 1555 only | 384/499 | 64 | 995 |
| `j >= 1` 4444 only | 384/499 | 65 | 998 |
| `j >= 1` both 16-bit | 403/499 | 52 | 1039 |

With `j >= 1` the 16-bit kernels take retail's pointer register (EBP, see the
0x1fe/0x20b hunks: `mov ebp,eax`/`add ebp,esi`) - the cascade direction is
right - but the `cmp reg,0x1` encodings and the partly-reordered heads cost
more than the flip saves. The next move is a K/refs change with ZERO byte
delta (the `n > 1` -> `n >= 2` swap proves same-size family moves are inert,
so it must be an ADDITIONAL reference or a moved reference per
`msvc-c2-what-adds-a-register-candidate`), or a `trace_scheduler.py`-guided
reference move across a branch in the guard blocks. Truth tests (`if (j)`),
signed forms, wrap tricks (`j-1 < j`) do not flip it (954-1386).

Region remains an equivalent recovery at 954 differing bytes (365/499
identical, 77 recorded differences, gate: structural 51/62, total 149/166).

## 2026-10-18 (evening): `n = 1`-init restructure; 954 -> 879 differing bytes

New lever (from the K/refs lead: the constant-1 family must be EMITTED in the
guard block to move the cascade, and phantom references fold away): in the
A1R5G5B5 and A4R4G4B4 kernels only, initialise `n` to 1 in the zero-init
block and put `n = 0` on the no-left-neighbour path:

```cpp
sum[0] = 0; sum[2] = 0; sum[1] = 0; n = 1;
if (j > 0 && p[-1].a != 0) { sum[0] = p[-1].r; sum[1] = p[-1].g; sum[2] = p[-1].b; }
else { n = 0; }
```

Exact same semantics (n counts the left neighbour as 1), same instruction and
byte count in isolation (the `mov reg,0x1` moves from the left body to the
init block and the `xor reg,reg` moves to the else, 5+2 = 2+5), and the
`mov reg,0x1` immediate now sits in the same block as the `j > 0` guard -
the reference move `msvc-c2-what-adds-a-register-candidate` predicts. The
scheduler/K effect saves ~27 bytes per kernel beyond the encoding: 369/499
identical, 73 hunks, **879 differing code bytes** (was 954), tail 12.

The 8888 kernel must keep the old shape (`n = 0` init, `n = 1` in the left
body): applying the restructure there regresses to 1371.

### Ruled out on this pass (all against the 879/954 baselines)

- Phantom-fold spellings (`sum[k] = 1 - 1`, `j > 1 - 1`, `2 - 2`, `!(j < 1)`
  as `j >= 1`): the constants fold before immediate identification - every
  fold-preserving spelling is byte-identical to its baseline (954); every
  spelling that keeps the emitted `cmp reg,0x1` (`j >= 1`, `1 <= j`,
  `!(j < 1)`, `j >= 1u` - all 402/52/1314) pays the compare bytes.
- `if (j > n)` (n is 0 there; register compare, same size as `test`): inert.
- `n > 1` -> `n >= 2` (same-size immediate-family swap): inert (881 with the
  restructure).
- `n -= 1` else form, `n = 1` first in the init, inverted else, `1u` suffix,
  reversed left-body reads, named array pointer in the 16-bit inits: 879-1205.
- `j >= 1` on top of the restructure (any kernel mix): 883-1158 - the two
  levers do not superpose; the restructure subsumes the flip's benefit.

State: 369/499 identical, 73 recorded differences (57 register-choice,
14 code-shape, 2 evaluation-order; structural 62 of 62 budget, total 144 of
166), 10 frame-offset, base_index_order 0. The head zero piece (`push esi`)
still does not materialise and the 16-bit register permutation persists.
