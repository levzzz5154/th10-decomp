#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00439350..0x0043938D: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00439350() {
    __asm {
    L_00439350:
        mov eax,dword ptr [data_0049251c]
    L_00439355:
        push esi
    L_00439356:
        mov esi,dword ptr [data_00466258]
    L_0043935c:
        push 2
    L_0043935e:
        push 0
    L_00439360:
        push eax
    L_00439361:
        push 11h
    L_00439363:
        call esi
    L_00439365:
        mov ecx,dword ptr [data_00492520]
    L_0043936b:
        push 2
    L_0043936d:
        push 0
    L_0043936f:
        push ecx
    L_00439370:
        push 55h
    L_00439372:
        call esi
    L_00439374:
        mov edx,dword ptr [data_00492524]
    L_0043937a:
        push 2
    L_0043937c:
        push 0
    L_0043937e:
        push edx
    L_0043937f:
        push 56h
    L_00439381:
        call esi
    L_00439383:
        push 1
    L_00439385:
        push 0
    L_00439387:
        call asm_WINNLSEnableIME_0045232c
    L_0043938c:
        pop esi
    L_0043938d:
        ret
    }
}
