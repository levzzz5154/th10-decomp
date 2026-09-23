# Archive-load cache slot helper at `0x0043D640`

## Recovered behavior

Ghidra's disassembly covers 37 bytes, `0x0043D640..0x0043D664`. The routine
calls `0x0044B360` with two zero stack arguments, stores the returned pointer at
`owner + 0x5230 + slot_index * 4`, then returns `0` for a non-null pointer or
`-1` for null. The null result is stored as well. Ghidra reports no incoming
xrefs to this entry; the direct call to `0x0044B360` is present at
`0x0043D644`.

The helper's decompilation identifies its hidden EAX input as the filename.
With the two zero stack arguments, `0x0044B360` performs a packed-archive
lookup/load (its `fromDisk` argument is zero) with no size-out pointer. Its
return value is the loaded buffer. The readable source model is in
`msvc/src/unidentified/unassigned_0043d640.cpp` and calls the existing
`Archive_LoadFile(file_name, 0, 0)` semantic interface.

## ABI and exactness

At retail entry, the filename is already in EAX; `[ESP+4]` is the owner and
`[ESP+8]` is the slot index. The routine returns with `RET 8`, cleaning those
two stack arguments. The helper call separately pushes its two zero arguments,
which the helper cleans with its own `RET 8`. This mixed convention cannot be
spelled by the ordinary C++ signature used for the semantic model, so the
source makes the filename an explicit parameter and uses a C `__cdecl`
symbol to retain the manifest's existing C-linkage symbol spelling. The
`Archive_LoadFile` header records that its retail name input is also EAX and
that its other two inputs are stack arguments; the current source signature
alone does not force this wrapper/helper pair to reproduce those register
roles or either `RET 8`. Matching them would require native-LTCG evidence for
the complete call topology. Byte-exactness and ABI matching are therefore
unverified. The manifest now classifies this span as semantic and preserves
its former assembly record. No build, probe, or test was run.
