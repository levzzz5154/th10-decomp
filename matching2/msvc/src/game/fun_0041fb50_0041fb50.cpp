#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00405F70..0x0040605B: ItemManager_DestroyRetail
// Naked body preserves the retail register/stack ABI.

// 0x0041FB50..0x0041FCF0: FUN_0041fb50
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0041fb50_0041fb50() {
    __asm {
    L_0041fb50:
        push 0FFFFFFFFh
    L_0041fb52:
        push 465696h
    L_0041fb57:
        mov eax,dword ptr fs:[0]
    L_0041fb5d:
        push eax
    L_0041fb5e:
        mov dword ptr fs:[0],esp
    L_0041fb65:
        push ecx
    L_0041fb66:
        push ebx
    L_0041fb67:
        push ebp
    L_0041fb68:
        push esi
    L_0041fb69:
        push edi
    L_0041fb6a:
        mov dword ptr [esp+1Ch],1
    L_0041fb72:
        mov edi,dword ptr [esp+24h]
    L_0041fb76:
        lea esi,[edi+10h]
    L_0041fb79:
        mov dword ptr [esp+10h],esi
    L_0041fb7d:
        call asm_Platform_StopWorker_0044c150
    L_0041fb82:
        mov edi,dword ptr [edi+8]
    L_0041fb85:
        test edi,edi
    L_0041fb87:
        mov ebx,dword ptr [data_00491be4]
    L_0041fb8d:
        mov esi,dword ptr [data_004660b0]
    L_0041fb93:
        mov ebp,dword ptr [data_004660b4]
    L_0041fb99:
        je short L_0041fbbe
    L_0041fb9b:
        push 492274h
    L_0041fba0:
        call esi
    L_0041fba2:
        inc byte ptr [data_0049231c]
    L_0041fba8:
        mov ecx,edi
    L_0041fbaa:
        mov edx,ebx
    L_0041fbac:
        call asm_Scheduler_Remove_00449f60
    L_0041fbb1:
        push 492274h
    L_0041fbb6:
        call ebp
    L_0041fbb8:
        dec byte ptr [data_0049231c]
    L_0041fbbe:
        mov eax,dword ptr [esp+24h]
    L_0041fbc2:
        mov edi,dword ptr [eax+0Ch]
    L_0041fbc5:
        test edi,edi
    L_0041fbc7:
        mov ebx,dword ptr [data_00491be4]
    L_0041fbcd:
        je short L_0041fbf2
    L_0041fbcf:
        push 492274h
    L_0041fbd4:
        call esi
    L_0041fbd6:
        inc byte ptr [data_0049231c]
    L_0041fbdc:
        mov ecx,edi
    L_0041fbde:
        mov edx,ebx
    L_0041fbe0:
        call asm_Scheduler_Remove_00449f60
    L_0041fbe5:
        push 492274h
    L_0041fbea:
        call ebp
    L_0041fbec:
        dec byte ptr [data_0049231c]
    L_0041fbf2:
        call asm_Recovery_ReleasePair_0041f930
    L_0041fbf7:
        mov ebx,dword ptr [data_00491c10]
    L_0041fbfd:
        mov edi,dword ptr [ebx+3AD070h]
    L_0041fc03:
        add ebx,3AD070h
    L_0041fc09:
        xor ebp,ebp
    L_0041fc0b:
        cmp edi,ebp
    L_0041fc0d:
        je short L_0041fc21
    L_0041fc0f:
        call asm_FUN_00447810_00447810
    L_0041fc14:
        mov ecx,dword ptr [ebx]
    L_0041fc16:
        push ecx
    L_0041fc17:
        call asm_free_004524a1
    L_0041fc1c:
        add esp,4
    L_0041fc1f:
        mov dword ptr [ebx],ebp
    L_0041fc21:
        mov esi,dword ptr [data_004776e0]
    L_0041fc27:
        cmp esi,ebp
    L_0041fc29:
        mov dword ptr [data_00477820],ebp
    L_0041fc2f:
        je short L_0041fc40
    L_0041fc31:
        push esi
    L_0041fc32:
        call asm_DestroyGameThread_00401260
    L_0041fc37:
        push esi
    L_0041fc38:
        call asm_free_004524a1
    L_0041fc3d:
        add esp,4
    L_0041fc40:
        mov ebx,dword ptr [data_00491c10]
    L_0041fc46:
        mov edi,dword ptr [ebx+3AD06Ch]
    L_0041fc4c:
        add ebx,3AD06Ch
    L_0041fc52:
        cmp edi,ebp
    L_0041fc54:
        je short L_0041fc68
    L_0041fc56:
        call asm_FUN_00447810_00447810
    L_0041fc5b:
        mov edx,dword ptr [ebx]
    L_0041fc5d:
        push edx
    L_0041fc5e:
        call asm_free_004524a1
    L_0041fc63:
        add esp,4
    L_0041fc66:
        mov dword ptr [ebx],ebp
    L_0041fc68:
        mov ebx,dword ptr [data_0047783c]
    L_0041fc6e:
        call asm_FUN_0042b1e0_0042b1e0
    L_0041fc73:
        mov edi,dword ptr [data_0047783c]
    L_0041fc79:
        cmp edi,ebp
    L_0041fc7b:
        je short L_0041fcaa
    L_0041fc7d:
        mov eax,dword ptr [edi]
    L_0041fc7f:
        cmp eax,ebp
    L_0041fc81:
        je short L_0041fc8e
    L_0041fc83:
        push eax
    L_0041fc84:
        call asm_free_00452422
    L_0041fc89:
        add esp,4
    L_0041fc8c:
        mov dword ptr [edi],ebp
    L_0041fc8e:
        mov eax,dword ptr [edi+4]
    L_0041fc91:
        cmp eax,ebp
    L_0041fc93:
        je short L_0041fca1
    L_0041fc95:
        push eax
    L_0041fc96:
        call asm_free_00452422
    L_0041fc9b:
        add esp,4
    L_0041fc9e:
        mov dword ptr [edi+4],ebp
    L_0041fca1:
        push edi
    L_0041fca2:
        call asm_free_004524a1
    L_0041fca7:
        add esp,4
    L_0041fcaa:
        mov esi,dword ptr [esp+24h]
    L_0041fcae:
        mov eax,dword ptr [esi+388h]
    L_0041fcb4:
        cmp eax,ebp
    L_0041fcb6:
        mov dword ptr [data_0047783c],ebp
    L_0041fcbc:
        je short L_0041fcc7
    L_0041fcbe:
        push eax
    L_0041fcbf:
        call asm_free_00452422
    L_0041fcc4:
        add esp,4
    L_0041fcc7:
        mov dword ptr [esi+388h],ebp
    L_0041fccd:
        mov esi,dword ptr [esp+10h]
    L_0041fcd1:
        mov dword ptr [esi],4703E4h
    L_0041fcd7:
        call asm_Platform_StopWorker_0044c150
    L_0041fcdc:
        mov ecx,dword ptr [esp+14h]
    L_0041fce0:
        pop edi
    L_0041fce1:
        pop esi
    L_0041fce2:
        pop ebp
    L_0041fce3:
        pop ebx
    L_0041fce4:
        mov dword ptr fs:[0],ecx
    L_0041fceb:
        add esp,10h
    L_0041fcee:
        ret 4
    }
}
