#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00460636..0x00460673: xtoa
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_xtoa_00460636() {
    __asm {
    L_00460636:
        cmp dword ptr [esp+8],0
    L_0046063b:
        je short L_00460643
    L_0046063d:
        mov byte ptr [ecx],2Dh
    L_00460640:
        inc ecx
    L_00460641:
        neg eax
    L_00460643:
        push esi
    L_00460644:
        mov esi,ecx
    L_00460646:
        xor edx,edx
    L_00460648:
        div dword ptr [esp+8]
    L_0046064c:
        cmp edx,9
    L_0046064f:
        jbe short L_00460656
    L_00460651:
        add dl,57h
    L_00460654:
        jmp short L_00460659
    L_00460656:
        add dl,30h
    L_00460659:
        mov byte ptr [ecx],dl
    L_0046065b:
        inc ecx
    L_0046065c:
        test eax,eax
    L_0046065e:
        ja short L_00460646
    L_00460660:
        mov byte ptr [ecx],0
    L_00460663:
        dec ecx
    L_00460664:
        mov dl,byte ptr [esi]
    L_00460666:
        mov al,byte ptr [ecx]
    L_00460668:
        mov byte ptr [ecx],dl
    L_0046066a:
        dec ecx
    L_0046066b:
        mov byte ptr [esi],al
    L_0046066d:
        inc esi
    L_0046066e:
        cmp esi,ecx
    L_00460670:
        jb short L_00460664
    L_00460672:
        pop esi
    L_00460673:
        ret
    }
}
