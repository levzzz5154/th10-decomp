#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0043A9B0..0x0043AA23: FUN_0043a9b0
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0043a9b0_0043a9b0() {
    __asm {
    L_0043a9b0:
        push ebp
    L_0043a9b1:
        mov ebp,dword ptr [esp+8]
    L_0043a9b5:
        push edi
    L_0043a9b6:
        mov edi,eax
    L_0043a9b8:
        cmp dword ptr [edi+10h],esi
    L_0043a9bb:
        jne short L_0043a9c2
    L_0043a9bd:
        call asm_FUN_0043ae20_0043ae20
    L_0043a9c2:
        mov eax,dword ptr [edi+esi*4+98h]
    L_0043a9c9:
        test eax,eax
    L_0043a9cb:
        je short L_0043a9e1
    L_0043a9cd:
        push eax
    L_0043a9ce:
        call asm_free_00452422
    L_0043a9d3:
        add esp,4
    L_0043a9d6:
        mov dword ptr [edi+esi*4+98h],0
    L_0043a9e1:
        push 0
    L_0043a9e3:
        push 0
    L_0043a9e5:
        mov eax,ebp
    L_0043a9e7:
        mov dword ptr [edi+esi*4+98h],0
    L_0043a9f2:
        call asm_FUN_0044b360_0044b360
    L_0043a9f7:
        test eax,eax
    L_0043a9f9:
        mov dword ptr [edi+esi*4+98h],eax
    L_0043aa00:
        jne short L_0043aa1d
    L_0043aa02:
        push ebp
    L_0043aa03:
        push 46F908h
    L_0043aa08:
        mov ecx,474F70h
    L_0043aa0d:
        call asm_TextLog_Append_0044b810
    L_0043aa12:
        add esp,8
    L_0043aa15:
        pop edi
    L_0043aa16:
        or eax,0FFFFFFFFh
    L_0043aa19:
        pop ebp
    L_0043aa1a:
        ret 4
    L_0043aa1d:
        pop edi
    L_0043aa1e:
        xor eax,eax
    L_0043aa20:
        pop ebp
    L_0043aa21:
        ret 4
    }
}
