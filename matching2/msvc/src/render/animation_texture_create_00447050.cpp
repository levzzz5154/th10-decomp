#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0040C480..0x0040C4C0: ?AnimationManager_StopAtFrame2@@
// Naked body preserves the retail register/stack ABI.

// 0x00447050..0x00447078: ?AnimationTexture_Create@@
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_AnimationTexture_Create_00447050() {
    __asm {
    L_00447050:
        mov eax,dword ptr [esi*4+46F288h]
    L_00447057:
        push edi
    L_00447058:
        push 1
    L_0044705a:
        push eax
    L_0044705b:
        mov eax,dword ptr [data_00491c30]
    L_00447060:
        push 0
    L_00447062:
        push 1
    L_00447064:
        push ecx
    L_00447065:
        push edx
    L_00447066:
        push eax
    L_00447067:
        call asm_D3DXCreateTexture_004521a0
    L_0044706c:
        mov ecx,dword ptr [esi*4+46F2A0h]
    L_00447073:
        mov dword ptr [edi+0Ch],ecx
    L_00447076:
        xor eax,eax
    L_00447078:
        ret
    }
}
