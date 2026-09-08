#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x004631D5..0x0046325F: CallCatchBlock
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_CallCatchBlock_004631d5() {
    __asm {
    L_004631d5:
        push 40h
    L_004631d7:
        push 46CAF0h
    L_004631dc:
        call asm_SEH_prolog_00454bbc
    L_004631e1:
        mov ebx,ecx
    L_004631e3:
        mov edi,dword ptr [ebp+0Ch]
    L_004631e6:
        mov esi,dword ptr [ebp+8]
    L_004631e9:
        mov dword ptr [ebp-20h],ebx
    L_004631ec:
        and dword ptr [ebp-48h],0
    L_004631f0:
        mov eax,dword ptr [edi-4]
    L_004631f3:
        mov dword ptr [ebp-38h],eax
    L_004631f6:
        push dword ptr [esi+18h]
    L_004631f9:
        lea eax,[ebp-50h]
    L_004631fc:
        push eax
    L_004631fd:
        call asm_CreateFrameInfo_004629eb
    L_00463202:
        pop ecx
    L_00463203:
        pop ecx
    L_00463204:
        mov dword ptr [ebp-3Ch],eax
    L_00463207:
        call asm_getptd_00456357
    L_0046320c:
        mov eax,dword ptr [eax+7Ch]
    L_0046320f:
        mov dword ptr [ebp-40h],eax
    L_00463212:
        call asm_getptd_00456357
    L_00463217:
        mov eax,dword ptr [eax+80h]
    L_0046321d:
        mov dword ptr [ebp-44h],eax
    L_00463220:
        call asm_getptd_00456357
    L_00463225:
        mov dword ptr [eax+7Ch],esi
    L_00463228:
        call asm_getptd_00456357
    L_0046322d:
        mov ecx,dword ptr [ebp+10h]
    L_00463230:
        mov dword ptr [eax+80h],ecx
    L_00463236:
        and dword ptr [ebp-4],0
    L_0046323a:
        mov dword ptr [ebp-4],1
    L_00463241:
        push dword ptr [ebp+1Ch]
    L_00463244:
        push dword ptr [ebp+18h]
    L_00463247:
        push ebx
    L_00463248:
        push dword ptr [ebp+14h]
    L_0046324b:
        push edi
    L_0046324c:
        call asm_CallCatchBlock2_00462a80
    L_00463251:
        add esp,14h
    L_00463254:
        mov dword ptr [ebp-20h],eax
    L_00463257:
        and dword ptr [ebp-4],0
    L_0046325b:
        jmp asm_CallCatchBlock_part_0046330f
    }
}

// 0x0046330F..0x00463320: CallCatchBlock
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_CallCatchBlock_part_0046330f() {
    __asm {
    L_0046330f:
        or dword ptr [ebp-4],0FFFFFFFFh
    L_00463313:
        call asm_FUN_0046332a_0046332a
    L_00463318:
        mov eax,dword ptr [ebp-20h]
    L_0046331b:
        call asm_SEH_epilog_00454bf7
    L_00463320:
        ret
    }
}
