// The live entry at 0x00436210 is the LZSS match-tree deletion routine.
// Its node index arrives in ECX; the old `MemoryFile_RemoveNode` label is stale.

struct LzssMatchNode_00436000 {
    int parent;
    int left;
    int right;
};

extern "C" LzssMatchNode_00436000 data_00477858[];

namespace {

void RelinkChild(LzssMatchNode_00436000* nodes, int source, int replacement) {
    const int parent = nodes[source].parent;
    nodes[replacement].parent = parent;
    if (nodes[parent].right == source)
        nodes[parent].right = replacement;
    else
        nodes[parent].left = replacement;
    nodes[source].parent = 0;
}

int FindPredecessor(const LzssMatchNode_00436000* nodes, int node) {
    int predecessor = nodes[node].left;
    while (nodes[predecessor].right != 0)
        predecessor = nodes[predecessor].right;
    return predecessor;
}

void ReplaceNode(LzssMatchNode_00436000* nodes, int source, int replacement) {
    const int parent = nodes[source].parent;
    if (nodes[parent].left == source)
        nodes[parent].left = replacement;
    else
        nodes[parent].right = replacement;

    nodes[replacement] = nodes[source];
    nodes[nodes[replacement].left].parent = replacement;
    nodes[nodes[replacement].right].parent = replacement;
    nodes[source].parent = 0;
}

} // namespace

// The single explicit parameter uses the observed ECX input register. Calls
// recurse through this typed entry instead of relying on private register
// conventions in the old relink, predecessor, and replace helpers.
extern "C" __declspec(noinline) void __fastcall Lzss_RemoveNode_00436210(int node) {
    LzssMatchNode_00436000* const nodes = data_00477858;
    if (nodes[node].parent == 0)
        return;

    if (nodes[node].right == 0) {
        RelinkChild(nodes, node, nodes[node].left);
        return;
    }
    if (nodes[node].left == 0) {
        RelinkChild(nodes, node, nodes[node].right);
        return;
    }

    const int predecessor = FindPredecessor(nodes, node);
    Lzss_RemoveNode_00436210(predecessor);
    ReplaceNode(nodes, node, predecessor);
}
