#ifndef TH10_GAME_COMPRESSION_TREE_HPP
#define TH10_GAME_COMPRESSION_TREE_HPP

#include <stddef.h>

struct CompressionTreeNode {
    int parent;
    int left;
    int right;
};

// Score compression uses 8,192 window positions and one extra root node.
// Node zero is the null sentinel; the root is node 0x2000.
struct CompressionTree {
    enum { NodeCount = 0x2001 };
    CompressionTreeNode nodes[NodeCount];
};

extern CompressionTree g_compression_tree;

__declspec(noinline) void CompressionTree_RelinkChild(int source, int replacement);
__declspec(noinline) int CompressionTree_FindPredecessor(int node);
__declspec(noinline) void CompressionTree_ReplaceNode(int source, int replacement);
extern "C" __declspec(noinline) void __fastcall Lzss_RemoveNode_00436210(int node);

typedef char CompressionTreeNode_size_must_be_12[sizeof(CompressionTreeNode) == 12 ? 1 : -1];
typedef char CompressionTreeNode_left_offset_must_be_4[offsetof(CompressionTreeNode, left) == 4 ? 1 : -1];
typedef char CompressionTreeNode_right_offset_must_be_8[offsetof(CompressionTreeNode, right) == 8 ? 1 : -1];

#endif
