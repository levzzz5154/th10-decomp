// Compiler context only; its bytes are not recovered game code.
#include "../../src/unidentified/FUN_0040a040_0040a040.cpp"

#pragma code_seg(".text$03context")
inline void* operator new(unsigned int, void* where) { return where; }
int __stdcall Ctx(void** p, int n) {
    int r = 0;
    for (int i = 0; i < n; ++i) r += (int)new (p[i]) CounterState_0040a040;
    return r;
}
#pragma code_seg()
