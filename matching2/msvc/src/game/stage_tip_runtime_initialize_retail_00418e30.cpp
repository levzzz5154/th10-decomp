#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00418D40..0x00418E2C: StageTipManager_Construct
// Naked body preserves the retail register/stack ABI.

// 0x00418E30..0x00418EB2: StageTipRuntime_InitializeRetail
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_StageTipRuntime_InitializeRetail_00418e30() {
    __asm {
    L_00418e30:
        push esi
    L_00418e31:
        push edi
    L_00418e32:
        push 4198A0h
    L_00418e37:
        call asm_SchedulerCallback_Create_00449ed0
    L_00418e3c:
        mov esi,eax
    L_00418e3e:
        mov edx,dword ptr [esi+4]
    L_00418e41:
        mov eax,dword ptr [data_00491be4]
    L_00418e46:
        and edx,0FFFFFFFDh
    L_00418e49:
        push eax
    L_00418e4a:
        mov edi,19h
    L_00418e4f:
        mov dword ptr [esi+20h],ebx
    L_00418e52:
        mov dword ptr [esi+4],edx
    L_00418e55:
        call asm_Scheduler_RegisterPrimary_00449ae0
    L_00418e5a:
        push 4198B0h
    L_00418e5f:
        mov dword ptr [ebx+8],esi
    L_00418e62:
        call asm_SchedulerCallback_Create_00449ed0
    L_00418e67:
        mov ecx,dword ptr [data_00491be4]
    L_00418e6d:
        mov esi,eax
    L_00418e6f:
        and dword ptr [esi+4],0FFFFFFFDh
    L_00418e73:
        push ecx
    L_00418e74:
        mov edi,2Ch
    L_00418e79:
        mov dword ptr [esi+20h],ebx
    L_00418e7c:
        call asm_Scheduler_RegisterSecondary_00449b70
    L_00418e81:
        mov dword ptr [ebx+0Ch],esi
    L_00418e84:
        mov dword ptr [ebx+10h],0
    L_00418e8b:
        mov al,byte ptr [data_00491d6a]
    L_00418e90:
        test al,al
    L_00418e92:
        pop edi
    L_00418e93:
        pop esi
    L_00418e94:
        je short L_00418eb0
    L_00418e96:
        push 0
    L_00418e98:
        push 46D6D8h
    L_00418e9d:
        push ebx
    L_00418e9e:
        call asm_FUN_00419960_00419960
    L_00418ea3:
        push 1
    L_00418ea5:
        push 46D6C4h
    L_00418eaa:
        push ebx
    L_00418eab:
        call asm_FUN_00419960_00419960
    L_00418eb0:
        xor eax,eax
    L_00418eb2:
        ret
    }
}
