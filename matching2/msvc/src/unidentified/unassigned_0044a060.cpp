#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0044A060..0x0044A08A: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_0044a060() {
    __asm {
    L_0044a060:
        push esi
    L_0044a061:
        push eax
    L_0044a062:
        call asm_SchedulerCallback_Create_00449ed0
    L_0044a067:
        mov ecx,dword ptr [esp+8]
    L_0044a06b:
        mov edx,dword ptr [data_00491be4]
    L_0044a071:
        mov esi,eax
    L_0044a073:
        mov dword ptr [esi+20h],ecx
    L_0044a076:
        mov ecx,dword ptr [esi+4]
    L_0044a079:
        and ecx,0FFFFFFFDh
    L_0044a07c:
        push edx
    L_0044a07d:
        mov dword ptr [esi+4],ecx
    L_0044a080:
        call asm_Scheduler_RegisterPrimary_00449ae0
    L_0044a085:
        mov eax,esi
    L_0044a087:
        pop esi
    L_0044a088:
        ret 4
    }
}
