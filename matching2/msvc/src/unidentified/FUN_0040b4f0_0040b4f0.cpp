#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0040B4F0..0x0040B4FA: FUN_0040b4f0
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0040b4f0_0040b4f0() {
    __asm {
    L_0040b4f0:
        push ebx
    L_0040b4f1:
        mov ebx,dword ptr [eax+18h]
    L_0040b4f4:
        call asm_StageBackground_RebindTextureRetail_0040c3c0
    L_0040b4f9:
        pop ebx
    L_0040b4fa:
        ret
    }
}
