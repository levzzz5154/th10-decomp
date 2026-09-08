#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x004521D6..0x004521DB: D3DXLoadSurfaceFromSurface
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_D3DXLoadSurfaceFromSurface_004521d6() {
    __asm {
    L_004521d6:
        jmp dword ptr [data_004662c0]
    }
}
