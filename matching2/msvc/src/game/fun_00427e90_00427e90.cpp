#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x004050D0..0x00405101: ?EmbeddedTimer_Reset@@
// Naked body preserves the retail register/stack ABI.

// 0x00427E90..0x0042815C: FUN_00427e90
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00427e90_00427e90() {
    __asm {
    L_00427e90:
        sub esp,14h
    L_00427e93:
        push ebx
    L_00427e94:
        mov ebx,dword ptr [esp+1Ch]
    L_00427e98:
        push esi
    L_00427e99:
        mov esi,dword ptr [esp+24h]
    L_00427e9d:
        mov al,byte ptr [esi+1Dh]
    L_00427ea0:
        xor ecx,ecx
    L_00427ea2:
        cmp al,3
    L_00427ea4:
        push edi
    L_00427ea5:
        lea edi,[ebx+49Ch]
    L_00427eab:
        jne short L_00427ebe
    L_00427ead:
        movsx eax,byte ptr [esi+1Ch]
    L_00427eb1:
        cmp dword ptr [ebx+eax*4+42F4h],ecx
    L_00427eb8:
        jne asm_target_00428152
    L_00427ebe:
        xor eax,eax
    L_00427ec0:
        cmp dword ptr [edi+40h],ecx
    L_00427ec3:
        je short L_00427edb
    L_00427ec5:
        inc eax
    L_00427ec6:
        add edi,5Ch
    L_00427ec9:
        cmp eax,80h
    L_00427ece:
        jl short L_00427ec0
    L_00427ed0:
        pop edi
    L_00427ed1:
        pop esi
    L_00427ed2:
        xor eax,eax
    L_00427ed4:
        pop ebx
    L_00427ed5:
        add esp,14h
    L_00427ed8:
        ret 0Ch
    L_00427edb:
        mov eax,dword ptr [edi+10h]
    L_00427ede:
        test al,1
    L_00427ee0:
        mov dword ptr [edi+40h],1
    L_00427ee7:
        mov dword ptr [edi+58h],esi
    L_00427eea:
        jne short L_00427f05
    L_00427eec:
        or eax,1
    L_00427eef:
        mov dword ptr [edi+4],ecx
    L_00427ef2:
        mov dword ptr [edi],0FFF0BDC1h
    L_00427ef8:
        mov dword ptr [edi+8],ecx
    L_00427efb:
        mov dword ptr [edi+0Ch],476F78h
    L_00427f02:
        mov dword ptr [edi+10h],eax
    L_00427f05:
        mov dword ptr [edi+4],ecx
    L_00427f08:
        mov dword ptr [edi+8],ecx
    L_00427f0b:
        mov dword ptr [edi],0FFFFFFFFh
    L_00427f11:
        mov al,byte ptr [esi+1Ch]
    L_00427f14:
        test al,al
    L_00427f16:
        push ebp
    L_00427f17:
        jne short L_00427f3a
    L_00427f19:
        lea ebp,[edi+14h]
    L_00427f1c:
        lea ecx,[ebx+3C0h]
    L_00427f22:
        mov eax,dword ptr [ecx]
    L_00427f24:
        mov edx,ebp
    L_00427f26:
        mov dword ptr [edx],eax
    L_00427f28:
        mov eax,dword ptr [ecx+4]
    L_00427f2b:
        mov dword ptr [edx+4],eax
    L_00427f2e:
        mov ecx,dword ptr [ecx+8]
    L_00427f31:
        mov dword ptr [esp+10h],ebp
    L_00427f35:
        mov dword ptr [edx+8],ecx
    L_00427f38:
        jmp short L_00427f91
    L_00427f3a:
        movsx edx,al
    L_00427f3d:
        imul edx,98h
    L_00427f43:
        fild dword ptr [edx+ebx+3244h]
    L_00427f4a:
        fmul dword ptr [data_00470b00]
    L_00427f50:
        fstp dword ptr [esp+18h]
    L_00427f54:
        fild dword ptr [edx+ebx+3248h]
    L_00427f5b:
        mov ecx,dword ptr [esp+18h]
    L_00427f5f:
        lea eax,[edx+ebx+3244h]
    L_00427f66:
        lea eax,[edi+14h]
    L_00427f69:
        fmul dword ptr [data_00470b00]
    L_00427f6f:
        mov dword ptr [esp+10h],eax
    L_00427f73:
        mov dword ptr [eax],ecx
    L_00427f75:
        mov dword ptr [esp+20h],0
    L_00427f7d:
        mov ecx,dword ptr [esp+20h]
    L_00427f81:
        fstp dword ptr [esp+1Ch]
    L_00427f85:
        mov edx,dword ptr [esp+1Ch]
    L_00427f89:
        mov dword ptr [eax+4],edx
    L_00427f8c:
        mov dword ptr [eax+8],ecx
    L_00427f8f:
        mov ebp,eax
    L_00427f91:
        cmp byte ptr [esi+1Dh],3
    L_00427f95:
        jne short L_00427fa6
    L_00427f97:
        movsx edx,byte ptr [esi+1Ch]
    L_00427f9b:
        mov dword ptr [ebx+edx*4+42F4h],1
    L_00427fa6:
        mov eax,dword ptr [esi+18h]
    L_00427fa9:
        mov dword ptr [edi+2Ch],eax
    L_00427fac:
        mov ecx,dword ptr [esi+14h]
    L_00427faf:
        push ecx
    L_00427fb0:
        call asm_Angle_Normalize_0044bc70
    L_00427fb5:
        fstp dword ptr [edi+30h]
    L_00427fb8:
        test byte ptr [ebp+28h],1
    L_00427fbc:
        jne short L_00427fd7
    L_00427fbe:
        mov edx,dword ptr [ebp+18h]
    L_00427fc1:
        mov eax,dword ptr [ebp+1Ch]
    L_00427fc4:
        push edx
    L_00427fc5:
        push eax
    L_00427fc6:
        lea ecx,[ebp+0Ch]
    L_00427fc9:
        call asm_Recovery_PolarToVectorRetail_0044c5d0
    L_00427fce:
        mov dword ptr [ebp+14h],0
    L_00427fd5:
        jmp short L_00427ff2
    L_00427fd7:
        fld dword ptr [ebp+24h]
    L_00427fda:
        push ecx
    L_00427fdb:
        fadd dword ptr [ebp+20h]
    L_00427fde:
        fstp dword ptr [ebp+20h]
    L_00427fe1:
        fld dword ptr [ebp+18h]
    L_00427fe4:
        fadd dword ptr [ebp+1Ch]
    L_00427fe7:
        fstp dword ptr [esp]
    L_00427fea:
        call asm_Angle_Normalize_0044bc70
    L_00427fef:
        fstp dword ptr [ebp+1Ch]
    L_00427ff2:
        fld dword ptr [esi+4]
    L_00427ff5:
        fsub dword ptr [edi+20h]
    L_00427ff8:
        fadd dword ptr [ebp]
    L_00427ffb:
        fstp dword ptr [ebp]
    L_00427ffe:
        fld dword ptr [esi+8]
    L_00428001:
        fsub dword ptr [edi+24h]
    L_00428004:
        fadd dword ptr [edi+18h]
    L_00428007:
        fstp dword ptr [edi+18h]
    L_0042800a:
        movsx ebp,word ptr [esi+1Eh]
    L_0042800e:
        mov ecx,dword ptr [ebx+10h]
    L_00428011:
        mov esi,dword ptr [data_00491c10]
    L_00428017:
        add ebp,5
    L_0042801a:
        mov dword ptr [esp+14h],ecx
    L_0042801e:
        call asm_FUN_00449950_00449950
    L_00428023:
        mov ecx,dword ptr [esp+14h]
    L_00428027:
        mov ebx,eax
    L_00428029:
        mov eax,dword ptr [ebx+35Ch]
    L_0042802f:
        push ebp
    L_00428030:
        or eax,40000000h
    L_00428035:
        push ebx
    L_00428036:
        mov dword ptr [ebx+20h],0Fh
    L_0042803d:
        mov dword ptr [ebx+35Ch],eax
    L_00428043:
        call asm_FUN_00449870_00449870
    L_00428048:
        mov esi,dword ptr [data_00491c10]
    L_0042804e:
        lea eax,[esp+14h]
    L_00428052:
        mov edx,esi
    L_00428054:
        call asm_AnimationManager_RegisterPrimaryBack_004489d0
    L_00428059:
        mov edx,dword ptr [esp+14h]
    L_0042805d:
        mov eax,edx
    L_0042805f:
        mov dword ptr [edi+44h],edx
    L_00428062:
        xor edx,edx
    L_00428064:
        cmp eax,edx
    L_00428066:
        jne short L_0042806c
    L_00428068:
        xor ecx,ecx
    L_0042806a:
        jmp short L_004280a7
    L_0042806c:
        mov ecx,dword ptr [esi+72DAD4h]
    L_00428072:
        cmp ecx,edx
    L_00428074:
        je short L_00428083
    L_00428076:
        mov ebx,dword ptr [ecx]
    L_00428078:
        cmp dword ptr [ebx],eax
    L_0042807a:
        je short L_004280a1
    L_0042807c:
        mov ecx,dword ptr [ecx+4]
    L_0042807f:
        cmp ecx,edx
    L_00428081:
        jne short L_00428076
    L_00428083:
        mov ecx,dword ptr [esi+72DADCh]
    L_00428089:
        cmp ecx,edx
    L_0042808b:
        je short L_00428068
    L_0042808d:
        TH10_NOP_LEA_ECX_DISP8()
    L_00428090:
        mov ebx,dword ptr [ecx]
    L_00428092:
        cmp dword ptr [ebx],eax
    L_00428094:
        je short L_004280a1
    L_00428096:
        mov ecx,dword ptr [ecx+4]
    L_00428099:
        cmp ecx,edx
    L_0042809b:
        jne short L_00428090
    L_0042809d:
        xor ecx,ecx
    L_0042809f:
        jmp short L_004280a7
    L_004280a1:
        mov ecx,dword ptr [ecx]
    L_004280a3:
        cmp ecx,edx
    L_004280a5:
        jne short L_004280aa
    L_004280a7:
        mov dword ptr [edi+44h],edx
    L_004280aa:
        mov eax,dword ptr [ecx+35Ch]
    L_004280b0:
        test eax,8000000h
    L_004280b5:
        mov ebx,dword ptr [esp+2Ch]
    L_004280b9:
        je short L_004280ca
    L_004280bb:
        mov ebp,dword ptr [ebx+14h]
    L_004280be:
        or eax,4
    L_004280c1:
        mov dword ptr [ecx+2Ch],ebp
    L_004280c4:
        mov dword ptr [ecx+35Ch],eax
    L_004280ca:
        cmp byte ptr [ebx+1Dh],3
    L_004280ce:
        jne short L_0042811d
    L_004280d0:
        mov eax,dword ptr [esp+28h]
    L_004280d4:
        mov ebp,dword ptr [eax+10h]
    L_004280d7:
        call asm_FUN_00449950_00449950
    L_004280dc:
        mov ebx,eax
    L_004280de:
        mov edx,dword ptr [ebx+35Ch]
    L_004280e4:
        push 10h
    L_004280e6:
        or edx,40000000h
    L_004280ec:
        push ebx
    L_004280ed:
        mov ecx,ebp
    L_004280ef:
        mov dword ptr [ebx+20h],0Fh
    L_004280f6:
        mov dword ptr [ebx+35Ch],edx
    L_004280fc:
        call asm_FUN_00449870_00449870
    L_00428101:
        mov edx,dword ptr [data_00491c10]
    L_00428107:
        lea eax,[esp+14h]
    L_0042810b:
        call asm_AnimationManager_RegisterPrimaryBack_004489d0
    L_00428110:
        mov ecx,dword ptr [esp+14h]
    L_00428114:
        mov ebx,dword ptr [esp+2Ch]
    L_00428118:
        mov dword ptr [edi+48h],ecx
    L_0042811b:
        jmp short L_00428120
    L_0042811d:
        mov dword ptr [edi+48h],edx
    L_00428120:
        mov eax,dword ptr [ebx+24h]
    L_00428123:
        test eax,eax
    L_00428125:
        pop ebp
    L_00428126:
        je short L_00428135
    L_00428128:
        mov edx,dword ptr [esp+2Ch]
    L_0042812c:
        mov ecx,dword ptr [esp+24h]
    L_00428130:
        push edx
    L_00428131:
        mov edx,edi
    L_00428133:
        call eax
    L_00428135:
        mov ax,word ptr [ebx+22h]
    L_00428139:
        test ax,ax
    L_0042813c:
        jl short L_00428152
    L_0042813e:
        mov ecx,dword ptr [esp+0Ch]
    L_00428142:
        mov edx,dword ptr [ecx]
    L_00428144:
        movsx ebx,ax
    L_00428147:
        push edx
    L_00428148:
        mov esi,492590h
    L_0042814d:
        call asm_FUN_0043dd10_0043dd10
    L_00428152:
        pop edi
    L_00428153:
        pop esi
    L_00428154:
        xor eax,eax
    L_00428156:
        pop ebx
    L_00428157:
        add esp,14h
    L_0042815a:
        ret 0Ch
    }
}
