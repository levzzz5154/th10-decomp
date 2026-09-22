// BLOCKED (D3307): closest_byte_count=21/41; first_diff=0x00417012;
// residual_class=private EAX-entry native-LTCG register allocation and loop
// scheduling (the readable member model selected the input/output registers in
// the opposite order and folded their pointer difference).
// variants_tested=live Ghidra complete decompilation with callers/xrefs and
// disassembly/variable audit; ordinary MSVC 13.10 readable cdecl candidate
// (43-byte extent); five native MSVC 13.10 schema-1 context builds using the
// EAX member model and reordered/volatile pointer locals (best 21/41).
// next_lever=retain the real caller-inclusive native-LTCG cluster and vary only
// the source expression shape that keeps independent input/output pointers and
// retail store/update order; promote only after all 41 bytes match.

#include <string.h>
#include "asm_encoding.hpp"

// Retail strrchr at 0x00452930 (cdecl: string, character).

// 0x00417010..0x00417038: ?Path_DecodeXor@@
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_Path_DecodeXor_00417010() {
    __asm {
    L_00417010:
        push esi
    L_00417011:
        push edi
    L_00417012:
        mov edi,eax
    L_00417014:
        mov cl,77h
    L_00417016:
        mov dl,7
    L_00417018:
        mov esi,497D40h
    L_0041701d:
        TH10_NOP_LEA_ECX_DISP8()
    L_00417020:
        mov al,byte ptr [edi]
    L_00417022:
        xor al,cl
    L_00417024:
        mov byte ptr [esi],al
    L_00417026:
        inc esi
    L_00417027:
        add cl,dl
    L_00417029:
        inc edi
    L_0041702a:
        add dl,10h
    L_0041702d:
        test al,al
    L_0041702f:
        jne short L_00417020
    L_00417031:
        pop edi
    L_00417032:
        mov eax,497D40h
    L_00417037:
        pop esi
    L_00417038:
        ret
    }
}
