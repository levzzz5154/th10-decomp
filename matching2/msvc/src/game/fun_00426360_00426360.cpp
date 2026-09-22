// BLOCKED (D3905): closest_byte_count=409/409 (exact assembly retained);
// first_diff=0x00426364 at the EAX receiver transfer into EDI.
// residual_class=private EAX/ESI entry ABI, x87 evaluation order and stack
// slots, indirect callback loop shape, and internal early-return labels.
// variants_tested=MSVC 13.10.6030 /O2 /Gz /MT /Gy /G6 /GF /GS /Zl with typed
// cdecl/fastcall receiver models, float/double cast variants, callback-loop
// forms, and reordered x87 temporaries; no readable candidate preserved the
// 409-byte extent.
// next_lever=schema2 native-LTCG cluster with the real game-state caller and
// callback context, preserving EAX/ESI and the x87 stack schedule.
#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x004247F0..0x00424938: FUN_004247f0
// Naked body preserves the retail register/stack ABI.

// 0x00426360..0x004264F8: FUN_00426360
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00426360_00426360() {
    __asm {
    L_00426360:
        sub esp,14h
    L_00426363:
        push edi
    L_00426364:
        mov edi,eax
    L_00426366:
        cmp dword ptr [edi+458h],2
    L_0042636d:
        je asm_target_004264ef
    L_00426373:
        fld dword ptr [edi+3C0h]
    L_00426379:
        mov ecx,dword ptr [data_00491c10]
    L_0042637f:
        fadd dword ptr [data_00470b4c]
    L_00426385:
        push ebx
    L_00426386:
        push esi
    L_00426387:
        fstp dword ptr [edi+354h]
    L_0042638d:
        fld dword ptr [edi+3C4h]
    L_00426393:
        fadd dword ptr [data_00470b48]
    L_00426399:
        fstp dword ptr [edi+358h]
    L_0042639f:
        mov eax,dword ptr [edi+3C8h]
    L_004263a5:
        mov dword ptr [edi+35Ch],eax
    L_004263ab:
        lea eax,[edi+14h]
    L_004263ae:
        call asm_FUN_004451c0_004451c0
    L_004263b3:
        lea esi,[edi+3334h]
    L_004263b9:
        mov ebx,4
    L_004263be:
        mov edi,edi
    L_004263c0:
        mov eax,dword ptr [esi]
    L_004263c2:
        test eax,eax
    L_004263c4:
        je short L_004263ce
    L_004263c6:
        lea ecx,[esi-94h]
    L_004263cc:
        call eax
    L_004263ce:
        add esi,98h
    L_004263d4:
        dec ebx
    L_004263d5:
        jne short L_004263c0
    L_004263d7:
        mov eax,dword ptr [data_00477810]
    L_004263dc:
        test eax,eax
    L_004263de:
        je asm_target_004264ed
    L_004263e4:
        mov cl,byte ptr [eax+54h]
    L_004263e7:
        test cl,cl
    L_004263e9:
        jns asm_target_004264ed
    L_004263ef:
        mov ecx,dword ptr [data_00477704]
    L_004263f5:
        test ecx,ecx
    L_004263f7:
        je asm_target_004264ed
    L_004263fd:
        mov eax,dword ptr [data_0047770c]
    L_00426402:
        test eax,eax
    L_00426404:
        je asm_target_004264ed
    L_0042640a:
        mov edx,dword ptr [ecx+10h]
    L_0042640d:
        test edx,edx
    L_0042640f:
        jne asm_target_004264ed
    L_00426415:
        mov ecx,dword ptr [eax+9EB8h]
    L_0042641b:
        test ecx,ecx
    L_0042641d:
        jne asm_target_004264ed
    L_00426423:
        mov ecx,dword ptr [data_00477830]
    L_00426429:
        mov eax,dword ptr [ecx+4]
    L_0042642c:
        test eax,eax
    L_0042642e:
        jne asm_target_004264ed
    L_00426434:
        mov eax,dword ptr [data_00474c58]
    L_00426439:
        test eax,eax
    L_0042643b:
        je asm_target_004264ed
    L_00426441:
        fld dword ptr [edi+3C0h]
    L_00426447:
        push ecx
    L_00426448:
        fadd dword ptr [data_00470cbc]
    L_0042644e:
        mov dword ptr [esp+10h],eax
    L_00426452:
        fsub dword ptr [data_00470b48]
    L_00426458:
        fstp dword ptr [esp]
    L_0042645b:
        call asm_Sound_ForwardFloatAsDouble_00427c50
    L_00426460:
        fstp dword ptr [esp+10h]
    L_00426464:
        push ecx
    L_00426465:
        fild dword ptr [esp+10h]
    L_00426469:
        fmul dword ptr [data_00470cb8]
    L_0042646f:
        fadd dword ptr [esp+14h]
    L_00426473:
        fstp dword ptr [esp+1Ch]
    L_00426477:
        fld dword ptr [edi+3C4h]
    L_0042647d:
        fadd dword ptr [data_00470cb4]
    L_00426483:
        fsub dword ptr [data_00470be8]
    L_00426489:
        fstp dword ptr [esp]
    L_0042648c:
        call asm_Sound_ForwardFloatAsDouble_00427c50
    L_00426491:
        fst dword ptr [esp+14h]
    L_00426495:
        mov ebx,80000000h
    L_0042649a:
        fadd dword ptr [data_00470b08]
    L_004264a0:
        lea edi,[esp+10h]
    L_004264a4:
        fstp dword ptr [esp+1Ch]
    L_004264a8:
        call asm_FUN_0043bda0_0043bda0
    L_004264ad:
        fld dword ptr [esp+10h]
    L_004264b1:
        or ebx,0FFFFFFFFh
    L_004264b4:
        fsub dword ptr [data_00470afc]
    L_004264ba:
        fstp dword ptr [esp+10h]
    L_004264be:
        fld dword ptr [esp+18h]
    L_004264c2:
        fsub dword ptr [data_00470afc]
    L_004264c8:
        fstp dword ptr [esp+18h]
    L_004264cc:
        fld dword ptr [esp+14h]
    L_004264d0:
        fsub dword ptr [data_00470afc]
    L_004264d6:
        fstp dword ptr [esp+14h]
    L_004264da:
        fld dword ptr [esp+1Ch]
    L_004264de:
        fsub dword ptr [data_00470afc]
    L_004264e4:
        fstp dword ptr [esp+1Ch]
    L_004264e8:
        call asm_FUN_0043bda0_0043bda0
    L_004264ed:
        pop esi
    L_004264ee:
        pop ebx
    L_004264ef:
        mov eax,1
    L_004264f4:
        pop edi
    L_004264f5:
        add esp,14h
    L_004264f8:
        ret
    }
}
