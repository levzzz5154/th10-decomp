#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0045E0E4..0x0045E119: _getenv
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_getenv_0045e0e4() {
    __asm {
    L_0045e0e4:
        push 0Ch
    L_0045e0e6:
        push 46C598h
    L_0045e0eb:
        call asm_SEH_prolog_00454bbc
    L_0045e0f0:
        push 7
    L_0045e0f2:
        call asm_lock_00453c0c
    L_0045e0f7:
        pop ecx
    L_0045e0f8:
        and dword ptr [ebp-4],0
    L_0045e0fc:
        push dword ptr [ebp+8]
    L_0045e0ff:
        call asm_getenv_lk_0045e063
    L_0045e104:
        pop ecx
    L_0045e105:
        mov dword ptr [ebp-1Ch],eax
    L_0045e108:
        or dword ptr [ebp-4],0FFFFFFFFh
    L_0045e10c:
        call asm_FUN_0045e11a_0045e11a
    L_0045e111:
        mov eax,dword ptr [ebp-1Ch]
    L_0045e114:
        call asm_SEH_epilog_00454bf7
    L_0045e119:
        ret
    }
}
