#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0040C480..0x0040C4C0: ?AnimationManager_StopAtFrame2@@
// Naked body preserves the retail register/stack ABI.

// 0x004423C0..0x004423D8: ?AnimationColor_MultiplyChannel@@
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_AnimationColor_MultiplyChannel_004423c0() {
    __asm {
    L_004423c0:
        movzx eax,al
    L_004423c3:
        movzx ecx,cl
    L_004423c6:
        imul eax,ecx
    L_004423c9:
        shr eax,7
    L_004423cc:
        cmp eax,100h
    L_004423d1:
        jb short L_004423d8
    L_004423d3:
        mov eax,0FFh
    L_004423d8:
        ret
    }
}
