#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x004133F0..0x0041344A: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_004133f0() {
    __asm {
    L_004133f0:
        push esi
    L_004133f1:
        mov esi,dword ptr [ebx+0Ch]
    L_004133f4:
        test esi,esi
    L_004133f6:
        push edi
    L_004133f7:
        mov edi,dword ptr [data_00491be4]
    L_004133fd:
        je short L_0041342a
    L_004133ff:
        push 492274h
    L_00413404:
        call dword ptr [data_004660b0]
    L_0041340a:
        inc byte ptr [data_0049231c]
    L_00413410:
        mov ecx,esi
    L_00413412:
        mov edx,edi
    L_00413414:
        call asm_Scheduler_Remove_00449f60
    L_00413419:
        push 492274h
    L_0041341e:
        call dword ptr [data_004660b4]
    L_00413424:
        dec byte ptr [data_0049231c]
    L_0041342a:
        test byte ptr [esp+0Ch],1
    L_0041342f:
        pop edi
    L_00413430:
        mov dword ptr [data_00477708],0
    L_0041343a:
        pop esi
    L_0041343b:
        je short L_00413446
    L_0041343d:
        push ebx
    L_0041343e:
        call asm_free_004524a1
    L_00413443:
        add esp,4
    L_00413446:
        mov eax,ebx
    L_00413448:
        ret 4
    }
}
