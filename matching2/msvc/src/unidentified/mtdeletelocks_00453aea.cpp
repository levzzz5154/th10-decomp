#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00453AEA..0x00453B3E: __mtdeletelocks
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_mtdeletelocks_00453aea() {
    __asm {
    L_00453aea:
        push ebx
    L_00453aeb:
        mov ebx,dword ptr [data_004660bc]
    L_00453af1:
        push esi
    L_00453af2:
        mov esi,473080h
    L_00453af7:
        push edi
    L_00453af8:
        mov edi,dword ptr [esi]
    L_00453afa:
        test edi,edi
    L_00453afc:
        je short L_00453b11
    L_00453afe:
        cmp dword ptr [esi+4],1
    L_00453b02:
        je short L_00453b11
    L_00453b04:
        push edi
    L_00453b05:
        call ebx
    L_00453b07:
        push edi
    L_00453b08:
        call asm_free_00452422
    L_00453b0d:
        and dword ptr [esi],0
    L_00453b10:
        pop ecx
    L_00453b11:
        add esi,8
    L_00453b14:
        cmp esi,4731A0h
    L_00453b1a:
        jl short L_00453af8
    L_00453b1c:
        mov esi,473080h
    L_00453b21:
        pop edi
    L_00453b22:
        mov eax,dword ptr [esi]
    L_00453b24:
        test eax,eax
    L_00453b26:
        je short L_00453b31
    L_00453b28:
        cmp dword ptr [esi+4],1
    L_00453b2c:
        jne short L_00453b31
    L_00453b2e:
        push eax
    L_00453b2f:
        call ebx
    L_00453b31:
        add esi,8
    L_00453b34:
        cmp esi,4731A0h
    L_00453b3a:
        jl short L_00453b22
    L_00453b3c:
        pop esi
    L_00453b3d:
        pop ebx
    L_00453b3e:
        ret
    }
}
