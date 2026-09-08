#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00436940..0x00436960: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00436940() {
    __asm {
    L_00436940:
        mov eax,edx
    L_00436942:
        push esi
    L_00436943:
        lea esi,[eax+1]
    L_00436946:
        mov cl,byte ptr [eax]
    L_00436948:
        inc eax
    L_00436949:
        test cl,cl
    L_0043694b:
        jne short L_00436946
    L_0043694d:
        mov ecx,dword ptr [esp+8]
    L_00436951:
        sub eax,esi
    L_00436953:
        push eax
    L_00436954:
        push edx
    L_00436955:
        add ecx,0Ch
    L_00436958:
        call asm_AssignRange_LegacyString_00438420
    L_0043695d:
        pop esi
    L_0043695e:
        ret 4
    }
}
