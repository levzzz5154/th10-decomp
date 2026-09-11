#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x004349E0..0x00434A1A: ?StageText_SkipLine@@
// Naked body preserves the retail register/stack ABI.

// 0x004349E0..0x00434A1A: ?StageText_SkipLine@@
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_StageText_SkipLine_004349e0() {
    __asm {
    L_004349e0:
        mov cl,byte ptr [eax]
    L_004349e2:
        cmp cl,0Ah
    L_004349e5:
        je short L_004349fd
    L_004349e7:
        cmp cl,0Dh
    L_004349ea:
        je short L_004349fd
    L_004349ec:
        mov ecx,dword ptr [edx]
    L_004349ee:
        test ecx,ecx
    L_004349f0:
        je short L_00434a1a
    L_004349f2:
        inc eax
    L_004349f3:
        dec ecx
    L_004349f4:
        mov dword ptr [edx],ecx
    L_004349f6:
        mov cl,byte ptr [eax]
    L_004349f8:
        cmp cl,0Ah
    L_004349fb:
        jne short L_004349e7
    L_004349fd:
        cmp dword ptr [edx],0
    L_00434a00:
        je short L_00434a1a
    L_00434a02:
        mov cl,byte ptr [eax]
    L_00434a04:
        cmp cl,0Ah
    L_00434a07:
        je short L_00434a0e
    L_00434a09:
        cmp cl,0Dh
    L_00434a0c:
        jne short L_00434a1a
    L_00434a0e:
        mov ecx,dword ptr [edx]
    L_00434a10:
        test ecx,ecx
    L_00434a12:
        je short L_00434a1a
    L_00434a14:
        inc eax
    L_00434a15:
        dec ecx
    L_00434a16:
        mov dword ptr [edx],ecx
    L_00434a18:
        jmp short L_00434a02
    L_00434a1a:
        ret
    }
}
