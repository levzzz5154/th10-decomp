// Compiler context only; never selected as recovered game code.
#include "../../../src/unreferenced/unassigned_428f30.cpp"

inline void* operator new(unsigned int, void* place) { return place; }

#pragma code_seg(".text$03context")
int __stdcall PoolBlockOwnerContext_00428f30(PoolBlockOwner* owners, int count) {
    for (int i = 0; i < count; ++i)
        new (&owners[i]) PoolBlockOwner;
    return 0;
}
#pragma code_seg()
