#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00420C00..0x00420C28: ?GameState_DispatchDummy@@
// Naked body preserves the retail register/stack ABI.

// 0x0044A030..0x0044A05A: ?Scheduler_CreateAndRegisterSecondary@@
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_Scheduler_CreateAndRegisterSecondary_0044a030() {
    __asm {
    L_0044a030:
        push esi
    L_0044a031:
        push eax
    L_0044a032:
        call asm_SchedulerCallback_Create_00449ed0
    L_0044a037:
        mov ecx,dword ptr [esp+8]
    L_0044a03b:
        mov edx,dword ptr [data_00491be4]
    L_0044a041:
        mov esi,eax
    L_0044a043:
        mov dword ptr [esi+20h],ecx
    L_0044a046:
        mov ecx,dword ptr [esi+4]
    L_0044a049:
        or ecx,2
    L_0044a04c:
        push edx
    L_0044a04d:
        mov dword ptr [esi+4],ecx
    L_0044a050:
        call asm_Scheduler_RegisterSecondary_00449b70
    L_0044a055:
        mov eax,esi
    L_0044a057:
        pop esi
    L_0044a058:
        ret 4
    }
}
