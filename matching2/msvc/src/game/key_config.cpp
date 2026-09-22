// BLOCKED (D3504): closest_byte_count=0/200; first_diff=0x00430250;
// residual_class=private EAX key-record receiver with ECX slot index/EDX key
// value, short-field swap ordering, and exact post-update callee argument
// setup for 0x0042F8B0 and 0x0043DC90.
// variants_tested=exact retail wrapper, live-Ghidra decompilation plus
// caller/callee graph, and a readable five-slot candidate measured at 128
// bytes (retail extent is 200); no cluster candidate was retained because the
// fixed-address region remains assembly-owned.
// next_lever=native-LTCG cluster over real caller 0x0042F6D8, this body, the
// 0x0042F8B0 and 0x0043DC90 callees, and the EAX/ECX/EDX entry tuple; then
// measure all 200 bytes.
#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00430250..0x00430317: KeyConfig_ReassignSlotRetail
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_KeyConfig_ReassignSlotRetail_00430250() {
    __asm {
    L_00430250:
        push esi
    L_00430251:
        mov si,word ptr [eax+ecx*2+59CCh]
    L_00430259:
        push edi
    L_0043025a:
        movsx edi,si
    L_0043025d:
        cmp edi,edx
    L_0043025f:
        je asm_target_00430315
    L_00430265:
        test ecx,ecx
    L_00430267:
        je short L_0043027b
    L_00430269:
        movsx edi,word ptr [eax+59CCh]
    L_00430270:
        cmp edi,edx
    L_00430272:
        jne short L_0043027b
    L_00430274:
        mov word ptr [eax+59CCh],si
    L_0043027b:
        cmp ecx,1
    L_0043027e:
        je short L_0043029a
    L_00430280:
        movsx esi,word ptr [eax+59CEh]
    L_00430287:
        cmp esi,edx
    L_00430289:
        jne short L_0043029a
    L_0043028b:
        mov si,word ptr [eax+ecx*2+59CCh]
    L_00430293:
        mov word ptr [eax+59CEh],si
    L_0043029a:
        cmp ecx,2
    L_0043029d:
        je short L_004302b9
    L_0043029f:
        movsx esi,word ptr [eax+59D0h]
    L_004302a6:
        cmp esi,edx
    L_004302a8:
        jne short L_004302b9
    L_004302aa:
        mov si,word ptr [eax+ecx*2+59CCh]
    L_004302b2:
        mov word ptr [eax+59D0h],si
    L_004302b9:
        cmp ecx,3
    L_004302bc:
        je short L_004302d8
    L_004302be:
        movsx esi,word ptr [eax+59D2h]
    L_004302c5:
        cmp esi,edx
    L_004302c7:
        jne short L_004302d8
    L_004302c9:
        mov si,word ptr [eax+ecx*2+59CCh]
    L_004302d1:
        mov word ptr [eax+59D2h],si
    L_004302d8:
        cmp ecx,4
    L_004302db:
        je short L_004302f7
    L_004302dd:
        movsx esi,word ptr [eax+59D4h]
    L_004302e4:
        cmp esi,edx
    L_004302e6:
        jne short L_004302f7
    L_004302e8:
        mov si,word ptr [eax+ecx*2+59CCh]
    L_004302f0:
        mov word ptr [eax+59D4h],si
    L_004302f7:
        mov word ptr [eax+ecx*2+59CCh],dx
    L_004302ff:
        call asm_FUN_0042f8b0_0042f8b0
    L_00430304:
        push 0
    L_00430306:
        mov edi,0Ah
    L_0043030b:
        mov ecx,492590h
    L_00430310:
        call asm_AnimationManager_QueueResource_0043dc90
    L_00430315:
        pop edi
    L_00430316:
        pop esi
    L_00430317:
        ret
    }
}
