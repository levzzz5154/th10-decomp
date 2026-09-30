#include "th10/game/compression_tree.hpp"
// 0x004362B0. Transplant a detached predecessor into the old node
// position and repair both children, including the null sentinel.

#pragma code_seg(".text$25replace")
void CompressionTree_ReplaceNode(int source, int replacement) {
    CompressionTreeNode* old_node = &g_compression_tree.nodes[source];
    int parent = old_node->parent;
    if (g_compression_tree.nodes[parent].left == source)
        g_compression_tree.nodes[parent].left = replacement;
    else
        g_compression_tree.nodes[parent].right = replacement;
    g_compression_tree.nodes[replacement] = *old_node;
    g_compression_tree.nodes[g_compression_tree.nodes[replacement].left].parent = replacement;
    g_compression_tree.nodes[g_compression_tree.nodes[replacement].right].parent = replacement;
    g_compression_tree.nodes[source].parent = 0;
}
#pragma code_seg()
