// Compiler context only; never selected as recovered game code.
#include "../../../src/unreferenced/unassigned_41c0b0.cpp"
#pragma code_seg(".text$03context")
extern "C" __declspec(noinline) void __stdcall InsertContext_0041c0b0(
        List** lists, Node3** nodes, int count) {
    for (int index = 0; index < count; ++index) Insert(lists[index], nodes[index]);
}
#pragma code_seg()
