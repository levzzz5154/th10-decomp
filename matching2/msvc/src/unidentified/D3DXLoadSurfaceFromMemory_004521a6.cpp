#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x004521A6..0x004521AB: D3DXLoadSurfaceFromMemory
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_D3DXLoadSurfaceFromMemory_004521a6() {
    __asm {
    L_004521a6:
        jmp dword ptr [data_004662e0]
    }
}
