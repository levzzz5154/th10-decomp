// BLOCKED (D2701): closest_byte_count=36; first_diff=unmeasured;
// residual_class=abi+linked-list-entry: retail starts from a VM pointer in
// EAX, walks the bound-node chain rooted at +0x1030, compares each pointed
// object's private identifier at +0x1010 against ECX, and returns the node
// address.  The receiver and search key are both promoted live-ins that a
// normal C++ declaration does not preserve.
// variants_tested=exact retail wrapper, the legacy linked-node
// ECL_FindVariable model, the ECL_ResetVariableBindings sibling, and the
// dispatcher call sites that establish the EAX/ECX tuple; no
// compiler-readable candidate was byte-measured.
// next_lever=compile the node walk in the existing ECL native-LTCG cluster
// with a synthetic caller pinning EAX and ECX, preserving the retail
// aligned-short-jump layout; retain the 36-byte wrapper until measured.

#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0044DF70..0x0044E195: EclVm_StartChildRetail
// Naked body preserves the retail register/stack ABI.

// 0x00450160..0x00450168: ?ECL_FindVariable@@
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_ECL_FindVariable_00450160() {
    __asm {
    L_00450160:
        add eax,1030h
    L_00450165:
        TH10_REL8(0x74, 0x00450165, VA_asm_target_00450181)
    L_00450167:
        TH10_REL8(0xeb, 0x00450167, VA_asm_ECL_FindVariable_part_00450170)
        _emit 0x8d
        _emit 0xa4
        _emit 0x24
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x00

    L_00450170:
        mov edx,dword ptr [eax]
    L_00450172:
        cmp dword ptr [edx+1010h],ecx
    L_00450178:
        je short L_00450183
    L_0045017a:
        mov eax,dword ptr [eax+4]
    L_0045017d:
        test eax,eax
    L_0045017f:
        jne short L_00450170
    L_00450181:
        xor eax,eax
    L_00450183:
        ret
    }
}
