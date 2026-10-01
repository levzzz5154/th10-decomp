#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00404530: maintained in src/game/fun_00404530_00404530.cpp.

// 0x00405500: maintained in src/game/player_clear_expired_flags_retail_00405500.cpp.

// 0x004055C0: recovered in src/game/recovery_install_pair_set_flags_004055c0.cpp.

// 0x00405750: maintained in src/game/update_player_00405750.cpp.

// 0x00405860: maintained in src/game/initialize_player_00405860.cpp.

// 0x004059F0..0x00405AB9: Player_HitTestRetail
// BLOCKED (D2701): closest_byte_count=223; first_diff=0x00405A26;
// residual_class=private-ABI/cluster; a typed native-LTCG reconstruction of
// the hit-test arithmetic and branch results emitted 223 bytes, with its first
// divergence at retail offset +0x36 (the post-FCOMI branch schedule).  The
// retail entry is a private usercall: ECX carries the player object while EAX
// carries the tested point, an ABI not expressible by an ordinary C++ function
// declaration.
// variants_tested=typed hit-test reconstruction with the player fields and
// global state/config accesses recovered from Ghidra, including fastcall and
// native-LTCG candidates (223 bytes, first mismatch +0x36); the exact naked
// usercall overlay remains the only exact body.
// next_lever=an actual native-LTCG caller/cluster preserving the incoming EAX
// point pointer and the original field/global declarations, or a compiler
// mechanism for this private ECX/EAX entry ABI without inline assembly.
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_Player_HitTestRetail_004059f0() {
    __asm {
    L_004059f0:
        mov edx,dword ptr [ecx+28h]
    L_004059f3:
        test edx,edx
    L_004059f5:
        jne short L_004059fa
    L_004059f7:
        xor eax,eax
    L_004059f9:
        ret
    L_004059fa:
        fld dword ptr [eax+4]
    L_004059fd:
        xor edx,edx
    L_004059ff:
        fsub dword ptr [ecx+34h]
    L_00405a02:
        fld dword ptr [eax]
    L_00405a04:
        fsub dword ptr [ecx+30h]
    L_00405a07:
        fld dword ptr [ecx+3Ch]
    L_00405a0a:
        fld st(1)
    L_00405a0c:
        fmul st,st(2)
    L_00405a0e:
        fld st(3)
    L_00405a10:
        fmul st,st(4)
    L_00405a12:
        faddp st(1),st
    L_00405a14:
        fld st(1)
    L_00405a16:
        fmul st,st(2)
    L_00405a18:
        fcompp
    L_00405a1a:
        fstp st(0)
    L_00405a1c:
        fnstsw ax
    L_00405a1e:
        fstp st(0)
    L_00405a20:
        test ah,41h
    L_00405a23:
        fstp st(0)
    L_00405a25:
        jne short L_00405a68
    L_00405a27:
        mov eax,dword ptr [ecx+44h]
    L_00405a2a:
        test eax,eax
    L_00405a2c:
        mov eax,dword ptr [data_004776f4]
    L_00405a31:
        mov cl,byte ptr [eax+378Ch]
    L_00405a37:
        jne short L_00405a46
    L_00405a39:
        test cl,1
    L_00405a3c:
        je short L_00405a53
    L_00405a3e:
        mov edx,3
    L_00405a43:
        mov eax,edx
    L_00405a45:
        ret
    L_00405a46:
        test cl,1
    L_00405a49:
        je short L_00405a53
    L_00405a4b:
        mov edx,26h
    L_00405a50:
        mov eax,edx
    L_00405a52:
        ret
    L_00405a53:
        mov eax,dword ptr [data_00477704]
    L_00405a58:
        mov edx,dword ptr [eax+10h]
    L_00405a5b:
        neg edx
    L_00405a5d:
        sbb edx,edx
    L_00405a5f:
        and edx,21h
    L_00405a62:
        add edx,5
    L_00405a65:
        mov eax,edx
    L_00405a67:
        ret
    L_00405a68:
        mov eax,dword ptr [data_004776f4]
    L_00405a6d:
        test byte ptr [eax+378Ch],1
    L_00405a74:
        je short L_00405a8f
    L_00405a76:
        cmp dword ptr [ecx+44h],1
    L_00405a7a:
        jne short L_00405ab7
    L_00405a7c:
        mov edx,dword ptr [data_00474c68]
    L_00405a82:
        neg edx
    L_00405a84:
        sbb edx,edx
    L_00405a86:
        and edx,0FFFFFFFDh
    L_00405a89:
        add edx,1Ah
    L_00405a8c:
        mov eax,edx
    L_00405a8e:
        ret
    L_00405a8f:
        mov eax,dword ptr [data_00477704]
    L_00405a94:
        push esi
    L_00405a95:
        mov esi,dword ptr [eax+10h]
    L_00405a98:
        test esi,esi
    L_00405a9a:
        pop esi
    L_00405a9b:
        je short L_00405ab7
    L_00405a9d:
        mov eax,dword ptr [ecx+44h]
    L_00405aa0:
        test eax,eax
    L_00405aa2:
        jne short L_00405ab7
    L_00405aa4:
        mov eax,dword ptr [data_00474c68]
    L_00405aa9:
        xor edx,edx
    L_00405aab:
        test eax,eax
    L_00405aad:
        sete dl
    L_00405ab0:
        lea edx,[edx*4+10h]
    L_00405ab7:
        mov eax,edx
    L_00405ab9:
        ret
    }
}

// 0x00405AC0: maintained in src/game/player_draw_00405ac0.cpp.
