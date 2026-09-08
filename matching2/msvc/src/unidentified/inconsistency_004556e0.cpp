#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x004556E0..0x004556FA: _inconsistency
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_inconsistency_004556e0() {
    __asm {
    L_004556e0:
        push 8
    L_004556e2:
        push 46A818h
    L_004556e7:
        call asm_SEH_prolog_00454bbc
    L_004556ec:
        mov eax,dword ptr [data_004731a8]
    L_004556f1:
        test eax,eax
    L_004556f3:
        TH10_REL8(0x74, 0x004556f3, VA_asm_inconsistency_part_00455708)
    L_004556f5:
        and dword ptr [ebp-4],0
    L_004556f9:
        call eax
    }
}

// 0x00455708..0x0045570C: _inconsistency
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_inconsistency_part_00455708() {
    __asm {
    L_00455708:
        jmp asm_terminate_00455693
    }
}
