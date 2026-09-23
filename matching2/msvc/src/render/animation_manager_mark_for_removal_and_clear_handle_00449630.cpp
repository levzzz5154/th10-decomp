// Recovery status: the standalone C++ candidates did not reproduce this
// private-ESI entry ABI.  Live Ghidra caller evidence and the next
// whole-call-cluster dependency are recorded in
// matching2/reference/recovery_notes/animation_manager_mark_for_removal_and_clear_handle_00449630.md.
// The retail body remains here until the callers and SetFlag helper can be
// modeled together and the fixed 21-byte contribution is verified.
#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0040C480..0x0040C4C0: ?AnimationManager_StopAtFrame2@@
// Naked body preserves the retail register/stack ABI.

// 0x00449630..0x00449644: ?AnimationManager_MarkForRemovalAndClearHandle@@
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_AnimationManager_MarkForRemovalAndClearHandle_00449630() {
    __asm {
    L_00449630:
        mov eax,dword ptr [esi]
    L_00449632:
        mov edx,dword ptr [data_00491c10]
    L_00449638:
        push eax
    L_00449639:
        call asm_AnimationManager_SetFlag_004492a0
    L_0044963e:
        mov dword ptr [esi],0
    L_00449644:
        ret
    }
}
