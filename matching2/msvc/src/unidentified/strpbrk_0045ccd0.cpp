#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0045CCD0..0x0045CD0F: _strpbrk
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_strpbrk_0045ccd0() {
    __asm {
    L_0045ccd0:
        push ebp
    L_0045ccd1:
        mov ebp,esp
    L_0045ccd3:
        push esi
    L_0045ccd4:
        xor eax,eax
    L_0045ccd6:
        push eax
    L_0045ccd7:
        push eax
    L_0045ccd8:
        push eax
    L_0045ccd9:
        push eax
    L_0045ccda:
        push eax
    L_0045ccdb:
        push eax
    L_0045ccdc:
        push eax
    L_0045ccdd:
        push eax
    L_0045ccde:
        mov edx,dword ptr [ebp+0Ch]
    L_0045cce1:
        TH10_NOP_LEA_ECX_DISP8()
    L_0045cce4:
        mov al,byte ptr [edx]
    L_0045cce6:
        or al,al
    L_0045cce8:
        je short L_0045ccf3
    L_0045ccea:
        add edx,1
    L_0045cced:
        bts dword ptr [esp],eax
    L_0045ccf1:
        jmp short L_0045cce4
    L_0045ccf3:
        mov esi,dword ptr [ebp+8]
    L_0045ccf6:
        mov edi,edi
    L_0045ccf8:
        mov al,byte ptr [esi]
    L_0045ccfa:
        or al,al
    L_0045ccfc:
        je short L_0045cd0a
    L_0045ccfe:
        add esi,1
    L_0045cd01:
        bt dword ptr [esp],eax
    L_0045cd05:
        jae short L_0045ccf8
    L_0045cd07:
        lea eax,[esi-1]
    L_0045cd0a:
        add esp,20h
    L_0045cd0d:
        pop esi
    L_0045cd0e:
        leave
    L_0045cd0f:
        ret
    }
}
