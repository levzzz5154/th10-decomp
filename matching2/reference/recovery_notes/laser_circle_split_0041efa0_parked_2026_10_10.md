# Circle laser split 0x0041EFA0: parked at 413 differing bytes (2026-10-10)

Source: `matching2/msvc/layout/ltcg/laser_cut/circle_cut.cpp`, a context
function of the `laser_cut` cluster. It has the retail size (1108 bytes) and the
same statements as the rectangle split, with `IsPartiallyOutside` and
`CreateOffset` inlined by the compiler (retail inlines them here and not in the
rectangle split only because of the block weight: one condition instead of four
in front of the hit block).

## What still differs

1. `count` lives in EDI in the model. Retail keeps it in EDX, stores it to its
   stack home after every definition (`inc edx; mov [esp+0x2c],edx`) and reloads
   it after the calls of the hit block, while EDI holds the inlined creator's
   resource pointer across the allocation call. The model spills the resource
   pointer to the stack instead.
2. `point += step` loads the step component first (`fld step; fadd point`);
   retail loads the point component first, for x and y only.
3. Entry: retail stores `step.z = 0` from EAX (the zero left by the `cut`
   memset) and the two counters from EDX; the model uses EDI for all of them.
   This follows from 1.
4. Unbound literal addresses of the helper constants (not a code difference).

## What was measured

`ChoosePhysReg` gives EDI to `count` (priority 71 after the first-pass spills
are re-costed) before the resource pointer and the script index (both
4 refs * K 7 * weight 2 = 56, never re-costed because they are block-local).
Removing 24 points from `count` (dropping one inner-loop test, which changes
the code) still left it in EDI, so the contest is not decided by that order
alone.

Putting `point`, `step`, `hit_count` and `count` in one struct whose address
escapes gives the resource pointer EDI and makes `count` reload after calls,
but it also makes every point write go straight to memory; too much.

No effect on either residual (36 combinations and single changes): named or
nested `index` / `resource` / `bank` / `sample_position` locals, named or
inline `dx` / `dy` / `distance`, operand order of the circle test, `<=`
instead of `!(>)`, `for` instead of `while`, unsigned `count`, a `total`
copy, a named result of `CreateOffset`, unused extra locals, declaration order
of `point` and `step`, and all orders of the creator's flag and bucket
statements. Declaring the counters before the `memset` moves `count` to ESI
and `this` to EBX (wrong). `step.z = 0` before the `memset` turns that store
into an immediate (wrong).

## Where to look next

The operand order of a local vector add depends on the local symbol ids
(`(id & 7) << 13`), so residual 2 says the retail function numbers its locals
differently; the same numbering may feed the register contest. Trace
`OptHashNode` for the two adds to learn the required shift before trying more
spellings. The standalone creator at 0x00448DB0 in this cluster still emits its
bucket store after the flag store (retail: before the `or`); the production
copy uses volatile accesses for that, so the natural source of the creator is
not known either and may be the real difference.
