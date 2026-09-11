#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00413980..0x00413A12: ItemFrontRuntime_InitializeRetail
// Naked body preserves the retail register/stack ABI.

// 0x0042CAA0..0x0042CB5F: Title_RegisterTasksRetail
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_Title_RegisterTasksRetail_0042caa0() {
    __asm {
    L_0042caa0:
        push esi
    L_0042caa1:
        push edi
    L_0042caa2:
        push 42D2E0h
    L_0042caa7:
        call asm_SchedulerCallback_Create_00449ed0
    L_0042caac:
        mov esi,eax
    L_0042caae:
        mov edi,dword ptr [esi+4]
    L_0042cab1:
        mov eax,dword ptr [data_00491be4]
    L_0042cab6:
        and edi,0FFFFFFFDh
    L_0042cab9:
        mov dword ptr [esi+4],edi
    L_0042cabc:
        push eax
    L_0042cabd:
        mov edi,6
    L_0042cac2:
        mov dword ptr [esi+20h],ebx
    L_0042cac5:
        call asm_Scheduler_RegisterPrimary_00449ae0
    L_0042caca:
        push 42D2F0h
    L_0042cacf:
        mov dword ptr [ebx+0Ch],esi
    L_0042cad2:
        call asm_SchedulerCallback_Create_00449ed0
    L_0042cad7:
        mov ecx,dword ptr [data_00491be4]
    L_0042cadd:
        mov esi,eax
    L_0042cadf:
        mov eax,dword ptr [esi+4]
    L_0042cae2:
        and eax,0FFFFFFFDh
    L_0042cae5:
        push ecx
    L_0042cae6:
        mov edi,3
    L_0042caeb:
        mov dword ptr [esi+20h],ebx
    L_0042caee:
        mov dword ptr [esi+4],eax
    L_0042caf1:
        call asm_Scheduler_RegisterSecondary_00449b70
    L_0042caf6:
        mov edx,dword ptr [data_00491c10]
    L_0042cafc:
        push 46F0ACh
    L_0042cb01:
        mov ecx,19h
    L_0042cb06:
        mov dword ptr [ebx+10h],esi
    L_0042cb09:
        call asm_Recovery_LoadCachedResource_00447280
    L_0042cb0e:
        test eax,eax
    L_0042cb10:
        pop edi
    L_0042cb11:
        mov dword ptr [ebx+14h],eax
    L_0042cb14:
        pop esi
    L_0042cb15:
        je short L_0042cb33
    L_0042cb17:
        mov edx,dword ptr [data_00491c10]
    L_0042cb1d:
        push 46F0A0h
    L_0042cb22:
        mov ecx,1Ah
    L_0042cb27:
        call asm_Recovery_LoadCachedResource_00447280
    L_0042cb2c:
        test eax,eax
    L_0042cb2e:
        mov dword ptr [ebx+18h],eax
    L_0042cb31:
        jne short L_0042cb49
    L_0042cb33:
        push 46CB68h
    L_0042cb38:
        mov ecx,474F70h
    L_0042cb3d:
        call asm_TextLog_Append_0044b810
    L_0042cb42:
        add esp,4
    L_0042cb45:
        or eax,0FFFFFFFFh
    L_0042cb48:
        ret
    L_0042cb49:
        mov dword ptr [ebx+0F4h],1
    L_0042cb53:
        mov dword ptr [data_004918a4],0
    L_0042cb5d:
        xor eax,eax
    L_0042cb5f:
        ret
    }
}
