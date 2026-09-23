# Pair addition and copy at `0x00427D00`

Ghidra identifies a 34-byte function, `0x00427D00..0x00427D21`. Its input
pair pointers arrive in `ECX` and `EDX`; an implicit output pointer is in
`EAX`. The disassembly establishes this behavior:

1. Add the two 32-bit words at `EDX + {0,4}` to the target words at
   `ECX + {0,4}`.
2. Store both sums back through `ECX`.
3. Copy the updated words from the target to the output at `EAX`.
4. Return without stack cleanup.

The readable candidate in `src/unidentified/unassigned_00427d00.cpp` models
this as a pair member that mutates its receiver and returns the updated pair by
value. The candidate gives the fields unsigned 32-bit types so overflow has
the modulo-2^32 behavior of the x86 `ADD` instructions. Ghidra's decompiler
renders the source words as `int`; retail code does not establish their
signedness. The class/member spelling and the explicit `__fastcall` annotation
are modeling choices, not recovered source facts. A user-defined copy
constructor makes the pair a nontrivial aggregate in the candidate, allowing
an implicit output buffer to be considered by the compiler.

The direct `Pair __fastcall` return attempt described in
`byte_sum_and_vector_return_0044c080_00427d00_004051f0.md` emitted 27 bytes
and returned the pair in `EDX:EAX`, unlike retail. The new `layout/ltcg`
context instead calls a mutating member that returns the updated pair. This is
a plausible way to model the observed receiver, delta, and output registers,
but neither the source ABI nor this context's placement and size has been
confirmed.

No build, probe, or test was run for this candidate. The semantic operation is
supported by Ghidra's listing and decompilation; source layout, exact ABI,
symbol decoration, compiler output, and byte equivalence all remain
unverified. The `size` and context extent in
`layout/ltcg/pair_add_copy_00427d00.json` are provisional layout entries, not
measured output.
