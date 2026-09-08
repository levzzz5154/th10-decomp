#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0045FA9D..0x0045FBF5: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_0045fa9d() {
    __asm {
    L_0045fa9d:
        push 10h
    L_0045fa9f:
        push 46C8C8h
    L_0045faa4:
        call asm_SEH_prolog_00454bbc
    L_0045faa9:
        mov ebx,dword ptr [ebp+8]
    L_0045faac:
        cmp ebx,dword ptr [data_004991e4]
    L_0045fab2:
        jae asm_target_0045fb3d
    L_0045fab8:
        mov eax,ebx
    L_0045faba:
        sar eax,5
    L_0045fabd:
        lea edi,[eax*4+499200h]
    L_0045fac4:
        mov eax,ebx
    L_0045fac6:
        and eax,1Fh
    L_0045fac9:
        lea esi,[eax+eax*8]
    L_0045facc:
        shl esi,2
    L_0045facf:
        mov eax,dword ptr [edi]
    L_0045fad1:
        test byte ptr [eax+esi+4],1
    L_0045fad6:
        je short L_0045fb3d
    L_0045fad8:
        push ebx
    L_0045fad9:
        call asm_lock_fhandle_0045f715
    L_0045fade:
        pop ecx
    L_0045fadf:
        and dword ptr [ebp-4],0
    L_0045fae3:
        mov eax,dword ptr [edi]
    L_0045fae5:
        test byte ptr [eax+esi+4],1
    L_0045faea:
        je short L_0045fb06
    L_0045faec:
        push dword ptr [ebp+14h]
    L_0045faef:
        push dword ptr [ebp+10h]
    L_0045faf2:
        push dword ptr [ebp+0Ch]
    L_0045faf5:
        push ebx
    L_0045faf6:
        call asm_lseeki64_lk_0045fa1a
    L_0045fafb:
        add esp,10h
    L_0045fafe:
        mov dword ptr [ebp-20h],eax
    L_0045fb01:
        mov dword ptr [ebp-1Ch],edx
    L_0045fb04:
        jmp short L_0045fb21
    L_0045fb06:
        call asm_FUN_00456af2_00456af2
    L_0045fb0b:
        mov dword ptr [eax],9
    L_0045fb11:
        call asm_FUN_00456afb_00456afb
    L_0045fb16:
        and dword ptr [eax],0
    L_0045fb19:
        or dword ptr [ebp-20h],0FFFFFFFFh
    L_0045fb1d:
        or dword ptr [ebp-1Ch],0FFFFFFFFh
    L_0045fb21:
        or dword ptr [ebp-4],0FFFFFFFFh
    L_0045fb25:
        call asm_target_0045fb35
    L_0045fb2a:
        mov eax,dword ptr [ebp-20h]
    L_0045fb2d:
        mov edx,dword ptr [ebp-1Ch]
    L_0045fb30:
        jmp short L_0045fb55
    L_0045fb32:
        mov ebx,dword ptr [ebp+8]
    L_0045fb35:
        push ebx
    L_0045fb36:
        call asm_FUN_0045f7b5_0045f7b5
    L_0045fb3b:
        pop ecx
    L_0045fb3c:
        ret
    L_0045fb3d:
        call asm_FUN_00456af2_00456af2
    L_0045fb42:
        mov dword ptr [eax],9
    L_0045fb48:
        call asm_FUN_00456afb_00456afb
    L_0045fb4d:
        and dword ptr [eax],0
    L_0045fb50:
        or edx,0FFFFFFFFh
    L_0045fb53:
        mov eax,edx
    L_0045fb55:
        call asm_SEH_epilog_00454bf7
    L_0045fb5a:
        ret
    L_0045fb5b:
        push 10h
    L_0045fb5d:
        push 46C8D8h
    L_0045fb62:
        call asm_SEH_prolog_00454bbc
    L_0045fb67:
        xor ebx,ebx
    L_0045fb69:
        mov dword ptr [ebp-1Ch],ebx
    L_0045fb6c:
        push 1
    L_0045fb6e:
        call asm_lock_00453c0c
    L_0045fb73:
        pop ecx
    L_0045fb74:
        mov dword ptr [ebp-4],ebx
    L_0045fb77:
        push 3
    L_0045fb79:
        pop edi
    L_0045fb7a:
        mov dword ptr [ebp-20h],edi
    L_0045fb7d:
        cmp edi,dword ptr [data_004991e0]
    L_0045fb83:
        jge short L_0045fbdb
    L_0045fb85:
        mov esi,edi
    L_0045fb87:
        shl esi,2
    L_0045fb8a:
        mov eax,dword ptr [data_004981d4]
    L_0045fb8f:
        mov eax,dword ptr [esi+eax]
    L_0045fb92:
        cmp eax,ebx
    L_0045fb94:
        je short L_0045fbd8
    L_0045fb96:
        test byte ptr [eax+0Ch],83h
    L_0045fb9a:
        je short L_0045fbab
    L_0045fb9c:
        push eax
    L_0045fb9d:
        call asm_unassigned_00461458
    L_0045fba2:
        pop ecx
    L_0045fba3:
        cmp eax,0FFFFFFFFh
    L_0045fba6:
        je short L_0045fbab
    L_0045fba8:
        inc dword ptr [ebp-1Ch]
    L_0045fbab:
        cmp edi,14h
    L_0045fbae:
        jl short L_0045fbd8
    L_0045fbb0:
        mov eax,dword ptr [data_004981d4]
    L_0045fbb5:
        mov eax,dword ptr [esi+eax]
    L_0045fbb8:
        add eax,20h
    L_0045fbbb:
        push eax
    L_0045fbbc:
        call dword ptr [data_004660bc]
    L_0045fbc2:
        mov eax,dword ptr [data_004981d4]
    L_0045fbc7:
        push dword ptr [esi+eax]
    L_0045fbca:
        call asm_free_00452422
    L_0045fbcf:
        pop ecx
    L_0045fbd0:
        mov eax,dword ptr [data_004981d4]
    L_0045fbd5:
        mov dword ptr [esi+eax],ebx
    L_0045fbd8:
        inc edi
    L_0045fbd9:
        jmp short L_0045fb7a
    L_0045fbdb:
        or dword ptr [ebp-4],0FFFFFFFFh
    L_0045fbdf:
        call asm_target_0045fbed
    L_0045fbe4:
        mov eax,dword ptr [ebp-1Ch]
    L_0045fbe7:
        call asm_SEH_epilog_00454bf7
    L_0045fbec:
        ret
    L_0045fbed:
        push 1
    L_0045fbef:
        call asm_FUN_00453b3f_00453b3f
    L_0045fbf4:
        pop ecx
    L_0045fbf5:
        ret
    }
}
