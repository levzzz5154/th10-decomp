#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0040C3A0..0x0040C3B1: FUN_0040c3a0
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0040c3a0_0040c3a0() {
    __asm {
    L_0040c3a0:
        mov eax,dword ptr [data_00477700]
    L_0040c3a5:
        push ebx
    L_0040c3a6:
        mov ebx,dword ptr [eax+18h]
    L_0040c3a9:
        call asm_StageBackground_RebindTextureRetail_0040c3c0
    L_0040c3ae:
        xor eax,eax
    L_0040c3b0:
        pop ebx
    L_0040c3b1:
        ret
    }
}
