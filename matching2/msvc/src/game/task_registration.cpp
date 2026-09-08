#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00413980..0x00413A12: ItemFrontRuntime_InitializeRetail
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_ItemFrontRuntime_InitializeRetail_00413980() {
    __asm {
    L_00413980:
        mov edx,dword ptr [data_00491c10]
    L_00413986:
        push 46D254h
    L_0041398b:
        mov ecx,6
    L_00413990:
        call asm_Recovery_LoadCachedResource_00447280
    L_00413995:
        test eax,eax
    L_00413997:
        mov dword ptr [ebx+9EC8h],eax
    L_0041399d:
        jne short L_004139b5
    L_0041399f:
        push 46CB68h
    L_004139a4:
        mov ecx,474F70h
    L_004139a9:
        call asm_TextLog_Append_0044b810
    L_004139ae:
        add esp,4
    L_004139b1:
        or eax,0FFFFFFFFh
    L_004139b4:
        ret
    L_004139b5:
        push ebx
    L_004139b6:
        call asm_FUN_00413a20_00413a20
    L_004139bb:
        test eax,eax
    L_004139bd:
        jne short L_004139b1
    L_004139bf:
        push esi
    L_004139c0:
        push edi
    L_004139c1:
        push 415AE0h
    L_004139c6:
        call asm_SchedulerCallback_Create_00449ed0
    L_004139cb:
        mov esi,eax
    L_004139cd:
        and dword ptr [esi+4],0FFFFFFFDh
    L_004139d1:
        mov eax,dword ptr [data_00491be4]
    L_004139d6:
        push eax
    L_004139d7:
        mov edi,18h
    L_004139dc:
        mov dword ptr [esi+20h],ebx
    L_004139df:
        call asm_Scheduler_RegisterPrimary_00449ae0
    L_004139e4:
        push 415AF0h
    L_004139e9:
        mov dword ptr [ebx+8],esi
    L_004139ec:
        call asm_SchedulerCallback_Create_00449ed0
    L_004139f1:
        mov esi,eax
    L_004139f3:
        and dword ptr [esi+4],0FFFFFFFDh
    L_004139f7:
        mov ecx,dword ptr [data_00491be4]
    L_004139fd:
        push ecx
    L_004139fe:
        mov edi,2Bh
    L_00413a03:
        mov dword ptr [esi+20h],ebx
    L_00413a06:
        call asm_Scheduler_RegisterSecondary_00449b70
    L_00413a0b:
        pop edi
    L_00413a0c:
        mov dword ptr [ebx+0Ch],esi
    L_00413a0f:
        xor eax,eax
    L_00413a11:
        pop esi
    L_00413a12:
        ret
    }
}

// 0x0041C120..0x0041C1B1: ScoreDisplay_RegisterTasksRetail
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_ScoreDisplay_RegisterTasksRetail_0041c120() {
    __asm {
    L_0041c120:
        mov edx,dword ptr [data_00491c10]
    L_0041c126:
        push 46CD88h
    L_0041c12b:
        mov ecx,7
    L_0041c130:
        call asm_Recovery_LoadCachedResource_00447280
    L_0041c135:
        test eax,eax
    L_0041c137:
        mov dword ptr [ebx+458h],eax
    L_0041c13d:
        jne short L_0041c155
    L_0041c13f:
        push 46CD54h
    L_0041c144:
        mov ecx,474F70h
    L_0041c149:
        call asm_TextLog_Append_0044b810
    L_0041c14e:
        add esp,4
    L_0041c151:
        or eax,0FFFFFFFFh
    L_0041c154:
        ret
    L_0041c155:
        push esi
    L_0041c156:
        push edi
    L_0041c157:
        push 41C480h
    L_0041c15c:
        call asm_SchedulerCallback_Create_00449ed0
    L_0041c161:
        mov esi,eax
    L_0041c163:
        and dword ptr [esi+4],0FFFFFFFDh
    L_0041c167:
        mov eax,dword ptr [data_00491be4]
    L_0041c16c:
        push eax
    L_0041c16d:
        mov edi,13h
    L_0041c172:
        mov dword ptr [esi+20h],ebx
    L_0041c175:
        call asm_Scheduler_RegisterPrimary_00449ae0
    L_0041c17a:
        push 41C4E0h
    L_0041c17f:
        mov dword ptr [ebx+8],esi
    L_0041c182:
        call asm_SchedulerCallback_Create_00449ed0
    L_0041c187:
        mov esi,eax
    L_0041c189:
        and dword ptr [esi+4],0FFFFFFFDh
    L_0041c18d:
        mov ecx,dword ptr [data_00491be4]
    L_0041c193:
        push ecx
    L_0041c194:
        mov edi,1Bh
    L_0041c199:
        mov dword ptr [esi+20h],ebx
    L_0041c19c:
        call asm_Scheduler_RegisterSecondary_00449b70
    L_0041c1a1:
        lea edx,[ebx+10h]
    L_0041c1a4:
        pop edi
    L_0041c1a5:
        mov dword ptr [ebx+0Ch],esi
    L_0041c1a8:
        mov dword ptr [ebx+434h],edx
    L_0041c1ae:
        xor eax,eax
    L_0041c1b0:
        pop esi
    L_0041c1b1:
        ret
    }
}

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
