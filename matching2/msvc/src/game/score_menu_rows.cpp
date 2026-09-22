// BLOCKED (D3907): closest_byte_count=0/419; first_diff=0x00431410
// (no readable native-LTCG body retained).
// residual_class=EDI receiver ABI, g_pGameThread/global table layouts,
// private AppendFormatted varargs convention, and float-stack loop state.
// variants_tested=["live Ghidra decompile at 0x00431410",
// "live caller 0x0042d260 and callee 0x00401630", "MSVC 13.10.6030
// authoritative probe (419/419 exact asm baseline)", "schema-2 native-LTCG
// feasibility review of receiver/formatter register topology"].
// next_lever=compile a schema-2 native-LTCG cluster containing the real
// 0x0042d260 caller, a typed score-menu body, and the real formatter callee;
// establish GameThread/table layouts before changing production metadata.
#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00431410..0x004315B2: FUN_00431410
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00431410_00431410() {
    __asm {
    L_00431410:
        mov eax,dword ptr [edi+20h]
    L_00431413:
        sub esp,0Ch
    L_00431416:
        cmp eax,2
    L_00431419:
        jl asm_target_004315aa
    L_0043141f:
        cmp eax,3
    L_00431422:
        jg asm_target_004315aa
    L_00431428:
        mov edx,dword ptr [data_004776e0]
    L_0043142e:
        push esi
    L_0043142f:
        mov esi,1
    L_00431434:
        mov dword ptr [edx+8988h],esi
    L_0043143a:
        cmp dword ptr [edi+2B4h],0Ah
    L_00431441:
        mov dword ptr [esp+4],42A00000h
    L_00431449:
        mov dword ptr [esp+8],42A00000h
    L_00431451:
        mov dword ptr [esp+0Ch],0
    L_00431459:
        jge short L_00431465
    L_0043145b:
        cmp dword ptr [edi+20h],3
    L_0043145f:
        jne asm_target_00431595
    L_00431465:
        mov eax,dword ptr [data_00474c68]
    L_0043146a:
        test eax,eax
    L_0043146c:
        mov dword ptr [esp+8],43580000h
    L_00431474:
        mov dword ptr [esp+4],43280000h
    L_0043147c:
        je short L_00431486
    L_0043147e:
        mov dword ptr [esp+4],43940000h
    L_00431486:
        push ebx
    L_00431487:
        jmp short L_00431490
    L_00431489:
        mov eax,dword ptr [data_00474c68]
    L_0043148e:
        mov edi,edi
    L_00431490:
        mov ebx,dword ptr [edi+24h]
    L_00431493:
        lea ecx,[esi-1]
    L_00431496:
        cmp ebx,ecx
    L_00431498:
        mov ecx,dword ptr [data_0047783c]
    L_0043149e:
        jne short L_00431509
    L_004314a0:
        mov ebx,dword ptr [data_00474c6c]
    L_004314a6:
        lea ebx,[ebx+eax*2]
    L_004314a9:
        add ebx,eax
    L_004314ab:
        mov eax,dword ptr [data_00474c74]
    L_004314b0:
        imul ebx,437Ch
    L_004314b6:
        lea eax,[eax+eax*2]
    L_004314b9:
        lea eax,[esi+eax*2]
    L_004314bc:
        add ebx,ecx
    L_004314be:
        cmp byte ptr [ebx+eax*8+4E1h],0
    L_004314c6:
        je short L_004314fd
    L_004314c8:
        cmp dword ptr [edi+20h],3
    L_004314cc:
        jne short L_004314f1
    L_004314ce:
        mov eax,dword ptr [edi+2B4h]
    L_004314d4:
        and eax,80000003h
    L_004314d9:
        jns short L_004314e0
    L_004314db:
        dec eax
    L_004314dc:
        or eax,0FFFFFFFCh
    L_004314df:
        inc eax
    L_004314e0:
        cmp eax,2
    L_004314e3:
        jl short L_004314f1
    L_004314e5:
        mov dword ptr [edx+8974h],0FF000000h
    L_004314ef:
        jmp short L_00431513
    L_004314f1:
        mov dword ptr [edx+8974h],0FFFFFF00h
    L_004314fb:
        jmp short L_00431513
    L_004314fd:
        mov dword ptr [edx+8974h],0FFDFDFDFh
    L_00431507:
        jmp short L_00431513
    L_00431509:
        mov dword ptr [edx+8974h],0FF808080h
    L_00431513:
        mov eax,dword ptr [data_00474c68]
    L_00431518:
        mov ebx,dword ptr [data_00474c6c]
    L_0043151e:
        lea ebx,[ebx+eax*2]
    L_00431521:
        add ebx,eax
    L_00431523:
        mov eax,dword ptr [data_00474c74]
    L_00431528:
        imul ebx,437Ch
    L_0043152e:
        add ebx,ecx
    L_00431530:
        lea eax,[eax+eax*2]
    L_00431533:
        lea eax,[esi+eax*2]
    L_00431536:
        mov cl,byte ptr [ebx+eax*8+4E1h]
    L_0043153d:
        lea eax,[ebx+eax*8]
    L_00431540:
        test cl,cl
    L_00431542:
        mov ecx,dword ptr [esi*4+47471Ch]
    L_00431549:
        lea ebx,[esp+8]
    L_0043154d:
        jne short L_00431560
    L_0043154f:
        push ecx
    L_00431550:
        push 46F008h
    L_00431555:
        push edx
    L_00431556:
        call asm_GameThread_AppendFormatted_00401630
    L_0043155b:
        add esp,0Ch
    L_0043155e:
        jmp short L_00431576
    L_00431560:
        mov eax,dword ptr [eax+4DCh]
    L_00431566:
        push eax
    L_00431567:
        push ecx
    L_00431568:
        push 46EFFCh
    L_0043156d:
        push edx
    L_0043156e:
        call asm_GameThread_AppendFormatted_00401630
    L_00431573:
        add esp,10h
    L_00431576:
        fld dword ptr [esp+0Ch]
    L_0043157a:
        mov edx,dword ptr [data_004776e0]
    L_00431580:
        fadd dword ptr [data_00470c0c]
    L_00431586:
        inc esi
    L_00431587:
        cmp esi,7
    L_0043158a:
        fstp dword ptr [esp+0Ch]
    L_0043158e:
        jl asm_target_00431489
    L_00431594:
        pop ebx
    L_00431595:
        mov dword ptr [edx+8974h],0FFFFFFFFh
    L_0043159f:
        mov dword ptr [edx+8988h],0
    L_004315a9:
        pop esi
    L_004315aa:
        mov eax,1
    L_004315af:
        add esp,0Ch
    L_004315b2:
        ret
    }
}
