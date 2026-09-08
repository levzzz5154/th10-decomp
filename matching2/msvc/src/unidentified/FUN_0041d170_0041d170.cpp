#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0041D170..0x0041D2B8: FUN_0041d170
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0041d170_0041d170() {
    __asm {
    L_0041d170:
        push ecx
    L_0041d171:
        push esi
    L_0041d172:
        mov esi,ecx
    L_0041d174:
        mov eax,dword ptr [esi+11Ch]
    L_0041d17a:
        cmp dword ptr [esi+0F8h],eax
    L_0041d180:
        mov dword ptr [esp+4],eax
    L_0041d184:
        jl asm_target_0041d229
    L_0041d18a:
        push ebx
    L_0041d18b:
        push edi
    L_0041d18c:
        mov edi,dword ptr [esi+40Ch]
    L_0041d192:
        xor ebx,ebx
    L_0041d194:
        cmp edi,ebx
    L_0041d196:
        jl short L_0041d1a3
    L_0041d198:
        push ebx
    L_0041d199:
        mov ecx,492590h
    L_0041d19e:
        call asm_AnimationManager_QueueResource_0043dc90
    L_0041d1a3:
        mov edx,dword ptr [esi+124h]
    L_0041d1a9:
        mov ecx,dword ptr [esi+120h]
    L_0041d1af:
        inc edx
    L_0041d1b0:
        mov eax,edx
    L_0041d1b2:
        cmp eax,ecx
    L_0041d1b4:
        mov dword ptr [esi+124h],edx
    L_0041d1ba:
        jl short L_0041d1c3
    L_0041d1bc:
        and dword ptr [esi+404h],0FFFFFFBFh
    L_0041d1c3:
        fld dword ptr [esi+10Ch]
    L_0041d1c9:
        fadd dword ptr [esi+3Ch]
    L_0041d1cc:
        fstp dword ptr [esi+3Ch]
    L_0041d1cf:
        fld dword ptr [esi+108h]
    L_0041d1d5:
        fst dword ptr [esi+48h]
    L_0041d1d8:
        mov eax,dword ptr [esi+104h]
    L_0041d1de:
        test al,1
    L_0041d1e0:
        fstp dword ptr [esp+0Ch]
    L_0041d1e4:
        jne short L_0041d20f
    L_0041d1e6:
        or eax,1
    L_0041d1e9:
        mov dword ptr [esi+0F8h],ebx
    L_0041d1ef:
        mov dword ptr [esi+0F4h],0FFF0BDC1h
    L_0041d1f9:
        mov dword ptr [esi+0FCh],ebx
    L_0041d1ff:
        mov dword ptr [esi+100h],476F78h
    L_0041d209:
        mov dword ptr [esi+104h],eax
    L_0041d20f:
        pop edi
    L_0041d210:
        mov dword ptr [esi+0F8h],ebx
    L_0041d216:
        mov dword ptr [esi+0FCh],ebx
    L_0041d21c:
        mov dword ptr [esi+0F4h],0FFFFFFFFh
    L_0041d226:
        pop ebx
    L_0041d227:
        jmp short L_0041d240
    L_0041d229:
        fld dword ptr [esi+48h]
    L_0041d22c:
        fld st(0)
    L_0041d22e:
        fmul dword ptr [esi+0FCh]
    L_0041d234:
        fidiv dword ptr [esp+4]
    L_0041d238:
        fsubr st,st(1)
    L_0041d23a:
        fstp dword ptr [esp+4]
    L_0041d23e:
        fstp st(0)
    L_0041d240:
        mov eax,dword ptr [esp+4]
    L_0041d244:
        mov ecx,dword ptr [esi+3Ch]
    L_0041d247:
        push eax
    L_0041d248:
        push ecx
    L_0041d249:
        lea ecx,[esi+30h]
    L_0041d24c:
        call asm_SetPolar_Vector2_0041f800
    L_0041d251:
        mov edx,dword ptr [esi+0F8h]
    L_0041d257:
        mov ecx,dword ptr [esi+100h]
    L_0041d25d:
        mov dword ptr [esi+0F4h],edx
    L_0041d263:
        fld dword ptr [ecx]
    L_0041d265:
        fcomp dword ptr [data_00470b68]
    L_0041d26b:
        fnstsw ax
    L_0041d26d:
        test ah,41h
    L_0041d270:
        jne short L_0041d29d
    L_0041d272:
        fld dword ptr [ecx]
    L_0041d274:
        fcomp dword ptr [data_00470b64]
    L_0041d27a:
        fnstsw ax
    L_0041d27c:
        test ah,5
    L_0041d27f:
        jp short L_0041d29d
    L_0041d281:
        fld dword ptr [esi+0FCh]
    L_0041d287:
        inc edx
    L_0041d288:
        fadd dword ptr [data_00470afc]
    L_0041d28e:
        mov dword ptr [esi+0F8h],edx
    L_0041d294:
        fstp dword ptr [esi+0FCh]
    L_0041d29a:
        pop esi
    L_0041d29b:
        pop ecx
    L_0041d29c:
        ret
    L_0041d29d:
        fld dword ptr [ecx]
    L_0041d29f:
        fadd dword ptr [esi+0FCh]
    L_0041d2a5:
        fst dword ptr [esi+0FCh]
    L_0041d2ab:
        call asm_FUN_00463b2c_00463b2c
    L_0041d2b0:
        mov dword ptr [esi+0F8h],eax
    L_0041d2b6:
        pop esi
    L_0041d2b7:
        pop ecx
    L_0041d2b8:
        ret
    }
}
