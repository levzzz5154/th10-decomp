#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0042AF90..0x0042AFDB: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_0042af90() {
    __asm {
    L_0042af90:
        push esi
    L_0042af91:
        mov esi,dword ptr [data_0047783c]
    L_0042af97:
        test esi,esi
    L_0042af99:
        je short L_0042afd0
    L_0042af9b:
        mov eax,dword ptr [esi]
    L_0042af9d:
        test eax,eax
    L_0042af9f:
        je short L_0042afb0
    L_0042afa1:
        push eax
    L_0042afa2:
        call asm_free_00452422
    L_0042afa7:
        add esp,4
    L_0042afaa:
        mov dword ptr [esi],0
    L_0042afb0:
        mov eax,dword ptr [esi+4]
    L_0042afb3:
        test eax,eax
    L_0042afb5:
        je short L_0042afc7
    L_0042afb7:
        push eax
    L_0042afb8:
        call asm_free_00452422
    L_0042afbd:
        add esp,4
    L_0042afc0:
        mov dword ptr [esi+4],0
    L_0042afc7:
        push esi
    L_0042afc8:
        call asm_free_004524a1
    L_0042afcd:
        add esp,4
    L_0042afd0:
        mov dword ptr [data_0047783c],0
    L_0042afda:
        pop esi
    L_0042afdb:
        ret
    }
}
