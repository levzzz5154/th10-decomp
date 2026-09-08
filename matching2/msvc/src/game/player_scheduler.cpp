#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00405BE0..0x00405C7D: Player_ResetSchedulerLinksRetail
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_Player_ResetSchedulerLinksRetail_00405be0() {
    __asm {
    L_00405be0:
        xor edx,edx
    L_00405be2:
        mov word ptr [eax+446h],dx
    L_00405be9:
        mov ecx,dword ptr [eax+408h]
    L_00405bef:
        test cl,1
    L_00405bf2:
        jne short L_00405c1d
    L_00405bf4:
        or ecx,1
    L_00405bf7:
        mov dword ptr [eax+3FCh],edx
    L_00405bfd:
        mov dword ptr [eax+3F8h],0FFF0BDC1h
    L_00405c07:
        mov dword ptr [eax+400h],edx
    L_00405c0d:
        mov dword ptr [eax+404h],476F78h
    L_00405c17:
        mov dword ptr [eax+408h],ecx
    L_00405c1d:
        mov dword ptr [eax+3FCh],edx
    L_00405c23:
        mov dword ptr [eax+400h],edx
    L_00405c29:
        mov dword ptr [eax+3F8h],0FFFFFFFFh
    L_00405c33:
        mov ecx,dword ptr [eax+41Ch]
    L_00405c39:
        test cl,1
    L_00405c3c:
        jne short L_00405c67
    L_00405c3e:
        or ecx,1
    L_00405c41:
        mov dword ptr [eax+410h],edx
    L_00405c47:
        mov dword ptr [eax+40Ch],0FFF0BDC1h
    L_00405c51:
        mov dword ptr [eax+414h],edx
    L_00405c57:
        mov dword ptr [eax+418h],476F78h
    L_00405c61:
        mov dword ptr [eax+41Ch],ecx
    L_00405c67:
        mov dword ptr [eax+410h],edx
    L_00405c6d:
        mov dword ptr [eax+414h],edx
    L_00405c73:
        mov dword ptr [eax+40Ch],0FFFFFFFFh
    L_00405c7d:
        ret
    }
}
