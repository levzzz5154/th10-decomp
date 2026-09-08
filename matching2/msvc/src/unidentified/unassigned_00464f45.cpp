#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00464F45..0x00464F87: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00464f45() {
    __asm {
    L_00464f45:
        mov eax,dword ptr [edx+4]
    L_00464f48:
        and eax,7FF00000h
    L_00464f4d:
        cmp eax,7FF00000h
    L_00464f52:
        je short L_00464f57
    L_00464f54:
        fld qword ptr [edx]
    L_00464f56:
        ret
    L_00464f57:
        mov eax,dword ptr [edx+4]
    L_00464f5a:
        sub esp,0Ah
    L_00464f5d:
        or eax,7FFF0000h
    L_00464f62:
        mov dword ptr [esp+6],eax
    L_00464f66:
        mov eax,dword ptr [edx+4]
    L_00464f69:
        mov ecx,dword ptr [edx]
    L_00464f6b:
        shld eax,ecx,0Bh
    L_00464f6f:
        shl ecx,0Bh
    L_00464f72:
        mov dword ptr [esp+4],eax
    L_00464f76:
        mov dword ptr [esp],ecx
    L_00464f79:
        fld tbyte ptr [esp]
    L_00464f7c:
        add esp,0Ah
    L_00464f7f:
        test eax,0
    L_00464f84:
        mov eax,dword ptr [edx+4]
    L_00464f87:
        ret
    }
}
