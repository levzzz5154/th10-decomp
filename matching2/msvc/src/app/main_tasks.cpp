#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0041FF80..0x0041FFF0: FUN_0041ff80
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0041ff80_0041ff80() {
    __asm {
    L_0041ff80:
        push esi
    L_0041ff81:
        mov esi,ecx
    L_0041ff83:
        mov al,byte ptr [esi+3CCh]
    L_0041ff89:
        test al,al
    L_0041ff8b:
        jns short L_0041ffa1
    L_0041ff8d:
        mov eax,dword ptr [esi+63Ch]
    L_0041ff93:
        test eax,eax
    L_0041ff95:
        jne short L_0041ffa1
    L_0041ff97:
        mov dword ptr [data_00491fb8],3
    L_0041ffa1:
        mov eax,492590h
    L_0041ffa6:
        call asm_FUN_00421e00_00421e00
    L_0041ffab:
        xor ecx,ecx
    L_0041ffad:
        call asm_FUN_0044a5f0_0044a5f0
    L_0041ffb2:
        mov eax,dword ptr [data_00491c10]
    L_0041ffb7:
        push eax
    L_0041ffb8:
        call asm_AnmPending_ServiceRetail_00447700
    L_0041ffbd:
        test eax,eax
    L_0041ffbf:
        je short L_0041ffc8
    L_0041ffc1:
        mov eax,4
    L_0041ffc6:
        pop esi
    L_0041ffc7:
        ret
    L_0041ffc8:
        mov eax,dword ptr [esi+648h]
    L_0041ffce:
        test eax,eax
    L_0041ffd0:
        je short L_0041ffe3
    L_0041ffd2:
        xor ecx,ecx
    L_0041ffd4:
        cmp eax,2
    L_0041ffd7:
        setne cl
    L_0041ffda:
        pop esi
    L_0041ffdb:
        dec ecx
    L_0041ffdc:
        and ecx,3
    L_0041ffdf:
        inc ecx
    L_0041ffe0:
        mov eax,ecx
    L_0041ffe2:
        ret
    L_0041ffe3:
        mov eax,esi
    L_0041ffe5:
        call asm_FUN_004218d0_004218d0
    L_0041ffea:
        cmp eax,1
    L_0041ffed:
        jne short L_0041ffef
    L_0041ffef:
        pop esi
    L_0041fff0:
        ret
    }
}




