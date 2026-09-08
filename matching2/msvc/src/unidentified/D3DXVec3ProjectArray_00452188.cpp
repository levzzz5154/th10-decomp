#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00452188..0x0045218D: D3DXVec3ProjectArray
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_D3DXVec3ProjectArray_00452188() {
    __asm {
    L_00452188:
        jmp dword ptr [data_004662f4]
    }
}
