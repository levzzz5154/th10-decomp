#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x004521BE..0x004521C3: D3DXMatrixRotationZ
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_D3DXMatrixRotationZ_004521be() {
    __asm {
    L_004521be:
        jmp dword ptr [data_004662d0]
    }
}
