#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00462E11..0x00462E5F: TypeMatch
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_TypeMatch_00462e11() {
    __asm {
    L_00462e11:
        mov eax,dword ptr [esi+4]
    L_00462e14:
        test eax,eax
    L_00462e16:
        je short L_00462e5c
    L_00462e18:
        lea edx,[eax+8]
    L_00462e1b:
        cmp byte ptr [edx],0
    L_00462e1e:
        je short L_00462e5c
    L_00462e20:
        mov ecx,dword ptr [edi+4]
    L_00462e23:
        cmp eax,ecx
    L_00462e25:
        je short L_00462e37
    L_00462e27:
        add ecx,8
    L_00462e2a:
        push ecx
    L_00462e2b:
        push edx
    L_00462e2c:
        call asm_strcmp_0045bf30
    L_00462e31:
        test eax,eax
    L_00462e33:
        pop ecx
    L_00462e34:
        pop ecx
    L_00462e35:
        jne short L_00462e59
    L_00462e37:
        test byte ptr [edi],2
    L_00462e3a:
        je short L_00462e41
    L_00462e3c:
        test byte ptr [esi],8
    L_00462e3f:
        je short L_00462e59
    L_00462e41:
        mov eax,dword ptr [esp+4]
    L_00462e45:
        mov eax,dword ptr [eax]
    L_00462e47:
        test al,1
    L_00462e49:
        je short L_00462e50
    L_00462e4b:
        test byte ptr [esi],1
    L_00462e4e:
        je short L_00462e59
    L_00462e50:
        test al,2
    L_00462e52:
        je short L_00462e5c
    L_00462e54:
        test byte ptr [esi],2
    L_00462e57:
        jne short L_00462e5c
    L_00462e59:
        xor eax,eax
    L_00462e5b:
        ret
    L_00462e5c:
        xor eax,eax
    L_00462e5e:
        inc eax
    L_00462e5f:
        ret
    }
}
