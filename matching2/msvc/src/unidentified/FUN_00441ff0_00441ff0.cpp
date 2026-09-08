#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00441FF0..0x00441FF4: FUN_00441ff0
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00441ff0_00441ff0() {
    __asm {
    L_00441ff0:
        mov ecx,dword ptr [eax]
    L_00441ff2:
        mov dword ptr [edx],ecx
    L_00441ff4:
        ret
    }
}
