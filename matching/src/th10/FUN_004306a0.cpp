// 004306A0: FUN_004306a0
// Original size: 960 bytes, actual code: 280 instructions
extern "C" void FUN_0040ad20(void);
extern "C" void FUN_0042c5c0(void);
extern "C" void FUN_0042c620(void);
extern "C" void FUN_0042c670(void);
extern "C" void FUN_0042c6d0(void);
extern "C" void FUN_0042c750(void);
extern "C" void FUN_0042c770(void);
extern "C" void FUN_0043dc90(void);
extern "C" void FUN_00449250(void);
extern "C" void FUN_00449470(void);
extern "C" void FUN_004497d0(void);
extern "C" void FUN_0044be20(void);
extern "C" void FUN_0044be70(void);
extern "C" void FUN_0044bea0(void);

extern "C" __declspec(naked) void FUN_004306a0(void) {
    __asm {
        push  ebx
        push  ebp
        mov  ebp,DWORD PTR [esp+0xc]
        mov  eax,DWORD PTR [ebp+0x20]
        cmp  eax,0x4
        ja loc_00430A3E
        push  esi
        push  edi
        jmp  DWORD PTR [eax*4+0x430a48]
        mov  DWORD PTR [ebp+0x2c],0x2
        cmp  DWORD PTR ds:0x474c74,0x4
        jne loc_0043077C
        mov  ecx,DWORD PTR ds:0x47783c
        mov  al,BYTE PTR [ecx+0x1d888]
        xor  edx,edx
        cmp  al,dl
        jne loc_0043072C
        cmp  BYTE PTR [ecx+0x1d889],dl
        jne loc_0043072C
        cmp  BYTE PTR [ecx+0x1d88a],dl
        jne loc_0043072C
        cmp  DWORD PTR [ebp+0x24],edx
        jne loc_00430719
        mov  eax,DWORD PTR [ebp+0x2c]
        cmp  eax,edx
        je loc_00430712
        cmp  eax,0x1
        jg loc_00430708
        dec  eax
        mov  DWORD PTR [ebp+0x24],eax
        jmp loc_00430719
    loc_00430708:
        mov  eax,0x1
        mov  DWORD PTR [ebp+0x24],eax
        jmp loc_00430719
    loc_00430712:
        mov  DWORD PTR [ebp+0x24],0x1
    loc_00430719:
        mov  eax,DWORD PTR [ebp+0xf8]
        mov  DWORD PTR [ebp+eax*4+0xb4],edx
        inc  DWORD PTR [ebp+0xf8]
    loc_0043072C:
        cmp  BYTE PTR [ecx+0x1d88b],dl
        jne loc_0043077C
        cmp  BYTE PTR [ecx+0x1d88c],dl
        jne loc_0043077C
        cmp  BYTE PTR [ecx+0x1d88d],dl
        jne loc_0043077C
        mov  eax,DWORD PTR [ebp+0x24]
        mov  ecx,0x1
        cmp  eax,ecx
        jne loc_00430769
        mov  eax,DWORD PTR [ebp+0x2c]
        cmp  eax,edx
        je loc_00430766
        jg loc_0043075F
        dec  eax
        mov  DWORD PTR [ebp+0x24],eax
        jmp loc_00430769
    loc_0043075F:
        xor  eax,eax
        mov  DWORD PTR [ebp+0x24],eax
        jmp loc_00430769
    loc_00430766:
        mov  DWORD PTR [ebp+0x24],edx
    loc_00430769:
        mov  edx,DWORD PTR [ebp+0xf8]
        mov  DWORD PTR [ebp+edx*4+0xb4],ecx
        inc  DWORD PTR [ebp+0xf8]
    loc_0043077C:
        push  ebp
        mov  edi,0x63
        call FUN_0042c670
        mov  esi,0x7d
        mov  edi,ebp
        call FUN_0042c6d0
        push  ebp
        mov  edi,esi
        call FUN_0042c670
        mov  eax,DWORD PTR [ebp+0x4b8]
        mov  edx,DWORD PTR ds:0x491c10
        push  eax
        mov  edi,0x3
        call FUN_00449250
        xor  esi,esi
        mov  si,WORD PTR [ebp+0x24]
        add  si,0x11
        mov  ecx,0x7d
        mov  eax,ebp
        call FUN_0042c770
        mov  ecx,0x1
        mov  eax,ebp
        call FUN_0042c620
        cmp  DWORD PTR [ebp+0x2b4],0x6
        jle loc_00430A3C
        mov  ecx,0x2
        mov  eax,ebp
        call FUN_0042c620
        pop  edi
        pop  esi
        pop  ebp
        mov  eax,0x1
        pop  ebx
        ret  0x4
        mov  ecx,DWORD PTR [ebp+0x24]
        lea  ebx,[ebp+0x24]
        mov  DWORD PTR [ebx+0x4],ecx
        mov  cl,BYTE PTR ds:0x474e36
        mov  al,0x40
        test  al,cl
        jne loc_00430816
        test  BYTE PTR ds:0x474e34,al
        je loc_0043081F
    loc_00430816:
        push  0xffffffff
        mov  eax,ebx
        call FUN_0044bea0
    loc_0043081F:
        mov  cl,BYTE PTR ds:0x474e36
        mov  al,0x80
        test  al,cl
        jne loc_00430833
        test  BYTE PTR ds:0x474e34,al
        je loc_0043083C
    loc_00430833:
        push  0x1
        mov  eax,ebx
        call FUN_0044bea0
    loc_0043083C:
        mov  edx,DWORD PTR [ebx+0x4]
        cmp  edx,DWORD PTR [ebx]
        je loc_00430875
        push  0x0
        mov  edi,0xc
        mov  ecx,0x492590
        call FUN_0043dc90
        mov  ecx,0x7d
        mov  eax,ebp
        call FUN_0042c750
        xor  esi,esi
        mov  si,WORD PTR [ebx]
        add  si,0x7
        mov  ecx,0x7d
        mov  eax,ebp
        call FUN_0042c770
    loc_00430875:
        mov  eax,ds:0x474e36
        test  al,0xa
        je loc_004308A7
        mov  ecx,0x4
        mov  eax,ebp
        call FUN_0042c620
        push  0x0
        mov  edi,0xb
        mov  ecx,0x492590
        call FUN_0043dc90
        pop  edi
        pop  esi
        pop  ebp
        mov  eax,0x1
        pop  ebx
        ret  0x4
    loc_004308A7:
        test  eax,0x1001
        je loc_00430A3C
        mov  ebx,DWORD PTR [ebx]
        lea  esi,[ebp+0x4b8]
        add  ebx,0x79
        lea  edi,[esp+0x14]
        call FUN_004497d0
        mov  esi,0x6
        mov  eax,edi
        call FUN_00449470
        mov  ebx,DWORD PTR [ebp+0x24]
        add  ebx,0x7b
        lea  edi,[esp+0x14]
        lea  esi,[ebp+0x4b8]
        call FUN_004497d0
        mov  esi,0x6
        mov  eax,edi
        call FUN_00449470
        mov  edx,DWORD PTR [ebp+0x24]
        mov  ebx,0x7a
        sub  ebx,edx
        lea  edi,[esp+0x14]
        lea  esi,[ebp+0x4b8]
        call FUN_004497d0
        mov  esi,0x1
        mov  eax,edi
        call FUN_00449470
        mov  ecx,DWORD PTR [ebp+0x24]
        mov  ebx,0x7c
        sub  ebx,ecx
        lea  edi,[esp+0x14]
        lea  esi,[ebp+0x4b8]
        call FUN_004497d0
        mov  esi,0x1
        mov  eax,edi
        call FUN_00449470
        push  0x0
        mov  edi,0xa
        mov  ecx,0x492590
        call FUN_0043dc90
        mov  ecx,0x3
        mov  eax,ebp
        call FUN_0042c620
        pop  edi
        pop  esi
        pop  ebp
        mov  eax,0x1
        pop  ebx
        ret  0x4
        cmp  DWORD PTR [ebp+0x2b4],0xe
        jl loc_00430A3C
        mov  esi,0x63
        mov  edi,ebp
        call FUN_0042c6d0
        mov  ecx,0x8
        mov  eax,ebp
        call FUN_0042c5c0
        mov  esi,DWORD PTR [ebp+0x24]
        mov  edi,DWORD PTR ds:0x474c68
        lea  eax,[ebp+0x24]
        mov  DWORD PTR ds:0x474c68,esi
        call FUN_0044be20
        cmp  edi,esi
        mov  DWORD PTR [ebp+0x2c],0x3
        je loc_004309E7
        mov  ecx,DWORD PTR [eax+0x8]
        test  ecx,ecx
        je loc_004309D5
        jg loc_004309C5
        pop  edi
        pop  esi
        dec  ecx
        pop  ebp
        mov  DWORD PTR [eax],ecx
        mov  eax,0x1
        pop  ebx
        ret  0x4
    loc_004309C5:
        pop  edi
        pop  esi
        xor  ecx,ecx
        pop  ebp
        mov  DWORD PTR [eax],ecx
        mov  eax,0x1
        pop  ebx
        ret  0x4
    loc_004309D5:
        pop  edi
        pop  esi
        pop  ebp
        mov  DWORD PTR [eax],0x0
        mov  eax,0x1
        pop  ebx
        ret  0x4
    loc_004309E7:
        mov  ecx,DWORD PTR ds:0x474c6c
        mov  edx,eax
        call FUN_0040ad20
        pop  edi
        pop  esi
        pop  ebp
        mov  eax,0x1
        pop  ebx
        ret  0x4
        cmp  DWORD PTR [ebp+0x2b4],0x6
        jl loc_00430A3C
        mov  esi,0x7d
        mov  edi,ebp
        call FUN_0042c6d0
        mov  esi,0x63
        call FUN_0042c6d0
        mov  ecx,0x6
        mov  eax,ebp
        call FUN_0042c5c0
        mov  ecx,DWORD PTR [ebp+0x24]
        lea  eax,[ebp+0x24]
        mov  DWORD PTR ds:0x474c68,ecx
        call FUN_0044be70
    loc_00430A3C:
        pop  edi
        pop  esi
    loc_00430A3E:
        pop  ebp
        mov  eax,0x1
        pop  ebx
        ret  0x4
        mov  ebx,0xd4004306
        pop  es
        inc  ebx
        add  cl,bh
        pop  es
        inc  ebx
        add  BYTE PTR [esi+0x9],ah
        inc  ebx
        add  BYTE PTR [eax],al
        or   al,BYTE PTR [ebx+0x0]
    }
}
