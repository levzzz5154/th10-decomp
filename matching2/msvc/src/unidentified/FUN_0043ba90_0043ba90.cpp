#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0043BA90..0x0043BAE2: FUN_0043ba90
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0043ba90_0043ba90() {
    __asm {
    L_0043ba90:
        and dword ptr [data_00491ff4],0FFFFF9FFh
    L_0043ba9a:
        mov eax,491C28h
    L_0043ba9f:
        call asm_FUN_0043b8d0_0043b8d0
    L_0043baa4:
        mov edx,dword ptr [data_00491c38]
    L_0043baaa:
        mov eax,dword ptr [data_00491ff4]
    L_0043baaf:
        xor ecx,ecx
    L_0043bab1:
        test edx,edx
    L_0043bab3:
        setne cl
    L_0043bab6:
        xor edx,edx
    L_0043bab8:
        shl ecx,9
    L_0043babb:
        xor ecx,eax
    L_0043babd:
        and ecx,200h
    L_0043bac3:
        xor eax,ecx
    L_0043bac5:
        mov ecx,dword ptr [data_00491c3c]
    L_0043bacb:
        test ecx,ecx
    L_0043bacd:
        setne dl
    L_0043bad0:
        shl edx,0Ah
    L_0043bad3:
        xor edx,eax
    L_0043bad5:
        and edx,400h
    L_0043badb:
        xor eax,edx
    L_0043badd:
        mov dword ptr [data_00491ff4],eax
    L_0043bae2:
        ret
    }
}
