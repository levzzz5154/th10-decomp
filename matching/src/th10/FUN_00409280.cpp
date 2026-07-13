// 00409280: FUN_00409280
// Original size: 2432 bytes, actual code: 659 instructions
extern "C" void FUN_00404f30(void);
extern "C" void FUN_0043dc90(void);
extern "C" void FUN_0043e710(void);
extern "C" void FUN_00447ae0(void);
extern "C" void FUN_004489d0(void);
extern "C" void FUN_00449350(void);
extern "C" void FUN_00449870(void);
extern "C" void FUN_00449950(void);

extern "C" __declspec(naked) void FUN_00409280(void) {
    __asm {
        mov  ecx,DWORD PTR [esp+0xc]
        push  ebx
        push  ebp
        mov  ebp,DWORD PTR [esp+0xc]
        mov  eax,DWORD PTR [ebp+0x3744]
        test  al,0x1
        push  esi
        push  edi
        mov  edi,DWORD PTR [esp+0x18]
        jne loc_004092C5
        xor  edx,edx
        or   eax,0x1
        mov  DWORD PTR [ebp+0x3738],edx
        mov  DWORD PTR [ebp+0x3734],0xfff0bdc1
        mov  DWORD PTR [ebp+0x373c],edx
        mov  DWORD PTR [ebp+0x3740],0x476f78
        mov  DWORD PTR [ebp+0x3744],eax
    loc_004092C5:
        xor  eax,eax
        mov  DWORD PTR [ebp+0x3738],eax
        mov  DWORD PTR [ebp+0x373c],eax
        lea  esi,[ebp+0x3748]
        mov  DWORD PTR [ebp+0x3734],0xffffffff
        mov  DWORD PTR [ebp+0x3788],edi
        mov  eax,ecx
        sub  esi,ecx
        nop
    loc_004092F0:
        mov  dl,BYTE PTR [eax]
        mov  BYTE PTR [esi+eax*1],dl
        inc  eax
        test  dl,dl
        jne loc_004092F0
        mov  eax,DWORD PTR [ebp+0x378c]
        mov  edx,DWORD PTR ds:0x477838
        and  eax,0xffffffe7
        or   eax,0x3
        mov  DWORD PTR [ebp+0x378c],eax
        cmp  DWORD PTR [edx+0x10],0x1
        je loc_004093BE
        mov  edx,DWORD PTR ds:0x474c68
        mov  ebx,DWORD PTR ds:0x47783c
        lea  eax,[edi+edi*8]
        mov  edi,DWORD PTR ds:0x474c6c
        lea  edi,[edi+edx*2]
        add  edi,edx
        imul  edi,edi,0x437c
        shl  eax,0x4
        add  edi,eax
        mov  esi,ecx
        lea  edi,[edi+ebx*1+0x5a4]
        lea  ebx,[ebx+0x0]
    loc_00409350:
        mov  dl,BYTE PTR [esi]
        inc  esi
        mov  BYTE PTR [edi],dl
        inc  edi
        test  dl,dl
        jne loc_00409350
        mov  edx,DWORD PTR ds:0x474c68
        mov  esi,DWORD PTR ds:0x474c6c
        lea  esi,[esi+edx*2]
        add  esi,edx
        imul  esi,esi,0x437c
        add  esi,eax
        lea  edx,[esi+ebx*1+0x5a4]
        mov  esi,DWORD PTR [edx+0x84]
        cmp  esi,0x1869f
        jge loc_0040938F
        inc  esi
        mov  DWORD PTR [edx+0x84],esi
    loc_0040938F:
        lea  esi,[eax+ebx*1+0x19a8c]
        mov  edx,esi
        sub  edx,ecx
        lea  ebx,[ebx+0x0]
    loc_004093A0:
        mov  al,BYTE PTR [ecx]
        mov  BYTE PTR [ecx+edx*1],al
        inc  ecx
        test  al,al
        jne loc_004093A0
        mov  eax,DWORD PTR [esi+0x84]
        cmp  eax,0x1869f
        jge loc_004093BE
        inc  eax
        mov  DWORD PTR [esi+0x84],eax
    loc_004093BE:
        xor  esi,esi
        lea  edi,[ebp+0x778]
        jmp loc_004093D0
        nop
        nop
    loc_004093D0:
        mov  ecx,DWORD PTR ds:0x47770c
        mov  ecx,DWORD PTR [ecx+0x9ec8]
        lea  ebx,[esi+0x3a]
        mov  eax,edi
        call FUN_0043e710
        inc  esi
        add  edi,0x3ac
        cmp  esi,0x8
        jl loc_004093D0
        xor  esi,esi
        lea  edi,[ebp+0x24d8]
        lea  ebx,[ebx+0x0]
    loc_00409400:
        mov  edx,DWORD PTR ds:0x47770c
        mov  ecx,DWORD PTR [edx+0x9ec8]
        lea  ebx,[esi+0x42]
        mov  eax,edi
        call FUN_0043e710
        inc  esi
        add  edi,0x3ac
        cmp  esi,0x5
        jl loc_00409400
        mov  eax,ds:0x4776e0
        mov  esi,DWORD PTR ds:0x491c10
        mov  ebx,DWORD PTR [eax+0x8994]
        call FUN_00449950
        mov  edi,eax
        mov  eax,DWORD PTR [edi+0x35c]
        push  0x1
        or   eax,0x40000000
        push  edi
        mov  ecx,ebx
        mov  DWORD PTR [edi+0x20],0xf
        mov  DWORD PTR [edi+0x35c],eax
        call FUN_00449870
        mov  esi,DWORD PTR ds:0x491c10
        lea  eax,[edi+0x4]
        xor  ebx,ebx
        mov  DWORD PTR [eax],edi
        mov  DWORD PTR [eax+0x4],ebx
        mov  DWORD PTR [eax+0x8],ebx
        cmp  DWORD PTR [esi+0x72dad4],ebx
        jne loc_0040947F
        mov  DWORD PTR [esi+0x72dad4],eax
        jmp loc_0040949B
    loc_0040947F:
        mov  ecx,DWORD PTR [esi+0x72dad8]
        mov  edx,DWORD PTR [ecx+0x4]
        cmp  edx,ebx
        je loc_00409495
        mov  DWORD PTR [eax+0x4],edx
        mov  edx,DWORD PTR [ecx+0x4]
        mov  DWORD PTR [edx+0x8],eax
    loc_00409495:
        mov  DWORD PTR [ecx+0x4],eax
        mov  DWORD PTR [eax+0x8],ecx
    loc_0040949B:
        mov  DWORD PTR [esi+0x72dad8],eax
        mov  ecx,DWORD PTR [esi+0x732454]
        inc  ecx
        mov  eax,ecx
        cmp  eax,ebx
        mov  DWORD PTR [esi+0x732454],ecx
        jne loc_004094BB
        inc  eax
        mov  DWORD PTR [esi+0x732454],eax
    loc_004094BB:
        mov  eax,DWORD PTR [esi+0x732454]
        mov  ecx,DWORD PTR ds:0x4776e0
        mov  DWORD PTR [edi],eax
        mov  eax,DWORD PTR [esi+0x732454]
        mov  DWORD PTR [ebp+0x768],eax
        mov  ebx,DWORD PTR [ecx+0x899c]
        call FUN_00449950
        mov  edi,eax
        mov  ecx,DWORD PTR [edi+0x35c]
        or   ecx,0x40000000
        push  0x48
        mov  DWORD PTR [edi+0x35c],ecx
        push  edi
        mov  ecx,ebx
        mov  DWORD PTR [edi+0x20],0xf
        call FUN_00449870
        mov  esi,DWORD PTR ds:0x491c10
        lea  eax,[edi+0x4]
        xor  ecx,ecx
        mov  DWORD PTR [eax],edi
        mov  DWORD PTR [eax+0x4],ecx
        mov  DWORD PTR [eax+0x8],ecx
        cmp  DWORD PTR [esi+0x72dad4],ecx
        jne loc_00409528
        mov  DWORD PTR [esi+0x72dad4],eax
        jmp loc_00409544
    loc_00409528:
        mov  ecx,DWORD PTR [esi+0x72dad8]
        mov  edx,DWORD PTR [ecx+0x4]
        test  edx,edx
        je loc_0040953E
        mov  DWORD PTR [eax+0x4],edx
        mov  edx,DWORD PTR [ecx+0x4]
        mov  DWORD PTR [edx+0x8],eax
    loc_0040953E:
        mov  DWORD PTR [ecx+0x4],eax
        mov  DWORD PTR [eax+0x8],ecx
    loc_00409544:
        mov  DWORD PTR [esi+0x72dad8],eax
        mov  ecx,DWORD PTR [esi+0x732454]
        inc  ecx
        xor  ebx,ebx
        mov  eax,ecx
        cmp  eax,ebx
        mov  DWORD PTR [esi+0x732454],ecx
        jne loc_00409566
        inc  eax
        mov  DWORD PTR [esi+0x732454],eax
    loc_00409566:
        mov  eax,DWORD PTR [esi+0x732454]
        mov  ecx,DWORD PTR ds:0x4776e0
        mov  DWORD PTR [edi],eax
        mov  eax,DWORD PTR [esi+0x732454]
        mov  DWORD PTR [ebp+0x76c],eax
        mov  edi,DWORD PTR [ecx+0x8994]
        call FUN_00449950
        mov  esi,eax
        mov  edx,DWORD PTR [esi+0x35c]
        push  0x2
        or   edx,0x40000000
        push  esi
        mov  ecx,edi
        mov  DWORD PTR [esi+0x20],0xf
        mov  DWORD PTR [esi+0x35c],edx
        call FUN_00449870
        mov  ecx,DWORD PTR ds:0x491c10
        lea  eax,[esi+0x4]
        mov  DWORD PTR [eax],esi
        mov  DWORD PTR [eax+0x4],ebx
        mov  DWORD PTR [eax+0x8],ebx
        cmp  DWORD PTR [ecx+0x72dad4],ebx
        jne loc_004095D1
        mov  DWORD PTR [ecx+0x72dad4],eax
        jmp loc_004095ED
    loc_004095D1:
        mov  edx,DWORD PTR [ecx+0x72dad8]
        mov  edi,DWORD PTR [edx+0x4]
        cmp  edi,ebx
        je loc_004095E7
        mov  DWORD PTR [eax+0x4],edi
        mov  edi,DWORD PTR [edx+0x4]
        mov  DWORD PTR [edi+0x8],eax
    loc_004095E7:
        mov  DWORD PTR [edx+0x4],eax
        mov  DWORD PTR [eax+0x8],edx
    loc_004095ED:
        mov  DWORD PTR [ecx+0x72dad8],eax
        mov  edx,DWORD PTR [ecx+0x732454]
        inc  edx
        mov  eax,edx
        cmp  eax,ebx
        mov  DWORD PTR [ecx+0x732454],edx
        jne loc_0040960D
        inc  eax
        mov  DWORD PTR [ecx+0x732454],eax
    loc_0040960D:
        mov  edx,DWORD PTR [ecx+0x732454]
        mov  DWORD PTR [esi],edx
        mov  eax,DWORD PTR [ecx+0x732454]
        mov  DWORD PTR [ebp+0x770],eax
        mov  edx,DWORD PTR [ebp+0x76c]
        cmp  edx,ebx
        jne loc_0040962F
    loc_0040962B:
        xor  eax,eax
        jmp loc_0040966E
    loc_0040962F:
        mov  eax,DWORD PTR [ecx+0x72dad4]
        cmp  eax,ebx
        je loc_0040964D
        nop
    loc_00409640:
        mov  esi,DWORD PTR [eax]
        cmp  DWORD PTR [esi],edx
        je loc_00409668
        mov  eax,DWORD PTR [eax+0x4]
        cmp  eax,ebx
        jne loc_00409640
    loc_0040964D:
        mov  eax,DWORD PTR [ecx+0x72dadc]
        cmp  eax,ebx
        je loc_0040962B
    loc_00409657:
        mov  esi,DWORD PTR [eax]
        cmp  DWORD PTR [esi],edx
        je loc_00409668
        mov  eax,DWORD PTR [eax+0x4]
        cmp  eax,ebx
        jne loc_00409657
        xor  eax,eax
        jmp loc_0040966E
    loc_00409668:
        mov  eax,DWORD PTR [eax]
        cmp  eax,ebx
        jne loc_00409674
    loc_0040966E:
        mov  DWORD PTR [ebp+0x76c],ebx
    loc_00409674:
        mov  edx,DWORD PTR [esp+0x1c]
        push  edx
        push  0xffffff
        push  ecx
        mov  esi,eax
        call FUN_00447ae0
        add  esp,0xc
        push  ebx
        mov  edi,0xe
        mov  ecx,0x492590
        call FUN_0043dc90
        mov  eax,ds:0x4776f0
        mov  esi,DWORD PTR ds:0x491c10
        mov  edi,DWORD PTR [eax+0x3e0b50]
        call FUN_00449950
        mov  esi,eax
        mov  ecx,DWORD PTR [esi+0x35c]
        or   ecx,0x40000000
        push  0x1a1
        mov  DWORD PTR [esi+0x35c],ecx
        push  esi
        mov  ecx,edi
        mov  DWORD PTR [esi+0x20],0xf
        call FUN_00449870
        mov  edi,DWORD PTR ds:0x491c10
        lea  eax,[esi+0x4]
        mov  DWORD PTR [eax],esi
        mov  DWORD PTR [eax+0x4],ebx
        mov  DWORD PTR [eax+0x8],ebx
        cmp  DWORD PTR [edi+0x72dad4],ebx
        jne loc_004096F8
        mov  DWORD PTR [edi+0x72dad4],eax
        jmp loc_00409714
    loc_004096F8:
        mov  ecx,DWORD PTR [edi+0x72dad8]
        mov  edx,DWORD PTR [ecx+0x4]
        cmp  edx,ebx
        je loc_0040970E
        mov  DWORD PTR [eax+0x4],edx
        mov  edx,DWORD PTR [ecx+0x4]
        mov  DWORD PTR [edx+0x8],eax
    loc_0040970E:
        mov  DWORD PTR [ecx+0x4],eax
        mov  DWORD PTR [eax+0x8],ecx
    loc_00409714:
        mov  DWORD PTR [edi+0x72dad8],eax
        mov  ecx,DWORD PTR [edi+0x732454]
        inc  ecx
        mov  eax,ecx
        cmp  eax,ebx
        mov  DWORD PTR [edi+0x732454],ecx
        jne loc_00409734
        inc  eax
        mov  DWORD PTR [edi+0x732454],eax
    loc_00409734:
        mov  eax,DWORD PTR [edi+0x732454]
        mov  ecx,DWORD PTR ds:0x477704
        mov  DWORD PTR [esi],eax
        mov  eax,DWORD PTR [edi+0x732454]
        mov  DWORD PTR [ebp+0x774],eax
        mov  edx,DWORD PTR [ecx+0x10]
        add  edx,0x1068
        mov  ebx,DWORD PTR [edx]
        lea  esi,[ebp+0x379c]
        mov  ecx,esi
        mov  DWORD PTR [ecx],ebx
        mov  ebx,DWORD PTR [edx+0x4]
        mov  DWORD PTR [ecx+0x4],ebx
        mov  edx,DWORD PTR [edx+0x8]
        mov  DWORD PTR [ecx+0x8],edx
        push  eax
        mov  edx,edi
        call FUN_00449350
        mov  ecx,DWORD PTR [ebp+0x774]
        xor  esi,esi
        cmp  ecx,esi
        jne loc_00409787
    loc_00409783:
        xor  eax,eax
        jmp loc_004097BF
    loc_00409787:
        mov  eax,DWORD PTR [edi+0x72dad4]
        cmp  eax,esi
        je loc_0040979E
    loc_00409791:
        mov  edx,DWORD PTR [eax]
        cmp  DWORD PTR [edx],ecx
        je loc_004097B9
        mov  eax,DWORD PTR [eax+0x4]
        cmp  eax,esi
        jne loc_00409791
    loc_0040979E:
        mov  eax,DWORD PTR [edi+0x72dadc]
        cmp  eax,esi
        je loc_00409783
    loc_004097A8:
        mov  edx,DWORD PTR [eax]
        cmp  DWORD PTR [edx],ecx
        je loc_004097B9
        mov  eax,DWORD PTR [eax+0x4]
        cmp  eax,esi
        jne loc_004097A8
        xor  eax,eax
        jmp loc_004097BF
    loc_004097B9:
        mov  eax,DWORD PTR [eax]
        cmp  eax,esi
        jne loc_004097C5
    loc_004097BF:
        mov  DWORD PTR [ebp+0x774],esi
    loc_004097C5:
        add  eax,0x10
        cmp  eax,esi
        je loc_004097E3
        mov  ecx,0x19f
    loc_004097D1:
        mov  edx,DWORD PTR [eax]
        cmp  WORD PTR [edx+0x38a],cx
        je loc_004097FD
        mov  eax,DWORD PTR [eax+0x4]
        cmp  eax,esi
        jne loc_004097D1
    loc_004097E3:
        xor  eax,eax
    loc_004097E5:
        mov  edx,DWORD PTR [esp+0x20]
        mov  DWORD PTR [eax+0x314],edx
        mov  ecx,DWORD PTR [ebp+0x774]
        cmp  ecx,esi
        jne loc_00409801
    loc_004097F9:
        xor  eax,eax
        jmp loc_0040983E
    loc_004097FD:
        mov  eax,DWORD PTR [eax]
        jmp loc_004097E5
    loc_00409801:
        mov  eax,DWORD PTR [edi+0x72dad4]
        cmp  eax,esi
        je loc_0040981D
        jmp loc_00409810
        nop
    loc_00409810:
        mov  ebx,DWORD PTR [eax]
        cmp  DWORD PTR [ebx],ecx
        je loc_00409838
        mov  eax,DWORD PTR [eax+0x4]
        cmp  eax,esi
        jne loc_00409810
    loc_0040981D:
        mov  eax,DWORD PTR [edi+0x72dadc]
        cmp  eax,esi
        je loc_004097F9
    loc_00409827:
        mov  ebx,DWORD PTR [eax]
        cmp  DWORD PTR [ebx],ecx
        je loc_00409838
        mov  eax,DWORD PTR [eax+0x4]
        cmp  eax,esi
        jne loc_00409827
        xor  eax,eax
        jmp loc_0040983E
    loc_00409838:
        mov  eax,DWORD PTR [eax]
        cmp  eax,esi
        jne loc_00409844
    loc_0040983E:
        mov  DWORD PTR [ebp+0x774],esi
    loc_00409844:
        add  eax,0x10
        cmp  eax,esi
        je loc_00409866
        mov  ecx,0x1a0
    loc_00409850:
        mov  ebx,DWORD PTR [eax]
        cmp  WORD PTR [ebx+0x38a],cx
        je loc_00409903
        mov  eax,DWORD PTR [eax+0x4]
        cmp  eax,esi
        jne loc_00409850
    loc_00409866:
        xor  eax,eax
    loc_00409868:
        mov  DWORD PTR [eax+0x314],edx
        mov  DWORD PTR [ebp+0x3798],edx
        mov  eax,ds:0x474c7c
        lea  eax,[eax+eax*2+0xa]
        imul  eax,DWORD PTR ds:0x474c4c
        lea  eax,[eax+eax*4]
        shl  eax,1
        cmp  eax,0x5f5e100
        mov  DWORD PTR [ebp+0x3790],eax
        mov  DWORD PTR [ebp+0x3794],eax
        jl loc_004098A6
        mov  DWORD PTR [ebp+0x3794],0x5f5e0ff
    loc_004098A6:
        mov  eax,ds:0x4776f0
        mov  ebx,DWORD PTR [eax+0x3e0b50]
        mov  esi,edi
        call FUN_00449950
        mov  esi,eax
        mov  ecx,DWORD PTR [esi+0x35c]
        or   ecx,0x40000000
        push  0x1ab
        mov  DWORD PTR [esi+0x35c],ecx
        push  esi
        mov  ecx,ebx
        mov  DWORD PTR [esi+0x20],0xf
        call FUN_00449870
        mov  ecx,DWORD PTR ds:0x491c10
        lea  eax,[esi+0x4]
        xor  ebx,ebx
        mov  DWORD PTR [eax],esi
        mov  DWORD PTR [eax+0x4],ebx
        mov  DWORD PTR [eax+0x8],ebx
        cmp  DWORD PTR [ecx+0x72dad4],ebx
        jne loc_0040990A
        mov  DWORD PTR [ecx+0x72dad4],eax
        jmp loc_00409926
    loc_00409903:
        mov  eax,DWORD PTR [eax]
        jmp loc_00409868
    loc_0040990A:
        mov  edx,DWORD PTR [ecx+0x72dad8]
        mov  edi,DWORD PTR [edx+0x4]
        cmp  edi,ebx
        je loc_00409920
        mov  DWORD PTR [eax+0x4],edi
        mov  edi,DWORD PTR [edx+0x4]
        mov  DWORD PTR [edi+0x8],eax
    loc_00409920:
        mov  DWORD PTR [edx+0x4],eax
        mov  DWORD PTR [eax+0x8],edx
    loc_00409926:
        mov  DWORD PTR [ecx+0x72dad8],eax
        mov  edx,DWORD PTR [ecx+0x732454]
        inc  edx
        mov  eax,edx
        cmp  eax,ebx
        mov  DWORD PTR [ecx+0x732454],edx
        jne loc_00409946
        inc  eax
        mov  DWORD PTR [ecx+0x732454],eax
    loc_00409946:
        mov  ecx,DWORD PTR [ecx+0x732454]
        mov  DWORD PTR [esi],ecx
        mov  eax,ds:0x474c7c
        dec  eax
        cmp  eax,0x6
        ja loc_00409BDC
        jmp  DWORD PTR [eax*4+0x409be4]
        mov  edx,DWORD PTR ds:0x477704
        mov  eax,DWORD PTR [edx+0x38]
        push  eax
        lea  esi,[ebp+0x10]
        mov  eax,0xc
        call FUN_00404f30
        mov  ecx,DWORD PTR ds:0x477704
        mov  edx,DWORD PTR [ecx+0x38]
        lea  esi,[ebp+0x3bc]
        push  edx
        mov  eax,0xb
        call FUN_00404f30
        cmp  DWORD PTR [esp+0x18],0x2
        mov  esi,DWORD PTR ds:0x491c10
        jl loc_004099B6
        mov  eax,ds:0x477704
        mov  edi,DWORD PTR [eax+0x38]
        call FUN_00449950
        push  0xe
        jmp loc_00409BB0
    loc_004099B6:
        mov  ecx,DWORD PTR ds:0x477704
        mov  edi,DWORD PTR [ecx+0x38]
        call FUN_00449950
        push  0xf
        jmp loc_00409BB0
        mov  edx,DWORD PTR ds:0x477704
        mov  eax,DWORD PTR [edx+0x38]
        push  eax
        lea  esi,[ebp+0x10]
        mov  eax,0xe
        call FUN_00404f30
        mov  ecx,DWORD PTR ds:0x477704
        mov  edx,DWORD PTR [ecx+0x38]
        lea  esi,[ebp+0x3bc]
        push  edx
        mov  eax,0xf
        call FUN_00404f30
        mov  eax,ds:0x477704
        mov  esi,DWORD PTR ds:0x491c10
        mov  edi,DWORD PTR [eax+0x38]
        call FUN_00449950
        push  0x11
        jmp loc_00409BB0
        mov  ecx,DWORD PTR ds:0x477704
        mov  edx,DWORD PTR [ecx+0x38]
        lea  esi,[ebp+0x10]
        push  edx
        mov  eax,0x12
        call FUN_00404f30
        mov  eax,ds:0x477704
        mov  ecx,DWORD PTR [eax+0x38]
        lea  esi,[ebp+0x3bc]
        push  ecx
        mov  eax,0x13
        call FUN_00404f30
        mov  edx,DWORD PTR ds:0x477704
        mov  esi,DWORD PTR ds:0x491c10
        mov  edi,DWORD PTR [edx+0x38]
        call FUN_00449950
        push  0x15
        jmp loc_00409BB0
        mov  eax,ds:0x477704
        mov  ecx,DWORD PTR [eax+0x38]
        lea  esi,[ebp+0x10]
        push  ecx
        mov  eax,0x13
        call FUN_00404f30
        mov  edx,DWORD PTR ds:0x477704
        mov  eax,DWORD PTR [edx+0x38]
        push  eax
        lea  esi,[ebp+0x3bc]
        mov  eax,0x14
        call FUN_00404f30
        mov  ecx,DWORD PTR ds:0x477704
        mov  esi,DWORD PTR ds:0x491c10
        mov  edi,DWORD PTR [ecx+0x38]
        call FUN_00449950
        push  0x16
        jmp loc_00409BB0
        mov  edx,DWORD PTR ds:0x477704
        mov  eax,DWORD PTR [edx+0x38]
        push  eax
        lea  esi,[ebp+0x10]
        mov  eax,0xc
        call FUN_00404f30
        mov  ecx,DWORD PTR ds:0x477704
        mov  edx,DWORD PTR [ecx+0x38]
        lea  esi,[ebp+0x3bc]
        push  edx
        mov  eax,0xd
        call FUN_00404f30
        mov  eax,ds:0x477704
        mov  esi,DWORD PTR ds:0x491c10
        mov  edi,DWORD PTR [eax+0x38]
        call FUN_00449950
        push  0xf
        jmp loc_00409BB0
        mov  ecx,DWORD PTR ds:0x477704
        mov  edx,DWORD PTR [ecx+0x38]
        lea  esi,[ebp+0x10]
        push  edx
        mov  eax,0x21
        call FUN_00404f30
        mov  eax,ds:0x477704
        mov  ecx,DWORD PTR [eax+0x38]
        lea  esi,[ebp+0x3bc]
        push  ecx
        mov  eax,0x22
        call FUN_00404f30
        mov  edx,DWORD PTR ds:0x477704
        mov  esi,DWORD PTR ds:0x491c10
        mov  edi,DWORD PTR [edx+0x38]
        call FUN_00449950
        push  0x24
        jmp loc_00409BB0
        cmp  DWORD PTR ds:0x474c84,0x18
        mov  eax,ds:0x477704
        mov  ecx,DWORD PTR [eax+0x38]
        lea  esi,[ebp+0x10]
        push  ecx
        jge loc_00409B76
        mov  eax,0x26
        call FUN_00404f30
        mov  edx,DWORD PTR ds:0x477704
        mov  esi,DWORD PTR ds:0x491c10
        mov  edi,DWORD PTR [edx+0x38]
        call FUN_00449950
        push  0x28
        jmp loc_00409BB0
    loc_00409B76:
        mov  eax,0x1b
        call FUN_00404f30
        mov  edx,DWORD PTR ds:0x477704
        mov  eax,DWORD PTR [edx+0x38]
        push  eax
        lea  esi,[ebp+0x3bc]
        mov  eax,0x1c
        call FUN_00404f30
        mov  ecx,DWORD PTR ds:0x477704
        mov  esi,DWORD PTR ds:0x491c10
        mov  edi,DWORD PTR [ecx+0x38]
        call FUN_00449950
        push  0x1e
    loc_00409BB0:
        mov  esi,eax
        or   DWORD PTR [esi+0x35c],0x40000000
        mov  ecx,edi
        push  esi
        mov  DWORD PTR [esi+0x20],0xf
        call FUN_00449870
        mov  edx,DWORD PTR ds:0x491c10
        lea  eax,[esp+0x1c]
        mov  ebx,esi
        call FUN_004489d0
    loc_00409BDC:
        pop  edi
        pop  esi
        pop  ebp
        pop  ebx
        ret  0x10
    }
}
