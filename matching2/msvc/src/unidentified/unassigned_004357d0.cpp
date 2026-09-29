#include "asm_encoding.hpp"
#include "asm_symbols.hpp"
// The typed registration candidate passes 120 retail comparisons, including
// count mutation/wrapping. See reference/recovery_notes/resource_paths_004357d0_0043599d.md.
// The EAX path convention remains an exact-build recovery requirement.

// 0x004357D0..0x004357F3: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_004357d0() {
    __asm {
    L_004357d0:
        mov ecx,dword ptr [data_00477850]
    L_004357d6:
        shl ecx,4
    L_004357d9:
        add ecx,4923B0h
    L_004357df:
        call asm_DatArchive_Open_00434c30
    L_004357e4:
        test al,al
    L_004357e6:
        je short L_004357f1
    L_004357e8:
        inc dword ptr [data_00477850]
    L_004357ee:
        mov al,1
    L_004357f0:
        ret
    L_004357f1:
        xor al,al
    L_004357f3:
        ret
    }
}
