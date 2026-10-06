#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0041DD80..0x0041E149: FUN_0041dd80
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0041dd80_0041dd80() {
    __asm {
    L_0041dd80:
        push ebp
    L_0041dd81:
        mov ebp,esp
    L_0041dd83:
        and esp,0FFFFFFF8h
    L_0041dd86:
        sub esp,334h
    L_0041dd8c:
        mov eax,dword ptr [data_00473660]
    L_0041dd91:
        push ebx
    L_0041dd92:
        mov ebx,ecx
    L_0041dd94:
        xor eax,ebp
    L_0041dd96:
        push esi
    L_0041dd97:
        mov dword ptr [esp+338h],eax
    L_0041dd9e:
        lea esi,[ebx+24h]
    L_0041dda1:
        mov eax,esi
    L_0041dda3:
        mov ecx,dword ptr [eax]
    L_0041dda5:
        mov dword ptr [esp+44h],ecx
    L_0041dda9:
        mov ecx,dword ptr [eax+4]
    L_0041ddac:
        mov eax,dword ptr [eax+8]
    L_0041ddaf:
        push edi
    L_0041ddb0:
        mov dword ptr [esp+4Ch],ecx
    L_0041ddb4:
        mov dword ptr [esp+50h],eax
    L_0041ddb8:
        xor eax,eax
    L_0041ddba:
        mov ecx,40h
    L_0041ddbf:
        lea edi,[esp+238h]
    L_0041ddc6:
        rep stosd
    L_0041ddc8:
        mov ecx,dword ptr [ebx+3Ch]
    L_0041ddcb:
        push 40C00000h
    L_0041ddd0:
        xor edx,edx
    L_0041ddd2:
        push ecx
    L_0041ddd3:
        lea ecx,[esp+28h]
    L_0041ddd7:
        mov dword ptr [esp+44h],ebx
    L_0041dddb:
        mov dword ptr [esp+34h],edx
    L_0041dddf:
        mov dword ptr [esp+4Ch],edx
    L_0041dde3:
        mov dword ptr [esp+48h],esi
    L_0041dde7:
        mov dword ptr [esp+18h],40C00000h
    L_0041ddef:
        mov dword ptr [esp+30h],eax
    L_0041ddf3:
        call asm_SetPolar_Vector2_0041f800
    L_0041ddf8:
        fld dword ptr [esp+20h]
    L_0041ddfc:
        fadd dword ptr [esi]
    L_0041ddfe:
        fstp dword ptr [esp+30h]
    L_0041de02:
        mov eax,dword ptr [esp+30h]
    L_0041de06:
        fld dword ptr [esp+24h]
    L_0041de0a:
        mov dword ptr [esp+14h],eax
    L_0041de0e:
        fadd dword ptr [esi+4]
    L_0041de11:
        fstp dword ptr [esp+34h]
    L_0041de15:
        mov ecx,dword ptr [esp+34h]
    L_0041de19:
        fld dword ptr [esp+28h]
    L_0041de1d:
        mov dword ptr [esp+18h],ecx
    L_0041de21:
        fadd dword ptr [esi+8]
    L_0041de24:
        fstp dword ptr [esp+38h]
    L_0041de28:
        mov eax,dword ptr [esp+38h]
    L_0041de2c:
        fld dword ptr [esp+20h]
    L_0041de30:
        mov dword ptr [esp+1Ch],eax
    L_0041de34:
        fadd st(0),st
    L_0041de36:
        mov dword ptr [esp+1Ch],edx
    L_0041de3a:
        fstp dword ptr [esp+20h]
    L_0041de3e:
        fld dword ptr [esp+24h]
    L_0041de42:
        fadd st(0),st
    L_0041de44:
        fstp dword ptr [esp+24h]
    L_0041de48:
        fld dword ptr [esp+28h]
    L_0041de4c:
        fadd st(0),st
    L_0041de4e:
        fstp dword ptr [esp+28h]
    L_0041de52:
        fld dword ptr [ebp+0Ch]
    L_0041de55:
        fmul dword ptr [ebp+0Ch]
    L_0041de58:
        fstp dword ptr [ebp+0Ch]
    L_0041de5b:
        fld dword ptr [data_00470cd8]
    L_0041de61:
        fcomp dword ptr [ebx+40h]
    L_0041de64:
        fnstsw ax
    L_0041de66:
        test ah,41h
    L_0041de69:
        jp asm_target_0041e23b
    L_0041de6f:
        nop
    L_0041de70:
        mov eax,dword ptr [ebp+8]
    L_0041de73:
        fld dword ptr [eax+4]
    L_0041de76:
        fsub dword ptr [esp+18h]
    L_0041de7a:
        fld dword ptr [eax]
    L_0041de7c:
        fsub dword ptr [esp+14h]
    L_0041de80:
        fld st(0)
    L_0041de82:
        fmul st,st(1)
    L_0041de84:
        fld st(2)
    L_0041de86:
        fmul st,st(3)
    L_0041de88:
        faddp st(1),st
    L_0041de8a:
        fcomp dword ptr [ebp+0Ch]
    L_0041de8d:
        fnstsw ax
    L_0041de8f:
        fstp st(0)
    L_0041de91:
        test ah,41h
    L_0041de94:
        fstp st(0)
    L_0041de96:
        je asm_target_0041dfb8
    L_0041de9c:
        mov ecx,dword ptr [esp+2Ch]
    L_0041dea0:
        mov eax,dword ptr [ebp+10h]
    L_0041dea3:
        inc ecx
    L_0041dea4:
        test eax,eax
    L_0041dea6:
        mov byte ptr [esp+edx+238h],1
    L_0041deae:
        mov dword ptr [esp+2Ch],ecx
    L_0041deb2:
        je short L_0041df2c
    L_0041deb4:
        fld dword ptr [esp+14h]
    L_0041deb8:
        fadd dword ptr [data_00470bcc]
    L_0041debe:
        fcomp dword ptr [data_00470b40]
    L_0041dec4:
        fnstsw ax
    L_0041dec6:
        test ah,41h
    L_0041dec9:
        jnp short L_0041df2c
    L_0041decb:
        fld dword ptr [esp+14h]
    L_0041decf:
        fsub dword ptr [data_00470bcc]
    L_0041ded5:
        fcomp dword ptr [data_00470b3c]
    L_0041dedb:
        fnstsw ax
    L_0041dedd:
        test ah,1
    L_0041dee0:
        je short L_0041df2c
    L_0041dee2:
        fld dword ptr [esp+18h]
    L_0041dee6:
        fadd dword ptr [data_00470bcc]
    L_0041deec:
        fcomp dword ptr [data_00470b04]
    L_0041def2:
        fnstsw ax
    L_0041def4:
        test ah,41h
    L_0041def7:
        jnp short L_0041df2c
    L_0041def9:
        fld dword ptr [esp+18h]
    L_0041defd:
        fsub dword ptr [data_00470bcc]
    L_0041df03:
        fcomp dword ptr [data_00470b38]
    L_0041df09:
        fnstsw ax
    L_0041df0b:
        test ah,1
    L_0041df0e:
        je short L_0041df2c
    L_0041df10:
        mov eax,dword ptr [data_00477818]
    L_0041df15:
        push 3F19999Ah
    L_0041df1a:
        push 0BFC90FDBh
    L_0041df1f:
        push 0FFFFFFFFh
    L_0041df21:
        push 8
    L_0041df23:
        lea ecx,[esp+24h]
    L_0041df27:
        call asm_FUN_0041bb00_0041bb00
    L_0041df2c:
        movsx ebx,word ptr [ebx+44Ah]
    L_0041df33:
        mov ecx,dword ptr [data_0047781c]
    L_0041df39:
        mov esi,dword ptr [data_00491c10]
    L_0041df3f:
        mov edi,dword ptr [ecx+458h]
    L_0041df45:
        lea ebx,[ebx+ebx+11h]
    L_0041df49:
        call asm_FUN_00449950_00449950
    L_0041df4e:
        mov edx,dword ptr [esp+1Ch]
    L_0041df52:
        fld dword ptr [esp+14h]
    L_0041df56:
        mov esi,eax
    L_0041df58:
        mov eax,dword ptr [esi+35Ch]
    L_0041df5e:
        fadd dword ptr [data_00470b4c]
    L_0041df64:
        or eax,40000000h
    L_0041df69:
        mov dword ptr [esi+35Ch],eax
    L_0041df6f:
        mov dword ptr [esi+20h],0
    L_0041df76:
        fstp dword ptr [esi+340h]
    L_0041df7c:
        mov eax,esi
    L_0041df7e:
        fld dword ptr [esp+18h]
    L_0041df82:
        mov ecx,edi
    L_0041df84:
        fadd dword ptr [data_00470b48]
    L_0041df8a:
        mov dword ptr [esi+348h],edx
    L_0041df90:
        fstp dword ptr [esi+344h]
    L_0041df96:
        call asm_AnimationObject_LoadScript_0043e710
    L_0041df9b:
        mov edx,dword ptr [data_00491c10]
    L_0041dfa1:
        mov ebx,esi
    L_0041dfa3:
        lea eax,[esp+54h]
    L_0041dfa7:
        call asm_AnimationManager_RegisterPrimaryBack_004489d0
    L_0041dfac:
        mov esi,dword ptr [esp+40h]
    L_0041dfb0:
        mov edx,dword ptr [esp+44h]
    L_0041dfb4:
        mov ebx,dword ptr [esp+3Ch]
    L_0041dfb8:
        fld dword ptr [esp+14h]
    L_0041dfbc:
        inc edx
    L_0041dfbd:
        fadd dword ptr [esp+20h]
    L_0041dfc1:
        mov dword ptr [esp+44h],edx
    L_0041dfc5:
        fstp dword ptr [esp+14h]
    L_0041dfc9:
        fld dword ptr [esp+18h]
    L_0041dfcd:
        fadd dword ptr [esp+24h]
    L_0041dfd1:
        fstp dword ptr [esp+18h]
    L_0041dfd5:
        fld dword ptr [esp+1Ch]
    L_0041dfd9:
        fadd dword ptr [esp+28h]
    L_0041dfdd:
        fstp dword ptr [esp+1Ch]
    L_0041dfe1:
        fld dword ptr [esp+10h]
    L_0041dfe5:
        fadd dword ptr [data_00470cd8]
    L_0041dfeb:
        fstp dword ptr [esp+10h]
    L_0041dfef:
        fld dword ptr [esp+10h]
    L_0041dff3:
        fadd dword ptr [data_00470d1c]
    L_0041dff9:
        fcomp dword ptr [ebx+40h]
    L_0041dffc:
        fnstsw ax
    L_0041dffe:
        test ah,41h
    L_0041e001:
        jnp asm_target_0041de70
    L_0041e007:
        mov eax,dword ptr [esp+2Ch]
    L_0041e00b:
        test eax,eax
    L_0041e00d:
        je asm_target_0041e23b
    L_0041e013:
        cmp eax,edx
    L_0041e015:
        jl short L_0041e032
    L_0041e017:
        mov byte ptr [ebx+50h],1
    L_0041e01b:
        pop edi
    L_0041e01c:
        pop esi
    L_0041e01d:
        pop ebx
    L_0041e01e:
        mov ecx,dword ptr [esp+330h]
    L_0041e025:
        xor ecx,ebp
    L_0041e027:
        call asm_security_check_cookie_00458ea5
    L_0041e02c:
        mov esp,ebp
    L_0041e02e:
        pop ebp
    L_0041e02f:
        ret 0Ch
    L_0041e032:
        xor ebx,ebx
    L_0041e034:
        test edx,edx
    L_0041e036:
        mov dword ptr [esp+10h],ebx
    L_0041e03a:
        jle asm_target_0041e0c7
    L_0041e040:
        mov al,byte ptr [esp+ebx+238h]
    L_0041e047:
        test al,al
    L_0041e049:
        je short L_0041e050
    L_0041e04b:
        inc ebx
    L_0041e04c:
        cmp ebx,edx
    L_0041e04e:
        jl short L_0041e040
    L_0041e050:
        test ebx,ebx
    L_0041e052:
        mov dword ptr [esp+10h],ebx
    L_0041e056:
        je short L_0041e0c7
    L_0041e058:
        fild dword ptr [esp+10h]
    L_0041e05c:
        mov ecx,dword ptr [esp+3Ch]
    L_0041e060:
        fld st(0)
    L_0041e062:
        fld dword ptr [esp+20h]
    L_0041e066:
        fmul st,st(1)
    L_0041e068:
        fld dword ptr [esp+24h]
    L_0041e06c:
        fmul st,st(2)
    L_0041e06e:
        fstp dword ptr [esp+34h]
    L_0041e072:
        fxch
    L_0041e074:
        fmul dword ptr [esp+28h]
    L_0041e078:
        fstp dword ptr [esp+38h]
    L_0041e07c:
        fadd dword ptr [esi]
    L_0041e07e:
        fstp dword ptr [esi]
    L_0041e080:
        fld dword ptr [esp+34h]
    L_0041e084:
        fadd dword ptr [esi+4]
    L_0041e087:
        fstp dword ptr [esi+4]
    L_0041e08a:
        fld dword ptr [esp+38h]
    L_0041e08e:
        fadd dword ptr [esi+8]
    L_0041e091:
        fstp dword ptr [esi+8]
    L_0041e094:
        fmul dword ptr [data_00470cd8]
    L_0041e09a:
        fld dword ptr [ecx+40h]
    L_0041e09d:
        fsub st,st(1)
    L_0041e09f:
        fcom dword ptr [data_00470c0c]
    L_0041e0a5:
        fst dword ptr [ecx+40h]
    L_0041e0a8:
        fnstsw ax
    L_0041e0aa:
        test ah,41h
    L_0041e0ad:
        jne short L_0041e0ba
    L_0041e0af:
        fstp dword ptr [ecx+434h]
    L_0041e0b5:
        fstp dword ptr [ecx+4Ch]
    L_0041e0b8:
        jmp short L_0041e0cb
    L_0041e0ba:
        fstp st(0)
    L_0041e0bc:
        mov byte ptr [ecx+50h],1
    L_0041e0c0:
        fstp st(0)
    L_0041e0c2:
        jmp asm_target_0041e23b
    L_0041e0c7:
        mov ecx,dword ptr [esp+3Ch]
    L_0041e0cb:
        xor eax,eax
    L_0041e0cd:
        cmp ebx,edx
    L_0041e0cf:
        mov dword ptr [esp+10h],eax
    L_0041e0d3:
        jge asm_target_0041e23b
    L_0041e0d9:
        lea esp,[esp+force_disp32_zero]
    L_0041e0e0:
        cmp byte ptr [esp+ebx+238h],0
    L_0041e0e8:
        jne short L_0041e0f9
    L_0041e0ea:
        inc ebx
    L_0041e0eb:
        inc eax
    L_0041e0ec:
        cmp ebx,edx
    L_0041e0ee:
        jl short L_0041e0e0
    L_0041e0f0:
        mov dword ptr [esp+10h],eax
    L_0041e0f4:
        jmp asm_target_0041e23b
    L_0041e0f9:
        cmp ebx,edx
    L_0041e0fb:
        mov dword ptr [esp+10h],eax
    L_0041e0ff:
        jge asm_target_0041e23b
    L_0041e105:
        fild dword ptr [esp+10h]
    L_0041e109:
        fmul dword ptr [data_00470cd8]
    L_0041e10f:
        fld dword ptr [ecx+40h]
    L_0041e112:
        fsub st,st(1)
    L_0041e114:
        fsubr dword ptr [ecx+434h]
    L_0041e11a:
        fstp dword ptr [ecx+434h]
    L_0041e120:
        fst dword ptr [ecx+40h]
    L_0041e123:
        fcomp dword ptr [data_00470c0c]
    L_0041e129:
        fnstsw ax
    L_0041e12b:
        test ah,5
    L_0041e12e:
        jp short L_0041e140
    L_0041e130:
        mov byte ptr [ecx+50h],1
    L_0041e134:
        jmp short L_0041e140
    L_0041e136:
        mov ecx,dword ptr [esp+3Ch]
    L_0041e13a:
        lea ebx,[ebx+force_disp32_zero]
    L_0041e140:
        cmp ebx,edx
    L_0041e142:
        jge asm_target_0041e23b
    L_0041e148:
        TH10_REL8(0xeb, 0x0041e148, VA_asm_FUN_0041dd80_part_0041e150)
        _emit 0x8d
        _emit 0x9b
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x00

    L_0041e150:
        mov al,byte ptr [esp+ebx+238h]
    L_0041e157:
        test al,al
    L_0041e159:
        je short L_0041e165
    L_0041e15b:
        inc ebx
    L_0041e15c:
        cmp ebx,edx
    L_0041e15e:
        jl short L_0041e150
    L_0041e160:
        jmp asm_target_0041e23b
    L_0041e165:
        cmp ebx,edx
    L_0041e167:
        jge asm_target_0041e23b
    L_0041e16d:
        xor eax,eax
    L_0041e16f:
        mov dword ptr [esp+10h],eax
    L_0041e173:
        mov dword ptr [esp+40h],ebx
    L_0041e177:
        TH10_REL8(0xeb, 0x0041e177, VA_asm_FUN_0041dd80_part_0041e180)
        _emit 0x8d
        _emit 0xa4
        _emit 0x24
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x00

    L_0041e180:
        cmp byte ptr [esp+ebx+238h],0
    L_0041e188:
        jne short L_0041e190
    L_0041e18a:
        inc ebx
    L_0041e18b:
        inc eax
    L_0041e18c:
        cmp ebx,edx
    L_0041e18e:
        jl short L_0041e180
    L_0041e190:
        mov dword ptr [esp+10h],eax
    L_0041e194:
        fild dword ptr [esp+10h]
    L_0041e198:
        lea esi,[ecx+424h]
    L_0041e19e:
        mov ecx,77h
    L_0041e1a3:
        lea edi,[esp+58h]
    L_0041e1a7:
        fmul dword ptr [data_00470cd8]
    L_0041e1ad:
        rep movsd
    L_0041e1af:
        fst dword ptr [esp+6Ch]
    L_0041e1b3:
        fst dword ptr [esp+68h]
    L_0041e1b7:
        fcomp dword ptr [data_00470c0c]
    L_0041e1bd:
        fnstsw ax
    L_0041e1bf:
        test ah,41h
    L_0041e1c2:
        jne short L_0041e233
    L_0041e1c4:
        fild dword ptr [esp+40h]
    L_0041e1c8:
        mov esi,dword ptr [data_0047781c]
    L_0041e1ce:
        fld dword ptr [esp+20h]
    L_0041e1d2:
        push 0
    L_0041e1d4:
        lea edi,[esp+5Ch]
    L_0041e1d8:
        fmul st,st(1)
    L_0041e1da:
        fld st(1)
    L_0041e1dc:
        fmul dword ptr [esp+28h]
    L_0041e1e0:
        fstp dword ptr [esp+1Ch]
    L_0041e1e4:
        fxch
    L_0041e1e6:
        fmul dword ptr [esp+2Ch]
    L_0041e1ea:
        fstp dword ptr [esp+20h]
    L_0041e1ee:
        fld dword ptr [esp+4Ch]
    L_0041e1f2:
        fadd st,st(1)
    L_0041e1f4:
        fstp dword ptr [esp+34h]
    L_0041e1f8:
        mov eax,dword ptr [esp+34h]
    L_0041e1fc:
        mov dword ptr [esp+5Ch],eax
    L_0041e200:
        fstp st(0)
    L_0041e202:
        fld dword ptr [esp+50h]
    L_0041e206:
        fadd dword ptr [esp+1Ch]
    L_0041e20a:
        fstp dword ptr [esp+38h]
    L_0041e20e:
        mov ecx,dword ptr [esp+38h]
    L_0041e212:
        fld dword ptr [esp+54h]
    L_0041e216:
        mov dword ptr [esp+60h],ecx
    L_0041e21a:
        fadd dword ptr [esp+20h]
    L_0041e21e:
        fstp dword ptr [esp+3Ch]
    L_0041e222:
        mov edx,dword ptr [esp+3Ch]
    L_0041e226:
        mov dword ptr [esp+64h],edx
    L_0041e22a:
        call asm_FUN_0041c510_0041c510
    L_0041e22f:
        mov edx,dword ptr [esp+44h]
    L_0041e233:
        cmp ebx,edx
    L_0041e235:
        jl asm_target_0041e136
    L_0041e23b:
        mov ecx,dword ptr [esp+33Ch]
    L_0041e242:
        mov eax,dword ptr [esp+2Ch]
    L_0041e246:
        pop edi
    L_0041e247:
        pop esi
    L_0041e248:
        xor ecx,ebp
    L_0041e24a:
        pop ebx
    L_0041e24b:
        call asm_security_check_cookie_00458ea5
    L_0041e250:
        mov esp,ebp
    L_0041e252:
        pop ebp
    L_0041e253:
        ret 0Ch
    }
}

// 0x0041EB00..0x0041EE49: FUN_0041eb00
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0041eb00_0041eb00() {
    __asm {
    L_0041eb00:
        push ebp
    L_0041eb01:
        mov ebp,esp
    L_0041eb03:
        and esp,0FFFFFFF8h
    L_0041eb06:
        sub esp,344h
    L_0041eb0c:
        mov eax,dword ptr [data_00473660]
    L_0041eb11:
        xor eax,ebp
    L_0041eb13:
        push ebx
    L_0041eb14:
        mov ebx,ecx
    L_0041eb16:
        mov dword ptr [esp+344h],eax
    L_0041eb1d:
        mov eax,dword ptr [ebp+0Ch]
    L_0041eb20:
        mov dword ptr [esp+24h],eax
    L_0041eb24:
        mov dword ptr [esp+14h],ebx
    L_0041eb28:
        mov edx,dword ptr [ebp+8]
    L_0041eb2b:
        add ebx,24h
    L_0041eb2e:
        mov ecx,ebx
    L_0041eb30:
        mov eax,dword ptr [ecx]
    L_0041eb32:
        mov dword ptr [esp+54h],eax
    L_0041eb36:
        mov eax,dword ptr [ecx+4]
    L_0041eb39:
        mov ecx,dword ptr [ecx+8]
    L_0041eb3c:
        mov dword ptr [esp+5Ch],ecx
    L_0041eb40:
        push esi
    L_0041eb41:
        mov dword ptr [esp+5Ch],eax
    L_0041eb45:
        push edi
    L_0041eb46:
        xor eax,eax
    L_0041eb48:
        mov ecx,40h
    L_0041eb4d:
        lea edi,[esp+248h]
    L_0041eb54:
        rep stosd
    L_0041eb56:
        mov eax,dword ptr [esp+2Ch]
    L_0041eb5a:
        mov edi,dword ptr [esp+1Ch]
    L_0041eb5e:
        xor esi,esi
    L_0041eb60:
        fld dword ptr [eax]
    L_0041eb62:
        push 40C00000h
    L_0041eb67:
        fmul dword ptr [data_00470b0c]
    L_0041eb6d:
        mov dword ptr [esp+34h],esi
    L_0041eb71:
        mov dword ptr [esp+10h],40C00000h
    L_0041eb79:
        fstp dword ptr [esp+14h]
    L_0041eb7d:
        fld dword ptr [eax+4]
    L_0041eb80:
        fmul dword ptr [data_00470b0c]
    L_0041eb86:
        fstp dword ptr [esp+18h]
    L_0041eb8a:
        mov ecx,dword ptr [esp+18h]
    L_0041eb8e:
        fld dword ptr [eax+8]
    L_0041eb91:
        mov eax,dword ptr [esp+14h]
    L_0041eb95:
        fmul dword ptr [data_00470b0c]
    L_0041eb9b:
        mov dword ptr [esp+38h],eax
    L_0041eb9f:
        mov dword ptr [esp+3Ch],ecx
    L_0041eba3:
        fstp dword ptr [esp+1Ch]
    L_0041eba7:
        mov eax,dword ptr [esp+1Ch]
    L_0041ebab:
        fld dword ptr [edx]
    L_0041ebad:
        mov dword ptr [esp+40h],eax
    L_0041ebb1:
        fsub dword ptr [esp+38h]
    L_0041ebb5:
        fstp dword ptr [esp+14h]
    L_0041ebb9:
        mov ecx,dword ptr [esp+14h]
    L_0041ebbd:
        fld dword ptr [edx+4]
    L_0041ebc0:
        mov dword ptr [esp+50h],ecx
    L_0041ebc4:
        fsub dword ptr [esp+3Ch]
    L_0041ebc8:
        fstp dword ptr [esp+18h]
    L_0041ebcc:
        mov eax,dword ptr [esp+18h]
    L_0041ebd0:
        fld dword ptr [edx+8]
    L_0041ebd3:
        mov dword ptr [esp+54h],eax
    L_0041ebd7:
        fsub dword ptr [esp+40h]
    L_0041ebdb:
        fstp dword ptr [esp+1Ch]
    L_0041ebdf:
        mov ecx,dword ptr [esp+1Ch]
    L_0041ebe3:
        fld dword ptr [esp+38h]
    L_0041ebe7:
        mov dword ptr [esp+58h],ecx
    L_0041ebeb:
        fadd dword ptr [edx]
    L_0041ebed:
        fstp dword ptr [esp+14h]
    L_0041ebf1:
        fld dword ptr [esp+3Ch]
    L_0041ebf5:
        fadd dword ptr [edx+4]
    L_0041ebf8:
        fstp dword ptr [esp+18h]
    L_0041ebfc:
        mov eax,dword ptr [esp+18h]
    L_0041ec00:
        fld dword ptr [esp+40h]
    L_0041ec04:
        mov dword ptr [esp+3Ch],eax
    L_0041ec08:
        fadd dword ptr [edx+8]
    L_0041ec0b:
        mov edx,dword ptr [esp+14h]
    L_0041ec0f:
        mov dword ptr [esp+38h],edx
    L_0041ec13:
        mov edx,dword ptr [edi+3Ch]
    L_0041ec16:
        fstp dword ptr [esp+1Ch]
    L_0041ec1a:
        mov ecx,dword ptr [esp+1Ch]
    L_0041ec1e:
        mov dword ptr [esp+40h],ecx
    L_0041ec22:
        push edx
    L_0041ec23:
        lea ecx,[esp+18h]
    L_0041ec27:
        mov dword ptr [esp+20h],esi
    L_0041ec2b:
        call asm_SetPolar_Vector2_0041f800
    L_0041ec30:
        fld dword ptr [esp+10h]
    L_0041ec34:
        fadd dword ptr [ebx]
    L_0041ec36:
        fstp dword ptr [esp+40h]
    L_0041ec3a:
        mov eax,dword ptr [esp+40h]
    L_0041ec3e:
        fld dword ptr [esp+14h]
    L_0041ec42:
        mov dword ptr [esp+20h],eax
    L_0041ec46:
        fadd dword ptr [ebx+4]
    L_0041ec49:
        fstp dword ptr [esp+44h]
    L_0041ec4d:
        mov ecx,dword ptr [esp+44h]
    L_0041ec51:
        fld dword ptr [esp+18h]
    L_0041ec55:
        mov dword ptr [esp+24h],ecx
    L_0041ec59:
        fadd dword ptr [ebx+8]
    L_0041ec5c:
        fstp dword ptr [esp+48h]
    L_0041ec60:
        mov edx,dword ptr [esp+48h]
    L_0041ec64:
        fld dword ptr [esp+10h]
    L_0041ec68:
        mov dword ptr [esp+28h],edx
    L_0041ec6c:
        fadd st(0),st
    L_0041ec6e:
        mov dword ptr [esp+28h],esi
    L_0041ec72:
        fstp dword ptr [esp+10h]
    L_0041ec76:
        fld dword ptr [esp+14h]
    L_0041ec7a:
        fadd st(0),st
    L_0041ec7c:
        fstp dword ptr [esp+14h]
    L_0041ec80:
        fld dword ptr [esp+18h]
    L_0041ec84:
        fadd st(0),st
    L_0041ec86:
        fstp dword ptr [esp+18h]
    L_0041ec8a:
        fld dword ptr [data_00470cd8]
    L_0041ec90:
        fcomp dword ptr [edi+40h]
    L_0041ec93:
        fnstsw ax
    L_0041ec95:
        test ah,5
    L_0041ec98:
        jp asm_target_0041ef78
    L_0041ec9e:
        mov ebx,dword ptr [ebp+10h]
    L_0041eca1:
        fld dword ptr [esp+20h]
    L_0041eca5:
        fcomp dword ptr [esp+4Ch]
    L_0041eca9:
        fnstsw ax
    L_0041ecab:
        test ah,5
    L_0041ecae:
        jnp asm_target_0041ed57
    L_0041ecb4:
        fld dword ptr [esp+20h]
    L_0041ecb8:
        fcomp dword ptr [esp+34h]
    L_0041ecbc:
        fnstsw ax
    L_0041ecbe:
        test ah,41h
    L_0041ecc1:
        je asm_target_0041ed57
    L_0041ecc7:
        fld dword ptr [esp+24h]
    L_0041eccb:
        fcomp dword ptr [esp+50h]
    L_0041eccf:
        fnstsw ax
    L_0041ecd1:
        test ah,5
    L_0041ecd4:
        jnp asm_target_0041ed57
    L_0041ecda:
        fld dword ptr [esp+24h]
    L_0041ecde:
        fcomp dword ptr [esp+38h]
    L_0041ece2:
        fnstsw ax
    L_0041ece4:
        test ah,41h
    L_0041ece7:
        je short L_0041ed57
    L_0041ece9:
        mov ecx,dword ptr [esp+30h]
    L_0041eced:
        inc ecx
    L_0041ecee:
        test ebx,ebx
    L_0041ecf0:
        mov byte ptr [esp+esi+248h],1
    L_0041ecf8:
        mov dword ptr [esp+30h],ecx
    L_0041ecfc:
        je short L_0041ed2d
    L_0041ecfe:
        push 42000000h
    L_0041ed03:
        push 42000000h
    L_0041ed08:
        lea ecx,[esp+28h]
    L_0041ed0c:
        call asm_Position_IsPartiallyInViewport_0041f7a0
    L_0041ed11:
        test eax,eax
    L_0041ed13:
        jne short L_0041ed2d
    L_0041ed15:
        mov eax,dword ptr [data_00477818]
    L_0041ed1a:
        push 3F19999Ah
    L_0041ed1f:
        push 0BFC90FDBh
    L_0041ed24:
        push 0FFFFFFFFh
    L_0041ed26:
        push 8
    L_0041ed28:
        call asm_FUN_0041bb00_0041bb00
    L_0041ed2d:
        movsx eax,word ptr [edi+466h]
    L_0041ed34:
        lea ecx,[eax+eax+11h]
    L_0041ed38:
        mov eax,dword ptr [data_0047781c]
    L_0041ed3d:
        push ecx
    L_0041ed3e:
        mov ecx,dword ptr [eax+458h]
    L_0041ed44:
        lea edx,[esp+5Ch]
    L_0041ed48:
        push edx
    L_0041ed49:
        push ecx
    L_0041ed4a:
        lea edi,[esp+2Ch]
    L_0041ed4e:
        call asm_PlayerAnimation_Create_00448db0
    L_0041ed53:
        mov edi,dword ptr [esp+1Ch]
    L_0041ed57:
        fld dword ptr [esp+10h]
    L_0041ed5b:
        inc esi
    L_0041ed5c:
        fadd dword ptr [esp+20h]
    L_0041ed60:
        fstp dword ptr [esp+20h]
    L_0041ed64:
        fld dword ptr [esp+14h]
    L_0041ed68:
        fadd dword ptr [esp+24h]
    L_0041ed6c:
        fstp dword ptr [esp+24h]
    L_0041ed70:
        fld dword ptr [esp+28h]
    L_0041ed74:
        fadd dword ptr [esp+18h]
    L_0041ed78:
        fstp dword ptr [esp+28h]
    L_0041ed7c:
        fld dword ptr [esp+0Ch]
    L_0041ed80:
        fadd dword ptr [data_00470cd8]
    L_0041ed86:
        fstp dword ptr [esp+0Ch]
    L_0041ed8a:
        fld dword ptr [esp+0Ch]
    L_0041ed8e:
        fadd dword ptr [data_00470d1c]
    L_0041ed94:
        fcomp dword ptr [edi+40h]
    L_0041ed97:
        fnstsw ax
    L_0041ed99:
        test ah,5
    L_0041ed9c:
        jnp asm_target_0041eca1
    L_0041eda2:
        mov eax,dword ptr [esp+30h]
    L_0041eda6:
        test eax,eax
    L_0041eda8:
        mov dword ptr [esp+2Ch],esi
    L_0041edac:
        je asm_target_0041ef78
    L_0041edb2:
        xor eax,eax
    L_0041edb4:
        xor ebx,ebx
    L_0041edb6:
        cmp esi,eax
    L_0041edb8:
        jle short L_0041eddd
    L_0041edba:
        lea ebx,[ebx+force_disp32_zero]
    L_0041edc0:
        mov cl,byte ptr [esp+ebx+248h]
    L_0041edc7:
        test cl,cl
    L_0041edc9:
        je short L_0041edd0
    L_0041edcb:
        inc ebx
    L_0041edcc:
        cmp ebx,esi
    L_0041edce:
        jl short L_0041edc0
    L_0041edd0:
        cmp ebx,eax
    L_0041edd2:
        je short L_0041eddd
    L_0041edd4:
        mov edx,dword ptr [esp+1Ch]
    L_0041edd8:
        mov dword ptr [edx+40h],eax
    L_0041eddb:
        jmp short L_0041ee27
    L_0041eddd:
        cmp esi,eax
    L_0041eddf:
        mov dword ptr [esp+0Ch],eax
    L_0041ede3:
        jle asm_target_0041ef78
    L_0041ede9:
        lea esp,[esp+force_disp32_zero]
    L_0041edf0:
        mov cl,byte ptr [esp+ebx+248h]
    L_0041edf7:
        test cl,cl
    L_0041edf9:
        jne short L_0041ee0a
    L_0041edfb:
        inc ebx
    L_0041edfc:
        inc eax
    L_0041edfd:
        cmp ebx,esi
    L_0041edff:
        jl short L_0041edf0
    L_0041ee01:
        mov dword ptr [esp+0Ch],eax
    L_0041ee05:
        jmp asm_target_0041ef78
    L_0041ee0a:
        cmp ebx,esi
    L_0041ee0c:
        mov dword ptr [esp+0Ch],eax
    L_0041ee10:
        jge asm_target_0041ef78
    L_0041ee16:
        fild dword ptr [esp+0Ch]
    L_0041ee1a:
        mov edx,dword ptr [esp+1Ch]
    L_0041ee1e:
        fmul dword ptr [data_00470cd8]
    L_0041ee24:
        fstp dword ptr [edx+40h]
    L_0041ee27:
        cmp ebx,esi
    L_0041ee29:
        jge asm_target_0041ef78
    L_0041ee2f:
        jmp short L_0041ee40
    L_0041ee31:
        mov esi,dword ptr [esp+2Ch]
    L_0041ee35:
        mov edx,dword ptr [esp+1Ch]
    L_0041ee39:
        lea esp,[esp+force_disp32_zero]
    L_0041ee40:
        cmp ebx,esi
    L_0041ee42:
        jge asm_target_0041ef78
    L_0041ee48:
        TH10_REL8(0xeb, 0x0041ee48, VA_asm_FUN_0041eb00_part_0041ee50)
        _emit 0x8d
        _emit 0x9b
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x00

    L_0041ee50:
        mov al,byte ptr [esp+ebx+248h]
    L_0041ee57:
        test al,al
    L_0041ee59:
        je short L_0041ee65
    L_0041ee5b:
        inc ebx
    L_0041ee5c:
        cmp ebx,esi
    L_0041ee5e:
        jl short L_0041ee50
    L_0041ee60:
        jmp asm_target_0041ef78
    L_0041ee65:
        cmp ebx,esi
    L_0041ee67:
        jge asm_target_0041ef78
    L_0041ee6d:
        xor eax,eax
    L_0041ee6f:
        mov dword ptr [esp+0Ch],eax
    L_0041ee73:
        mov dword ptr [esp+58h],ebx
    L_0041ee77:
        TH10_REL8(0xeb, 0x0041ee77, VA_asm_FUN_0041eb00_part_0041ee80)
        _emit 0x8d
        _emit 0xa4
        _emit 0x24
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x00

    L_0041ee80:
        mov cl,byte ptr [esp+ebx+248h]
    L_0041ee87:
        test cl,cl
    L_0041ee89:
        jne short L_0041ee91
    L_0041ee8b:
        inc ebx
    L_0041ee8c:
        inc eax
    L_0041ee8d:
        cmp ebx,esi
    L_0041ee8f:
        jl short L_0041ee80
    L_0041ee91:
        mov dword ptr [esp+0Ch],eax
    L_0041ee95:
        fild dword ptr [esp+0Ch]
    L_0041ee99:
        xor eax,eax
    L_0041ee9b:
        mov ecx,77h
    L_0041eea0:
        lea edi,[esp+68h]
    L_0041eea4:
        fmul dword ptr [data_00470cd8]
    L_0041eeaa:
        rep stosd
    L_0041eeac:
        fst dword ptr [esp+7Ch]
    L_0041eeb0:
        fstp dword ptr [esp+78h]
    L_0041eeb4:
        mov esi,dword ptr [data_0047781c]
    L_0041eeba:
        fild dword ptr [esp+58h]
    L_0041eebe:
        push 0
    L_0041eec0:
        lea edi,[esp+6Ch]
    L_0041eec4:
        mov dword ptr [esp+8Ch],41000000h
    L_0041eecf:
        fld st(0)
    L_0041eed1:
        fld dword ptr [esp+14h]
    L_0041eed5:
        fmul st,st(1)
    L_0041eed7:
        fld dword ptr [esp+18h]
    L_0041eedb:
        fmul st,st(2)
    L_0041eedd:
        fstp dword ptr [esp+54h]
    L_0041eee1:
        fxch
    L_0041eee3:
        fmul dword ptr [esp+1Ch]
    L_0041eee7:
        fstp dword ptr [esp+58h]
    L_0041eeeb:
        fld dword ptr [esp+60h]
    L_0041eeef:
        fadd st,st(1)
    L_0041eef1:
        fstp dword ptr [esp+44h]
    L_0041eef5:
        mov eax,dword ptr [esp+44h]
    L_0041eef9:
        mov dword ptr [esp+6Ch],eax
    L_0041eefd:
        fstp st(0)
    L_0041eeff:
        fld dword ptr [esp+64h]
    L_0041ef03:
        fadd dword ptr [esp+54h]
    L_0041ef07:
        fstp dword ptr [esp+48h]
    L_0041ef0b:
        mov ecx,dword ptr [esp+48h]
    L_0041ef0f:
        fld dword ptr [esp+68h]
    L_0041ef13:
        mov dword ptr [esp+70h],ecx
    L_0041ef17:
        fadd dword ptr [esp+58h]
    L_0041ef1b:
        mov ecx,dword ptr [edx+3Ch]
    L_0041ef1e:
        mov dword ptr [esp+78h],ecx
    L_0041ef22:
        mov cx,word ptr [edx+464h]
    L_0041ef29:
        fstp dword ptr [esp+4Ch]
    L_0041ef2d:
        mov eax,dword ptr [esp+4Ch]
    L_0041ef31:
        mov dword ptr [esp+74h],eax
    L_0041ef35:
        fmul dword ptr [data_00470cd8]
    L_0041ef3b:
        mov eax,dword ptr [edx+44h]
    L_0041ef3e:
        mov dword ptr [esp+88h],eax
    L_0041ef45:
        mov ax,word ptr [edx+466h]
    L_0041ef4c:
        fsubr dword ptr [edx+444h]
    L_0041ef52:
        mov word ptr [esp+90h],cx
    L_0041ef5a:
        mov word ptr [esp+92h],ax
    L_0041ef62:
        fstp dword ptr [esp+84h]
    L_0041ef69:
        call asm_FUN_0041c510_0041c510
    L_0041ef6e:
        cmp ebx,dword ptr [esp+2Ch]
    L_0041ef72:
        jl asm_target_0041ee31
    L_0041ef78:
        mov ecx,dword ptr [esp+34Ch]
    L_0041ef7f:
        mov eax,dword ptr [esp+30h]
    L_0041ef83:
        pop edi
    L_0041ef84:
        pop esi
    L_0041ef85:
        xor ecx,ebp
    L_0041ef87:
        pop ebx
    L_0041ef88:
        call asm_security_check_cookie_00458ea5
    L_0041ef8d:
        mov esp,ebp
    L_0041ef8f:
        pop ebp
    L_0041ef90:
        ret 0Ch
    }
}

// 0x0041EFA0..0x0041F08C: FUN_0041efa0
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0041efa0_0041efa0() {
    __asm {
    L_0041efa0:
        push ebp
    L_0041efa1:
        mov ebp,esp
    L_0041efa3:
        and esp,0FFFFFFF8h
    L_0041efa6:
        sub esp,32Ch
    L_0041efac:
        mov eax,dword ptr [data_00473660]
    L_0041efb1:
        push ebx
    L_0041efb2:
        xor eax,ebp
    L_0041efb4:
        push esi
    L_0041efb5:
        mov esi,ecx
    L_0041efb7:
        mov dword ptr [esp+330h],eax
    L_0041efbe:
        lea ebx,[esi+24h]
    L_0041efc1:
        mov eax,ebx
    L_0041efc3:
        mov ecx,dword ptr [eax]
    L_0041efc5:
        mov dword ptr [esp+40h],ecx
    L_0041efc9:
        mov ecx,dword ptr [eax+4]
    L_0041efcc:
        mov eax,dword ptr [eax+8]
    L_0041efcf:
        push edi
    L_0041efd0:
        mov dword ptr [esp+48h],ecx
    L_0041efd4:
        mov dword ptr [esp+4Ch],eax
    L_0041efd8:
        xor eax,eax
    L_0041efda:
        mov ecx,40h
    L_0041efdf:
        lea edi,[esp+230h]
    L_0041efe6:
        rep stosd
    L_0041efe8:
        mov ecx,dword ptr [esi+3Ch]
    L_0041efeb:
        push 40C00000h
    L_0041eff0:
        xor edx,edx
    L_0041eff2:
        push ecx
    L_0041eff3:
        lea ecx,[esp+24h]
    L_0041eff7:
        mov dword ptr [esp+44h],esi
    L_0041effb:
        mov dword ptr [esp+30h],edx
    L_0041efff:
        mov dword ptr [esp+34h],edx
    L_0041f003:
        mov dword ptr [esp+14h],40C00000h
    L_0041f00b:
        mov dword ptr [esp+2Ch],eax
    L_0041f00f:
        call asm_SetPolar_Vector2_0041f800
    L_0041f014:
        fld dword ptr [esp+1Ch]
    L_0041f018:
        fadd dword ptr [ebx]
    L_0041f01a:
        fstp dword ptr [esp+30h]
    L_0041f01e:
        mov eax,dword ptr [esp+30h]
    L_0041f022:
        fld dword ptr [esp+20h]
    L_0041f026:
        mov dword ptr [esp+10h],eax
    L_0041f02a:
        fadd dword ptr [ebx+4]
    L_0041f02d:
        fstp dword ptr [esp+34h]
    L_0041f031:
        mov ecx,dword ptr [esp+34h]
    L_0041f035:
        fld dword ptr [esp+24h]
    L_0041f039:
        mov dword ptr [esp+14h],ecx
    L_0041f03d:
        fadd dword ptr [ebx+8]
    L_0041f040:
        fstp dword ptr [esp+38h]
    L_0041f044:
        mov eax,dword ptr [esp+38h]
    L_0041f048:
        fld dword ptr [esp+1Ch]
    L_0041f04c:
        mov dword ptr [esp+18h],eax
    L_0041f050:
        fadd st(0),st
    L_0041f052:
        mov dword ptr [esp+18h],edx
    L_0041f056:
        fstp dword ptr [esp+1Ch]
    L_0041f05a:
        fld dword ptr [esp+20h]
    L_0041f05e:
        fadd st(0),st
    L_0041f060:
        fstp dword ptr [esp+20h]
    L_0041f064:
        fld dword ptr [esp+24h]
    L_0041f068:
        fadd st(0),st
    L_0041f06a:
        fstp dword ptr [esp+24h]
    L_0041f06e:
        fld dword ptr [ebp+0Ch]
    L_0041f071:
        fmul dword ptr [ebp+0Ch]
    L_0041f074:
        fstp dword ptr [ebp+0Ch]
    L_0041f077:
        fld dword ptr [data_00470cd8]
    L_0041f07d:
        fcomp dword ptr [esi+40h]
    L_0041f080:
        fnstsw ax
    L_0041f082:
        test ah,5
    L_0041f085:
        jp asm_target_0041f3d9
    L_0041f08b:
        TH10_REL8(0xeb, 0x0041f08b, VA_asm_FUN_0041efa0_part_0041f090)
        _emit 0x8d
        _emit 0x49
        _emit 0x00

    L_0041f090:
        mov eax,dword ptr [ebp+8]
    L_0041f093:
        fld dword ptr [eax+4]
    L_0041f096:
        fsub dword ptr [esp+14h]
    L_0041f09a:
        fld dword ptr [eax]
    L_0041f09c:
        fsub dword ptr [esp+10h]
    L_0041f0a0:
        fld st(0)
    L_0041f0a2:
        fmul st,st(1)
    L_0041f0a4:
        fld st(2)
    L_0041f0a6:
        fmul st,st(3)
    L_0041f0a8:
        faddp st(1),st
    L_0041f0aa:
        fcomp dword ptr [ebp+0Ch]
    L_0041f0ad:
        fnstsw ax
    L_0041f0af:
        fstp st(0)
    L_0041f0b1:
        test ah,41h
    L_0041f0b4:
        fstp st(0)
    L_0041f0b6:
        je asm_target_0041f1d4
    L_0041f0bc:
        mov ecx,dword ptr [esp+28h]
    L_0041f0c0:
        mov eax,dword ptr [ebp+10h]
    L_0041f0c3:
        inc ecx
    L_0041f0c4:
        test eax,eax
    L_0041f0c6:
        mov byte ptr [esp+edx+230h],1
    L_0041f0ce:
        mov dword ptr [esp+28h],ecx
    L_0041f0d2:
        je short L_0041f14c
    L_0041f0d4:
        fld dword ptr [esp+10h]
    L_0041f0d8:
        fadd dword ptr [data_00470bcc]
    L_0041f0de:
        fcomp dword ptr [data_00470b40]
    L_0041f0e4:
        fnstsw ax
    L_0041f0e6:
        test ah,41h
    L_0041f0e9:
        jnp short L_0041f14c
    L_0041f0eb:
        fld dword ptr [esp+10h]
    L_0041f0ef:
        fsub dword ptr [data_00470bcc]
    L_0041f0f5:
        fcomp dword ptr [data_00470b3c]
    L_0041f0fb:
        fnstsw ax
    L_0041f0fd:
        test ah,1
    L_0041f100:
        je short L_0041f14c
    L_0041f102:
        fld dword ptr [esp+14h]
    L_0041f106:
        fadd dword ptr [data_00470bcc]
    L_0041f10c:
        fcomp dword ptr [data_00470b04]
    L_0041f112:
        fnstsw ax
    L_0041f114:
        test ah,41h
    L_0041f117:
        jnp short L_0041f14c
    L_0041f119:
        fld dword ptr [esp+14h]
    L_0041f11d:
        fsub dword ptr [data_00470bcc]
    L_0041f123:
        fcomp dword ptr [data_00470b38]
    L_0041f129:
        fnstsw ax
    L_0041f12b:
        test ah,1
    L_0041f12e:
        je short L_0041f14c
    L_0041f130:
        mov eax,dword ptr [data_00477818]
    L_0041f135:
        push 3F19999Ah
    L_0041f13a:
        push 0BFC90FDBh
    L_0041f13f:
        push 0FFFFFFFFh
    L_0041f141:
        push 8
    L_0041f143:
        lea ecx,[esp+20h]
    L_0041f147:
        call asm_FUN_0041bb00_0041bb00
    L_0041f14c:
        movsx ebx,word ptr [esi+466h]
    L_0041f153:
        mov ecx,dword ptr [data_0047781c]
    L_0041f159:
        mov esi,dword ptr [data_00491c10]
    L_0041f15f:
        mov edi,dword ptr [ecx+458h]
    L_0041f165:
        lea ebx,[ebx+ebx+11h]
    L_0041f169:
        call asm_FUN_00449950_00449950
    L_0041f16e:
        mov edx,dword ptr [esp+18h]
    L_0041f172:
        fld dword ptr [esp+10h]
    L_0041f176:
        mov esi,eax
    L_0041f178:
        mov eax,dword ptr [esi+35Ch]
    L_0041f17e:
        fadd dword ptr [data_00470b4c]
    L_0041f184:
        or eax,40000000h
    L_0041f189:
        mov dword ptr [esi+35Ch],eax
    L_0041f18f:
        mov dword ptr [esi+20h],0
    L_0041f196:
        fstp dword ptr [esi+340h]
    L_0041f19c:
        mov eax,esi
    L_0041f19e:
        fld dword ptr [esp+14h]
    L_0041f1a2:
        mov ecx,edi
    L_0041f1a4:
        fadd dword ptr [data_00470b48]
    L_0041f1aa:
        mov dword ptr [esi+348h],edx
    L_0041f1b0:
        fstp dword ptr [esi+344h]
    L_0041f1b6:
        call asm_AnimationObject_LoadScript_0043e710
    L_0041f1bb:
        mov edx,dword ptr [data_00491c10]
    L_0041f1c1:
        mov ebx,esi
    L_0041f1c3:
        lea eax,[esp+40h]
    L_0041f1c7:
        call asm_AnimationManager_RegisterPrimaryBack_004489d0
    L_0041f1cc:
        mov edx,dword ptr [esp+2Ch]
    L_0041f1d0:
        mov esi,dword ptr [esp+3Ch]
    L_0041f1d4:
        fld dword ptr [esp+10h]
    L_0041f1d8:
        inc edx
    L_0041f1d9:
        fadd dword ptr [esp+1Ch]
    L_0041f1dd:
        mov dword ptr [esp+2Ch],edx
    L_0041f1e1:
        fstp dword ptr [esp+10h]
    L_0041f1e5:
        fld dword ptr [esp+14h]
    L_0041f1e9:
        fadd dword ptr [esp+20h]
    L_0041f1ed:
        fstp dword ptr [esp+14h]
    L_0041f1f1:
        fld dword ptr [esp+18h]
    L_0041f1f5:
        fadd dword ptr [esp+24h]
    L_0041f1f9:
        fstp dword ptr [esp+18h]
    L_0041f1fd:
        fld dword ptr [esp+0Ch]
    L_0041f201:
        fadd dword ptr [data_00470cd8]
    L_0041f207:
        fstp dword ptr [esp+0Ch]
    L_0041f20b:
        fld dword ptr [esp+0Ch]
    L_0041f20f:
        fadd dword ptr [data_00470d1c]
    L_0041f215:
        fcomp dword ptr [esi+40h]
    L_0041f218:
        fnstsw ax
    L_0041f21a:
        test ah,5
    L_0041f21d:
        jnp asm_FUN_0041efa0_part_0041f090
    L_0041f223:
        mov eax,dword ptr [esp+28h]
    L_0041f227:
        test eax,eax
    L_0041f229:
        je asm_target_0041f3d9
    L_0041f22f:
        xor eax,eax
    L_0041f231:
        xor ebx,ebx
    L_0041f233:
        cmp edx,eax
    L_0041f235:
        TH10_REL8(0x7e, 0x0041f235, VA_asm_target_0041f259)
    L_0041f237:
        TH10_REL8(0xeb, 0x0041f237, VA_asm_FUN_0041efa0_part_0041f240)
        _emit 0x8d
        _emit 0xa4
        _emit 0x24
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x00

    L_0041f240:
        mov cl,byte ptr [esp+ebx+230h]
    L_0041f247:
        test cl,cl
    L_0041f249:
        je short L_0041f250
    L_0041f24b:
        inc ebx
    L_0041f24c:
        cmp ebx,edx
    L_0041f24e:
        jl short L_0041f240
    L_0041f250:
        cmp ebx,eax
    L_0041f252:
        je short L_0041f259
    L_0041f254:
        mov dword ptr [esi+40h],eax
    L_0041f257:
        jmp short L_0041f298
    L_0041f259:
        cmp edx,eax
    L_0041f25b:
        mov dword ptr [esp+0Ch],eax
    L_0041f25f:
        jle asm_target_0041f3d9
    L_0041f265:
        mov cl,byte ptr [esp+ebx+230h]
    L_0041f26c:
        test cl,cl
    L_0041f26e:
        jne short L_0041f27f
    L_0041f270:
        inc ebx
    L_0041f271:
        inc eax
    L_0041f272:
        cmp ebx,edx
    L_0041f274:
        jl short L_0041f265
    L_0041f276:
        mov dword ptr [esp+0Ch],eax
    L_0041f27a:
        jmp asm_target_0041f3d9
    L_0041f27f:
        cmp ebx,edx
    L_0041f281:
        mov dword ptr [esp+0Ch],eax
    L_0041f285:
        jge asm_target_0041f3d9
    L_0041f28b:
        fild dword ptr [esp+0Ch]
    L_0041f28f:
        fmul dword ptr [data_00470cd8]
    L_0041f295:
        fstp dword ptr [esi+40h]
    L_0041f298:
        cmp ebx,edx
    L_0041f29a:
        jge asm_target_0041f3d9
    L_0041f2a0:
        jmp short L_0041f2b0
    L_0041f2a2:
        mov edx,dword ptr [esp+2Ch]
    L_0041f2a6:
        mov esi,dword ptr [esp+3Ch]
    L_0041f2aa:
        lea ebx,[ebx+force_disp32_zero]
    L_0041f2b0:
        cmp ebx,edx
    L_0041f2b2:
        jge asm_target_0041f3d9
    L_0041f2b8:
        TH10_REL8(0xeb, 0x0041f2b8, VA_asm_FUN_0041efa0_part_0041f2c0)
        _emit 0x8d
        _emit 0x9b
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x00

    L_0041f2c0:
        mov al,byte ptr [esp+ebx+230h]
    L_0041f2c7:
        test al,al
    L_0041f2c9:
        je short L_0041f2d5
    L_0041f2cb:
        inc ebx
    L_0041f2cc:
        cmp ebx,edx
    L_0041f2ce:
        jl short L_0041f2c0
    L_0041f2d0:
        jmp asm_target_0041f3d9
    L_0041f2d5:
        cmp ebx,edx
    L_0041f2d7:
        jge asm_target_0041f3d9
    L_0041f2dd:
        xor eax,eax
    L_0041f2df:
        mov dword ptr [esp+0Ch],eax
    L_0041f2e3:
        mov dword ptr [esp+40h],ebx
    L_0041f2e7:
        TH10_REL8(0xeb, 0x0041f2e7, VA_asm_FUN_0041efa0_part_0041f2f0)
        _emit 0x8d
        _emit 0xa4
        _emit 0x24
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x00

    L_0041f2f0:
        mov cl,byte ptr [esp+ebx+230h]
    L_0041f2f7:
        test cl,cl
    L_0041f2f9:
        jne short L_0041f301
    L_0041f2fb:
        inc ebx
    L_0041f2fc:
        inc eax
    L_0041f2fd:
        cmp ebx,edx
    L_0041f2ff:
        jl short L_0041f2f0
    L_0041f301:
        mov dword ptr [esp+0Ch],eax
    L_0041f305:
        fild dword ptr [esp+0Ch]
    L_0041f309:
        xor eax,eax
    L_0041f30b:
        mov ecx,77h
    L_0041f310:
        lea edi,[esp+50h]
    L_0041f314:
        fmul dword ptr [data_00470cd8]
    L_0041f31a:
        rep stosd
    L_0041f31c:
        fst dword ptr [esp+64h]
    L_0041f320:
        fstp dword ptr [esp+60h]
    L_0041f324:
        push 0
    L_0041f326:
        fild dword ptr [esp+44h]
    L_0041f32a:
        lea edi,[esp+54h]
    L_0041f32e:
        mov dword ptr [esp+74h],41000000h
    L_0041f336:
        fld st(0)
    L_0041f338:
        fld dword ptr [esp+20h]
    L_0041f33c:
        fmul st,st(1)
    L_0041f33e:
        fld dword ptr [esp+24h]
    L_0041f342:
        fmul st,st(2)
    L_0041f344:
        fstp dword ptr [esp+18h]
    L_0041f348:
        fxch
    L_0041f34a:
        fmul dword ptr [esp+28h]
    L_0041f34e:
        fstp dword ptr [esp+1Ch]
    L_0041f352:
        fld dword ptr [esp+48h]
    L_0041f356:
        fadd st,st(1)
    L_0041f358:
        fstp dword ptr [esp+34h]
    L_0041f35c:
        mov eax,dword ptr [esp+34h]
    L_0041f360:
        mov dword ptr [esp+54h],eax
    L_0041f364:
        mov eax,dword ptr [esi+3Ch]
    L_0041f367:
        fstp st(0)
    L_0041f369:
        fld dword ptr [esp+4Ch]
    L_0041f36d:
        mov dword ptr [esp+60h],eax
    L_0041f371:
        fadd dword ptr [esp+18h]
    L_0041f375:
        mov ax,word ptr [esi+466h]
    L_0041f37c:
        mov word ptr [esp+7Ah],ax
    L_0041f381:
        fstp dword ptr [esp+38h]
    L_0041f385:
        mov ecx,dword ptr [esp+38h]
    L_0041f389:
        fld dword ptr [esp+50h]
    L_0041f38d:
        mov dword ptr [esp+58h],ecx
    L_0041f391:
        fadd dword ptr [esp+1Ch]
    L_0041f395:
        mov ecx,dword ptr [esi+44h]
    L_0041f398:
        mov dword ptr [esp+70h],ecx
    L_0041f39c:
        fstp dword ptr [esp+3Ch]
    L_0041f3a0:
        mov edx,dword ptr [esp+3Ch]
    L_0041f3a4:
        mov dword ptr [esp+5Ch],edx
    L_0041f3a8:
        fmul dword ptr [data_00470cd8]
    L_0041f3ae:
        mov dx,word ptr [esi+464h]
    L_0041f3b5:
        mov word ptr [esp+78h],dx
    L_0041f3ba:
        fsubr dword ptr [esi+444h]
    L_0041f3c0:
        mov esi,dword ptr [data_0047781c]
    L_0041f3c6:
        fstp dword ptr [esp+6Ch]
    L_0041f3ca:
        call asm_FUN_0041c510_0041c510
    L_0041f3cf:
        cmp ebx,dword ptr [esp+2Ch]
    L_0041f3d3:
        jl asm_target_0041f2a2
    L_0041f3d9:
        mov ecx,dword ptr [esp+334h]
    L_0041f3e0:
        mov eax,dword ptr [esp+28h]
    L_0041f3e4:
        pop edi
    L_0041f3e5:
        pop esi
    L_0041f3e6:
        xor ecx,ebp
    L_0041f3e8:
        pop ebx
    L_0041f3e9:
        call asm_security_check_cookie_00458ea5
    L_0041f3ee:
        mov esp,ebp
    L_0041f3f0:
        pop ebp
    L_0041f3f1:
        ret 0Ch
    }
}
