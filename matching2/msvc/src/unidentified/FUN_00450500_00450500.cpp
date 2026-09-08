#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00450500..0x00450558: FUN_00450500
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00450500_00450500() {
    __asm {
    L_00450500:
        push esi
    L_00450501:
        push 103Ch
    L_00450506:
        call asm_operator_new_00452493
    L_0045050b:
        add esp,4
    L_0045050e:
        test eax,eax
    L_00450510:
        je short L_00450530
    L_00450512:
        mov dword ptr [eax],46D0D8h
    L_00450518:
        mov dword ptr [eax+1010h],0
    L_00450522:
        mov dword ptr [eax+1014h],0
    L_0045052c:
        mov esi,eax
    L_0045052e:
        jmp short L_00450532
    L_00450530:
        xor esi,esi
    L_00450532:
        mov eax,dword ptr [esp+8]
    L_00450536:
        push eax
    L_00450537:
        mov eax,edi
    L_00450539:
        mov dword ptr [esi+102Ch],edi
    L_0045053f:
        call asm_FUN_00450470_00450470
    L_00450544:
        mov ecx,dword ptr [esi+4]
    L_00450547:
        mov dword ptr [ecx+4],eax
    L_0045054a:
        mov edx,dword ptr [esi+4]
    L_0045054d:
        mov eax,esi
    L_0045054f:
        mov dword ptr [edx],0
    L_00450555:
        pop esi
    L_00450556:
        ret 4
    }
}
