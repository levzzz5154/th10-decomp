#include "th10/game/compression_tree.hpp"
// 0x00436210. Delete a match-tree node, transplanting its predecessor
// when both children exist. Zero is the detached/null node sentinel.

#pragma code_seg(".text$05remove")
extern "C" void __fastcall Lzss_RemoveNode_00436210(int node) {
    if (g_compression_tree.nodes[node].parent == 0)
        return;
    if (g_compression_tree.nodes[node].right == 0) {
        CompressionTree_RelinkChild(node, g_compression_tree.nodes[node].left);
        return;
    }
    if (g_compression_tree.nodes[node].left == 0) {
        CompressionTree_RelinkChild(node, g_compression_tree.nodes[node].right);
        return;
    }
    int predecessor = CompressionTree_FindPredecessor(node);
    Lzss_RemoveNode_00436210(predecessor);
    CompressionTree_ReplaceNode(node, predecessor);
}
#pragma code_seg()
