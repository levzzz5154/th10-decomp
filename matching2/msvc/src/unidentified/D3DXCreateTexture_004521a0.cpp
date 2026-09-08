#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x004521A0..0x004521A5: D3DXCreateTexture
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_D3DXCreateTexture_004521a0() {
    __asm {
    L_004521a0:
        jmp dword ptr [data_004662e4]
    }
}
