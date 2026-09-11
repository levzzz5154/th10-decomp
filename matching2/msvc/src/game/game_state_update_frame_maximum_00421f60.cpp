#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00420C00..0x00420C28: ?GameState_DispatchDummy@@
// Naked body preserves the retail register/stack ABI.

// 0x00421F60..0x00421F7B: ?GameState_UpdateFrameMaximum@@
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_GameState_UpdateFrameMaximum_00421f60() {
    __asm {
    L_00421f60:
        mov ecx,dword ptr [data_00474c44]
    L_00421f66:
        mov dword ptr [eax+9E78h],ecx
    L_00421f6c:
        mov eax,ecx
    L_00421f6e:
        cmp dword ptr [data_00474c40],eax
    L_00421f74:
        jge short L_00421f7b
    L_00421f76:
        mov dword ptr [data_00474c40],eax
    L_00421f7b:
        ret
    }
}
