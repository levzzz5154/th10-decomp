#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0045CC10..0x0045CCC7: _memcmp
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_memcmp_0045cc10() {
    __asm {
    L_0045cc10:
        mov eax,dword ptr [esp+0Ch]
    L_0045cc14:
        test eax,eax
    L_0045cc16:
        je short L_0045cc62
    L_0045cc18:
        mov edx,dword ptr [esp+4]
    L_0045cc1c:
        push esi
    L_0045cc1d:
        push edi
    L_0045cc1e:
        mov esi,edx
    L_0045cc20:
        mov edi,dword ptr [esp+10h]
    L_0045cc24:
        or edx,edi
    L_0045cc26:
        and edx,3
    L_0045cc29:
        je short L_0045cc63
    L_0045cc2b:
        test eax,1
    L_0045cc30:
        je short L_0045cc43
    L_0045cc32:
        mov cl,byte ptr [esi]
    L_0045cc34:
        cmp cl,byte ptr [edi]
    L_0045cc36:
        jne short L_0045cc90
    L_0045cc38:
        add esi,1
    L_0045cc3b:
        add edi,1
    L_0045cc3e:
        sub eax,1
    L_0045cc41:
        je short L_0045cc60
    L_0045cc43:
        mov cl,byte ptr [esi]
    L_0045cc45:
        mov dl,byte ptr [edi]
    L_0045cc47:
        TH10_CMP_R8_STORE(TH10_R8_CL, TH10_R8_DL)
    L_0045cc49:
        jne short L_0045cc90
    L_0045cc4b:
        mov cl,byte ptr [esi+1]
    L_0045cc4e:
        mov dl,byte ptr [edi+1]
    L_0045cc51:
        TH10_CMP_R8_STORE(TH10_R8_CL, TH10_R8_DL)
    L_0045cc53:
        jne short L_0045cc90
    L_0045cc55:
        add edi,2
    L_0045cc58:
        add esi,2
    L_0045cc5b:
        sub eax,2
    L_0045cc5e:
        jne short L_0045cc43
    L_0045cc60:
        pop edi
    L_0045cc61:
        pop esi
    L_0045cc62:
        ret
    L_0045cc63:
        mov ecx,eax
    L_0045cc65:
        and eax,3
    L_0045cc68:
        shr ecx,2
    L_0045cc6b:
        je short L_0045cc98
    L_0045cc6d:
        repe cmpsd
    L_0045cc6f:
        je short L_0045cc98
    L_0045cc71:
        mov ecx,dword ptr [esi-4]
    L_0045cc74:
        mov edx,dword ptr [edi-4]
    L_0045cc77:
        TH10_CMP_R8_STORE(TH10_R8_CL, TH10_R8_DL)
    L_0045cc79:
        jne short L_0045cc8b
    L_0045cc7b:
        TH10_CMP_R8_STORE(TH10_R8_CH, TH10_R8_DH)
    L_0045cc7d:
        jne short L_0045cc8b
    L_0045cc7f:
        shr ecx,10h
    L_0045cc82:
        shr edx,10h
    L_0045cc85:
        TH10_CMP_R8_STORE(TH10_R8_CL, TH10_R8_DL)
    L_0045cc87:
        jne short L_0045cc8b
    L_0045cc89:
        TH10_CMP_R8_STORE(TH10_R8_CH, TH10_R8_DH)
    L_0045cc8b:
        mov eax,0
    L_0045cc90:
        sbb eax,eax
    L_0045cc92:
        pop edi
    L_0045cc93:
        sbb eax,0FFFFFFFFh
    L_0045cc96:
        pop esi
    L_0045cc97:
        ret
    L_0045cc98:
        test eax,eax
    L_0045cc9a:
        je short L_0045cc60
    L_0045cc9c:
        mov edx,dword ptr [esi]
    L_0045cc9e:
        mov ecx,dword ptr [edi]
    L_0045cca0:
        TH10_CMP_R8_STORE(TH10_R8_DL, TH10_R8_CL)
    L_0045cca2:
        jne short L_0045cc8b
    L_0045cca4:
        sub eax,1
    L_0045cca7:
        je short L_0045ccc5
    L_0045cca9:
        TH10_CMP_R8_STORE(TH10_R8_DH, TH10_R8_CH)
    L_0045ccab:
        jne short L_0045cc8b
    L_0045ccad:
        sub eax,1
    L_0045ccb0:
        je short L_0045ccc5
    L_0045ccb2:
        and ecx,0FF0000h
    L_0045ccb8:
        and edx,0FF0000h
    L_0045ccbe:
        cmp edx,ecx
    L_0045ccc0:
        jne short L_0045cc8b
    L_0045ccc2:
        sub eax,1
    L_0045ccc5:
        pop edi
    L_0045ccc6:
        pop esi
    L_0045ccc7:
        ret
    }
}
