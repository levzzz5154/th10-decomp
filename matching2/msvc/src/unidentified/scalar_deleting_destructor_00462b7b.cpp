#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00462B7B..0x00462B96: `scalar_deleting_destructor'
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_scalar_deleting_destructor_00462b7b() {
    __asm {
    L_00462b7b:
        push esi
    L_00462b7c:
        mov esi,ecx
    L_00462b7e:
        call asm_type_info_00462b35
    L_00462b83:
        test byte ptr [esp+8],1
    L_00462b88:
        je short L_00462b91
    L_00462b8a:
        push esi
    L_00462b8b:
        call asm_free_004524a1
    L_00462b90:
        pop ecx
    L_00462b91:
        mov eax,esi
    L_00462b93:
        pop esi
    L_00462b94:
        ret 4
    }
}
