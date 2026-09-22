// BLOCKED (D3803): closest_byte_count=0/359; first_diff=0x00427960
// (no readable native-LTCG body retained).
// residual_class=private ESI receiver, EBX/EDI/EBP register lifetime across
// the branch and x87 loop, fixed table layout at 0x00477834, and the
// private FUN_00463B2C call/float-pool placement.
// variants_tested=live Ghidra complete decompile with caller 0x00427953 and
// callee 0x00463B2C; MSVC 13.10.6030 authoritative production probe
// (359/359 exact); native-LTCG cluster feasibility review of the real
// callback caller, x87 evaluation order, and fixed data/callee topology.
// next_lever=compile a schema-2 native-LTCG cluster containing the real
// 0x00427953 caller, 0x00463B2C, the fixed table/data bindings, and the
// complete float loop; require exact 359-byte body and relocation agreement
// before changing production metadata.

#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0040C3C0..0x0040C43D: StageBackground_RebindTextureRetail
// Naked body preserves the retail register/stack ABI.

// 0x00427960..0x00427A09: FUN_00427960
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00427960_00427960() {
    __asm {
    L_00427960:
        sub esp,0Ch
    L_00427963:
        mov eax,dword ptr [esi+88h]
    L_00427969:
        push ebx
    L_0042796a:
        push ebp
    L_0042796b:
        push edi
    L_0042796c:
        mov edi,dword ptr [data_00477834]
    L_00427972:
        mov ebx,dword ptr [edi+4474h]
    L_00427978:
        shl eax,6
    L_0042797b:
        test ebx,ebx
    L_0042797d:
        mov ecx,dword ptr [eax+edi+43ACh]
    L_00427984:
        lea eax,[eax+edi+43ACh]
    L_0042798b:
        mov dword ptr [esi+34h],ecx
    L_0042798e:
        mov edx,dword ptr [eax+4]
    L_00427991:
        mov dword ptr [esp+14h],ebx
    L_00427995:
        mov dword ptr [esi+38h],edx
    L_00427998:
        jne short L_004279b9
    L_0042799a:
        mov ebp,dword ptr [edi+3CCh]
    L_004279a0:
        mov eax,ecx
    L_004279a2:
        mov ecx,edx
    L_004279a4:
        mov edx,dword ptr [edi+3D0h]
    L_004279aa:
        sub eax,ebp
    L_004279ac:
        sub ecx,edx
    L_004279ae:
        mov dword ptr [esi+44h],eax
    L_004279b1:
        mov dword ptr [esi+48h],ecx
    L_004279b4:
        jmp asm_target_00427a9e
    L_004279b9:
        mov edx,dword ptr [esi+48h]
    L_004279bc:
        fld dword ptr [data_00470b90]
    L_004279c2:
        mov ecx,dword ptr [edi+3D0h]
    L_004279c8:
        mov ebp,dword ptr [esi+44h]
    L_004279cb:
        mov eax,dword ptr [edi+3CCh]
    L_004279d1:
        add ecx,edx
    L_004279d3:
        mov edx,dword ptr [esi+88h]
    L_004279d9:
        add eax,ebp
    L_004279db:
        shl edx,6
    L_004279de:
        lea edx,[edx+edi+43ACh]
    L_004279e5:
        mov dword ptr [edx],eax
    L_004279e7:
        mov dword ptr [edx+4],ecx
    L_004279ea:
        mov eax,dword ptr [esi+88h]
    L_004279f0:
        shl eax,3
    L_004279f3:
        lea ebp,[eax+1]
    L_004279f6:
        add eax,7
    L_004279f9:
        cmp ebp,eax
    L_004279fb:
        jg asm_target_00427a9c
    L_00427a01:
        lea ebx,[edi+ebp*8+4370h]
    L_00427a08:
        TH10_REL8(0xeb, 0x00427a08, VA_asm_FUN_00427960_part_00427a10)
        _emit 0x8d
        _emit 0x9b
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x00

    L_00427a10:
        mov eax,dword ptr [esi+88h]
    L_00427a16:
        shl eax,6
    L_00427a19:
        mov ecx,dword ptr [eax+edi+436Ch]
    L_00427a20:
        mov edx,dword ptr [eax+edi+43ACh]
    L_00427a27:
        add eax,edi
    L_00427a29:
        sub edx,ecx
    L_00427a2b:
        mov dword ptr [esp+0Ch],edx
    L_00427a2f:
        fild dword ptr [esp+0Ch]
    L_00427a33:
        mov dword ptr [esp+10h],ecx
    L_00427a37:
        fmul st,st(1)
    L_00427a39:
        fiadd dword ptr [esp+10h]
    L_00427a3d:
        call asm_FUN_00463b2c_00463b2c
    L_00427a42:
        mov dword ptr [ebx-4],eax
    L_00427a45:
        mov eax,dword ptr [esi+88h]
    L_00427a4b:
        shl eax,6
    L_00427a4e:
        mov ecx,dword ptr [eax+edi+4370h]
    L_00427a55:
        mov edx,dword ptr [eax+edi+43B0h]
    L_00427a5c:
        add eax,edi
    L_00427a5e:
        sub edx,ecx
    L_00427a60:
        mov dword ptr [esp+10h],edx
    L_00427a64:
        fild dword ptr [esp+10h]
    L_00427a68:
        mov dword ptr [esp+0Ch],ecx
    L_00427a6c:
        fmul st,st(1)
    L_00427a6e:
        fiadd dword ptr [esp+0Ch]
    L_00427a72:
        call asm_FUN_00463b2c_00463b2c
    L_00427a77:
        fadd dword ptr [data_00470b90]
    L_00427a7d:
        mov dword ptr [ebx],eax
    L_00427a7f:
        mov eax,dword ptr [esi+88h]
    L_00427a85:
        inc ebp
    L_00427a86:
        lea ecx,[eax*8+7]
    L_00427a8d:
        add ebx,8
    L_00427a90:
        cmp ebp,ecx
    L_00427a92:
        jle asm_FUN_00427960_part_00427a10
    L_00427a98:
        mov ebx,dword ptr [esp+14h]
    L_00427a9c:
        fstp st(0)
    L_00427a9e:
        mov ebp,dword ptr [edi+3CCh]
    L_00427aa4:
        mov eax,dword ptr [esi+44h]
    L_00427aa7:
        mov edx,dword ptr [edi+3D0h]
    L_00427aad:
        mov ecx,dword ptr [esi+48h]
    L_00427ab0:
        add eax,ebp
    L_00427ab2:
        pop edi
    L_00427ab3:
        add ecx,edx
    L_00427ab5:
        mov dword ptr [esi+34h],eax
    L_00427ab8:
        mov dword ptr [esi+38h],ecx
    L_00427abb:
        pop ebp
    L_00427abc:
        mov dword ptr [esi+84h],ebx
    L_00427ac2:
        pop ebx
    L_00427ac3:
        add esp,0Ch
    L_00427ac6:
        ret
    }
}
