#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00436770..0x0043677C: FUN_00436770
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00436770_00436770() {
    __asm {
    L_00436770:
        mov eax,dword ptr [esp+8]
    L_00436774:
        mov cl,byte ptr [eax]
    L_00436776:
        mov edx,dword ptr [esp+4]
    L_0043677a:
        mov byte ptr [edx],cl
    L_0043677c:
        ret
    }
}
