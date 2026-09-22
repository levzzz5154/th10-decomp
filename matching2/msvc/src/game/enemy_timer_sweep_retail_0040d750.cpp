// BLOCKED (D3906): closest_byte_count=0/166; first_diff=0x0040D750
// (standalone readable candidate emitted a 78-byte body, so no byte
// comparison was admissible).
// residual_class=private EDI receiver, helper-call register preservation,
// virtual-retire ABI, frame-clock tail, and compiler save/restore ordering.
// variants_tested=live IDA assembly and caller 0x0040D810; legacy semantic
// EnemyList_TickInterpolators translation; MSVC 13.10 schema-2/native-LTCG
// feasibility review plus standalone native probe (78-byte body versus the
// 166-byte retail region).
// next_lever=promote 0x0040D810 and this leaf in one schema-2 native-LTCG
// cluster so the real caller establishes the EDI receiver and the private
// helper/retire conventions, then change the production region to semantic.
#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x004066E0..0x00406765: FUN_004066e0
// Naked body preserves the retail register/stack ABI.

// 0x0040D750..0x0040D7F5: Enemy_TimerSweepRetail
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_Enemy_TimerSweepRetail_0040d750() {
    __asm {
    L_0040d750:
        push esi
    L_0040d751:
        mov esi,dword ptr [edi+58h]
    L_0040d754:
        test esi,esi
    L_0040d756:
        je short L_0040d7a2
    L_0040d758:
        push ebx
    L_0040d759:
        lea esp,[esp+force_disp32_zero]
    L_0040d760:
        mov eax,dword ptr [esi]
    L_0040d762:
        test dword ptr [eax+2480h],20000h
    L_0040d76c:
        mov ebx,dword ptr [esi+4]
    L_0040d76f:
        jne short L_0040d78e
    L_0040d771:
        add eax,103Ch
    L_0040d776:
        push eax
    L_0040d777:
        call asm_FUN_0040dc80_0040dc80
    L_0040d77c:
        test eax,eax
    L_0040d77e:
        jne short L_0040d78e
    L_0040d780:
        mov esi,dword ptr [esi]
    L_0040d782:
        and dword ptr [esi+2480h],0FFFFFBFFh
    L_0040d78c:
        jmp short L_0040d79b
    L_0040d78e:
        mov ecx,dword ptr [esi]
    L_0040d790:
        test ecx,ecx
    L_0040d792:
        je short L_0040d79b
    L_0040d794:
        mov eax,dword ptr [ecx]
    L_0040d796:
        push 1
    L_0040d798:
        call dword ptr [eax+14h]
    L_0040d79b:
        test ebx,ebx
    L_0040d79d:
        mov esi,ebx
    L_0040d79f:
        jne short L_0040d760
    L_0040d7a1:
        pop ebx
    L_0040d7a2:
        mov edx,dword ptr [edi+44h]
    L_0040d7a5:
        mov ecx,dword ptr [edi+4Ch]
    L_0040d7a8:
        mov dword ptr [edi+40h],edx
    L_0040d7ab:
        fld dword ptr [ecx]
    L_0040d7ad:
        fcomp dword ptr [data_00470b68]
    L_0040d7b3:
        pop esi
    L_0040d7b4:
        fnstsw ax
    L_0040d7b6:
        test ah,41h
    L_0040d7b9:
        jne short L_0040d7e0
    L_0040d7bb:
        fld dword ptr [ecx]
    L_0040d7bd:
        fcomp dword ptr [data_00470b64]
    L_0040d7c3:
        fnstsw ax
    L_0040d7c5:
        test ah,5
    L_0040d7c8:
        jp short L_0040d7e0
    L_0040d7ca:
        fld dword ptr [edi+48h]
    L_0040d7cd:
        inc edx
    L_0040d7ce:
        fadd dword ptr [data_00470afc]
    L_0040d7d4:
        mov dword ptr [edi+44h],edx
    L_0040d7d7:
        mov eax,1
    L_0040d7dc:
        fstp dword ptr [edi+48h]
    L_0040d7df:
        ret
    L_0040d7e0:
        fld dword ptr [ecx]
    L_0040d7e2:
        fadd dword ptr [edi+48h]
    L_0040d7e5:
        fst dword ptr [edi+48h]
    L_0040d7e8:
        call asm_FUN_00463b2c_00463b2c
    L_0040d7ed:
        mov dword ptr [edi+44h],eax
    L_0040d7f0:
        mov eax,1
    L_0040d7f5:
        ret
    }
}
