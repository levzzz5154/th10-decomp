#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00458E74..0x00458E90: report_failure
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_report_failure_00458e74() {
    __asm {
    L_00458e74:
        push 8
    L_00458e76:
        push 46AC30h
    L_00458e7b:
        call asm_SEH_prolog_00454bbc
    L_00458e80:
        and dword ptr [ebp-4],0
    L_00458e84:
        push 0
    L_00458e86:
        push 1
    L_00458e88:
        call asm_FUN_0045f259_0045f259
    L_00458e8d:
        pop ecx
    L_00458e8e:
        pop ecx
    L_00458e8f:
        TH10_REL8(0xeb, 0x00458e8f, VA_asm_report_failure_part_00458e98)
        _emit 0x33
        _emit 0xc0
        _emit 0x40
        _emit 0xc3
        _emit 0x8b
        _emit 0x65
        _emit 0xe8

    L_00458e98:
        or dword ptr [ebp-4],0FFFFFFFFh
    L_00458e9c:
        push 3
    L_00458e9e:
        call dword ptr [data_0046614c]
    }
}
