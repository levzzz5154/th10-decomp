#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00452ABC..0x00452AE7: FUN_00452abc
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00452abc_00452abc() {
    __asm {
    L_00452abc:
        push 0
    L_00452abe:
        push dword ptr [esp+8]
    L_00452ac2:
        call dword ptr [data_004661e0]
    L_00452ac8:
        test eax,eax
    L_00452aca:
        jne short L_00452ad4
    L_00452acc:
        call dword ptr [data_0046610c]
    L_00452ad2:
        jmp short L_00452ad6
    L_00452ad4:
        xor eax,eax
    L_00452ad6:
        test eax,eax
    L_00452ad8:
        je short L_00452ae5
    L_00452ada:
        push eax
    L_00452adb:
        call asm_dosmaperr_00456b04
    L_00452ae0:
        pop ecx
    L_00452ae1:
        or eax,0FFFFFFFFh
    L_00452ae4:
        ret
    L_00452ae5:
        xor eax,eax
    L_00452ae7:
        ret
    }
}
