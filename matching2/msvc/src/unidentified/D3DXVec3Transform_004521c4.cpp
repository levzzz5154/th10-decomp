#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x004521C4..0x004521C9: D3DXVec3Transform
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_D3DXVec3Transform_004521c4() {
    __asm {
    L_004521c4:
        jmp dword ptr [data_004662cc]
    }
}
