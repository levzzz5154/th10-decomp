#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x004200D0..0x004200F6: FUN_004200d0
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_004200d0_004200d0() {
    __asm {
    L_004200d0:
        push esi
    L_004200d1:
        mov esi,dword ptr [data_00491c10]
    L_004200d7:
        call asm_AnimationManager_FlushQuadBatch_00442f50
    L_004200dc:
        mov dword ptr [data_00491e64],0
    L_004200e6:
        mov dword ptr [data_00491e68],0
    L_004200f0:
        mov eax,1
    L_004200f5:
        pop esi
    L_004200f6:
        ret
    }
}
