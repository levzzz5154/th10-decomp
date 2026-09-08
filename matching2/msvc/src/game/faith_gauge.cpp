#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00418930..0x004189D5: FaithGauge_AddRetail
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FaithGauge_AddRetail_00418930() {
    __asm {
    L_00418930:
        push ebp
    L_00418931:
        mov ebp,dword ptr [esp+8]
    L_00418935:
        push esi
    L_00418936:
        mov esi,eax
    L_00418938:
        mov ax,word ptr [esi+8]
    L_0041893c:
        cmp ax,64h
    L_00418940:
        jl short L_00418949
    L_00418942:
        pop esi
    L_00418943:
        xor eax,eax
    L_00418945:
        pop ebp
    L_00418946:
        ret 4
    L_00418949:
        add eax,ebp
    L_0041894b:
        cmp ax,64h
    L_0041894f:
        mov word ptr [esi+8],ax
    L_00418953:
        jle short L_0041899b
    L_00418955:
        mov edx,dword ptr [data_00491c10]
    L_0041895b:
        push ebx
    L_0041895c:
        push edi
    L_0041895d:
        mov edi,dword ptr [data_0047770c]
    L_00418963:
        mov word ptr [esi+8],64h
    L_00418969:
        mov eax,dword ptr [edi+9E18h]
    L_0041896f:
        lea ebx,[edi+9E18h]
    L_00418975:
        push eax
    L_00418976:
        call asm_AnimationManager_SetFlag_004492a0
    L_0041897b:
        push 0Fh
    L_0041897d:
        mov dword ptr [ebx],0
    L_00418983:
        mov ecx,dword ptr [edi+9EC8h]
    L_00418989:
        push 49h
    L_0041898b:
        push ecx
    L_0041898c:
        lea edi,[esp+20h]
    L_00418990:
        call asm_AnimationManager_CreatePrimaryBack_00448d00
    L_00418995:
        mov edx,dword ptr [eax]
    L_00418997:
        pop edi
    L_00418998:
        mov dword ptr [ebx],edx
    L_0041899a:
        pop ebx
    L_0041899b:
        movsx esi,word ptr [esi+8]
    L_0041899f:
        movsx eax,bp
    L_004189a2:
        mov ecx,esi
    L_004189a4:
        sub ecx,eax
    L_004189a6:
        mov eax,66666667h
    L_004189ab:
        imul ecx
    L_004189ad:
        sar edx,3
    L_004189b0:
        mov ecx,edx
    L_004189b2:
        shr ecx,1Fh
    L_004189b5:
        add ecx,edx
    L_004189b7:
        mov eax,66666667h
    L_004189bc:
        imul esi
    L_004189be:
        sar edx,3
    L_004189c1:
        mov eax,edx
    L_004189c3:
        shr eax,1Fh
    L_004189c6:
        add eax,edx
    L_004189c8:
        xor edx,edx
    L_004189ca:
        cmp ecx,eax
    L_004189cc:
        setne dl
    L_004189cf:
        pop esi
    L_004189d0:
        pop ebp
    L_004189d1:
        mov eax,edx
    L_004189d3:
        ret 4
    }
}
