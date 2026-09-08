#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0043A700..0x0043A724: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_0043a700() {
    __asm {
    L_0043a700:
        push ecx
    L_0043a701:
        mov eax,dword ptr [esp+8]
    L_0043a705:
        mov ecx,eax
    L_0043a707:
        mov edx,eax
    L_0043a709:
        shr ecx,18h
    L_0043a70c:
        shr edx,10h
    L_0043a70f:
        mov byte ptr [esp],cl
    L_0043a712:
        mov byte ptr [esp+1],dl
    L_0043a716:
        mov byte ptr [esp+2],ah
    L_0043a71a:
        mov byte ptr [esp+3],al
    L_0043a71e:
        mov eax,dword ptr [esp]
    L_0043a721:
        pop ecx
    L_0043a722:
        ret 4
    }
}
