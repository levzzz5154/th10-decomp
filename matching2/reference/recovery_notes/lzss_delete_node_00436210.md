# LZSS match-tree deletion `0x00436210`

Date: 2026-09-23

## Live Ghidra evidence

Read-only queries against the active `th10.exe` program report one function at
`0x00436210`, body `0x00436210..0x0043625F` (80 bytes). The entry takes one node
index in `ECX`, returns with plain `RET`, and has no other incoming state. The
compressor caller at `0x00435C8C` sets `ECX` from `ESI` immediately before the
call. The only other callers are the function's own recursive call at
`0x00436250`.

The three tree fields are 32-bit integers at offsets `+0`, `+4`, and `+8` in
each 12-byte record rooted at `0x00477858`: parent, left child, and right
child. This ordering is visible in the insertion body at `0x00436000`, the
deletion body, and the related helpers.

The deletion cases in the live body are:

1. Return when `parent == 0` (the node is not linked).
2. If there is no right child, relink the left child in the node's parent.
3. Otherwise, if there is no left child, relink the right child.
4. With both children, find the rightmost node in the left subtree, recursively
   detach it, and replace the deleted node with it.

The adjacent live helper contracts were checked directly from their
disassembly. `0x00436260` reads the source index from private `ESI` and the
replacement from `EDX`; `0x00436330` reads its node index from `EAX` and returns
the predecessor in `EAX`; `0x004362B0` reads the source index from `EAX` and
replacement from `ECX`. The new implementation performs those same tree
updates directly in typed C++, so it does not depend on the helpers' private
register conventions.

## Implementation and integration

`matching2/msvc/src/platform/memory_file_remove_node_00436210.cpp` now defines
`extern "C" void __fastcall Lzss_RemoveNode_00436210(int node)` and implements
the cases above against `data_00477858`. The previous `MemoryFile_RemoveNode`
label was stale; this routine belongs to the LZSS match tree used by the
compressor. Its one-argument ECX ABI is explicit in the typed entry. The
compressor now calls that typed entry, and the shared declaration and manifest
row use its fastcall symbol. No build, probe, or test was run, so compiled byte
equality and symbol placement remain unverified.
