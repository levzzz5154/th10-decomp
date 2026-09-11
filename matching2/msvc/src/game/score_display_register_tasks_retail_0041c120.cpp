#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00413980..0x00413A12: ItemFrontRuntime_InitializeRetail
// Naked body preserves the retail register/stack ABI.

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
