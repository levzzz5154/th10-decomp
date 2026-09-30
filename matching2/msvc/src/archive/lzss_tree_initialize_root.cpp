#include "th10/game/compression_tree.hpp"

// 0x00435FA0. Make one dictionary position the match tree's first node.
// The root's right link is also the legacy data_0048F860 symbol.
#pragma code_seg(".text$01accessor")
__declspec(noinline) void Lzss_InitializeRoot(int node) {
    g_compression_tree.nodes[0x2000].right = node;
    g_compression_tree.nodes[node].parent = 0x2000;
    g_compression_tree.nodes[node].right = 0;
    g_compression_tree.nodes[node].left = 0;
}
#pragma code_seg()
