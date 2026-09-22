// BLOCKED (D3805): closest_byte_count=116/185; first_diff=unmeasured.
// residual_class=C++ EH registration and vector-constructor layout, plus the
// private register ABI and concrete object layout required by FUN_00428F60.
// variants_tested=["live Ghidra/IDA decompilation", "ordinary __stdcall
// readable candidate under MSVC 13.10 (116-byte extent)", "retail assembly
// baseline probe (185/185 exact)"].
// next_lever=promote a caller-inclusive schema2/native-LTCG build with the
// production object layout, EH handlers, and FUN_00428F60 edge visible.
#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00408910..0x004089BF: PlayerManager_ConstructRetail
// Naked body preserves the retail register/stack ABI.

// 0x00429610..0x004296C8: FUN_00429610
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00429610_00429610() {
    __asm {
    L_00429610:
        push 0FFFFFFFFh
    L_00429612:
        push 46566Bh
    L_00429617:
        mov eax,dword ptr fs:[0]
    L_0042961d:
        push eax
    L_0042961e:
        mov dword ptr fs:[0],esp
    L_00429625:
        push ecx
    L_00429626:
        push esi
    L_00429627:
        push 2D4h
    L_0042962c:
        call asm_operator_new_00452493
    L_00429631:
        mov esi,eax
    L_00429633:
        add esp,4
    L_00429636:
        mov dword ptr [esp+4],esi
    L_0042963a:
        test esi,esi
    L_0042963c:
        mov dword ptr [esp+10h],0
    L_00429644:
        je short L_0042966f
    L_00429646:
        push edi
    L_00429647:
        push 42AC60h
    L_0042964c:
        push 42AC20h
    L_00429651:
        push 8
    L_00429653:
        push 24h
    L_00429655:
        lea eax,[esi+0A0h]
    L_0042965b:
        push eax
    L_0042965c:
        call asm_eh_vector_constructor_iterator_0045252d
    L_00429661:
        mov ecx,0B5h
    L_00429666:
        xor eax,eax
    L_00429668:
        mov edi,esi
    L_0042966a:
        rep stosd
    L_0042966c:
        pop edi
    L_0042966d:
        jmp short L_00429671
    L_0042966f:
        xor esi,esi
    L_00429671:
        mov ecx,dword ptr [esp+1Ch]
    L_00429675:
        mov eax,dword ptr [esp+18h]
    L_00429679:
        push ebx
    L_0042967a:
        mov ebx,esi
    L_0042967c:
        mov dword ptr [esp+14h],0FFFFFFFFh
    L_00429684:
        call asm_FUN_00428f60_00428f60
    L_00429689:
        test eax,eax
    L_0042968b:
        pop ebx
    L_0042968c:
        je short L_004296b5
    L_0042968e:
        test esi,esi
    L_00429690:
        je short L_004296a1
    L_00429692:
        push esi
    L_00429693:
        call asm_FUN_004294a0_004294a0
    L_00429698:
        push esi
    L_00429699:
        call asm_free_004524a1
    L_0042969e:
        add esp,4
    L_004296a1:
        xor eax,eax
    L_004296a3:
        pop esi
    L_004296a4:
        mov ecx,dword ptr [esp+4]
    L_004296a8:
        mov dword ptr fs:[0],ecx
    L_004296af:
        add esp,10h
    L_004296b2:
        ret 8
    L_004296b5:
        mov ecx,dword ptr [esp+8]
    L_004296b9:
        mov eax,esi
    L_004296bb:
        pop esi
    L_004296bc:
        mov dword ptr fs:[0],ecx
    L_004296c3:
        add esp,10h
    L_004296c6:
        ret 8
    }
}
