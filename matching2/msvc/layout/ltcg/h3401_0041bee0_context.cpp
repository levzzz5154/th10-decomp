// Compiler context only; never selected as recovered game code.
#include "../../src/unidentified/FUN_0041bee0_0041bee0.cpp"

#pragma code_seg(".text$03context")
extern "C" __declspec(noinline) int __cdecl M3401Context_0041bee0(
        H3401LinkNode_0041bee0** nodes,
        H3401LinkNode_0041bee0** peers,
        int count) {
    int total = 0;
    while (count--) {
        total += (*nodes++)->Link(*peers++) != 0;
    }
    return total;
}
#pragma code_seg()
