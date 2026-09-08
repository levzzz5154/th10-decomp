#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0045FBF6..0x0045FC52: __flush
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_flush_0045fbf6() {
    __asm {
    L_0045fbf6:
        push ebx
    L_0045fbf7:
        push esi
    L_0045fbf8:
        mov esi,dword ptr [esp+0Ch]
    L_0045fbfc:
        mov eax,dword ptr [esi+0Ch]
    L_0045fbff:
        mov ecx,eax
    L_0045fc01:
        and cl,3
    L_0045fc04:
        xor ebx,ebx
    L_0045fc06:
        cmp cl,2
    L_0045fc09:
        jne short L_0045fc45
    L_0045fc0b:
        test ax,108h
    L_0045fc0f:
        je short L_0045fc45
    L_0045fc11:
        mov eax,dword ptr [esi+8]
    L_0045fc14:
        push edi
    L_0045fc15:
        mov edi,dword ptr [esi]
    L_0045fc17:
        sub edi,eax
    L_0045fc19:
        test edi,edi
    L_0045fc1b:
        jle short L_0045fc44
    L_0045fc1d:
        push edi
    L_0045fc1e:
        push eax
    L_0045fc1f:
        push dword ptr [esi+10h]
    L_0045fc22:
        call asm_write_00459e8e
    L_0045fc27:
        add esp,0Ch
    L_0045fc2a:
        cmp eax,edi
    L_0045fc2c:
        jne short L_0045fc3d
    L_0045fc2e:
        mov eax,dword ptr [esi+0Ch]
    L_0045fc31:
        test al,al
    L_0045fc33:
        jns short L_0045fc44
    L_0045fc35:
        and eax,0FFFFFFFDh
    L_0045fc38:
        mov dword ptr [esi+0Ch],eax
    L_0045fc3b:
        jmp short L_0045fc44
    L_0045fc3d:
        or dword ptr [esi+0Ch],20h
    L_0045fc41:
        or ebx,0FFFFFFFFh
    L_0045fc44:
        pop edi
    L_0045fc45:
        mov eax,dword ptr [esi+8]
    L_0045fc48:
        and dword ptr [esi+4],0
    L_0045fc4c:
        mov dword ptr [esi],eax
    L_0045fc4e:
        pop esi
    L_0045fc4f:
        mov eax,ebx
    L_0045fc51:
        pop ebx
    L_0045fc52:
        ret
    }
}
