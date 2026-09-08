#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00459F7D..0x00459FA6: __isatty
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_isatty_00459f7d() {
    __asm {
    L_00459f7d:
        mov eax,dword ptr [esp+4]
    L_00459f81:
        cmp eax,dword ptr [data_004991e4]
    L_00459f87:
        jb short L_00459f8c
    L_00459f89:
        xor eax,eax
    L_00459f8b:
        ret
    L_00459f8c:
        mov ecx,eax
    L_00459f8e:
        and eax,1Fh
    L_00459f91:
        sar ecx,5
    L_00459f94:
        mov ecx,dword ptr [ecx*4+499200h]
    L_00459f9b:
        lea eax,[eax+eax*8]
    L_00459f9e:
        movsx eax,byte ptr [ecx+eax*4+4]
    L_00459fa3:
        and eax,40h
    L_00459fa6:
        ret
    }
}
