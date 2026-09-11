#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x004601E8..0x004602C8: FUN_004601e8
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) void __cdecl asm_FUN_004601e8_004601e8() {
    __asm {
    L_004601e8:
        push 44h
    L_004601ea:
        push 46C940h
    L_004601ef:
        call asm_SEH_prolog_00454bbc
    L_004601f4:
        mov eax,dword ptr [data_00473660]
    L_004601f9:
        xor eax,ebp
    L_004601fb:
        mov dword ptr [ebp-1Ch],eax
    L_004601fe:
        mov esi,dword ptr [ebp+10h]
    L_00460201:
        mov dword ptr [ebp-44h],esi
    L_00460204:
        mov eax,dword ptr [ebp+14h]
    L_00460207:
        mov dword ptr [ebp-50h],eax
    L_0046020a:
        mov ecx,dword ptr [ebp+18h]
    L_0046020d:
        mov dword ptr [ebp-40h],ecx
    L_00460210:
        xor edi,edi
    L_00460212:
        mov dword ptr [ebp-34h],edi
    L_00460215:
        mov dword ptr [ebp-4Ch],edi
    L_00460218:
        mov ebx,dword ptr [eax]
    L_0046021a:
        mov dword ptr [ebp-48h],ebx
    L_0046021d:
        mov dword ptr [ebp-38h],edi
    L_00460220:
        mov eax,dword ptr [ebp+8]
    L_00460223:
        cmp eax,dword ptr [ebp+0Ch]
    L_00460226:
        je asm_target_0046039d
    L_0046022c:
        lea ecx,[ebp-30h]
    L_0046022f:
        push ecx
    L_00460230:
        push eax
    L_00460231:
        call dword ptr [data_00466064]
    L_00460237:
        test eax,eax
    L_00460239:
        je short L_0046025d
    L_0046023b:
        cmp dword ptr [ebp-30h],1
    L_0046023f:
        jne short L_0046025d
    L_00460241:
        lea eax,[ebp-30h]
    L_00460244:
        push eax
    L_00460245:
        push dword ptr [ebp+0Ch]
    L_00460248:
        call dword ptr [data_00466064]
    L_0046024e:
        test eax,eax
    L_00460250:
        je short L_0046025d
    L_00460252:
        xor eax,eax
    L_00460254:
        inc eax
    L_00460255:
        cmp dword ptr [ebp-30h],eax
    L_00460258:
        jne short L_0046025d
    L_0046025a:
        mov dword ptr [ebp-38h],eax
    L_0046025d:
        cmp dword ptr [ebp-38h],edi
    L_00460260:
        je short L_0046027a
    L_00460262:
        cmp ebx,0FFFFFFFFh
    L_00460265:
        je short L_0046026b
    L_00460267:
        mov esi,ebx
    L_00460269:
        jmp short L_00460275
    L_0046026b:
        push esi
    L_0046026c:
        call asm_strlen_00456720
    L_00460271:
        pop ecx
    L_00460272:
        mov esi,eax
    L_00460274:
        inc esi
    L_00460275:
        mov dword ptr [ebp-3Ch],esi
    L_00460278:
        jmp short L_0046027d
    L_0046027a:
        mov esi,dword ptr [ebp-3Ch]
    L_0046027d:
        cmp dword ptr [ebp-38h],edi
    L_00460280:
        jne short L_0046029c
    L_00460282:
        push edi
    L_00460283:
        push edi
    L_00460284:
        push ebx
    L_00460285:
        push dword ptr [ebp-44h]
    L_00460288:
        push 1
    L_0046028a:
        push dword ptr [ebp+8]
    L_0046028d:
        call dword ptr [data_00466104]
    L_00460293:
        mov esi,eax
    L_00460295:
        mov dword ptr [ebp-3Ch],esi
    L_00460298:
        cmp esi,edi
    L_0046029a:
        TH10_REL8(0x74, 0x0046029a, VA_asm_target_004602f4)
    L_0046029c:
        mov dword ptr [ebp-4],edi
    L_0046029f:
        lea eax,[esi+esi]
    L_004602a2:
        add eax,3
    L_004602a5:
        and eax,0FFFFFFFCh
    L_004602a8:
        call asm_chkstk_00458ec0
    L_004602ad:
        mov dword ptr [ebp-18h],esp
    L_004602b0:
        mov ebx,esp
    L_004602b2:
        mov dword ptr [ebp-54h],ebx
    L_004602b5:
        lea eax,[esi+esi]
    L_004602b8:
        push eax
    L_004602b9:
        push edi
    L_004602ba:
        push ebx
    L_004602bb:
        call asm_memset_0045bed0
    L_004602c0:
        add esp,0Ch
    L_004602c3:
        or dword ptr [ebp-4],0FFFFFFFFh
    L_004602c7:
        TH10_REL8(0xeb, 0x004602c7, VA_asm_FUN_004601e8_part_004602e0)
        _emit 0x33
        _emit 0xc0
        _emit 0x40
        _emit 0xc3
        _emit 0x8b
        _emit 0x65
        _emit 0xe8
        _emit 0xe8
        _emit 0xbc
        _emit 0x8a
        _emit 0xff
        _emit 0xff
        _emit 0x33
        _emit 0xff
        _emit 0x33
        _emit 0xdb
        _emit 0x83
        _emit 0x4d
        _emit 0xfc
        _emit 0xff
        _emit 0x8b
        _emit 0x75
        _emit 0xc4

    L_004602e0:
        cmp ebx,edi
    L_004602e2:
        jne short L_00460302
    L_004602e4:
        push esi
    L_004602e5:
        push 2
    L_004602e7:
        call asm_FUN_0045794d_0045794d
    L_004602ec:
        pop ecx
    L_004602ed:
        pop ecx
    L_004602ee:
        mov ebx,eax
    L_004602f0:
        cmp ebx,edi
    L_004602f2:
        jne short L_004602fb
    L_004602f4:
        xor eax,eax
    L_004602f6:
        jmp asm_target_004603af
    L_004602fb:
        mov dword ptr [ebp-4Ch],1
    L_00460302:
        push esi
    L_00460303:
        push ebx
    L_00460304:
        push dword ptr [ebp-48h]
    L_00460307:
        push dword ptr [ebp-44h]
    L_0046030a:
        push 1
    L_0046030c:
        push dword ptr [ebp+8]
    L_0046030f:
        call dword ptr [data_00466104]
    L_00460315:
        test eax,eax
    L_00460317:
        je asm_target_004603a0
    L_0046031d:
        cmp dword ptr [ebp-40h],edi
    L_00460320:
        je short L_00460342
    L_00460322:
        push edi
    L_00460323:
        push edi
    L_00460324:
        push dword ptr [ebp+1Ch]
    L_00460327:
        push dword ptr [ebp-40h]
    L_0046032a:
        push esi
    L_0046032b:
        push ebx
    L_0046032c:
        push edi
    L_0046032d:
        push dword ptr [ebp+0Ch]
    L_00460330:
        call dword ptr [data_00466154]
    L_00460336:
        test eax,eax
    L_00460338:
        je short L_004603a0
    L_0046033a:
        mov eax,dword ptr [ebp-40h]
    L_0046033d:
        mov dword ptr [ebp-34h],eax
    L_00460340:
        jmp short L_004603a0
    L_00460342:
        cmp dword ptr [ebp-38h],edi
    L_00460345:
        jne short L_0046035d
    L_00460347:
        push edi
    L_00460348:
        push edi
    L_00460349:
        push edi
    L_0046034a:
        push edi
    L_0046034b:
        push esi
    L_0046034c:
        push ebx
    L_0046034d:
        push edi
    L_0046034e:
        push dword ptr [ebp+0Ch]
    L_00460351:
        call dword ptr [data_00466154]
    L_00460357:
        mov esi,eax
    L_00460359:
        cmp esi,edi
    L_0046035b:
        je short L_004603a0
    L_0046035d:
        push esi
    L_0046035e:
        push 1
    L_00460360:
        call asm_FUN_0045794d_0045794d
    L_00460365:
        pop ecx
    L_00460366:
        pop ecx
    L_00460367:
        mov dword ptr [ebp-34h],eax
    L_0046036a:
        cmp eax,edi
    L_0046036c:
        je short L_004603a0
    L_0046036e:
        push edi
    L_0046036f:
        push edi
    L_00460370:
        push esi
    L_00460371:
        push eax
    L_00460372:
        push esi
    L_00460373:
        push ebx
    L_00460374:
        push edi
    L_00460375:
        push dword ptr [ebp+0Ch]
    L_00460378:
        call dword ptr [data_00466154]
    L_0046037e:
        cmp eax,edi
    L_00460380:
        jne short L_00460390
    L_00460382:
        push dword ptr [ebp-34h]
    L_00460385:
        call asm_free_00452422
    L_0046038a:
        pop ecx
    L_0046038b:
        mov dword ptr [ebp-34h],edi
    L_0046038e:
        jmp short L_004603a0
    L_00460390:
        cmp dword ptr [ebp-48h],0FFFFFFFFh
    L_00460394:
        je short L_004603a0
    L_00460396:
        mov ecx,dword ptr [ebp-50h]
    L_00460399:
        mov dword ptr [ecx],eax
    L_0046039b:
        jmp short L_004603a0
    L_0046039d:
        mov ebx,dword ptr [ebp-54h]
    L_004603a0:
        cmp dword ptr [ebp-4Ch],edi
    L_004603a3:
        je short L_004603ac
    L_004603a5:
        push ebx
    L_004603a6:
        call asm_free_00452422
    L_004603ab:
        pop ecx
    L_004603ac:
        mov eax,dword ptr [ebp-34h]
    L_004603af:
        lea esp,[ebp-60h]
    L_004603b2:
        mov ecx,dword ptr [ebp-1Ch]
    L_004603b5:
        xor ecx,ebp
    L_004603b7:
        call asm_security_check_cookie_00458ea5
    L_004603bc:
        call asm_SEH_epilog_00454bf7
    L_004603c1:
        ret
    }
}
