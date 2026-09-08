#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00452182..0x00452187: D3DXMatrixTranslation
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_D3DXMatrixTranslation_00452182() {
    __asm {
    L_00452182:
        jmp dword ptr [data_004662f8]
    }
}
