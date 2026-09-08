#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0042AB20..0x0042AB7C: FUN_0042ab20
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0042ab20_0042ab20() {
    __asm {
    L_0042ab20:
        lea eax,[eax+eax*2]
    L_0042ab23:
        mov eax,dword ptr [ecx+eax*4+40h]
    L_0042ab27:
        push edi
    L_0042ab28:
        xor edi,edi
    L_0042ab2a:
        cmp eax,edi
    L_0042ab2c:
        je short L_0042ab7b
    L_0042ab2e:
        push esi
    L_0042ab2f:
        nop
    L_0042ab30:
        mov esi,dword ptr [eax+4]
    L_0042ab33:
        mov eax,dword ptr [eax]
    L_0042ab35:
        cmp eax,edi
    L_0042ab37:
        je short L_0042ab74
    L_0042ab39:
        mov ecx,dword ptr [eax+627Ch]
    L_0042ab3f:
        cmp ecx,edi
    L_0042ab41:
        je short L_0042ab4c
    L_0042ab43:
        mov edx,dword ptr [eax+6280h]
    L_0042ab49:
        mov dword ptr [ecx+8],edx
    L_0042ab4c:
        mov ecx,dword ptr [eax+6280h]
    L_0042ab52:
        cmp ecx,edi
    L_0042ab54:
        je short L_0042ab5f
    L_0042ab56:
        mov edx,dword ptr [eax+627Ch]
    L_0042ab5c:
        mov dword ptr [ecx+4],edx
    L_0042ab5f:
        push eax
    L_0042ab60:
        mov dword ptr [eax+627Ch],edi
    L_0042ab66:
        mov dword ptr [eax+6280h],edi
    L_0042ab6c:
        call asm_free_004524a1
    L_0042ab71:
        add esp,4
    L_0042ab74:
        cmp esi,edi
    L_0042ab76:
        mov eax,esi
    L_0042ab78:
        jne short L_0042ab30
    L_0042ab7a:
        pop esi
    L_0042ab7b:
        pop edi
    L_0042ab7c:
        ret
    }
}
