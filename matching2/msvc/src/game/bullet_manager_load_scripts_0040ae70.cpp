#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0040AE70..0x0040AEF5: ?BulletManager_LoadScripts@@
// Naked body preserves the retail register/stack ABI.

// 0x0040AE70..0x0040AEF5: ?BulletManager_LoadScripts@@
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_BulletManager_LoadScripts_0040ae70() {
    __asm {
    L_0040ae70:
        mov edx,dword ptr [data_00491c10]
    L_0040ae76:
        push 46CD88h
    L_0040ae7b:
        mov ecx,7
    L_0040ae80:
        call asm_Recovery_LoadCachedResource_00447280
    L_0040ae85:
        test eax,eax
    L_0040ae87:
        mov dword ptr [ebx+10h],eax
    L_0040ae8a:
        jne short L_0040aea2
    L_0040ae8c:
        push 46CF74h
    L_0040ae91:
        mov ecx,474F70h
    L_0040ae96:
        call asm_TextLog_Append_0044b810
    L_0040ae9b:
        add esp,4
    L_0040ae9e:
        or eax,0FFFFFFFFh
    L_0040aea1:
        ret
    L_0040aea2:
        push esi
    L_0040aea3:
        push edi
    L_0040aea4:
        push 40B050h
    L_0040aea9:
        call asm_SchedulerCallback_Create_00449ed0
    L_0040aeae:
        mov esi,eax
    L_0040aeb0:
        and dword ptr [esi+4],0FFFFFFFDh
    L_0040aeb4:
        mov eax,dword ptr [data_00491be4]
    L_0040aeb9:
        push eax
    L_0040aeba:
        mov edi,17h
    L_0040aebf:
        mov dword ptr [esi+20h],ebx
    L_0040aec2:
        call asm_Scheduler_RegisterPrimary_00449ae0
    L_0040aec7:
        push 40B060h
    L_0040aecc:
        mov dword ptr [ebx+8],esi
    L_0040aecf:
        call asm_SchedulerCallback_Create_00449ed0
    L_0040aed4:
        mov esi,eax
    L_0040aed6:
        and dword ptr [esi+4],0FFFFFFFDh
    L_0040aeda:
        mov ecx,dword ptr [data_00491be4]
    L_0040aee0:
        push ecx
    L_0040aee1:
        mov edi,20h
    L_0040aee6:
        mov dword ptr [esi+20h],ebx
    L_0040aee9:
        call asm_Scheduler_RegisterSecondary_00449b70
    L_0040aeee:
        pop edi
    L_0040aeef:
        mov dword ptr [ebx+0Ch],esi
    L_0040aef2:
        xor eax,eax
    L_0040aef4:
        pop esi
    L_0040aef5:
        ret
    }
}
