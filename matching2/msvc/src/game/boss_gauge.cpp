#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00428C20..0x00428C9C: FUN_00428c20
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00428c20_00428c20() {
    __asm {
    L_00428c20:
        sub esp,0Ch
    L_00428c23:
        push esi
    L_00428c24:
        mov esi,dword ptr [edx+58h]
    L_00428c27:
        movsx eax,byte ptr [esi+1Ch]
    L_00428c2b:
        imul eax,98h
    L_00428c31:
        fild dword ptr [eax+ecx+3244h]
    L_00428c38:
        fmul dword ptr [data_00470b00]
    L_00428c3e:
        fstp dword ptr [esp+4]
    L_00428c42:
        fild dword ptr [eax+ecx+3248h]
    L_00428c49:
        lea eax,[eax+ecx+3244h]
    L_00428c50:
        push edi
    L_00428c51:
        mov edi,dword ptr [esp+8]
    L_00428c55:
        fmul dword ptr [data_00470b00]
    L_00428c5b:
        lea eax,[edx+14h]
    L_00428c5e:
        mov ecx,eax
    L_00428c60:
        mov dword ptr [ecx],edi
    L_00428c62:
        fstp dword ptr [esp+0Ch]
    L_00428c66:
        mov edi,dword ptr [esp+0Ch]
    L_00428c6a:
        mov dword ptr [ecx+4],edi
    L_00428c6d:
        mov dword ptr [esp+10h],0
    L_00428c75:
        mov edi,dword ptr [esp+10h]
    L_00428c79:
        mov dword ptr [ecx+8],edi
    L_00428c7c:
        pop edi
    L_00428c7d:
        fld dword ptr [esi+4]
    L_00428c80:
        pop esi
    L_00428c81:
        fsub dword ptr [edx+20h]
    L_00428c84:
        fadd dword ptr [eax]
    L_00428c86:
        fstp dword ptr [eax]
    L_00428c88:
        mov eax,dword ptr [edx+58h]
    L_00428c8b:
        fld dword ptr [eax+8]
    L_00428c8e:
        xor eax,eax
    L_00428c90:
        fsub dword ptr [edx+24h]
    L_00428c93:
        fadd dword ptr [edx+18h]
    L_00428c96:
        fstp dword ptr [edx+18h]
    L_00428c99:
        add esp,0Ch
    L_00428c9c:
        ret
    }
}

// 0x00428E10..0x00428E62: FUN_00428e10
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00428e10_00428e10() {
    __asm {
    L_00428e10:
        mov edx,dword ptr [ecx]
    L_00428e12:
        mov dword ptr [eax+3CCh],edx
    L_00428e18:
        mov ecx,dword ptr [ecx+4]
    L_00428e1b:
        mov dword ptr [eax+3D0h],ecx
    L_00428e21:
        fild dword ptr [eax+3CCh]
    L_00428e27:
        mov ecx,1
    L_00428e2c:
        fmul dword ptr [data_00470b00]
    L_00428e32:
        fstp dword ptr [eax+3C0h]
    L_00428e38:
        fild dword ptr [eax+3D0h]
    L_00428e3e:
        fmul dword ptr [data_00470b00]
    L_00428e44:
        fstp dword ptr [eax+3C4h]
    L_00428e4a:
        mov dword ptr [eax+332Ch],ecx
    L_00428e50:
        mov dword ptr [eax+33C4h],ecx
    L_00428e56:
        mov dword ptr [eax+345Ch],ecx
    L_00428e5c:
        mov dword ptr [eax+34F4h],ecx
    L_00428e62:
        ret
    }
}
