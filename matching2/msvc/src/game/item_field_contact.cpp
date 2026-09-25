// BLOCKED (D2702): closest_byte_count=316; first_diff=unmeasured;
// residual_class=private EAX/EDX/ECX entry plus x87 compare scheduling:
// the contact point arrives in EAX, the field in EDX, and the position record
// in ECX, while the body also calls trigger activation on one branch.
// variants_tested=exact retail wrapper, live-Ghidra callers/callees, dataflow
// and global audits, and the legacy Item_TestFieldContact semantic model;
// no compiler-readable candidate was byte-measured without changing fixed
// region ownership.
// next_lever=native-LTCG schema-2 cluster with both real contact callers and
// the 0x00426CF0 callee, then measure x87 ordering and the complete extent.
#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x004266B0..0x004267EB: FUN_004266b0
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_004266b0_004266b0() {
    __asm {
    L_004266b0:
        sub esp,10h
    L_004266b3:
        fld dword ptr [eax]
    L_004266b5:
        fmul dword ptr [data_00470b0c]
    L_004266bb:
        fld dword ptr [ecx]
    L_004266bd:
        fsub st,st(1)
    L_004266bf:
        fstp dword ptr [esp]
    L_004266c2:
        fld dword ptr [eax+4]
    L_004266c5:
        fmul dword ptr [data_00470b0c]
    L_004266cb:
        fld dword ptr [ecx+4]
    L_004266ce:
        fsub st,st(1)
    L_004266d0:
        fstp dword ptr [esp+4]
    L_004266d4:
        fxch
    L_004266d6:
        fadd dword ptr [ecx]
    L_004266d8:
        fstp dword ptr [esp+8]
    L_004266dc:
        fadd dword ptr [ecx+4]
    L_004266df:
        fld dword ptr [edx+404h]
    L_004266e5:
        fcomp dword ptr [esp+8]
    L_004266e9:
        fnstsw ax
    L_004266eb:
        test ah,41h
    L_004266ee:
        je short L_0042676f
    L_004266f0:
        fcomp dword ptr [edx+408h]
    L_004266f6:
        fnstsw ax
    L_004266f8:
        test ah,5
    L_004266fb:
        jnp short L_00426771
    L_004266fd:
        fld dword ptr [edx+410h]
    L_00426703:
        fcomp dword ptr [esp]
    L_00426706:
        fnstsw ax
    L_00426708:
        test ah,5
    L_0042670b:
        jnp short L_00426771
    L_0042670d:
        fld dword ptr [edx+414h]
    L_00426713:
        fcomp dword ptr [esp+4]
    L_00426717:
        fnstsw ax
    L_00426719:
        test ah,5
    L_0042671c:
        jnp short L_00426771
    L_0042671e:
        mov eax,dword ptr [data_0047770c]
    L_00426723:
        test eax,eax
    L_00426725:
        je short L_00426735
    L_00426727:
        mov ecx,dword ptr [eax+9EB8h]
    L_0042672d:
        test ecx,ecx
    L_0042672f:
        jne asm_target_004267e6
    L_00426735:
        mov eax,dword ptr [edx+458h]
    L_0042673b:
        cmp eax,2
    L_0042673e:
        je asm_target_004267e6
    L_00426744:
        cmp eax,4
    L_00426747:
        je asm_target_004267e6
    L_0042674d:
        cmp eax,3
    L_00426750:
        je asm_target_004267e6
    L_00426756:
        mov eax,dword ptr [edx+4310h]
    L_0042675c:
        test eax,eax
    L_0042675e:
        jg short L_00426766
    L_00426760:
        push edx
    L_00426761:
        call asm_FUN_00426cf0_00426cf0
    L_00426766:
        mov eax,1
    L_0042676b:
        add esp,10h
    L_0042676e:
        ret
    L_0042676f:
        fstp st(0)
    L_00426771:
        fld dword ptr [ecx]
    L_00426773:
        fsub dword ptr [data_00470be8]
    L_00426779:
        fstp dword ptr [esp]
    L_0042677c:
        fld dword ptr [ecx+4]
    L_0042677f:
        fsub dword ptr [data_00470be8]
    L_00426785:
        fstp dword ptr [esp+4]
    L_00426789:
        fld dword ptr [ecx]
    L_0042678b:
        fadd dword ptr [data_00470be8]
    L_00426791:
        fld dword ptr [ecx+4]
    L_00426794:
        fadd dword ptr [data_00470be8]
    L_0042679a:
        fstp dword ptr [esp+0Ch]
    L_0042679e:
        fcomp dword ptr [edx+404h]
    L_004267a4:
        fnstsw ax
    L_004267a6:
        test ah,5
    L_004267a9:
        jnp short L_004267e6
    L_004267ab:
        fld dword ptr [edx+408h]
    L_004267b1:
        fcomp dword ptr [esp+0Ch]
    L_004267b5:
        fnstsw ax
    L_004267b7:
        test ah,41h
    L_004267ba:
        je short L_004267e6
    L_004267bc:
        fld dword ptr [edx+410h]
    L_004267c2:
        fcomp dword ptr [esp]
    L_004267c5:
        fnstsw ax
    L_004267c7:
        test ah,5
    L_004267ca:
        jnp short L_004267e6
    L_004267cc:
        fld dword ptr [edx+414h]
    L_004267d2:
        fcomp dword ptr [esp+4]
    L_004267d6:
        fnstsw ax
    L_004267d8:
        test ah,5
    L_004267db:
        jnp short L_004267e6
    L_004267dd:
        mov eax,2
    L_004267e2:
        add esp,10h
    L_004267e5:
        ret
    L_004267e6:
        xor eax,eax
    L_004267e8:
        add esp,10h
    L_004267eb:
        ret
    }
}
