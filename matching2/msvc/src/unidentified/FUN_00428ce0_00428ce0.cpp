#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00428CE0..0x00428D2F: FUN_00428ce0
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00428ce0_00428ce0() {
    __asm {
    L_00428ce0:
        fld dword ptr [esp+4]
    L_00428ce4:
        fsub dword ptr [esp+8]
    L_00428ce8:
        fcom dword ptr [data_00470b18]
    L_00428cee:
        fnstsw ax
    L_00428cf0:
        test ah,41h
    L_00428cf3:
        jne short L_00428d08
    L_00428cf5:
        fstp st(0)
    L_00428cf7:
        fld dword ptr [esp+8]
    L_00428cfb:
        fadd dword ptr [data_00470b14]
    L_00428d01:
        fsubr dword ptr [esp+4]
    L_00428d05:
        ret 8
    L_00428d08:
        fld dword ptr [esp+8]
    L_00428d0c:
        fsub dword ptr [esp+4]
    L_00428d10:
        fcomp dword ptr [data_00470b18]
    L_00428d16:
        fnstsw ax
    L_00428d18:
        test ah,41h
    L_00428d1b:
        jne short L_00428d2d
    L_00428d1d:
        fstp st(0)
    L_00428d1f:
        fld dword ptr [esp+8]
    L_00428d23:
        fsub dword ptr [data_00470b14]
    L_00428d29:
        fsubr dword ptr [esp+4]
    L_00428d2d:
        ret 8
    }
}
