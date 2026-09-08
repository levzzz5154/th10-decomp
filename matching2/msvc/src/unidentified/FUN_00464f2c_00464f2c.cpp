#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00464F2C..0x00464F44: FUN_00464f2c
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00464f2c_00464f2c() {
    __asm {
    L_00464f2c:
        test eax,80000h
    L_00464f31:
        je short L_00464f39
    L_00464f33:
        mov eax,7
    L_00464f38:
        ret
    L_00464f39:
        fadd qword ptr [data_00470d90]
    L_00464f3f:
        mov eax,1
    L_00464f44:
        ret
    }
}
