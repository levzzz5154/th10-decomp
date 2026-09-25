# `0x00454479` small-block heap region release

The readable C++ model is in
[`unassigned_00454479.cpp`](../semantic_candidates/unassigned_00454479.cpp).
It preserves the existing C-linkage entry symbol and implements a no-argument
`__cdecl` procedure.

## Behavior

The routine reads the current small-block heap group from `0x00499324` and the
region index from `0x0049933C`. If there is no current group, it returns. It
decommits the corresponding 32 KiB range with `VirtualFree` (`MEM_DECOMMIT`),
marks that region available in the group bitmap, clears its region metadata
word, and decrements the group's active-region count. When that count becomes
zero, it clears bit zero of the group's upper class bitmap.

If all region bits are available and the descriptor table contains more than
one group, it frees the group's metadata allocation, compacts the 20-byte
descriptor table with `asm_memmove_00453280`, and decrements the descriptor
count. In all non-null-group cases, it clears the current-group global before
returning. The `VirtualFree` and `HeapFree` return values are ignored, matching
the instructions.

## Ghidra evidence and ABI

Ghidra's `disassemble_bytes` covers the complete 209-byte extent
`0x00454479..0x00454549`: it begins with the global load at `0x00454479` and
ends with a plain `RET` at `0x00454549`. The preceding
`___sbh_resize_block` ends with its own `RET` at `0x00454478`; the next known
function, `___sbh_heap_check`, starts at `0x0045454A`.

Ghidra does not currently create a function at `0x00454479`, and reports no
incoming xrefs to the entry. The decoded body reads no stack arguments, changes
only EAX/ECX/EDX among the general registers, and returns no value. Its Windows
API calls are stdcall calls; its `memmove` call is cdecl and explicitly
caller-cleaned. These observations support a normal `void __cdecl(void)` body
without a private register or stack ABI. The missing incoming xref leaves the
helper's original symbolic name and caller context unidentified.

The manifest now classifies the full 209-byte range as semantic C++ and keeps
the raw entry symbol as its link name. The shared symbol header declares the
observed no-argument cdecl ABI; the routine's exact original name remains
unidentified.

**Build status (2026-09-25):** the full byte-verified build showed that this model does not reproduce the retail bytes. The maintained source keeps the exact assembly, and the model is preserved in `reference/semantic_candidates/`.
