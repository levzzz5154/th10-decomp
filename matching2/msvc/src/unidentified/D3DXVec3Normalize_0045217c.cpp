#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0045217C..0x00452181: D3DXVec3Normalize
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_D3DXVec3Normalize_0045217c() {
    __asm {
    L_0045217c:
        jmp dword ptr [data_004662bc]
    }
}
