// Compiler context only; never selected as recovered game code.
#include "../../src/unidentified/unassigned_004658f0.cpp"
extern "C" void __cdecl InitConfigAnchor_00418c40(int reserved, void* config);
#pragma code_seg(".text$01anchor")
__declspec(noinline) void __stdcall Init_00421f00(void* object) {
    unsigned char* p = (unsigned char*)object;
    InitConfigAnchor_00418c40(0, p + 0x120);
    *(unsigned int*)(p + 0x630) = 0;
    *(unsigned int*)(p + 0x634) = 0;
    *(unsigned int*)(p + 0x638) = 0;
    *(unsigned int*)(p + 0x63c) = 0;
    *(unsigned int*)(p + 0x62c) = 0x4703E4;
    unsigned int* d = (unsigned int*)p;
    for (int i = 0; i < 0x1e1; ++i) d[i] = 0;
    *(unsigned int*)(p + 0x3cc) |= 0x140;
}
#pragma code_seg()

#pragma code_seg(".text$05context")
int __stdcall StartContext_004658f0(int count) {
    int total = 0;
    while (count--) { StartThread_004658f0(); total += count; }
    return total;
}
#pragma code_seg()
