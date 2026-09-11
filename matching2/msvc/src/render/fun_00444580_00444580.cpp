#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00438A60..0x00438ACE: FUN_00438a60
// Naked body preserves the retail register/stack ABI.

// 0x00444580..0x004445BB: FUN_00444580
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00444580_00444580() {
    __asm {
    L_00444580:
        push edi
    L_00444581:
        mov eax,esi
    L_00444583:
        call asm_FUN_00444240_00444240
    L_00444588:
        push 0
    L_0044458a:
        mov eax,esi
    L_0044458c:
        mov ecx,edi
    L_0044458e:
        call asm_FUN_00442670_00442670
    L_00444593:
        mov dword ptr [data_00497920],3F800000h
    L_0044459d:
        mov dword ptr [data_00497904],3F800000h
    L_004445a7:
        mov dword ptr [data_004978e8],3F800000h
    L_004445b1:
        mov dword ptr [data_004978cc],3F800000h
    L_004445bb:
        ret
    }
}
