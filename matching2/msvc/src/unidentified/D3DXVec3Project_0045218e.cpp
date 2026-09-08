#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0045218E..0x00452193: D3DXVec3Project
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_D3DXVec3Project_0045218e() {
    __asm {
    L_0045218e:
        jmp dword ptr [data_004662f0]
    }
}
