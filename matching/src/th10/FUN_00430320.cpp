// 00430320: FUN_00430320
// Original size: 896 bytes, actual code: 256 instructions
extern "C" void FUN_00409e50(void);
extern "C" void FUN_0040ace0(void);
extern "C" void FUN_0040ad20(void);
extern "C" void FUN_0042c5c0(void);
extern "C" void FUN_0042c620(void);
extern "C" void FUN_0042c670(void);
extern "C" void FUN_0042c6d0(void);
extern "C" void FUN_0042c750(void);
extern "C" void FUN_0042c770(void);
extern "C" void FUN_0043dc90(void);
extern "C" void FUN_00448d00(void);
extern "C" void FUN_004491c0(void);
extern "C" void FUN_00449250(void);
extern "C" void FUN_00449470(void);
extern "C" void FUN_004497d0(void);
extern "C" void FUN_0044be20(void);
extern "C" void FUN_0044be70(void);
extern "C" void FUN_0044bea0(void);

extern "C" __declspec(naked) void FUN_00430320(void) {
    __asm {
        push  ecx
        push  ebx
        push  ebp
        mov  ebp,DWORD PTR [esp+0x10]
        mov  eax,DWORD PTR [ebp+0x20]
        xor  ebx,ebx
        push  esi
        mov  esi,DWORD PTR ds:0x474c74
        cmp  esi,0x4
        setge bl
        add  ebx,0x77
        cmp  eax,0x4
        mov  DWORD PTR [esp+0x14],ebx
        ja loc_00430675
        push  edi
        jmp  DWORD PTR [eax*4+0x430684]
        mov  eax,DWORD PTR [ebp+0x43c]
        mov  edx,DWORD PTR ds:0x491c10
        push  eax
        call FUN_004491c0
        test  eax,eax
        jne loc_0043039A
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
        mov  esi,DWORD PTR ds:0x474c74
    loc_0043039A:
        xor  eax,eax
        cmp  esi,0x4
        setge al
        mov  esi,ebx
        mov  edi,ebp
        dec  eax
        and  eax,0x3
        inc  eax
        mov  DWORD PTR [ebp+0x2c],eax
        call FUN_0042c6d0
        push  ebp
        mov  edi,ebx
        call FUN_0042c670
        mov  ecx,DWORD PTR [ebp+ebx*4+0x2c4]
        mov  edx,DWORD PTR ds:0x491c10
        push  ecx
        mov  edi,0x3
        call FUN_00449250
        xor  esi,esi
        mov  si,WORD PTR [ebp+0x24]
        add  si,0x11
        mov  ecx,ebx
        mov  eax,ebp
        call FUN_0042c770
        push  ebp
        mov  edi,0x62
        call FUN_0042c670
        mov  ecx,0x1
        mov  eax,ebp
        call FUN_0042c620
        cmp  DWORD PTR [ebp+0x2b4],0x6
        jle loc_00430674
        mov  ecx,0x2
        mov  eax,ebp
        call FUN_0042c620
        pop  edi
        pop  esi
        pop  ebp
        mov  eax,0x1
        pop  ebx
        pop  ecx
        ret  0x4
        cmp  esi,0x4
        jge loc_0043049C
        mov  edx,DWORD PTR [ebp+0x24]
        lea  esi,[ebp+0x24]
        mov  eax,0x10
        mov  ecx,0x474e30
        mov  DWORD PTR [esi+0x4],edx
        call FUN_0040ace0
        test  ax,ax
        je loc_0043044E
        push  0xffffffff
        mov  eax,esi
        call FUN_0044bea0
    loc_0043044E:
        mov  eax,0x20
        mov  ecx,0x474e30
        call FUN_0040ace0
        test  ax,ax
        je loc_0043046B
        push  0x1
        mov  eax,esi
        call FUN_0044bea0
    loc_0043046B:
        mov  eax,DWORD PTR [esi+0x4]
        cmp  eax,DWORD PTR [esi]
        je loc_0043049C
        push  0x0
        mov  edi,0xc
        mov  ecx,0x492590
        call FUN_0043dc90
        mov  ecx,ebx
        mov  eax,ebp
        call FUN_0042c750
        movsx esi,WORD PTR [esi]
        add  si,0x7
        mov  ecx,ebx
        mov  eax,ebp
        call FUN_0042c770
    loc_0043049C:
        mov  eax,ds:0x474e36
        test  al,0xa
        je loc_004304D8
        mov  ecx,0x4
        mov  eax,ebp
        call FUN_0042c620
        push  0x0
        mov  edi,0xb
        mov  ecx,0x492590
        call FUN_0043dc90
        mov  esi,ebx
        mov  edi,ebp
        call FUN_0042c6d0
        pop  edi
        pop  esi
        pop  ebp
        mov  eax,0x1
        pop  ebx
        pop  ecx
        ret  0x4
    loc_004304D8:
        test  eax,0x1001
        je loc_00430674
        mov  esi,0x6
        mov  ecx,ebx
        mov  eax,ebp
        call FUN_0042c770
        cmp  DWORD PTR ds:0x474c74,0x4
        jge loc_00430516
        mov  ebx,DWORD PTR [ebp+0x24]
        mov  ecx,DWORD PTR [esp+0x18]
        add  ebx,0x6d
        lea  esi,[ebp+ecx*4+0x2c4]
        lea  edi,[esp+0x18]
        call FUN_004497d0
        jmp loc_00430558
    loc_00430516:
        mov  edx,DWORD PTR [ebp+ebx*4+0x2c4]
        push  edx
        mov  edx,DWORD PTR ds:0x491c10
        call FUN_004491c0
        xor  edx,edx
        cmp  eax,edx
        jne loc_00430536
        mov  DWORD PTR [ebp+ebx*4+0x2c4],edx
    loc_00430536:
        add  eax,0x10
        cmp  eax,edx
        je loc_00430554
        mov  ecx,0x71
    loc_00430542:
        mov  esi,DWORD PTR [eax]
        cmp  WORD PTR [esi+0x38a],cx
        je loc_00430590
        mov  eax,DWORD PTR [eax+0x4]
        cmp  eax,edx
        jne loc_00430542
    loc_00430554:
        mov  DWORD PTR [esp+0x18],edx
    loc_00430558:
        lea  eax,[esp+0x18]
        mov  esi,0x2
        call FUN_00449470
        mov  ecx,0x3
        mov  eax,ebp
        call FUN_0042c620
        push  0x0
        mov  edi,0xa
        mov  ecx,0x492590
        call FUN_0043dc90
        pop  edi
        pop  esi
        pop  ebp
        mov  eax,0x1
        pop  ebx
        pop  ecx
        ret  0x4
    loc_00430590:
        mov  eax,DWORD PTR [eax]
        mov  ecx,DWORD PTR [eax]
        mov  DWORD PTR [esp+0x18],ecx
        jmp loc_00430558
        cmp  DWORD PTR [ebp+0x2b4],0xe
        jl loc_00430674
        mov  esi,0x62
        mov  edi,ebp
        call FUN_0042c6d0
        mov  ecx,0x7
        mov  eax,ebp
        call FUN_0042c5c0
        cmp  DWORD PTR ds:0x474c74,0x4
        jge loc_004305D1
        mov  edx,DWORD PTR [ebp+0x24]
        mov  DWORD PTR ds:0x474c74,edx
    loc_004305D1:
        lea  eax,[ebp+0x24]
        call FUN_0044be20
        mov  DWORD PTR [ebp+0x2c],0x2
        mov  ecx,DWORD PTR ds:0x474c68
        mov  edx,eax
        call FUN_0040ad20
        pop  edi
        pop  esi
        pop  ebp
        mov  eax,0x1
        pop  ebx
        pop  ecx
        ret  0x4
        cmp  DWORD PTR [ebp+0x2b4],0x6
        jl loc_00430674
        mov  esi,0x62
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
        cmp  DWORD PTR ds:0x474c74,0x4
        jge loc_00430660
        mov  eax,DWORD PTR [ebp+0x24]
        mov  ds:0x474c74,eax
        jmp loc_0043066C
    loc_00430660:
        mov  ecx,DWORD PTR [ebp+0x58f0]
        mov  DWORD PTR ds:0x474c74,ecx
    loc_0043066C:
        lea  eax,[ebp+0x24]
        call FUN_0044be70
    loc_00430674:
        pop  edi
    loc_00430675:
        pop  esi
        pop  ebp
        mov  eax,0x1
        pop  ebx
        pop  ecx
        ret  0x4
        nop
        push  ecx
        add  eax,DWORD PTR [ebx+0x0]
        std
        add  eax,DWORD PTR [ebx+0x0]
        and  eax,DWORD PTR [ebx+eax*2]
        add  BYTE PTR [edx-0x5ffbcfb],bl
        add  eax,0xcccc0043
    }
}
