#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00438AD0..0x0043900C: GameMain
// Naked body preserves the retail register/stack ABI.

// 0x004390E0..0x004391E8: FUN_004390e0
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_004390e0_004390e0() {
    __asm {
    L_004390e0:
        push ebx
    L_004390e1:
        mov ebx,dword ptr [esp+10h]
    L_004390e5:
        push ebp
    L_004390e6:
        mov ebp,dword ptr [esp+0Ch]
    L_004390ea:
        push esi
    L_004390eb:
        mov esi,dword ptr [esp+1Ch]
    L_004390ef:
        push edi
    L_004390f0:
        mov edi,dword ptr [esp+18h]
    L_004390f4:
        cmp edi,20h
    L_004390f7:
        ja asm_target_004391a1
    L_004390fd:
        je short L_0043914b
    L_004390ff:
        cmp edi,10h
    L_00439102:
        je short L_00439135
    L_00439104:
        cmp edi,14h
    L_00439107:
        je short L_0043913f
    L_00439109:
        cmp edi,1Ch
    L_0043910c:
        jne asm_target_004391d8
    L_00439112:
        xor eax,eax
    L_00439114:
        test ebx,ebx
    L_00439116:
        push esi
    L_00439117:
        sete al
    L_0043911a:
        push ebx
    L_0043911b:
        push edi
    L_0043911c:
        push ebp
    L_0043911d:
        mov dword ptr [data_004924fc],ebx
    L_00439123:
        mov dword ptr [data_00492500],eax
    L_00439128:
        call dword ptr [data_00466248]
    L_0043912e:
        pop edi
    L_0043912f:
        pop esi
    L_00439130:
        pop ebp
    L_00439131:
        pop ebx
    L_00439132:
        ret 10h
    L_00439135:
        or dword ptr [data_00491ff4],80h
    L_0043913f:
        pop edi
    L_00439140:
        pop esi
    L_00439141:
        pop ebp
    L_00439142:
        mov eax,1
    L_00439147:
        pop ebx
    L_00439148:
        ret 10h
    L_0043914b:
        mov al,byte ptr [data_00491d65]
    L_00439150:
        test al,al
    L_00439152:
        jne short L_00439179
    L_00439154:
        mov eax,dword ptr [data_00492500]
    L_00439159:
        test eax,eax
    L_0043915b:
        jne short L_00439179
    L_0043915d:
        push 0
    L_0043915f:
        call dword ptr [data_00466230]
    L_00439165:
        push 0
    L_00439167:
        call dword ptr [data_00466224]
    L_0043916d:
        pop edi
    L_0043916e:
        pop esi
    L_0043916f:
        pop ebp
    L_00439170:
        mov eax,1
    L_00439175:
        pop ebx
    L_00439176:
        ret 10h
    L_00439179:
        push 7F00h
    L_0043917e:
        push 0
    L_00439180:
        call dword ptr [data_00466260]
    L_00439186:
        push eax
    L_00439187:
        call dword ptr [data_00466224]
    L_0043918d:
        push 1
    L_0043918f:
        call dword ptr [data_00466230]
    L_00439195:
        pop edi
    L_00439196:
        pop esi
    L_00439197:
        pop ebp
    L_00439198:
        mov eax,1
    L_0043919d:
        pop ebx
    L_0043919e:
        ret 10h
    L_004391a1:
        cmp edi,201h
    L_004391a7:
        je short L_004391d1
    L_004391a9:
        cmp edi,3C9h
    L_004391af:
        jne short L_004391d8
    L_004391b1:
        mov edx,dword ptr [data_00491fe8]
    L_004391b7:
        test edx,edx
    L_004391b9:
        je short L_004391d8
    L_004391bb:
        call asm_FUN_0043aeb0_0043aeb0
    L_004391c0:
        push esi
    L_004391c1:
        push ebx
    L_004391c2:
        push edi
    L_004391c3:
        push ebp
    L_004391c4:
        call dword ptr [data_00466248]
    L_004391ca:
        pop edi
    L_004391cb:
        pop esi
    L_004391cc:
        pop ebp
    L_004391cd:
        pop ebx
    L_004391ce:
        ret 10h
    L_004391d1:
        push ebp
    L_004391d2:
        call dword ptr [data_004661f0]
    L_004391d8:
        push esi
    L_004391d9:
        push ebx
    L_004391da:
        push edi
    L_004391db:
        push ebp
    L_004391dc:
        call dword ptr [data_00466248]
    L_004391e2:
        pop edi
    L_004391e3:
        pop esi
    L_004391e4:
        pop ebp
    L_004391e5:
        pop ebx
    L_004391e6:
        ret 10h
    }
}
