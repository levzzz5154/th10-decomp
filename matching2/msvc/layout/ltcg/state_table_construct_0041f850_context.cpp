// Compiler context only; its bytes are not recovered game code.
#include "../../src/game/loading/recovery_initialize_state_table_0041f850.cpp"

#pragma code_seg(".text$03context")
inline void* operator new(unsigned int, void* where) { return where; }
int __stdcall Ctx(void** p, int n) {
    int r = 0;
    for (int i = 0; i < n; ++i) r += (int)new (p[i]) StateTable_0041f850;
    return r;
}
#pragma code_seg()
