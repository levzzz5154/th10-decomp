// BLOCKED (H3101): closest_byte_count=0/25; first_diff=0x00424620;
// residual_class=private ECX receiver plus EAX value ABI. Live Ghidra
// classifies 00424620..00424638 as four stores and RET, with IDA's
// result@EAX/a2@ECX signature. Native-LTCG probes tested a free stdcall
// (35 bytes, stack arguments), a member int setter (31 bytes, stack value
// and RET 4), and reversed free-parameter order (stack arguments); none
// exposed value in EAX while retaining the ECX receiver.
// variants_tested=free H3101Set24620(S24620*,int), member
// S24620::Set(int), and free H3101Set24620(int,S24620*) under /GL /LTCG.
// next_lever=coupled real caller context that induces the private
// ECX/EAX split, or compiler mechanism for the hidden register ABI.
#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00424620..0x00424638: FUN_00424620
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00424620_00424620() {
    __asm {
    L_00424620:
        mov dword ptr [ecx+332Ch],eax
    L_00424626:
        mov dword ptr [ecx+33C4h],eax
    L_0042462c:
        mov dword ptr [ecx+345Ch],eax
    L_00424632:
        mov dword ptr [ecx+34F4h],eax
    L_00424638:
        ret
    }
}
