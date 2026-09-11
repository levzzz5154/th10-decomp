#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0040C480..0x0040C4C0: ?AnimationManager_StopAtFrame2@@
// Naked body preserves the retail register/stack ABI.

// 0x00449450..0x00449464: ?AnimationManager_ValidateHandle@@
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_AnimationManager_ValidateHandle_00449450() {
    __asm {
    L_00449450:
        mov eax,dword ptr [esi]
    L_00449452:
        mov edx,dword ptr [data_00491c10]
    L_00449458:
        push eax
    L_00449459:
        call asm_AnimationManager_Find_004491c0
    L_0044945e:
        test eax,eax
    L_00449460:
        jne short L_00449464
    L_00449462:
        mov dword ptr [esi],eax
    L_00449464:
        ret
    }
}
