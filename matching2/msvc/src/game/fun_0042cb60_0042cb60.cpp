#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00405F70..0x0040605B: ItemManager_DestroyRetail
// Naked body preserves the retail register/stack ABI.

// 0x0042CB60..0x0042CD4A: FUN_0042cb60
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0042cb60_0042cb60() {
    __asm {
    L_0042cb60:
        push 0FFFFFFFFh
    L_0042cb62:
        push 46562Eh
    L_0042cb67:
        mov eax,dword ptr fs:[0]
    L_0042cb6d:
        push eax
    L_0042cb6e:
        mov dword ptr fs:[0],esp
    L_0042cb75:
        push ecx
    L_0042cb76:
        push ebx
    L_0042cb77:
        push ebp
    L_0042cb78:
        push esi
    L_0042cb79:
        push edi
    L_0042cb7a:
        mov edi,dword ptr [esp+24h]
    L_0042cb7e:
        mov dword ptr [edi],46ECF0h
    L_0042cb84:
        lea esi,[edi+5AB0h]
    L_0042cb8a:
        mov dword ptr [esp+1Ch],0
    L_0042cb92:
        mov dword ptr [esp+10h],esi
    L_0042cb96:
        call asm_Platform_StopWorker_0044c150
    L_0042cb9b:
        mov edi,dword ptr [edi+0Ch]
    L_0042cb9e:
        test edi,edi
    L_0042cba0:
        mov ebx,dword ptr [data_00491be4]
    L_0042cba6:
        mov esi,dword ptr [data_004660b0]
    L_0042cbac:
        mov ebp,dword ptr [data_004660b4]
    L_0042cbb2:
        je short L_0042cbd7
    L_0042cbb4:
        push 492274h
    L_0042cbb9:
        call esi
    L_0042cbbb:
        inc byte ptr [data_0049231c]
    L_0042cbc1:
        mov ecx,edi
    L_0042cbc3:
        mov edx,ebx
    L_0042cbc5:
        call asm_Scheduler_Remove_00449f60
    L_0042cbca:
        push 492274h
    L_0042cbcf:
        call ebp
    L_0042cbd1:
        dec byte ptr [data_0049231c]
    L_0042cbd7:
        mov eax,dword ptr [esp+24h]
    L_0042cbdb:
        mov edi,dword ptr [eax+10h]
    L_0042cbde:
        test edi,edi
    L_0042cbe0:
        mov ebx,dword ptr [data_00491be4]
    L_0042cbe6:
        je short L_0042cc0b
    L_0042cbe8:
        push 492274h
    L_0042cbed:
        call esi
    L_0042cbef:
        inc byte ptr [data_0049231c]
    L_0042cbf5:
        mov ecx,edi
    L_0042cbf7:
        mov edx,ebx
    L_0042cbf9:
        call asm_Scheduler_Remove_00449f60
    L_0042cbfe:
        push 492274h
    L_0042cc03:
        call ebp
    L_0042cc05:
        dec byte ptr [data_0049231c]
    L_0042cc0b:
        mov ebx,dword ptr [data_00491c10]
    L_0042cc11:
        mov edi,dword ptr [ebx+3AD0D0h]
    L_0042cc17:
        add ebx,3AD0D0h
    L_0042cc1d:
        xor ebp,ebp
    L_0042cc1f:
        cmp edi,ebp
    L_0042cc21:
        je short L_0042cc35
    L_0042cc23:
        call asm_FUN_00447810_00447810
    L_0042cc28:
        mov ecx,dword ptr [ebx]
    L_0042cc2a:
        push ecx
    L_0042cc2b:
        call asm_free_004524a1
    L_0042cc30:
        add esp,4
    L_0042cc33:
        mov dword ptr [ebx],ebp
    L_0042cc35:
        mov ebx,dword ptr [data_00491c10]
    L_0042cc3b:
        mov edi,dword ptr [ebx+3AD0D4h]
    L_0042cc41:
        add ebx,3AD0D4h
    L_0042cc47:
        cmp edi,ebp
    L_0042cc49:
        je short L_0042cc5d
    L_0042cc4b:
        call asm_FUN_00447810_00447810
    L_0042cc50:
        mov edx,dword ptr [ebx]
    L_0042cc52:
        push edx
    L_0042cc53:
        call asm_free_004524a1
    L_0042cc58:
        add esp,4
    L_0042cc5b:
        mov dword ptr [ebx],ebp
    L_0042cc5d:
        mov ebx,dword ptr [esp+24h]
    L_0042cc61:
        add ebx,59E4h
    L_0042cc67:
        mov esi,32h
    L_0042cc6c:
        TH10_NOP_LEA_ESP_DISP8()
    L_0042cc70:
        mov edi,dword ptr [ebx]
    L_0042cc72:
        cmp edi,ebp
    L_0042cc74:
        je short L_0042cc85
    L_0042cc76:
        push edi
    L_0042cc77:
        call asm_FUN_004294a0_004294a0
    L_0042cc7c:
        push edi
    L_0042cc7d:
        call asm_free_004524a1
    L_0042cc82:
        add esp,4
    L_0042cc85:
        add ebx,4
    L_0042cc88:
        dec esi
    L_0042cc89:
        jne short L_0042cc70
    L_0042cc8b:
        mov esi,dword ptr [esp+24h]
    L_0042cc8f:
        mov ecx,dword ptr [esi+5D0h]
    L_0042cc95:
        cmp ecx,ebp
    L_0042cc97:
        je short L_0042cd04
    L_0042cc99:
        mov edx,dword ptr [data_00491c10]
    L_0042cc9f:
        mov eax,dword ptr [edx+72DAD4h]
    L_0042cca5:
        cmp eax,ebp
    L_0042cca7:
        je short L_0042ccbd
    L_0042cca9:
        lea esp,[esp+force_disp32_zero]
    L_0042ccb0:
        mov edi,dword ptr [eax]
    L_0042ccb2:
        cmp dword ptr [edi],ecx
    L_0042ccb4:
        je short L_0042ccd6
    L_0042ccb6:
        mov eax,dword ptr [eax+4]
    L_0042ccb9:
        cmp eax,ebp
    L_0042ccbb:
        jne short L_0042ccb0
    L_0042ccbd:
        mov eax,dword ptr [edx+72DADCh]
    L_0042ccc3:
        cmp eax,ebp
    L_0042ccc5:
        je short L_0042cd04
    L_0042ccc7:
        mov edx,dword ptr [eax]
    L_0042ccc9:
        cmp dword ptr [edx],ecx
    L_0042cccb:
        je short L_0042ccd6
    L_0042cccd:
        mov eax,dword ptr [eax+4]
    L_0042ccd0:
        cmp eax,ebp
    L_0042ccd2:
        jne short L_0042ccc7
    L_0042ccd4:
        jmp short L_0042cd04
    L_0042ccd6:
        mov eax,dword ptr [eax]
    L_0042ccd8:
        cmp eax,ebp
    L_0042ccda:
        je short L_0042cd04
    L_0042ccdc:
        cmp dword ptr [eax+18h],ebp
    L_0042ccdf:
        mov ecx,1
    L_0042cce4:
        mov word ptr [eax+304h],cx
    L_0042cceb:
        jne short L_0042cd04
    L_0042cced:
        mov eax,dword ptr [eax+14h]
    L_0042ccf0:
        cmp eax,ebp
    L_0042ccf2:
        je short L_0042cd04
    L_0042ccf4:
        mov edx,dword ptr [eax]
    L_0042ccf6:
        mov word ptr [edx+304h],cx
    L_0042ccfd:
        mov eax,dword ptr [eax+4]
    L_0042cd00:
        cmp eax,ebp
    L_0042cd02:
        jne short L_0042ccf4
    L_0042cd04:
        mov eax,dword ptr [esi+5AACh]
    L_0042cd0a:
        cmp eax,ebp
    L_0042cd0c:
        je short L_0042cd21
    L_0042cd0e:
        push eax
    L_0042cd0f:
        call asm_free_00452422
    L_0042cd14:
        mov eax,dword ptr [esp+28h]
    L_0042cd18:
        add esp,4
    L_0042cd1b:
        mov dword ptr [eax+5AACh],ebp
    L_0042cd21:
        mov esi,dword ptr [esp+10h]
    L_0042cd25:
        mov dword ptr [data_0047784c],ebp
    L_0042cd2b:
        mov dword ptr [esi],4703E4h
    L_0042cd31:
        call asm_Platform_StopWorker_0044c150
    L_0042cd36:
        mov ecx,dword ptr [esp+14h]
    L_0042cd3a:
        pop edi
    L_0042cd3b:
        pop esi
    L_0042cd3c:
        pop ebp
    L_0042cd3d:
        pop ebx
    L_0042cd3e:
        mov dword ptr fs:[0],ecx
    L_0042cd45:
        add esp,10h
    L_0042cd48:
        ret 4
    }
}
