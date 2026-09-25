#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x00453280..0x004532DA: _memmove
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_memmove_00453280() {
    __asm {
    L_00453280:
        push ebp
    L_00453281:
        mov ebp,esp
    L_00453283:
        push edi
    L_00453284:
        push esi
    L_00453285:
        mov esi,dword ptr [ebp+0Ch]
    L_00453288:
        mov ecx,dword ptr [ebp+10h]
    L_0045328b:
        mov edi,dword ptr [ebp+8]
    L_0045328e:
        mov eax,ecx
    L_00453290:
        mov edx,ecx
    L_00453292:
        add eax,esi
    L_00453294:
        cmp edi,esi
    L_00453296:
        jbe short L_004532a0
    L_00453298:
        cmp edi,eax
    L_0045329a:
        jb asm_memmove_part_0045341c
    L_004532a0:
        test edi,3
    L_004532a6:
        jne short L_004532bc
    L_004532a8:
        shr ecx,2
    L_004532ab:
        and edx,3
    L_004532ae:
        cmp ecx,8
    L_004532b1:
        TH10_REL8(0x72, 0x004532b1, VA_asm_memmove_part_004532dc)
    L_004532b3:
        rep movsd
    L_004532b5:
        jmp dword ptr [edx*4+4533CCh]
    L_004532bc:
        mov eax,edi
    L_004532be:
        mov edx,3
    L_004532c3:
        sub ecx,4
    L_004532c6:
        jb short L_004532d4
    L_004532c8:
        and eax,3
    L_004532cb:
        add ecx,eax
    L_004532cd:
        jmp dword ptr [eax*4+4532E0h]
    L_004532d4:
        jmp dword ptr [ecx*4+4533DCh]
    }
}

// 0x004532DC..0x004532E2: _memmove
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_memmove_part_004532dc() {
    __asm {
    L_004532dc:
        jmp dword ptr [ecx*4+453360h]
    }
}

// 0x004532F0..0x00453318: _memmove
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_memmove_part_004532f0() {
    __asm {
    L_004532f0:
        and edx,ecx
    L_004532f2:
        mov al,byte ptr [esi]
    L_004532f4:
        mov byte ptr [edi],al
    L_004532f6:
        mov al,byte ptr [esi+1]
    L_004532f9:
        mov byte ptr [edi+1],al
    L_004532fc:
        mov al,byte ptr [esi+2]
    L_004532ff:
        shr ecx,2
    L_00453302:
        mov byte ptr [edi+2],al
    L_00453305:
        add esi,3
    L_00453308:
        add edi,3
    L_0045330b:
        cmp ecx,8
    L_0045330e:
        TH10_REL8(0x72, 0x0045330e, VA_asm_memmove_part_004532dc)
    L_00453310:
        rep movsd
    L_00453312:
        jmp dword ptr [edx*4+4533CCh]
    }
}

// 0x0045331C..0x0045333E: _memmove
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_memmove_part_0045331c() {
    __asm {
    L_0045331c:
        and edx,ecx
    L_0045331e:
        mov al,byte ptr [esi]
    L_00453320:
        mov byte ptr [edi],al
    L_00453322:
        mov al,byte ptr [esi+1]
    L_00453325:
        shr ecx,2
    L_00453328:
        mov byte ptr [edi+1],al
    L_0045332b:
        add esi,2
    L_0045332e:
        add edi,2
    L_00453331:
        cmp ecx,8
    L_00453334:
        TH10_REL8(0x72, 0x00453334, VA_asm_memmove_part_004532dc)
    L_00453336:
        rep movsd
    L_00453338:
        jmp dword ptr [edx*4+4533CCh]
    }
}

// 0x00453340..0x0045335C: _memmove
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_memmove_part_00453340() {
    __asm {
    L_00453340:
        and edx,ecx
    L_00453342:
        mov al,byte ptr [esi]
    L_00453344:
        mov byte ptr [edi],al
    L_00453346:
        add esi,1
    L_00453349:
        shr ecx,2
    L_0045334c:
        add edi,1
    L_0045334f:
        cmp ecx,8
    L_00453352:
        TH10_REL8(0x72, 0x00453352, VA_asm_memmove_part_004532dc)
    L_00453354:
        rep movsd
    L_00453356:
        jmp dword ptr [edx*4+4533CCh]
    }
}

// 0x00453380..0x004533C9: _memmove
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_memmove_part_00453380() {
    __asm {
    L_00453380:
        mov eax,dword ptr [esi+ecx*4-1Ch]
    L_00453384:
        mov dword ptr [edi+ecx*4-1Ch],eax
    L_00453388:
        mov eax,dword ptr [esi+ecx*4-18h]
    L_0045338c:
        mov dword ptr [edi+ecx*4-18h],eax
    L_00453390:
        mov eax,dword ptr [esi+ecx*4-14h]
    L_00453394:
        mov dword ptr [edi+ecx*4-14h],eax
    L_00453398:
        mov eax,dword ptr [esi+ecx*4-10h]
    L_0045339c:
        mov dword ptr [edi+ecx*4-10h],eax
    L_004533a0:
        mov eax,dword ptr [esi+ecx*4-0Ch]
    L_004533a4:
        mov dword ptr [edi+ecx*4-0Ch],eax
    L_004533a8:
        mov eax,dword ptr [esi+ecx*4-8]
    L_004533ac:
        mov dword ptr [edi+ecx*4-8],eax
    L_004533b0:
        mov eax,dword ptr [esi+ecx*4-4]
    L_004533b4:
        mov dword ptr [edi+ecx*4-4],eax
    L_004533b8:
        lea eax,[ecx*4]
    L_004533bf:
        add esi,eax
    L_004533c1:
        add edi,eax
    L_004533c3:
        jmp dword ptr [edx*4+4533CCh]
    }
}

// 0x004533DC..0x004533E2: _memmove
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_memmove_part_004533dc() {
    __asm {
    L_004533dc:
        mov eax,dword ptr [ebp+8]
    L_004533df:
        pop esi
    L_004533e0:
        pop edi
    L_004533e1:
        leave
    L_004533e2:
        ret
    }
}

// 0x004533E4..0x004533EE: _memmove
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_memmove_part_004533e4() {
    __asm {
    L_004533e4:
        mov al,byte ptr [esi]
    L_004533e6:
        mov byte ptr [edi],al
    L_004533e8:
        mov eax,dword ptr [ebp+8]
    L_004533eb:
        pop esi
    L_004533ec:
        pop edi
    L_004533ed:
        leave
    L_004533ee:
        ret
    }
}

// 0x004533F0..0x00453400: _memmove
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_memmove_part_004533f0() {
    __asm {
    L_004533f0:
        mov al,byte ptr [esi]
    L_004533f2:
        mov byte ptr [edi],al
    L_004533f4:
        mov al,byte ptr [esi+1]
    L_004533f7:
        mov byte ptr [edi+1],al
    L_004533fa:
        mov eax,dword ptr [ebp+8]
    L_004533fd:
        pop esi
    L_004533fe:
        pop edi
    L_004533ff:
        leave
    L_00453400:
        ret
    }
}

// 0x00453404..0x0045341A: _memmove
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_memmove_part_00453404() {
    __asm {
    L_00453404:
        mov al,byte ptr [esi]
    L_00453406:
        mov byte ptr [edi],al
    L_00453408:
        mov al,byte ptr [esi+1]
    L_0045340b:
        mov byte ptr [edi+1],al
    L_0045340e:
        mov al,byte ptr [esi+2]
    L_00453411:
        mov byte ptr [edi+2],al
    L_00453414:
        mov eax,dword ptr [ebp+8]
    L_00453417:
        pop esi
    L_00453418:
        pop edi
    L_00453419:
        leave
    L_0045341a:
        ret
    }
}

// 0x0045341C..0x00453441: _memmove
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_memmove_part_0045341c() {
    __asm {
    L_0045341c:
        lea esi,[ecx+esi-4]
    L_00453420:
        lea edi,[ecx+edi-4]
    L_00453424:
        test edi,3
    L_0045342a:
        TH10_REL8(0x75, 0x0045342a, VA_asm_memmove_part_00453450)
    L_0045342c:
        shr ecx,2
    L_0045342f:
        and edx,3
    L_00453432:
        cmp ecx,8
    L_00453435:
        TH10_REL8(0x72, 0x00453435, VA_asm_memmove_part_00453444)
    L_00453437:
        std
    L_00453438:
        rep movsd
    L_0045343a:
        cld
    L_0045343b:
        jmp dword ptr [edx*4+453568h]
    }
}

// 0x00453444..0x0045344C: _memmove
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_memmove_part_00453444() {
    __asm {
    L_00453444:
        neg ecx
    L_00453446:
        jmp dword ptr [ecx*4+453518h]
    }
}

// 0x00453450..0x0045346E: _memmove
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_memmove_part_00453450() {
    __asm {
    L_00453450:
        mov eax,edi
    L_00453452:
        mov edx,3
    L_00453457:
        cmp ecx,4
    L_0045345a:
        jb short L_00453468
    L_0045345c:
        and eax,3
    L_0045345f:
        sub ecx,eax
    L_00453461:
        jmp dword ptr [eax*4+45346Ch]
    L_00453468:
        jmp dword ptr [ecx*4+453568h]
    }
}

// 0x0045347C..0x0045349C: _memmove
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_memmove_part_0045347c() {
    __asm {
    L_0045347c:
        mov al,byte ptr [esi+3]
    L_0045347f:
        and edx,ecx
    L_00453481:
        mov byte ptr [edi+3],al
    L_00453484:
        sub esi,1
    L_00453487:
        shr ecx,2
    L_0045348a:
        sub edi,1
    L_0045348d:
        cmp ecx,8
    L_00453490:
        TH10_REL8(0x72, 0x00453490, VA_asm_memmove_part_00453444)
    L_00453492:
        std
    L_00453493:
        rep movsd
    L_00453495:
        cld
    L_00453496:
        jmp dword ptr [edx*4+453568h]
    }
}

// 0x004534A0..0x004534C6: _memmove
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_memmove_part_004534a0() {
    __asm {
    L_004534a0:
        mov al,byte ptr [esi+3]
    L_004534a3:
        and edx,ecx
    L_004534a5:
        mov byte ptr [edi+3],al
    L_004534a8:
        mov al,byte ptr [esi+2]
    L_004534ab:
        shr ecx,2
    L_004534ae:
        mov byte ptr [edi+2],al
    L_004534b1:
        sub esi,2
    L_004534b4:
        sub edi,2
    L_004534b7:
        cmp ecx,8
    L_004534ba:
        TH10_REL8(0x72, 0x004534ba, VA_asm_memmove_part_00453444)
    L_004534bc:
        std
    L_004534bd:
        rep movsd
    L_004534bf:
        cld
    L_004534c0:
        jmp dword ptr [edx*4+453568h]
    }
}

// 0x004534C8..0x004534F8: _memmove
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_memmove_part_004534c8() {
    __asm {
    L_004534c8:
        mov al,byte ptr [esi+3]
    L_004534cb:
        and edx,ecx
    L_004534cd:
        mov byte ptr [edi+3],al
    L_004534d0:
        mov al,byte ptr [esi+2]
    L_004534d3:
        mov byte ptr [edi+2],al
    L_004534d6:
        mov al,byte ptr [esi+1]
    L_004534d9:
        shr ecx,2
    L_004534dc:
        mov byte ptr [edi+1],al
    L_004534df:
        sub esi,3
    L_004534e2:
        sub edi,3
    L_004534e5:
        cmp ecx,8
    L_004534e8:
        jb asm_memmove_part_00453444
    L_004534ee:
        std
    L_004534ef:
        rep movsd
    L_004534f1:
        cld
    L_004534f2:
        jmp dword ptr [edx*4+453568h]
    }
}

// 0x0045351C..0x00453565: _memmove
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_memmove_part_0045351c() {
    __asm {
    L_0045351c:
        mov eax,dword ptr [esi+ecx*4+1Ch]
    L_00453520:
        mov dword ptr [edi+ecx*4+1Ch],eax
    L_00453524:
        mov eax,dword ptr [esi+ecx*4+18h]
    L_00453528:
        mov dword ptr [edi+ecx*4+18h],eax
    L_0045352c:
        mov eax,dword ptr [esi+ecx*4+14h]
    L_00453530:
        mov dword ptr [edi+ecx*4+14h],eax
    L_00453534:
        mov eax,dword ptr [esi+ecx*4+10h]
    L_00453538:
        mov dword ptr [edi+ecx*4+10h],eax
    L_0045353c:
        mov eax,dword ptr [esi+ecx*4+0Ch]
    L_00453540:
        mov dword ptr [edi+ecx*4+0Ch],eax
    L_00453544:
        mov eax,dword ptr [esi+ecx*4+8]
    L_00453548:
        mov dword ptr [edi+ecx*4+8],eax
    L_0045354c:
        mov eax,dword ptr [esi+ecx*4+4]
    L_00453550:
        mov dword ptr [edi+ecx*4+4],eax
    L_00453554:
        lea eax,[ecx*4]
    L_0045355b:
        add esi,eax
    L_0045355d:
        add edi,eax
    L_0045355f:
        jmp dword ptr [edx*4+453568h]
    }
}

// 0x00453578..0x0045357E: _memmove
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_memmove_part_00453578() {
    __asm {
    L_00453578:
        mov eax,dword ptr [ebp+8]
    L_0045357b:
        pop esi
    L_0045357c:
        pop edi
    L_0045357d:
        leave
    L_0045357e:
        ret
    }
}

// 0x00453580..0x0045358C: _memmove
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_memmove_part_00453580() {
    __asm {
    L_00453580:
        mov al,byte ptr [esi+3]
    L_00453583:
        mov byte ptr [edi+3],al
    L_00453586:
        mov eax,dword ptr [ebp+8]
    L_00453589:
        pop esi
    L_0045358a:
        pop edi
    L_0045358b:
        leave
    L_0045358c:
        ret
    }
}

// 0x00453590..0x004535A2: _memmove
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_memmove_part_00453590() {
    __asm {
    L_00453590:
        mov al,byte ptr [esi+3]
    L_00453593:
        mov byte ptr [edi+3],al
    L_00453596:
        mov al,byte ptr [esi+2]
    L_00453599:
        mov byte ptr [edi+2],al
    L_0045359c:
        mov eax,dword ptr [ebp+8]
    L_0045359f:
        pop esi
    L_004535a0:
        pop edi
    L_004535a1:
        leave
    L_004535a2:
        ret
    }
}

// 0x004535A4..0x004535BC: _memmove
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_memmove_part_004535a4() {
    __asm {
    L_004535a4:
        mov al,byte ptr [esi+3]
    L_004535a7:
        mov byte ptr [edi+3],al
    L_004535aa:
        mov al,byte ptr [esi+2]
    L_004535ad:
        mov byte ptr [edi+2],al
    L_004535b0:
        mov al,byte ptr [esi+1]
    L_004535b3:
        mov byte ptr [edi+1],al
    L_004535b6:
        mov eax,dword ptr [ebp+8]
    L_004535b9:
        pop esi
    L_004535ba:
        pop edi
    L_004535bb:
        leave
    L_004535bc:
        ret
    }
}
