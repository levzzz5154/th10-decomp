#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0042BC30..0x0042BDC4: FUN_0042bc30
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0042bc30_0042bc30() {
    __asm {
    L_0042bc30:
        mov eax,dword ptr fs:[0]
    L_0042bc36:
        push 0FFFFFFFFh
    L_0042bc38:
        push 4653EBh
    L_0042bc3d:
        push eax
    L_0042bc3e:
        mov dword ptr fs:[0],esp
    L_0042bc45:
        push ebx
    L_0042bc46:
        push ebp
    L_0042bc47:
        push esi
    L_0042bc48:
        mov esi,dword ptr [esp+1Ch]
    L_0042bc4c:
        push edi
    L_0042bc4d:
        mov dword ptr [esp+18h],0
    L_0042bc55:
        call asm_FUN_0042bad0_0042bad0
    L_0042bc5a:
        mov edi,dword ptr [esi+8]
    L_0042bc5d:
        test edi,edi
    L_0042bc5f:
        mov ebx,dword ptr [data_00491be4]
    L_0042bc65:
        mov ebp,dword ptr [data_004660b0]
    L_0042bc6b:
        je short L_0042bc94
    L_0042bc6d:
        push 492274h
    L_0042bc72:
        call ebp
    L_0042bc74:
        inc byte ptr [data_0049231c]
    L_0042bc7a:
        mov ecx,edi
    L_0042bc7c:
        mov edx,ebx
    L_0042bc7e:
        call asm_Scheduler_Remove_00449f60
    L_0042bc83:
        push 492274h
    L_0042bc88:
        call dword ptr [data_004660b4]
    L_0042bc8e:
        dec byte ptr [data_0049231c]
    L_0042bc94:
        mov edi,dword ptr [esi+0Ch]
    L_0042bc97:
        test edi,edi
    L_0042bc99:
        mov ebx,dword ptr [data_00491be4]
    L_0042bc9f:
        je short L_0042bcc8
    L_0042bca1:
        push 492274h
    L_0042bca6:
        call ebp
    L_0042bca8:
        inc byte ptr [data_0049231c]
    L_0042bcae:
        mov ecx,edi
    L_0042bcb0:
        mov edx,ebx
    L_0042bcb2:
        call asm_Scheduler_Remove_00449f60
    L_0042bcb7:
        push 492274h
    L_0042bcbc:
        call dword ptr [data_004660b4]
    L_0042bcc2:
        dec byte ptr [data_0049231c]
    L_0042bcc8:
        mov eax,dword ptr [esi+2E0h]
    L_0042bcce:
        test eax,eax
    L_0042bcd0:
        je short L_0042bce5
    L_0042bcd2:
        push eax
    L_0042bcd3:
        call asm_free_00452422
    L_0042bcd8:
        add esp,4
    L_0042bcdb:
        mov dword ptr [esi+2E0h],0
    L_0042bce5:
        mov edi,dword ptr [esi+2D8h]
    L_0042bceb:
        test edi,edi
    L_0042bced:
        je short L_0042bd25
    L_0042bcef:
        mov eax,dword ptr [edi+8Ch]
    L_0042bcf5:
        test eax,eax
    L_0042bcf7:
        mov dword ptr [edi],46D0F0h
    L_0042bcfd:
        je short L_0042bd12
    L_0042bcff:
        push eax
    L_0042bd00:
        call asm_free_00452422
    L_0042bd05:
        add esp,4
    L_0042bd08:
        mov dword ptr [edi+8Ch],0
    L_0042bd12:
        push edi
    L_0042bd13:
        call asm_free_004524a1
    L_0042bd18:
        add esp,4
    L_0042bd1b:
        mov dword ptr [esi+2D8h],0
    L_0042bd25:
        mov ecx,dword ptr [esi+2DCh]
    L_0042bd2b:
        test ecx,ecx
    L_0042bd2d:
        je short L_0042bd40
    L_0042bd2f:
        mov eax,dword ptr [ecx]
    L_0042bd31:
        push 1
    L_0042bd33:
        call dword ptr [eax+14h]
    L_0042bd36:
        mov dword ptr [esi+2DCh],0
    L_0042bd40:
        mov ebx,dword ptr [data_00491c10]
    L_0042bd46:
        mov edi,dword ptr [ebx+3AD088h]
    L_0042bd4c:
        add ebx,3AD088h
    L_0042bd52:
        test edi,edi
    L_0042bd54:
        je short L_0042bd6c
    L_0042bd56:
        call asm_FUN_00447810_00447810
    L_0042bd5b:
        mov ecx,dword ptr [ebx]
    L_0042bd5d:
        push ecx
    L_0042bd5e:
        call asm_free_004524a1
    L_0042bd63:
        add esp,4
    L_0042bd66:
        mov dword ptr [ebx],0
    L_0042bd6c:
        mov ebx,dword ptr [data_00491c10]
    L_0042bd72:
        mov edi,dword ptr [ebx+3AD084h]
    L_0042bd78:
        add ebx,3AD084h
    L_0042bd7e:
        test edi,edi
    L_0042bd80:
        je short L_0042bd98
    L_0042bd82:
        call asm_FUN_00447810_00447810
    L_0042bd87:
        mov edx,dword ptr [ebx]
    L_0042bd89:
        push edx
    L_0042bd8a:
        call asm_free_004524a1
    L_0042bd8f:
        add esp,4
    L_0042bd92:
        mov dword ptr [ebx],0
    L_0042bd98:
        add esi,10h
    L_0042bd9b:
        mov dword ptr [data_00477844],0
    L_0042bda5:
        mov dword ptr [esi],4703E4h
    L_0042bdab:
        call asm_Platform_StopWorker_0044c150
    L_0042bdb0:
        mov ecx,dword ptr [esp+10h]
    L_0042bdb4:
        pop edi
    L_0042bdb5:
        pop esi
    L_0042bdb6:
        pop ebp
    L_0042bdb7:
        mov dword ptr fs:[0],ecx
    L_0042bdbe:
        pop ebx
    L_0042bdbf:
        add esp,0Ch
    L_0042bdc2:
        ret 4
    }
}
