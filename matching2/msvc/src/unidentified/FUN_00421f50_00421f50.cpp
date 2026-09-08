#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00421F50..0x00421F5B: FUN_00421f50
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00421f50_00421f50() {
    __asm {
    L_00421f50:
        mov eax,dword ptr [data_004776e0]
    L_00421f55:
        mov eax,dword ptr [eax+8998h]
    L_00421f5b:
        ret
    }
}
