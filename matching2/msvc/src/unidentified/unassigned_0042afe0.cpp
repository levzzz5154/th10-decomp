#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0042AFE0..0x0042B020: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_0042afe0() {
    __asm {
    L_0042afe0:
        mov eax,dword ptr [esi]
    L_0042afe2:
        test eax,eax
    L_0042afe4:
        je short L_0042aff5
    L_0042afe6:
        push eax
    L_0042afe7:
        call asm_free_00452422
    L_0042afec:
        add esp,4
    L_0042afef:
        mov dword ptr [esi],0
    L_0042aff5:
        mov eax,dword ptr [esi+4]
    L_0042aff8:
        test eax,eax
    L_0042affa:
        je short L_0042b00c
    L_0042affc:
        push eax
    L_0042affd:
        call asm_free_00452422
    L_0042b002:
        add esp,4
    L_0042b005:
        mov dword ptr [esi+4],0
    L_0042b00c:
        test byte ptr [esp+4],1
    L_0042b011:
        je short L_0042b01c
    L_0042b013:
        push esi
    L_0042b014:
        call asm_free_004524a1
    L_0042b019:
        add esp,4
    L_0042b01c:
        mov eax,esi
    L_0042b01e:
        ret 4
    }
}
