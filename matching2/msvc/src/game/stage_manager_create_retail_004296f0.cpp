#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00408910..0x004089BF: PlayerManager_ConstructRetail
// Naked body preserves the retail register/stack ABI.

// BLOCKED (D3301): closest_byte_count=6/181; first_diff=0x004296F0;
// residual_class=schema2 SEH/vector-constructor sequencing and private
// cleanup-helper ABI; variants_tested=live-Ghidra decompile plus callers
// (0x004236F0, 0x0042CDF0, 0x004315C0, 0x00433570) and callees
// (0x004294A0, 0x0042A200, operator_new, vector_constructor, free), MSVC
// 13.10 readable candidate (106-byte extent, 6 matching bytes), and native-
// LTCG synthetic dtor/delete context (59/59 bytes differ); next_lever=derive
// the real 0x0042A200/0x004294A0 caller context and compile schema2 with
// native-LTCG SEH enabled.

// 0x004296F0..0x004297A4: StageManager_CreateRetail
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_StageManager_CreateRetail_004296f0() {
    __asm {
    L_004296f0:
        push 0FFFFFFFFh
    L_004296f2:
        push 46564Bh
    L_004296f7:
        mov eax,dword ptr fs:[0]
    L_004296fd:
        push eax
    L_004296fe:
        mov dword ptr fs:[0],esp
    L_00429705:
        push ecx
    L_00429706:
        push esi
    L_00429707:
        push 2D4h
    L_0042970c:
        call asm_operator_new_00452493
    L_00429711:
        mov esi,eax
    L_00429713:
        add esp,4
    L_00429716:
        mov dword ptr [esp+4],esi
    L_0042971a:
        test esi,esi
    L_0042971c:
        mov dword ptr [esp+10h],0
    L_00429724:
        je short L_0042974f
    L_00429726:
        push edi
    L_00429727:
        push 42AC60h
    L_0042972c:
        push 42AC20h
    L_00429731:
        push 8
    L_00429733:
        push 24h
    L_00429735:
        lea eax,[esi+0A0h]
    L_0042973b:
        push eax
    L_0042973c:
        call asm_eh_vector_constructor_iterator_0045252d
    L_00429741:
        mov ecx,0B5h
    L_00429746:
        xor eax,eax
    L_00429748:
        mov edi,esi
    L_0042974a:
        rep stosd
    L_0042974c:
        pop edi
    L_0042974d:
        jmp short L_00429751
    L_0042974f:
        xor esi,esi
    L_00429751:
        mov ecx,dword ptr [esp+18h]
    L_00429755:
        mov dword ptr [esp+10h],0FFFFFFFFh
    L_0042975d:
        push ecx
    L_0042975e:
        mov dword ptr [esi+10h],2
    L_00429765:
        call asm_FUN_0042a200_0042a200
    L_0042976a:
        test eax,eax
    L_0042976c:
        je short L_00429791
    L_0042976e:
        push esi
    L_0042976f:
        call asm_FUN_004294a0_004294a0
    L_00429774:
        push esi
    L_00429775:
        call asm_free_004524a1
    L_0042977a:
        add esp,4
    L_0042977d:
        xor eax,eax
    L_0042977f:
        pop esi
    L_00429780:
        mov ecx,dword ptr [esp+4]
    L_00429784:
        mov dword ptr fs:[0],ecx
    L_0042978b:
        add esp,10h
    L_0042978e:
        ret 4
    L_00429791:
        mov ecx,dword ptr [esp+8]
    L_00429795:
        mov eax,esi
    L_00429797:
        pop esi
    L_00429798:
        mov dword ptr fs:[0],ecx
    L_0042979f:
        add esp,10h
    L_004297a2:
        ret 4
    }
}
