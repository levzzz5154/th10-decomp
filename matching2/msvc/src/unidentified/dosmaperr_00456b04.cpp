#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00456B04..0x00456B76: __dosmaperr
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_dosmaperr_00456b04() {
    __asm {
    L_00456b04:
        push esi
    L_00456b05:
        call asm_getptd_00456357
    L_00456b0a:
        mov ecx,dword ptr [esp+8]
    L_00456b0e:
        mov dword ptr [eax+0Ch],ecx
    L_00456b11:
        xor esi,esi
    L_00456b13:
        cmp ecx,dword ptr [esi*8+4733B8h]
    L_00456b1a:
        je short L_00456b3a
    L_00456b1c:
        inc esi
    L_00456b1d:
        cmp esi,2Dh
    L_00456b20:
        jb short L_00456b13
    L_00456b22:
        cmp ecx,13h
    L_00456b25:
        jb short L_00456b4b
    L_00456b27:
        cmp ecx,24h
    L_00456b2a:
        ja short L_00456b4b
    L_00456b2c:
        call asm_getptd_00456357
    L_00456b31:
        mov dword ptr [eax+8],0Dh
    L_00456b38:
        pop esi
    L_00456b39:
        ret
    L_00456b3a:
        call asm_getptd_00456357
    L_00456b3f:
        mov ecx,dword ptr [esi*8+4733BCh]
    L_00456b46:
        mov dword ptr [eax+8],ecx
    L_00456b49:
        pop esi
    L_00456b4a:
        ret
    L_00456b4b:
        cmp ecx,0BCh
    L_00456b51:
        jb short L_00456b69
    L_00456b53:
        cmp ecx,0CAh
    L_00456b59:
        ja short L_00456b69
    L_00456b5b:
        call asm_getptd_00456357
    L_00456b60:
        mov dword ptr [eax+8],8
    L_00456b67:
        pop esi
    L_00456b68:
        ret
    L_00456b69:
        call asm_getptd_00456357
    L_00456b6e:
        mov dword ptr [eax+8],16h
    L_00456b75:
        pop esi
    L_00456b76:
        ret
    }
}
