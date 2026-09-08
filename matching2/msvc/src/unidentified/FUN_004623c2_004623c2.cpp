#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x004623C2..0x004623DD: FUN_004623c2
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_004623c2_004623c2() {
    __asm {
    L_004623c2:
        push esi
    L_004623c3:
        mov esi,ecx
    L_004623c5:
        call asm_FUN_004623de_004623de
    L_004623ca:
        test byte ptr [esp+8],1
    L_004623cf:
        je short L_004623d8
    L_004623d1:
        push esi
    L_004623d2:
        call asm_free_004524a1
    L_004623d7:
        pop ecx
    L_004623d8:
        mov eax,esi
    L_004623da:
        pop esi
    L_004623db:
        ret 4
    }
}
