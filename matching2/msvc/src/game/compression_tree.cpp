#include "th10/game/compression_tree.hpp"

// 0x00436260. Replace one parent-to-child link, then detach the old child.
// The sentinel's parent is written too when replacement is zero.
#pragma code_seg(".text$10relink")
void CompressionTree_RelinkChild(int source, int replacement) {
    g_compression_tree.nodes[replacement].parent =
        g_compression_tree.nodes[source].parent;
    if (g_compression_tree.nodes[g_compression_tree.nodes[source].parent].right == source) {
        g_compression_tree.nodes[g_compression_tree.nodes[source].parent].right = replacement;
    } else {
        g_compression_tree.nodes[g_compression_tree.nodes[source].parent].left = replacement;
    }
    g_compression_tree.nodes[source].parent = 0;
}

// 0x00436330. The predecessor is the rightmost node in the left subtree.
#pragma code_seg(".text$30predecessor")
int CompressionTree_FindPredecessor(int node) {
    node = g_compression_tree.nodes[node].left;
    while (g_compression_tree.nodes[node].right) {
        node = g_compression_tree.nodes[node].right;
    }
    return node;
}
#pragma code_seg()
