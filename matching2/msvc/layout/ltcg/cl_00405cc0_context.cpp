// Compiler context only; never selected as recovered game code.
#include "../../src/unreferenced/unassigned_00405cc0.cpp"

inline void* operator new(unsigned int, void* place) { return place; }

#pragma code_seg(".text$03context")
int __stdcall BulletManagerContext_00405cc0(BulletManager_00405cc0** managers, int count) {
    for (int i = 0; i < count; ++i)
        new (managers[i]) BulletManager_00405cc0;
    return 0;
}
#pragma code_seg()
