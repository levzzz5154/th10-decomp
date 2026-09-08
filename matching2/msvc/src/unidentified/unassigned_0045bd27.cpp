#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0045BD27..0x0045BD71: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_0045bd27() {
    __asm {
    L_0045bd27:
        call asm_getptd_00456357
    L_0045bd2c:
        mov eax,dword ptr [eax+64h]
    L_0045bd2f:
        cmp eax,dword ptr [data_0047320c]
    L_0045bd35:
        je short L_0045bd3c
    L_0045bd37:
        call asm_updatetlocinfo_00455ade
    L_0045bd3c:
        mov eax,dword ptr [eax+4]
    L_0045bd3f:
        ret
    L_0045bd40:
        call asm_getptd_00456357
    L_0045bd45:
        mov eax,dword ptr [eax+64h]
    L_0045bd48:
        cmp eax,dword ptr [data_0047320c]
    L_0045bd4e:
        je short L_0045bd55
    L_0045bd50:
        call asm_updatetlocinfo_00455ade
    L_0045bd55:
        mov eax,dword ptr [eax+8]
    L_0045bd58:
        ret
    L_0045bd59:
        call asm_getptd_00456357
    L_0045bd5e:
        mov eax,dword ptr [eax+64h]
    L_0045bd61:
        cmp eax,dword ptr [data_0047320c]
    L_0045bd67:
        je short L_0045bd6e
    L_0045bd69:
        call asm_updatetlocinfo_00455ade
    L_0045bd6e:
        add eax,0Ch
    L_0045bd71:
        ret
    }
}
