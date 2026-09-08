#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0045F655..0x0045F6D3: __free_osfhnd
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_free_osfhnd_0045f655() {
    __asm {
    L_0045f655:
        mov ecx,dword ptr [esp+4]
    L_0045f659:
        cmp ecx,dword ptr [data_004991e4]
    L_0045f65f:
        push esi
    L_0045f660:
        push edi
    L_0045f661:
        jae short L_0045f6bb
    L_0045f663:
        mov eax,ecx
    L_0045f665:
        sar eax,5
    L_0045f668:
        lea edi,[eax*4+499200h]
    L_0045f66f:
        mov eax,ecx
    L_0045f671:
        and eax,1Fh
    L_0045f674:
        lea esi,[eax+eax*8]
    L_0045f677:
        mov eax,dword ptr [edi]
    L_0045f679:
        shl esi,2
    L_0045f67c:
        add eax,esi
    L_0045f67e:
        test byte ptr [eax+4],1
    L_0045f682:
        je short L_0045f6bb
    L_0045f684:
        cmp dword ptr [eax],0FFFFFFFFh
    L_0045f687:
        je short L_0045f6bb
    L_0045f689:
        cmp dword ptr [data_00473074],1
    L_0045f690:
        jne short L_0045f6b1
    L_0045f692:
        xor eax,eax
    L_0045f694:
        sub ecx,eax
    L_0045f696:
        je short L_0045f6a8
    L_0045f698:
        dec ecx
    L_0045f699:
        je short L_0045f6a3
    L_0045f69b:
        dec ecx
    L_0045f69c:
        jne short L_0045f6b1
    L_0045f69e:
        push eax
    L_0045f69f:
        push 0FFFFFFF4h
    L_0045f6a1:
        jmp short L_0045f6ab
    L_0045f6a3:
        push eax
    L_0045f6a4:
        push 0FFFFFFF5h
    L_0045f6a6:
        jmp short L_0045f6ab
    L_0045f6a8:
        push eax
    L_0045f6a9:
        push 0FFFFFFF6h
    L_0045f6ab:
        call dword ptr [data_004661bc]
    L_0045f6b1:
        mov eax,dword ptr [edi]
    L_0045f6b3:
        or dword ptr [esi+eax],0FFFFFFFFh
    L_0045f6b7:
        xor eax,eax
    L_0045f6b9:
        jmp short L_0045f6d1
    L_0045f6bb:
        call asm_FUN_00456af2_00456af2
    L_0045f6c0:
        mov dword ptr [eax],9
    L_0045f6c6:
        call asm_FUN_00456afb_00456afb
    L_0045f6cb:
        and dword ptr [eax],0
    L_0045f6ce:
        or eax,0FFFFFFFFh
    L_0045f6d1:
        pop edi
    L_0045f6d2:
        pop esi
    L_0045f6d3:
        ret
    }
}
