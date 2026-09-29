#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0043D640..0x0043D664: load an archive buffer into an unchecked pending-WAVE slot.
// Tested C++: reference/semantic_candidates/unassigned_0043d640.cpp.
// See reference/recovery_notes/archive_load_cache_slot_0043d640.md.
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_unassigned_0043d640() {
    __asm {
    L_0043d640:
        push 0
    L_0043d642:
        push 0
    L_0043d644:
        call asm_FUN_0044b360_0044b360
    L_0043d649:
        mov ecx,dword ptr [esp+4]
    L_0043d64d:
        mov edx,dword ptr [esp+8]
    L_0043d651:
        mov dword ptr [ecx+edx*4+5230h],eax
    L_0043d658:
        xor ecx,ecx
    L_0043d65a:
        test eax,eax
    L_0043d65c:
        setne cl
    L_0043d65f:
        dec ecx
    L_0043d660:
        mov eax,ecx
    L_0043d662:
        ret 8
    }
}
