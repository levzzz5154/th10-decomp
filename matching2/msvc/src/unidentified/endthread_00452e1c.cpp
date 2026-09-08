#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00452E1C..0x00452E58: __endthread
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_endthread_00452e1c() {
    __asm {
    L_00452e1c:
        mov eax,dword ptr [data_004733b0]
    L_00452e21:
        test eax,eax
    L_00452e23:
        je short L_00452e27
    L_00452e25:
        call eax
    L_00452e27:
        push esi
    L_00452e28:
        call asm_getptd_00456357
    L_00452e2d:
        mov esi,eax
    L_00452e2f:
        test esi,esi
    L_00452e31:
        jne short L_00452e3b
    L_00452e33:
        push 10h
    L_00452e35:
        call asm_amsg_exit_0045373d
    L_00452e3a:
        pop ecx
    L_00452e3b:
        mov eax,dword ptr [esi+4]
    L_00452e3e:
        cmp eax,0FFFFFFFFh
    L_00452e41:
        je short L_00452e4a
    L_00452e43:
        push eax
    L_00452e44:
        call dword ptr [data_004660cc]
    L_00452e4a:
        push esi
    L_00452e4b:
        call asm_freeptd_0045650f
    L_00452e50:
        pop ecx
    L_00452e51:
        push 0
    L_00452e53:
        call dword ptr [data_004661ac]
    }
}
