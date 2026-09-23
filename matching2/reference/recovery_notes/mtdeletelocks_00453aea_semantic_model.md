# `0x00453AEA` `__mtdeletelocks` semantic model

The ordinary C++ model is in
[`mtdeletelocks_00453aea.cpp`](../../msvc/src/unidentified/mtdeletelocks_00453aea.cpp).
It keeps the existing C-linkage entry name and `void __cdecl(void)` ABI.

## Behavior

The function walks 36 eight-byte records beginning at `0x00473080`. Each record
contains a critical-section pointer at offset `+0` and a flag at offset `+4`;
flag value `1` identifies statically allocated lock storage.

It makes two passes. The first pass skips null pointers and records whose flag
is `1`; for every remaining record it calls `DeleteCriticalSection`, frees the
storage with `_free`, and clears the pointer slot. The second pass skips null
pointers and records whose flag is not `1`; it calls `DeleteCriticalSection`
but leaves the statically owned storage and table pointer intact.

## ABI and call graph

Ghidra identifies the entry as a no-argument `void __cdecl` function ending in
plain `RET`. It has no hidden register inputs. Retail saves and restores EBX,
ESI, and EDI; the ordinary C++ source relies on the compiler's normal
callee-preservation rules instead of spelling that register schedule.

Ghidra reports one direct caller: `__mtterm` at `0x00456327`. The function
loads the `DeleteCriticalSection` function pointer from `0x004660BC` and calls
it for each selected lock. Its other direct callee is `_free` at `0x00452422`.

## Exactness limits

This source records the recovered behavior and keeps the existing entry ABI.
It does not claim byte identity with the retail body. The region is part of
the VC7.1 CRT; the local recovery notes record that the matching CRT source is
not present, so matching compiler choices for the two loops and cleanup code
remain unverified. The manifest now classifies the 85-byte row as semantic
under the unchanged `_asm_mtdeletelocks_00453aea` symbol and preserves the old
assembly record in `previous_record`. Ghidra's plate comment records the
two-pass algorithm, no-argument ABI, caller, and callees. No build or tests
were run for this model.
