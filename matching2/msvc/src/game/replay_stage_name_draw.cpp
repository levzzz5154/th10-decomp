// BLOCKED (live Ghidra ABI audit): keep the exact body until the hidden
// GameThread vector-in-EBX call contract and the fixed RET 4 entry alias have
// a declared bridge. 0x00401630 formats varargs, then calls 0x00401530 with
// text in EAX, receiver in ECX, and the three-word position vector in EBX;
// ordinary C++ varargs cannot express that vector argument. The public region
// alias is currently an undecorated cdecl/no-argument symbol, while the retail
// entry consumes its stack argument with RET 4. The previous MSVC 13.10
// readable-stub probe emitted only 5/826 bytes; no probe/build/test was run
// for this audit. See replay_stage_name_draw_00433230_abi_blocker.md.
#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00433230..0x004333DC: FUN_00433230
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_00433230_00433230() {
    __asm {
    L_00433230:
        mov eax,dword ptr [esp+4]
    L_00433234:
        mov ecx,dword ptr [eax+20h]
    L_00433237:
        sub esp,0Ch
    L_0043323a:
        sub ecx,2
    L_0043323d:
        jne asm_target_0043355f
    L_00433243:
        push ebx
    L_00433244:
        mov ebx,dword ptr [data_004776e0]
    L_0043324a:
        push ebp
    L_0043324b:
        push esi
    L_0043324c:
        push edi
    L_0043324d:
        mov edi,dword ptr [data_00474c74]
    L_00433253:
        xor esi,esi
    L_00433255:
        imul edi,0F0h
    L_0043325b:
        mov dword ptr [esp+10h],42400000h
    L_00433263:
        mov dword ptr [esp+14h],43200000h
    L_0043326b:
        mov dword ptr [esp+18h],0
    L_00433273:
        mov dword ptr [ebx+8988h],1
    L_0043327d:
        mov ebp,0FFh
    L_00433282:
        jmp short L_00433290
    L_00433284:
        mov ebx,dword ptr [data_004776e0]
    L_0043328a:
        mov eax,dword ptr [esp+20h]
    L_0043328e:
        mov edi,edi
    L_00433290:
        mov ecx,dword ptr [eax+58ECh]
    L_00433296:
        test ecx,ecx
    L_00433298:
        je short L_004332b1
    L_0043329a:
        mov eax,ebp
    L_0043329c:
        shl eax,8
    L_0043329f:
        or eax,ebp
    L_004332a1:
        shl eax,8
    L_004332a4:
        or eax,0FF0000FFh
    L_004332a9:
        mov dword ptr [ebx+8974h],eax
    L_004332af:
        jmp short L_004332c9
    L_004332b1:
        mov edx,dword ptr [eax+24h]
    L_004332b4:
        xor ecx,ecx
    L_004332b6:
        cmp edx,esi
    L_004332b8:
        sete cl
    L_004332bb:
        dec ecx
    L_004332bc:
        and ecx,0FF404041h
    L_004332c2:
        dec ecx
    L_004332c3:
        mov dword ptr [ebx+8974h],ecx
    L_004332c9:
        mov ecx,dword ptr [data_00474c68]
    L_004332cf:
        mov edx,dword ptr [data_00474c6c]
    L_004332d5:
        lea eax,[edx+ecx*2]
    L_004332d8:
        mov edx,dword ptr [data_0047783c]
    L_004332de:
        add eax,ecx
    L_004332e0:
        imul eax,437Ch
    L_004332e6:
        lea ecx,[edi+eax]
    L_004332e9:
        add ecx,edx
    L_004332eb:
        cmp dword ptr [ecx+28h],0
    L_004332ef:
        je asm_target_0043337a
    L_004332f5:
        lea eax,[eax+edx+8]
    L_004332f9:
        lea edx,[edi+eax+20h]
    L_004332fd:
        push edx
    L_004332fe:
        call asm_localtime_00452baa
    L_00433303:
        mov ecx,dword ptr [data_00474c68]
    L_00433309:
        mov edx,dword ptr [data_00474c6c]
    L_0043330f:
        lea edx,[edx+ecx*2]
    L_00433312:
        add edx,ecx
    L_00433314:
        mov ecx,dword ptr [data_0047783c]
    L_0043331a:
        imul edx,437Ch
    L_00433320:
        add edx,edi
    L_00433322:
        add ecx,edx
    L_00433324:
        movsx edx,byte ptr [ecx+1Ch]
    L_00433328:
        fld dword ptr [ecx+2Ch]
    L_0043332b:
        mov edx,dword ptr [edx*4+47471Ch]
    L_00433332:
        push ecx
    L_00433333:
        inc esi
    L_00433334:
        add ecx,1Eh
    L_00433337:
        fstp qword ptr [esp]
    L_0043333a:
        push edx
    L_0043333b:
        mov edx,dword ptr [eax+4]
    L_0043333e:
        push edx
    L_0043333f:
        mov edx,dword ptr [eax+8]
    L_00433342:
        push edx
    L_00433343:
        mov edx,dword ptr [eax+0Ch]
    L_00433346:
        push edx
    L_00433347:
        mov edx,dword ptr [eax+10h]
    L_0043334a:
        mov eax,dword ptr [eax+14h]
    L_0043334d:
        inc edx
    L_0043334e:
        push edx
    L_0043334f:
        movsx edx,byte ptr [ecx-1]
    L_00433353:
        add eax,76Ch
    L_00433358:
        push eax
    L_00433359:
        mov eax,dword ptr [ecx-6]
    L_0043335c:
        push edx
    L_0043335d:
        push eax
    L_0043335e:
        push ecx
    L_0043335f:
        mov ecx,dword ptr [data_004776e0]
    L_00433365:
        push esi
    L_00433366:
        push 46EE84h
    L_0043336b:
        push ecx
    L_0043336c:
        lea ebx,[esp+48h]
    L_00433370:
        call asm_GameThread_AppendFormatted_00401630
    L_00433375:
        add esp,38h
    L_00433378:
        jmp short L_004333a4
    L_0043337a:
        movsx edx,byte ptr [ecx+1Dh]
    L_0043337e:
        fld dword ptr [ecx+2Ch]
    L_00433381:
        mov eax,dword ptr [ecx+18h]
    L_00433384:
        sub esp,8
    L_00433387:
        add ecx,1Eh
    L_0043338a:
        inc esi
    L_0043338b:
        fstp qword ptr [esp]
    L_0043338e:
        push edx
    L_0043338f:
        push eax
    L_00433390:
        push ecx
    L_00433391:
        push esi
    L_00433392:
        push 46EE50h
    L_00433397:
        push ebx
    L_00433398:
        lea ebx,[esp+30h]
    L_0043339c:
        call asm_GameThread_AppendFormatted_00401630
    L_004333a1:
        add esp,20h
    L_004333a4:
        fld dword ptr [esp+14h]
    L_004333a8:
        sub ebp,10h
    L_004333ab:
        fadd dword ptr [data_00470c0c]
    L_004333b1:
        add edi,18h
    L_004333b4:
        cmp ebp,5Fh
    L_004333b7:
        fstp dword ptr [esp+14h]
    L_004333bb:
        jg asm_target_00433284
    L_004333c1:
        mov edi,dword ptr [esp+20h]
    L_004333c5:
        mov eax,dword ptr [edi+58ECh]
    L_004333cb:
        test eax,eax
    L_004333cd:
        jne asm_target_0043355b
    L_004333d3:
        mov eax,dword ptr [data_004746d8]
    L_004333d8:
        lea edx,[eax+1]
    L_004333db:
        TH10_REL8(0xeb, 0x004333db, VA_asm_FUN_00433230_part_004333e0)
        _emit 0x8d
        _emit 0x49
        _emit 0x00

    L_004333e0:
        mov cl,byte ptr [eax]
    L_004333e2:
        inc eax
    L_004333e3:
        test cl,cl
    L_004333e5:
        jne short L_004333e0
    L_004333e7:
        fild dword ptr [edi+24h]
    L_004333ea:
        sub eax,edx
    L_004333ec:
        lea ecx,[edi+58DCh]
    L_004333f2:
        push ecx
    L_004333f3:
        fmul dword ptr [data_00470c0c]
    L_004333f9:
        mov ebp,eax
    L_004333fb:
        mov eax,dword ptr [data_004776e0]
    L_00433400:
        push 46E1C8h
    L_00433405:
        fadd dword ptr [data_00470c24]
    L_0043340b:
        or esi,0FFFFFFFFh
    L_0043340e:
        push eax
    L_0043340f:
        lea ebx,[esp+1Ch]
    L_00433413:
        fstp dword ptr [esp+20h]
    L_00433417:
        mov dword ptr [esp+1Ch],42A80000h
    L_0043341f:
        mov dword ptr [esp+24h],0
    L_00433427:
        mov dword ptr [eax+8974h],esi
    L_0043342d:
        call asm_GameThread_AppendFormatted_00401630
    L_00433432:
        mov eax,dword ptr [edi+58E8h]
    L_00433438:
        lea edx,[eax+eax*8]
    L_0043343b:
        mov dword ptr [esp+2Ch],edx
    L_0043343f:
        fild dword ptr [esp+2Ch]
    L_00433443:
        add esp,0Ch
    L_00433446:
        cmp eax,8
    L_00433449:
        fadd dword ptr [data_00470c20]
    L_0043344f:
        fstp dword ptr [esp+10h]
    L_00433453:
        jne short L_00433463
    L_00433455:
        fld dword ptr [esp+10h]
    L_00433459:
        fsub dword ptr [data_00470c10]
    L_0043345f:
        fstp dword ptr [esp+10h]
    L_00433463:
        mov eax,dword ptr [data_004776e0]
    L_00433468:
        push 46E1C4h
    L_0043346d:
        push eax
    L_0043346e:
        lea ebx,[esp+18h]
    L_00433472:
        mov dword ptr [eax+8974h],0FFFFFF00h
    L_0043347c:
        call asm_GameThread_AppendFormatted_00401630
    L_00433481:
        mov eax,dword ptr [data_004776e0]
    L_00433486:
        mov dword ptr [eax+8974h],esi
    L_0043348c:
        add esp,8
    L_0043348f:
        xor esi,esi
    L_00433491:
        test ebp,ebp
    L_00433493:
        mov dword ptr [esp+10h],43540000h
    L_0043349b:
        mov dword ptr [esp+14h],43B40000h
    L_004334a3:
        mov dword ptr [esp+18h],0
    L_004334ab:
        jle asm_target_00433551
    L_004334b1:
        mov edx,dword ptr [edi+58F4h]
    L_004334b7:
        xor ecx,ecx
    L_004334b9:
        cmp edx,esi
    L_004334bb:
        setne cl
    L_004334be:
        dec ecx
    L_004334bf:
        and ecx,7F7E80h
    L_004334c5:
        add ecx,0FF808080h
    L_004334cb:
        mov dword ptr [eax+8974h],ecx
    L_004334d1:
        lea ecx,[ebp-3]
    L_004334d4:
        cmp esi,ecx
    L_004334d6:
        jge short L_004334e4
    L_004334d8:
        mov edx,dword ptr [data_004746d8]
    L_004334de:
        movsx ecx,byte ptr [edx+esi]
    L_004334e2:
        jmp short L_004334fa
    L_004334e4:
        jne short L_004334ed
    L_004334e6:
        mov ecx,81h
    L_004334eb:
        jmp short L_004334fa
    L_004334ed:
        xor ecx,ecx
    L_004334ef:
        lea edx,[ebp-2]
    L_004334f2:
        cmp esi,edx
    L_004334f4:
        setne cl
    L_004334f7:
        add ecx,7Fh
    L_004334fa:
        push ecx
    L_004334fb:
        push 46E1C0h
    L_00433500:
        lea ebx,[esp+18h]
    L_00433504:
        push eax
    L_00433505:
        call asm_GameThread_AppendFormatted_00401630
    L_0043350a:
        xor edx,edx
    L_0043350c:
        mov eax,esi
    L_0043350e:
        mov ecx,0Dh
    L_00433513:
        div ecx
    L_00433515:
        add esp,0Ch
    L_00433518:
        cmp edx,0Ch
    L_0043351b:
        jne short L_00433535
    L_0043351d:
        fld dword ptr [esp+14h]
    L_00433521:
        mov dword ptr [esp+10h],43540000h
    L_00433529:
        fadd dword ptr [data_00470b48]
    L_0043352f:
        fstp dword ptr [esp+14h]
    L_00433533:
        jmp short L_00433543
    L_00433535:
        fld dword ptr [esp+10h]
    L_00433539:
        fadd dword ptr [data_00470c0c]
    L_0043353f:
        fstp dword ptr [esp+10h]
    L_00433543:
        mov eax,dword ptr [data_004776e0]
    L_00433548:
        inc esi
    L_00433549:
        cmp esi,ebp
    L_0043354b:
        jl asm_target_004334b1
    L_00433551:
        mov dword ptr [eax+8974h],0FFFFFFFFh
    L_0043355b:
        pop edi
    L_0043355c:
        pop esi
    L_0043355d:
        pop ebp
    L_0043355e:
        pop ebx
    L_0043355f:
        mov eax,1
    L_00433564:
        add esp,0Ch
    L_00433567:
        ret 4
    }
}
