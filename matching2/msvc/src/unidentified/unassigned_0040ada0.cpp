#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0040ADA0..0x0040ADB8: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_0040ada0() {
    __asm {
    L_0040ada0:
        lea edx,[eax+eax*2]
    L_0040ada3:
        shl edx,4
    L_0040ada6:
        add edx,474788h
    L_0040adac:
        mov dword ptr [data_00477848],edx
    L_0040adb2:
        mov dword ptr [ecx+3Ch],eax
    L_0040adb5:
        mov dword ptr [ecx+40h],eax
    L_0040adb8:
        ret
    }
}
