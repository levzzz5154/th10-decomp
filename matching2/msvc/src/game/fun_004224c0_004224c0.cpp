#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x004224C0..0x00422653: FUN_004224c0
// Naked body preserves the retail register/stack ABI.

// 0x004224C0..0x00422653: FUN_004224c0
// Naked body preserves the retail register/stack ABI.
// BLOCKED (D3704): closest_byte_count=0/404; first_diff=0x004224C0;
// residual_class=real-caller ABI and hidden GameThread/score-record layout;
// variants_tested=["live Ghidra decompile at 0x004224C0",
// "live caller 0x00422660", "MSVC 13.10 schema-2 baseline probe"];
// next_lever=native-LTCG cluster rooted by caller 0x00422660 with typed
// GameThread/score-record declarations; production region currently requires
// the custom EAX/stack argument shape and cannot be represented as plain C++.
extern "C" __declspec(naked) void __cdecl asm_FUN_004224c0_004224c0() {
    __asm {
    L_004224c0:
        push ecx
    L_004224c1:
        mov eax,dword ptr [data_004746d8]
    L_004224c6:
        lea edx,[eax+1]
    L_004224c9:
        lea esp,[esp+force_disp32_zero]
    L_004224d0:
        mov cl,byte ptr [eax]
    L_004224d2:
        inc eax
    L_004224d3:
        test cl,cl
    L_004224d5:
        jne short L_004224d0
    L_004224d7:
        mov ecx,dword ptr [data_004776e0]
    L_004224dd:
        push ebx
    L_004224de:
        push esi
    L_004224df:
        mov esi,dword ptr [esp+10h]
    L_004224e3:
        push edi
    L_004224e4:
        sub eax,edx
    L_004224e6:
        mov edi,eax
    L_004224e8:
        lea eax,[esi+2B4h]
    L_004224ee:
        push eax
    L_004224ef:
        push 46E1C8h
    L_004224f4:
        push ecx
    L_004224f5:
        lea ebx,[esp+24h]
    L_004224f9:
        call asm_GameThread_AppendFormatted_00401630
    L_004224fe:
        mov eax,dword ptr [esi+1E0h]
    L_00422504:
        lea edx,[eax+eax*8]
    L_00422507:
        mov dword ptr [esp+18h],edx
    L_0042250b:
        fild dword ptr [esp+18h]
    L_0042250f:
        add esp,0Ch
    L_00422512:
        cmp eax,8
    L_00422515:
        fadd dword ptr [esp+18h]
    L_00422519:
        fstp dword ptr [esp+18h]
    L_0042251d:
        jne short L_0042252d
    L_0042251f:
        fld dword ptr [esp+18h]
    L_00422523:
        fsub dword ptr [data_00470c10]
    L_00422529:
        fstp dword ptr [esp+18h]
    L_0042252d:
        mov eax,dword ptr [data_004776e0]
    L_00422532:
        push 46E1C4h
    L_00422537:
        push eax
    L_00422538:
        lea ebx,[esp+20h]
    L_0042253c:
        mov dword ptr [eax+8974h],0FFFFFF00h
    L_00422546:
        call asm_GameThread_AppendFormatted_00401630
    L_0042254b:
        mov eax,dword ptr [data_004776e0]
    L_00422550:
        or ecx,0FFFFFFFFh
    L_00422553:
        add esp,8
    L_00422556:
        xor esi,esi
    L_00422558:
        test edi,edi
    L_0042255a:
        mov dword ptr [eax+8974h],ecx
    L_00422560:
        mov dword ptr [esp+18h],42E00000h
    L_00422568:
        mov dword ptr [esp+1Ch],43A00000h
    L_00422570:
        mov dword ptr [esp+20h],0
    L_00422578:
        jle asm_target_00422647
    L_0042257e:
        push ebp
    L_0042257f:
        lea ebp,[edi-3]
    L_00422582:
        jmp short L_00422590
    L_00422584:
        mov eax,dword ptr [data_004776e0]
    L_00422589:
        lea esp,[esp+force_disp32_zero]
    L_00422590:
        mov edx,dword ptr [esp+18h]
    L_00422594:
        mov ebx,dword ptr [edx+0FCh]
    L_0042259a:
        xor ecx,ecx
    L_0042259c:
        cmp ebx,esi
    L_0042259e:
        setne cl
    L_004225a1:
        dec ecx
    L_004225a2:
        and ecx,7F7E80h
    L_004225a8:
        add ecx,0FF808080h
    L_004225ae:
        cmp esi,ebp
    L_004225b0:
        mov dword ptr [eax+8974h],ecx
    L_004225b6:
        jge short L_004225c5
    L_004225b8:
        mov ecx,dword ptr [data_004746d8]
    L_004225be:
        movsx edx,byte ptr [ecx+esi]
    L_004225c2:
        push edx
    L_004225c3:
        jmp short L_004225de
    L_004225c5:
        jne short L_004225ce
    L_004225c7:
        mov ecx,81h
    L_004225cc:
        jmp short L_004225dd
    L_004225ce:
        lea ecx,[edi-2]
    L_004225d1:
        xor edx,edx
    L_004225d3:
        cmp esi,ecx
    L_004225d5:
        setne dl
    L_004225d8:
        add edx,7Fh
    L_004225db:
        mov ecx,edx
    L_004225dd:
        push ecx
    L_004225de:
        push 46E1C0h
    L_004225e3:
        lea ebx,[esp+24h]
    L_004225e7:
        push eax
    L_004225e8:
        call asm_GameThread_AppendFormatted_00401630
    L_004225ed:
        xor edx,edx
    L_004225ef:
        mov eax,esi
    L_004225f1:
        mov ecx,0Dh
    L_004225f6:
        div ecx
    L_004225f8:
        add esp,0Ch
    L_004225fb:
        cmp edx,0Ch
    L_004225fe:
        jne short L_00422618
    L_00422600:
        fld dword ptr [esp+20h]
    L_00422604:
        mov dword ptr [esp+1Ch],42E00000h
    L_0042260c:
        fadd dword ptr [data_00470b48]
    L_00422612:
        fstp dword ptr [esp+20h]
    L_00422616:
        jmp short L_00422626
    L_00422618:
        fld dword ptr [esp+1Ch]
    L_0042261c:
        fadd dword ptr [data_00470c0c]
    L_00422622:
        fstp dword ptr [esp+1Ch]
    L_00422626:
        inc esi
    L_00422627:
        cmp esi,edi
    L_00422629:
        jl asm_target_00422584
    L_0042262f:
        mov edx,dword ptr [data_004776e0]
    L_00422635:
        pop ebp
    L_00422636:
        pop edi
    L_00422637:
        pop esi
    L_00422638:
        mov dword ptr [edx+8974h],0FFFFFFFFh
    L_00422642:
        pop ebx
    L_00422643:
        pop ecx
    L_00422644:
        ret 10h
    L_00422647:
        pop edi
    L_00422648:
        pop esi
    L_00422649:
        mov dword ptr [eax+8974h],ecx
    L_0042264f:
        pop ebx
    L_00422650:
        pop ecx
    L_00422651:
        ret 10h
    }
}
