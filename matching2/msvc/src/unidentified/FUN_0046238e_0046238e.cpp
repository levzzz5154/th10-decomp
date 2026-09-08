#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0046238E..0x004623A9: FUN_0046238e
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0046238e_0046238e() {
    __asm {
    L_0046238e:
        push esi
    L_0046238f:
        mov esi,ecx
    L_00462391:
        call asm_FUN_00462371_00462371
    L_00462396:
        test byte ptr [esp+8],1
    L_0046239b:
        je short L_004623a4
    L_0046239d:
        push esi
    L_0046239e:
        call asm_free_004524a1
    L_004623a3:
        pop ecx
    L_004623a4:
        mov eax,esi
    L_004623a6:
        pop esi
    L_004623a7:
        ret 4
    }
}
