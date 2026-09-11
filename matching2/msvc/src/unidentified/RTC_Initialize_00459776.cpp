#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00459776..0x004597A2: __RTC_Initialize
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_RTC_Initialize_00459776() {
    __asm {
    L_00459776:
        push 0Ch
    L_00459778:
        push 46B048h
    L_0045977d:
        call asm_SEH_prolog_00454bbc
    L_00459782:
        mov dword ptr [ebp-1Ch],471128h
    L_00459789:
        cmp dword ptr [ebp-1Ch],471128h
    L_00459790:
        TH10_REL8(0x73, 0x00459790, VA_asm_target_004597b4)
    L_00459792:
        and dword ptr [ebp-4],0
    L_00459796:
        mov eax,dword ptr [ebp-1Ch]
    L_00459799:
        mov eax,dword ptr [eax]
    L_0045979b:
        test eax,eax
    L_0045979d:
        TH10_REL8(0x74, 0x0045979d, VA_asm_RTC_Initialize_part_004597aa)
    L_0045979f:
        call eax
    L_004597a1:
        TH10_REL8(0xeb, 0x004597a1, VA_asm_RTC_Initialize_part_004597aa)
        _emit 0x33
        _emit 0xc0
        _emit 0x40
        _emit 0xc3
        _emit 0x8b
        _emit 0x65
        _emit 0xe8

    L_004597aa:
        or dword ptr [ebp-4],0FFFFFFFFh
    L_004597ae:
        add dword ptr [ebp-1Ch],4
    L_004597b2:
        TH10_REL8(0xeb, 0x004597b2, VA_asm_target_00459789)
    L_004597b4:
        call asm_SEH_epilog_00454bf7
    L_004597b9:
        ret
    }
}
