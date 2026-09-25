# `0x00453C52` `___sbh_heap_init` semantic model

The ordinary C++ model is in
[`sbh_heap_init_00453c52.cpp`](../semantic_candidates/sbh_heap_init_00453c52.cpp).
It preserves the C-linkage symbol with the recovered
`int __cdecl asm_sbh_heap_init_00453c52(unsigned int size)` ABI.

## Behavior

The function calls `HeapAlloc` through the IAT pointer at `0x004661E4`, passing
the process heap handle from `0x00499340`, flags `0`, and allocation size
`0x140`. It stores the returned pointer at `0x0049932C` and returns `0` if the
allocation fails. On success, it clears the dwords at `0x00499324` and
`0x00499328`, stores the allocation pointer at `0x00499334`, copies the caller's
`size` argument to `0x00499330`, stores `0x10` at `0x00499338`, and returns
`1`.

## ABI and call graph

Ghidra shows one stack argument at entry (`[ESP+4]`), a plain `RET`, and an EAX
result of `0` or `1`. There are no private register inputs. `HeapAlloc` is the
only callee; its three arguments use the Windows API stdcall convention.

Ghidra's defined-caller listing reports `__heap_init` at `0x004539CB`, which
calls this function at `0x004539FF` with `0x3F8`. Ghidra also has an incoming
call xref at `0x0045489B`, but does not identify a defined caller for that
address. The existing source model in `unassigned_00454863.cpp` places that
call within its threshold helper at `0x00454863` and passes the requested size.

## Exactness limits

This is a semantic model; it does not claim byte identity with the retail
region. The region is identified as VC7.1 CRT code, and the matching CRT source
is not present locally. The manifest now classifies the 72-byte row as
semantic under the unchanged `_asm_sbh_heap_init_00453c52` symbol and preserves
the old assembly record in `previous_record`. Ghidra's plate comment records
the algorithm, cdecl stack input, both callsite forms, and the HeapAlloc callee.
No build or tests were run for this model.

**Build status (2026-09-25):** the full byte-verified build showed that this model does not reproduce the retail bytes. The maintained source keeps the exact assembly, and the model is preserved in `reference/semantic_candidates/`.
