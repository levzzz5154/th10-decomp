#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0041F990..0x0041FABA: FUN_0041f990
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0041f990_0041f990() {
    __asm {
    L_0041f990:
        push ecx
    L_0041f991:
        mov edx,dword ptr [data_00491c10]
    L_0041f997:
        push esi
    L_0041f998:
        mov esi,dword ptr [data_00477820]
    L_0041f99e:
        mov dword ptr [esp+4],ecx
    L_0041f9a2:
        push 46DC50h
    L_0041f9a7:
        mov ecx,1
    L_0041f9ac:
        call asm_Recovery_LoadCachedResource_00447280
    L_0041f9b1:
        test eax,eax
    L_0041f9b3:
        mov dword ptr [esi+3E0h],eax
    L_0041f9b9:
        je short L_0041fa0e
    L_0041f9bb:
        mov eax,dword ptr [esi+0Ch]
    L_0041f9be:
        or dword ptr [eax+4],2
    L_0041f9c2:
        mov dword ptr [esi+3E4h],1
    L_0041f9cc:
        call asm_CreateGameThread_00401440
    L_0041f9d1:
        test eax,eax
    L_0041f9d3:
        jne short L_0041f9e9
    L_0041f9d5:
        push 46DC28h
    L_0041f9da:
        mov ecx,474F70h
    L_0041f9df:
        call asm_TextLog_Append_0044b810
    L_0041f9e4:
        add esp,4
    L_0041f9e7:
        jmp short L_0041fa0e
    L_0041f9e9:
        mov edx,dword ptr [data_00491c10]
    L_0041f9ef:
        push 46CB5Ch
    L_0041f9f4:
        xor ecx,ecx
    L_0041f9f6:
        mov dword ptr [esi+3E8h],1
    L_0041fa00:
        call asm_Recovery_LoadCachedResource_00447280
    L_0041fa05:
        test eax,eax
    L_0041fa07:
        mov dword ptr [data_00491fec],eax
    L_0041fa0c:
        jne short L_0041fa24
    L_0041fa0e:
        mov dword ptr [data_00491fb8],3
    L_0041fa18:
        mov esi,dword ptr [esi+8]
    L_0041fa1b:
        or dword ptr [esi+4],2
    L_0041fa1f:
        xor eax,eax
    L_0041fa21:
        pop esi
    L_0041fa22:
        pop ecx
    L_0041fa23:
        ret
    L_0041fa24:
        push 0
    L_0041fa26:
        push 0
    L_0041fa28:
        mov eax,46DC14h
    L_0041fa2d:
        call asm_FUN_0044b360_0044b360
    L_0041fa32:
        test eax,eax
    L_0041fa34:
        mov dword ptr [data_00494514],eax
    L_0041fa39:
        jne short L_0041fa4d
    L_0041fa3b:
        push 46DBECh
    L_0041fa40:
        mov ecx,474F70h
    L_0041fa45:
        call asm_TextLog_Append_0044b810
    L_0041fa4a:
        add esp,4
    L_0041fa4d:
        push ebx
    L_0041fa4e:
        mov ebx,492590h
    L_0041fa53:
        call asm_FUN_0043db60_0043db60
    L_0041fa58:
        push 46DBE0h
    L_0041fa5d:
        call asm_File_ProbeExists_0044b4d0
    L_0041fa62:
        test eax,eax
    L_0041fa64:
        pop ebx
    L_0041fa65:
        je short L_0041faa5
    L_0041fa67:
        test byte ptr [data_00491d78],10h
    L_0041fa6e:
        jne short L_0041fa81
    L_0041fa70:
        push 46DBE0h
    L_0041fa75:
        mov eax,492590h
    L_0041fa7a:
        call asm_FUN_0043d690_0043d690
    L_0041fa7f:
        jmp short L_0041faa5
    L_0041fa81:
        mov eax,dword ptr [data_0046dbe0]
    L_0041fa86:
        mov ecx,dword ptr [data_0046dbe4]
    L_0041fa8c:
        mov dx,word ptr [data_0046dbe8]
    L_0041fa93:
        mov dword ptr [data_00497698],eax
    L_0041fa98:
        mov dword ptr [data_0049769c],ecx
    L_0041fa9e:
        mov word ptr [data_004976a0],dx
    L_0041faa5:
        call asm_Recovery_LoadStartupResources_0041f8d0
    L_0041faaa:
        mov esi,dword ptr [esi+8]
    L_0041faad:
        or dword ptr [esi+4],2
    L_0041fab1:
        call asm_FUN_0042af20_0042af20
    L_0041fab6:
        xor eax,eax
    L_0041fab8:
        pop esi
    L_0041fab9:
        pop ecx
    L_0041faba:
        ret
    }
}
