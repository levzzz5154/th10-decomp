#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x004524A6..0x004524FC: _vsprintf
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_vsprintf_004524a6() {
    __asm {
    L_004524a6:
        push ebp
    L_004524a7:
        mov ebp,esp
    L_004524a9:
        sub esp,20h
    L_004524ac:
        push esi
    L_004524ad:
        mov esi,dword ptr [ebp+8]
    L_004524b0:
        push edi
    L_004524b1:
        push dword ptr [ebp+10h]
    L_004524b4:
        lea eax,[ebp-20h]
    L_004524b7:
        push dword ptr [ebp+0Ch]
    L_004524ba:
        mov dword ptr [ebp-1Ch],7FFFFFFFh
    L_004524c1:
        push eax
    L_004524c2:
        mov dword ptr [ebp-14h],42h
    L_004524c9:
        mov dword ptr [ebp-18h],esi
    L_004524cc:
        mov dword ptr [ebp-20h],esi
    L_004524cf:
        call asm_FUN_00454ed7_00454ed7
    L_004524d4:
        add esp,0Ch
    L_004524d7:
        test esi,esi
    L_004524d9:
        mov edi,eax
    L_004524db:
        je short L_004524f7
    L_004524dd:
        dec dword ptr [ebp-1Ch]
    L_004524e0:
        js short L_004524ea
    L_004524e2:
        mov eax,dword ptr [ebp-20h]
    L_004524e5:
        mov byte ptr [eax],0
    L_004524e8:
        jmp short L_004524f7
    L_004524ea:
        lea eax,[ebp-20h]
    L_004524ed:
        push eax
    L_004524ee:
        push 0
    L_004524f0:
        call asm_flsbuf_00454d11
    L_004524f5:
        pop ecx
    L_004524f6:
        pop ecx
    L_004524f7:
        mov eax,edi
    L_004524f9:
        pop edi
    L_004524fa:
        pop esi
    L_004524fb:
        leave
    L_004524fc:
        ret
    }
}
