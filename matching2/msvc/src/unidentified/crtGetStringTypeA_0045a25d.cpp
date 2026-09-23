#include "asm_encoding.hpp"
#include "asm_symbols.hpp"

// 0x0045A25D..0x0045A335: ___crtGetStringTypeA
// Naked body preserves the retail register/stack ABI.
extern "C" __declspec(naked) int __cdecl asm_crtGetStringTypeA_0045a25d(
    unsigned int,
    const char*,
    int,
    unsigned short*,
    unsigned int,
    unsigned int,
    int) {
    __asm {
    L_0045a25d:
        push 1Ch
    L_0045a25f:
        push 46B5C8h
    L_0045a264:
        call asm_SEH_prolog_00454bbc
    L_0045a269:
        xor esi,esi
    L_0045a26b:
        cmp dword ptr [data_00477618],esi
    L_0045a271:
        jne short L_0045a2a8
    L_0045a273:
        lea eax,[ebp-1Ch]
    L_0045a276:
        push eax
    L_0045a277:
        xor edi,edi
    L_0045a279:
        inc edi
    L_0045a27a:
        push edi
    L_0045a27b:
        push 46B5C4h
    L_0045a280:
        push edi
    L_0045a281:
        call dword ptr [data_00466070]
    L_0045a287:
        test eax,eax
    L_0045a289:
        je short L_0045a293
    L_0045a28b:
        mov dword ptr [data_00477618],edi
    L_0045a291:
        jmp short L_0045a2a8
    L_0045a293:
        call dword ptr [data_0046610c]
    L_0045a299:
        cmp eax,78h
    L_0045a29c:
        jne short L_0045a2a8
    L_0045a29e:
        mov dword ptr [data_00477618],2
    L_0045a2a8:
        mov eax,dword ptr [data_00477618]
    L_0045a2ad:
        cmp eax,2
    L_0045a2b0:
        je asm_target_0045a3a0
    L_0045a2b6:
        cmp eax,esi
    L_0045a2b8:
        je asm_target_0045a3a0
    L_0045a2be:
        cmp eax,1
    L_0045a2c1:
        jne asm_target_0045a3c6
    L_0045a2c7:
        mov dword ptr [ebp-24h],esi
    L_0045a2ca:
        mov dword ptr [ebp-20h],esi
    L_0045a2cd:
        cmp dword ptr [ebp+18h],esi
    L_0045a2d0:
        jne short L_0045a2da
    L_0045a2d2:
        mov eax,dword ptr [data_00477664]
    L_0045a2d7:
        mov dword ptr [ebp+18h],eax
    L_0045a2da:
        push esi
    L_0045a2db:
        push esi
    L_0045a2dc:
        push dword ptr [ebp+10h]
    L_0045a2df:
        push dword ptr [ebp+0Ch]
    L_0045a2e2:
        xor eax,eax
    L_0045a2e4:
        cmp dword ptr [ebp+20h],esi
    L_0045a2e7:
        setne al
    L_0045a2ea:
        lea eax,[eax*8+1]
    L_0045a2f1:
        push eax
    L_0045a2f2:
        push dword ptr [ebp+18h]
    L_0045a2f5:
        call dword ptr [data_00466104]
    L_0045a2fb:
        mov edi,eax
    L_0045a2fd:
        mov dword ptr [ebp-28h],edi
    L_0045a300:
        test edi,edi
    L_0045a302:
        je asm_target_0045a3c6
    L_0045a308:
        and dword ptr [ebp-4],0
    L_0045a30c:
        lea ebx,[edi+edi]
    L_0045a30f:
        mov eax,ebx
    L_0045a311:
        add eax,3
    L_0045a314:
        and eax,0FFFFFFFCh
    L_0045a317:
        call asm_chkstk_00458ec0
    L_0045a31c:
        mov dword ptr [ebp-18h],esp
    L_0045a31f:
        mov esi,esp
    L_0045a321:
        mov dword ptr [ebp-2Ch],esi
    L_0045a324:
        push ebx
    L_0045a325:
        push 0
    L_0045a327:
        push esi
    L_0045a328:
        call asm_memset_0045bed0
    L_0045a32d:
        add esp,0Ch
    L_0045a330:
        or dword ptr [ebp-4],0FFFFFFFFh
    L_0045a334:
        TH10_REL8(0xeb, 0x0045a334, VA_asm_crtGetStringTypeA_part_0045a34b)
        _emit 0x33
        _emit 0xc0
        _emit 0x40
        _emit 0xc3
        _emit 0x8b
        _emit 0x65
        _emit 0xe8
        _emit 0xe8
        _emit 0x4f
        _emit 0xea
        _emit 0xff
        _emit 0xff
        _emit 0x33
        _emit 0xf6
        _emit 0x83
        _emit 0x4d
        _emit 0xfc
        _emit 0xff
        _emit 0x8b
        _emit 0x7d
        _emit 0xd8

    L_0045a34b:
        test esi,esi
    L_0045a34d:
        jne short L_0045a366
    L_0045a34f:
        push edi
    L_0045a350:
        push 2
    L_0045a352:
        call asm_FUN_0045794d_0045794d
    L_0045a357:
        pop ecx
    L_0045a358:
        pop ecx
    L_0045a359:
        mov esi,eax
    L_0045a35b:
        test esi,esi
    L_0045a35d:
        je short L_0045a3c6
    L_0045a35f:
        mov dword ptr [ebp-20h],1
    L_0045a366:
        push edi
    L_0045a367:
        push esi
    L_0045a368:
        push dword ptr [ebp+10h]
    L_0045a36b:
        push dword ptr [ebp+0Ch]
    L_0045a36e:
        push 1
    L_0045a370:
        push dword ptr [ebp+18h]
    L_0045a373:
        call dword ptr [data_00466104]
    L_0045a379:
        test eax,eax
    L_0045a37b:
        je short L_0045a38e
    L_0045a37d:
        push dword ptr [ebp+14h]
    L_0045a380:
        push eax
    L_0045a381:
        push esi
    L_0045a382:
        push dword ptr [ebp+8]
    L_0045a385:
        call dword ptr [data_00466070]
    L_0045a38b:
        mov dword ptr [ebp-24h],eax
    L_0045a38e:
        cmp dword ptr [ebp-20h],0
    L_0045a392:
        je short L_0045a39b
    L_0045a394:
        push esi
    L_0045a395:
        call asm_free_00452422
    L_0045a39a:
        pop ecx
    L_0045a39b:
        mov eax,dword ptr [ebp-24h]
    L_0045a39e:
        jmp short L_0045a40e
    L_0045a3a0:
        mov ebx,dword ptr [ebp+1Ch]
    L_0045a3a3:
        cmp ebx,esi
    L_0045a3a5:
        jne short L_0045a3ad
    L_0045a3a7:
        mov ebx,dword ptr [data_00477654]
    L_0045a3ad:
        mov edi,dword ptr [ebp+18h]
    L_0045a3b0:
        test edi,edi
    L_0045a3b2:
        jne short L_0045a3ba
    L_0045a3b4:
        mov edi,dword ptr [data_00477664]
    L_0045a3ba:
        push ebx
    L_0045a3bb:
        call asm_FUN_004601a1_004601a1
    L_0045a3c0:
        pop ecx
    L_0045a3c1:
        cmp eax,0FFFFFFFFh
    L_0045a3c4:
        jne short L_0045a3ca
    L_0045a3c6:
        xor eax,eax
    L_0045a3c8:
        jmp short L_0045a40e
    L_0045a3ca:
        cmp eax,edi
    L_0045a3cc:
        je short L_0045a3ec
    L_0045a3ce:
        push 0
    L_0045a3d0:
        push 0
    L_0045a3d2:
        lea ecx,[ebp+10h]
    L_0045a3d5:
        push ecx
    L_0045a3d6:
        push dword ptr [ebp+0Ch]
    L_0045a3d9:
        push eax
    L_0045a3da:
        push edi
    L_0045a3db:
        call asm_FUN_004601e8_004601e8
    L_0045a3e0:
        add esp,18h
    L_0045a3e3:
        mov esi,eax
    L_0045a3e5:
        test esi,esi
    L_0045a3e7:
        je short L_0045a3c6
    L_0045a3e9:
        mov dword ptr [ebp+0Ch],esi
    L_0045a3ec:
        push dword ptr [ebp+14h]
    L_0045a3ef:
        push dword ptr [ebp+10h]
    L_0045a3f2:
        push dword ptr [ebp+0Ch]
    L_0045a3f5:
        push dword ptr [ebp+8]
    L_0045a3f8:
        push ebx
    L_0045a3f9:
        call dword ptr [data_00466074]
    L_0045a3ff:
        mov edi,eax
    L_0045a401:
        test esi,esi
    L_0045a403:
        je short L_0045a40c
    L_0045a405:
        push esi
    L_0045a406:
        call asm_free_00452422
    L_0045a40b:
        pop ecx
    L_0045a40c:
        mov eax,edi
    L_0045a40e:
        lea esp,[ebp-38h]
    L_0045a411:
        call asm_SEH_epilog_00454bf7
    L_0045a416:
        ret
    }
}
