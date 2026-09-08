#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x004521CA..0x004521CF: D3DXCreateTextureFromFileInMemoryEx
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_D3DXCreateTextureFromFileInMemoryEx_004521ca() {
    __asm {
    L_004521ca:
        jmp dword ptr [data_004662c8]
    }
}
