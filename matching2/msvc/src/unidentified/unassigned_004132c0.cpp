#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x004132C0..0x004132F1: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_004132c0() {
    __asm {
    L_004132c0:
        push esi
    L_004132c1:
        push edi
    L_004132c2:
        push 413690h
    L_004132c7:
        call asm_SchedulerCallback_Create_00449ed0
    L_004132cc:
        mov esi,eax
    L_004132ce:
        mov edx,dword ptr [esi+4]
    L_004132d1:
        mov eax,dword ptr [data_00491be4]
    L_004132d6:
        or edx,2
    L_004132d9:
        push eax
    L_004132da:
        mov edi,2Fh
    L_004132df:
        mov dword ptr [esi+20h],ebx
    L_004132e2:
        mov dword ptr [esi+4],edx
    L_004132e5:
        call asm_Scheduler_RegisterSecondary_00449b70
    L_004132ea:
        pop edi
    L_004132eb:
        mov dword ptr [ebx+0Ch],esi
    L_004132ee:
        xor eax,eax
    L_004132f0:
        pop esi
    L_004132f1:
        ret
    }
}
