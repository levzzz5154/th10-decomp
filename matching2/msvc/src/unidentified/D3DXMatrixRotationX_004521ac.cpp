#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x004521AC..0x004521B1: D3DXMatrixRotationX
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_D3DXMatrixRotationX_004521ac() {
    __asm {
    L_004521ac:
        jmp dword ptr [data_004662dc]
    }
}
