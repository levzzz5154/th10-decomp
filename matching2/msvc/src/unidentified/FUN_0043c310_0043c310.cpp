#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0043C310..0x0043C3BE: FUN_0043c310
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0043c310_0043c310() {
    __asm {
    L_0043c310:
        push ecx
    L_0043c311:
        push esi
    L_0043c312:
        mov esi,ecx
    L_0043c314:
        mov eax,dword ptr [esi+2Ch]
    L_0043c317:
        test eax,eax
    L_0043c319:
        jne short L_0043c342
    L_0043c31b:
        mov eax,dword ptr [esi+1Ch]
    L_0043c31e:
        test eax,eax
    L_0043c320:
        mov dword ptr [esp+4],eax
    L_0043c324:
        je short L_0043c360
    L_0043c326:
        cmp dword ptr [esi+34h],eax
    L_0043c329:
        jg short L_0043c360
    L_0043c32b:
        fld dword ptr [esi+38h]
    L_0043c32e:
        fmul dword ptr [data_00470bf4]
    L_0043c334:
        fidiv dword ptr [esp+4]
    L_0043c338:
        call asm_FUN_00463b2c_00463b2c
    L_0043c33d:
        mov dword ptr [esi+18h],eax
    L_0043c340:
        jmp short L_0043c360
    L_0043c342:
        cmp dword ptr [esi+34h],8
    L_0043c346:
        jg short L_0043c3b7
    L_0043c348:
        fld dword ptr [esi+38h]
    L_0043c34b:
        fmul dword ptr [data_00470b48]
    L_0043c351:
        call asm_FUN_00463b2c_00463b2c
    L_0043c356:
        mov ecx,80h
    L_0043c35b:
        sub ecx,eax
    L_0043c35d:
        mov dword ptr [esi+18h],ecx
    L_0043c360:
        mov edx,dword ptr [esi+34h]
    L_0043c363:
        mov ecx,dword ptr [esi+3Ch]
    L_0043c366:
        mov dword ptr [esi+30h],edx
    L_0043c369:
        fld dword ptr [ecx]
    L_0043c36b:
        fcomp dword ptr [data_00470b68]
    L_0043c371:
        fnstsw ax
    L_0043c373:
        test ah,41h
    L_0043c376:
        jne short L_0043c39f
    L_0043c378:
        fld dword ptr [ecx]
    L_0043c37a:
        fcomp dword ptr [data_00470b64]
    L_0043c380:
        fnstsw ax
    L_0043c382:
        test ah,5
    L_0043c385:
        jp short L_0043c39f
    L_0043c387:
        fld dword ptr [esi+38h]
    L_0043c38a:
        inc edx
    L_0043c38b:
        fadd dword ptr [data_00470afc]
    L_0043c391:
        mov dword ptr [esi+34h],edx
    L_0043c394:
        mov eax,1
    L_0043c399:
        fstp dword ptr [esi+38h]
    L_0043c39c:
        pop esi
    L_0043c39d:
        pop ecx
    L_0043c39e:
        ret
    L_0043c39f:
        fld dword ptr [ecx]
    L_0043c3a1:
        fadd dword ptr [esi+38h]
    L_0043c3a4:
        fst dword ptr [esi+38h]
    L_0043c3a7:
        call asm_FUN_00463b2c_00463b2c
    L_0043c3ac:
        mov dword ptr [esi+34h],eax
    L_0043c3af:
        mov eax,1
    L_0043c3b4:
        pop esi
    L_0043c3b5:
        pop ecx
    L_0043c3b6:
        ret
    L_0043c3b7:
        mov eax,7
    L_0043c3bc:
        pop esi
    L_0043c3bd:
        pop ecx
    L_0043c3be:
        ret
    }
}
