# Script name table loader 0x00450220: equivalent recovery (2026-10-11)

`ScriptFileLoader::Parse` now builds from
`msvc/equivalent/script/ecl_name_table_00450220.cpp`: 589 of 589 bytes used,
181 of 198 instructions identical, 13 recorded differences. The exact bytes
stay in `msvc/src/script/ecl_name_table.cpp` for `make EXACT=1`. Plain
`cl /O2` reproduces the function; no LTCG context is needed.

## What the retail code fixes about the source

- The parameter is reused as the cursor over the file's offset table (its
  stack home `[esp+0x24]` is that cursor).
- Both loops advance that cursor in the `for` increment (`i++, data++` and
  `merged++, data++`). With `data++` as the last body statement the split
  `add [mem],4` gets a different scratch register, because Riscify hands them
  out per block scanning backwards.
- The search loop indexes `entries[index].name`; a hand-written walking
  pointer loses retail's strength-reduced walker and its stack home.
- The allocation size is a named local (`size`). Inline in the call the
  product is a rotation temporary and the head uses `lea edx,[eax*8]`.
- `test ebp,ebp` appears twice (branch to the merge path, and before
  `rep movs` for the `je` over `free`). c2 removes the second test whenever
  both tests read one variable, whatever the spelling (macro, inline helper,
  cast, delete expression, nulling free, flag computed from the variable).
  It survives only when the two tests read two locals that are each loaded
  from `entries`; the loads are merged later, after the fold.

## The one open decision: who gets EBP

Only EBX and EBP are available to values that live across the inlined
`strcmp`/`strlen`/`rep movs`. EBX is `this`. Retail gives EBP to the old table
pointer (then to the search index) and leaves the names cursor in memory with
per-block register pieces. In the model the two are ChoosePhysReg candidates a
few points apart, and the names cursor wins unless the old pointer is strictly
ahead (a tie goes to the lower candidate number, the names cursor).

Priorities are `refs * K * weight` per block minus `K * weight` per block lived
through, `K` = candidates referenced in the block. The old pointer has
references only in the head block (K 11), the copy block (K 5) and the free
block (K 1); the names cursor is referenced in both loops.

| source | names | old |
| --- | --- | --- |
| allocation size inline | 67 | 62 |
| named `size` | 69 | 66 |
| + offsets table in a local, copied into the parameter after the names pointer is computed | 71 | 70 |
| + copy size written out again as `name_count - sub_count` (shipped model) | 68 | 70 |

With the old pointer in EBP every other block falls into retail's shape: the
copy block, both loops, the stack frame (0x10), the slot order.

## Why the shipped model is not exact

The extra candidate in the copy block comes from writing the kept count
twice: the compiler computes it once into a temporary and copies it into
`kept`. That copy is a store, so `kept` has no register in the copy block and
is reloaded at the top of the merge loop. Retail computes the count straight
into EDX, uses `lea ecx,[edx+edx]` for the copy length and keeps EDX through
the `free` block (reloading it after the call) into the first loop guard.
Seven of the 13 differences are that; three are the head using ECX instead of
EDX for the new count (the temporary cursor is one step off, which follows
from the temporaries allocated in the copy block), two are padding, one is the
loop back edge reaching the reload.

`memcpy(entries, old, kept * sizeof(ScriptSub))` gives retail's copy block
exactly but drops the old pointer back to 66 against 69. So the true source
has `kept` computed once and some other reason for 4 more points.

## What adds a candidate (measured)

- a named local passed to a real call (`size`); not to `memcpy`;
- an expression written twice and merged late (`entries`, the kept count);
- a single-assignment local that is used and then copied into a variable
  with other assignments (`offsets` into the parameter, a `count` into
  `kept`). The copy must come after the other use, otherwise the later uses
  are rewritten to the target and the local disappears;
- immediates used twice with one type (0, -1, 2, 4, 8 here): they count in
  `K` wherever referenced, with no references of their own.

What does not: statement order in the head, `total`/`chunk`/`header`/`fresh`
locals, loop spellings (`while`, `do`, reversed compares, counter types),
shift or multiply spellings of the sizes, a third pointer local, a nulling
free, a per-iteration copy of the names cursor, a copied search index. A
separate cursor for the fill loop gives retail's merge path but puts the fill
cursor in ESI. A local for `sub_count` wins EBP but stops the per-iteration
re-read. Bounding the search by `kept + merged` removes the walker.

## Next

Find one more candidate referenced in the head block (worth +4 for the old
pointer, +2 for the names cursor, so two are needed there) or one in the copy
block that is not the kept count (+4 and -1), or one in a loop block the names
cursor only lives through (-2 or more per block). Tools: the regalloc tracers
work on a one-entry commands file holding the plain `cl.exe /c /O2 /Gz /MT
/Gy /G6 /GF /GS /Zl` command.

## 2026-10-17: the single-count copy block probed; parked

The `Next` recipe's trade was confirmed exactly as predicted: the single
count spelling (`memcpy(entries, old, sizeof(ScriptSub) * kept)`) fixes the
copy block's seven differences but drops the old pointer's EBP and overshoots
to 40 hunks. Adding the two head-block candidates the recipe calls for
(`int fc_a = file_count; int fc_b = file_count;` each feeding one store, the
`msvc-c2-what-adds-a-register-candidate` merged-late expression shape) moves
the totals the wrong way (47 hunks): the head K values are not the pair the
recipe assumes without the Spillcosts numbers.

Region stays equivalent (366 differing bytes). The next step is unchanged:
trace Spillcosts once and pick the candidate shape from the measured K table.

# ecl_name_table 0x00450220 — note addendum (2026-10-18)

Stage this section into `matching2/reference/recovery_notes/ecl_name_table_00450220_equivalent_2026_10_11.md`
(or the layout's `note` file) on integration.

## 2026-10-18: register contest closed; 4 hunks remain (head name_count rotation)

State: 194/198 identical, 4 hunks, 23 differing bytes (was 181/198, 13 hunks,
366 bytes). Layout `differences` re-recorded to the 4-hunk set (classes:
`evaluation-order` x1, `register-choice` x3); `base_index_order` 0, no
frame_shift; strict check `not_equivalent: []`. Final model:
`msvc/src/script/sptlib/ecl_name_table.cpp` (single-count kept + the `sub`
candidate, see below).

### The EBP lever (the register contest)

Retail gives EBP to the old-table pointer. The contest is ChoosePhysReg
placement order over Spillcosts priority; names wins ties (lower candidate
number), so old must be strictly ahead. Measured at the EBP decision
(trace_choose_physreg.py on the sandbox compile):

| source shape | names | old |
| --- | --- | --- |
| single count (kept = name_count - sub_count) | 69 | 66 |
| + offsets local (row-3 shape) | 71 | 70 |
| + sub candidate in the copy block (final) | 68 | 70 |
| shipped double count (temp + kept-copy) | 68 | 70 |
| + hoisted count in the guard (sub_local) | 58 | 66 |

Priority formula, validated across ten variants:
  old   = 4*K(head) + 4*K(copy) + 2*K(free)
  names = 2*K(head) + SUM(refs*K*w over its six ref blocks) - SUM(K*w live-through)

One candidate added to a block: old gains refs_old(b)*w(b); names gains
refs_names(b)*w(b) if referenced there, else loses w(b). So the copy block is
the (+4, -1) lever and each head candidate is (+4, +2).

The working shape (K(copy) 5 -> 6):

    } else {
        int sub = files[file_count]->sub_count;
        int kept = name_count - sub;
        memcpy(entries, old, sizeof(ScriptSub) * kept);
        if (previous) crt_free((sub == files[file_count]->sub_count) ? previous : previous);

`sub` re-read in the free condition is a constant-true consistency check that
keeps `sub` as a copy-block register candidate (its def plus a real use); the
use must not be a foldable identity (xor/sub self, &0, *0, comma all fold away
and lose the candidacy) and must not be a named copy (propagated). kept's def
stays a real computation so it keeps its cross-block register piece (the
jmp-over-reload at the merge top, the `lea ecx,[edx+edx]` copy length, the
store-before-rep-movs order all follow automatically).

### The head-rotation trade-off (the two levers are coupled)

The final 4 hunks are the head's `name_count` load only:
retail 0x261 `mov edx,[ebx+0x8]` immediately after the chunk_size load (EDX);
model 0x52 `mov ecx,[ebx+0x8]`, deferred past the pushes, data lea and sub load
(ECX), with `add/mov eax/mov [ebx+8]` following in the same register.

Mechanism (msvc-c2-list-scheduler-priority + msvc-c2-temp-register-rotation-named-local):
the load is a rotation temporary; in ECX an anti-edge from the data-lea's
chunk_size ECX reference pins it behind that node, in EDX (retail) the only
earlier reference is long dead and the +32 load bonus hoists it above the
pushes. The rotation is one step off because materialising the `sub` compare in
the copy block allocates one extra single-use expression temporary, and
RegAssign's cursor runs over the whole function.

Trade-off proof (measured): with the second `sub` reference removed
(`int sub = ...; int kept = name_count - sub;` alone, or kept reading the
member), the head is EXACT (mov edx,[ebx+0x8] at 0x261) but K(copy) falls back
to 5 and the flip is lost (names 69 > old 66, 40 hunks). With any second
reference kept (nine compare spellings tested: ==0, !=0, >=0, >-1, ==sub, ==2,
==4, !=-1, ==0x10000, byte-cast, multi-and), the flip holds at 4 hunks / 23
bytes but the head rotation stays off. So the copy-block candidate and the head
rotation are coupled through the temp count; closing the last 23 bytes needs
either a reference form that allocates no temporary, or a compensating temp
removal elsewhere in the function.

### Ruled out (evidence in /tmp/campaign/ecl_name/STATUS.md)

free-block named-local shapes; third/fourth `entries` loads (merged away);
head double-load pairs (fc_a/fc_b 47, name/chunk/sub pairs 0-change, total/na/nb
0-change, slot pair 45, fa/fb pair 45); offsets doubled (names priority explodes
to 119 - wrong direction); C++ reference aliases (frame grows 0x10 -> 0x14);
double-count orderings (dbl_rev/D4/r1-r4/t1 collapse to the shipped
temp+copy = 13/366, or break the memcpy fold into shl/shr + rep movsb);
shift-loop use-then-copy (j-shape: code grows 15 bytes -> "short branch leaves
the function"; field-copy spelling: the address recomputes, +15 bytes);
use-then-copy into names/kept/index (folded away or wrong block);
operand-order sweeps (7 shapes, 0 change); `count + merged` IV bound (41);
sub-expression splits and statement reorders (0 change or 41-45).
