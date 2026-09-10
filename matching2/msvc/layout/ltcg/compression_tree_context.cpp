// Compiler context only. These shared uses establish the internal register
// conventions; this caller is not selected into the recovered application.
#pragma code_seg(".text$50context")
#include "../../src/game/compression_tree.cpp"

#pragma code_seg(".text$50context")
void __stdcall CompressionTreeCompilerContext(const int* replacements,
                                               int* predecessors, int count) {
    for (int source = 0; source < count; ++source) {
        CompressionTree_RelinkChild(source, replacements[source]);
        predecessors[source] = CompressionTree_FindPredecessor(source);
    }
}
#pragma code_seg()
