# 0x00436DA0 transparent pixel fill: register-allocation state, 2026-10-10

`FontAtlas_Convert_00436da0(atlas, rows)` gives every fully transparent pixel
of the font atlas the (halved, for 4-bit) average colour of its opaque
left/right/up/down neighbours. 946 bytes, still assembly
(`src/render/transparent_pixel_fill.cpp`). Plain `cl /O2` model below: 934
bytes, 213 of 316 instructions (4-bit path 105 of 176, 32-bit path 108 of 140).

## The finding: the colour sums are one aggregate

Retail's frame has five slots: row `[esp+0x10]`, column `[esp+0x14]`, an
unused slot `[esp+0x18]`, green `[esp+0x1c]`, blue `[esp+0x20]`. The unused
slot is red's home: the three sums are `unsigned int sum[3]` (a struct of three
compiles the same). Elements of a local aggregate are register candidates
limited to ECX and EBX (`ChoosePhysReg` shows `avail=[2, 4]`), so red and
green take those two and blue always stays in memory, with its
load/operate/store code. Three scalars instead all get registers (127 of 316).

The same explains the 32-bit path, where only red is in a register (ECX is the
second pixel pointer there) and green and blue are in memory.

## Model

```cpp
struct Pixel8888 {
    unsigned char b;
    unsigned char g;
    unsigned char r;
    unsigned char a;
};

struct Pixel4444 {
    unsigned short b : 4;
    unsigned short g : 4;
    unsigned short r : 4;
    unsigned short a : 4;
};

extern "C" char __stdcall TransparentPixelFill_00436da0(TextSurface* surface, unsigned int rows) {
    unsigned int i;
    unsigned int j;
    unsigned int sum[3];
    unsigned int n;
    unsigned short v;

    switch (surface->format) {
    case 26: {
        Pixel4444* p = (Pixel4444*)surface->bits;
        for (i = 0; i < rows; i++) {
            for (j = 0; j < (unsigned int)surface->width; j++) {
                if (p->a == 0) {
                    sum[0] = 0;
                    sum[1] = 0;
                    sum[2] = 0;
                    n = 0;
                    if (j > 0 && p[-1].a != 0) {
                        sum[0] = p[-1].r;
                        sum[1] = p[-1].g;
                        sum[2] = p[-1].b;
                        n = 1;
                    }
                    if (j < (unsigned int)surface->width - 1 && p[1].a != 0) {
                        sum[0] += p[1].r;
                        sum[1] += p[1].g;
                        sum[2] += p[1].b;
                        n++;
                    }
                    if (i > 0) {
                        Pixel4444* above = p - surface->pitch / 2;
                        if (above->a != 0) {
                            sum[0] += above->r;
                            sum[1] += above->g;
                            sum[2] += above->b;
                            n++;
                        }
                    }
                    if (i < (unsigned int)surface->height - 1) {
                        Pixel4444* below = p + surface->pitch / 2;
                        if (below->a != 0) {
                            sum[0] += below->r;
                            sum[1] += below->g;
                            sum[2] += below->b;
                            n++;
                        }
                    }
                    if (n > 1) {
                        sum[0] /= n;
                        sum[1] /= n;
                        sum[2] /= n;
                    }
                    sum[0] >>= 1;
                    sum[1] >>= 1;
                    sum[2] >>= 1;
                    p->r = (unsigned char)sum[0];
                    p->g = (unsigned char)sum[1];
                    p->b = (unsigned char)sum[2];
                }
                p++;
            }
        }
        break;
    }
    case 21: {
        unsigned char* q = surface->bits;
        unsigned char* c = q - 2;
        for (i = 0; i < rows; i++) {
            for (j = 0; j < (unsigned int)surface->width; j++) {
                if (c[5] == 0) {
                    sum[0] = 0;
                    sum[1] = 0;
                    sum[2] = 0;
                    n = 0;
                    if (j > 0 && c[1] != 0) {
                        sum[0] = c[0];
                        sum[1] = c[-1];
                        sum[2] = c[-2];
                        n = 1;
                    }
                    if (j < (unsigned int)surface->width - 1 && c[9] != 0) {
                        sum[0] += c[8];
                        sum[1] += c[7];
                        sum[2] += c[6];
                        n++;
                    }
                    if (i > 0) {
                        unsigned char* above = q - surface->pitch / 4 * 4;
                        if (above[3] != 0) {
                            sum[0] += above[2];
                            sum[1] += above[1];
                            sum[2] += above[0];
                            n++;
                        }
                    }
                    if (i < (unsigned int)surface->height - 1) {
                        unsigned char* below = q + surface->pitch / 4 * 4;
                        if (below[3] != 0) {
                            sum[0] += below[2];
                            sum[1] += below[1];
                            sum[2] += below[0];
                            n++;
                        }
                    }
                    if (n > 1) {
                        sum[0] /= n;
                        sum[1] /= n;
                        sum[2] /= n;
                    }
                    c[4] = (unsigned char)sum[0];
                    c[3] = (unsigned char)sum[1];
                    q[0] = (unsigned char)sum[2];
                }
                c += 4;
                q += 4;
            }
        }
        break;
    }
    }
    return 1;
}
```

## Still different

4-bit path (retail / model): neighbour count ESI / EDI, pixel pointer EDI /
EBP, column EBP / EDX, width EDX / ESI, atlas ESI / EBX. `ChoosePhysReg`
gives ESI to the right neighbour's zero-extended pixel temporary (its
`avail` is `[6, 7, 8]`, EAX and EDX excluded) before the count is chosen; in
retail all four neighbour temporaries are in EAX. Everything else follows:
count -> EDI, pointer -> EBP, the atlas only finds EBX. Equal costs are taken
in the order ESI, EDI, EBX, EBP, so with that temporary in EAX the count,
pointer and column would land where retail has them.

32-bit path: retail shares the zero register with red (EBX is zero before the
loops, is used for `rows > 0`, `width > 0` and the green/blue resets, and is
cleared again after the stores); the model shares it with the count in ESI
because the atlas holds EBX. Retail also computes the second pointer
(`lea ecx,[ebp-2]`) at the start of every row, so it is an inner-loop
induction pointer the compiler made from indexed accesses, not a source
variable; the model's explicit `c = q - 2` is computed once.

### What pushes that temporary out of EAX

Deleting `sum[2] += p[1].b` from the right-neighbour block (a diagnostic, not a
candidate) puts the temporary back in EAX and also fixes most of the 32-bit
path (114 of 140), because the atlas then gets ESI. So the blue element's
live piece running from the left block's store to the right block's update is
what excludes EAX and EDX. The above/below blocks are immune because their
pixel word is loaded through a pointer that is already in EAX. With three
scalar sums the right block is allocated like the others.

No change from: the right block written with a named pointer, nested `if`s,
blue first, `n++` first, the left block as `+=`, moving the right block after
the other neighbours (it is still the one that differs), or one shared
`Pixel4444` copy for the four neighbours (worse, 147).

Zero order matters: `n = 0; sum[2] = 0; sum[1] = 0; sum[0] = 0;` in the 4-bit
path (or `memset(sum, 0, sizeof(sum))`) gives exactly 946 bytes and 316
instructions, moves the width into EDX as in retail and the 32-bit path to 114
of 140, but the column then takes ESI (4-bit path 89 of 176; count EDI, pointer
EBP, atlas EBX). Reversing the left neighbour's three assignments is worse.

## Tried on the scalar model, no change

Declaration order; initialisers at function scope with a reset after the
stores; the accumulation as a `__forceinline` helper with reference or pointer
parameters; `p->r = (unsigned char)(r >>= 1)` and similar; order and spelling
of the neighbour blocks. The regalloc tracers work on a plain compile: put the
`cl.exe` command line in a one-entry `cmds.json`.

## Later the same day: why the right-neighbour temporary left EAX, and the equivalent recovery

Traced with `compiler_traces/regalloc/trace_byte_register_pressure.py`.

Before a candidate gets its register, c2 walks the tuples of its lifetime. At
a tuple that names another candidate which has no register yet and carries the
byte-register flag, it compares `need` (byte-flagged candidates already in a
register at that point, plus that operand) with the four byte registers. When
`need == 4 - 1` the candidate being placed is restricted to ESI/EDI/EBP.

In the model with `(unsigned char)` casts on the 4-bit stores:

- red and green hold ECX and EBX (flagged, in a register: 2);
- blue lost ECX/EBX and was re-queued over the whole pixel body with EAX/EDX
  as its registers, still flagged because the casts read it as a byte;
- the right-neighbour block contains `blue += temporary`, so `need` is 3 and
  the temporary is pushed to ESI. The left block only *assigns* blue (a move,
  which the check skips) and the above/below blocks follow a `cdq`, where the
  re-queued blue has a hole and a local unflagged piece. That is why only the
  right neighbour was affected.

Without the casts (`p->r = sum[0];`) the re-queued blue is not flagged, the
temporary takes EAX, and the count, pointer, column, atlas and width all land
in retail's registers: the 4-bit loop body is identical to retail. The zero
order is then `sum[0] = sum[1] = sum[2] = 0; n = 0;`.

What is left in the 4-bit path is the nibble packing at the end. Retail masks
the halved sums as bytes (`and cl,0Fh; movzx ax,cl`) and reads blue back from
its slot as a byte after storing the shifted value (`shr edx,1; mov
[esp+20h],edx; ... mov cl,[esp+20h]`). Every spelling that reads a sum as a
byte (`(unsigned char)sum[k]`, `*(unsigned char*)&sum[k]`, a byte local, `&
0x0F` on the cast) flags blue again and brings the ESI temporary back. Reading
blue through a *named* pointer (`unsigned char* bytes = (unsigned char*)sum;
... bytes[8]`, or `unsigned int* s = sum; (unsigned char)s[2]`) does give
retail's store-then-byte-load tail, but blue then becomes an ordinary
candidate, wins ESI and the frame grows to 0x18. `(unsigned char)(sum[k] >>
1)` without the separate shift also removes the ECX/EBX restriction.

32-bit path, still open: retail keeps zero in EBX (it doubles as red's reset)
and computes the trailing pointer `pixel - 2` at the top of every row.
Declaring the second pointer inside the row loop gives the per-row `lea` but
costs 20 instructions in the 4-bit path. The single-pointer struct form
(`p[-1].r`) shares the zero in EBX like retail but has no second pointer.

Registered as an equivalent recovery
(`equivalent/platform/font_atlas_fill_transparent_00436da0.cpp`): 284 of 316
instructions identical, 16 recorded differences (the 4-bit nibble packing and
the 32-bit zero register and row pointer).

0x004465B0 (`src/render/transparent_pixel_fill_locked.cpp`) looks like the
same fill on a locked texture; start it from this source.

### Evidence from the sibling 0x004465B0

Its A4R4G4B4 and A1R5G5B5 kernels do not halve. They mask the sums in place
(`and cl,0Fh; movzx cx,cl`), read blue with `mov al,[esp+2Ch]`, and their
right-neighbour temporary *is* in ESI with the count in EDI and the pointer in
EBP: exactly what the `(unsigned char)sum[k]` model gives. So the casts are
the source form, and in 0x00436DA0 it is the halving that keeps blue from
being a byte-flagged candidate over the loop body.

`p->r = (unsigned char)(sum[0] >>= 1);` (same for g, b) gives retail's packing
sequence instruction for instruction (`shr ecx,1; and cl,0Fh; movzx ax,cl`,
result in EAX), but blue is then an ordinary candidate of the count's
priority, takes ESI and is never stored. Retail has that form with blue in
memory (`shr edx,1; mov [esp+20h],edx; mov cl,[esp+20h]`). Mixing the forms per
channel, `/= 2`, and `>> 1` inside the cast do not get there.

## 2026-10-17: state reviewed; parked

The16 hunks are the packing-sequence scheduling the note's channel sweep
already characterised (`shr`/`and`/`movzx` per-channel forms with the blue
candidate question) plus the zero-compare family (retail `xor ebx,ebx`/`cmp
eax,ebx` where the model has `test eax,eax` — the reverse of
`ecl_start_child`'s residual, so the same c2 rule applies from the other
side: the compared value must be a register variable for the zero register
to appear). The note's conclusion that the halving keeps blue from being a
byte-flagged candidate stands.

Region stays equivalent (550 differing bytes).

## 2026-10-17: the register contest traced; it is cost-driven

`compiler_traces/regalloc/trace_choose_physreg.py` on the link command
`prepare.py` regenerates
(`build/experiments/allocator_oracle_2026_10_17/font_atlas_fill_transparent_00436da0/`,
1,513 lines: 33 CHOOSE, 30 SPILL). Chosen-register histogram: EAX 17,
ESI 4, ECX 3, EBP 3, EBX 2, EDI 2, EDX 2.

The residual's `mov edx,[esp+0x20]` against `mov eax,[esp+0x20]` is a
cost/benefit decision, not a tie:

```
CHOOSE reg=1 num=40 prio=136 avail=[1,3,6,8] costs=1:-1 3:0 6:0 8:0
CHOOSE reg=2 num=62 prio=24  avail=[2]        costs=2:-1
CHOOSE reg=4 num=18 prio=632 avail=[4]        costs=4:8800
CHOOSE reg=6 num=26 prio=-3  avail=[6]        costs=6:14200
```

Two shapes appear. Where several registers are free the compiler takes a
`-1` preference (EAX and ECX each carry one). Where only one is free it takes
a cost of 400 to 14,200 without complaint. So the model's EAX is what the
cost function wants; retail's EDX implies its candidate set or benefit counts
differed, exactly the `msvc-c2-immediate-register-candidates` family the
note names. Nothing in this function's spelling changes a cost.

Same picture as `front_script_tick`'s trace: the choices are decided before
the source is consulted. Region stays equivalent.

## 2026-10-17: the register-variable lever probed; no movement

The note's own rule — "the compared value must be a register variable for the
zero register to appear" — was tested directly, by reading each tested alpha
into a value before the compare. Five spellings, measured with the byte script
against the baseline 284/316, 16 hunks, 550 differing bytes:

| variant | result |
| --- | --- |
| `alpha-int` (each alpha read into an `int`) | 284/316, 16 hunks, 550 bytes — identical to baseline |
| `alpha-locals`, `alpha-register`, `pixel-local`, `outer-alpha-only` | a branch retargets (+0x58, +0x1d or +0x38f), so the shape changes well before the compare |

Widening the alpha to `int` compiles byte-identically, so the compare operand
being in a register is not sufficient: c2 still emits `test eax,eax` rather
than `xor ebx,ebx` / `cmp eax,ebx`. The other four spellings change control
flow before they reach the compare. Region stays equivalent.

# 2026-10-18 FontFillReg session: zero-register mechanism decoded; stores family closed (550 -> 549)

Measured with the byte gate (`variant.py`, `equivalence.py --layout`), working in
/tmp/campaign/font_fill. Final spelling (`F1-chain-body-only`, kept):
the 32-bit path's reset block reordered to
`n = 0; sum[1] = sum[2] = sum[0] = 0;` (was `sum[0] = 0; sum[1] = 0;
sum[2] = 0; n = 0;`). Result: 285/316 identical (was 284), 16 recorded
differences (layout updated in the sandbox copy), 549 differing bytes (was 550),
`equivalence.py` gate clean (`not_equivalent: []`, base_index_order 0,
frame_offset 0). The chained reset makes the green/blue zero stores source
red's register (EBX) exactly as retail (`mov [esp+20h],ebx / mov [esp+1ch],ebx`);
the old spelling sourced the count's register (ESI). The trade: the left-alpha
compare flipped from `cmp BYTE PTR [ecx+1],0x0` (matched) to
`cmp BYTE PTR [ecx+1],bl` (new `register-choice` hunk at 0x258).

## Mechanism established this session (c2 13.10.6030, traced with
compiler_traces/regalloc/ + a CmdCanEnregImmed/GrgRewriteImmedAsReg trace)

1. Every eligible `0` immediate is rewritten to one function-wide register
   candidate (CmdIdentifyImmedCandidates / GrgRewriteImmedAsReg); all 25 zero
   tuples of this function were rewritten, including the byte alpha compares
   (`cmp <mem6>, imm0 | base-reg` tuples) and the loop-guard compares.
2. The emitted form depends on the zero candidate's piece at the use:
   - piece registered in a byte register -> `cmp [mem8], bl` (F1's 0x258);
   - piece registered in a non-byte register -> the compare is unencodable and
     materialises `mov r8,[mem8]; test r8,r8` with Riscify's round-robin scratch
     (the baseline's `mov bl,[ecx+5]; test bl,bl`, scratch BL/AL/DL rotating);
   - piece spilled (SpillObvious: 1 ref + f40 < 1) -> the immediate is
     rematerialised: `cmp [mem8],0` (retail's alphas) and `test r,r` for
     register compares (retail's `i > 0` / `j > 0`).
3. Retail's `xor ebx,ebx` at the path entry and after the stores is the same
   zero/red candidate: `sum[0] = 0` coalesced with the zero immediate, its def
   placed at the loop preheader and re-established at the latch. Retail's
   guards (`cmp eax,ebx` / `cmp edi,ebx`) are `cmp <var>, 0` compares whose
   zero piece is registered; the model's pieces at the guards fail
   (1 ref, no f40) and fold to `test`.
4. The alpha compare splits when a byte-capable scratch register is free at the
   compare (all four of EAX/ECX/EDX/EBX live -> `cmp [mem],0` survives, as at
   retail's head/left compares); this is why red's zero def placement decides
   the head-alpha form.

## Levers ruled out this session (all measured, `bytes` per variant.py)

- Reset orders in the 32-bit body (12 spellings: n-first, chains, reversed
  chains, blue-green-first, red-last): 549-555 bytes, 18-31 hunks; only
  `n = 0` first + the chain order moved bytes (-1). The 4-bit path's reset
  order is load-bearing (`sum[0] = sum[1] = sum[2] = 0; n = 0;`): four
  respellings cost 2-6 bytes.
- Alpha-test polarity (`if (!c[5])`, `if (c[5] != 0) {} else`, `!(c[5] != 0)`):
  byte-identical to the plain form (the IL tuple is the same).
- Loop-guard spellings (explicit `if (rows != 0)` + do-while, named bound
  locals, wrapped fors): identical or 7-300 bytes worse; the guard compares'
  form is decided by the zero piece, not the spelling (confirmed: spellings of
  the test never change this, cf. msvc-c2-immediate-register-candidates).
- Struct access shapes (Pixel8888 p-stores, struct reads + c/q stores,
  struct-via-(c+2)): reproduce retail's zero register exactly (`xor ebx,ebx`
  at entry + `cmp reg,ebx` guards + latch xor) but fold the two IVs into one
  and rotate the register map (231-251/316, 32-40 hunks); the c+2 spelling
  gives retail's displacements but c2 re-derives them from q.
- Latch-reset shape (`sum[0] = 0` before the loops + after the stores, body
  without sum[0]'s reset): flips both guards to `cmp reg,ebx` and the left
  alpha to the immediate form (retail!) but spills red to the aggregate slot
  (857-869 bytes).
- The `c = q - 2` declaration inside the row loop (the per-row `lea` lever)
  re-confirmed catastrophic on the current source: 853 bytes.

## What remains (16 hunks, 549 bytes)

- 4-bit nibble packing (3 hunks, 0x17e-0x1c3): retail reads the halved sums as
  bytes (`and cl,0Fh; movzx ax,cl`, blue via `mov cl,[esp+20h]`) where the
  source masks whole registers. The byte-cast spellings that give retail's
  packing flag blue for the byte-register pressure check and push the
  right-neighbour temporary to ESI (recorded 2026-10-10 dead ends).
- 32-bit guards (5 hunks): `xor ebx,ebx` at entry + `cmp eax,ebx`/`cmp edi,ebx`
  need the zero piece to survive at the guard blocks (2 refs) with red staying
  an ECX/EBX aggregate element; every spelling that extends the zero's range
  (hoisted/latch resets) spills red out of the aggregate.
- Alpha forms (2 hunks): head `cmp [ecx+5],0` needs no free byte scratch at the
  head (red's def before the compare) AND the zero piece failed there; F1's
  0x258 needs the zero piece failed at the left-alpha block while the stores'
  piece stays registered — retail manages exactly this split and the model's
  pieces merge.
- Tail scheduling (5 hunks): `mov [ecx+4],bl` placement, the latch
  `xor ebx,ebx`, `add ecx,4` order.

Best hypothesis for the remaining contest: retail's zero pieces are split
per referencing cluster (the two guard compares share one piece, the two zero
stores share one, each lone alpha compare has its own) while the model's pieces
merge per block; the split granularity is what keeps the stores' piece on EBX
while the lone alpha pieces fold to immediates.
## 2026-10-18 (later): SpillObvious piece-formation traced; the residual's
## split granularity is NOT source-reachable — region parked at 549 bytes

Traced with a SpillObvious (0x107A9D71) candidate dump and a joined
reference/tuple trace (REF candidate-num + operand node x TUPLE opcode +
operand kinds), on the kept F1 spelling (`trace/spillobvious.txt`,
`trace/join2.txt` in the sandbox).

### Verdict-input decode (SpillObvious)

SpillObvious walks the candidate list by number and spills a candidate when
`+0x24` (referencing instructions) < 2 AND (`+0x40` (f40) < 1 OR its `+0x3c`
tuple is not a 0x26a move); candidates with `+0x24 == 2` go through
FUN_107ac13e. At that moment the zero immediate is ONE big piece (r24 = 25 =
the 25 rewritten zero tuples) or two (10+10 / 10+5) — NOT per referencing
cluster. The 14-piece structure seen in the Spillcosts trace forms LATER, by
the fail -> re-queue split (0x10801B42) around register-killing blocks
(cdq/div), and each retry re-splits finer.

### What the pieces actually cluster (the join trace, per round)

The zero's 25 ref sites form one contiguous IL-ordered sequence
(14 MOV sites = the resets/inits/stores, 6 CMP sites = the guards/IV
compares and the alpha compares, plus 3 other ops). Every piece covers a
CONTIGUOUS RANGE of that sequence; the boundaries move between rounds:

  round 4: #45 sites 1-7 (MOV,CMP,MOV,op33,MOV,MOV) | #48 sites 8-10
  round 5: #57 sites 1-6 | #14 sites 7-8 | #12 sites 9-14 (incl. a CMP-mem)
  round 6: #32 sites 1-3 | #62 sites 4-6 | #44 sites 7-10
  round 7: #14 site 1 | #46 sites 2-3 (a CMP + a MOV) | #58 ... | #57 ...

So the two guard compares do NOT share a dedicated piece, lone alpha compares
do NOT get their own piece: guard CMPs sit inside pieces with the adjacent
reset MOVs, and a CMP-mem (alpha) shares a piece with surrounding MOVs
(round 3's #62 = MOV,MOV,CMP-reg,MOV,CMP-mem). Membership is range-based,
not kind- or cluster-based.

### The register-form substitution (why F1's 0x258 is `bl`)

A rewritten zero reference emits the register form when a register holding 0
is live at the use (the coalesced zero+red candidate in EBX, prio 632);
otherwise the zero piece's fate decides (registered in a non-byte register ->
`mov r8,[mem8]; test r8,r8` with a Riscify scratch; failed -> `cmp [mem8],0`).
F1's stores + left-alpha sit after red's reset (`xor ebx,ebx` in the body) and
substitute EBX (`mov [esp+1ch],ebx`, `cmp [ecx+1],bl`); the guards sit before
it and fall back to `test`. Verified by moving red's reset into the left
block's else branch (M1): the `bl` form disappears (the alpha becomes
`mov dl,[ecx+1]; test dl,dl`) and the stores still borrow EBX — but red then
spills to the aggregate slot and the region regresses to 556 bytes.
Retail's guards get the register form because its zero/red def is at the path
entry (`xor ebx,ebx` at 0x20d) — the latch-reset shape reproduces that
(D1/S10 flip both guards to `cmp reg,ebx`) but spills red (857 B) or folds the
two IVs (struct forms).

### Why the retail alpha forms are not reachable

Retail's head/left alphas are `cmp BYTE PTR [ecx+N],0x0` (immediate) while its
stores borrow EBX in the SAME block. That requires the alpha's zero reference
to be absent (its load-candidate temp's immediate excluded
CmdCanEnregImmed-wise and the temp rematerialised as a memory operand at the
use, cf. msvc-c2-choosephysreg-cost-score) or in a piece that fails while the
stores' piece wins — a piece boundary between two adjacent same-block sites,
never observed in any round of the trace. All model spellings produce
mem-form compare tuples (the canenreg trace: 5 x `op=2f src{k6|k7 imm0|k1}`
alpha tuples, all rewritten to the zero candidate); 40+ source variants
(reset orders/placements, polarity, struct forms, guard spellings) change the
substitution point or the register rotation but never the piece clustering.

Recorded dump excerpts: trace/spillobvious.txt (call 1: the zero
`#3 r24=25 f40=-2 op=26a`; call 5: `#1 r24=10 av[6] | #17 r24=10 av[1,3]`),
trace/join2.txt (the REF/TUPLE stream above). Region parked: the remaining
549 bytes need the retail IL's alpha-load-candidate shape (a per-use load
candidate whose immediate is excluded), which is not reachable from the
spellings in this source's style; everything else is explained and measured.
