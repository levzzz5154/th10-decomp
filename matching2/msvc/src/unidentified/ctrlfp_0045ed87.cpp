#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0045ED87..0x0045EDAA: __ctrlfp
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_ctrlfp_0045ed87() {
    __asm {
    L_0045ed87:
        push ebp
    L_0045ed88:
        mov ebp,esp
    L_0045ed8a:
        push ecx
    L_0045ed8b:
        wait
        fnstcw word ptr [ebp-4]
    L_0045ed8f:
        mov eax,dword ptr [ebp+0Ch]
    L_0045ed92:
        mov ecx,dword ptr [ebp+8]
    L_0045ed95:
        and ecx,dword ptr [ebp+0Ch]
    L_0045ed98:
        not eax
    L_0045ed9a:
        and eax,dword ptr [ebp-4]
    L_0045ed9d:
        or eax,ecx
    L_0045ed9f:
        mov dword ptr [ebp+0Ch],eax
    L_0045eda2:
        fldcw word ptr [ebp+0Ch]
    L_0045eda5:
        movsx eax,word ptr [ebp-4]
    L_0045eda9:
        leave
    L_0045edaa:
        ret
    }
}
