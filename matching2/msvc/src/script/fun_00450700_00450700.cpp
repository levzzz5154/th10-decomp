#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00450470..0x004504F7: FUN_00450470
// Naked body preserves the retail register/stack ABI.

// 0x00450700..0x0045071D: FUN_00450700
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00450700_00450700() {
    __asm {
    L_00450700:
        mov eax,dword ptr [esi+102Ch]
    L_00450706:
        push ecx
    L_00450707:
        call asm_FUN_00450470_00450470
    L_0045070c:
        mov edx,dword ptr [esi+4]
    L_0045070f:
        mov dword ptr [edx+4],eax
    L_00450712:
        mov eax,dword ptr [esi+4]
    L_00450715:
        mov dword ptr [eax],0
    L_0045071b:
        xor eax,eax
    L_0045071d:
        ret
    }
}
