#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0045F3A4..0x0045F3B3: FUN_0045f3a4
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0045f3a4_0045f3a4() {
    __asm {
    L_0045f3a4:
        mov ecx,dword ptr [esp+4]
    L_0045f3a8:
        mov eax,dword ptr [data_00477698]
    L_0045f3ad:
        mov dword ptr [data_00477698],ecx
    L_0045f3b3:
        ret
    }
}
