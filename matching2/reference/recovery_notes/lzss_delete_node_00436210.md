# LZSS match-tree maintenance

2026-09-26. The root initializer at `0x00435FA0`, deletion routine at `0x00436210` and
transplantation helper at `0x004362B0` are now readable C++ in
`src/archive/lzss_tree_initialize_root.cpp`, `src/archive/lzss_tree_remove.cpp`
and `src/archive/lzss_tree_replace.cpp`. Their previous `MemoryFile` labels were
stale. Both belong to the compressor's binary match tree.

## Ghidra evidence

Live Ghidra MCP decompilation, disassembly and call references establish:

| Entry | Complete extent | Contract |
| --- | ---: | --- |
| `0x00435FA0` | 36 bytes | Node index in EAX; void; plain RET |
| `0x00436210` | 80 bytes | Node index in ECX; void; plain RET |
| `0x00436260` | 79 bytes | Source in ESI, replacement in EDX; void; plain RET |
| `0x004362B0` | 117 bytes | Source in EAX, replacement in ECX; void; plain RET |
| `0x00436330` | 49 bytes | Node in EAX; predecessor returned in EAX; plain RET |

The only deletion callers are the compressor's call at `0x00435C8C` and its
own recursion at `0x00436250`. Tree nodes are 12-byte records at `0x00477858`,
with parent, left and right indices at offsets 0, 4 and 8. There are 8192
window positions and an extra root at index `0x2000`; zero is the null
sentinel. The root's right link is also the old `data_0048F860` symbol.
Ghidra now names all five routines and types the global node array. The root
initializer publishes the first node in root.right, sets its parent to
`0x2000`, and clears both child links.

Deletion leaves a node with parent zero alone. With one child, it redirects
the parent's link to that child. With both children, it recursively removes
the rightmost node of the left subtree and transplants that predecessor.
Transplantation copies the three old-node fields and repairs both child-parent
links. Writes to the null sentinel's parent are intentional retail behavior.

## Compiler recovery

`layout/ltcg/compression_tree.json` compiles all four real bodies together.
The recursive entry is rooted to preserve ECX. Its real calls establish the
private helper conventions, while the existing synthetic context retains the
relink and predecessor contributions. No compiler-context or layout-gap
bytes are selected as recovered code.

In transplantation, keep a pointer to the old node for the three-field copy,
use a parent **index** for the parent-link updates, and clear the old node
through `g_compression_tree.nodes[source].parent`. Clearing through the local
pointer instead causes MSVC to load the parent through a scaled global access
before materializing the pointer; that candidate emits 122 bytes. Using a
parent pointer emits 115 bytes. The indexed clear yields the exact 117-byte
body without volatile accesses, instruction patching or assembly.

The root initializer uses the separate `lzss_tree_initialize_root.json`
cluster. Native LTCG retains its EAX input. Its driver includes the shared
node declarations rather than treating root.right as a separate global.

The maintained-source probes verified all five bodies: 36 + 80 + 79 + 117 +
49 = 361 bytes, including every linker-filled target. The three new conversions
remove 233 bytes of inline assembly. The reproducible host-side property check
in `matching2/tests/lzss_tree_properties.cpp` exercises stale-child root
initialization, 6350 randomized deletions and repeated deletion of detached
nodes, verifying binary-search ordering, exact node membership, absence of
cycles and every active parent link. Its compile/run command is in that file.
