#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00443FB0..0x00444232: FUN_00443fb0
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00443fb0_00443fb0() {
    __asm {
    L_00443fb0:
        sub esp,20h
    L_00443fb3:
        mov eax,edi
    L_00443fb5:
        call asm_FUN_00443b60_00443b60
    L_00443fba:
        test eax,eax
    L_00443fbc:
        je short L_00443fc5
    L_00443fbe:
        or eax,0FFFFFFFFh
    L_00443fc1:
        add esp,20h
    L_00443fc4:
        ret
    L_00443fc5:
        mov eax,dword ptr [edi+35Ch]
    L_00443fcb:
        fld dword ptr [data_00491e78]
    L_00443fd1:
        test ah,ah
    L_00443fd3:
        fsub dword ptr [data_00491e7c]
    L_00443fd9:
        jns short L_00443fe6
    L_00443fdb:
        mov eax,dword ptr [edi+300h]
    L_00443fe1:
        mov dword ptr [esp],eax
    L_00443fe4:
        jmp short L_00443fef
    L_00443fe6:
        mov ecx,dword ptr [edi+2FCh]
    L_00443fec:
        mov dword ptr [esp],ecx
    L_00443fef:
        fld dword ptr [edi+340h]
    L_00443ff5:
        push ebx
    L_00443ff6:
        fadd dword ptr [edi+334h]
    L_00443ffc:
        fld dword ptr [edi+344h]
    L_00444002:
        fadd dword ptr [edi+338h]
    L_00444008:
        fld dword ptr [edi+348h]
    L_0044400e:
        fadd dword ptr [edi+33Ch]
    L_00444014:
        fstp dword ptr [esp+20h]
    L_00444018:
        fxch
    L_0044401a:
        fadd dword ptr [edi+34Ch]
    L_00444020:
        fstp dword ptr [esp+0Ch]
    L_00444024:
        fadd dword ptr [edi+350h]
    L_0044402a:
        fld dword ptr [esp+20h]
    L_0044402e:
        fadd dword ptr [edi+354h]
    L_00444034:
        fld dword ptr [esp+0Ch]
    L_00444038:
        fsub dword ptr [data_00491d7c]
    L_0044403e:
        fstp dword ptr [esp+18h]
    L_00444042:
        mov edx,dword ptr [esp+18h]
    L_00444046:
        fxch
    L_00444048:
        mov dword ptr [esp+0Ch],edx
    L_0044404c:
        fsub dword ptr [data_00491d80]
    L_00444052:
        fstp dword ptr [esp+1Ch]
    L_00444056:
        mov eax,dword ptr [esp+1Ch]
    L_0044405a:
        mov dword ptr [esp+10h],eax
    L_0044405e:
        fsub dword ptr [data_00491d84]
    L_00444064:
        mov eax,dword ptr [esi+73245Ch]
    L_0044406a:
        test eax,eax
    L_0044406c:
        fstp dword ptr [esp+20h]
    L_00444070:
        mov ecx,dword ptr [esp+20h]
    L_00444074:
        mov dword ptr [esp+14h],ecx
    L_00444078:
        fld dword ptr [esp+14h]
    L_0044407c:
        fmul dword ptr [esp+14h]
    L_00444080:
        fld dword ptr [esp+10h]
    L_00444084:
        fmul dword ptr [esp+10h]
    L_00444088:
        faddp st(1),st
    L_0044408a:
        fld dword ptr [esp+0Ch]
    L_0044408e:
        fmul dword ptr [esp+0Ch]
    L_00444092:
        faddp st(1),st
    L_00444094:
        fsqrt
    L_00444096:
        je asm_target_00444128
    L_0044409c:
        movzx eax,byte ptr [esi+73245Ah]
    L_004440a3:
        movzx edx,byte ptr [esp+6]
    L_004440a8:
        imul eax,edx
    L_004440ab:
        shr eax,7
    L_004440ae:
        cmp eax,100h
    L_004440b3:
        jb short L_004440ba
    L_004440b5:
        mov eax,0FFh
    L_004440ba:
        movzx ecx,byte ptr [esp+5]
    L_004440bf:
        mov byte ptr [esp+6],al
    L_004440c3:
        movzx eax,byte ptr [esi+732459h]
    L_004440ca:
        imul eax,ecx
    L_004440cd:
        shr eax,7
    L_004440d0:
        cmp eax,100h
    L_004440d5:
        jb short L_004440dc
    L_004440d7:
        mov eax,0FFh
    L_004440dc:
        movzx edx,byte ptr [esp+4]
    L_004440e1:
        mov byte ptr [esp+5],al
    L_004440e5:
        movzx eax,byte ptr [esi+732458h]
    L_004440ec:
        imul eax,edx
    L_004440ef:
        shr eax,7
    L_004440f2:
        cmp eax,100h
    L_004440f7:
        jb short L_004440fe
    L_004440f9:
        mov eax,0FFh
    L_004440fe:
        movzx ecx,byte ptr [esp+7]
    L_00444103:
        mov bl,al
    L_00444105:
        movzx eax,byte ptr [esi+73245Bh]
    L_0044410c:
        imul eax,ecx
    L_0044410f:
        shr eax,7
    L_00444112:
        cmp eax,100h
    L_00444117:
        mov byte ptr [esp+4],bl
    L_0044411b:
        jb short L_00444122
    L_0044411d:
        mov eax,0FFh
    L_00444122:
        mov byte ptr [esp+7],al
    L_00444126:
        jmp short L_0044412c
    L_00444128:
        mov bl,byte ptr [esp+4]
    L_0044412c:
        fld dword ptr [data_00491e78]
    L_00444132:
        fcomp
    L_00444134:
        fnstsw ax
    L_00444136:
        test ah,5
    L_00444139:
        jp asm_target_00444207
    L_0044413f:
        fld dword ptr [data_00491e78]
    L_00444145:
        fsub st,st(1)
    L_00444147:
        fdivrp st(2),st
    L_00444149:
        fstp st(0)
    L_0044414b:
        fcom dword ptr [data_00470afc]
    L_00444151:
        fnstsw ax
    L_00444153:
        test ah,1
    L_00444156:
        jne short L_00444164
    L_00444158:
        fstp st(0)
    L_0044415a:
        mov eax,0FFFFFFFFh
    L_0044415f:
        pop ebx
    L_00444160:
        add esp,20h
    L_00444163:
        ret
    L_00444164:
        fld dword ptr [data_00491e80]
    L_0044416a:
        call asm_FUN_00463b2c_00463b2c
    L_0044416f:
        movzx edx,bl
    L_00444172:
        sub edx,eax
    L_00444174:
        mov dword ptr [esp+8],edx
    L_00444178:
        fild dword ptr [esp+8]
    L_0044417c:
        fmul st,st(1)
    L_0044417e:
        call asm_FUN_00463b2c_00463b2c
    L_00444183:
        fld dword ptr [data_00491e84]
    L_00444189:
        sub bl,al
    L_0044418b:
        mov byte ptr [data_004978d0],bl
    L_00444191:
        call asm_FUN_00463b2c_00463b2c
    L_00444196:
        mov bl,byte ptr [esp+5]
    L_0044419a:
        movzx ecx,bl
    L_0044419d:
        sub ecx,eax
    L_0044419f:
        mov dword ptr [esp+8],ecx
    L_004441a3:
        fild dword ptr [esp+8]
    L_004441a7:
        fmul st,st(1)
    L_004441a9:
        call asm_FUN_00463b2c_00463b2c
    L_004441ae:
        fld dword ptr [data_00491e88]
    L_004441b4:
        sub bl,al
    L_004441b6:
        mov byte ptr [data_004978d1],bl
    L_004441bc:
        call asm_FUN_00463b2c_00463b2c
    L_004441c1:
        mov bl,byte ptr [esp+6]
    L_004441c5:
        movzx edx,bl
    L_004441c8:
        sub edx,eax
    L_004441ca:
        mov dword ptr [esp+8],edx
    L_004441ce:
        fild dword ptr [esp+8]
    L_004441d2:
        fmul st,st(1)
    L_004441d4:
        call asm_FUN_00463b2c_00463b2c
    L_004441d9:
        fld dword ptr [data_00470afc]
    L_004441df:
        sub bl,al
    L_004441e1:
        fsub st,st(1)
    L_004441e3:
        movzx eax,byte ptr [esp+7]
    L_004441e8:
        mov dword ptr [esp+8],eax
    L_004441ec:
        mov byte ptr [data_004978d2],bl
    L_004441f2:
        fimul dword ptr [esp+8]
    L_004441f6:
        call asm_FUN_00463b2c_00463b2c
    L_004441fb:
        mov byte ptr [data_004978d3],al
    L_00444200:
        mov eax,dword ptr [data_004978d0]
    L_00444205:
        jmp short L_00444212
    L_00444207:
        mov eax,dword ptr [esp+4]
    L_0044420b:
        fstp st(0)
    L_0044420d:
        mov dword ptr [data_004978d0],eax
    L_00444212:
        mov dword ptr [data_004978ec],eax
    L_00444217:
        fstp st(0)
    L_00444219:
        mov dword ptr [data_00497908],eax
    L_0044421e:
        mov dword ptr [data_00497924],eax
    L_00444223:
        push 2
    L_00444225:
        mov eax,edi
    L_00444227:
        mov ecx,esi
    L_00444229:
        call asm_FUN_00442670_00442670
    L_0044422e:
        pop ebx
    L_0044422f:
        add esp,20h
    L_00444232:
        ret
    }
}
