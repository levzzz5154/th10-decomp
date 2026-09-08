#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0042A430..0x0042A44B: FUN_0042a430
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0042a430_0042a430() {
    __asm {
    L_0042a430:
        mov eax,dword ptr [data_00477810]
    L_0042a435:
        test eax,eax
    L_0042a437:
        je short L_0042a445
    L_0042a439:
        test byte ptr [eax+58h],4
    L_0042a43d:
        je short L_0042a445
    L_0042a43f:
        mov eax,1
    L_0042a444:
        ret
    L_0042a445:
        mov edx,ecx
    L_0042a447:
        jmp asm_FUN_00429a70_00429a70
    }
}
