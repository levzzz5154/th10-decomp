#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00462B35..0x00462B71: ~type_info
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_type_info_00462b35() {
    __asm {
    L_00462b35:
        push 8
    L_00462b37:
        push 46CA58h
    L_00462b3c:
        call asm_SEH_prolog_00454bbc
    L_00462b41:
        mov esi,ecx
    L_00462b43:
        mov dword ptr [esi],46CA54h
    L_00462b49:
        push 0Eh
    L_00462b4b:
        call asm_lock_00453c0c
    L_00462b50:
        pop ecx
    L_00462b51:
        and dword ptr [ebp-4],0
    L_00462b55:
        mov esi,dword ptr [esi+4]
    L_00462b58:
        test esi,esi
    L_00462b5a:
        je short L_00462b63
    L_00462b5c:
        push esi
    L_00462b5d:
        call asm_free_00452422
    L_00462b62:
        pop ecx
    L_00462b63:
        or dword ptr [ebp-4],0FFFFFFFFh
    L_00462b67:
        call asm_FUN_00462b72_00462b72
    L_00462b6c:
        call asm_SEH_epilog_00454bf7
    L_00462b71:
        ret
    }
}
