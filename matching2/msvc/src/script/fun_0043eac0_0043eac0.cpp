#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0043EAC0..0x0043EC0D: FUN_0043eac0
// Naked body preserves the retail register/stack ABI.

// 0x0043EAC0..0x0043EC0D: FUN_0043eac0
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0043eac0_0043eac0() {
    __asm {
    L_0043eac0:
        fld dword ptr [esp+4]
    L_0043eac4:
        call asm_FUN_00463b2c_00463b2c
    L_0043eac9:
        add eax,0FFFFD8F0h
    L_0043eace:
        cmp eax,15h
    L_0043ead1:
        ja asm_target_0043ec07
    L_0043ead7:
        jmp dword ptr [eax*4+43EC10h]
    L_0043eade:
        fild dword ptr [esi+30Ch]
    L_0043eae4:
        ret 4
    L_0043eae7:
        fild dword ptr [esi+310h]
    L_0043eaed:
        ret 4
    L_0043eaf0:
        fild dword ptr [esi+314h]
    L_0043eaf6:
        ret 4
    L_0043eaf9:
        fild dword ptr [esi+318h]
    L_0043eaff:
        ret 4
    L_0043eb02:
        fld dword ptr [esi+31Ch]
    L_0043eb08:
        ret 4
    L_0043eb0b:
        fld dword ptr [esi+320h]
    L_0043eb11:
        ret 4
    L_0043eb14:
        fld dword ptr [esi+324h]
    L_0043eb1a:
        ret 4
    L_0043eb1d:
        fld dword ptr [esi+328h]
    L_0043eb23:
        ret 4
    L_0043eb26:
        fild dword ptr [esi+32Ch]
    L_0043eb2c:
        ret 4
    L_0043eb2f:
        fild dword ptr [esi+330h]
    L_0043eb35:
        ret 4
    L_0043eb38:
        test dword ptr [esi+35Ch],40000000h
    L_0043eb42:
        je short L_0043eb51
    L_0043eb44:
        mov ecx,4918A8h
    L_0043eb49:
        call asm_Rng_NextFloat_0044bb20
    L_0043eb4e:
        ret 4
    L_0043eb51:
        mov ecx,4918B0h
    L_0043eb56:
        call asm_Rng_NextFloat_0044bb20
    L_0043eb5b:
        ret 4
    L_0043eb5e:
        test dword ptr [esi+35Ch],40000000h
    L_0043eb68:
        je short L_0043eb77
    L_0043eb6a:
        mov ecx,4918A8h
    L_0043eb6f:
        call asm_Rng_NextFloatSigned_0044bb90
    L_0043eb74:
        ret 4
    L_0043eb77:
        mov ecx,4918B0h
    L_0043eb7c:
        call asm_Rng_NextFloatSigned_0044bb90
    L_0043eb81:
        ret 4
    L_0043eb84:
        test dword ptr [esi+35Ch],40000000h
    L_0043eb8e:
        je short L_0043eba3
    L_0043eb90:
        mov ecx,4918A8h
    L_0043eb95:
        call asm_Rng_NextFloatSigned_0044bb90
    L_0043eb9a:
        fmul dword ptr [data_00470b18]
    L_0043eba0:
        ret 4
    L_0043eba3:
        mov ecx,4918B0h
    L_0043eba8:
        call asm_Rng_NextFloatSigned_0044bb90
    L_0043ebad:
        fmul dword ptr [data_00470b18]
    L_0043ebb3:
        ret 4
    L_0043ebb6:
        fld dword ptr [esi+334h]
    L_0043ebbc:
        ret 4
    L_0043ebbf:
        fld dword ptr [esi+338h]
    L_0043ebc5:
        ret 4
    L_0043ebc8:
        fld dword ptr [esi+33Ch]
    L_0043ebce:
        ret 4
    L_0043ebd1:
        fld dword ptr [data_00491d7c]
    L_0043ebd7:
        ret 4
    L_0043ebda:
        fld dword ptr [data_00491d80]
    L_0043ebe0:
        ret 4
    L_0043ebe3:
        fld dword ptr [data_00491d84]
    L_0043ebe9:
        ret 4
    L_0043ebec:
        fld dword ptr [data_00491da0]
    L_0043ebf2:
        ret 4
    L_0043ebf5:
        fld dword ptr [data_00491da4]
    L_0043ebfb:
        ret 4
    L_0043ebfe:
        fld dword ptr [data_00491da8]
    L_0043ec04:
        ret 4
    L_0043ec07:
        fld dword ptr [esp+4]
    L_0043ec0b:
        ret 4
        _emit 0x8b
        _emit 0xff
        _emit 0xde
        _emit 0xea
        _emit 0x43
        _emit 0x00
        _emit 0xe7
        _emit 0xea
        _emit 0x43
        _emit 0x00
        _emit 0xf0
        _emit 0xea
        _emit 0x43
        _emit 0x00
        _emit 0xf9
        _emit 0xea
        _emit 0x43
        _emit 0x00
        _emit 0x02
        _emit 0xeb
        _emit 0x43
        _emit 0x00
        _emit 0x0b
        _emit 0xeb
        _emit 0x43
        _emit 0x00
        _emit 0x14
        _emit 0xeb
        _emit 0x43
        _emit 0x00
        _emit 0x1d
        _emit 0xeb
        _emit 0x43
        _emit 0x00
        _emit 0x26
        _emit 0xeb
        _emit 0x43
        _emit 0x00
        _emit 0x2f
        _emit 0xeb
        _emit 0x43
        _emit 0x00
        _emit 0x84
        _emit 0xeb
        _emit 0x43
        _emit 0x00
        _emit 0x38
        _emit 0xeb
        _emit 0x43
        _emit 0x00
        _emit 0x5e
        _emit 0xeb
        _emit 0x43
        _emit 0x00
        _emit 0xb6
        _emit 0xeb
        _emit 0x43
        _emit 0x00
        _emit 0xbf
        _emit 0xeb
        _emit 0x43
        _emit 0x00
        _emit 0xc8
        _emit 0xeb
        _emit 0x43
        _emit 0x00
        _emit 0xd1
        _emit 0xeb
        _emit 0x43
        _emit 0x00
        _emit 0xda
        _emit 0xeb
        _emit 0x43
        _emit 0x00
        _emit 0xe3
        _emit 0xeb
        _emit 0x43
        _emit 0x00
        _emit 0xec
        _emit 0xeb
        _emit 0x43
        _emit 0x00
        _emit 0xf5
        _emit 0xeb
        _emit 0x43
        _emit 0x00
        _emit 0xfe
        _emit 0xeb
        _emit 0x43
        _emit 0x00
    }
}
