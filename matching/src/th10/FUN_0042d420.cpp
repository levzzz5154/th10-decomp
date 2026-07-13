// 0042D420: FUN_0042d420
// Original size: 1280 bytes, actual code: 391 instructions
extern "C" void FUN_0040ad20(void);
extern "C" void FUN_0042c5c0(void);
extern "C" void FUN_0042c620(void);
extern "C" void FUN_0042c670(void);
extern "C" void FUN_0042c6d0(void);
extern "C" void FUN_0042c750(void);
extern "C" void FUN_0042c770(void);
extern "C" void FUN_0042c850(void);
extern "C" void FUN_0043dc90(void);
extern "C" void FUN_004491c0(void);
extern "C" void FUN_00449250(void);
extern "C" void FUN_0044be20(void);
extern "C" void FUN_0044bea0(void);

extern "C" __declspec(naked) void FUN_0042d420(void) {
    __asm {
        mov  eax,DWORD PTR [ebx+0x20]
        cmp  eax,0x4
        push  ebp
        ja loc_0042D8C4
        push  esi
        push  edi
        jmp  DWORD PTR [eax*4+0x42d8cc]
        mov  eax,ds:0x47783c
        mov  DWORD PTR [ebx+0x2c],0x8
        call FUN_0042c850
        test  eax,eax
        jne loc_0042D462
        mov  eax,DWORD PTR [ebx+0xf8]
        mov  DWORD PTR [ebx+eax*4+0xb4],0x1
        inc  DWORD PTR [ebx+0xf8]
    loc_0042D462:
        test  BYTE PTR ds:0x474ca0,0x10
        je loc_0042D495
        mov  eax,DWORD PTR [ebx+0x2c]
        test  eax,eax
        je loc_0042D487
        cmp  eax,0x2
        jg loc_0042D47D
        dec  eax
        mov  DWORD PTR [ebx+0x24],eax
        jmp loc_0042D48E
    loc_0042D47D:
        mov  eax,0x2
        mov  DWORD PTR [ebx+0x24],eax
        jmp loc_0042D48E
    loc_0042D487:
        mov  DWORD PTR [ebx+0x24],0x2
    loc_0042D48E:
        and  DWORD PTR ds:0x474ca0,0xffffffef
    loc_0042D495:
        mov  ecx,DWORD PTR [ebx+0x424]
        mov  edx,DWORD PTR ds:0x491c10
        push  ecx
        call FUN_004491c0
        test  eax,eax
        jne loc_0042D4B6
        push  ebx
        mov  edi,0x58
        call FUN_0042c670
    loc_0042D4B6:
        push  ebx
        xor  edi,edi
        call FUN_0042c670
        mov  ecx,0x1
        mov  eax,ebx
        call FUN_0042c620
        cmp  DWORD PTR [ebx+0x2b4],0xa
        jle loc_0042D8C2
        mov  ecx,0x2
        mov  eax,ebx
        call FUN_0042c620
        mov  edx,DWORD PTR [ebx+0x2c4]
        push  edx
        mov  edx,DWORD PTR ds:0x491c10
        mov  edi,0x3
        call FUN_00449250
        xor  esi,esi
        mov  si,WORD PTR [ebx+0x24]
        add  si,0x11
        xor  ecx,ecx
        mov  eax,ebx
        call FUN_0042c770
        pop  edi
        pop  esi
        mov  eax,0x1
        pop  ebp
        ret
        mov  eax,DWORD PTR [ebx+0x24]
        lea  ebp,[ebx+0x24]
        mov  DWORD PTR [ebp+0x4],eax
        mov  cl,BYTE PTR ds:0x474e36
        mov  al,0x10
        test  al,cl
        jne loc_0042D533
        test  BYTE PTR ds:0x474e34,al
        je loc_0042D53C
    loc_0042D533:
        push  0xffffffff
        mov  eax,ebp
        call FUN_0044bea0
    loc_0042D53C:
        mov  cl,BYTE PTR ds:0x474e36
        mov  al,0x20
        test  al,cl
        jne loc_0042D550
        test  BYTE PTR ds:0x474e34,al
        je loc_0042D559
    loc_0042D550:
        push  0x1
        mov  eax,ebp
        call FUN_0044bea0
    loc_0042D559:
        mov  ecx,DWORD PTR [ebp+0x4]
        cmp  ecx,DWORD PTR [ebp+0x0]
        je loc_0042D59C
        push  0x0
        mov  edi,0xc
        mov  ecx,0x492590
        call FUN_0043dc90
        mov  edx,DWORD PTR [ebx+0x2c4]
        push  edx
        mov  edx,DWORD PTR ds:0x491c10
        mov  edi,0x3
        call FUN_00449250
        xor  esi,esi
        mov  si,WORD PTR [ebp+0x0]
        add  si,0x7
        xor  ecx,ecx
        mov  eax,ebx
        call FUN_0042c770
    loc_0042D59C:
        test  BYTE PTR ds:0x474e36,0xa
        je loc_0042D5FF
        cmp  DWORD PTR [ebp+0x0],0x7
        je loc_0042D700
        push  0x0
        mov  edi,0xb
        mov  ecx,0x492590
        call FUN_0043dc90
        mov  eax,DWORD PTR [ebp+0x8]
        test  eax,eax
        je loc_0042D5DC
        cmp  eax,0x7
        jg loc_0042D5D2
        dec  eax
        mov  DWORD PTR [ebp+0x0],eax
        jmp loc_0042D5E3
    loc_0042D5D2:
        mov  eax,0x7
        mov  DWORD PTR [ebp+0x0],eax
        jmp loc_0042D5E3
    loc_0042D5DC:
        mov  DWORD PTR [ebp+0x0],0x7
    loc_0042D5E3:
        xor  ecx,ecx
        mov  eax,ebx
        call FUN_0042c750
        xor  esi,esi
        mov  si,WORD PTR [ebp+0x0]
        add  si,0x7
        xor  ecx,ecx
        mov  eax,ebx
        call FUN_0042c770
    loc_0042D5FF:
        test  DWORD PTR ds:0x474e36,0x1001
        je loc_0042D8C2
        mov  esi,0x6
        xor  ecx,ecx
        mov  eax,ebx
        call FUN_0042c770
        mov  ebp,DWORD PTR [ebp+0x0]
        cmp  ebp,0x7
        ja loc_0042D8C2
        jmp  DWORD PTR [ebp*4+0x42d8e0]
        push  0x0
        mov  edi,0xa
        mov  ecx,0x492590
        call FUN_0043dc90
        mov  esi,0x7
        mov  ecx,0x5a
        mov  eax,ebx
        call FUN_0042c770
        mov  ecx,0x5b
        mov  eax,ebx
        call FUN_0042c770
        mov  ecx,0x4
        mov  eax,ebx
        call FUN_0042c620
        pop  edi
        pop  esi
        mov  eax,0x1
        pop  ebp
        ret
        push  0x0
        mov  edi,0xa
        mov  ecx,0x492590
        call FUN_0043dc90
        mov  esi,0x7
        mov  ecx,0x5a
        mov  eax,ebx
        call FUN_0042c770
        mov  ecx,0x5b
        mov  eax,ebx
        call FUN_0042c770
        mov  ecx,0x4
        mov  eax,ebx
        call FUN_0042c620
        push  0x0
        mov  ecx,0x492590
        call FUN_0043dc90
        pop  edi
        pop  esi
        mov  eax,0x1
        pop  ebp
        ret
        push  0x0
        mov  edi,0xa
        mov  ecx,0x492590
        call FUN_0043dc90
        mov  ecx,0x4
        mov  eax,ebx
        call FUN_0042c620
        mov  ecx,0x5a
        mov  eax,ebx
        call FUN_0042c750
        mov  ecx,0x5b
        mov  eax,ebx
        call FUN_0042c750
        pop  edi
        pop  esi
        mov  eax,0x1
        pop  ebp
        ret
    loc_0042D700:
        push  0x0
        mov  edi,0xb
        mov  ecx,0x492590
        call FUN_0043dc90
        mov  ecx,0x4
        mov  eax,ebx
        call FUN_0042c620
        pop  edi
        pop  esi
        mov  eax,0x1
        pop  ebp
        ret
        cmp  DWORD PTR [ebx+0x2b4],0x14
        jl loc_0042D8C2
        mov  eax,DWORD PTR [ebx+0x24]
        cmp  eax,0x7
        lea  ebp,[ebx+0x24]
        ja loc_0042D8C2
        jmp  DWORD PTR [eax*4+0x42d900]
        mov  ecx,DWORD PTR ds:0x474ca0
        and  ecx,0xffffffef
        jmp loc_0042D7D7
        mov  edx,DWORD PTR ds:0x474ca0
        and  edx,0xffffffef
        mov  esi,0x58
        mov  edi,ebx
        mov  DWORD PTR ds:0x474ca0,edx
        call FUN_0042c6d0
        mov  ecx,0x6
        mov  eax,ebx
        call FUN_0042c5c0
        mov  eax,ebp
        call FUN_0044be20
        mov  eax,ds:0x474c74
        mov  DWORD PTR [ebx+0x58f0],eax
        mov  DWORD PTR ds:0x474c74,0x4
        mov  eax,DWORD PTR [ebp+0x8]
        test  eax,eax
        je loc_0042D7BE
        jg loc_0042D7B0
        pop  edi
        dec  eax
        mov  DWORD PTR [ebp+0x0],eax
        pop  esi
        mov  eax,0x1
        pop  ebp
        ret
    loc_0042D7B0:
        pop  edi
        xor  eax,eax
        mov  DWORD PTR [ebp+0x0],eax
        pop  esi
        mov  eax,0x1
        pop  ebp
        ret
    loc_0042D7BE:
        pop  edi
        pop  esi
        mov  DWORD PTR [ebp+0x0],0x0
        mov  eax,0x1
        pop  ebp
        ret
        mov  ecx,DWORD PTR ds:0x474ca0
        or   ecx,0x10
    loc_0042D7D7:
        mov  edi,ebx
        mov  esi,0x58
        mov  DWORD PTR ds:0x474ca0,ecx
        call FUN_0042c6d0
        mov  eax,ebx
        mov  ecx,0x6
        call FUN_0042c5c0
        mov  eax,ebp
        call FUN_0044be20
        mov  ecx,DWORD PTR ds:0x474c74
        cmp  ecx,0x4
        jl loc_0042D812
        mov  ecx,0x1
        mov  DWORD PTR ds:0x474c74,ecx
    loc_0042D812:
        mov  edx,ebp
        call FUN_0040ad20
        pop  edi
        pop  esi
        mov  eax,0x1
        pop  ebp
        ret
        mov  esi,0x58
        mov  edi,ebx
        call FUN_0042c6d0
        mov  ecx,0xc
        mov  eax,ebx
        call FUN_0042c5c0
        mov  eax,ebp
        call FUN_0044be20
        pop  edi
        pop  esi
        mov  eax,0x1
        pop  ebp
        ret
        mov  esi,0x58
        mov  edi,ebx
        call FUN_0042c6d0
        mov  ecx,0xb
        mov  eax,ebx
        call FUN_0042c5c0
        mov  eax,ebp
        call FUN_0044be20
        pop  edi
        pop  esi
        mov  eax,0x1
        pop  ebp
        ret
        mov  esi,0x58
        mov  edi,ebx
        call FUN_0042c6d0
        mov  ecx,0xe
        mov  eax,ebx
        call FUN_0042c5c0
        mov  eax,ebp
        call FUN_0044be20
        pop  edi
        pop  esi
        mov  eax,0x1
        pop  ebp
        ret
        mov  ecx,0x4
        mov  eax,ebx
        call FUN_0042c5c0
        mov  eax,ebp
        call FUN_0044be20
        pop  edi
        pop  esi
        mov  eax,0x1
        pop  ebp
        ret
        mov  ecx,0x3
        mov  eax,ebx
        call FUN_0042c5c0
    loc_0042D8C2:
        pop  edi
        pop  esi
    loc_0042D8C4:
        mov  eax,0x1
        pop  ebp
        ret
    }
}
