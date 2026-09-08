#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00456AC4..0x00456AD3: FUN_00456ac4
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00456ac4_00456ac4() {
    __asm {
    L_00456ac4:
        mov ecx,dword ptr [esp+4]
    L_00456ac8:
        mov eax,dword ptr [data_00477384]
    L_00456acd:
        mov dword ptr [data_00477384],ecx
    L_00456ad3:
        ret
    }
}
