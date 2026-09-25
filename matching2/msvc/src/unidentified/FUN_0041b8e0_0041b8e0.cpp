#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0041B8E0..0x0041B8F7: FUN_0041b8e0
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0041b8e0_0041b8e0() {
    __asm {
    L_0041b8e0:
        push ebx
    L_0041b8e1:
        push ebp
    L_0041b8e2:
        push esi
    L_0041b8e3:
        push edi
    L_0041b8e4:
        mov edi,eax
    L_0041b8e6:
        add edi,14h
    L_0041b8e9:
        lea esi,[edi+338h]
    L_0041b8ef:
        mov ebp,896h
    L_0041b8f4:
        mov bl,0FFh
    L_0041b8f6:
        TH10_REL8(0xeb, 0x0041b8f6, VA_asm_FUN_0041b8e0_part_0041b900)
        _emit 0x8d
        _emit 0xa4
        _emit 0x24
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x90

    L_0041b900:
        mov eax,dword ptr [esi+0A4h]
    L_0041b906:
        test eax,eax
    L_0041b908:
        je asm_target_0041b9dc
    L_0041b90e:
        fld dword ptr [esi+74h]
    L_0041b911:
        fadd dword ptr [data_00470b4c]
    L_0041b917:
        fstp dword ptr [esi-4]
    L_0041b91a:
        fld dword ptr [esi+78h]
    L_0041b91d:
        fadd dword ptr [data_00470b48]
    L_0041b923:
        fstp dword ptr [esi]
    L_0041b925:
        mov eax,dword ptr [esi+7Ch]
    L_0041b928:
        mov dword ptr [esi+4],eax
    L_0041b92b:
        fld dword ptr [esi]
    L_0041b92d:
        fcomp dword ptr [data_00470bd0]
    L_0041b933:
        fnstsw ax
    L_0041b935:
        test ah,5
    L_0041b938:
        jp short L_0041b99f
    L_0041b93a:
        fld dword ptr [esi]
    L_0041b93c:
        mov dword ptr [esi],41C00000h
    L_0041b942:
        fsub dword ptr [data_00470bd0]
    L_0041b948:
        fcom dword ptr [data_00470bcc]
    L_0041b94e:
        fnstsw ax
    L_0041b950:
        test ah,1
    L_0041b953:
        jne short L_0041b95c
    L_0041b955:
        fstp st(0)
    L_0041b957:
        mov byte ptr [esi-39h],bl
    L_0041b95a:
        jmp short L_0041b970
    L_0041b95c:
        fmul dword ptr [data_00470d20]
    L_0041b962:
        fmul dword ptr [data_00470bf8]
    L_0041b968:
        call asm_FUN_00463b2c_00463b2c
    L_0041b96d:
        mov byte ptr [esi-39h],al
    L_0041b970:
        mov eax,dword ptr [esi+0ACh]
    L_0041b976:
        movsx ecx,word ptr [esi+4Ch]
    L_0041b97a:
        lea edx,[eax+161h]
    L_0041b980:
        cmp ecx,edx
    L_0041b982:
        je short L_0041b9cf
    L_0041b984:
        mov ecx,dword ptr [data_004776f0]
    L_0041b98a:
        mov ecx,dword ptr [ecx+3E0B50h]
    L_0041b990:
        lea edx,[eax+160h]
    L_0041b996:
        mov eax,edi
    L_0041b998:
        call asm_AnimationObject_ConfigureFromResource_0043e5a0
    L_0041b99d:
        jmp short L_0041b9cf
    L_0041b99f:
        mov eax,dword ptr [esi+0ACh]
    L_0041b9a5:
        movsx edx,word ptr [esi+4Ch]
    L_0041b9a9:
        lea ecx,[eax+158h]
    L_0041b9af:
        cmp edx,ecx
    L_0041b9b1:
        je short L_0041b9cf
    L_0041b9b3:
        mov ecx,dword ptr [data_004776f0]
    L_0041b9b9:
        mov ecx,dword ptr [ecx+3E0B50h]
    L_0041b9bf:
        lea edx,[eax+157h]
    L_0041b9c5:
        mov eax,edi
    L_0041b9c7:
        call asm_AnimationObject_ConfigureFromResource_0043e5a0
    L_0041b9cc:
        mov byte ptr [esi-39h],bl
    L_0041b9cf:
        mov ecx,dword ptr [data_00491c10]
    L_0041b9d5:
        mov eax,edi
    L_0041b9d7:
        call asm_FUN_004451c0_004451c0
    L_0041b9dc:
        add edi,3F0h
    L_0041b9e2:
        add esi,3F0h
    L_0041b9e8:
        dec ebp
    L_0041b9e9:
        jne asm_FUN_0041b8e0_part_0041b900
    L_0041b9ef:
        pop edi
    L_0041b9f0:
        pop esi
    L_0041b9f1:
        pop ebp
    L_0041b9f2:
        mov eax,1
    L_0041b9f7:
        pop ebx
    L_0041b9f8:
        ret
    }
}
