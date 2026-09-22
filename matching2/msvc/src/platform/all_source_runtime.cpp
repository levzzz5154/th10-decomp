#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x004054B0..0x004054FE: FUN_004054b0
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_004054b0_004054b0() {
    __asm {
    L_004054b0:
        mov ecx,dword ptr [esi+9EC8h]
    L_004054b6:
        push edi
    L_004054b7:
        add edx,8
    L_004054ba:
        lea eax,[esi+6A8Ch]
    L_004054c0:
        call asm_AnimationObject_ConfigureFromResource_0043e5a0
    L_004054c5:
        mov eax,dword ptr [esp+8]
    L_004054c9:
        cdq
    L_004054ca:
        mov ecx,0Ah
    L_004054cf:
        idiv ecx
    L_004054d1:
        mov ecx,dword ptr [esi+9EC8h]
    L_004054d7:
        mov edi,edx
    L_004054d9:
        lea edx,[eax+8]
    L_004054dc:
        lea eax,[esi+71E4h]
    L_004054e2:
        call asm_AnimationObject_ConfigureFromResource_0043e5a0
    L_004054e7:
        mov ecx,dword ptr [esi+9EC8h]
    L_004054ed:
        lea edx,[edi+8]
    L_004054f0:
        lea eax,[esi+7590h]
    L_004054f6:
        call asm_AnimationObject_ConfigureFromResource_0043e5a0
    L_004054fb:
        pop edi
    L_004054fc:
        ret 4
    }
}
// BLOCKED (D3303): closest_byte_count=0/79; first_diff=none;
// residual_class=private ESI owner and EDX first-value ABI, plus three
// compiler-sensitive calls whose callee expects the same live registers.
// variants_tested=live Ghidra decompilation/topology and MSVC 13.10 readable
// stdcall candidates (82/79 and 84/79 extents); next_lever=native-LTCG
// cluster/schema2 with callers 0041AFD0, 00425730, 00405860 and
// ConfigureFromResource callee.
// Current assembly overlay remains exact.


