// Compiler context only; never selected as recovered game code.
#include "../../src/unidentified/unassigned_0041c0d0.cpp"
#pragma code_seg(".text$03context")
extern "C" __declspec(noinline) void __stdcall RemoveContext_0041c0d0(
        List_0041c0d0** lists, Node_0041c0d0** nodes, int count) {
    for (int index = 0; index < count; ++index) Remove_0041c0d0(lists[index], nodes[index]);
}
#pragma code_seg()
