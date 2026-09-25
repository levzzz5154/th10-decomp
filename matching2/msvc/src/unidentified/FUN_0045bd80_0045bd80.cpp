#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0045BD80..0x0045BD86: FUN_0045bd80
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0045bd80_0045bd80() {
    __asm {
    L_0045bd80:
        push edi
    L_0045bd81:
        mov edi,dword ptr [esp+8]
    L_0045bd85:
        TH10_REL8(0xeb, 0x0045bd85, VA_asm_target_0045bdf5)
    }
}
