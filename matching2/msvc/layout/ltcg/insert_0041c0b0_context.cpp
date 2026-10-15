// Compiler context only; never selected as recovered game code.
#include "../../src/unreferenced/unassigned_0041c0b0.cpp"
#pragma code_seg(".text$03context")
extern "C" __declspec(noinline) void __stdcall InsertContext_0041c0b0(
        List_0041c0b0** lists, Node_0041c0b0** nodes, int count) {
    for (int index = 0; index < count; ++index) Insert_0041c0b0(lists[index], nodes[index]);
}
#pragma code_seg()
