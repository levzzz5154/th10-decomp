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
