#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00458B1E..0x00458B3E: FUN_00458b1e
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00458b1e_00458b1e() {
    __asm {
    L_00458b1e:
        push 0Ch
    L_00458b20:
        push 46AC08h
    L_00458b25:
        call asm_SEH_prolog_00454bbc
    L_00458b2a:
        and dword ptr [ebp-1Ch],0
    L_00458b2e:
        and dword ptr [ebp-4],0
    L_00458b32:
        movapd xmm0,xmm1
    L_00458b36:
        mov dword ptr [ebp-1Ch],1
    L_00458b3d:
        TH10_REL8(0xeb, 0x00458b3d, VA_asm_FUN_00458b1e_part_00458b46)
    }
}

// 0x00458B46..0x00458B52: FUN_00458b1e
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00458b1e_part_00458b46() {
    __asm {
    L_00458b46:
        or dword ptr [ebp-4],0FFFFFFFFh
    L_00458b4a:
        mov eax,dword ptr [ebp-1Ch]
    L_00458b4d:
        call asm_SEH_epilog_00454bf7
    L_00458b52:
        ret
    }
}
