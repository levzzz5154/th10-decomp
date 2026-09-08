#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0041D2C0..0x0041D3CC: FUN_0041d2c0
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_0041d2c0_0041d2c0() {
    __asm {
    L_0041d2c0:
        sub esp,0Ch
    L_0041d2c3:
        push esi
    L_0041d2c4:
        mov esi,ecx
    L_0041d2c6:
        mov eax,dword ptr [esi+90h]
    L_0041d2cc:
        cmp eax,dword ptr [esi+0B4h]
    L_0041d2d2:
        jl short L_0041d2e0
    L_0041d2d4:
        and dword ptr [esi+404h],0FFFFFFEFh
    L_0041d2db:
        jmp asm_target_0041d361
    L_0041d2e0:
        fld dword ptr [data_00476f78]
    L_0041d2e6:
        fmul dword ptr [esi+0A0h]
    L_0041d2ec:
        fadd dword ptr [esi+48h]
    L_0041d2ef:
        fstp dword ptr [esi+48h]
    L_0041d2f2:
        fld dword ptr [data_00476f78]
    L_0041d2f8:
        fmul dword ptr [esi+0A8h]
    L_0041d2fe:
        fld dword ptr [data_00476f78]
    L_0041d304:
        fmul dword ptr [esi+0ACh]
    L_0041d30a:
        fld dword ptr [data_00476f78]
    L_0041d310:
        fmul dword ptr [esi+0B0h]
    L_0041d316:
        fstp dword ptr [esp+0Ch]
    L_0041d31a:
        fxch
    L_0041d31c:
        fadd dword ptr [esi+30h]
    L_0041d31f:
        fstp dword ptr [esi+30h]
    L_0041d322:
        fadd dword ptr [esi+34h]
    L_0041d325:
        fstp dword ptr [esi+34h]
    L_0041d328:
        fld dword ptr [esp+0Ch]
    L_0041d32c:
        fadd dword ptr [esi+38h]
    L_0041d32f:
        fstp dword ptr [esi+38h]
    L_0041d332:
        fld dword ptr [esi+30h]
    L_0041d335:
        fabs
    L_0041d337:
        fcomp dword ptr [data_00470c58]
    L_0041d33d:
        fnstsw ax
    L_0041d33f:
        test ah,41h
    L_0041d342:
        je short L_0041d356
    L_0041d344:
        fld dword ptr [esi+34h]
    L_0041d347:
        fabs
    L_0041d349:
        fcomp dword ptr [data_00470c58]
    L_0041d34f:
        fnstsw ax
    L_0041d351:
        test ah,41h
    L_0041d354:
        jne short L_0041d361
    L_0041d356:
        fld dword ptr [esi+34h]
    L_0041d359:
        fld dword ptr [esi+30h]
    L_0041d35c:
        fpatan
    L_0041d35e:
        fstp dword ptr [esi+3Ch]
    L_0041d361:
        mov edx,dword ptr [esi+90h]
    L_0041d367:
        mov ecx,dword ptr [esi+98h]
    L_0041d36d:
        mov dword ptr [esi+8Ch],edx
    L_0041d373:
        fld dword ptr [ecx]
    L_0041d375:
        fcomp dword ptr [data_00470b68]
    L_0041d37b:
        fnstsw ax
    L_0041d37d:
        test ah,41h
    L_0041d380:
        jne short L_0041d3af
    L_0041d382:
        fld dword ptr [ecx]
    L_0041d384:
        fcomp dword ptr [data_00470b64]
    L_0041d38a:
        fnstsw ax
    L_0041d38c:
        test ah,5
    L_0041d38f:
        jp short L_0041d3af
    L_0041d391:
        fld dword ptr [esi+94h]
    L_0041d397:
        inc edx
    L_0041d398:
        fadd dword ptr [data_00470afc]
    L_0041d39e:
        mov dword ptr [esi+90h],edx
    L_0041d3a4:
        fstp dword ptr [esi+94h]
    L_0041d3aa:
        pop esi
    L_0041d3ab:
        add esp,0Ch
    L_0041d3ae:
        ret
    L_0041d3af:
        fld dword ptr [esi+94h]
    L_0041d3b5:
        fadd dword ptr [ecx]
    L_0041d3b7:
        fst dword ptr [esi+94h]
    L_0041d3bd:
        call asm_FUN_00463b2c_00463b2c
    L_0041d3c2:
        mov dword ptr [esi+90h],eax
    L_0041d3c8:
        pop esi
    L_0041d3c9:
        add esp,0Ch
    L_0041d3cc:
        ret
    }
}
