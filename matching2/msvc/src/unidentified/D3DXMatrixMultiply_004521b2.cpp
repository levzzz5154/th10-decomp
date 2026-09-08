#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x004521B2..0x004521B7: D3DXMatrixMultiply
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_D3DXMatrixMultiply_004521b2() {
    __asm {
    L_004521b2:
        jmp dword ptr [data_004662d8]
    }
}
