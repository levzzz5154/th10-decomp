#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00418850..0x00418890: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00418850() {
    __asm {
    L_00418850:
        mov byte ptr [data_00497c38],0
    L_00418857:
        mov ecx,eax
    L_00418859:
        lea esp,[esp+force_disp32_zero]
    L_00418860:
        mov dl,byte ptr [eax]
    L_00418862:
        inc eax
    L_00418863:
        test dl,dl
    L_00418865:
        jne short L_00418860
    L_00418867:
        push esi
    L_00418868:
        push edi
    L_00418869:
        mov edi,497C38h
    L_0041886e:
        sub eax,ecx
    L_00418870:
        mov esi,ecx
    L_00418872:
        dec edi
    L_00418873:
        mov cl,byte ptr [edi+1]
    L_00418876:
        inc edi
    L_00418877:
        test cl,cl
    L_00418879:
        jne short L_00418873
    L_0041887b:
        mov ecx,eax
    L_0041887d:
        shr ecx,2
    L_00418880:
        rep movsd
    L_00418882:
        mov ecx,eax
    L_00418884:
        and ecx,3
    L_00418887:
        rep movsb
    L_00418889:
        pop edi
    L_0041888a:
        mov eax,497C38h
    L_0041888f:
        pop esi
    L_00418890:
        ret
    }
}
