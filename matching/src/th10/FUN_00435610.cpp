// 00435610: FUN_00435610
// Original size: 224 bytes, actual code: 55 instructions
extern "C" void FUN_00452730(void);
extern "C" void _strrchr(void);

extern "C" __declspec(naked) void FUN_00435610(void) {
    __asm {
        push  esi
        push  edi
        mov  esi,eax
        push  0x3a
        push  esi
        mov  edi,ecx
        call FUN_00452730
        add  esp,0x8
        test  eax,eax
        je loc_0043563D
        mov  eax,esi
        sub  edi,esi
        nop
    loc_00435630:
        mov  cl,BYTE PTR [eax]
        mov  BYTE PTR [edi+eax*1],cl
        inc  eax
        test  cl,cl
        jne loc_00435630
        pop  edi
        pop  esi
        ret
    loc_0043563D:
        push  0x104
        push  edi
        push  0x0
        call  DWORD PTR ds:0x4660dc
        push  0x5c
        push  edi
        call _strrchr
        add  esp,0x8
        test  eax,eax
        jne loc_0043565C
        mov  BYTE PTR [edi],al
    loc_0043565C:
        mov  BYTE PTR [eax+0x1],0x0
        mov  eax,esi
        mov  ecx,esi
    loc_00435664:
        mov  dl,BYTE PTR [eax]
        inc  eax
        test  dl,dl
        jne loc_00435664
        sub  eax,ecx
        mov  esi,ecx
        dec  edi
    loc_00435670:
        mov  cl,BYTE PTR [edi+0x1]
        inc  edi
        test  cl,cl
        jne loc_00435670
        mov  ecx,eax
        shr  ecx,0x2
        rep movsd
        mov  ecx,eax
        and  ecx,0x3
        rep movs BYTE PTR es:[edi],BYTE PTR ds:[esi]
        pop  edi
        pop  esi
        ret
    }
}
