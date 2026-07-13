// 004315C0: FUN_004315c0
// Original size: 1504 bytes, actual code: 380 instructions
extern "C" void FUN_00409e50(void);
extern "C" void FUN_0040ace0(void);
extern "C" void FUN_0040ad20(void);
extern "C" void FUN_0040c540(void);
extern "C" void FUN_00420c30(void);
extern "C" void FUN_004294a0(void);
extern "C" void FUN_004296f0(void);
extern "C" void FUN_0042c5c0(void);
extern "C" void FUN_0042c620(void);
extern "C" void FUN_0042c670(void);
extern "C" void FUN_0042c6d0(void);
extern "C" void FUN_0042c770(void);
extern "C" void FUN_0043c8b0(void);
extern "C" void FUN_0043dc90(void);
extern "C" void FUN_00448d00(void);
extern "C" void FUN_004491c0(void);
extern "C" void FUN_0044be20(void);
extern "C" void FUN_0044be70(void);
extern "C" void FUN_0044bea0(void);
extern "C" void _free(void);
extern "C" void FUN_00452abc(void);
extern "C" void _sprintf(void);
extern "C" void FUN_00453111(void);
extern "C" void __security_check_cookie(void);

extern "C" __declspec(naked) void FUN_004315c0(void) {
    __asm {
        sub  esp,0x188
        mov  eax,ds:0x473660
        xor  eax,esp
        push  ebp
        mov  ebp,DWORD PTR [esp+0x190]
        mov  DWORD PTR [esp+0x188],eax
        mov  eax,DWORD PTR [ebp+0x20]
        cmp  eax,0x5
        ja loc_00431B5D
        push  ebx
        push  esi
        push  edi
        jmp  DWORD PTR [eax*4+0x431b7c]
        mov  ecx,DWORD PTR ds:0x491c04
        lea  edx,[ebp+0x24]
        mov  DWORD PTR [ebp+0x2c],0x19
        call FUN_0040ad20
        mov  eax,DWORD PTR [ebp+0x43c]
        mov  edx,DWORD PTR ds:0x491c10
        xor  ebx,ebx
        push  eax
        mov  DWORD PTR ds:0x491c04,ebx
        call FUN_004491c0
        test  eax,eax
        jne loc_00431652
        push  ebp
        mov  edi,0x5e
        call FUN_0042c670
        mov  ecx,DWORD PTR ds:0x4776e0
        mov  eax,DWORD PTR [ecx+0x8994]
        push  0xf
        push  0x8
        push  eax
        lea  edi,[esp+0x1c]
        call FUN_00448d00
        mov  edx,DWORD PTR [eax]
        mov  DWORD PTR [ebp+0x5d0],edx
    loc_00431652:
        push  ebp
        mov  edi,0x65
        call FUN_0042c670
        mov  ecx,0x1
        mov  eax,ebp
        call FUN_0042c620
        lea  edx,[ebp+0x59e4]
        mov  ecx,0x32
        xor  eax,eax
        mov  edi,edx
        rep stosd
        mov  esi,0x1
        mov  edi,edx
    loc_00431681:
        push  esi
        lea  eax,[esp+0x158]
        push  0x46e0c8
        push  eax
        call _sprintf
        add  esp,0xc
        lea  ecx,[esp+0x154]
        push  ecx
        call FUN_004296f0
        mov  DWORD PTR [edi],eax
        inc  esi
        add  edi,0x4
        cmp  esi,0x19
        jle loc_00431681
        push  0x46e650
        call FUN_00452abc
        push  0x46e650
        call FUN_00453111
        add  esp,0x8
        lea  edx,[esp+0x14]
        push  edx
        push  0x46efec
        call  DWORD PTR ds:0x4660a0
        mov  edi,eax
        cmp  edi,0xffffffff
        je loc_00431731
        mov  ebx,0x19
        lea  esi,[ebp+0x5a48]
        jmp loc_004316F0
        lea  ebx,[ebx+0x0]
    loc_004316F0:
        push  0x46efe8
        call FUN_00453111
        add  esp,0x4
        lea  eax,[esp+0x40]
        push  eax
        call FUN_004296f0
        push  0x46e650
        mov  DWORD PTR [esi],eax
        call FUN_00453111
        add  esp,0x4
        lea  ecx,[esp+0x14]
        push  ecx
        push  edi
        call  DWORD PTR ds:0x4660a4
        test  eax,eax
        je loc_0043172F
        inc  ebx
        add  esi,0x4
        cmp  ebx,0x32
        jl loc_004316F0
    loc_0043172F:
        xor  ebx,ebx
    loc_00431731:
        push  edi
        call  DWORD PTR ds:0x4660a8
        push  0x46efe8
        call FUN_00453111
        add  esp,0x4
        mov  DWORD PTR [ebp+0x59d8],ebx
        jmp loc_0043174F
        xor  ebx,ebx
    loc_0043174F:
        cmp  DWORD PTR [ebp+0x2b4],0x6
        jle loc_00431B5A
        mov  DWORD PTR [ebp+0x20],0x2
        mov  eax,DWORD PTR [ebp+0x2c0]
        test  al,0x1
        jne loc_00431796
        or   eax,0x1
        mov  DWORD PTR [ebp+0x2b4],ebx
        mov  DWORD PTR [ebp+0x2b0],0xfff0bdc1
        mov  DWORD PTR [ebp+0x2b8],ebx
        mov  DWORD PTR [ebp+0x2bc],0x476f78
        mov  DWORD PTR [ebp+0x2c0],eax
    loc_00431796:
        mov  DWORD PTR [ebp+0x2b4],ebx
        mov  DWORD PTR [ebp+0x2b8],ebx
        mov  DWORD PTR [ebp+0x2b0],0xffffffff
        jmp loc_00431B5A
        mov  edx,DWORD PTR [ebp+0x24]
        lea  esi,[ebp+0x24]
        mov  DWORD PTR [esi+0x4],edx
        mov  cl,BYTE PTR ds:0x474e36
        mov  al,0x10
        test  al,cl
        jne loc_004317CE
        test  BYTE PTR ds:0x474e34,al
        je loc_004317D7
    loc_004317CE:
        push  0xffffffff
        mov  eax,esi
        call FUN_0044bea0
    loc_004317D7:
        mov  cl,BYTE PTR ds:0x474e36
        mov  al,0x20
        test  al,cl
        jne loc_004317EB
        test  BYTE PTR ds:0x474e34,al
        je loc_004317F4
    loc_004317EB:
        push  0x1
        mov  eax,esi
        call FUN_0044bea0
    loc_004317F4:
        mov  eax,DWORD PTR [esi+0x4]
        cmp  eax,DWORD PTR [esi]
        je loc_0043180C
        push  0x0
        mov  edi,0xc
        mov  ecx,0x492590
        call FUN_0043dc90
    loc_0043180C:
        mov  eax,ds:0x474e36
        test  al,0xa
        je loc_00431837
        mov  ecx,0x5
    loc_0043181A:
        mov  eax,ebp
        call FUN_0042c620
        push  0x0
        mov  edi,0xb
        mov  ecx,0x492590
        call FUN_0043dc90
        jmp loc_00431B5A
    loc_00431837:
        test  eax,0x1001
        je loc_00431B5A
        mov  ecx,DWORD PTR [esi]
        mov  eax,DWORD PTR [ebp+ecx*4+0x59e4]
        test  eax,eax
        je loc_00431B5A
        mov  ecx,0x4
        mov  eax,ebp
        call FUN_0042c620
        mov  edx,DWORD PTR [esi]
        mov  eax,esi
        mov  DWORD PTR [ebp+0x59dc],edx
        call FUN_0044be20
        push  0x0
        mov  edi,0xa
        mov  ecx,0x492590
        call FUN_0043dc90
        mov  DWORD PTR [ebp+0x2c],0x7
        mov  eax,DWORD PTR [esi+0x8]
        test  eax,eax
        je loc_0043189A
        jg loc_00431894
        dec  eax
        mov  DWORD PTR [esi],eax
        jmp loc_004318A0
    loc_00431894:
        xor  eax,eax
        mov  DWORD PTR [esi],eax
        jmp loc_004318A0
    loc_0043189A:
        mov  DWORD PTR [esi],0x0
    loc_004318A0:
        xor  ecx,ecx
        xor  eax,eax
        jmp loc_004318B0
        nop
        nop
    loc_004318B0:
        mov  edx,DWORD PTR [ebp+0x59dc]
        mov  edx,DWORD PTR [ebp+edx*4+0x59e4]
        mov  edi,DWORD PTR [edx+eax*1+0xd4]
        test  edi,edi
        jne loc_004318DB
        mov  edx,DWORD PTR [esi+0xd4]
        mov  DWORD PTR [esi+edx*4+0x90],ecx
        inc  DWORD PTR [esi+0xd4]
    loc_004318DB:
        add  eax,0x24
        inc  ecx
        cmp  eax,0xfc
        jl loc_004318B0
        push  0xffffffff
        mov  eax,esi
        call FUN_0044bea0
        push  0x1
        mov  eax,esi
        call FUN_0044bea0
        jmp loc_00431B5A
        cmp  DWORD PTR [ebp+0x2b4],0xf
        jl loc_00431B5A
        mov  eax,DWORD PTR [ebp+0x24]
        lea  esi,[ebp+0x24]
        mov  DWORD PTR [esi+0x4],eax
        mov  eax,0x10
        mov  ecx,0x474e30
        call FUN_0040ace0
        test  ax,ax
        je loc_00431930
        push  0xffffffff
        mov  eax,esi
        call FUN_0044bea0
    loc_00431930:
        mov  eax,0x20
        mov  ecx,0x474e30
        call FUN_0040ace0
        test  ax,ax
        je loc_0043194D
        push  0x1
        mov  eax,esi
        call FUN_0044bea0
    loc_0043194D:
        mov  ecx,DWORD PTR [esi+0x4]
        cmp  ecx,DWORD PTR [esi]
        je loc_00431965
        push  0x0
        mov  edi,0xc
        mov  ecx,0x492590
        call FUN_0043dc90
    loc_00431965:
        mov  eax,ds:0x474e36
        test  al,0xa
        je loc_00431990
        mov  eax,esi
        call FUN_0044be70
        mov  DWORD PTR [ebp+0x2c],0x19
        mov  DWORD PTR [ebp+0xf8],0x0
        mov  ecx,0x2
        jmp loc_0043181A
    loc_00431990:
        test  eax,0x1001
        je loc_00431B5A
        mov  edx,DWORD PTR [esi]
        mov  ecx,0x3
        mov  eax,ebp
        mov  DWORD PTR [ebp+0x59e0],edx
        call FUN_0042c620
        jmp loc_00431B5A
        mov  eax,DWORD PTR [ebp+0x2b4]
        mov  edi,0x2
        cmp  eax,edi
        jne loc_004319EC
        push  0x0
        push  0x0
        push  0x0
        push  0x20
        push  0x5
        mov  ebx,0x2b
        call FUN_0043c8b0
        mov  esi,DWORD PTR ds:0x4776e0
        push  0x43c40000
        push  0x43f00000
        call FUN_0040c540
    loc_004319EC:
        cmp  DWORD PTR [ebp+0x2b4],0x20
        jl loc_00431B5A
        mov  ecx,0x3
        mov  eax,ebp
        call FUN_0042c5c0
        mov  eax,DWORD PTR [ebp+0x59e0]
        inc  eax
        lea  ecx,[eax+eax*2]
        shl  ecx,0x4
        add  ecx,0x474788
        push  0x40c00000
        mov  DWORD PTR ds:0x477848,ecx
        mov  ds:0x474c7c,eax
        mov  ds:0x474c80,eax
        call FUN_00420c30
        mov  DWORD PTR ds:0x491fb8,0xc
        mov  edx,DWORD PTR [ebp+0x59dc]
        mov  eax,DWORD PTR [ebp+edx*4+0x59e4]
        add  eax,0x1d4
        mov  edx,0x477710
    loc_00431A53:
        mov  cl,BYTE PTR [eax]
        inc  eax
        mov  BYTE PTR [edx],cl
        inc  edx
        test  cl,cl
        jne loc_00431A53
        mov  eax,DWORD PTR [ebp+0x59dc]
        mov  ecx,DWORD PTR [ebp+eax*4+0x59e4]
        mov  eax,DWORD PTR [ecx+0x18]
        mov  edx,DWORD PTR [eax+0x50]
        mov  DWORD PTR ds:0x474c68,edx
        mov  ecx,DWORD PTR [eax+0x54]
        mov  DWORD PTR ds:0x474c6c,ecx
        mov  edx,DWORD PTR [eax+0x58]
        mov  DWORD PTR ds:0x474c74,edx
        mov  eax,DWORD PTR [ebp+0x59dc]
        mov  DWORD PTR ds:0x491c00,edi
        mov  ds:0x491c04,eax
        jmp loc_00431B5A
        cmp  DWORD PTR [ebp+0x2b4],0x6
        jl loc_00431B5A
        lea  ebx,[ebp+0x59e4]
        mov  edi,0x32
    loc_00431AB6:
        mov  esi,DWORD PTR [ebx]
        test  esi,esi
        je loc_00431ACB
        push  esi
        call FUN_004294a0
        push  esi
        call _free
        add  esp,0x4
    loc_00431ACB:
        add  ebx,0x4
        dec  edi
        jne loc_00431AB6
        xor  eax,eax
        mov  ecx,0x32
        lea  edi,[ebp+0x59e4]
        rep stosd
        mov  esi,0x65
        mov  edi,ebp
        call FUN_0042c6d0
        mov  esi,0x8
        mov  ecx,0x5a
        mov  eax,ebp
        call FUN_0042c770
        mov  ecx,0x5b
        mov  eax,ebp
        call FUN_0042c770
        mov  esi,0x5e
        call FUN_0042c6d0
        lea  eax,[ebp+0x5d0]
        call FUN_00409e50
        mov  ecx,0x2
        mov  eax,ebp
        call FUN_0042c5c0
        dec  DWORD PTR [ebp+0xb0]
        jns loc_00431B3C
        mov  DWORD PTR [ebp+0xb0],0x0
    loc_00431B3C:
        mov  eax,DWORD PTR [ebp+0xb0]
        mov  ecx,DWORD PTR [ebp+eax*4+0x30]
        mov  DWORD PTR [ebp+0x24],ecx
        mov  edx,DWORD PTR [ebp+eax*4+0x70]
        mov  DWORD PTR [ebp+0x2c],edx
        mov  DWORD PTR [ebp+0xf8],0x0
    loc_00431B5A:
        pop  edi
        pop  esi
        pop  ebx
    loc_00431B5D:
        mov  ecx,DWORD PTR [esp+0x188]
        pop  ebp
        xor  ecx,esp
        mov  eax,0x1
        call __security_check_cookie
        add  esp,0x188
        ret  0x4
        mov  edi,edi
        repnz adc eax,0x174d0043
        inc  ebx
        add  BYTE PTR [ecx-0x4bffbce9],dh
        sbb  DWORD PTR [ebx+0x0],eax
        std
        sbb  BYTE PTR [ebx+0x0],al
        sahf
        sbb  al,BYTE PTR [ebx+0x0]
    }
}
