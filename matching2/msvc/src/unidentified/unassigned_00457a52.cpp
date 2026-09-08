#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00457A52..0x00457A7B: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00457a52() {
    __asm {
    L_00457a52:
        cmp dword ptr [esp+4],0FFFFFFFFh
    L_00457a57:
        je short L_00457a5e
    L_00457a59:
        jmp asm_FID_conflict__ungetc_0045e204
    L_00457a5e:
        ret
    L_00457a5f:
        push edi
    L_00457a60:
        mov edx,dword ptr [esp+8]
    L_00457a64:
        inc dword ptr [esi]
    L_00457a66:
        call asm_inc_00457a3c
    L_00457a6b:
        mov edi,eax
    L_00457a6d:
        push edi
    L_00457a6e:
        call asm_isspace_004568d7
    L_00457a73:
        test eax,eax
    L_00457a75:
        pop ecx
    L_00457a76:
        jne short L_00457a60
    L_00457a78:
        mov eax,edi
    L_00457a7a:
        pop edi
    L_00457a7b:
        ret
    }
}
