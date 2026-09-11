#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00438A60..0x00438ACE: FUN_00438a60
// Naked body preserves the retail register/stack ABI.

// 0x00443F80..0x00443FA0: FUN_00443f80
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00443f80_00443f80() {
    __asm {
    L_00443f80:
        mov eax,esi
    L_00443f82:
        call asm_FUN_00443b60_00443b60
    L_00443f87:
        test eax,eax
    L_00443f89:
        je short L_00443f91
    L_00443f8b:
        or eax,0FFFFFFFFh
    L_00443f8e:
        ret 4
    L_00443f91:
        mov ecx,dword ptr [esp+4]
    L_00443f95:
        push 0
    L_00443f97:
        mov eax,esi
    L_00443f99:
        call asm_FUN_00442670_00442670
    L_00443f9e:
        ret 4
    }
}
