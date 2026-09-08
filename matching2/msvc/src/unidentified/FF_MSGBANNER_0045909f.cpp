#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0045909F..0x004590D7: __FF_MSGBANNER
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FF_MSGBANNER_0045909f() {
    __asm {
    L_0045909f:
        mov eax,dword ptr [data_0047720c]
    L_004590a4:
        cmp eax,1
    L_004590a7:
        je short L_004590b6
    L_004590a9:
        test eax,eax
    L_004590ab:
        jne short L_004590d7
    L_004590ad:
        cmp dword ptr [data_00473074],1
    L_004590b4:
        jne short L_004590d7
    L_004590b6:
        push 0FCh
    L_004590bb:
        call asm_FUN_00458efd_00458efd
    L_004590c0:
        mov eax,dword ptr [data_004774b4]
    L_004590c5:
        test eax,eax
    L_004590c7:
        pop ecx
    L_004590c8:
        je short L_004590cc
    L_004590ca:
        call eax
    L_004590cc:
        push 0FFh
    L_004590d1:
        call asm_FUN_00458efd_00458efd
    L_004590d6:
        pop ecx
    L_004590d7:
        ret
    }
}
