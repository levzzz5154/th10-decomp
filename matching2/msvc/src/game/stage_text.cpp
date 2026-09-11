#include "asm_encoding.hpp"
#include "asm_symbols.hpp"



// 0x00434A80..0x00434B4D: ?StageText_Initialize@@
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_StageText_Initialize_00434a80() {
    __asm {
    L_00434a80:
        push esi
    L_00434a81:
        mov esi,dword ptr [esp+8]
    L_00434a85:
        mov dword ptr [eax+0B4h],esi
    L_00434a8b:
        push edi
    L_00434a8c:
        mov edi,dword ptr [data_00491c14]
    L_00434a92:
        lea esi,[eax+88h]
    L_00434a98:
        mov dword ptr [esi],edi
    L_00434a9a:
        mov edi,dword ptr [data_00491c18]
    L_00434aa0:
        mov dword ptr [esi+4],edi
    L_00434aa3:
        mov edi,dword ptr [data_00491c1c]
    L_00434aa9:
        mov dword ptr [esi+8],edi
    L_00434aac:
        mov edi,dword ptr [data_00491c14]
    L_00434ab2:
        lea esi,[eax+94h]
    L_00434ab8:
        mov dword ptr [esi],edi
    L_00434aba:
        mov edi,dword ptr [data_00491c18]
    L_00434ac0:
        mov dword ptr [esi+4],edi
    L_00434ac3:
        mov edi,dword ptr [data_00491c1c]
    L_00434ac9:
        mov dword ptr [esi+8],edi
    L_00434acc:
        movzx esi,byte ptr [esp+10h]
    L_00434ad1:
        mov dword ptr [eax+0B8h],esi
    L_00434ad7:
        mov edi,dword ptr [edx]
    L_00434ad9:
        lea esi,[eax+70h]
    L_00434adc:
        mov dword ptr [esi],edi
    L_00434ade:
        mov edi,dword ptr [edx+4]
    L_00434ae1:
        mov dword ptr [esi+4],edi
    L_00434ae4:
        mov edx,dword ptr [edx+8]
    L_00434ae7:
        mov dword ptr [esi+8],edx
    L_00434aea:
        mov esi,dword ptr [ecx]
    L_00434aec:
        lea edx,[eax+7Ch]
    L_00434aef:
        mov dword ptr [edx],esi
    L_00434af1:
        mov esi,dword ptr [ecx+4]
    L_00434af4:
        mov dword ptr [edx+4],esi
    L_00434af7:
        mov ecx,dword ptr [ecx+8]
    L_00434afa:
        mov dword ptr [edx+8],ecx
    L_00434afd:
        mov ecx,dword ptr [eax+0B0h]
    L_00434b03:
        xor edx,edx
    L_00434b05:
        test cl,1
    L_00434b08:
        pop edi
    L_00434b09:
        pop esi
    L_00434b0a:
        jne short L_00434b35
    L_00434b0c:
        or ecx,1
    L_00434b0f:
        mov dword ptr [eax+0A4h],edx
    L_00434b15:
        mov dword ptr [eax+0A0h],0FFF0BDC1h
    L_00434b1f:
        mov dword ptr [eax+0A8h],edx
    L_00434b25:
        mov dword ptr [eax+0ACh],476F78h
    L_00434b2f:
        mov dword ptr [eax+0B0h],ecx
    L_00434b35:
        mov dword ptr [eax+0A4h],edx
    L_00434b3b:
        mov dword ptr [eax+0A8h],edx
    L_00434b41:
        mov dword ptr [eax+0A0h],0FFFFFFFFh
    L_00434b4b:
        ret 8
    }
}
