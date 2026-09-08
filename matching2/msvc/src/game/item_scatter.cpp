#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0040C9D0..0x0040CBC6: FUN_0040c9d0
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0040c9d0_0040c9d0() {
    __asm {
    L_0040c9d0:
        sub esp,18h
    L_0040c9d3:
        push ebx
    L_0040c9d4:
        push ebp
    L_0040c9d5:
        mov ebp,dword ptr [esp+24h]
    L_0040c9d9:
        push edi
    L_0040c9da:
        mov ecx,4918B0h
    L_0040c9df:
        call asm_Rng_NextFloatSigned_0044bb90
    L_0040c9e4:
        fmul dword ptr [data_00470b18]
    L_0040c9ea:
        lea edi,[ebp+4]
    L_0040c9ed:
        mov dword ptr [esp+0Ch],0
    L_0040c9f5:
        fstp dword ptr [esp+28h]
    L_0040c9f9:
        mov dword ptr [esp+10h],edi
    L_0040c9fd:
        TH10_NOP_LEA_ECX_DISP8()
    L_0040ca00:
        mov eax,dword ptr [edi]
    L_0040ca02:
        xor ebx,ebx
    L_0040ca04:
        test eax,eax
    L_0040ca06:
        jle asm_target_0040cb9c
    L_0040ca0c:
        TH10_NOP_LEA_ESP_DISP8()
    L_0040ca10:
        mov eax,dword ptr [ebp+38h]
    L_0040ca13:
        mov ecx,dword ptr [ebp+34h]
    L_0040ca16:
        mov edx,dword ptr [esp+28h]
    L_0040ca1a:
        push eax
    L_0040ca1b:
        push ecx
    L_0040ca1c:
        push edx
    L_0040ca1d:
        lea ecx,[esp+24h]
    L_0040ca21:
        call asm_Vector2_SetEllipticPolar_00413270
    L_0040ca26:
        mov eax,dword ptr [data_004918b0]
    L_0040ca2b:
        xor ecx,ecx
    L_0040ca2d:
        xor eax,9630h
    L_0040ca32:
        sub eax,6553h
    L_0040ca37:
        mov cx,ax
    L_0040ca3a:
        shr cx,0Eh
    L_0040ca3e:
        lea edx,[eax*4]
    L_0040ca45:
        add ecx,edx
    L_0040ca47:
        mov word ptr [data_004918b0],cx
    L_0040ca4e:
        mov eax,dword ptr [data_004918b0]
    L_0040ca53:
        mov edx,dword ptr [data_004918b4]
    L_0040ca59:
        xor eax,9630h
    L_0040ca5e:
        xor ecx,ecx
    L_0040ca60:
        sub eax,6553h
    L_0040ca65:
        mov cx,ax
    L_0040ca68:
        shr cx,0Eh
    L_0040ca6c:
        shl eax,2
    L_0040ca6f:
        inc edx
    L_0040ca70:
        add ecx,eax
    L_0040ca72:
        movzx eax,cx
    L_0040ca75:
        mov word ptr [data_004918b0],cx
    L_0040ca7c:
        mov ecx,eax
    L_0040ca7e:
        shl ecx,10h
    L_0040ca81:
        or ecx,eax
    L_0040ca83:
        inc edx
    L_0040ca84:
        test ecx,ecx
    L_0040ca86:
        mov dword ptr [esp+14h],ecx
    L_0040ca8a:
        mov dword ptr [data_004918b4],edx
    L_0040ca90:
        fild dword ptr [esp+14h]
    L_0040ca94:
        jge short L_0040ca9c
    L_0040ca96:
        fadd dword ptr [data_00470b98]
    L_0040ca9c:
        mov eax,dword ptr [esp+0Ch]
    L_0040caa0:
        mov edx,dword ptr [esi+8]
    L_0040caa3:
        fmul dword ptr [data_00470d18]
    L_0040caa9:
        push 400CCCCDh
    L_0040caae:
        push 0BFC90FDBh
    L_0040cab3:
        fadd dword ptr [data_00470b0c]
    L_0040cab9:
        inc eax
    L_0040caba:
        fld dword ptr [esp+20h]
    L_0040cabe:
        push 0FFFFFFFFh
    L_0040cac0:
        push eax
    L_0040cac1:
        mov eax,dword ptr [data_00477818]
    L_0040cac6:
        fmul st,st(1)
    L_0040cac8:
        fld dword ptr [esp+2Ch]
    L_0040cacc:
        lea ecx,[esp+28h]
    L_0040cad0:
        fmul st,st(2)
    L_0040cad2:
        mov dword ptr [esp+30h],edx
    L_0040cad6:
        fstp dword ptr [esp+2Ch]
    L_0040cada:
        fadd dword ptr [esi]
    L_0040cadc:
        fstp dword ptr [esp+28h]
    L_0040cae0:
        fstp st(0)
    L_0040cae2:
        fld dword ptr [esp+2Ch]
    L_0040cae6:
        fadd dword ptr [esi+4]
    L_0040cae9:
        fstp dword ptr [esp+2Ch]
    L_0040caed:
        call asm_FUN_0041bb00_0041bb00
    L_0040caf2:
        mov eax,dword ptr [data_004918b0]
    L_0040caf7:
        xor ecx,ecx
    L_0040caf9:
        xor eax,9630h
    L_0040cafe:
        sub eax,6553h
    L_0040cb03:
        mov cx,ax
    L_0040cb06:
        shr cx,0Eh
    L_0040cb0a:
        lea edx,[eax*4]
    L_0040cb11:
        add ecx,edx
    L_0040cb13:
        mov word ptr [data_004918b0],cx
    L_0040cb1a:
        mov eax,dword ptr [data_004918b0]
    L_0040cb1f:
        mov edx,dword ptr [data_004918b4]
    L_0040cb25:
        xor eax,9630h
    L_0040cb2a:
        xor ecx,ecx
    L_0040cb2c:
        sub eax,6553h
    L_0040cb31:
        mov cx,ax
    L_0040cb34:
        shr cx,0Eh
    L_0040cb38:
        shl eax,2
    L_0040cb3b:
        inc edx
    L_0040cb3c:
        add ecx,eax
    L_0040cb3e:
        movzx eax,cx
    L_0040cb41:
        mov word ptr [data_004918b0],cx
    L_0040cb48:
        mov ecx,eax
    L_0040cb4a:
        shl ecx,10h
    L_0040cb4d:
        or ecx,eax
    L_0040cb4f:
        inc edx
    L_0040cb50:
        test ecx,ecx
    L_0040cb52:
        mov dword ptr [esp+14h],ecx
    L_0040cb56:
        mov dword ptr [data_004918b4],edx
    L_0040cb5c:
        fild dword ptr [esp+14h]
    L_0040cb60:
        jge short L_0040cb68
    L_0040cb62:
        fadd dword ptr [data_00470b98]
    L_0040cb68:
        fmul dword ptr [data_00470bec]
    L_0040cb6e:
        push ecx
    L_0040cb6f:
        fsub dword ptr [data_00470afc]
    L_0040cb75:
        fmul dword ptr [data_00470c48]
    L_0040cb7b:
        fadd dword ptr [esp+2Ch]
    L_0040cb7f:
        fadd dword ptr [data_00470b94]
    L_0040cb85:
        fstp dword ptr [esp]
    L_0040cb88:
        call asm_Angle_Normalize_0044bc70
    L_0040cb8d:
        mov eax,dword ptr [edi]
    L_0040cb8f:
        fstp dword ptr [esp+28h]
    L_0040cb93:
        inc ebx
    L_0040cb94:
        cmp ebx,eax
    L_0040cb96:
        jl asm_target_0040ca10
    L_0040cb9c:
        mov eax,dword ptr [esp+0Ch]
    L_0040cba0:
        inc eax
    L_0040cba1:
        add edi,4
    L_0040cba4:
        cmp eax,0Bh
    L_0040cba7:
        mov dword ptr [esp+0Ch],eax
    L_0040cbab:
        jl asm_target_0040ca00
    L_0040cbb1:
        mov edi,dword ptr [esp+10h]
    L_0040cbb5:
        mov ecx,0Ch
    L_0040cbba:
        xor eax,eax
    L_0040cbbc:
        rep stosd
    L_0040cbbe:
        pop edi
    L_0040cbbf:
        pop ebp
    L_0040cbc0:
        pop ebx
    L_0040cbc1:
        add esp,18h
    L_0040cbc4:
        ret 4
    }
}
