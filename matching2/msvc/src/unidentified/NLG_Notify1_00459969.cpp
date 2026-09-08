#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00459969..0x00459971: __NLG_Notify1
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_NLG_Notify1_00459969() {
    __asm {
    L_00459969:
        push ebx
    L_0045996a:
        push ecx
    L_0045996b:
        mov ebx,47372Ch
    L_00459970:
        TH10_REL8(0xeb, 0x00459970, VA_asm_target_0045997c)
    }
}
