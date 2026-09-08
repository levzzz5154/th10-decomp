#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00442390..0x00442395: FUN_00442390
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00442390_00442390() {
    __asm {
    L_00442390:
        mov ecx,dword ptr [eax]
    L_00442392:
        mov dword ptr [edx+8],ecx
    L_00442395:
        ret
    }
}
