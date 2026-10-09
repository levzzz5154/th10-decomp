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
