#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00422150..0x004221DD: MainMenu_RegisterTasksRetail
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_MainMenu_RegisterTasksRetail_00422150() {
    __asm {
    L_00422150:
        push esi
    L_00422151:
        push edi
    L_00422152:
        push 422A90h
    L_00422157:
        call asm_SchedulerCallback_Create_00449ed0
    L_0042215c:
        mov esi,eax
    L_0042215e:
        mov edi,dword ptr [esi+4]
    L_00422161:
        mov eax,dword ptr [data_00491be4]
    L_00422166:
        and edi,0FFFFFFFDh
    L_00422169:
        mov dword ptr [esi+4],edi
    L_0042216c:
        push eax
    L_0042216d:
        mov edi,9
    L_00422172:
        mov dword ptr [esi+20h],ebx
    L_00422175:
        call asm_Scheduler_RegisterPrimary_00449ae0
    L_0042217a:
        push 422AA0h
    L_0042217f:
        mov dword ptr [ebx+8],esi
    L_00422182:
        call asm_SchedulerCallback_Create_00449ed0
    L_00422187:
        mov ecx,dword ptr [data_00491be4]
    L_0042218d:
        mov esi,eax
    L_0042218f:
        mov eax,dword ptr [esi+4]
    L_00422192:
        and eax,0FFFFFFFDh
    L_00422195:
        push ecx
    L_00422196:
        mov edi,2Eh
    L_0042219b:
        mov dword ptr [esi+20h],ebx
    L_0042219e:
        mov dword ptr [esi+4],eax
    L_004221a1:
        call asm_Scheduler_RegisterSecondary_00449b70
    L_004221a6:
        mov dword ptr [ebx+0Ch],esi
    L_004221a9:
        mov eax,dword ptr [ebx+20h]
    L_004221ac:
        xor ecx,ecx
    L_004221ae:
        test al,1
    L_004221b0:
        pop edi
    L_004221b1:
        pop esi
    L_004221b2:
        jne short L_004221ce
    L_004221b4:
        or eax,1
    L_004221b7:
        mov dword ptr [ebx+14h],ecx
    L_004221ba:
        mov dword ptr [ebx+10h],0FFF0BDC1h
    L_004221c1:
        mov dword ptr [ebx+18h],ecx
    L_004221c4:
        mov dword ptr [ebx+1Ch],476F78h
    L_004221cb:
        mov dword ptr [ebx+20h],eax
    L_004221ce:
        mov dword ptr [ebx+14h],ecx
    L_004221d1:
        mov dword ptr [ebx+18h],ecx
    L_004221d4:
        mov dword ptr [ebx+10h],0FFFFFFFFh
    L_004221db:
        xor eax,eax
    L_004221dd:
        ret
    }
}

// 0x004223F0..0x004224A2: FUN_004223f0
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_004223f0_004223f0() {
    __asm {
    L_004223f0:
        mov eax,dword ptr [esi+4]
    L_004223f3:
        cmp eax,0Dh
    L_004223f6:
        ja short L_00422450
    L_004223f8:
        movzx eax,byte ptr [eax+4224B0h]
    L_004223ff:
        jmp dword ptr [eax*4+4224A4h]
    L_00422406:
        test byte ptr [data_00474ca0],20h
    L_0042240d:
        jne short L_00422450
    L_0042240f:
        test byte ptr [data_00474e36],8
    L_00422416:
        jne short L_00422421
    L_00422418:
        test byte ptr [data_00491ff4],10h
    L_0042241f:
        je short L_00422450
    L_00422421:
        mov ecx,dword ptr [data_00477810]
    L_00422427:
        mov eax,dword ptr [ecx+8]
    L_0042242a:
        test eax,eax
    L_0042242c:
        je short L_00422450
    L_0042242e:
        test byte ptr [eax+4],2
    L_00422432:
        je short L_00422450
    L_00422434:
        cmp dword ptr [ecx+14h],1Eh
    L_00422438:
        jl short L_00422450
    L_0042243a:
        push esi
    L_0042243b:
        call asm_FUN_00422ab0_00422ab0
    L_00422440:
        jmp short L_00422450
    L_00422442:
        push esi
    L_00422443:
        call asm_FUN_00422c80_00422c80
    L_00422448:
        jmp short L_00422450
    L_0042244a:
        push esi
    L_0042244b:
        call asm_FUN_004236f0_004236f0
    L_00422450:
        mov edx,dword ptr [esi+14h]
    L_00422453:
        mov ecx,dword ptr [esi+1Ch]
    L_00422456:
        mov dword ptr [esi+10h],edx
    L_00422459:
        fld dword ptr [ecx]
    L_0042245b:
        fcomp dword ptr [data_00470b68]
    L_00422461:
        fnstsw ax
    L_00422463:
        test ah,41h
    L_00422466:
        jne short L_0042248d
    L_00422468:
        fld dword ptr [ecx]
    L_0042246a:
        fcomp dword ptr [data_00470b64]
    L_00422470:
        fnstsw ax
    L_00422472:
        test ah,5
    L_00422475:
        jp short L_0042248d
    L_00422477:
        fld dword ptr [esi+18h]
    L_0042247a:
        inc edx
    L_0042247b:
        fadd dword ptr [data_00470afc]
    L_00422481:
        mov dword ptr [esi+14h],edx
    L_00422484:
        mov eax,1
    L_00422489:
        fstp dword ptr [esi+18h]
    L_0042248c:
        ret
    L_0042248d:
        fld dword ptr [ecx]
    L_0042248f:
        fadd dword ptr [esi+18h]
    L_00422492:
        fst dword ptr [esi+18h]
    L_00422495:
        call asm_FUN_00463b2c_00463b2c
    L_0042249a:
        mov dword ptr [esi+14h],eax
    L_0042249d:
        mov eax,1
    L_004224a2:
        ret
    }
}

// 0x00422660..0x00422916: FUN_00422660
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00422660_00422660() {
    __asm {
    L_00422660:
        mov ecx,dword ptr [data_004776e0]
    L_00422666:
        sub esp,10h
    L_00422669:
        push ebx
    L_0042266a:
        push ebp
    L_0042266b:
        mov ebp,dword ptr [esp+1Ch]
    L_0042266f:
        mov dword ptr [ecx+8988h],1
    L_00422679:
        mov eax,dword ptr [ebp+4]
    L_0042267c:
        add eax,0FFFFFFF6h
    L_0042267f:
        cmp eax,9
    L_00422682:
        push esi
    L_00422683:
        push edi
    L_00422684:
        ja asm_target_00422a52
    L_0042268a:
        movzx eax,byte ptr [eax+422A7Ch]
    L_00422691:
        jmp dword ptr [eax*4+422A6Ch]
    L_00422698:
        lea edx,[ebp+1ECh]
    L_0042269e:
        mov dword ptr [esp+14h],42400000h
    L_004226a6:
        mov dword ptr [esp+18h],42800000h
    L_004226ae:
        mov dword ptr [esp+1Ch],0
    L_004226b6:
        xor edi,edi
    L_004226b8:
        mov dword ptr [esp+24h],edx
    L_004226bc:
        TH10_NOP_LEA_ESP_DISP8()
    L_004226c0:
        mov esi,dword ptr [ebp+24h]
    L_004226c3:
        mov edx,dword ptr [esp+24h]
    L_004226c7:
        xor eax,eax
    L_004226c9:
        cmp esi,edi
    L_004226cb:
        setne al
    L_004226ce:
        dec eax
    L_004226cf:
        and eax,7F7E80h
    L_004226d4:
        add eax,0FF808080h
    L_004226d9:
        mov dword ptr [ecx+8974h],eax
    L_004226df:
        mov eax,dword ptr [edx]
    L_004226e1:
        test eax,eax
    L_004226e3:
        je short L_0042274c
    L_004226e5:
        mov esi,dword ptr [eax+18h]
    L_004226e8:
        lea eax,[esi+0Ch]
    L_004226eb:
        push eax
    L_004226ec:
        call asm_localtime_00452baa
    L_004226f1:
        mov ecx,dword ptr [esi+5Ch]
    L_004226f4:
        mov edx,dword ptr [ecx*4+474744h]
    L_004226fb:
        mov ecx,dword ptr [esi+58h]
    L_004226fe:
        push edx
    L_004226ff:
        mov edx,dword ptr [ecx*4+474708h]
    L_00422706:
        mov ecx,dword ptr [esi+50h]
    L_00422709:
        push edx
    L_0042270a:
        mov edx,dword ptr [esi+54h]
    L_0042270d:
        lea ecx,[ecx+ecx*2]
    L_00422710:
        add ecx,edx
    L_00422712:
        mov edx,dword ptr [ecx*4+4746DCh]
    L_00422719:
        mov ecx,dword ptr [eax+0Ch]
    L_0042271c:
        push edx
    L_0042271d:
        mov edx,dword ptr [eax+10h]
    L_00422720:
        mov eax,dword ptr [eax+14h]
    L_00422723:
        push ecx
    L_00422724:
        inc edi
    L_00422725:
        inc edx
    L_00422726:
        push edx
    L_00422727:
        cdq
    L_00422728:
        mov ecx,64h
    L_0042272d:
        idiv ecx
    L_0042272f:
        lea ebx,[esp+2Ch]
    L_00422733:
        push edx
    L_00422734:
        mov edx,dword ptr [data_004776e0]
    L_0042273a:
        push esi
    L_0042273b:
        push edi
    L_0042273c:
        push 46E19Ch
    L_00422741:
        push edx
    L_00422742:
        call asm_GameThread_AppendFormatted_00401630
    L_00422747:
        add esp,2Ch
    L_0042274a:
        jmp short L_00422760
    L_0042274c:
        inc edi
    L_0042274d:
        push edi
    L_0042274e:
        push 46E174h
    L_00422753:
        push ecx
    L_00422754:
        lea ebx,[esp+20h]
    L_00422758:
        call asm_GameThread_AppendFormatted_00401630
    L_0042275d:
        add esp,0Ch
    L_00422760:
        fld dword ptr [esp+18h]
    L_00422764:
        mov ecx,dword ptr [esp+24h]
    L_00422768:
        fadd dword ptr [data_00470c08]
    L_0042276e:
        add ecx,4
    L_00422771:
        cmp edi,19h
    L_00422774:
        mov dword ptr [esp+24h],ecx
    L_00422778:
        mov ecx,dword ptr [data_004776e0]
    L_0042277e:
        fstp dword ptr [esp+18h]
    L_00422782:
        jl asm_target_004226c0
    L_00422788:
        jmp asm_target_00422a48
    L_0042278d:
        mov eax,dword ptr [ebp+14h]
    L_00422790:
        cmp eax,0Ah
    L_00422793:
        mov edi,dword ptr [ebp+24h]
    L_00422796:
        mov dword ptr [esp+1Ch],0
    L_0042279e:
        mov dword ptr [esp+24h],edi
    L_004227a2:
        mov dword ptr [esp+10h],eax
    L_004227a6:
        jge short L_004227d4
    L_004227a8:
        fild dword ptr [esp+24h]
    L_004227ac:
        fmul dword ptr [data_00470c08]
    L_004227b2:
        fadd dword ptr [data_00470bc8]
    L_004227b8:
        fld dword ptr [data_00470b4c]
    L_004227be:
        fsub st,st(1)
    L_004227c0:
        fimul dword ptr [esp+10h]
    L_004227c4:
        fmul dword ptr [data_00470c18]
    L_004227ca:
        fadd st,st(1)
    L_004227cc:
        fstp dword ptr [esp+18h]
    L_004227d0:
        fstp st(0)
    L_004227d2:
        jmp short L_004227dc
    L_004227d4:
        mov dword ptr [esp+18h],43600000h
    L_004227dc:
        mov edx,dword ptr [esp+18h]
    L_004227e0:
        sub esp,0Ch
    L_004227e3:
        mov eax,esp
    L_004227e5:
        mov dword ptr [esp+20h],42CC0000h
    L_004227ed:
        mov ecx,dword ptr [esp+20h]
    L_004227f1:
        mov dword ptr [eax],ecx
    L_004227f3:
        mov ecx,dword ptr [esp+28h]
    L_004227f7:
        mov dword ptr [eax+4],edx
    L_004227fa:
        push ebp
    L_004227fb:
        mov dword ptr [eax+8],ecx
    L_004227fe:
        call asm_FUN_004224c0_004224c0
    L_00422803:
        mov edx,dword ptr [data_00477838]
    L_00422809:
        mov esi,dword ptr [edx+18h]
    L_0042280c:
        lea eax,[esi+0Ch]
    L_0042280f:
        push eax
    L_00422810:
        mov dword ptr [esp+18h],42400000h
    L_00422818:
        call asm_localtime_00452baa
    L_0042281d:
        mov ecx,dword ptr [data_00474c7c]
    L_00422823:
        mov edx,dword ptr [ecx*4+474744h]
    L_0042282a:
        mov ecx,dword ptr [esi+58h]
    L_0042282d:
        mov ebx,dword ptr [esi+54h]
    L_00422830:
        push edx
    L_00422831:
        mov edx,dword ptr [ecx*4+474708h]
    L_00422838:
        mov ecx,dword ptr [esi+50h]
    L_0042283b:
        push edx
    L_0042283c:
        lea ecx,[ecx+ecx*2]
    L_0042283f:
        add ecx,ebx
    L_00422841:
        mov edx,dword ptr [ecx*4+4746DCh]
    L_00422848:
        mov ecx,dword ptr [eax+0Ch]
    L_0042284b:
        push edx
    L_0042284c:
        mov edx,dword ptr [eax+10h]
    L_0042284f:
        mov eax,dword ptr [eax+14h]
    L_00422852:
        push ecx
    L_00422853:
        inc edx
    L_00422854:
        push edx
    L_00422855:
        cdq
    L_00422856:
        mov ecx,64h
    L_0042285b:
        idiv ecx
    L_0042285d:
        inc edi
    L_0042285e:
        lea ebx,[esp+2Ch]
    L_00422862:
        push edx
    L_00422863:
        mov edx,dword ptr [data_004776e0]
    L_00422869:
        push edi
    L_0042286a:
        push 46E148h
    L_0042286f:
        push edx
    L_00422870:
        call asm_GameThread_AppendFormatted_00401630
    L_00422875:
        mov ecx,dword ptr [data_004776e0]
    L_0042287b:
        add esp,28h
    L_0042287e:
        jmp asm_target_00422a52
    L_00422883:
        mov eax,dword ptr [ebp+24h]
    L_00422886:
        push 46E12Ch
    L_0042288b:
        push ecx
    L_0042288c:
        lea ebx,[esp+1Ch]
    L_00422890:
        mov dword ptr [esp+1Ch],42400000h
    L_00422898:
        mov dword ptr [esp+24h],0
    L_004228a0:
        mov dword ptr [esp+2Ch],eax
    L_004228a4:
        mov dword ptr [esp+20h],42800000h
    L_004228ac:
        call asm_GameThread_AppendFormatted_00401630
    L_004228b1:
        fild dword ptr [esp+2Ch]
    L_004228b5:
        mov eax,dword ptr [ebp+1E8h]
    L_004228bb:
        add esp,8
    L_004228be:
        test eax,eax
    L_004228c0:
        fmul dword ptr [data_00470c0c]
    L_004228c6:
        mov dword ptr [esp+14h],42960000h
    L_004228ce:
        fadd dword ptr [data_00470c80]
    L_004228d4:
        fstp dword ptr [esp+18h]
    L_004228d8:
        jne short L_004228fb
    L_004228da:
        mov edx,dword ptr [esp+14h]
    L_004228de:
        mov eax,dword ptr [esp+18h]
    L_004228e2:
        sub esp,0Ch
    L_004228e5:
        mov ecx,esp
    L_004228e7:
        mov dword ptr [ecx],edx
    L_004228e9:
        mov edx,dword ptr [esp+28h]
    L_004228ed:
        mov dword ptr [ecx+4],eax
    L_004228f0:
        push ebp
    L_004228f1:
        mov dword ptr [ecx+8],edx
    L_004228f4:
        call asm_FUN_004224c0_004224c0
    L_004228f9:
        jmp short L_00422903
    L_004228fb:
        mov dword ptr [esp+24h],0FFFFFFFFh
    L_00422903:
        mov dword ptr [esp+14h],42400000h
    L_0042290b:
        mov dword ptr [esp+18h],42C00000h
    L_00422913:
        xor esi,esi
    L_00422915:
        TH10_REL8(0xeb, 0x00422915, VA_asm_FUN_00422660_part_00422920)
        _emit 0x8d
        _emit 0xa4
        _emit 0x24
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x8b
        _emit 0xff

    L_00422920:
        mov edx,dword ptr [esp+24h]
    L_00422924:
        mov ebx,dword ptr [data_004776e0]
    L_0042292a:
        xor eax,eax
    L_0042292c:
        cmp esi,edx
    L_0042292e:
        setne al
    L_00422931:
        mov edi,dword ptr [data_0047783c]
    L_00422937:
        dec eax
    L_00422938:
        and eax,7F7E80h
    L_0042293d:
        add eax,0FF808080h
    L_00422942:
        mov dword ptr [ebx+8974h],eax
    L_00422948:
        mov ecx,dword ptr [data_00474c68]
    L_0042294e:
        mov edx,dword ptr [data_00474c6c]
    L_00422954:
        lea eax,[edx+ecx*2]
    L_00422957:
        add eax,ecx
    L_00422959:
        mov ecx,dword ptr [data_00474c74]
    L_0042295f:
        imul eax,437Ch
    L_00422965:
        lea ecx,[ecx+ecx*4]
    L_00422968:
        lea ecx,[esi+ecx*2]
    L_0042296b:
        lea ecx,[ecx+ecx*2]
    L_0042296e:
        shl ecx,3
    L_00422971:
        lea edx,[ecx+eax]
    L_00422974:
        mov ebp,dword ptr [edx+edi+28h]
    L_00422978:
        add edx,edi
    L_0042297a:
        test ebp,ebp
    L_0042297c:
        je asm_target_00422a0a
    L_00422982:
        lea eax,[eax+edi+8]
    L_00422986:
        lea eax,[ecx+eax+20h]
    L_0042298a:
        push eax
    L_0042298b:
        call asm_localtime_00452baa
    L_00422990:
        mov ecx,dword ptr [data_00474c68]
    L_00422996:
        mov edx,dword ptr [data_00474c6c]
    L_0042299c:
        mov ebp,dword ptr [data_0047783c]
    L_004229a2:
        lea edx,[edx+ecx*2]
    L_004229a5:
        add edx,ecx
    L_004229a7:
        mov ecx,dword ptr [data_00474c74]
    L_004229ad:
        imul edx,437Ch
    L_004229b3:
        add edx,ebp
    L_004229b5:
        lea ecx,[ecx+ecx*4]
    L_004229b8:
        lea ecx,[esi+ecx*2]
    L_004229bb:
        lea ecx,[ecx+ecx*2]
    L_004229be:
        lea ecx,[edx+ecx*8]
    L_004229c1:
        movsx edx,byte ptr [ecx+1Ch]
    L_004229c5:
        mov edx,dword ptr [edx*4+47471Ch]
    L_004229cc:
        push edx
    L_004229cd:
        mov edx,dword ptr [eax+0Ch]
    L_004229d0:
        push edx
    L_004229d1:
        mov edx,dword ptr [eax+10h]
    L_004229d4:
        mov eax,dword ptr [eax+14h]
    L_004229d7:
        inc esi
    L_004229d8:
        inc edx
    L_004229d9:
        push edx
    L_004229da:
        cdq
    L_004229db:
        mov edi,64h
    L_004229e0:
        idiv edi
    L_004229e2:
        movsx eax,byte ptr [ecx+1Dh]
    L_004229e6:
        add ecx,1Eh
    L_004229e9:
        lea ebx,[esp+24h]
    L_004229ed:
        push edx
    L_004229ee:
        mov edx,dword ptr [ecx-6]
    L_004229f1:
        push eax
    L_004229f2:
        mov eax,dword ptr [data_004776e0]
    L_004229f7:
        push edx
    L_004229f8:
        push ecx
    L_004229f9:
        push esi
    L_004229fa:
        push 46E108h
    L_004229ff:
        push eax
    L_00422a00:
        call asm_GameThread_AppendFormatted_00401630
    L_00422a05:
        add esp,2Ch
    L_00422a08:
        jmp short L_00422a2b
    L_00422a0a:
        movsx ecx,byte ptr [edx+1Dh]
    L_00422a0e:
        mov eax,dword ptr [edx+18h]
    L_00422a11:
        push ecx
    L_00422a12:
        push eax
    L_00422a13:
        add edx,1Eh
    L_00422a16:
        push edx
    L_00422a17:
        inc esi
    L_00422a18:
        push esi
    L_00422a19:
        push 46E0E8h
    L_00422a1e:
        push ebx
    L_00422a1f:
        lea ebx,[esp+2Ch]
    L_00422a23:
        call asm_GameThread_AppendFormatted_00401630
    L_00422a28:
        add esp,18h
    L_00422a2b:
        cmp esi,0Ah
    L_00422a2e:
        fld dword ptr [esp+18h]
    L_00422a32:
        fadd dword ptr [data_00470c0c]
    L_00422a38:
        fstp dword ptr [esp+18h]
    L_00422a3c:
        jl asm_FUN_00422660_part_00422920
    L_00422a42:
        mov ecx,dword ptr [data_004776e0]
    L_00422a48:
        mov dword ptr [ecx+8974h],0FFFFFFFFh
    L_00422a52:
        pop edi
    L_00422a53:
        pop esi
    L_00422a54:
        pop ebp
    L_00422a55:
        mov dword ptr [ecx+8988h],0
    L_00422a5f:
        mov eax,1
    L_00422a64:
        pop ebx
    L_00422a65:
        add esp,10h
    L_00422a68:
        ret 4
    }
}

// 0x00422AB0..0x00422C2D: FUN_00422ab0
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00422ab0_00422ab0() {
    __asm {
    L_00422ab0:
        push ebx
    L_00422ab1:
        push ebp
    L_00422ab2:
        mov ebp,dword ptr [esp+0Ch]
    L_00422ab6:
        mov dword ptr [ebp+4],1
    L_00422abd:
        mov eax,dword ptr [ebp+20h]
    L_00422ac0:
        push esi
    L_00422ac1:
        xor ecx,ecx
    L_00422ac3:
        test al,1
    L_00422ac5:
        push edi
    L_00422ac6:
        jne short L_00422ae2
    L_00422ac8:
        or eax,1
    L_00422acb:
        mov dword ptr [ebp+14h],ecx
    L_00422ace:
        mov dword ptr [ebp+10h],0FFF0BDC1h
    L_00422ad5:
        mov dword ptr [ebp+18h],ecx
    L_00422ad8:
        mov dword ptr [ebp+1Ch],476F78h
    L_00422adf:
        mov dword ptr [ebp+20h],eax
    L_00422ae2:
        mov eax,dword ptr [data_00477810]
    L_00422ae7:
        mov dword ptr [ebp+14h],ecx
    L_00422aea:
        mov dword ptr [ebp+18h],ecx
    L_00422aed:
        mov dword ptr [ebp+10h],0FFFFFFFFh
    L_00422af4:
        or dword ptr [eax+58h],10h
    L_00422af8:
        mov eax,dword ptr [data_004776e0]
    L_00422afd:
        mov esi,dword ptr [data_00491c10]
    L_00422b03:
        mov edi,dword ptr [eax+8998h]
    L_00422b09:
        call asm_FUN_00449950_00449950
    L_00422b0e:
        mov ebx,eax
    L_00422b10:
        mov edx,dword ptr [ebx+35Ch]
    L_00422b16:
        push 0
    L_00422b18:
        or edx,40000000h
    L_00422b1e:
        push ebx
    L_00422b1f:
        mov ecx,edi
    L_00422b21:
        mov dword ptr [ebx+20h],0Fh
    L_00422b28:
        mov dword ptr [ebx+35Ch],edx
    L_00422b2e:
        call asm_FUN_00449870_00449870
    L_00422b33:
        mov esi,dword ptr [data_00491c10]
    L_00422b39:
        lea eax,[esp+14h]
    L_00422b3d:
        mov edx,esi
    L_00422b3f:
        call asm_AnimationManager_RegisterSecondaryBack_00448ac0
    L_00422b44:
        mov eax,dword ptr [esp+14h]
    L_00422b48:
        push 1C0h
    L_00422b4d:
        push 180h
    L_00422b52:
        push 10h
    L_00422b54:
        push 20h
    L_00422b56:
        push eax
    L_00422b57:
        mov dword ptr [ebp+1D8h],eax
    L_00422b5d:
        call asm_FUN_00424480_00424480
    L_00422b62:
        mov ecx,dword ptr [data_0047770c]
    L_00422b68:
        mov edi,dword ptr [ecx+9EC8h]
    L_00422b6e:
        mov dword ptr [ebp+2C4h],edi
    L_00422b74:
        call asm_FUN_00449950_00449950
    L_00422b79:
        mov ebx,eax
    L_00422b7b:
        mov edx,dword ptr [ebx+35Ch]
    L_00422b81:
        push 79h
    L_00422b83:
        or edx,40000000h
    L_00422b89:
        push ebx
    L_00422b8a:
        mov ecx,edi
    L_00422b8c:
        mov dword ptr [ebx+20h],0Fh
    L_00422b93:
        mov dword ptr [ebx+35Ch],edx
    L_00422b99:
        call asm_FUN_00449870_00449870
    L_00422b9e:
        mov edx,dword ptr [data_00491c10]
    L_00422ba4:
        lea eax,[esp+14h]
    L_00422ba8:
        call asm_AnimationManager_RegisterSecondaryBack_00448ac0
    L_00422bad:
        mov edx,dword ptr [esp+14h]
    L_00422bb1:
        lea esi,[ebp+1D4h]
    L_00422bb7:
        mov eax,esi
    L_00422bb9:
        mov dword ptr [esi],edx
    L_00422bbb:
        call asm_AnimationManager_StopAtFrame3_0040c4d0
    L_00422bc0:
        push 0
    L_00422bc2:
        mov edi,20h
    L_00422bc7:
        mov ecx,492590h
    L_00422bcc:
        call asm_AnimationManager_QueueResource_0043dc90
    L_00422bd1:
        push 0
    L_00422bd3:
        push 6
    L_00422bd5:
        mov edx,46E0C0h
    L_00422bda:
        mov eax,ecx
    L_00422bdc:
        call asm_AnimationManager_RegisterResource_0043e460
    L_00422be1:
        mov eax,dword ptr [data_00477810]
    L_00422be6:
        mov ecx,dword ptr [eax+5Ch]
    L_00422be9:
        test ecx,ecx
    L_00422beb:
        je short L_00422c11
    L_00422bed:
        mov ebx,75h
    L_00422bf2:
        lea edi,[esp+14h]
    L_00422bf6:
        call asm_AnimationManager_FindChildByScriptIndex_004497d0
    L_00422bfb:
        mov edx,dword ptr [data_00491c10]
    L_00422c01:
        mov esi,eax
    L_00422c03:
        mov ecx,dword ptr [esi]
    L_00422c05:
        push ecx
    L_00422c06:
        call asm_AnimationManager_SetFlag_004492a0
    L_00422c0b:
        mov dword ptr [esi],0
    L_00422c11:
        mov edx,dword ptr [data_00476f78]
    L_00422c17:
        pop edi
    L_00422c18:
        pop esi
    L_00422c19:
        mov dword ptr [ebp+2C0h],edx
    L_00422c1f:
        pop ebp
    L_00422c20:
        mov dword ptr [data_00476f78],3F800000h
    L_00422c2a:
        pop ebx
    L_00422c2b:
        ret 4
    }
}

// 0x00422C80..0x004231B9: FUN_00422c80
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00422c80_00422c80() {
    __asm {
    L_00422c80:
        sub esp,14h
    L_00422c83:
        push ebp
    L_00422c84:
        mov ebp,dword ptr [esp+1Ch]
    L_00422c88:
        mov eax,dword ptr [ebp+4]
    L_00422c8b:
        dec eax
    L_00422c8c:
        cmp eax,4
    L_00422c8f:
        ja asm_target_004231b3
    L_00422c95:
        push ebx
    L_00422c96:
        push esi
    L_00422c97:
        push edi
    L_00422c98:
        jmp dword ptr [eax*4+4231BCh]
    L_00422c9f:
        cmp dword ptr [ebp+14h],0Ah
    L_00422ca3:
        jl asm_target_004231b0
    L_00422ca9:
        mov eax,dword ptr [data_00477810]
    L_00422cae:
        mov dword ptr [ebp+4],2
    L_00422cb5:
        mov ecx,dword ptr [eax+5Ch]
    L_00422cb8:
        neg ecx
    L_00422cba:
        sbb ecx,ecx
    L_00422cbc:
        add ecx,3
    L_00422cbf:
        mov eax,ecx
    L_00422cc1:
        test eax,eax
    L_00422cc3:
        mov dword ptr [ebp+2Ch],ecx
    L_00422cc6:
        mov dword ptr [ebp+0F4h],1
    L_00422cd0:
        je short L_00422ce1
    L_00422cd2:
        jg short L_00422cda
    L_00422cd4:
        dec eax
    L_00422cd5:
        mov dword ptr [ebp+24h],eax
    L_00422cd8:
        jmp short L_00422ce8
    L_00422cda:
        xor eax,eax
    L_00422cdc:
        mov dword ptr [ebp+24h],eax
    L_00422cdf:
        jmp short L_00422ce8
    L_00422ce1:
        mov dword ptr [ebp+24h],0
    L_00422ce8:
        xor esi,esi
    L_00422cea:
        mov si,word ptr [ebp+24h]
    L_00422cee:
        add si,7
    L_00422cf2:
        lea eax,[ebp+1D4h]
    L_00422cf8:
        call asm_AnimationManager_SetStopFrameFromHandleRetail_00449470
    L_00422cfd:
        pop edi
    L_00422cfe:
        pop esi
    L_00422cff:
        pop ebx
    L_00422d00:
        pop ebp
    L_00422d01:
        add esp,14h
    L_00422d04:
        ret 4
    L_00422d07:
        mov edx,dword ptr [ebp+24h]
    L_00422d0a:
        lea ebx,[ebp+24h]
    L_00422d0d:
        mov dword ptr [ebx+4],edx
    L_00422d10:
        mov cl,byte ptr [data_00474e36]
    L_00422d16:
        mov al,10h
    L_00422d18:
        test cl,al
    L_00422d1a:
        jne short L_00422d24
    L_00422d1c:
        test byte ptr [data_00474e34],al
    L_00422d22:
        je short L_00422d2d
    L_00422d24:
        push 0FFFFFFFFh
    L_00422d26:
        mov eax,ebx
    L_00422d28:
        call asm_MenuCursor_Advance_0044bea0
    L_00422d2d:
        mov cl,byte ptr [data_00474e36]
    L_00422d33:
        mov al,20h
    L_00422d35:
        test cl,al
    L_00422d37:
        jne short L_00422d41
    L_00422d39:
        test byte ptr [data_00474e34],al
    L_00422d3f:
        je short L_00422d4a
    L_00422d41:
        push 1
    L_00422d43:
        mov eax,ebx
    L_00422d45:
        call asm_MenuCursor_Advance_0044bea0
    L_00422d4a:
        mov eax,dword ptr [ebx+4]
    L_00422d4d:
        mov ecx,dword ptr [ebx]
    L_00422d4f:
        cmp eax,ecx
    L_00422d51:
        je short L_00422d78
    L_00422d53:
        xor esi,esi
    L_00422d55:
        mov si,cx
    L_00422d58:
        add si,7
    L_00422d5c:
        lea eax,[ebp+1D4h]
    L_00422d62:
        call asm_AnimationManager_SetStopFrameFromHandleRetail_00449470
    L_00422d67:
        push 0
    L_00422d69:
        mov edi,0Ch
    L_00422d6e:
        mov ecx,492590h
    L_00422d73:
        call asm_AnimationManager_QueueResource_0043dc90
    L_00422d78:
        test dword ptr [data_00474e36],1001h
    L_00422d82:
        je asm_target_00422e28
    L_00422d88:
        push 0
    L_00422d8a:
        mov edi,0Ah
    L_00422d8f:
        mov ecx,492590h
    L_00422d94:
        call asm_AnimationManager_QueueResource_0043dc90
    L_00422d99:
        mov ebx,dword ptr [ebx]
    L_00422d9b:
        sub ebx,0
    L_00422d9e:
        je short L_00422df6
    L_00422da0:
        dec ebx
    L_00422da1:
        je short L_00422dc8
    L_00422da3:
        dec ebx
    L_00422da4:
        jne short L_00422e1e
    L_00422da6:
        lea esi,[ebp+1D4h]
    L_00422dac:
        mov ebx,75h
    L_00422db1:
        lea edi,[esp+28h]
    L_00422db5:
        call asm_AnimationManager_FindChildByScriptIndex_004497d0
    L_00422dba:
        call asm_Recovery_MarkAnimationTree_004243f0
    L_00422dbf:
        mov dword ptr [ebp+4],4
    L_00422dc6:
        jmp short L_00422e1e
    L_00422dc8:
        lea esi,[ebp+1D4h]
    L_00422dce:
        mov ebx,74h
    L_00422dd3:
        lea edi,[esp+10h]
    L_00422dd7:
        call asm_AnimationManager_FindChildByScriptIndex_004497d0
    L_00422ddc:
        call asm_Recovery_MarkAnimationTree_004243f0
    L_00422de1:
        mov ecx,dword ptr [data_00477810]
    L_00422de7:
        mov edx,dword ptr [ecx+5Ch]
    L_00422dea:
        neg edx
    L_00422dec:
        sbb edx,edx
    L_00422dee:
        add edx,4
    L_00422df1:
        mov dword ptr [ebp+4],edx
    L_00422df4:
        jmp short L_00422e1e
    L_00422df6:
        lea eax,[ebp+1D8h]
    L_00422dfc:
        call asm_FUN_00409e50_00409e50
    L_00422e01:
        lea eax,[ebp+1D4h]
    L_00422e07:
        call asm_FUN_00409e50_00409e50
    L_00422e0c:
        lea eax,[ebp+1DCh]
    L_00422e12:
        call asm_FUN_00409e50_00409e50
    L_00422e17:
        mov dword ptr [ebp+4],3
    L_00422e1e:
        push 0
    L_00422e20:
        lea eax,[ebp+10h]
    L_00422e23:
        call asm_Player_SetSchedulerValue_00405410
    L_00422e28:
        mov eax,dword ptr [data_00474e36]
    L_00422e2d:
        test ah,40h
    L_00422e30:
        je short L_00422e9b
    L_00422e32:
        push 0
    L_00422e34:
        mov edi,0Ah
    L_00422e39:
        mov ecx,492590h
    L_00422e3e:
        call asm_AnimationManager_QueueResource_0043dc90
    L_00422e43:
        lea esi,[ebp+1D4h]
    L_00422e49:
        mov ebx,75h
    L_00422e4e:
        lea edi,[esp+14h]
    L_00422e52:
        call asm_AnimationManager_FindChildByScriptIndex_004497d0
    L_00422e57:
        call asm_Recovery_MarkAnimationTree_004243f0
    L_00422e5c:
        push 0
    L_00422e5e:
        lea eax,[ebp+10h]
    L_00422e61:
        mov dword ptr [ebp+4],3
    L_00422e68:
        call asm_Player_SetSchedulerValue_00405410
    L_00422e6d:
        mov eax,dword ptr [ebp+2Ch]
    L_00422e70:
        test eax,eax
    L_00422e72:
        je short L_00422e89
    L_00422e74:
        cmp eax,2
    L_00422e77:
        jg short L_00422e7f
    L_00422e79:
        dec eax
    L_00422e7a:
        mov dword ptr [ebp+24h],eax
    L_00422e7d:
        jmp short L_00422e90
    L_00422e7f:
        mov eax,2
    L_00422e84:
        mov dword ptr [ebp+24h],eax
    L_00422e87:
        jmp short L_00422e90
    L_00422e89:
        mov dword ptr [ebp+24h],2
    L_00422e90:
        lea eax,[ebp+1D8h]
    L_00422e96:
        call asm_FUN_00409e50_00409e50
    L_00422e9b:
        mov eax,dword ptr [data_00474e36]
    L_00422ea0:
        test ah,2
    L_00422ea3:
        je asm_target_00423059
    L_00422ea9:
        push 0
    L_00422eab:
        mov edi,0Ah
    L_00422eb0:
        mov ecx,492590h
    L_00422eb5:
        call asm_AnimationManager_QueueResource_0043dc90
    L_00422eba:
        lea esi,[ebp+1D4h]
    L_00422ec0:
        mov ebx,74h
    L_00422ec5:
        lea edi,[esp+18h]
    L_00422ec9:
        call asm_AnimationManager_FindChildByScriptIndex_004497d0
    L_00422ece:
        call asm_Recovery_MarkAnimationTree_004243f0
    L_00422ed3:
        push 0
    L_00422ed5:
        lea eax,[ebp+10h]
    L_00422ed8:
        mov dword ptr [ebp+4],3
    L_00422edf:
        call asm_Player_SetSchedulerValue_00405410
    L_00422ee4:
        mov eax,dword ptr [ebp+2Ch]
    L_00422ee7:
        test eax,eax
    L_00422ee9:
        je short L_00422f06
    L_00422eeb:
        cmp eax,1
    L_00422eee:
        jg short L_00422ef9
    L_00422ef0:
        dec eax
    L_00422ef1:
        mov dword ptr [ebp+24h],eax
    L_00422ef4:
        jmp asm_target_00423059
    L_00422ef9:
        mov eax,1
    L_00422efe:
        mov dword ptr [ebp+24h],eax
    L_00422f01:
        jmp asm_target_00423059
    L_00422f06:
        mov dword ptr [ebp+24h],1
    L_00422f0d:
        jmp asm_target_00423059
    L_00422f12:
        mov eax,dword ptr [ebp+14h]
    L_00422f15:
        cmp eax,14h
    L_00422f18:
        jl asm_target_004231b0
    L_00422f1e:
        jne short L_00422f69
    L_00422f20:
        lea eax,[ebp+24h]
    L_00422f23:
        call asm_Score_InputHistorySave_0044be20
    L_00422f28:
        mov dword ptr [ebp+2Ch],2
    L_00422f2f:
        mov dword ptr [ebp+0F4h],1
    L_00422f39:
        mov ecx,dword ptr [eax+8]
    L_00422f3c:
        test ecx,ecx
    L_00422f3e:
        je short L_00422f53
    L_00422f40:
        cmp ecx,1
    L_00422f43:
        jg short L_00422f4a
    L_00422f45:
        dec ecx
    L_00422f46:
        mov dword ptr [eax],ecx
    L_00422f48:
        jmp short L_00422f59
    L_00422f4a:
        mov ecx,1
    L_00422f4f:
        mov dword ptr [eax],ecx
    L_00422f51:
        jmp short L_00422f59
    L_00422f53:
        mov dword ptr [eax],1
    L_00422f59:
        lea eax,[ebp+1D4h]
    L_00422f5f:
        mov esi,0Eh
    L_00422f64:
        call asm_AnimationManager_SetStopFrameFromHandleRetail_00449470
    L_00422f69:
        mov eax,dword ptr [ebp+14h]
    L_00422f6c:
        cmp eax,1Eh
    L_00422f6f:
        jl asm_target_004231b0
    L_00422f75:
        jne short L_00422f8c
    L_00422f77:
        xor esi,esi
    L_00422f79:
        mov si,word ptr [ebp+24h]
    L_00422f7d:
        add si,0Fh
    L_00422f81:
        lea eax,[ebp+1D4h]
    L_00422f87:
        call asm_AnimationManager_SetStopFrameFromHandleRetail_00449470
    L_00422f8c:
        mov eax,dword ptr [ebp+24h]
    L_00422f8f:
        lea ebx,[ebp+24h]
    L_00422f92:
        mov dword ptr [ebx+4],eax
    L_00422f95:
        mov eax,10h
    L_00422f9a:
        mov ecx,474E30h
    L_00422f9f:
        call asm_InputMaskActive_0040ace0
    L_00422fa4:
        test ax,ax
    L_00422fa7:
        je short L_00422fb2
    L_00422fa9:
        push 0FFFFFFFFh
    L_00422fab:
        mov eax,ebx
    L_00422fad:
        call asm_MenuCursor_Advance_0044bea0
    L_00422fb2:
        mov eax,20h
    L_00422fb7:
        mov ecx,474E30h
    L_00422fbc:
        call asm_InputMaskActive_0040ace0
    L_00422fc1:
        test ax,ax
    L_00422fc4:
        je short L_00422fcf
    L_00422fc6:
        push 1
    L_00422fc8:
        mov eax,ebx
    L_00422fca:
        call asm_MenuCursor_Advance_0044bea0
    L_00422fcf:
        mov ecx,dword ptr [ebx+4]
    L_00422fd2:
        mov eax,dword ptr [ebx]
    L_00422fd4:
        cmp ecx,eax
    L_00422fd6:
        je short L_00422ffd
    L_00422fd8:
        xor esi,esi
    L_00422fda:
        mov si,ax
    L_00422fdd:
        add si,0Fh
    L_00422fe1:
        lea eax,[ebp+1D4h]
    L_00422fe7:
        call asm_AnimationManager_SetStopFrameFromHandleRetail_00449470
    L_00422fec:
        push 0
    L_00422fee:
        mov edi,0Ch
    L_00422ff3:
        mov ecx,492590h
    L_00422ff8:
        call asm_AnimationManager_QueueResource_0043dc90
    L_00422ffd:
        test dword ptr [data_00474e36],1001h
    L_00423007:
        je short L_00423059
    L_00423009:
        push 0
    L_0042300b:
        mov edi,0Ah
    L_00423010:
        mov ecx,492590h
    L_00423015:
        call asm_AnimationManager_QueueResource_0043dc90
    L_0042301a:
        mov ebx,dword ptr [ebx]
    L_0042301c:
        sub ebx,0
    L_0042301f:
        je short L_0042302f
    L_00423021:
        dec ebx
    L_00423022:
        jne short L_0042304f
    L_00423024:
        mov ebx,78h
    L_00423029:
        lea edi,[esp+1Ch]
    L_0042302d:
        jmp short L_00423038
    L_0042302f:
        mov ebx,77h
    L_00423034:
        lea edi,[esp+20h]
    L_00423038:
        lea esi,[ebp+1D4h]
    L_0042303e:
        call asm_AnimationManager_FindChildByScriptIndex_004497d0
    L_00423043:
        call asm_Recovery_MarkAnimationTree_004243f0
    L_00423048:
        mov dword ptr [ebp+4],5
    L_0042304f:
        push 0
    L_00423051:
        lea eax,[ebp+10h]
    L_00423054:
        call asm_Player_SetSchedulerValue_00405410
    L_00423059:
        test byte ptr [data_00474e36],8
    L_00423060:
        je asm_target_004231b0
    L_00423066:
        mov eax,dword ptr [ebp+2Ch]
    L_00423069:
        test eax,eax
    L_0042306b:
        je short L_0042307c
    L_0042306d:
        jg short L_00423075
    L_0042306f:
        dec eax
    L_00423070:
        mov dword ptr [ebp+24h],eax
    L_00423073:
        jmp short L_00423083
    L_00423075:
        xor eax,eax
    L_00423077:
        mov dword ptr [ebp+24h],eax
    L_0042307a:
        jmp short L_00423083
    L_0042307c:
        mov dword ptr [ebp+24h],0
    L_00423083:
        lea eax,[ebp+1D8h]
    L_00423089:
        call asm_FUN_00409e50_00409e50
    L_0042308e:
        lea eax,[ebp+1D4h]
    L_00423094:
        call asm_FUN_00409e50_00409e50
    L_00423099:
        lea eax,[ebp+1DCh]
    L_0042309f:
        call asm_FUN_00409e50_00409e50
    L_004230a4:
        push 0
    L_004230a6:
        lea eax,[ebp+10h]
    L_004230a9:
        mov dword ptr [ebp+4],3
    L_004230b0:
        call asm_Player_SetSchedulerValue_00405410
    L_004230b5:
        pop edi
    L_004230b6:
        pop esi
    L_004230b7:
        pop ebx
    L_004230b8:
        pop ebp
    L_004230b9:
        add esp,14h
    L_004230bc:
        ret 4
    L_004230bf:
        cmp dword ptr [ebp+14h],14h
    L_004230c3:
        jl asm_target_004231b0
    L_004230c9:
        mov eax,dword ptr [ebp+24h]
    L_004230cc:
        sub eax,0
    L_004230cf:
        lea esi,[ebp+24h]
    L_004230d2:
        je short L_0042310b
    L_004230d4:
        dec eax
    L_004230d5:
        jne short L_0042312f
    L_004230d7:
        mov eax,esi
    L_004230d9:
        call asm_Score_InputHistoryStep_0044be70
    L_004230de:
        movsx esi,word ptr [esi]
    L_004230e1:
        add si,7
    L_004230e5:
        lea eax,[ebp+1D4h]
    L_004230eb:
        call asm_AnimationManager_SetStopFrameFromHandleRetail_00449470
    L_004230f0:
        push 0
    L_004230f2:
        lea eax,[ebp+10h]
    L_004230f5:
        mov dword ptr [ebp+4],2
    L_004230fc:
        call asm_Player_SetSchedulerValue_00405410
    L_00423101:
        pop edi
    L_00423102:
        pop esi
    L_00423103:
        pop ebx
    L_00423104:
        pop ebp
    L_00423105:
        add esp,14h
    L_00423108:
        ret 4
    L_0042310b:
        lea eax,[ebp+1D8h]
    L_00423111:
        call asm_FUN_00409e50_00409e50
    L_00423116:
        lea eax,[ebp+1D4h]
    L_0042311c:
        call asm_FUN_00409e50_00409e50
    L_00423121:
        mov eax,esi
    L_00423123:
        mov dword ptr [ebp+4],3
    L_0042312a:
        call asm_Score_InputHistoryStep_0044be70
    L_0042312f:
        push 0
    L_00423131:
        lea eax,[ebp+10h]
    L_00423134:
        call asm_Player_SetSchedulerValue_00405410
    L_00423139:
        pop edi
    L_0042313a:
        pop esi
    L_0042313b:
        pop ebx
    L_0042313c:
        pop ebp
    L_0042313d:
        add esp,14h
    L_00423140:
        ret 4
    L_00423143:
        cmp dword ptr [ebp+14h],0Ch
    L_00423147:
        jl short L_004231b0
    L_00423149:
        mov eax,dword ptr [ebp+24h]
    L_0042314c:
        sub eax,0
    L_0042314f:
        mov dword ptr [ebp+4],0
    L_00423156:
        je short L_004231a9
    L_00423158:
        dec eax
    L_00423159:
        je short L_0042317d
    L_0042315b:
        dec eax
    L_0042315c:
        jne short L_004231b0
    L_0042315e:
        lea eax,[ebp+1D4h]
    L_00423164:
        call asm_FUN_00409e50_00409e50
    L_00423169:
        pop edi
    L_0042316a:
        pop esi
    L_0042316b:
        pop ebx
    L_0042316c:
        mov dword ptr [data_00491fb8],0Ah
    L_00423176:
        pop ebp
    L_00423177:
        add esp,14h
    L_0042317a:
        ret 4
    L_0042317d:
        lea eax,[ebp+1D8h]
    L_00423183:
        call asm_FUN_00409e50_00409e50
    L_00423188:
        lea eax,[ebp+1D4h]
    L_0042318e:
        call asm_FUN_00409e50_00409e50
    L_00423193:
        push 4
    L_00423195:
        mov eax,491C28h
    L_0042319a:
        call asm_SetInputMode_0040ac90
    L_0042319f:
        pop edi
    L_004231a0:
        pop esi
    L_004231a1:
        pop ebx
    L_004231a2:
        pop ebp
    L_004231a3:
        add esp,14h
    L_004231a6:
        ret 4
    L_004231a9:
        mov esi,ebp
    L_004231ab:
        call asm_GameState_Unpause_00422c30
    L_004231b0:
        pop edi
    L_004231b1:
        pop esi
    L_004231b2:
        pop ebx
    L_004231b3:
        pop ebp
    L_004231b4:
        add esp,14h
    L_004231b7:
        ret 4
    }
}

// 0x004236F0..0x0042438A: FUN_004236f0
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_004236f0_004236f0() {
    __asm {
    L_004236f0:
        sub esp,4Ch
    L_004236f3:
        mov eax,dword ptr [data_00473660]
    L_004236f8:
        xor eax,esp
    L_004236fa:
        push ebp
    L_004236fb:
        mov ebp,dword ptr [esp+54h]
    L_004236ff:
        mov dword ptr [esp+4Ch],eax
    L_00423703:
        mov eax,dword ptr [ebp+4]
    L_00423706:
        add eax,0FFFFFFFAh
    L_00423709:
        cmp eax,7
    L_0042370c:
        ja asm_target_00424379
    L_00423712:
        push ebx
    L_00423713:
        push esi
    L_00423714:
        push edi
    L_00423715:
        jmp dword ptr [eax*4+42438Ch]
    L_0042371c:
        mov eax,dword ptr [ebp+14h]
    L_0042371f:
        mov edi,0Ah
    L_00423724:
        cmp eax,edi
    L_00423726:
        jl asm_target_00424376
    L_0042372c:
        test dword ptr [data_00474e36],1001h
    L_00423736:
        je asm_target_00424376
    L_0042373c:
        push 0
    L_0042373e:
        mov ecx,492590h
    L_00423743:
        call asm_AnimationManager_QueueResource_0043dc90
    L_00423748:
        lea eax,[ebp+1D4h]
    L_0042374e:
        mov esi,2
    L_00423753:
        mov dword ptr [ebp+4],7
    L_0042375a:
        call asm_AnimationManager_SetStopFrameFromHandleRetail_00449470
    L_0042375f:
        push 0
    L_00423761:
        lea eax,[ebp+10h]
    L_00423764:
        call asm_Player_SetSchedulerValue_00405410
    L_00423769:
        pop edi
    L_0042376a:
        pop esi
    L_0042376b:
        pop ebx
    L_0042376c:
        pop ebp
    L_0042376d:
        mov ecx,dword ptr [esp+48h]
    L_00423771:
        xor ecx,esp
    L_00423773:
        call asm_security_check_cookie_00458ea5
    L_00423778:
        add esp,4Ch
    L_0042377b:
        ret 4
    L_0042377e:
        cmp dword ptr [ebp+14h],0Ah
    L_00423782:
        jl asm_target_00424376
    L_00423788:
        mov eax,dword ptr [data_0047770c]
    L_0042378d:
        call asm_GameState_UpdateFrameMaximum_00421f60
    L_00423792:
        test byte ptr [data_00474ca0],10h
    L_00423799:
        je asm_target_00423849
    L_0042379f:
        mov eax,dword ptr [data_00474c68]
    L_004237a4:
        mov ecx,dword ptr [data_00474c6c]
    L_004237aa:
        mov esi,dword ptr [data_0047783c]
    L_004237b0:
        lea edx,[ecx+eax*2]
    L_004237b3:
        mov ecx,dword ptr [data_00474c7c]
    L_004237b9:
        add edx,eax
    L_004237bb:
        mov eax,dword ptr [data_00474c74]
    L_004237c0:
        imul edx,437Ch
    L_004237c6:
        lea eax,[eax+eax*2]
    L_004237c9:
        add edx,esi
    L_004237cb:
        lea eax,[ecx+eax*2]
    L_004237ce:
        mov ecx,dword ptr [data_00474c44]
    L_004237d4:
        lea eax,[edx+eax*8+4DCh]
    L_004237db:
        cmp ecx,dword ptr [eax]
    L_004237dd:
        jle short L_004237e1
    L_004237df:
        mov dword ptr [eax],ecx
    L_004237e1:
        mov dword ptr [ebp+4],8
    L_004237e8:
        mov dword ptr [ebp+2Ch],3
    L_004237ef:
        mov dword ptr [ebp+0F4h],1
    L_004237f9:
        mov eax,dword ptr [ebp+2Ch]
    L_004237fc:
        test eax,eax
    L_004237fe:
        je short L_0042380f
    L_00423800:
        cmp eax,2
    L_00423803:
        jg asm_target_0042388e
    L_00423809:
        dec eax
    L_0042380a:
        mov dword ptr [ebp+24h],eax
    L_0042380d:
        jmp short L_00423816
    L_0042380f:
        mov dword ptr [ebp+24h],2
    L_00423816:
        lea edi,[ebp+1D4h]
    L_0042381c:
        mov eax,edi
    L_0042381e:
        call asm_AnimationManager_StopAtFrame3_0040c4d0
    L_00423823:
        xor esi,esi
    L_00423825:
        mov si,word ptr [ebp+24h]
    L_00423829:
        add si,7
    L_0042382d:
        mov eax,edi
    L_0042382f:
        call asm_AnimationManager_SetStopFrameFromHandleRetail_00449470
    L_00423834:
        pop edi
    L_00423835:
        pop esi
    L_00423836:
        pop ebx
    L_00423837:
        pop ebp
    L_00423838:
        mov ecx,dword ptr [esp+48h]
    L_0042383c:
        xor ecx,esp
    L_0042383e:
        call asm_security_check_cookie_00458ea5
    L_00423843:
        add esp,4Ch
    L_00423846:
        ret 4
    L_00423849:
        push ebp
    L_0042384a:
        call asm_FUN_00423570_00423570
    L_0042384f:
        push 0
    L_00423851:
        lea eax,[ebp+10h]
    L_00423854:
        call asm_Player_SetSchedulerValue_00405410
    L_00423859:
        mov eax,dword ptr [ebp+1E8h]
    L_0042385f:
        test eax,eax
    L_00423861:
        jne asm_target_004237e1
    L_00423867:
        lea eax,[ebp+1D4h]
    L_0042386d:
        mov dword ptr [ebp+4],0Ch
    L_00423874:
        call asm_AnimationManager_ClearFlag_004495e0
    L_00423879:
        pop edi
    L_0042387a:
        pop esi
    L_0042387b:
        pop ebx
    L_0042387c:
        pop ebp
    L_0042387d:
        mov ecx,dword ptr [esp+48h]
    L_00423881:
        xor ecx,esp
    L_00423883:
        call asm_security_check_cookie_00458ea5
    L_00423888:
        add esp,4Ch
    L_0042388b:
        ret 4
    L_0042388e:
        mov eax,2
    L_00423893:
        mov dword ptr [ebp+24h],eax
    L_00423896:
        jmp asm_target_00423816
    L_0042389b:
        mov ecx,dword ptr [ebp+24h]
    L_0042389e:
        lea esi,[ebp+24h]
    L_004238a1:
        mov dword ptr [esi+4],ecx
    L_004238a4:
        test byte ptr [data_00474e36],10h
    L_004238ab:
        jne short L_004238b6
    L_004238ad:
        test byte ptr [data_00474e34],10h
    L_004238b4:
        je short L_004238bf
    L_004238b6:
        push 0FFFFFFFFh
    L_004238b8:
        mov eax,esi
    L_004238ba:
        call asm_MenuCursor_Advance_0044bea0
    L_004238bf:
        test byte ptr [data_00474e36],20h
    L_004238c6:
        jne short L_004238d1
    L_004238c8:
        test byte ptr [data_00474e34],20h
    L_004238cf:
        je short L_004238da
    L_004238d1:
        push 1
    L_004238d3:
        mov eax,esi
    L_004238d5:
        call asm_MenuCursor_Advance_0044bea0
    L_004238da:
        mov edx,dword ptr [esi+4]
    L_004238dd:
        mov eax,dword ptr [esi]
    L_004238df:
        cmp edx,eax
    L_004238e1:
        je short L_00423906
    L_004238e3:
        movsx esi,ax
    L_004238e6:
        add si,7
    L_004238ea:
        lea eax,[ebp+1D4h]
    L_004238f0:
        call asm_AnimationManager_SetStopFrameFromHandleRetail_00449470
    L_004238f5:
        push 0
    L_004238f7:
        mov edi,0Ch
    L_004238fc:
        mov ecx,492590h
    L_00423901:
        call asm_AnimationManager_QueueResource_0043dc90
    L_00423906:
        test dword ptr [data_00474e36],1001h
    L_00423910:
        je asm_target_00423a0a
    L_00423916:
        mov eax,dword ptr [ebp+24h]
    L_00423919:
        lea esi,[ebp+1D4h]
    L_0042391f:
        lea ebx,[eax+7Ch]
    L_00423922:
        lea edi,[esp+14h]
    L_00423926:
        call asm_AnimationManager_FindChildByScriptIndex_004497d0
    L_0042392b:
        call asm_Recovery_MarkAnimationTree_004243f0
    L_00423930:
        push 0
    L_00423932:
        mov edi,0Ah
    L_00423937:
        mov ecx,492590h
    L_0042393c:
        call asm_AnimationManager_QueueResource_0043dc90
    L_00423941:
        lea edi,[ebp+10h]
    L_00423944:
        push 0
    L_00423946:
        mov eax,edi
    L_00423948:
        mov dword ptr [ebp+4],0Dh
    L_0042394f:
        call asm_Player_SetSchedulerValue_00405410
    L_00423954:
        mov eax,dword ptr [data_0047770c]
    L_00423959:
        call asm_GameState_UpdateFrameMaximum_00421f60
    L_0042395e:
        mov eax,dword ptr [ebp+24h]
    L_00423961:
        dec eax
    L_00423962:
        je short L_00423991
    L_00423964:
        dec eax
    L_00423965:
        jne asm_target_00423a0a
    L_0042396b:
        push 0
    L_0042396d:
        mov eax,edi
    L_0042396f:
        mov dword ptr [ebp+4],0Dh
    L_00423976:
        call asm_Player_SetSchedulerValue_00405410
    L_0042397b:
        push 0
    L_0042397d:
        mov edi,0Ah
    L_00423982:
        mov ecx,492590h
    L_00423987:
        call asm_AnimationManager_QueueResource_0043dc90
    L_0042398c:
        jmp asm_target_00423a0a
    L_00423991:
        push 0
    L_00423993:
        mov eax,edi
    L_00423995:
        mov dword ptr [ebp+4],0Ah
    L_0042399c:
        call asm_Player_SetSchedulerValue_00405410
    L_004239a1:
        mov eax,esi
    L_004239a3:
        call asm_AnimationManager_ClearFlag_004495e0
    L_004239a8:
        lea eax,[ebp+24h]
    L_004239ab:
        call asm_Score_InputHistorySave_0044be20
    L_004239b0:
        mov esi,1
    L_004239b5:
        mov dword ptr [ebp+2Ch],19h
    L_004239bc:
        mov dword ptr [ebp+0F4h],esi
    L_004239c2:
        mov ecx,dword ptr [eax+8]
    L_004239c5:
        test ecx,ecx
    L_004239c7:
        je short L_004239d6
    L_004239c9:
        jg short L_004239d0
    L_004239cb:
        dec ecx
    L_004239cc:
        mov dword ptr [eax],ecx
    L_004239ce:
        jmp short L_004239dc
    L_004239d0:
        xor ecx,ecx
    L_004239d2:
        mov dword ptr [eax],ecx
    L_004239d4:
        jmp short L_004239dc
    L_004239d6:
        mov dword ptr [eax],0
    L_004239dc:
        lea edi,[ebp+1ECh]
    L_004239e2:
        push esi
    L_004239e3:
        lea eax,[esp+1Ch]
    L_004239e7:
        push 46E0C8h
    L_004239ec:
        push eax
    L_004239ed:
        call asm_sprintf_00452ae8
    L_004239f2:
        add esp,0Ch
    L_004239f5:
        lea ecx,[esp+18h]
    L_004239f9:
        push ecx
    L_004239fa:
        call asm_StageManager_CreateRetail_004296f0
    L_004239ff:
        mov dword ptr [edi],eax
    L_00423a01:
        inc esi
    L_00423a02:
        add edi,4
    L_00423a05:
        cmp esi,19h
    L_00423a08:
        jle short L_004239e2
    L_00423a0a:
        test byte ptr [data_00474e36],0Ah
    L_00423a11:
        je asm_target_00424376
    L_00423a17:
        push 0
    L_00423a19:
        mov edi,0Bh
    L_00423a1e:
        mov ecx,492590h
    L_00423a23:
        call asm_AnimationManager_QueueResource_0043dc90
    L_00423a28:
        cmp dword ptr [ebp+24h],2
    L_00423a2c:
        je asm_target_00424376
    L_00423a32:
        mov eax,dword ptr [ebp+2Ch]
    L_00423a35:
        test eax,eax
    L_00423a37:
        je short L_00423a4e
    L_00423a39:
        cmp eax,2
    L_00423a3c:
        jg short L_00423a44
    L_00423a3e:
        dec eax
    L_00423a3f:
        mov dword ptr [ebp+24h],eax
    L_00423a42:
        jmp short L_00423a55
    L_00423a44:
        mov eax,2
    L_00423a49:
        mov dword ptr [ebp+24h],eax
    L_00423a4c:
        jmp short L_00423a55
    L_00423a4e:
        mov dword ptr [ebp+24h],2
    L_00423a55:
        xor esi,esi
    L_00423a57:
        mov si,word ptr [ebp+24h]
    L_00423a5b:
        add si,7
    L_00423a5f:
        lea eax,[ebp+1D4h]
    L_00423a65:
        call asm_AnimationManager_SetStopFrameFromHandleRetail_00449470
    L_00423a6a:
        pop edi
    L_00423a6b:
        pop esi
    L_00423a6c:
        pop ebx
    L_00423a6d:
        pop ebp
    L_00423a6e:
        mov ecx,dword ptr [esp+48h]
    L_00423a72:
        xor ecx,esp
    L_00423a74:
        call asm_security_check_cookie_00458ea5
    L_00423a79:
        add esp,4Ch
    L_00423a7c:
        ret 4
    L_00423a7f:
        cmp dword ptr [ebp+14h],0Ah
    L_00423a83:
        jl asm_target_00424376
    L_00423a89:
        mov edx,dword ptr [ebp+24h]
    L_00423a8c:
        lea esi,[ebp+24h]
    L_00423a8f:
        mov eax,10h
    L_00423a94:
        mov ecx,474E30h
    L_00423a99:
        mov dword ptr [esi+4],edx
    L_00423a9c:
        call asm_InputMaskActive_0040ace0
    L_00423aa1:
        test ax,ax
    L_00423aa4:
        je short L_00423aaf
    L_00423aa6:
        push 0FFFFFFFFh
    L_00423aa8:
        mov eax,esi
    L_00423aaa:
        call asm_MenuCursor_Advance_0044bea0
    L_00423aaf:
        mov eax,20h
    L_00423ab4:
        mov ecx,474E30h
    L_00423ab9:
        call asm_InputMaskActive_0040ace0
    L_00423abe:
        test ax,ax
    L_00423ac1:
        je short L_00423acc
    L_00423ac3:
        push 1
    L_00423ac5:
        mov eax,esi
    L_00423ac7:
        call asm_MenuCursor_Advance_0044bea0
    L_00423acc:
        mov eax,dword ptr [esi+4]
    L_00423acf:
        cmp eax,dword ptr [esi]
    L_00423ad1:
        je short L_00423ae4
    L_00423ad3:
        push 0
    L_00423ad5:
        mov edi,0Ch
    L_00423ada:
        mov ecx,492590h
    L_00423adf:
        call asm_AnimationManager_QueueResource_0043dc90
    L_00423ae4:
        mov eax,dword ptr [data_00474e36]
    L_00423ae9:
        test eax,1001h
    L_00423aee:
        je asm_target_00423c20
    L_00423af4:
        push 0
    L_00423af6:
        lea eax,[ebp+10h]
    L_00423af9:
        mov dword ptr [ebp+4],0Bh
    L_00423b00:
        call asm_Player_SetSchedulerValue_00405410
    L_00423b05:
        mov eax,dword ptr [ebp+104h]
    L_00423b0b:
        test eax,eax
    L_00423b0d:
        lea ebx,[ebp+0FCh]
    L_00423b13:
        je short L_00423b22
    L_00423b15:
        jg short L_00423b1c
    L_00423b17:
        dec eax
    L_00423b18:
        mov dword ptr [ebx],eax
    L_00423b1a:
        jmp short L_00423b28
    L_00423b1c:
        xor eax,eax
    L_00423b1e:
        mov dword ptr [ebx],eax
    L_00423b20:
        jmp short L_00423b28
    L_00423b22:
        mov dword ptr [ebx],0
    L_00423b28:
        mov eax,dword ptr [data_004746d8]
    L_00423b2d:
        lea edx,[eax+1]
    L_00423b30:
        mov cl,byte ptr [eax]
    L_00423b32:
        inc eax
    L_00423b33:
        test cl,cl
    L_00423b35:
        jne short L_00423b30
    L_00423b37:
        sub eax,edx
    L_00423b39:
        mov dword ptr [ebp+104h],eax
    L_00423b3f:
        mov eax,dword ptr [ebp+1E4h]
    L_00423b45:
        test eax,eax
    L_00423b47:
        mov dword ptr [ebp+1CCh],1
    L_00423b51:
        je short L_00423b7c
    L_00423b53:
        test byte ptr [data_00474ca0],10h
    L_00423b5a:
        jne short L_00423b7c
    L_00423b5c:
        mov esi,dword ptr [data_00477838]
    L_00423b62:
        mov ecx,dword ptr [esi+18h]
    L_00423b65:
        add esi,18h
    L_00423b68:
        add ecx,0Ch
    L_00423b6b:
        push ecx
    L_00423b6c:
        call asm_FID_conflict___time32_00452b71
    L_00423b71:
        mov edx,dword ptr [esi]
    L_00423b73:
        mov dword ptr [edx+5Ch],8
    L_00423b7a:
        jmp short L_00423b9c
    L_00423b7c:
        mov esi,dword ptr [data_00477838]
    L_00423b82:
        mov eax,dword ptr [esi+18h]
    L_00423b85:
        add esi,18h
    L_00423b88:
        add eax,0Ch
    L_00423b8b:
        push eax
    L_00423b8c:
        call asm_FID_conflict___time32_00452b71
    L_00423b91:
        mov ecx,dword ptr [esi]
    L_00423b93:
        mov edx,dword ptr [data_00474c7c]
    L_00423b99:
        mov dword ptr [ecx+5Ch],edx
    L_00423b9c:
        mov eax,dword ptr [data_0047783c]
    L_00423ba1:
        lea esi,[ebp+2B4h]
    L_00423ba7:
        add eax,1D878h
    L_00423bac:
        mov edx,esi
    L_00423bae:
        add esp,4
    L_00423bb1:
        sub edx,eax
    L_00423bb3:
        mov cl,byte ptr [eax]
    L_00423bb5:
        mov byte ptr [edx+eax],cl
    L_00423bb8:
        inc eax
    L_00423bb9:
        test cl,cl
    L_00423bbb:
        jne short L_00423bb3
    L_00423bbd:
        mov edi,46E354h
    L_00423bc2:
        mov ecx,9
    L_00423bc7:
        xor eax,eax
    L_00423bc9:
        mov dword ptr [ebp+1E0h],0
    L_00423bd3:
        repe cmpsb
    L_00423bd5:
        je short L_00423be0
    L_00423bd7:
        push 0FFFFFFFFh
    L_00423bd9:
        mov eax,ebx
    L_00423bdb:
        call asm_MenuCursor_Advance_0044bea0
    L_00423be0:
        mov eax,8
    L_00423be5:
        cmp byte ptr [eax+ebp+2B3h],20h
    L_00423bed:
        jne short L_00423bf4
    L_00423bef:
        dec eax
    L_00423bf0:
        test eax,eax
    L_00423bf2:
        jg short L_00423be5
    L_00423bf4:
        mov dword ptr [ebp+1E0h],eax
    L_00423bfa:
        push 0
    L_00423bfc:
        mov edi,0Ah
    L_00423c01:
        mov ecx,492590h
    L_00423c06:
        call asm_AnimationManager_QueueResource_0043dc90
    L_00423c0b:
        pop edi
    L_00423c0c:
        pop esi
    L_00423c0d:
        pop ebx
    L_00423c0e:
        pop ebp
    L_00423c0f:
        mov ecx,dword ptr [esp+48h]
    L_00423c13:
        xor ecx,esp
    L_00423c15:
        call asm_security_check_cookie_00458ea5
    L_00423c1a:
        add esp,4Ch
    L_00423c1d:
        ret 4
    L_00423c20:
        test al,0Ah
    L_00423c22:
        je asm_target_00424376
    L_00423c28:
        lea ebx,[ebp+10h]
    L_00423c2b:
        push 0
    L_00423c2d:
        mov eax,ebx
    L_00423c2f:
        mov dword ptr [ebp+4],8
    L_00423c36:
        call asm_Player_SetSchedulerValue_00405410
    L_00423c3b:
        lea edi,[ebp+1D4h]
    L_00423c41:
        mov eax,edi
    L_00423c43:
        call asm_AnimationManager_SetFlagBit1_00449590
    L_00423c48:
        mov eax,esi
    L_00423c4a:
        call asm_Score_InputHistoryStep_0044be70
    L_00423c4f:
        movsx esi,word ptr [esi]
    L_00423c52:
        add si,7
    L_00423c56:
        mov eax,edi
    L_00423c58:
        mov dword ptr [ebp+2Ch],3
    L_00423c5f:
        mov dword ptr [ebp+0F4h],1
    L_00423c69:
        call asm_AnimationManager_SetStopFrameFromHandleRetail_00449470
    L_00423c6e:
        lea esi,[ebp+1ECh]
    L_00423c74:
        mov dword ptr [esp+10h],19h
    L_00423c7c:
        TH10_NOP_LEA_ESP_DISP8()
    L_00423c80:
        mov edi,dword ptr [esi]
    L_00423c82:
        test edi,edi
    L_00423c84:
        je short L_00423c95
    L_00423c86:
        push edi
    L_00423c87:
        call asm_FUN_004294a0_004294a0
    L_00423c8c:
        push edi
    L_00423c8d:
        call asm_free_004524a1
    L_00423c92:
        add esp,4
    L_00423c95:
        mov eax,dword ptr [esp+10h]
    L_00423c99:
        mov dword ptr [esi],0
    L_00423c9f:
        add esi,4
    L_00423ca2:
        dec eax
    L_00423ca3:
        mov dword ptr [esp+10h],eax
    L_00423ca7:
        jne short L_00423c80
    L_00423ca9:
        push 0
    L_00423cab:
        mov eax,ebx
    L_00423cad:
        mov dword ptr [ebp+4],8
    L_00423cb4:
        call asm_Player_SetSchedulerValue_00405410
    L_00423cb9:
        push 0
    L_00423cbb:
        mov edi,0Bh
    L_00423cc0:
        mov ecx,492590h
    L_00423cc5:
        call asm_AnimationManager_QueueResource_0043dc90
    L_00423cca:
        pop edi
    L_00423ccb:
        pop esi
    L_00423ccc:
        pop ebx
    L_00423ccd:
        pop ebp
    L_00423cce:
        mov ecx,dword ptr [esp+48h]
    L_00423cd2:
        xor ecx,esp
    L_00423cd4:
        call asm_security_check_cookie_00458ea5
    L_00423cd9:
        add esp,4Ch
    L_00423cdc:
        ret 4
    L_00423cdf:
        mov eax,dword ptr [ebp+14h]
    L_00423ce2:
        mov ebx,0Ah
    L_00423ce7:
        cmp eax,ebx
    L_00423ce9:
        jl asm_target_00424376
    L_00423cef:
        mov ecx,dword ptr [ebp+0FCh]
    L_00423cf5:
        lea esi,[ebp+0FCh]
    L_00423cfb:
        mov dword ptr [esi+4],ecx
    L_00423cfe:
        mov eax,10h
    L_00423d03:
        mov ecx,474E30h
    L_00423d08:
        call asm_InputMaskActive_0040ace0
    L_00423d0d:
        test ax,ax
    L_00423d10:
        je short L_00423d1b
    L_00423d12:
        push 0FFFFFFF3h
    L_00423d14:
        mov eax,esi
    L_00423d16:
        call asm_MenuCursor_Advance_0044bea0
    L_00423d1b:
        mov eax,20h
    L_00423d20:
        mov ecx,474E30h
    L_00423d25:
        call asm_InputMaskActive_0040ace0
    L_00423d2a:
        test ax,ax
    L_00423d2d:
        je short L_00423d38
    L_00423d2f:
        push 0Dh
    L_00423d31:
        mov eax,esi
    L_00423d33:
        call asm_MenuCursor_Advance_0044bea0
    L_00423d38:
        mov eax,40h
    L_00423d3d:
        mov ecx,474E30h
    L_00423d42:
        call asm_InputMaskActive_0040ace0
    L_00423d47:
        test ax,ax
    L_00423d4a:
        je short L_00423d67
    L_00423d4c:
        mov eax,dword ptr [esi]
    L_00423d4e:
        cdq
    L_00423d4f:
        mov ecx,0Dh
    L_00423d54:
        idiv ecx
    L_00423d56:
        mov eax,esi
    L_00423d58:
        test edx,edx
    L_00423d5a:
        je short L_00423d60
    L_00423d5c:
        push 0FFFFFFFFh
    L_00423d5e:
        jmp short L_00423d62
    L_00423d60:
        push 0Ch
    L_00423d62:
        call asm_MenuCursor_Advance_0044bea0
    L_00423d67:
        mov eax,80h
    L_00423d6c:
        mov ecx,474E30h
    L_00423d71:
        call asm_InputMaskActive_0040ace0
    L_00423d76:
        test ax,ax
    L_00423d79:
        je short L_00423d97
    L_00423d7b:
        mov eax,dword ptr [esi]
    L_00423d7d:
        cdq
    L_00423d7e:
        mov ecx,0Dh
    L_00423d83:
        idiv ecx
    L_00423d85:
        mov eax,esi
    L_00423d87:
        cmp edx,0Ch
    L_00423d8a:
        je short L_00423d90
    L_00423d8c:
        push 1
    L_00423d8e:
        jmp short L_00423d92
    L_00423d90:
        push 0FFFFFFF4h
    L_00423d92:
        call asm_MenuCursor_Advance_0044bea0
    L_00423d97:
        mov edx,dword ptr [esi+4]
    L_00423d9a:
        cmp edx,dword ptr [esi]
    L_00423d9c:
        je short L_00423daf
    L_00423d9e:
        push 0
    L_00423da0:
        mov edi,0Ch
    L_00423da5:
        mov ecx,492590h
    L_00423daa:
        call asm_AnimationManager_QueueResource_0043dc90
    L_00423daf:
        test dword ptr [data_00474e36],1001h
    L_00423db9:
        je short L_00423e07
    L_00423dbb:
        mov edi,dword ptr [data_004746d8]
    L_00423dc1:
        mov eax,edi
    L_00423dc3:
        lea edx,[eax+1]
    L_00423dc6:
        mov cl,byte ptr [eax]
    L_00423dc8:
        inc eax
    L_00423dc9:
        test cl,cl
    L_00423dcb:
        jne short L_00423dc6
    L_00423dcd:
        mov ecx,dword ptr [esi]
    L_00423dcf:
        sub eax,edx
    L_00423dd1:
        lea edx,[eax-3]
    L_00423dd4:
        cmp ecx,edx
    L_00423dd6:
        jge short L_00423e53
    L_00423dd8:
        mov edx,dword ptr [ebp+1E0h]
    L_00423dde:
        cmp edx,8
    L_00423de1:
        jge short L_00423def
    L_00423de3:
        mov cl,byte ptr [ecx+edi]
    L_00423de6:
        mov byte ptr [edx+ebp+2B4h],cl
    L_00423ded:
        jmp short L_00423e68
    L_00423def:
        mov al,byte ptr [ecx+edi]
    L_00423df2:
        mov byte ptr [edx+ebp+2B3h],al
    L_00423df9:
        push 0
    L_00423dfb:
        mov edi,ebx
    L_00423dfd:
        mov ecx,492590h
    L_00423e02:
        call asm_AnimationManager_QueueResource_0043dc90
    L_00423e07:
        test byte ptr [data_00474e36],bl
    L_00423e0d:
        je asm_target_00424376
    L_00423e13:
        push 0
    L_00423e15:
        mov edi,0Bh
    L_00423e1a:
        mov ecx,492590h
    L_00423e1f:
        call asm_AnimationManager_QueueResource_0043dc90
    L_00423e24:
        mov eax,dword ptr [ebp+1E0h]
    L_00423e2a:
        test eax,eax
    L_00423e2c:
        jne asm_target_00423f6f
    L_00423e32:
        push eax
    L_00423e33:
        lea eax,[ebp+10h]
    L_00423e36:
        mov dword ptr [ebp+4],ebx
    L_00423e39:
        call asm_Player_SetSchedulerValue_00405410
    L_00423e3e:
        pop edi
    L_00423e3f:
        pop esi
    L_00423e40:
        pop ebx
    L_00423e41:
        pop ebp
    L_00423e42:
        mov ecx,dword ptr [esp+48h]
    L_00423e46:
        xor ecx,esp
    L_00423e48:
        call asm_security_check_cookie_00458ea5
    L_00423e4d:
        add esp,4Ch
    L_00423e50:
        ret 4
    L_00423e53:
        jne short L_00423e9c
    L_00423e55:
        mov ecx,dword ptr [ebp+1E0h]
    L_00423e5b:
        cmp ecx,8
    L_00423e5e:
        jge short L_00423e8f
    L_00423e60:
        mov byte ptr [ecx+ebp+2B4h],20h
    L_00423e68:
        mov edx,dword ptr [ebp+1E0h]
    L_00423e6e:
        inc edx
    L_00423e6f:
        mov ecx,edx
    L_00423e71:
        cmp ecx,8
    L_00423e74:
        mov dword ptr [ebp+1E0h],edx
    L_00423e7a:
        jl asm_target_00423df9
    L_00423e80:
        lea ecx,[eax-1]
    L_00423e83:
        mov edx,esi
    L_00423e85:
        call asm_FUN_0040ad20_0040ad20
    L_00423e8a:
        jmp asm_target_00423df9
    L_00423e8f:
        mov byte ptr [ecx+ebp+2B3h],20h
    L_00423e97:
        jmp asm_target_00423df9
    L_00423e9c:
        lea edx,[eax-2]
    L_00423e9f:
        cmp ecx,edx
    L_00423ea1:
        jne short L_00423ec5
    L_00423ea3:
        mov eax,dword ptr [ebp+1E0h]
    L_00423ea9:
        test eax,eax
    L_00423eab:
        je asm_target_00424376
    L_00423eb1:
        dec eax
    L_00423eb2:
        mov dword ptr [ebp+1E0h],eax
    L_00423eb8:
        mov byte ptr [eax+ebp+2B4h],20h
    L_00423ec0:
        jmp asm_target_00423cb9
    L_00423ec5:
        dec eax
    L_00423ec6:
        cmp ecx,eax
    L_00423ec8:
        jne asm_target_00423df9
    L_00423ece:
        push 0
    L_00423ed0:
        mov edi,2Ch
    L_00423ed5:
        mov ecx,492590h
    L_00423eda:
        call asm_AnimationManager_QueueResource_0043dc90
    L_00423edf:
        mov eax,dword ptr [ebp+24h]
    L_00423ee2:
        inc eax
    L_00423ee3:
        push eax
    L_00423ee4:
        lea ecx,[esp+1Ch]
    L_00423ee8:
        push 46E0C8h
    L_00423eed:
        push ecx
    L_00423eee:
        call asm_sprintf_00452ae8
    L_00423ef3:
        mov edx,dword ptr [ebp+24h]
    L_00423ef6:
        mov esi,dword ptr [ebp+edx*4+1ECh]
    L_00423efd:
        add esp,0Ch
    L_00423f00:
        call asm_Platform_DeletingDestructorWithRelease_004297b0
    L_00423f05:
        mov ecx,dword ptr [data_00477838]
    L_00423f0b:
        lea esi,[ebp+2B4h]
    L_00423f11:
        push esi
    L_00423f12:
        lea edx,[esp+1Ch]
    L_00423f16:
        call asm_FUN_00429b60_00429b60
    L_00423f1b:
        mov edi,dword ptr [ebp+24h]
    L_00423f1e:
        lea eax,[esp+18h]
    L_00423f22:
        push eax
    L_00423f23:
        call asm_StageManager_CreateRetail_004296f0
    L_00423f28:
        mov dword ptr [ebp+edi*4+1ECh],eax
    L_00423f2f:
        push 0
    L_00423f31:
        lea eax,[ebp+10h]
    L_00423f34:
        mov dword ptr [ebp+4],ebx
    L_00423f37:
        call asm_Player_SetSchedulerValue_00405410
    L_00423f3c:
        mov ecx,dword ptr [data_0047783c]
    L_00423f42:
        add ecx,1D878h
    L_00423f48:
        mov eax,esi
    L_00423f4a:
        sub ecx,esi
    L_00423f4c:
        TH10_NOP_LEA_ESP_DISP8()
    L_00423f50:
        mov dl,byte ptr [eax]
    L_00423f52:
        mov byte ptr [ecx+eax],dl
    L_00423f55:
        inc eax
    L_00423f56:
        test dl,dl
    L_00423f58:
        jne short L_00423f50
    L_00423f5a:
        pop edi
    L_00423f5b:
        pop esi
    L_00423f5c:
        pop ebx
    L_00423f5d:
        pop ebp
    L_00423f5e:
        mov ecx,dword ptr [esp+48h]
    L_00423f62:
        xor ecx,esp
    L_00423f64:
        call asm_security_check_cookie_00458ea5
    L_00423f69:
        add esp,4Ch
    L_00423f6c:
        ret 4
    L_00423f6f:
        pop edi
    L_00423f70:
        dec eax
    L_00423f71:
        pop esi
    L_00423f72:
        mov dword ptr [ebp+1E0h],eax
    L_00423f78:
        pop ebx
    L_00423f79:
        mov byte ptr [eax+ebp+2B4h],20h
    L_00423f81:
        pop ebp
    L_00423f82:
        mov ecx,dword ptr [esp+48h]
    L_00423f86:
        xor ecx,esp
    L_00423f88:
        call asm_security_check_cookie_00458ea5
    L_00423f8d:
        add esp,4Ch
    L_00423f90:
        ret 4
    L_00423f93:
        cmp dword ptr [ebp+14h],0Ah
    L_00423f97:
        jl asm_target_00424376
    L_00423f9d:
        mov eax,dword ptr [ebp+1E8h]
    L_00423fa3:
        test eax,eax
    L_00423fa5:
        mov ebx,1
    L_00423faa:
        jne asm_target_0042406f
    L_00423fb0:
        mov ecx,dword ptr [ebp+0FCh]
    L_00423fb6:
        lea esi,[ebp+0FCh]
    L_00423fbc:
        mov dword ptr [esi+4],ecx
    L_00423fbf:
        mov eax,10h
    L_00423fc4:
        mov ecx,474E30h
    L_00423fc9:
        call asm_InputMaskActive_0040ace0
    L_00423fce:
        test ax,ax
    L_00423fd1:
        je short L_00423fdc
    L_00423fd3:
        push 0FFFFFFF3h
    L_00423fd5:
        mov eax,esi
    L_00423fd7:
        call asm_MenuCursor_Advance_0044bea0
    L_00423fdc:
        mov eax,20h
    L_00423fe1:
        mov ecx,474E30h
    L_00423fe6:
        call asm_InputMaskActive_0040ace0
    L_00423feb:
        test ax,ax
    L_00423fee:
        je short L_00423ff9
    L_00423ff0:
        push 0Dh
    L_00423ff2:
        mov eax,esi
    L_00423ff4:
        call asm_MenuCursor_Advance_0044bea0
    L_00423ff9:
        mov eax,40h
    L_00423ffe:
        mov ecx,474E30h
    L_00424003:
        call asm_InputMaskActive_0040ace0
    L_00424008:
        test ax,ax
    L_0042400b:
        je short L_00424028
    L_0042400d:
        mov eax,dword ptr [esi]
    L_0042400f:
        cdq
    L_00424010:
        mov ecx,0Dh
    L_00424015:
        idiv ecx
    L_00424017:
        mov eax,esi
    L_00424019:
        test edx,edx
    L_0042401b:
        je short L_00424021
    L_0042401d:
        push 0FFFFFFFFh
    L_0042401f:
        jmp short L_00424023
    L_00424021:
        push 0Ch
    L_00424023:
        call asm_MenuCursor_Advance_0044bea0
    L_00424028:
        mov eax,80h
    L_0042402d:
        mov ecx,474E30h
    L_00424032:
        call asm_InputMaskActive_0040ace0
    L_00424037:
        test ax,ax
    L_0042403a:
        je short L_00424057
    L_0042403c:
        mov eax,dword ptr [esi]
    L_0042403e:
        cdq
    L_0042403f:
        mov ecx,0Dh
    L_00424044:
        idiv ecx
    L_00424046:
        mov eax,esi
    L_00424048:
        cmp edx,0Ch
    L_0042404b:
        je short L_00424050
    L_0042404d:
        push ebx
    L_0042404e:
        jmp short L_00424052
    L_00424050:
        push 0FFFFFFF4h
    L_00424052:
        call asm_MenuCursor_Advance_0044bea0
    L_00424057:
        mov edx,dword ptr [esi+4]
    L_0042405a:
        cmp edx,dword ptr [esi]
    L_0042405c:
        je short L_0042406f
    L_0042405e:
        push 0
    L_00424060:
        mov edi,0Ch
    L_00424065:
        mov ecx,492590h
    L_0042406a:
        call asm_AnimationManager_QueueResource_0043dc90
    L_0042406f:
        test dword ptr [data_00474e36],1001h
    L_00424079:
        je asm_target_0042426d
    L_0042407f:
        mov eax,dword ptr [ebp+1E8h]
    L_00424085:
        test eax,eax
    L_00424087:
        jne asm_target_00424217
    L_0042408d:
        mov edi,dword ptr [data_004746d8]
    L_00424093:
        mov eax,edi
    L_00424095:
        lea edx,[eax+1]
    L_00424098:
        mov cl,byte ptr [eax]
    L_0042409a:
        inc eax
    L_0042409b:
        test cl,cl
    L_0042409d:
        jne short L_00424098
    L_0042409f:
        mov ecx,dword ptr [ebp+0FCh]
    L_004240a5:
        sub eax,edx
    L_004240a7:
        lea edx,[ebp+0FCh]
    L_004240ad:
        lea esi,[eax-3]
    L_004240b0:
        cmp ecx,esi
    L_004240b2:
        jge short L_004240da
    L_004240b4:
        mov esi,dword ptr [ebp+1E0h]
    L_004240ba:
        cmp esi,8
    L_004240bd:
        jge short L_004240cb
    L_004240bf:
        mov cl,byte ptr [ecx+edi]
    L_004240c2:
        mov byte ptr [esi+ebp+2B4h],cl
    L_004240c9:
        jmp short L_004240ef
    L_004240cb:
        mov dl,byte ptr [ecx+edi]
    L_004240ce:
        mov byte ptr [esi+ebp+2B3h],dl
    L_004240d5:
        jmp asm_target_00424204
    L_004240da:
        jne short L_00424121
    L_004240dc:
        mov ecx,dword ptr [ebp+1E0h]
    L_004240e2:
        cmp ecx,8
    L_004240e5:
        jge short L_00424114
    L_004240e7:
        mov byte ptr [ecx+ebp+2B4h],20h
    L_004240ef:
        mov esi,dword ptr [ebp+1E0h]
    L_004240f5:
        inc esi
    L_004240f6:
        mov ecx,esi
    L_004240f8:
        cmp ecx,8
    L_004240fb:
        mov dword ptr [ebp+1E0h],esi
    L_00424101:
        jl asm_target_00424204
    L_00424107:
        lea ecx,[eax-1]
    L_0042410a:
        call asm_FUN_0040ad20_0040ad20
    L_0042410f:
        jmp asm_target_00424204
    L_00424114:
        mov byte ptr [ecx+ebp+2B3h],20h
    L_0042411c:
        jmp asm_target_00424204
    L_00424121:
        lea edx,[eax-2]
    L_00424124:
        cmp ecx,edx
    L_00424126:
        jne short L_0042414a
    L_00424128:
        mov eax,dword ptr [ebp+1E0h]
    L_0042412e:
        test eax,eax
    L_00424130:
        je asm_target_00424376
    L_00424136:
        dec eax
    L_00424137:
        mov dword ptr [ebp+1E0h],eax
    L_0042413d:
        mov byte ptr [eax+ebp+2B4h],20h
    L_00424145:
        jmp asm_target_00424204
    L_0042414a:
        dec eax
    L_0042414b:
        cmp ecx,eax
    L_0042414d:
        jne asm_target_00424204
    L_00424153:
        mov ecx,dword ptr [data_00474c68]
    L_00424159:
        mov eax,dword ptr [data_00474c6c]
    L_0042415e:
        mov edi,dword ptr [ebp+24h]
    L_00424161:
        lea eax,[eax+ecx*2]
    L_00424164:
        add eax,ecx
    L_00424166:
        mov ecx,dword ptr [data_00474c74]
    L_0042416c:
        imul eax,437Ch
    L_00424172:
        lea ecx,[ecx+ecx*4]
    L_00424175:
        lea ecx,[edi+ecx*2]
    L_00424178:
        mov edi,dword ptr [data_0047783c]
    L_0042417e:
        lea esi,[ebp+2B4h]
    L_00424184:
        lea ecx,[ecx+ecx*2]
    L_00424187:
        add eax,edi
    L_00424189:
        mov edx,esi
    L_0042418b:
        lea ecx,[eax+ecx*8+1Eh]
    L_0042418f:
        nop
    L_00424190:
        mov al,byte ptr [edx]
    L_00424192:
        inc edx
    L_00424193:
        mov byte ptr [ecx],al
    L_00424195:
        inc ecx
    L_00424196:
        test al,al
    L_00424198:
        jne short L_00424190
    L_0042419a:
        lea edx,[edi+1D878h]
    L_004241a0:
        mov eax,esi
    L_004241a2:
        sub edx,esi
    L_004241a4:
        mov cl,byte ptr [eax]
    L_004241a6:
        mov byte ptr [edx+eax],cl
    L_004241a9:
        inc eax
    L_004241aa:
        test cl,cl
    L_004241ac:
        jne short L_004241a4
    L_004241ae:
        lea edi,[ebp+1D4h]
    L_004241b4:
        mov eax,edi
    L_004241b6:
        call asm_AnimationManager_SetFlagBit1_00449590
    L_004241bb:
        mov dword ptr [ebp+4],8
    L_004241c2:
        mov dword ptr [ebp+2Ch],3
    L_004241c9:
        mov dword ptr [ebp+0F4h],ebx
    L_004241cf:
        mov eax,dword ptr [ebp+2Ch]
    L_004241d2:
        test eax,eax
    L_004241d4:
        je short L_004241e5
    L_004241d6:
        jg short L_004241de
    L_004241d8:
        dec eax
    L_004241d9:
        mov dword ptr [ebp+24h],eax
    L_004241dc:
        jmp short L_004241ec
    L_004241de:
        xor eax,eax
    L_004241e0:
        mov dword ptr [ebp+24h],eax
    L_004241e3:
        jmp short L_004241ec
    L_004241e5:
        mov dword ptr [ebp+24h],0
    L_004241ec:
        mov eax,edi
    L_004241ee:
        call asm_AnimationManager_StopAtFrame3_0040c4d0
    L_004241f3:
        xor esi,esi
    L_004241f5:
        mov si,word ptr [ebp+24h]
    L_004241f9:
        add si,7
    L_004241fd:
        mov eax,edi
    L_004241ff:
        call asm_AnimationManager_SetStopFrameFromHandleRetail_00449470
    L_00424204:
        push 0
    L_00424206:
        mov edi,0Ah
    L_0042420b:
        mov ecx,492590h
    L_00424210:
        call asm_AnimationManager_QueueResource_0043dc90
    L_00424215:
        jmp short L_0042426d
    L_00424217:
        lea edi,[ebp+1D4h]
    L_0042421d:
        mov eax,edi
    L_0042421f:
        call asm_AnimationManager_SetFlagBit1_00449590
    L_00424224:
        mov dword ptr [ebp+4],8
    L_0042422b:
        mov dword ptr [ebp+2Ch],3
    L_00424232:
        mov dword ptr [ebp+0F4h],ebx
    L_00424238:
        mov eax,dword ptr [ebp+2Ch]
    L_0042423b:
        test eax,eax
    L_0042423d:
        je short L_0042424e
    L_0042423f:
        jg short L_00424247
    L_00424241:
        dec eax
    L_00424242:
        mov dword ptr [ebp+24h],eax
    L_00424245:
        jmp short L_00424255
    L_00424247:
        xor eax,eax
    L_00424249:
        mov dword ptr [ebp+24h],eax
    L_0042424c:
        jmp short L_00424255
    L_0042424e:
        mov dword ptr [ebp+24h],0
    L_00424255:
        mov eax,edi
    L_00424257:
        call asm_AnimationManager_StopAtFrame3_0040c4d0
    L_0042425c:
        xor esi,esi
    L_0042425e:
        mov si,word ptr [ebp+24h]
    L_00424262:
        add si,7
    L_00424266:
        mov eax,edi
    L_00424268:
        call asm_AnimationManager_SetStopFrameFromHandleRetail_00449470
    L_0042426d:
        test byte ptr [data_00474e36],0Ah
    L_00424274:
        je asm_target_00424376
    L_0042427a:
        mov eax,dword ptr [ebp+24h]
    L_0042427d:
        test eax,eax
    L_0042427f:
        jl short L_004242ca
    L_00424281:
        mov eax,dword ptr [ebp+1E0h]
    L_00424287:
        test eax,eax
    L_00424289:
        je asm_target_00424376
    L_0042428f:
        push 0
    L_00424291:
        mov edi,0Bh
    L_00424296:
        mov ecx,492590h
    L_0042429b:
        call asm_AnimationManager_QueueResource_0043dc90
    L_004242a0:
        mov eax,dword ptr [ebp+1E0h]
    L_004242a6:
        pop edi
    L_004242a7:
        dec eax
    L_004242a8:
        pop esi
    L_004242a9:
        mov dword ptr [ebp+1E0h],eax
    L_004242af:
        pop ebx
    L_004242b0:
        mov byte ptr [eax+ebp+2B4h],20h
    L_004242b8:
        pop ebp
    L_004242b9:
        mov ecx,dword ptr [esp+48h]
    L_004242bd:
        xor ecx,esp
    L_004242bf:
        call asm_security_check_cookie_00458ea5
    L_004242c4:
        add esp,4Ch
    L_004242c7:
        ret 4
    L_004242ca:
        mov dword ptr [ebp+4],8
    L_004242d1:
        mov dword ptr [ebp+2Ch],3
    L_004242d8:
        mov eax,dword ptr [ebp+2Ch]
    L_004242db:
        test eax,eax
    L_004242dd:
        je short L_00424307
    L_004242df:
        jg short L_004242f4
    L_004242e1:
        dec eax
    L_004242e2:
        mov dword ptr [ebp+24h],eax
    L_004242e5:
        push 0
    L_004242e7:
        lea eax,[ebp+10h]
    L_004242ea:
        call asm_Player_SetSchedulerValue_00405410
    L_004242ef:
        jmp asm_target_00423bfa
    L_004242f4:
        xor eax,eax
    L_004242f6:
        mov dword ptr [ebp+24h],eax
    L_004242f9:
        push eax
    L_004242fa:
        lea eax,[ebp+10h]
    L_004242fd:
        call asm_Player_SetSchedulerValue_00405410
    L_00424302:
        jmp asm_target_00423bfa
    L_00424307:
        push 0
    L_00424309:
        lea eax,[ebp+10h]
    L_0042430c:
        mov dword ptr [ebp+24h],0
    L_00424313:
        call asm_Player_SetSchedulerValue_00405410
    L_00424318:
        jmp asm_target_00423bfa
    L_0042431d:
        cmp dword ptr [ebp+14h],0Ch
    L_00424321:
        jl short L_00424376
    L_00424323:
        mov esi,ebp
    L_00424325:
        call asm_Recovery_InitializeTimedState_00423510
    L_0042432a:
        mov eax,dword ptr [ebp+24h]
    L_0042432d:
        sub eax,0
    L_00424330:
        mov dword ptr [ebp+4],15h
    L_00424337:
        je short L_00424360
    L_00424339:
        dec eax
    L_0042433a:
        je short L_0042433f
    L_0042433c:
        dec eax
    L_0042433d:
        jne short L_00424376
    L_0042433f:
        push 4
    L_00424341:
        mov eax,491C28h
    L_00424346:
        call asm_SetInputMode_0040ac90
    L_0042434b:
        pop edi
    L_0042434c:
        pop esi
    L_0042434d:
        pop ebx
    L_0042434e:
        pop ebp
    L_0042434f:
        mov ecx,dword ptr [esp+48h]
    L_00424353:
        xor ecx,esp
    L_00424355:
        call asm_security_check_cookie_00458ea5
    L_0042435a:
        add esp,4Ch
    L_0042435d:
        ret 4
    L_00424360:
        mov edx,dword ptr [ebp+1E4h]
    L_00424366:
        neg edx
    L_00424368:
        sbb edx,edx
    L_0042436a:
        and edx,0FFFFFFFDh
    L_0042436d:
        add edx,0Dh
    L_00424370:
        mov dword ptr [data_00491fb8],edx
    L_00424376:
        pop edi
    L_00424377:
        pop esi
    L_00424378:
        pop ebx
    L_00424379:
        mov ecx,dword ptr [esp+4Ch]
    L_0042437d:
        pop ebp
    L_0042437e:
        xor ecx,esp
    L_00424380:
        call asm_security_check_cookie_00458ea5
    L_00424385:
        add esp,4Ch
    L_00424388:
        ret 4
    }
}
