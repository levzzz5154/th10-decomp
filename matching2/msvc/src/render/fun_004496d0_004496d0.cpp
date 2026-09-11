#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0040C480..0x0040C4C0: ?AnimationManager_StopAtFrame2@@
// Naked body preserves the retail register/stack ABI.

// 0x004496D0..0x004496F3: FUN_004496d0
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_004496d0_004496d0() {
    __asm {
    L_004496d0:
        mov ecx,dword ptr [eax]
    L_004496d2:
        mov edx,dword ptr [data_00491c10]
    L_004496d8:
        push ecx
    L_004496d9:
        call asm_AnimationManager_Find_004491c0
    L_004496de:
        test eax,eax
    L_004496e0:
        je short L_004496f1
    L_004496e2:
        mov ecx,dword ptr [esp+4]
    L_004496e6:
        mov edx,dword ptr [eax+308h]
    L_004496ec:
        call asm_AnimationObject_ChangeScript_0043e8b0
    L_004496f1:
        ret 4
    }
}
