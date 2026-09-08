#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x004269D0..0x00426CEB: FUN_004269d0
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_004269d0_004269d0() {
    __asm {
    L_004269d0:
        push ecx
    L_004269d1:
        push ebx
    L_004269d2:
        push ebp
    L_004269d3:
        push esi
    L_004269d4:
        mov esi,dword ptr [data_00474c4c]
    L_004269da:
        push edi
    L_004269db:
        lea edi,[esi-1388h]
    L_004269e1:
        mov eax,55555555h
    L_004269e6:
        imul edi
    L_004269e8:
        sub edx,edi
    L_004269ea:
        sar edx,1
    L_004269ec:
        mov ecx,dword ptr [data_00474c70]
    L_004269f2:
        mov eax,edx
    L_004269f4:
        shr eax,1Fh
    L_004269f7:
        add eax,edx
    L_004269f9:
        mov ebp,dword ptr [esp+18h]
    L_004269fd:
        lea edx,[eax+eax*4]
    L_00426a00:
        shl edx,1
    L_00426a02:
        mov eax,66666667h
    L_00426a07:
        imul edx
    L_00426a09:
        sar edx,2
    L_00426a0c:
        mov eax,edx
    L_00426a0e:
        shr eax,1Fh
    L_00426a11:
        add eax,edx
    L_00426a13:
        add esi,eax
    L_00426a15:
        dec ecx
    L_00426a16:
        cmp esi,1388h
    L_00426a1c:
        mov dword ptr [data_00474c70],ecx
    L_00426a22:
        mov dword ptr [data_00474c4c],esi
    L_00426a28:
        jge short L_00426a34
    L_00426a2a:
        mov dword ptr [data_00474c4c],1388h
    L_00426a34:
        xor edi,edi
    L_00426a36:
        cmp ecx,edi
    L_00426a38:
        jl short L_00426a44
    L_00426a3a:
        mov eax,dword ptr [data_0047770c]
    L_00426a3f:
        call asm_Animation_SetActiveCount_00413790
    L_00426a44:
        mov dword ptr [ebp+458h],2
    L_00426a4e:
        mov eax,dword ptr [ebp+484h]
    L_00426a54:
        test al,1
    L_00426a56:
        mov edx,0FFF0BDC1h
    L_00426a5b:
        mov ecx,476F78h
    L_00426a60:
        jne short L_00426a83
    L_00426a62:
        or eax,1
    L_00426a65:
        mov dword ptr [ebp+478h],edi
    L_00426a6b:
        mov dword ptr [ebp+474h],edx
    L_00426a71:
        mov dword ptr [ebp+47Ch],edi
    L_00426a77:
        mov dword ptr [ebp+480h],ecx
    L_00426a7d:
        mov dword ptr [ebp+484h],eax
    L_00426a83:
        mov dword ptr [ebp+478h],edi
    L_00426a89:
        mov dword ptr [ebp+47Ch],edi
    L_00426a8f:
        mov dword ptr [ebp+474h],0FFFFFFFFh
    L_00426a99:
        mov eax,dword ptr [ebp+431Ch]
    L_00426a9f:
        test al,1
    L_00426aa1:
        jne short L_00426ac4
    L_00426aa3:
        or eax,1
    L_00426aa6:
        mov dword ptr [ebp+4310h],edi
    L_00426aac:
        mov dword ptr [ebp+430Ch],edx
    L_00426ab2:
        mov dword ptr [ebp+4314h],edi
    L_00426ab8:
        mov dword ptr [ebp+4318h],ecx
    L_00426abe:
        mov dword ptr [ebp+431Ch],eax
    L_00426ac4:
        mov dword ptr [ebp+4310h],0B4h
    L_00426ace:
        mov dword ptr [ebp+4314h],43340000h
    L_00426ad8:
        mov dword ptr [ebp+430Ch],0B3h
    L_00426ae2:
        mov ecx,dword ptr [ebp+10h]
    L_00426ae5:
        lea eax,[ebp+14h]
    L_00426ae8:
        xor ebx,ebx
    L_00426aea:
        call asm_AnimationObject_LoadScript_0043e710
    L_00426aef:
        mov esi,dword ptr [data_00491c10]
    L_00426af5:
        lea ebx,[ebp+3308h]
    L_00426afb:
        mov dword ptr [esp+18h],ebx
    L_00426aff:
        mov dword ptr [esp+10h],4
    L_00426b07:
        mov ecx,dword ptr [ebx]
    L_00426b09:
        cmp ecx,edi
    L_00426b0b:
        mov dword ptr [ebx-68h],edi
    L_00426b0e:
        je short L_00426b44
    L_00426b10:
        mov eax,dword ptr [esi+72DAD4h]
    L_00426b16:
        cmp eax,edi
    L_00426b18:
        je short L_00426b2d
    L_00426b1a:
        lea ebx,[ebx+force_disp32_zero]
    L_00426b20:
        mov edx,dword ptr [eax]
    L_00426b22:
        cmp dword ptr [edx],ecx
    L_00426b24:
        je short L_00426b86
    L_00426b26:
        mov eax,dword ptr [eax+4]
    L_00426b29:
        cmp eax,edi
    L_00426b2b:
        jne short L_00426b20
    L_00426b2d:
        mov eax,dword ptr [esi+72DADCh]
    L_00426b33:
        cmp eax,edi
    L_00426b35:
        je short L_00426b44
    L_00426b37:
        mov edx,dword ptr [eax]
    L_00426b39:
        cmp dword ptr [edx],ecx
    L_00426b3b:
        je short L_00426b86
    L_00426b3d:
        mov eax,dword ptr [eax+4]
    L_00426b40:
        cmp eax,edi
    L_00426b42:
        jne short L_00426b37
    L_00426b44:
        mov edx,1
    L_00426b49:
        mov ecx,dword ptr [ebx+4]
    L_00426b4c:
        cmp ecx,edi
    L_00426b4e:
        je asm_target_00426be0
    L_00426b54:
        mov eax,dword ptr [esi+72DAD4h]
    L_00426b5a:
        cmp eax,edi
    L_00426b5c:
        je short L_00426b6d
    L_00426b5e:
        mov edi,edi
    L_00426b60:
        mov ebx,dword ptr [eax]
    L_00426b62:
        cmp dword ptr [ebx],ecx
    L_00426b64:
        je short L_00426bb6
    L_00426b66:
        mov eax,dword ptr [eax+4]
    L_00426b69:
        cmp eax,edi
    L_00426b6b:
        jne short L_00426b60
    L_00426b6d:
        mov eax,dword ptr [esi+72DADCh]
    L_00426b73:
        cmp eax,edi
    L_00426b75:
        je short L_00426be0
    L_00426b77:
        mov ebx,dword ptr [eax]
    L_00426b79:
        cmp dword ptr [ebx],ecx
    L_00426b7b:
        je short L_00426bb6
    L_00426b7d:
        mov eax,dword ptr [eax+4]
    L_00426b80:
        cmp eax,edi
    L_00426b82:
        jne short L_00426b77
    L_00426b84:
        jmp short L_00426be0
    L_00426b86:
        mov eax,dword ptr [eax]
    L_00426b88:
        cmp eax,edi
    L_00426b8a:
        je short L_00426b44
    L_00426b8c:
        cmp dword ptr [eax+18h],edi
    L_00426b8f:
        mov edx,1
    L_00426b94:
        mov word ptr [eax+304h],dx
    L_00426b9b:
        jne short L_00426b49
    L_00426b9d:
        mov eax,dword ptr [eax+14h]
    L_00426ba0:
        cmp eax,edi
    L_00426ba2:
        je short L_00426b49
    L_00426ba4:
        mov ecx,dword ptr [eax]
    L_00426ba6:
        mov word ptr [ecx+304h],dx
    L_00426bad:
        mov eax,dword ptr [eax+4]
    L_00426bb0:
        cmp eax,edi
    L_00426bb2:
        jne short L_00426ba4
    L_00426bb4:
        jmp short L_00426b49
    L_00426bb6:
        mov eax,dword ptr [eax]
    L_00426bb8:
        cmp eax,edi
    L_00426bba:
        je short L_00426be0
    L_00426bbc:
        cmp dword ptr [eax+18h],edi
    L_00426bbf:
        mov word ptr [eax+304h],dx
    L_00426bc6:
        jne short L_00426be0
    L_00426bc8:
        mov eax,dword ptr [eax+14h]
    L_00426bcb:
        cmp eax,edi
    L_00426bcd:
        je short L_00426be0
    L_00426bcf:
        nop
    L_00426bd0:
        mov ecx,dword ptr [eax]
    L_00426bd2:
        mov word ptr [ecx+304h],dx
    L_00426bd9:
        mov eax,dword ptr [eax+4]
    L_00426bdc:
        cmp eax,edi
    L_00426bde:
        jne short L_00426bd0
    L_00426be0:
        mov ebx,dword ptr [esp+18h]
    L_00426be4:
        mov eax,dword ptr [esp+10h]
    L_00426be8:
        add ebx,98h
    L_00426bee:
        dec eax
    L_00426bef:
        mov dword ptr [esp+18h],ebx
    L_00426bf3:
        mov dword ptr [esp+10h],eax
    L_00426bf7:
        jne asm_target_00426b07
    L_00426bfd:
        mov edx,dword ptr [data_00477838]
    L_00426c03:
        mov dword ptr [ebp+3500h],edi
    L_00426c09:
        cmp dword ptr [edx+10h],1
    L_00426c0d:
        je short L_00426c26
    L_00426c0f:
        mov esi,dword ptr [data_00477814]
    L_00426c15:
        add ebp,3C0h
    L_00426c1b:
        push ebp
    L_00426c1c:
        push 46E360h
    L_00426c21:
        call asm_StageTip_CreateUrgent_00424650
    L_00426c26:
        mov eax,dword ptr [data_004776f4]
    L_00426c2b:
        cmp dword ptr [eax+3738h],3Ch
    L_00426c32:
        jl short L_00426caf
    L_00426c34:
        mov dword ptr [eax+3790h],edi
    L_00426c3a:
        mov edi,dword ptr [eax+378Ch]
    L_00426c40:
        mov ecx,0FFFFFFFDh
    L_00426c45:
        and edi,ecx
    L_00426c47:
        mov dword ptr [eax+378Ch],edi
    L_00426c4d:
        mov esi,dword ptr [eax+0AD4h]
    L_00426c53:
        mov edx,dword ptr [eax+0E80h]
    L_00426c59:
        mov ebp,dword ptr [eax+15D8h]
    L_00426c5f:
        mov ebx,dword ptr [eax+1984h]
    L_00426c65:
        mov edi,dword ptr [eax+1D30h]
    L_00426c6b:
        and esi,ecx
    L_00426c6d:
        and edx,ecx
    L_00426c6f:
        mov dword ptr [eax+0AD4h],esi
    L_00426c75:
        mov esi,dword ptr [eax+20DCh]
    L_00426c7b:
        mov dword ptr [eax+0E80h],edx
    L_00426c81:
        mov edx,dword ptr [eax+2488h]
    L_00426c87:
        and ebp,ecx
    L_00426c89:
        and ebx,ecx
    L_00426c8b:
        and edi,ecx
    L_00426c8d:
        and esi,ecx
    L_00426c8f:
        and edx,ecx
    L_00426c91:
        mov dword ptr [eax+15D8h],ebp
    L_00426c97:
        mov dword ptr [eax+1984h],ebx
    L_00426c9d:
        mov dword ptr [eax+1D30h],edi
    L_00426ca3:
        mov dword ptr [eax+20DCh],esi
    L_00426ca9:
        mov dword ptr [eax+2488h],edx
    L_00426caf:
        mov eax,dword ptr [data_00474c98]
    L_00426cb4:
        pop edi
    L_00426cb5:
        pop esi
    L_00426cb6:
        sub eax,400h
    L_00426cbb:
        cmp eax,400h
    L_00426cc0:
        pop ebp
    L_00426cc1:
        mov dword ptr [data_00474c98],eax
    L_00426cc6:
        pop ebx
    L_00426cc7:
        jle short L_00426cd7
    L_00426cc9:
        mov dword ptr [data_00474c98],400h
    L_00426cd3:
        pop ecx
    L_00426cd4:
        ret 4
    L_00426cd7:
        cmp eax,0FFFFFC00h
    L_00426cdc:
        jge short L_00426ce8
    L_00426cde:
        mov dword ptr [data_00474c98],0FFFFFC00h
    L_00426ce8:
        pop ecx
    L_00426ce9:
        ret 4
    }
}
