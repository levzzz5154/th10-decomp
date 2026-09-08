#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0045F3C0..0x0045F3CF: FUN_0045f3c0
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0045f3c0_0045f3c0() {
    __asm {
    L_0045f3c0:
        mov ecx,dword ptr [esp+4]
    L_0045f3c4:
        mov eax,dword ptr [data_00477698]
    L_0045f3c9:
        mov dword ptr [data_00477698],ecx
    L_0045f3cf:
        ret
    }
}
