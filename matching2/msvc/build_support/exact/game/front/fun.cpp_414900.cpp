// BLOCKED (H2501): closest_byte_count=3836; first_diff=unmeasured;
// residual_class=large front-HUD update with nonstandard helper live-ins:
// the traced scheduler ABI is expressible as a one-argument stdcall callback,
// but FUN_0043E5A0 consumes the target in EAX, FUN_00449950 consumes the
// manager in ESI, FUN_0043DC90 consumes the sound id in EDI, and FUN_00463B2C
// consumes x87 ST0. Those effects cannot be called faithfully with ordinary
// C++ prototypes; keep the exact retail body until their semantics/layouts
// can replace the hidden-register edges;
// variants_tested=legacy ui_final_runtime semantic counterpart, live Ghidra
// decompilation/call graph/disassembly of this body, its scheduler callback,
// and the coupled helpers;
// next_lever=integrate typed semantic equivalents for those helpers and their
// state layouts, then replace the body without an uncompiled sidecar.

#include "../../../include/asm_encoding.hpp"
#include "../../../include/asm_symbols.hpp"


// 0x00414900..0x004157DC: FUN_00414900
// Retail body retained pending semantic equivalents for hidden-register callees.
extern "C" __declspec(naked) void __cdecl asm_FUN_00414900_00414900() {
    __asm {
    L_00414900:
        push ecx
    L_00414901:
        push edi
    L_00414902:
        mov edi,dword ptr [esp+0Ch]
    L_00414906:
        test byte ptr [edi+9EB4h],10h
    L_0041490d:
        je short L_0041493c
    L_0041490f:
        mov ecx,dword ptr [edi+9ECCh]
    L_00414915:
        inc ecx
    L_00414916:
        mov eax,ecx
    L_00414918:
        cmp eax,78h
    L_0041491b:
        mov dword ptr [edi+9ECCh],ecx
    L_00414921:
        jl short L_0041493c
    L_00414923:
        mov eax,dword ptr [g_app_flags]
    L_00414928:
        and eax,1000h
    L_0041492d:
        neg eax
    L_0041492f:
        sbb eax,eax
    L_00414931:
        and eax,0FFFFFFF4h
    L_00414934:
        add eax,0Eh
    L_00414937:
        mov dword ptr [g_main_state],eax
    L_0041493c:
        push ebx
    L_0041493d:
        push ebp
    L_0041493e:
        push esi
    L_0041493f:
        lea esi,[edi+4980h]
    L_00414945:
        mov ebx,9
    L_0041494a:
        lea ebx,[ebx+force_disp32_zero]
    L_00414950:
        push esi
    L_00414951:
        call asm_FUN_0043ee30_0043ee30
    L_00414956:
        add esi,3ACh
    L_0041495c:
        dec ebx
    L_0041495d:
        jne short L_00414950
    L_0041495f:
        lea esi,[edi+6A8Ch]
    L_00414965:
        mov ebx,4
    L_0041496a:
        lea ebx,[ebx+force_disp32_zero]
    L_00414970:
        push esi
    L_00414971:
        call asm_FUN_0043ee30_0043ee30
    L_00414976:
        add esi,3ACh
    L_0041497c:
        dec ebx
    L_0041497d:
        jne short L_00414970
    L_0041497f:
        lea esi,[edi+793Ch]
    L_00414985:
        mov ebx,2
    L_0041498a:
        lea ebx,[ebx+force_disp32_zero]
    L_00414990:
        push esi
    L_00414991:
        call asm_FUN_0043ee30_0043ee30
    L_00414996:
        add esi,3ACh
    L_0041499c:
        dec ebx
    L_0041499d:
        jne short L_00414990
    L_0041499f:
        test byte ptr [edi+9EB4h],1
    L_004149a6:
        mov ecx,dword ptr [g_player]
    L_004149ac:
        TH10_REL8(0x75, 0x004149ac, VA_asm_target_00414a08)
    L_004149ae:
        test ecx,ecx
    L_004149b0:
        je asm_target_00414a5c
    L_004149b6:
        fld dword ptr [ecx+3C4h]
    L_004149bc:
        fcomp dword ptr [flt_416]
    L_004149c2:
        fnstsw ax
    L_004149c4:
        test ah,41h
    L_004149c7:
        jne asm_target_00414a5c
    L_004149cd:
        fld dword ptr [ecx+3C0h]
    L_004149d3:
        fcomp qword ptr [dbl_neg128]
    L_004149d9:
        fnstsw ax
    L_004149db:
        test ah,5
    L_004149de:
        TH10_REL8(0x7a, 0x004149de, VA_asm_target_00414a5c)
    L_004149e0:
        lea eax,[edi+8398h]
    L_004149e6:
        mov ecx,7
    L_004149eb:
        TH10_REL8(0xeb, 0x004149eb, VA_asm_FUN_00414900_part_004149f0)
        _emit 0x8d
        _emit 0x49
        _emit 0x00

    L_004149f0:
        mov word ptr [eax],3
    L_004149f5:
        add eax,3ACh
    L_004149fa:
        dec ecx
    L_004149fb:
        jne short L_004149f0
    L_004149fd:
        mov eax,dword ptr [edi+9EB4h]
    L_00414a03:
        or eax,1
    L_00414a06:
        jmp short L_00414a56
    L_00414a08:
        test ecx,ecx
    L_00414a0a:
        je short L_00414a5c
    L_00414a0c:
        fld dword ptr [ecx+3C4h]
    L_00414a12:
        fcomp dword ptr [flt_400]
    L_00414a18:
        fnstsw ax
    L_00414a1a:
        test ah,5
    L_00414a1d:
        jnp short L_00414a32
    L_00414a1f:
        fld dword ptr [ecx+3C0h]
    L_00414a25:
        fcomp qword ptr [dbl_neg112]
    L_00414a2b:
        fnstsw ax
    L_00414a2d:
        test ah,41h
    L_00414a30:
        jne short L_00414a5c
    L_00414a32:
        lea eax,[edi+8398h]
    L_00414a38:
        mov ecx,7
    L_00414a3d:
        TH10_NOP_LEA_ECX_DISP8()
    L_00414a40:
        mov word ptr [eax],2
    L_00414a45:
        add eax,3ACh
    L_00414a4a:
        dec ecx
    L_00414a4b:
        jne short L_00414a40
    L_00414a4d:
        mov eax,dword ptr [edi+9EB4h]
    L_00414a53:
        and eax,0FFFFFFFEh
    L_00414a56:
        mov dword ptr [edi+9EB4h],eax
    L_00414a5c:
        mov edi,dword ptr [esp+18h]
    L_00414a60:
        mov ebp,dword ptr [g_globals_gauge]
    L_00414a66:
        lea ecx,[edi+8094h]
    L_00414a6c:
        push ecx
    L_00414a6d:
        mov esi,2710h
    L_00414a72:
        call asm_FUN_0043ee30_0043ee30
    L_00414a77:
        add edi,8440h
    L_00414a7d:
        mov ebx,5
    L_00414a82:
        mov eax,ebp
    L_00414a84:
        cdq
    L_00414a85:
        idiv esi
    L_00414a87:
        mov ecx,dword ptr [esp+18h]
    L_00414a8b:
        mov ecx,dword ptr [ecx+9EC8h]
    L_00414a91:
        mov ebp,edx
    L_00414a93:
        lea edx,[eax+1Eh]
    L_00414a96:
        mov eax,edi
    L_00414a98:
        call asm_AnimationObject_ConfigureFromResource_0043e5a0
    L_00414a9d:
        mov eax,66666667h
    L_00414aa2:
        imul esi
    L_00414aa4:
        sar edx,2
    L_00414aa7:
        mov eax,edx
    L_00414aa9:
        shr eax,1Fh
    L_00414aac:
        add eax,edx
    L_00414aae:
        push edi
    L_00414aaf:
        mov esi,eax
    L_00414ab1:
        call asm_FUN_0043ee30_0043ee30
    L_00414ab6:
        add edi,3ACh
    L_00414abc:
        dec ebx
    L_00414abd:
        jne short L_00414a82
    L_00414abf:
        mov edi,dword ptr [esp+18h]
    L_00414ac3:
        lea ecx,[edi+969Ch]
    L_00414ac9:
        push ecx
    L_00414aca:
        call asm_FUN_0043ee30_0043ee30
    L_00414acf:
        mov eax,dword ptr [g_enemy_ctrl]
    L_00414ad4:
        test eax,eax
    L_00414ad6:
        je asm_target_0041508c
    L_00414adc:
        mov eax,dword ptr [eax+10h]
    L_00414adf:
        test eax,eax
    L_00414ae1:
        je asm_target_0041508c
    L_00414ae7:
        mov ecx,dword ptr [edi+9EB8h]
    L_00414aed:
        test ecx,ecx
    L_00414aef:
        jne asm_target_0041508c
    L_00414af5:
        mov ecx,dword ptr [eax+23FCh]
    L_00414afb:
        mov dword ptr [esp+10h],ecx
    L_00414aff:
        fild dword ptr [esp+10h]
    L_00414b03:
        mov dword ptr [edi+9E8Ch],ecx
    L_00414b09:
        fidiv dword ptr [eax+2400h]
    L_00414b0f:
        fst dword ptr [edi+9E88h]
    L_00414b15:
        fcomp dword ptr [edi+9E84h]
    L_00414b1b:
        fnstsw ax
    L_00414b1d:
        test ah,41h
    L_00414b20:
        jne short L_00414b34
    L_00414b22:
        fld dword ptr [edi+9E84h]
    L_00414b28:
        fadd dword ptr [flt_0_025]
    L_00414b2e:
        fstp dword ptr [edi+9E84h]
    L_00414b34:
        fld dword ptr [edi+9E84h]
    L_00414b3a:
        fcomp dword ptr [edi+9E88h]
    L_00414b40:
        fnstsw ax
    L_00414b42:
        test ah,41h
    L_00414b45:
        jne short L_00414b53
    L_00414b47:
        mov edx,dword ptr [edi+9E88h]
    L_00414b4d:
        mov dword ptr [edi+9E84h],edx
    L_00414b53:
        test byte ptr [edi+9EB4h],8
    L_00414b5a:
        mov ecx,dword ptr [g_player]
    L_00414b60:
        mov esi,dword ptr [g_sprt_ctrl]
    L_00414b66:
        fld dword ptr [ecx+3C4h]
    L_00414b6c:
        je asm_target_00414cae
    L_00414b72:
        fcomp dword ptr [flt_80]
    L_00414b78:
        fnstsw ax
    L_00414b7a:
        test ah,1
    L_00414b7d:
        je short L_00414b96
    L_00414b7f:
        fld dword ptr [ecx+3C0h]
    L_00414b85:
        fcomp dword ptr [flt_0]
    L_00414b8b:
        fnstsw ax
    L_00414b8d:
        test ah,41h
    L_00414b90:
        jne asm_target_00414def
    L_00414b96:
        mov eax,dword ptr [edi+9E90h]
    L_00414b9c:
        xor ebx,ebx
    L_00414b9e:
        test eax,eax
    L_00414ba0:
        jle short L_00414c1e
    L_00414ba2:
        lea edx,[edi+9E28h]
    L_00414ba8:
        mov ecx,dword ptr [edx]
    L_00414baa:
        test ecx,ecx
    L_00414bac:
        je short L_00414c10
    L_00414bae:
        mov eax,dword ptr [esi+72DAD4h]
    L_00414bb4:
        test eax,eax
    L_00414bb6:
        je short L_00414bc6
    L_00414bb8:
        mov ebp,dword ptr [eax]
    L_00414bba:
        cmp dword ptr [ebp],ecx
    L_00414bbd:
        je short L_00414be0
    L_00414bbf:
        mov eax,dword ptr [eax+4]
    L_00414bc2:
        test eax,eax
    L_00414bc4:
        jne short L_00414bb8
    L_00414bc6:
        mov eax,dword ptr [esi+72DADCh]
    L_00414bcc:
        test eax,eax
    L_00414bce:
        je short L_00414c10
    L_00414bd0:
        mov ebp,dword ptr [eax]
    L_00414bd2:
        cmp dword ptr [ebp],ecx
    L_00414bd5:
        je short L_00414be0
    L_00414bd7:
        mov eax,dword ptr [eax+4]
    L_00414bda:
        test eax,eax
    L_00414bdc:
        jne short L_00414bd0
    L_00414bde:
        jmp short L_00414c10
    L_00414be0:
        mov eax,dword ptr [eax]
    L_00414be2:
        test eax,eax
    L_00414be4:
        je short L_00414c10
    L_00414be6:
        mov ebp,dword ptr [eax+18h]
    L_00414be9:
        test ebp,ebp
    L_00414beb:
        mov ecx,2
    L_00414bf0:
        mov word ptr [eax+304h],cx
    L_00414bf7:
        jne short L_00414c10
    L_00414bf9:
        mov eax,dword ptr [eax+14h]
    L_00414bfc:
        test eax,eax
    L_00414bfe:
        je short L_00414c10
    L_00414c00:
        mov ebp,dword ptr [eax]
    L_00414c02:
        mov word ptr [ebp+304h],cx
    L_00414c09:
        mov eax,dword ptr [eax+4]
    L_00414c0c:
        test eax,eax
    L_00414c0e:
        jne short L_00414c00
    L_00414c10:
        mov eax,dword ptr [edi+9E90h]
    L_00414c16:
        inc ebx
    L_00414c17:
        add edx,4
    L_00414c1a:
        cmp ebx,eax
    L_00414c1c:
        jl short L_00414ba8
    L_00414c1e:
        mov ecx,dword ptr [edi+9E24h]
    L_00414c24:
        test ecx,ecx
    L_00414c26:
        TH10_REL8(0x74, 0x00414c26, VA_asm_target_00414ca0)
    L_00414c28:
        mov eax,dword ptr [esi+72DAD4h]
    L_00414c2e:
        test eax,eax
    L_00414c30:
        je short L_00414c3f
    L_00414c32:
        mov edx,dword ptr [eax]
    L_00414c34:
        cmp dword ptr [edx],ecx
    L_00414c36:
        je short L_00414c6b
    L_00414c38:
        mov eax,dword ptr [eax+4]
    L_00414c3b:
        test eax,eax
    L_00414c3d:
        jne short L_00414c32
    L_00414c3f:
        mov eax,dword ptr [esi+72DADCh]
    L_00414c45:
        test eax,eax
    L_00414c47:
        TH10_REL8(0x74, 0x00414c47, VA_asm_target_00414ca0)
    L_00414c49:
        lea esp,[esp+force_disp32_zero]
    L_00414c50:
        mov edx,dword ptr [eax]
    L_00414c52:
        cmp dword ptr [edx],ecx
    L_00414c54:
        je short L_00414c6b
    L_00414c56:
        mov eax,dword ptr [eax+4]
    L_00414c59:
        test eax,eax
    L_00414c5b:
        jne short L_00414c50
    L_00414c5d:
        mov eax,dword ptr [edi+9EB4h]
    L_00414c63:
        and eax,0FFFFFFF7h
    L_00414c66:
        jmp asm_target_00414de9
    L_00414c6b:
        mov eax,dword ptr [eax]
    L_00414c6d:
        test eax,eax
    L_00414c6f:
        TH10_REL8(0x74, 0x00414c6f, VA_asm_target_00414ca0)
    L_00414c71:
        mov edx,dword ptr [eax+18h]
    L_00414c74:
        test edx,edx
    L_00414c76:
        mov ecx,2
    L_00414c7b:
        mov word ptr [eax+304h],cx
    L_00414c82:
        TH10_REL8(0x75, 0x00414c82, VA_asm_target_00414ca0)
    L_00414c84:
        mov eax,dword ptr [eax+14h]
    L_00414c87:
        test eax,eax
    L_00414c89:
        TH10_REL8(0x74, 0x00414c89, VA_asm_target_00414ca0)
    L_00414c8b:
        TH10_REL8(0xeb, 0x00414c8b, VA_asm_FUN_00414900_part_00414c90)
        _emit 0x8d
        _emit 0x49
        _emit 0x00

    L_00414c90:
        mov edx,dword ptr [eax]
    L_00414c92:
        mov word ptr [edx+304h],cx
    L_00414c99:
        mov eax,dword ptr [eax+4]
    L_00414c9c:
        test eax,eax
    L_00414c9e:
        jne short L_00414c90
    L_00414ca0:
        mov eax,dword ptr [edi+9EB4h]
    L_00414ca6:
        and eax,0FFFFFFF7h
    L_00414ca9:
        jmp asm_target_00414de9
    L_00414cae:
        fcomp dword ptr [flt_64]
    L_00414cb4:
        fnstsw ax
    L_00414cb6:
        test ah,41h
    L_00414cb9:
        jp asm_target_00414def
    L_00414cbf:
        fld dword ptr [ecx+3C0h]
    L_00414cc5:
        fcomp dword ptr [flt_neg64]
    L_00414ccb:
        fnstsw ax
    L_00414ccd:
        test ah,5
    L_00414cd0:
        jp asm_target_00414def
    L_00414cd6:
        mov eax,dword ptr [edi+9E90h]
    L_00414cdc:
        xor ebx,ebx
    L_00414cde:
        test eax,eax
    L_00414ce0:
        jle asm_target_00414d6e
    L_00414ce6:
        lea edx,[edi+9E28h]
    L_00414cec:
        TH10_NOP_LEA_ESP_DISP8()
    L_00414cf0:
        mov ecx,dword ptr [edx]
    L_00414cf2:
        test ecx,ecx
    L_00414cf4:
        TH10_REL8(0x74, 0x00414cf4, VA_asm_target_00414d60)
    L_00414cf6:
        mov eax,dword ptr [esi+72DAD4h]
    L_00414cfc:
        test eax,eax
    L_00414cfe:
        je short L_00414d0e
    L_00414d00:
        mov ebp,dword ptr [eax]
    L_00414d02:
        cmp dword ptr [ebp],ecx
    L_00414d05:
        je short L_00414d28
    L_00414d07:
        mov eax,dword ptr [eax+4]
    L_00414d0a:
        test eax,eax
    L_00414d0c:
        jne short L_00414d00
    L_00414d0e:
        mov eax,dword ptr [esi+72DADCh]
    L_00414d14:
        test eax,eax
    L_00414d16:
        TH10_REL8(0x74, 0x00414d16, VA_asm_target_00414d60)
    L_00414d18:
        mov ebp,dword ptr [eax]
    L_00414d1a:
        cmp dword ptr [ebp],ecx
    L_00414d1d:
        je short L_00414d28
    L_00414d1f:
        mov eax,dword ptr [eax+4]
    L_00414d22:
        test eax,eax
    L_00414d24:
        jne short L_00414d18
    L_00414d26:
        TH10_REL8(0xeb, 0x00414d26, VA_asm_target_00414d60)
    L_00414d28:
        mov eax,dword ptr [eax]
    L_00414d2a:
        test eax,eax
    L_00414d2c:
        TH10_REL8(0x74, 0x00414d2c, VA_asm_target_00414d60)
    L_00414d2e:
        mov ebp,dword ptr [eax+18h]
    L_00414d31:
        test ebp,ebp
    L_00414d33:
        mov ecx,3
    L_00414d38:
        mov word ptr [eax+304h],cx
    L_00414d3f:
        TH10_REL8(0x75, 0x00414d3f, VA_asm_target_00414d60)
    L_00414d41:
        mov eax,dword ptr [eax+14h]
    L_00414d44:
        test eax,eax
    L_00414d46:
        TH10_REL8(0x74, 0x00414d46, VA_asm_target_00414d60)
    L_00414d48:
        TH10_REL8(0xeb, 0x00414d48, VA_asm_FUN_00414900_part_00414d50)
        _emit 0x8d
        _emit 0x9b
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x00

    L_00414d50:
        mov ebp,dword ptr [eax]
    L_00414d52:
        mov word ptr [ebp+304h],cx
    L_00414d59:
        mov eax,dword ptr [eax+4]
    L_00414d5c:
        test eax,eax
    L_00414d5e:
        jne short L_00414d50
    L_00414d60:
        mov eax,dword ptr [edi+9E90h]
    L_00414d66:
        inc ebx
    L_00414d67:
        add edx,4
    L_00414d6a:
        cmp ebx,eax
    L_00414d6c:
        TH10_REL8(0x7c, 0x00414d6c, VA_asm_target_00414cf0)
    L_00414d6e:
        mov ecx,dword ptr [edi+9E24h]
    L_00414d74:
        test ecx,ecx
    L_00414d76:
        je short L_00414de0
    L_00414d78:
        mov eax,dword ptr [esi+72DAD4h]
    L_00414d7e:
        test eax,eax
    L_00414d80:
        je short L_00414d8f
    L_00414d82:
        mov edx,dword ptr [eax]
    L_00414d84:
        cmp dword ptr [edx],ecx
    L_00414d86:
        je short L_00414daf
    L_00414d88:
        mov eax,dword ptr [eax+4]
    L_00414d8b:
        test eax,eax
    L_00414d8d:
        jne short L_00414d82
    L_00414d8f:
        mov eax,dword ptr [esi+72DADCh]
    L_00414d95:
        test eax,eax
    L_00414d97:
        je short L_00414de0
    L_00414d99:
        lea esp,[esp+force_disp32_zero]
    L_00414da0:
        mov edx,dword ptr [eax]
    L_00414da2:
        cmp dword ptr [edx],ecx
    L_00414da4:
        je short L_00414daf
    L_00414da6:
        mov eax,dword ptr [eax+4]
    L_00414da9:
        test eax,eax
    L_00414dab:
        jne short L_00414da0
    L_00414dad:
        jmp short L_00414de0
    L_00414daf:
        mov eax,dword ptr [eax]
    L_00414db1:
        test eax,eax
    L_00414db3:
        je short L_00414de0
    L_00414db5:
        mov edx,dword ptr [eax+18h]
    L_00414db8:
        test edx,edx
    L_00414dba:
        mov ecx,3
    L_00414dbf:
        mov word ptr [eax+304h],cx
    L_00414dc6:
        jne short L_00414de0
    L_00414dc8:
        mov eax,dword ptr [eax+14h]
    L_00414dcb:
        test eax,eax
    L_00414dcd:
        je short L_00414de0
    L_00414dcf:
        nop
    L_00414dd0:
        mov edx,dword ptr [eax]
    L_00414dd2:
        mov word ptr [edx+304h],cx
    L_00414dd9:
        mov eax,dword ptr [eax+4]
    L_00414ddc:
        test eax,eax
    L_00414dde:
        jne short L_00414dd0
    L_00414de0:
        mov eax,dword ptr [edi+9EB4h]
    L_00414de6:
        or eax,8
    L_00414de9:
        mov dword ptr [edi+9EB4h],eax
    L_00414def:
        mov eax,dword ptr [edi+9E24h]
    L_00414df5:
        test eax,eax
    L_00414df7:
        jne asm_target_00414f33
    L_00414dfd:
        mov eax,dword ptr [g_globals_stage]
    L_00414e02:
        dec eax
    L_00414e03:
        cmp eax,6
    L_00414e06:
        mov ebp,85h
    L_00414e0b:
        ja short L_00414e87
    L_00414e0d:
        jmp dword ptr [eax*4+4157E0h]
    L_00414e14:
        cmp dword ptr [g_stage_progress],18h
    L_00414e1b:
        jl short L_00414e87
    L_00414e1d:
        mov ebp,86h
    L_00414e22:
        jmp short L_00414e87
    L_00414e24:
        cmp dword ptr [g_stage_progress],18h
    L_00414e2b:
        jl asm_target_00414f33
    L_00414e31:
        mov ebp,87h
    L_00414e36:
        jmp short L_00414e87
    L_00414e38:
        cmp dword ptr [g_stage_progress],18h
    L_00414e3f:
        jl asm_target_00414f33
    L_00414e45:
        mov ebp,88h
    L_00414e4a:
        jmp short L_00414e87
    L_00414e4c:
        mov edx,dword ptr [g_stage_progress]
    L_00414e52:
        xor eax,eax
    L_00414e54:
        cmp edx,18h
    L_00414e57:
        setge al
    L_00414e5a:
        add eax,89h
    L_00414e5f:
        mov ebp,eax
    L_00414e61:
        jmp short L_00414e87
    L_00414e63:
        mov ebp,8Bh
    L_00414e68:
        jmp short L_00414e87
    L_00414e6a:
        mov ebp,8Ch
    L_00414e6f:
        jmp short L_00414e87
    L_00414e71:
        mov edx,dword ptr [g_stage_progress]
    L_00414e77:
        xor ecx,ecx
    L_00414e79:
        cmp edx,18h
    L_00414e7c:
        setge cl
    L_00414e7f:
        add ecx,8Ch
    L_00414e85:
        mov ebp,ecx
    L_00414e87:
        mov edx,dword ptr [esp+18h]
    L_00414e8b:
        mov ebx,dword ptr [edx+9EC8h]
    L_00414e91:
        call asm_FUN_00449950_00449950
    L_00414e96:
        mov edi,eax
    L_00414e98:
        mov ecx,dword ptr [edi+35Ch]
    L_00414e9e:
        or ecx,40000000h
    L_00414ea4:
        push ebp
    L_00414ea5:
        mov dword ptr [edi+35Ch],ecx
    L_00414eab:
        push edi
    L_00414eac:
        mov ecx,ebx
    L_00414eae:
        mov dword ptr [edi+20h],0Fh
    L_00414eb5:
        call asm_FUN_00449870_00449870
    L_00414eba:
        mov esi,dword ptr [g_sprt_ctrl]
    L_00414ec0:
        lea eax,[edi+4]
    L_00414ec3:
        xor ecx,ecx
    L_00414ec5:
        mov dword ptr [eax],edi
    L_00414ec7:
        mov dword ptr [eax+4],ecx
    L_00414eca:
        mov dword ptr [eax+8],ecx
    L_00414ecd:
        cmp dword ptr [esi+72DAD4h],ecx
    L_00414ed3:
        jne short L_00414edd
    L_00414ed5:
        mov dword ptr [esi+72DAD4h],eax
    L_00414edb:
        jmp short L_00414ef9
    L_00414edd:
        mov ecx,dword ptr [esi+72DAD8h]
    L_00414ee3:
        mov edx,dword ptr [ecx+4]
    L_00414ee6:
        test edx,edx
    L_00414ee8:
        je short L_00414ef3
    L_00414eea:
        mov dword ptr [eax+4],edx
    L_00414eed:
        mov edx,dword ptr [ecx+4]
    L_00414ef0:
        mov dword ptr [edx+8],eax
    L_00414ef3:
        mov dword ptr [ecx+4],eax
    L_00414ef6:
        mov dword ptr [eax+8],ecx
    L_00414ef9:
        mov dword ptr [esi+72DAD8h],eax
    L_00414eff:
        mov ecx,dword ptr [esi+732454h]
    L_00414f05:
        inc ecx
    L_00414f06:
        mov eax,ecx
    L_00414f08:
        test eax,eax
    L_00414f0a:
        mov dword ptr [esi+732454h],ecx
    L_00414f10:
        jne short L_00414f19
    L_00414f12:
        inc eax
    L_00414f13:
        mov dword ptr [esi+732454h],eax
    L_00414f19:
        mov eax,dword ptr [esi+732454h]
    L_00414f1f:
        mov edx,dword ptr [esp+18h]
    L_00414f23:
        mov dword ptr [edi],eax
    L_00414f25:
        mov ecx,dword ptr [esi+732454h]
    L_00414f2b:
        mov dword ptr [edx+9E24h],ecx
    L_00414f31:
        mov edi,edx
    L_00414f33:
        lea edx,[edi+9E28h]
    L_00414f39:
        xor ebx,ebx
    L_00414f3b:
        mov dword ptr [esp+10h],edx
    L_00414f3f:
        nop
    L_00414f40:
        cmp ebx,dword ptr [edi+9E90h]
    L_00414f46:
        jge asm_target_00414ffc
    L_00414f4c:
        cmp dword ptr [edx],0
    L_00414f4f:
        jne asm_target_00415076
    L_00414f55:
        mov eax,dword ptr [esp+18h]
    L_00414f59:
        mov ebp,dword ptr [eax+9EC8h]
    L_00414f5f:
        call asm_FUN_00449950_00449950
    L_00414f64:
        mov edi,eax
    L_00414f66:
        or dword ptr [edi+35Ch],40000000h
    L_00414f70:
        lea ecx,[ebx+5Bh]
    L_00414f73:
        push ecx
    L_00414f74:
        push edi
    L_00414f75:
        mov ecx,ebp
    L_00414f77:
        mov dword ptr [edi+20h],0Fh
    L_00414f7e:
        call asm_FUN_00449870_00449870
    L_00414f83:
        mov esi,dword ptr [g_sprt_ctrl]
    L_00414f89:
        lea eax,[edi+4]
    L_00414f8c:
        xor ecx,ecx
    L_00414f8e:
        mov dword ptr [eax],edi
    L_00414f90:
        mov dword ptr [eax+4],ecx
    L_00414f93:
        mov dword ptr [eax+8],ecx
    L_00414f96:
        cmp dword ptr [esi+72DAD4h],ecx
    L_00414f9c:
        jne short L_00414fa6
    L_00414f9e:
        mov dword ptr [esi+72DAD4h],eax
    L_00414fa4:
        jmp short L_00414fc2
    L_00414fa6:
        mov ecx,dword ptr [esi+72DAD8h]
    L_00414fac:
        mov edx,dword ptr [ecx+4]
    L_00414faf:
        test edx,edx
    L_00414fb1:
        je short L_00414fbc
    L_00414fb3:
        mov dword ptr [eax+4],edx
    L_00414fb6:
        mov edx,dword ptr [ecx+4]
    L_00414fb9:
        mov dword ptr [edx+8],eax
    L_00414fbc:
        mov dword ptr [ecx+4],eax
    L_00414fbf:
        mov dword ptr [eax+8],ecx
    L_00414fc2:
        mov dword ptr [esi+72DAD8h],eax
    L_00414fc8:
        mov ecx,dword ptr [esi+732454h]
    L_00414fce:
        inc ecx
    L_00414fcf:
        mov eax,ecx
    L_00414fd1:
        test eax,eax
    L_00414fd3:
        mov dword ptr [esi+732454h],ecx
    L_00414fd9:
        jne short L_00414fe2
    L_00414fdb:
        inc eax
    L_00414fdc:
        mov dword ptr [esi+732454h],eax
    L_00414fe2:
        mov eax,dword ptr [esi+732454h]
    L_00414fe8:
        mov edx,dword ptr [esp+10h]
    L_00414fec:
        mov dword ptr [edi],eax
    L_00414fee:
        mov ecx,dword ptr [esi+732454h]
    L_00414ff4:
        mov edi,dword ptr [esp+18h]
    L_00414ff8:
        mov dword ptr [edx],ecx
    L_00414ffa:
        TH10_REL8(0xeb, 0x00414ffa, VA_asm_target_00415076)
    L_00414ffc:
        mov ecx,dword ptr [edx]
    L_00414ffe:
        test ecx,ecx
    L_00415000:
        TH10_REL8(0x74, 0x00415000, VA_asm_target_00415076)
    L_00415002:
        mov eax,dword ptr [esi+72DAD4h]
    L_00415008:
        test eax,eax
    L_0041500a:
        je short L_0041501e
    L_0041500c:
        TH10_NOP_LEA_ESP_DISP8()
    L_00415010:
        mov ebp,dword ptr [eax]
    L_00415012:
        cmp dword ptr [ebp],ecx
    L_00415015:
        je short L_00415038
    L_00415017:
        mov eax,dword ptr [eax+4]
    L_0041501a:
        test eax,eax
    L_0041501c:
        jne short L_00415010
    L_0041501e:
        mov eax,dword ptr [esi+72DADCh]
    L_00415024:
        test eax,eax
    L_00415026:
        TH10_REL8(0x74, 0x00415026, VA_asm_target_00415070)
    L_00415028:
        mov ebp,dword ptr [eax]
    L_0041502a:
        cmp dword ptr [ebp],ecx
    L_0041502d:
        je short L_00415038
    L_0041502f:
        mov eax,dword ptr [eax+4]
    L_00415032:
        test eax,eax
    L_00415034:
        jne short L_00415028
    L_00415036:
        TH10_REL8(0xeb, 0x00415036, VA_asm_target_00415070)
    L_00415038:
        mov eax,dword ptr [eax]
    L_0041503a:
        test eax,eax
    L_0041503c:
        TH10_REL8(0x74, 0x0041503c, VA_asm_target_00415070)
    L_0041503e:
        mov ebp,dword ptr [eax+18h]
    L_00415041:
        test ebp,ebp
    L_00415043:
        mov ecx,1
    L_00415048:
        mov word ptr [eax+304h],cx
    L_0041504f:
        TH10_REL8(0x75, 0x0041504f, VA_asm_target_00415070)
    L_00415051:
        mov eax,dword ptr [eax+14h]
    L_00415054:
        test eax,eax
    L_00415056:
        TH10_REL8(0x74, 0x00415056, VA_asm_target_00415070)
    L_00415058:
        TH10_REL8(0xeb, 0x00415058, VA_asm_FUN_00414900_part_00415060)
        _emit 0x8d
        _emit 0x9b
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x00

    L_00415060:
        mov ebp,dword ptr [eax]
    L_00415062:
        mov word ptr [ebp+304h],cx
    L_00415069:
        mov eax,dword ptr [eax+4]
    L_0041506c:
        test eax,eax
    L_0041506e:
        jne short L_00415060
    L_00415070:
        mov dword ptr [edx],0
    L_00415076:
        inc ebx
    L_00415077:
        add edx,4
    L_0041507a:
        cmp ebx,0Ah
    L_0041507d:
        mov dword ptr [esp+10h],edx
    L_00415081:
        jb asm_target_00414f40
    L_00415087:
        jmp asm_target_0041513c
    L_0041508c:
        mov ecx,dword ptr [edi+9E24h]
    L_00415092:
        test ecx,ecx
    L_00415094:
        je short L_0041510a
    L_00415096:
        mov edx,dword ptr [g_sprt_ctrl]
    L_0041509c:
        mov eax,dword ptr [edx+72DAD4h]
    L_004150a2:
        test eax,eax
    L_004150a4:
        je short L_004150b3
    L_004150a6:
        mov esi,dword ptr [eax]
    L_004150a8:
        cmp dword ptr [esi],ecx
    L_004150aa:
        je short L_004150cf
    L_004150ac:
        mov eax,dword ptr [eax+4]
    L_004150af:
        test eax,eax
    L_004150b1:
        jne short L_004150a6
    L_004150b3:
        mov eax,dword ptr [edx+72DADCh]
    L_004150b9:
        test eax,eax
    L_004150bb:
        je short L_00415100
    L_004150bd:
        TH10_NOP_LEA_ECX_DISP8()
    L_004150c0:
        mov edx,dword ptr [eax]
    L_004150c2:
        cmp dword ptr [edx],ecx
    L_004150c4:
        je short L_004150cf
    L_004150c6:
        mov eax,dword ptr [eax+4]
    L_004150c9:
        test eax,eax
    L_004150cb:
        jne short L_004150c0
    L_004150cd:
        jmp short L_00415100
    L_004150cf:
        mov eax,dword ptr [eax]
    L_004150d1:
        test eax,eax
    L_004150d3:
        je short L_00415100
    L_004150d5:
        mov edx,dword ptr [eax+18h]
    L_004150d8:
        test edx,edx
    L_004150da:
        mov ecx,1
    L_004150df:
        mov word ptr [eax+304h],cx
    L_004150e6:
        jne short L_00415100
    L_004150e8:
        mov eax,dword ptr [eax+14h]
    L_004150eb:
        test eax,eax
    L_004150ed:
        je short L_00415100
    L_004150ef:
        nop
    L_004150f0:
        mov edx,dword ptr [eax]
    L_004150f2:
        mov word ptr [edx+304h],cx
    L_004150f9:
        mov eax,dword ptr [eax+4]
    L_004150fc:
        test eax,eax
    L_004150fe:
        jne short L_004150f0
    L_00415100:
        mov dword ptr [edi+9E24h],0
    L_0041510a:
        mov dword ptr [edi+9E84h],0
    L_00415114:
        mov dword ptr [edi+9E94h],0
    L_0041511e:
        mov dword ptr [edi+9E9Ch],0
    L_00415128:
        mov dword ptr [edi+9EA4h],0
    L_00415132:
        mov dword ptr [edi+9EACh],0
    L_0041513c:
        mov esi,dword ptr [edi+9EB8h]
    L_00415142:
        test esi,esi
    L_00415144:
        je asm_target_0041549a
    L_0041514a:
        push esi
    L_0041514b:
        call asm_FUN_00415e90_00415e90
    L_00415150:
        test eax,eax
    L_00415152:
        jne short L_004151a5
    L_00415154:
        mov edx,dword ptr [esi+8]
    L_00415157:
        mov ecx,dword ptr [esi+10h]
    L_0041515a:
        mov dword ptr [esi+4],edx
    L_0041515d:
        fld dword ptr [ecx]
    L_0041515f:
        fcomp dword ptr [flt_0_99]
    L_00415165:
        fnstsw ax
    L_00415167:
        test ah,41h
    L_0041516a:
        jne short L_00415190
    L_0041516c:
        fld dword ptr [ecx]
    L_0041516e:
        fcomp dword ptr [flt_1_01]
    L_00415174:
        fnstsw ax
    L_00415176:
        test ah,5
    L_00415179:
        jp short L_00415190
    L_0041517b:
        fld dword ptr [esi+0Ch]
    L_0041517e:
        inc edx
    L_0041517f:
        fadd dword ptr [flt_1]
    L_00415185:
        mov dword ptr [esi+8],edx
    L_00415188:
        fstp dword ptr [esi+0Ch]
    L_0041518b:
        jmp asm_target_0041549a
    L_00415190:
        fld dword ptr [ecx]
    L_00415192:
        fadd dword ptr [esi+0Ch]
    L_00415195:
        fst dword ptr [esi+0Ch]
    L_00415198:
        call asm_FUN_00463b2c_00463b2c
    L_0041519d:
        mov dword ptr [esi+8],eax
    L_004151a0:
        jmp asm_target_0041549a
    L_004151a5:
        mov ebx,dword ptr [edi+9EB8h]
    L_004151ab:
        test ebx,ebx
    L_004151ad:
        je asm_target_00415490
    L_004151b3:
        mov ecx,dword ptr [ebx+40h]
    L_004151b6:
        test ecx,ecx
    L_004151b8:
        mov edx,dword ptr [g_sprt_ctrl]
    L_004151be:
        mov esi,4000000h
    L_004151c3:
        je short L_0041522f
    L_004151c5:
        mov eax,dword ptr [edx+72DAD4h]
    L_004151cb:
        test eax,eax
    L_004151cd:
        je short L_004151de
    L_004151cf:
        nop
    L_004151d0:
        mov ebp,dword ptr [eax]
    L_004151d2:
        cmp dword ptr [ebp],ecx
    L_004151d5:
        je short L_004151f8
    L_004151d7:
        mov eax,dword ptr [eax+4]
    L_004151da:
        test eax,eax
    L_004151dc:
        jne short L_004151d0
    L_004151de:
        mov eax,dword ptr [edx+72DADCh]
    L_004151e4:
        test eax,eax
    L_004151e6:
        je short L_0041522f
    L_004151e8:
        mov ebp,dword ptr [eax]
    L_004151ea:
        cmp dword ptr [ebp],ecx
    L_004151ed:
        je short L_004151f8
    L_004151ef:
        mov eax,dword ptr [eax+4]
    L_004151f2:
        test eax,eax
    L_004151f4:
        jne short L_004151e8
    L_004151f6:
        jmp short L_0041522f
    L_004151f8:
        mov eax,dword ptr [eax]
    L_004151fa:
        test eax,eax
    L_004151fc:
        je short L_0041522f
    L_004151fe:
        mov ebp,dword ptr [eax+35Ch]
    L_00415204:
        mov ecx,dword ptr [eax+18h]
    L_00415207:
        or ebp,esi
    L_00415209:
        test ecx,ecx
    L_0041520b:
        mov dword ptr [eax+35Ch],ebp
    L_00415211:
        jne short L_0041522f
    L_00415213:
        mov eax,dword ptr [eax+14h]
    L_00415216:
        test eax,eax
    L_00415218:
        je short L_0041522f
    L_0041521a:
        lea ebx,[ebx+force_disp32_zero]
    L_00415220:
        mov ecx,dword ptr [eax]
    L_00415222:
        or dword ptr [ecx+35Ch],esi
    L_00415228:
        mov eax,dword ptr [eax+4]
    L_0041522b:
        test eax,eax
    L_0041522d:
        jne short L_00415220
    L_0041522f:
        mov dword ptr [ebx+40h],0
    L_00415236:
        mov ecx,dword ptr [ebx+44h]
    L_00415239:
        test ecx,ecx
    L_0041523b:
        je short L_004152a1
    L_0041523d:
        mov eax,dword ptr [edx+72DAD4h]
    L_00415243:
        test eax,eax
    L_00415245:
        je short L_00415255
    L_00415247:
        mov ebp,dword ptr [eax]
    L_00415249:
        cmp dword ptr [ebp],ecx
    L_0041524c:
        je short L_00415270
    L_0041524e:
        mov eax,dword ptr [eax+4]
    L_00415251:
        test eax,eax
    L_00415253:
        jne short L_00415247
    L_00415255:
        mov eax,dword ptr [edx+72DADCh]
    L_0041525b:
        test eax,eax
    L_0041525d:
        je short L_004152a1
    L_0041525f:
        nop
    L_00415260:
        mov ebp,dword ptr [eax]
    L_00415262:
        cmp dword ptr [ebp],ecx
    L_00415265:
        je short L_00415270
    L_00415267:
        mov eax,dword ptr [eax+4]
    L_0041526a:
        test eax,eax
    L_0041526c:
        jne short L_00415260
    L_0041526e:
        jmp short L_004152a1
    L_00415270:
        mov eax,dword ptr [eax]
    L_00415272:
        test eax,eax
    L_00415274:
        je short L_004152a1
    L_00415276:
        mov ebp,dword ptr [eax+35Ch]
    L_0041527c:
        mov ecx,dword ptr [eax+18h]
    L_0041527f:
        or ebp,esi
    L_00415281:
        test ecx,ecx
    L_00415283:
        mov dword ptr [eax+35Ch],ebp
    L_00415289:
        jne short L_004152a1
    L_0041528b:
        mov eax,dword ptr [eax+14h]
    L_0041528e:
        test eax,eax
    L_00415290:
        je short L_004152a1
    L_00415292:
        mov ecx,dword ptr [eax]
    L_00415294:
        or dword ptr [ecx+35Ch],esi
    L_0041529a:
        mov eax,dword ptr [eax+4]
    L_0041529d:
        test eax,eax
    L_0041529f:
        jne short L_00415292
    L_004152a1:
        mov dword ptr [ebx+44h],0
    L_004152a8:
        mov ecx,dword ptr [ebx+48h]
    L_004152ab:
        test ecx,ecx
    L_004152ad:
        je short L_0041531f
    L_004152af:
        mov eax,dword ptr [edx+72DAD4h]
    L_004152b5:
        test eax,eax
    L_004152b7:
        je short L_004152ce
    L_004152b9:
        lea esp,[esp+force_disp32_zero]
    L_004152c0:
        mov ebp,dword ptr [eax]
    L_004152c2:
        cmp dword ptr [ebp],ecx
    L_004152c5:
        je short L_004152e8
    L_004152c7:
        mov eax,dword ptr [eax+4]
    L_004152ca:
        test eax,eax
    L_004152cc:
        jne short L_004152c0
    L_004152ce:
        mov eax,dword ptr [edx+72DADCh]
    L_004152d4:
        test eax,eax
    L_004152d6:
        je short L_0041531f
    L_004152d8:
        mov ebp,dword ptr [eax]
    L_004152da:
        cmp dword ptr [ebp],ecx
    L_004152dd:
        je short L_004152e8
    L_004152df:
        mov eax,dword ptr [eax+4]
    L_004152e2:
        test eax,eax
    L_004152e4:
        jne short L_004152d8
    L_004152e6:
        jmp short L_0041531f
    L_004152e8:
        mov eax,dword ptr [eax]
    L_004152ea:
        test eax,eax
    L_004152ec:
        je short L_0041531f
    L_004152ee:
        mov ebp,dword ptr [eax+35Ch]
    L_004152f4:
        mov ecx,dword ptr [eax+18h]
    L_004152f7:
        or ebp,esi
    L_004152f9:
        test ecx,ecx
    L_004152fb:
        mov dword ptr [eax+35Ch],ebp
    L_00415301:
        jne short L_0041531f
    L_00415303:
        mov eax,dword ptr [eax+14h]
    L_00415306:
        test eax,eax
    L_00415308:
        je short L_0041531f
    L_0041530a:
        lea ebx,[ebx+force_disp32_zero]
    L_00415310:
        mov ecx,dword ptr [eax]
    L_00415312:
        or dword ptr [ecx+35Ch],esi
    L_00415318:
        mov eax,dword ptr [eax+4]
    L_0041531b:
        test eax,eax
    L_0041531d:
        jne short L_00415310
    L_0041531f:
        mov dword ptr [ebx+48h],0
    L_00415326:
        mov ecx,dword ptr [ebx+4Ch]
    L_00415329:
        test ecx,ecx
    L_0041532b:
        je short L_00415391
    L_0041532d:
        mov eax,dword ptr [edx+72DAD4h]
    L_00415333:
        test eax,eax
    L_00415335:
        je short L_00415345
    L_00415337:
        mov ebp,dword ptr [eax]
    L_00415339:
        cmp dword ptr [ebp],ecx
    L_0041533c:
        je short L_00415360
    L_0041533e:
        mov eax,dword ptr [eax+4]
    L_00415341:
        test eax,eax
    L_00415343:
        jne short L_00415337
    L_00415345:
        mov eax,dword ptr [edx+72DADCh]
    L_0041534b:
        test eax,eax
    L_0041534d:
        je short L_00415391
    L_0041534f:
        nop
    L_00415350:
        mov ebp,dword ptr [eax]
    L_00415352:
        cmp dword ptr [ebp],ecx
    L_00415355:
        je short L_00415360
    L_00415357:
        mov eax,dword ptr [eax+4]
    L_0041535a:
        test eax,eax
    L_0041535c:
        jne short L_00415350
    L_0041535e:
        jmp short L_00415391
    L_00415360:
        mov eax,dword ptr [eax]
    L_00415362:
        test eax,eax
    L_00415364:
        je short L_00415391
    L_00415366:
        mov ebp,dword ptr [eax+35Ch]
    L_0041536c:
        mov ecx,dword ptr [eax+18h]
    L_0041536f:
        or ebp,esi
    L_00415371:
        test ecx,ecx
    L_00415373:
        mov dword ptr [eax+35Ch],ebp
    L_00415379:
        jne short L_00415391
    L_0041537b:
        mov eax,dword ptr [eax+14h]
    L_0041537e:
        test eax,eax
    L_00415380:
        je short L_00415391
    L_00415382:
        mov ecx,dword ptr [eax]
    L_00415384:
        or dword ptr [ecx+35Ch],esi
    L_0041538a:
        mov eax,dword ptr [eax+4]
    L_0041538d:
        test eax,eax
    L_0041538f:
        jne short L_00415382
    L_00415391:
        mov dword ptr [ebx+4Ch],0
    L_00415398:
        mov ecx,dword ptr [ebx+50h]
    L_0041539b:
        test ecx,ecx
    L_0041539d:
        je short L_0041540f
    L_0041539f:
        mov eax,dword ptr [edx+72DAD4h]
    L_004153a5:
        test eax,eax
    L_004153a7:
        je short L_004153be
    L_004153a9:
        lea esp,[esp+force_disp32_zero]
    L_004153b0:
        mov ebp,dword ptr [eax]
    L_004153b2:
        cmp dword ptr [ebp],ecx
    L_004153b5:
        je short L_004153d8
    L_004153b7:
        mov eax,dword ptr [eax+4]
    L_004153ba:
        test eax,eax
    L_004153bc:
        jne short L_004153b0
    L_004153be:
        mov eax,dword ptr [edx+72DADCh]
    L_004153c4:
        test eax,eax
    L_004153c6:
        je short L_0041540f
    L_004153c8:
        mov ebp,dword ptr [eax]
    L_004153ca:
        cmp dword ptr [ebp],ecx
    L_004153cd:
        je short L_004153d8
    L_004153cf:
        mov eax,dword ptr [eax+4]
    L_004153d2:
        test eax,eax
    L_004153d4:
        jne short L_004153c8
    L_004153d6:
        jmp short L_0041540f
    L_004153d8:
        mov eax,dword ptr [eax]
    L_004153da:
        test eax,eax
    L_004153dc:
        je short L_0041540f
    L_004153de:
        mov ebp,dword ptr [eax+35Ch]
    L_004153e4:
        mov ecx,dword ptr [eax+18h]
    L_004153e7:
        or ebp,esi
    L_004153e9:
        test ecx,ecx
    L_004153eb:
        mov dword ptr [eax+35Ch],ebp
    L_004153f1:
        jne short L_0041540f
    L_004153f3:
        mov eax,dword ptr [eax+14h]
    L_004153f6:
        test eax,eax
    L_004153f8:
        je short L_0041540f
    L_004153fa:
        lea ebx,[ebx+force_disp32_zero]
    L_00415400:
        mov ecx,dword ptr [eax]
    L_00415402:
        or dword ptr [ecx+35Ch],esi
    L_00415408:
        mov eax,dword ptr [eax+4]
    L_0041540b:
        test eax,eax
    L_0041540d:
        jne short L_00415400
    L_0041540f:
        mov dword ptr [ebx+50h],0
    L_00415416:
        mov ecx,dword ptr [ebx+54h]
    L_00415419:
        test ecx,ecx
    L_0041541b:
        je short L_00415480
    L_0041541d:
        mov eax,dword ptr [edx+72DAD4h]
    L_00415423:
        test eax,eax
    L_00415425:
        je short L_00415435
    L_00415427:
        mov ebp,dword ptr [eax]
    L_00415429:
        cmp dword ptr [ebp],ecx
    L_0041542c:
        je short L_0041544f
    L_0041542e:
        mov eax,dword ptr [eax+4]
    L_00415431:
        test eax,eax
    L_00415433:
        jne short L_00415427
    L_00415435:
        mov eax,dword ptr [edx+72DADCh]
    L_0041543b:
        test eax,eax
    L_0041543d:
        je short L_00415480
    L_0041543f:
        nop
    L_00415440:
        mov edx,dword ptr [eax]
    L_00415442:
        cmp dword ptr [edx],ecx
    L_00415444:
        je short L_0041544f
    L_00415446:
        mov eax,dword ptr [eax+4]
    L_00415449:
        test eax,eax
    L_0041544b:
        jne short L_00415440
    L_0041544d:
        jmp short L_00415480
    L_0041544f:
        mov eax,dword ptr [eax]
    L_00415451:
        test eax,eax
    L_00415453:
        je short L_00415480
    L_00415455:
        mov edx,dword ptr [eax+35Ch]
    L_0041545b:
        mov ecx,dword ptr [eax+18h]
    L_0041545e:
        or edx,esi
    L_00415460:
        test ecx,ecx
    L_00415462:
        mov dword ptr [eax+35Ch],edx
    L_00415468:
        jne short L_00415480
    L_0041546a:
        mov eax,dword ptr [eax+14h]
    L_0041546d:
        test eax,eax
    L_0041546f:
        je short L_00415480
    L_00415471:
        mov ecx,dword ptr [eax]
    L_00415473:
        or dword ptr [ecx+35Ch],esi
    L_00415479:
        mov eax,dword ptr [eax+4]
    L_0041547c:
        test eax,eax
    L_0041547e:
        jne short L_00415471
    L_00415480:
        push ebx
    L_00415481:
        mov dword ptr [ebx+54h],0
    L_00415488:
        call asm_free_004524a1
    L_0041548d:
        add esp,4
    L_00415490:
        mov dword ptr [edi+9EB8h],0
    L_0041549a:
        mov ecx,dword ptr [g_enemy_ctrl]
    L_004154a0:
        test ecx,ecx
    L_004154a2:
        je asm_target_00415764
    L_004154a8:
        mov eax,dword ptr [edi+9EC0h]
    L_004154ae:
        test eax,eax
    L_004154b0:
        jl asm_target_004155ba
    L_004154b6:
        mov edx,dword ptr [ecx+10h]
    L_004154b9:
        test edx,edx
    L_004154bb:
        je asm_target_004155ba
    L_004154c1:
        mov edx,dword ptr [edi+9EB8h]
    L_004154c7:
        test edx,edx
    L_004154c9:
        jne asm_target_004155ba
    L_004154cf:
        mov ecx,dword ptr [edi+9EC4h]
    L_004154d5:
        cmp eax,ecx
    L_004154d7:
        jge short L_0041553f
    L_004154d9:
        cmp eax,5
    L_004154dc:
        jg short L_0041550c
    L_004154de:
        mov eax,dword ptr [esp+18h]
    L_004154e2:
        mov ecx,9
    L_004154e7:
        mov word ptr [eax+7C40h],cx
    L_004154ee:
        mov word ptr [eax+7FECh],cx
    L_004154f5:
        push 0
    L_004154f7:
        mov edi,24h
    L_004154fc:
        mov ecx,492590h
    L_00415501:
        call asm_AnimationManager_QueueResource_0043dc90
    L_00415506:
        mov edi,dword ptr [esp+18h]
    L_0041550a:
        jmp short L_00415554
    L_0041550c:
        cmp eax,0Ah
    L_0041550f:
        jg short L_00415554
    L_00415511:
        mov eax,dword ptr [esp+18h]
    L_00415515:
        mov ecx,8
    L_0041551a:
        mov word ptr [eax+7C40h],cx
    L_00415521:
        mov word ptr [eax+7FECh],cx
    L_00415528:
        push 0
    L_0041552a:
        mov edi,1Bh
    L_0041552f:
        mov ecx,492590h
    L_00415534:
        call asm_AnimationManager_QueueResource_0043dc90
    L_00415539:
        mov edi,dword ptr [esp+18h]
    L_0041553d:
        jmp short L_00415554
    L_0041553f:
        jle short L_00415554
    L_00415541:
        mov eax,7
    L_00415546:
        mov word ptr [edi+7C40h],ax
    L_0041554d:
        mov word ptr [edi+7FECh],ax
    L_00415554:
        mov ecx,dword ptr [edi+9EC0h]
    L_0041555a:
        cmp ecx,dword ptr [edi+9EC4h]
    L_00415560:
        je short L_004155a8
    L_00415562:
        mov eax,66666667h
    L_00415567:
        imul ecx
    L_00415569:
        mov ecx,dword ptr [edi+9EC8h]
    L_0041556f:
        sar edx,2
    L_00415572:
        mov eax,edx
    L_00415574:
        shr eax,1Fh
    L_00415577:
        lea edx,[edx+eax+8]
    L_0041557b:
        lea eax,[edi+793Ch]
    L_00415581:
        call asm_AnimationObject_ConfigureFromResource_0043e5a0
    L_00415586:
        mov eax,dword ptr [edi+9EC0h]
    L_0041558c:
        cdq
    L_0041558d:
        mov ecx,0Ah
    L_00415592:
        idiv ecx
    L_00415594:
        mov ecx,dword ptr [edi+9EC8h]
    L_0041559a:
        lea eax,[edi+7CE8h]
    L_004155a0:
        add edx,8
    L_004155a3:
        call asm_AnimationObject_ConfigureFromResource_0043e5a0
    L_004155a8:
        mov edx,dword ptr [edi+9EC0h]
    L_004155ae:
        mov ecx,dword ptr [g_enemy_ctrl]
    L_004155b4:
        mov dword ptr [edi+9EC4h],edx
    L_004155ba:
        mov esi,dword ptr [ecx+10h]
    L_004155bd:
        test esi,esi
    L_004155bf:
        je asm_target_00415764
    L_004155c5:
        mov eax,dword ptr [esi+2480h]
    L_004155cb:
        mov ecx,eax
    L_004155cd:
        shr ecx,4
    L_004155d0:
        not ecx
    L_004155d2:
        test cl,1
    L_004155d5:
        je asm_target_00415764
    L_004155db:
        not eax
    L_004155dd:
        test al,1
    L_004155df:
        je asm_target_00415764
    L_004155e5:
        mov edx,dword ptr [g_card]
    L_004155eb:
        test byte ptr [edx+378Ch],1
    L_004155f2:
        mov eax,dword ptr [edi+9EB4h]
    L_004155f8:
        mov ecx,eax
    L_004155fa:
        je short L_00415646
    L_004155fc:
        shr ecx,1
    L_004155fe:
        and ecx,3
    L_00415601:
        jne short L_0041560f
    L_00415603:
        cmp dword ptr [esi+2404h],7D0h
    L_0041560d:
        jmp short L_00415657
    L_0041560f:
        cmp ecx,1
    L_00415612:
        jne short L_00415620
    L_00415614:
        cmp dword ptr [esi+2404h],3E8h
    L_0041561e:
        jmp short L_00415679
    L_00415620:
        cmp ecx,2
    L_00415623:
        jne short L_00415631
    L_00415625:
        cmp dword ptr [esi+2404h],190h
    L_0041562f:
        jmp short L_0041569b
    L_00415631:
        cmp ecx,3
    L_00415634:
        jne asm_target_004156ce
    L_0041563a:
        cmp dword ptr [esi+2404h],190h
    L_00415644:
        jmp short L_004156ba
    L_00415646:
        shr ecx,1
    L_00415648:
        and ecx,3
    L_0041564b:
        jne short L_0041566a
    L_0041564d:
        cmp dword ptr [esi+2404h],2BCh
    L_00415657:
        jge short L_004156ce
    L_00415659:
        and eax,0FFFFFFFBh
    L_0041565c:
        mov word ptr [edi+9D4Ch],7
    L_00415665:
        or eax,2
    L_00415668:
        jmp short L_004156c8
    L_0041566a:
        cmp ecx,1
    L_0041566d:
        jne short L_0041568c
    L_0041566f:
        cmp dword ptr [esi+2404h],190h
    L_00415679:
        jge short L_004156ce
    L_0041567b:
        and eax,0FFFFFFFDh
    L_0041567e:
        mov word ptr [edi+9D4Ch],8
    L_00415687:
        or eax,4
    L_0041568a:
        jmp short L_004156c8
    L_0041568c:
        cmp ecx,2
    L_0041568f:
        jne short L_004156ab
    L_00415691:
        cmp dword ptr [esi+2404h],0C8h
    L_0041569b:
        jge short L_004156ce
    L_0041569d:
        mov word ptr [edi+9D4Ch],9
    L_004156a6:
        or eax,6
    L_004156a9:
        jmp short L_004156c8
    L_004156ab:
        cmp ecx,3
    L_004156ae:
        jne short L_004156ce
    L_004156b0:
        cmp dword ptr [esi+2404h],0C8h
    L_004156ba:
        jle short L_004156ce
    L_004156bc:
        mov word ptr [edi+9D4Ch],0Ah
    L_004156c5:
        and eax,0FFFFFFF9h
    L_004156c8:
        mov dword ptr [edi+9EB4h],eax
    L_004156ce:
        lea eax,[edi+9A48h]
    L_004156d4:
        push eax
    L_004156d5:
        call asm_FUN_0043ee30_0043ee30
    L_004156da:
        fld dword ptr [esi+1068h]
    L_004156e0:
        fadd dword ptr [flt_224]
    L_004156e6:
        mov ecx,dword ptr [g_player]
    L_004156ec:
        mov dword ptr [edi+9D8Ch],43F00000h
    L_004156f6:
        fstp dword ptr [edi+9D88h]
    L_004156fc:
        fld dword ptr [esi+1068h]
    L_00415702:
        fsub dword ptr [ecx+3C0h]
    L_00415708:
        fabs
    L_0041570a:
        fcom qword ptr [dbl_64]
    L_00415710:
        fnstsw ax
    L_00415712:
        test ah,1
    L_00415715:
        jne short L_00415722
    L_00415717:
        fstp st(0)
    L_00415719:
        mov byte ptr [edi+9D47h],0FFh
    L_00415720:
        jmp short L_00415737
    L_00415722:
        fmul dword ptr [flt_neg2_984375]
    L_00415728:
        call asm_FUN_00463b2c_00463b2c
    L_0041572d:
        mov dl,40h
    L_0041572f:
        sub dl,al
    L_00415731:
        mov byte ptr [edi+9D47h],dl
    L_00415737:
        fld dword ptr [esi+1068h]
    L_0041573d:
        fcomp dword ptr [flt_neg192]
    L_00415743:
        fnstsw ax
    L_00415745:
        test ah,5
    L_00415748:
        jnp short L_0041575d
    L_0041574a:
        fld dword ptr [esi+1068h]
    L_00415750:
        fcomp dword ptr [flt_192]
    L_00415756:
        fnstsw ax
    L_00415758:
        test ah,41h
    L_0041575b:
        jne short L_00415764
    L_0041575d:
        mov byte ptr [edi+9D47h],0
    L_00415764:
        mov edx,dword ptr [edi+9E64h]
    L_0041576a:
        mov ecx,dword ptr [edi+9E6Ch]
    L_00415770:
        mov dword ptr [edi+9E60h],edx
    L_00415776:
        fld dword ptr [ecx]
    L_00415778:
        fcomp dword ptr [flt_0_99]
    L_0041577e:
        pop esi
    L_0041577f:
        pop ebp
    L_00415780:
        pop ebx
    L_00415781:
        fnstsw ax
    L_00415783:
        test ah,41h
    L_00415786:
        jne short L_004157ba
    L_00415788:
        fld dword ptr [ecx]
    L_0041578a:
        fcomp dword ptr [flt_1_01]
    L_00415790:
        fnstsw ax
    L_00415792:
        test ah,5
    L_00415795:
        jp short L_004157ba
    L_00415797:
        fld dword ptr [edi+9E68h]
    L_0041579d:
        inc edx
    L_0041579e:
        fadd dword ptr [flt_1]
    L_004157a4:
        mov dword ptr [edi+9E64h],edx
    L_004157aa:
        mov eax,1
    L_004157af:
        fstp dword ptr [edi+9E68h]
    L_004157b5:
        pop edi
    L_004157b6:
        pop ecx
    L_004157b7:
        ret 4
    L_004157ba:
        fld dword ptr [ecx]
    L_004157bc:
        fadd dword ptr [edi+9E68h]
    L_004157c2:
        fst dword ptr [edi+9E68h]
    L_004157c8:
        call asm_FUN_00463b2c_00463b2c
    L_004157cd:
        mov dword ptr [edi+9E64h],eax
    L_004157d3:
        mov eax,1
    L_004157d8:
        pop edi
    L_004157d9:
        pop ecx
    L_004157da:
        ret 4
        _emit 0x8d
        _emit 0x49
        _emit 0x00
        _emit 0x14
        _emit 0x4e
        _emit 0x41
        _emit 0x00
        _emit 0x24
        _emit 0x4e
        _emit 0x41
        _emit 0x00
        _emit 0x38
        _emit 0x4e
        _emit 0x41
        _emit 0x00
        _emit 0x4c
        _emit 0x4e
        _emit 0x41
        _emit 0x00
        _emit 0x63
        _emit 0x4e
        _emit 0x41
        _emit 0x00
        _emit 0x6a
        _emit 0x4e
        _emit 0x41
        _emit 0x00
        _emit 0x71
        _emit 0x4e
        _emit 0x41
        _emit 0x00
    }
}
