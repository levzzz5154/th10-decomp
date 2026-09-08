#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0044A950..0x0044A9CE: FUN_0044a950
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0044a950_0044a950() {
    __asm {
    L_0044a950:
        push ecx
    L_0044a951:
        imul ecx,6Ah
    L_0044a954:
        add ecx,474E30h
    L_0044a95a:
        mov dx,word ptr [ecx]
    L_0044a95d:
        push esi
    L_0044a95e:
        push edi
    L_0044a95f:
        mov word ptr [ecx+2],dx
    L_0044a963:
        mov word ptr [ecx],ax
    L_0044a966:
        mov esi,1
    L_0044a96b:
        mov dword ptr [esp+8],eax
    L_0044a96f:
        mov word ptr [ecx+4],0
    L_0044a975:
        lea edx,[ecx+0Ah]
    L_0044a978:
        mov edi,10h
    L_0044a97d:
        TH10_NOP_LEA_ECX_DISP8()
    L_0044a980:
        test byte ptr [esp+8],1
    L_0044a985:
        je short L_0044a99b
    L_0044a987:
        inc word ptr [edx]
    L_0044a98a:
        cmp word ptr [edx],1Ah
    L_0044a98e:
        jb short L_0044a9a0
    L_0044a990:
        or word ptr [ecx+4],si
    L_0044a994:
        TH10_ADD_M16_IMM16(TH10_R32_EDX, 0xfff8)
    L_0044a999:
        jmp short L_0044a9a0
    L_0044a99b:
        mov word ptr [edx],0
    L_0044a9a0:
        shr word ptr [esp+8],1
    L_0044a9a5:
        add edx,2
    L_0044a9a8:
        shl esi,1
    L_0044a9aa:
        dec edi
    L_0044a9ab:
        jne short L_0044a980
    L_0044a9ad:
        xor esi,esi
    L_0044a9af:
        mov si,word ptr [ecx+2]
    L_0044a9b3:
        xor edx,edx
    L_0044a9b5:
        mov dx,word ptr [ecx]
    L_0044a9b8:
        xor si,dx
    L_0044a9bb:
        mov edi,esi
    L_0044a9bd:
        and edi,edx
    L_0044a9bf:
        not edx
    L_0044a9c1:
        mov word ptr [ecx+6],di
    L_0044a9c5:
        and edx,esi
    L_0044a9c7:
        pop edi
    L_0044a9c8:
        mov word ptr [ecx+8],dx
    L_0044a9cc:
        pop esi
    L_0044a9cd:
        pop ecx
    L_0044a9ce:
        ret
    }
}
