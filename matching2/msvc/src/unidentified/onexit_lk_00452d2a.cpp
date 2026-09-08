#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00452D2A..0x00452DA9: __onexit_lk
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_onexit_lk_00452d2a() {
    __asm {
    L_00452d2a:
        push esi
    L_00452d2b:
        push dword ptr [data_00499310]
    L_00452d31:
        call asm_msize_0045772c
    L_00452d36:
        pop ecx
    L_00452d37:
        mov ecx,dword ptr [data_0049930c]
    L_00452d3d:
        mov esi,eax
    L_00452d3f:
        mov eax,dword ptr [data_00499310]
    L_00452d44:
        mov edx,ecx
    L_00452d46:
        sub edx,eax
    L_00452d48:
        add edx,4
    L_00452d4b:
        cmp esi,edx
    L_00452d4d:
        jae short L_00452d9d
    L_00452d4f:
        mov ecx,800h
    L_00452d54:
        cmp esi,ecx
    L_00452d56:
        jae short L_00452d5a
    L_00452d58:
        mov ecx,esi
    L_00452d5a:
        add ecx,esi
    L_00452d5c:
        push ecx
    L_00452d5d:
        push eax
    L_00452d5e:
        call asm_FUN_00457395_00457395
    L_00452d63:
        test eax,eax
    L_00452d65:
        pop ecx
    L_00452d66:
        pop ecx
    L_00452d67:
        jne short L_00452d80
    L_00452d69:
        add esi,10h
    L_00452d6c:
        push esi
    L_00452d6d:
        push dword ptr [data_00499310]
    L_00452d73:
        call asm_FUN_00457395_00457395
    L_00452d78:
        test eax,eax
    L_00452d7a:
        pop ecx
    L_00452d7b:
        pop ecx
    L_00452d7c:
        jne short L_00452d80
    L_00452d7e:
        pop esi
    L_00452d7f:
        ret
    L_00452d80:
        mov ecx,dword ptr [data_0049930c]
    L_00452d86:
        sub ecx,dword ptr [data_00499310]
    L_00452d8c:
        mov dword ptr [data_00499310],eax
    L_00452d91:
        sar ecx,2
    L_00452d94:
        lea ecx,[eax+ecx*4]
    L_00452d97:
        mov dword ptr [data_0049930c],ecx
    L_00452d9d:
        mov dword ptr [ecx],edi
    L_00452d9f:
        add dword ptr [data_0049930c],4
    L_00452da6:
        mov eax,edi
    L_00452da8:
        pop esi
    L_00452da9:
        ret
    }
}
