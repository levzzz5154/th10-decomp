#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0045219A..0x0045219F: D3DXMatrixPerspectiveFovLH
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_D3DXMatrixPerspectiveFovLH_0045219a() {
    __asm {
    L_0045219a:
        jmp dword ptr [data_004662e8]
    }
}
