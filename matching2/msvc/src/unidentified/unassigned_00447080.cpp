#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00447080..0x004470B1: unassigned code fragment
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_00447080() {
    __asm {
    L_00447080:
        push eax
    L_00447081:
        push ecx
    L_00447082:
        push esi
    L_00447083:
        call asm_FUN_004470c0_004470c0
    L_00447088:
        test eax,eax
    L_0044708a:
        je short L_004470b1
    L_0044708c:
        mov dword ptr [eax+124h],1
    L_00447096:
        mov ecx,dword ptr [eax+124h]
    L_0044709c:
        test ecx,ecx
    L_0044709e:
        je short L_004470b1
    L_004470a0:
        push eax
    L_004470a1:
        push esi
    L_004470a2:
        call asm_AnmArchive_AdvanceScriptCursorRetail_004473c0
    L_004470a7:
        mov ecx,dword ptr [eax+124h]
    L_004470ad:
        test ecx,ecx
    L_004470af:
        jne short L_004470a0
    L_004470b1:
        ret
    }
}
