#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00464EA0..0x00464EB6: FUN_00464ea0
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00464ea0_00464ea0() {
    __asm {
    L_00464ea0:
        push ebp
    L_00464ea1:
        mov ebp,esp
    L_00464ea3:
        add esp,0FFFFFFE0h
    L_00464ea6:
        mov dword ptr [ebp-20h],eax
    L_00464ea9:
        mov eax,dword ptr [ebp+18h]
    L_00464eac:
        mov dword ptr [ebp-10h],eax
    L_00464eaf:
        mov eax,dword ptr [ebp+1Ch]
    L_00464eb2:
        mov dword ptr [ebp-0Ch],eax
    L_00464eb5:
        TH10_REL8(0xeb, 0x00464eb5, VA_asm_target_00464ec0)
    }
}
