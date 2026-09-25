#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0043CB00..0x0043CB7E: ?Recovery_ReleaseRawPair@@
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_Recovery_ReleaseRawPair_0043cb00() {
    __asm {
    L_0043cb00:
        mov eax,dword ptr [esp+4]
    L_0043cb04:
        push ebx
    L_0043cb05:
        mov ebx,dword ptr [data_004660b0]
    L_0043cb0b:
        push ebp
    L_0043cb0c:
        mov ebp,dword ptr [data_004660b4]
    L_0043cb12:
        push esi
    L_0043cb13:
        mov esi,dword ptr [eax+8]
    L_0043cb16:
        test esi,esi
    L_0043cb18:
        push edi
    L_0043cb19:
        mov edi,dword ptr [data_00491be4]
    L_0043cb1f:
        je short L_0043cb44
    L_0043cb21:
        push 492274h
    L_0043cb26:
        call ebx
    L_0043cb28:
        inc byte ptr [data_0049231c]
    L_0043cb2e:
        mov ecx,esi
    L_0043cb30:
        mov edx,edi
    L_0043cb32:
        call asm_Scheduler_Remove_00449f60
    L_0043cb37:
        push 492274h
    L_0043cb3c:
        call ebp
    L_0043cb3e:
        dec byte ptr [data_0049231c]
    L_0043cb44:
        mov ecx,dword ptr [esp+14h]
    L_0043cb48:
        mov esi,dword ptr [ecx+0Ch]
    L_0043cb4b:
        test esi,esi
    L_0043cb4d:
        mov edi,dword ptr [data_00491be4]
    L_0043cb53:
        je short L_0043cb78
    L_0043cb55:
        push 492274h
    L_0043cb5a:
        call ebx
    L_0043cb5c:
        inc byte ptr [data_0049231c]
    L_0043cb62:
        mov ecx,esi
    L_0043cb64:
        mov edx,edi
    L_0043cb66:
        call asm_Scheduler_Remove_00449f60
    L_0043cb6b:
        push 492274h
    L_0043cb70:
        call ebp
    L_0043cb72:
        dec byte ptr [data_0049231c]
    L_0043cb78:
        pop edi
    L_0043cb79:
        pop esi
    L_0043cb7a:
        pop ebp
    L_0043cb7b:
        pop ebx
    L_0043cb7c:
        ret 4
    }
}
