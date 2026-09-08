#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0044C590..0x0044C5C8: FUN_0044c590
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0044c590_0044c590() {
    __asm {
    L_0044c590:
        fld dword ptr [esi]
    L_0044c592:
        sub esp,8
    L_0044c595:
        fmul dword ptr [data_00470b44]
    L_0044c59b:
        fstp qword ptr [esp]
    L_0044c59e:
        call asm_FUN_00452ff0_00452ff0
    L_0044c5a3:
        fmul dword ptr [data_00470b00]
    L_0044c5a9:
        fstp dword ptr [esi]
    L_0044c5ab:
        fld dword ptr [esi+4]
    L_0044c5ae:
        fmul dword ptr [data_00470b44]
    L_0044c5b4:
        fstp qword ptr [esp]
    L_0044c5b7:
        call asm_FUN_00452ff0_00452ff0
    L_0044c5bc:
        fmul dword ptr [data_00470b00]
    L_0044c5c2:
        add esp,8
    L_0044c5c5:
        fstp dword ptr [esi+4]
    L_0044c5c8:
        ret
    }
}
