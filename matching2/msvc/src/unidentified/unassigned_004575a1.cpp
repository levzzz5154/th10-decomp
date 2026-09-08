#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x004575A1..0x004575BE: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_004575a1() {
    __asm {
    L_004575a1:
        push esi
    L_004575a2:
        mov esi,eax
    L_004575a4:
        xor eax,eax
    L_004575a6:
        jmp short L_004575b7
    L_004575a8:
        test eax,eax
    L_004575aa:
        jne short L_004575bd
    L_004575ac:
        mov ecx,dword ptr [esi]
    L_004575ae:
        test ecx,ecx
    L_004575b0:
        je short L_004575b4
    L_004575b2:
        call ecx
    L_004575b4:
        add esi,4
    L_004575b7:
        cmp esi,dword ptr [esp+8]
    L_004575bb:
        jb short L_004575a8
    L_004575bd:
        pop esi
    L_004575be:
        ret
    }
}
