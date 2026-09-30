// Compiler context only; no context bytes count as recovered game code.
#include "../../src/archive/lzss_tree_initialize_root.cpp"
#pragma code_seg(".text$03context")
void __stdcall LzssRootContext(const int* nodes, int count) {
    for (int i = 0; i < count; ++i) Lzss_InitializeRoot(nodes[i]);
}
#pragma code_seg()
