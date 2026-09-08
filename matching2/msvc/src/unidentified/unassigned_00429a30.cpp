#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00429A30..0x00429A69: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00429a30() {
    __asm {
    L_00429a30:
        mov ecx,dword ptr [data_00477810]
    L_00429a36:
        test ecx,ecx
    L_00429a38:
        je short L_00429a64
    L_00429a3a:
        cmp dword ptr [eax+10h],1
    L_00429a3e:
        jne short L_00429a64
    L_00429a40:
        mov ecx,dword ptr [data_00474e30]
    L_00429a46:
        test ch,1
    L_00429a49:
        je short L_00429a64
    L_00429a4b:
        mov eax,dword ptr [eax+1C8h]
    L_00429a51:
        and eax,80000003h
    L_00429a56:
        jns short L_00429a5d
    L_00429a58:
        dec eax
    L_00429a59:
        or eax,0FFFFFFFCh
    L_00429a5c:
        inc eax
    L_00429a5d:
        mov eax,6
    L_00429a62:
        jne short L_00429a69
    L_00429a64:
        mov eax,1
    L_00429a69:
        ret
    }
}
