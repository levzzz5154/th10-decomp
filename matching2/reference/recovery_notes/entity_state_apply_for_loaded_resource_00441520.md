# `0x00441520` — entity state update gated by animation resource

Status: **semantic C++ region; private entry ABI and byte exactness unresolved**.
The source is `src/unidentified/unassigned_00441520.cpp`; the manifest now
classifies its 97-byte region as semantic while retaining the original C
symbol name for the source definition.

## Observed behavior

Ghidra's listing and decompilation show a leaf routine that walks a count of
fixed-size entities. It updates the 16-bit field at entity offset `+0x304` only
when the following resource path is present:

1. Read the animation handle pointer at entity offset `+0x394`.
2. Read the signed resource ID from the first dword of that handle; skip null
   handles and negative IDs.
3. Load the manager pointer stored at `data_00491c10`, then index its resource
   pointer table at manager offset `+0x3AD06C` by that ID.
4. Require both a non-null resource and a non-null pointer at resource offset
   `+0x120` before storing the supplied 16-bit state.

The loop advances entities by `0x3AC` bytes. The retail body does not perform an
upper-bound check on the resource ID before indexing the table, so the model
preserves that observed behavior rather than adding a guessed limit. It also
leaves the entity state untouched when any resource check fails. For a zero
count it returns before loading the global manager pointer, matching the early
branch at `0x00441528`.

## ABI evidence and model limitation

The retail entry reads its count from EAX and its base pointer from ECX. At
`0x00441523`, after saving EBP, `mov bp, word ptr [esp+8]` loads the low word of
the first stack argument; `0x0044157E` returns with `ret 4`. Ghidra consequently
shows the live count as `in_EAX`, with a `this` pointer and a 16-bit stack
parameter. The source uses explicit ordinary C++ arguments `(entity_base,
entity_count, state_value)` to make the algorithm readable. That declaration
does not preserve the retail register/stack calling convention and must not be
treated as a drop-in ABI reconstruction.

The loop and field conditions follow the observed instructions at `0x00441520`
through `0x00441578`: the entry count test, `+0x394` handle read, signed-negative
ID branch, manager slot lookup, resource `+0x120` test, `+0x304` word store, and
`+0x3AC` iteration step. This is a semantic model only; no compiler-output
comparison or exactness claim has been made.

## Earlier recovery evidence

`ownerless_60_256_wave19.md` recorded this region as blocked for exact compiler
recovery because its entry depends on EAX and ECX plus a stack word. This update
retains that caveat while replacing the assembly-only body with a readable loop
model. The original alias remains in the manifest symbol map. No build, probe,
or tests were run.
