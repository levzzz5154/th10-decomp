#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00404E10..0x00404E6B: ParticleSeed_Combine
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_ParticleSeed_Combine_00404e10() {
    __asm {
    L_00404e10:
        fld dword ptr [eax+14h]
    L_00404e13:
        fadd dword ptr [ecx+14h]
    L_00404e16:
        fld dword ptr [eax+10h]
    L_00404e19:
        fadd dword ptr [ecx+10h]
    L_00404e1c:
        fld dword ptr [eax+0Ch]
    L_00404e1f:
        fadd dword ptr [ecx+0Ch]
    L_00404e22:
        fld dword ptr [eax+8]
    L_00404e25:
        fadd dword ptr [ecx+8]
    L_00404e28:
        fld dword ptr [eax+4]
    L_00404e2b:
        fadd dword ptr [ecx+4]
    L_00404e2e:
        fld dword ptr [eax]
    L_00404e30:
        fadd dword ptr [ecx]
    L_00404e32:
        fstp dword ptr [esi]
    L_00404e34:
        fstp dword ptr [esi+4]
    L_00404e37:
        fst dword ptr [esi+8]
    L_00404e3a:
        fld st(1)
    L_00404e3c:
        fstp dword ptr [esi+0Ch]
    L_00404e3f:
        fld st(2)
    L_00404e41:
        fstp dword ptr [esi+10h]
    L_00404e44:
        fld st(3)
    L_00404e46:
        fstp dword ptr [esi+14h]
    L_00404e49:
        call asm_FUN_00463b2c_00463b2c
    L_00404e4e:
        mov byte ptr [esi+18h],al
    L_00404e51:
        call asm_FUN_00463b2c_00463b2c
    L_00404e56:
        mov byte ptr [esi+19h],al
    L_00404e59:
        call asm_FUN_00463b2c_00463b2c
    L_00404e5e:
        mov byte ptr [esi+1Ah],al
    L_00404e61:
        call asm_FUN_00463b2c_00463b2c
    L_00404e66:
        mov byte ptr [esi+1Bh],al
    L_00404e69:
        mov eax,esi
    L_00404e6b:
        ret
    }
}
