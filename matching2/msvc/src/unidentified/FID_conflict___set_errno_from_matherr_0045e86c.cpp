#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0045E86C..0x0045E893: FID_conflict:__set_errno_from_matherr
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FID_conflict___set_errno_from_matherr_0045e86c() {
    __asm {
    L_0045e86c:
        mov eax,dword ptr [esp+4]
    L_0045e870:
        cmp eax,1
    L_0045e873:
        je short L_0045e888
    L_0045e875:
        jle short L_0045e893
    L_0045e877:
        cmp eax,3
    L_0045e87a:
        jg short L_0045e893
    L_0045e87c:
        call asm_FUN_00456af2_00456af2
    L_0045e881:
        mov dword ptr [eax],22h
    L_0045e887:
        ret
    L_0045e888:
        call asm_FUN_00456af2_00456af2
    L_0045e88d:
        mov dword ptr [eax],21h
    L_0045e893:
        ret
    }
}
