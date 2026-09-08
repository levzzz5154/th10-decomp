#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0045A1B0..0x0045A244: __aulldvrm
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_aulldvrm_0045a1b0() {
    __asm {
    L_0045a1b0:
        push esi
    L_0045a1b1:
        mov eax,dword ptr [esp+14h]
    L_0045a1b5:
        or eax,eax
    L_0045a1b7:
        jne short L_0045a1e1
    L_0045a1b9:
        mov ecx,dword ptr [esp+10h]
    L_0045a1bd:
        mov eax,dword ptr [esp+0Ch]
    L_0045a1c1:
        xor edx,edx
    L_0045a1c3:
        div ecx
    L_0045a1c5:
        mov ebx,eax
    L_0045a1c7:
        mov eax,dword ptr [esp+8]
    L_0045a1cb:
        div ecx
    L_0045a1cd:
        mov esi,eax
    L_0045a1cf:
        mov eax,ebx
    L_0045a1d1:
        mul dword ptr [esp+10h]
    L_0045a1d5:
        mov ecx,eax
    L_0045a1d7:
        mov eax,esi
    L_0045a1d9:
        mul dword ptr [esp+10h]
    L_0045a1dd:
        add edx,ecx
    L_0045a1df:
        jmp short L_0045a228
    L_0045a1e1:
        mov ecx,eax
    L_0045a1e3:
        mov ebx,dword ptr [esp+10h]
    L_0045a1e7:
        mov edx,dword ptr [esp+0Ch]
    L_0045a1eb:
        mov eax,dword ptr [esp+8]
    L_0045a1ef:
        shr ecx,1
    L_0045a1f1:
        rcr ebx,1
    L_0045a1f3:
        shr edx,1
    L_0045a1f5:
        rcr eax,1
    L_0045a1f7:
        or ecx,ecx
    L_0045a1f9:
        jne short L_0045a1ef
    L_0045a1fb:
        div ebx
    L_0045a1fd:
        mov esi,eax
    L_0045a1ff:
        mul dword ptr [esp+14h]
    L_0045a203:
        mov ecx,eax
    L_0045a205:
        mov eax,dword ptr [esp+10h]
    L_0045a209:
        mul esi
    L_0045a20b:
        add edx,ecx
    L_0045a20d:
        jb short L_0045a21d
    L_0045a20f:
        cmp edx,dword ptr [esp+0Ch]
    L_0045a213:
        ja short L_0045a21d
    L_0045a215:
        jb short L_0045a226
    L_0045a217:
        cmp eax,dword ptr [esp+8]
    L_0045a21b:
        jbe short L_0045a226
    L_0045a21d:
        dec esi
    L_0045a21e:
        sub eax,dword ptr [esp+10h]
    L_0045a222:
        sbb edx,dword ptr [esp+14h]
    L_0045a226:
        xor ebx,ebx
    L_0045a228:
        sub eax,dword ptr [esp+8]
    L_0045a22c:
        sbb edx,dword ptr [esp+0Ch]
    L_0045a230:
        neg edx
    L_0045a232:
        neg eax
    L_0045a234:
        sbb edx,0
    L_0045a237:
        mov ecx,edx
    L_0045a239:
        mov edx,ebx
    L_0045a23b:
        mov ebx,ecx
    L_0045a23d:
        mov ecx,eax
    L_0045a23f:
        mov eax,esi
    L_0045a241:
        pop esi
    L_0045a242:
        ret 10h
    }
}
