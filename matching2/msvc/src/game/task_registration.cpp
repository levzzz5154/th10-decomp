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


