#include "asm_encoding.hpp"
#include "asm_symbols.hpp"


// 0x00449A90..0x00449A9B: ?D3DResourceList_ClearPending@@
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_D3DResourceList_ClearPending_00449a90() {
    __asm {
    L_00449a90:
        xor ecx,ecx
    L_00449a92:
        mov dword ptr [eax+8],ecx
    L_00449a95:
        mov dword ptr [eax+0Ch],ecx
    L_00449a98:
        mov dword ptr [eax+10h],ecx
    L_00449a9b:
        ret
    }
}


