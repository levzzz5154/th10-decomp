#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00434C20..0x00434C29: ?DatArchive_Reset@@
// Naked body preserves the retail register/stack ABI.

// 0x00434EF0..0x00434F22: ?DatArchive_FindSize@@
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_DatArchive_FindSize_00434ef0() {
    __asm {
    L_00434ef0:
        push esi
    L_00434ef1:
        push edi
    L_00434ef2:
        mov edi,dword ptr [eax]
    L_00434ef4:
        test edi,edi
    L_00434ef6:
        je short L_00434f18
    L_00434ef8:
        mov esi,dword ptr [eax+4]
    L_00434efb:
        test esi,esi
    L_00434efd:
        jle short L_00434f18
    L_00434eff:
        nop
    L_00434f00:
        mov eax,dword ptr [edi]
    L_00434f02:
        push eax
    L_00434f03:
        push ebx
    L_00434f04:
        call asm_stricmp_0046054e
    L_00434f09:
        add esp,8
    L_00434f0c:
        test eax,eax
    L_00434f0e:
        je short L_00434f1d
    L_00434f10:
        dec esi
    L_00434f11:
        add edi,10h
    L_00434f14:
        test esi,esi
    L_00434f16:
        jg short L_00434f00
    L_00434f18:
        pop edi
    L_00434f19:
        xor eax,eax
    L_00434f1b:
        pop esi
    L_00434f1c:
        ret
    L_00434f1d:
        mov eax,dword ptr [edi+8]
    L_00434f20:
        pop edi
    L_00434f21:
        pop esi
    L_00434f22:
        ret
    }
}
