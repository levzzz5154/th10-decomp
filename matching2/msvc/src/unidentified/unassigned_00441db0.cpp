#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00441DB0..0x00441DC3: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00441db0() {
    __asm {
    L_00441db0:
        fild dword ptr [eax+34h]
    L_00441db3:
        push ecx
    L_00441db4:
        mov ecx,dword ptr [eax+28h]
    L_00441db7:
        mov eax,dword ptr [eax+38h]
    L_00441dba:
        fstp dword ptr [esp]
    L_00441dbd:
        push ecx
    L_00441dbe:
        call asm_FUN_0044c350_0044c350
    L_00441dc3:
        ret
    }
}
