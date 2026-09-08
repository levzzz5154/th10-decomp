#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00452194..0x00452199: D3DXMatrixLookAtLH
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_D3DXMatrixLookAtLH_00452194() {
    __asm {
    L_00452194:
        jmp dword ptr [data_004662ec]
    }
}
