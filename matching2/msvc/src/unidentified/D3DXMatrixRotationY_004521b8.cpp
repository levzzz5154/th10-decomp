#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x004521B8..0x004521BD: D3DXMatrixRotationY
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_D3DXMatrixRotationY_004521b8() {
    __asm {
    L_004521b8:
        jmp dword ptr [data_004662d4]
    }
}
