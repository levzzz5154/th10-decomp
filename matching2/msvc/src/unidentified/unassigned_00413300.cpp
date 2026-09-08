#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00413300..0x00413346: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00413300() {
    __asm {
    L_00413300:
        push esi
    L_00413301:
        mov esi,dword ptr [eax+0Ch]
    L_00413304:
        test esi,esi
    L_00413306:
        push edi
    L_00413307:
        mov edi,dword ptr [data_00491be4]
    L_0041330d:
        je short L_0041333a
    L_0041330f:
        push 492274h
    L_00413314:
        call dword ptr [data_004660b0]
    L_0041331a:
        inc byte ptr [data_0049231c]
    L_00413320:
        mov ecx,esi
    L_00413322:
        mov edx,edi
    L_00413324:
        call asm_Scheduler_Remove_00449f60
    L_00413329:
        push 492274h
    L_0041332e:
        call dword ptr [data_004660b4]
    L_00413334:
        dec byte ptr [data_0049231c]
    L_0041333a:
        pop edi
    L_0041333b:
        mov dword ptr [data_00477708],0
    L_00413345:
        pop esi
    L_00413346:
        ret
    }
}
