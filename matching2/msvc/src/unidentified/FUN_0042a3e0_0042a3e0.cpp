#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0042A3E0..0x0042A423: FUN_0042a3e0
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0042a3e0_0042a3e0() {
    __asm {
    L_0042a3e0:
        mov eax,dword ptr [data_00477810]
    L_0042a3e5:
        test eax,eax
    L_0042a3e7:
        je short L_0042a41e
    L_0042a3e9:
        test byte ptr [eax+58h],4
    L_0042a3ed:
        mov eax,1
    L_0042a3f2:
        jne short L_0042a41d
    L_0042a3f4:
        cmp dword ptr [ecx+10h],eax
    L_0042a3f7:
        jne short L_0042a41d
    L_0042a3f9:
        mov edx,dword ptr [data_00474e30]
    L_0042a3ff:
        test dh,al
    L_0042a401:
        je short L_0042a41d
    L_0042a403:
        mov ecx,dword ptr [ecx+1C8h]
    L_0042a409:
        and ecx,80000003h
    L_0042a40f:
        jns short L_0042a416
    L_0042a411:
        dec ecx
    L_0042a412:
        or ecx,0FFFFFFFCh
    L_0042a415:
        inc ecx
    L_0042a416:
        je short L_0042a41d
    L_0042a418:
        mov eax,6
    L_0042a41d:
        ret
    L_0042a41e:
        mov eax,1
    L_0042a423:
        ret
    }
}
