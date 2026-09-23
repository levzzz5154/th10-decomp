#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x004054B0..0x004054FE: configure the three power-display digit objects.
// The focused Ghidra contract and ABI evidence is in
// matching2/reference/recovery_notes/power_display_digit_triplet_004054b0.md.
// Keep this body until its register-based callers and ConfigureFromResource
// callee can be recovered as one typed native-LTCG cluster.
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
// BLOCKED (D3303): no ABI-compatible standalone C++ entry. This body receives
// its useful value in EDX, its decimal value on the stack, and its owner in
// ESI; the configured symbol/header is zero-argument __cdecl. Each resource
// call also uses ECX=resource, EAX=target, EDX=index. Prior stdcall candidates
// emitted 82/79 and 84/79 bytes. Next lever: native-LTCG schema2 recovery of
// callers 0041AFD0, 00425730, 00405860 and callee 0043E5A0 together.
// Current assembly overlay remains exact.

