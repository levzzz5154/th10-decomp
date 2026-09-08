#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x004494C0..0x004494CE: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_004494c0() {
    __asm {
    L_004494c0:
        mov ecx,dword ptr [eax]
    L_004494c2:
        mov edx,dword ptr [data_00491c10]
    L_004494c8:
        push ecx
    L_004494c9:
        call asm_AnimationManager_SetStopFrameAndRun_00449250
    L_004494ce:
        ret
    }
}
