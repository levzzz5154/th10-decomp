#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x004617E0..0x00461840: ___ascii_strnicmp
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_ascii_strnicmp_004617e0() {
    __asm {
    L_004617e0:
        push ebp
    L_004617e1:
        mov ebp,esp
    L_004617e3:
        push edi
    L_004617e4:
        push esi
    L_004617e5:
        push ebx
    L_004617e6:
        mov ecx,dword ptr [ebp+10h]
    L_004617e9:
        or ecx,ecx
    L_004617eb:
        je short L_0046183a
    L_004617ed:
        mov esi,dword ptr [ebp+8]
    L_004617f0:
        mov edi,dword ptr [ebp+0Ch]
    L_004617f3:
        mov bh,41h
    L_004617f5:
        mov bl,5Ah
    L_004617f7:
        mov dh,20h
    L_004617f9:
        TH10_NOP_LEA_ECX_DISP8()
    L_004617fc:
        mov ah,byte ptr [esi]
    L_004617fe:
        or ah,ah
    L_00461800:
        mov al,byte ptr [edi]
    L_00461802:
        je short L_0046182b
    L_00461804:
        or al,al
    L_00461806:
        je short L_0046182b
    L_00461808:
        add esi,1
    L_0046180b:
        add edi,1
    L_0046180e:
        TH10_CMP_R8_STORE(TH10_R8_AH, TH10_R8_BH)
    L_00461810:
        jb short L_00461818
    L_00461812:
        TH10_CMP_R8_STORE(TH10_R8_AH, TH10_R8_BL)
    L_00461814:
        ja short L_00461818
    L_00461816:
        add ah,dh
    L_00461818:
        TH10_CMP_R8_STORE(TH10_R8_AL, TH10_R8_BH)
    L_0046181a:
        jb short L_00461822
    L_0046181c:
        TH10_CMP_R8_STORE(TH10_R8_AL, TH10_R8_BL)
    L_0046181e:
        ja short L_00461822
    L_00461820:
        add al,dh
    L_00461822:
        TH10_CMP_R8_STORE(TH10_R8_AH, TH10_R8_AL)
    L_00461824:
        jne short L_00461831
    L_00461826:
        sub ecx,1
    L_00461829:
        jne short L_004617fc
    L_0046182b:
        xor ecx,ecx
    L_0046182d:
        TH10_CMP_R8_STORE(TH10_R8_AH, TH10_R8_AL)
    L_0046182f:
        je short L_0046183a
    L_00461831:
        mov ecx,0FFFFFFFFh
    L_00461836:
        jb short L_0046183a
    L_00461838:
        neg ecx
    L_0046183a:
        mov eax,ecx
    L_0046183c:
        pop ebx
    L_0046183d:
        pop esi
    L_0046183e:
        pop edi
    L_0046183f:
        leave
    L_00461840:
        ret
    }
}
