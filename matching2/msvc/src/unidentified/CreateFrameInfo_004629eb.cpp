#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x004629EB..0x00462A12: _CreateFrameInfo
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_CreateFrameInfo_004629eb() {
    __asm {
    L_004629eb:
        mov eax,dword ptr [esp+8]
    L_004629ef:
        push esi
    L_004629f0:
        mov esi,dword ptr [esp+8]
    L_004629f4:
        mov dword ptr [esi],eax
    L_004629f6:
        call asm_getptd_00456357
    L_004629fb:
        mov eax,dword ptr [eax+88h]
    L_00462a01:
        mov dword ptr [esi+4],eax
    L_00462a04:
        call asm_getptd_00456357
    L_00462a09:
        mov dword ptr [eax+88h],esi
    L_00462a0f:
        mov eax,esi
    L_00462a11:
        pop esi
    L_00462a12:
        ret
    }
}
