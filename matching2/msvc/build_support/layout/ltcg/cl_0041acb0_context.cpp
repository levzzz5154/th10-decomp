// Compiler context only; never selected as recovered game code.
#include "../../../src/unreferenced/unassigned_41acb0.cpp"

inline void* operator new(unsigned int, void* place) { return place; }

#pragma code_seg(".text$03context")
int __stdcall EffectManagerContext_0041acb0(EffectManager** managers, int count) {
    for (int i = 0; i < count; ++i)
        new (managers[i]) EffectManager;
    return 0;
}
#pragma code_seg()
