#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00456640..0x00456673: __allmul
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_allmul_00456640() {
    __asm {
    L_00456640:
        mov eax,dword ptr [esp+8]
    L_00456644:
        mov ecx,dword ptr [esp+10h]
    L_00456648:
        or ecx,eax
    L_0045664a:
        mov ecx,dword ptr [esp+0Ch]
    L_0045664e:
        jne short L_00456659
    L_00456650:
        mov eax,dword ptr [esp+4]
    L_00456654:
        mul ecx
    L_00456656:
        ret 10h
    L_00456659:
        push ebx
    L_0045665a:
        mul ecx
    L_0045665c:
        mov ebx,eax
    L_0045665e:
        mov eax,dword ptr [esp+8]
    L_00456662:
        mul dword ptr [esp+14h]
    L_00456666:
        add ebx,eax
    L_00456668:
        mov eax,dword ptr [esp+8]
    L_0045666c:
        mul ecx
    L_0045666e:
        add edx,ebx
    L_00456670:
        pop ebx
    L_00456671:
        ret 10h
    }
}
