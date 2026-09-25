#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00445880..0x00445898: FUN_00445880
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00445880_00445880() {
    __asm {
    L_00445880:
        mov eax,ecx
    L_00445882:
        mov ecx,dword ptr [eax+358h]
    L_00445888:
        push 21h
    L_0044588a:
        push ecx
    L_0044588b:
        mov ecx,dword ptr [data_00491c10]
    L_00445891:
        call asm_FUN_004450e0_004450e0
    L_00445896:
        xor eax,eax
    L_00445898:
        ret
    }
}
