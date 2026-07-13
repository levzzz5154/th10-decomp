// 00430FF0: FUN_00430ff0
// Original size: 1056 bytes, actual code: 294 instructions
extern "C" void FUN_0040c540(void);
extern "C" void FUN_00420c30(void);
extern "C" void FUN_0042c5c0(void);
extern "C" void FUN_0042c620(void);
extern "C" void FUN_0042c670(void);
extern "C" void FUN_0042c6d0(void);
extern "C" void FUN_0043c8b0(void);
extern "C" void FUN_0043dc90(void);
extern "C" void FUN_0044b010(void);
extern "C" void FUN_0044be20(void);
extern "C" void FUN_0044be70(void);
extern "C" void FUN_0044bea0(void);

extern "C" __declspec(naked) void FUN_00430ff0(void) {
    __asm {
        push  ebp
        mov  ebp,DWORD PTR [esp+0x8]
        mov  eax,DWORD PTR [ebp+0x20]
        cmp  eax,0x4
        ja loc_004313EE
        push  ebx
        push  esi
        push  edi
        jmp  DWORD PTR [eax*4+0x4313f8]
        mov  DWORD PTR [ebp+0x2c],0x6
        mov  eax,DWORD PTR [ebp+0x2c]
        test  eax,eax
        je loc_00431032
        mov  ecx,DWORD PTR ds:0x491c08
        cmp  ecx,eax
        jl loc_00431026
        dec  eax
        jmp loc_00431037
    loc_00431026:
        xor  eax,eax
        test  ecx,ecx
        setl  al
        dec  eax
        and  eax,ecx
        jmp loc_00431037
    loc_00431032:
        mov  eax,ds:0x491c08
    loc_00431037:
        push  ebp
        mov  edi,0x6a
        mov  DWORD PTR [ebp+0x24],eax
        call FUN_0042c670
        mov  edi,DWORD PTR ds:0x474c68
        add  edi,0x6b
        push  ebp
        call FUN_0042c670
        mov  ecx,0x1
        mov  eax,ebp
        call FUN_0042c620
        cmp  DWORD PTR [ebp+0x2b4],0xa
        jle loc_004313EB
        mov  ecx,0x2
        mov  eax,ebp
        call FUN_0042c620
        pop  edi
        pop  esi
        pop  ebx
        mov  eax,0x1
        pop  ebp
        ret  0x4
        mov  ecx,DWORD PTR [ebp+0x24]
        lea  esi,[ebp+0x24]
        mov  DWORD PTR [esi+0x4],ecx
        mov  cl,BYTE PTR ds:0x474e36
        mov  al,0x10
        test  al,cl
        jne loc_004310A2
        test  BYTE PTR ds:0x474e34,al
        je loc_004310AB
    loc_004310A2:
        push  0xffffffff
        mov  eax,esi
        call FUN_0044bea0
    loc_004310AB:
        mov  cl,BYTE PTR ds:0x474e36
        mov  al,0x20
        test  al,cl
        jne loc_004310BF
        test  BYTE PTR ds:0x474e34,al
        je loc_004310C8
    loc_004310BF:
        push  0x1
        mov  eax,esi
        call FUN_0044bea0
    loc_004310C8:
        mov  edx,DWORD PTR [esi+0x4]
        cmp  edx,DWORD PTR [esi]
        je loc_004310E0
        push  0x0
        mov  edi,0xc
        mov  ecx,0x492590
        call FUN_0043dc90
    loc_004310E0:
        mov  eax,ds:0x474e36
        test  al,0xa
        je loc_00431119
        mov  ecx,0x4
        mov  eax,ebp
        call FUN_0042c620
        push  0x0
        mov  edi,0xb
        mov  ecx,0x492590
        call FUN_0043dc90
        mov  eax,DWORD PTR [esi]
        pop  edi
        pop  esi
        pop  ebx
        mov  ds:0x491c08,eax
        mov  eax,0x1
        pop  ebp
        ret  0x4
    loc_00431119:
        test  eax,0x1001
        je loc_004313EB
        mov  eax,ds:0x474c74
        mov  edx,DWORD PTR [esi]
        mov  edi,DWORD PTR ds:0x47783c
        lea  ecx,[eax+eax*2]
        mov  eax,ds:0x474c68
        lea  ecx,[edx+ecx*2]
        mov  edx,DWORD PTR ds:0x474c6c
        lea  edx,[edx+eax*2]
        add  edx,eax
        imul  edx,edx,0x437c
        add  edx,edi
        mov  al,BYTE PTR [edx+ecx*8+0x4e9]
        test  al,al
        mov  ebx,0x3
        jne loc_00431166
        mov  edi,0x25
        jmp loc_00431174
    loc_00431166:
        mov  ecx,ebx
        mov  eax,ebp
        call FUN_0042c620
        mov  edi,0xa
    loc_00431174:
        mov  ecx,0x492590
        push  0x0
        call FUN_0043dc90
        mov  eax,DWORD PTR [esi]
        mov  edx,0x497aa8
        mov  ds:0x491c08,eax
        mov  DWORD PTR ds:0x474cac,0x0
        call FUN_0044b010
        test  eax,eax
        mov  al,0x80
        jne loc_004312B5
        test  BYTE PTR ds:0x497ad9,al
        je loc_004311C3
    loc_004311AD:
        pop  edi
        pop  esi
        pop  ebx
        mov  DWORD PTR ds:0x474cac,0x1
        mov  eax,0x1
        pop  ebp
        ret  0x4
    loc_004311C3:
        test  BYTE PTR ds:0x497ada,al
        je loc_004311E1
    loc_004311CB:
        pop  edi
        pop  esi
        pop  ebx
        mov  DWORD PTR ds:0x474cac,0x2
        mov  eax,0x1
        pop  ebp
        ret  0x4
    loc_004311E1:
        test  BYTE PTR ds:0x497adb,al
        je loc_004311FB
    loc_004311E9:
        pop  edi
        pop  esi
        mov  DWORD PTR ds:0x474cac,ebx
        pop  ebx
        mov  eax,0x1
        pop  ebp
        ret  0x4
    loc_004311FB:
        test  BYTE PTR ds:0x497adc,al
        je loc_00431219
    loc_00431203:
        pop  edi
        pop  esi
        pop  ebx
        mov  DWORD PTR ds:0x474cac,0x4
        mov  eax,0x1
        pop  ebp
        ret  0x4
    loc_00431219:
        test  BYTE PTR ds:0x497add,al
        je loc_00431237
    loc_00431221:
        pop  edi
        pop  esi
        pop  ebx
        mov  DWORD PTR ds:0x474cac,0x5
        mov  eax,0x1
        pop  ebp
        ret  0x4
    loc_00431237:
        test  BYTE PTR ds:0x497ade,al
        je loc_00431255
    loc_0043123F:
        pop  edi
        pop  esi
        pop  ebx
        mov  DWORD PTR ds:0x474cac,0x6
        mov  eax,0x1
        pop  ebp
        ret  0x4
    loc_00431255:
        test  BYTE PTR ds:0x497adf,al
        je loc_00431273
    loc_0043125D:
        pop  edi
        pop  esi
        pop  ebx
        mov  DWORD PTR ds:0x474cac,0x7
        mov  eax,0x1
        pop  ebp
        ret  0x4
    loc_00431273:
        test  BYTE PTR ds:0x497ae0,al
        je loc_00431291
    loc_0043127B:
        pop  edi
        pop  esi
        pop  ebx
        mov  DWORD PTR ds:0x474cac,0x8
        mov  eax,0x1
        pop  ebp
        ret  0x4
    loc_00431291:
        mov  cl,BYTE PTR ds:0x497ae1
    loc_00431297:
        test  al,cl
        je loc_004313EB
        pop  edi
        pop  esi
        pop  ebx
        mov  DWORD PTR ds:0x474cac,0x9
        mov  eax,0x1
        pop  ebp
        ret  0x4
    loc_004312B5:
        test  BYTE PTR ds:0x497aaa,al
        jne loc_004311AD
        test  BYTE PTR ds:0x497aab,al
        jne loc_004311CB
        test  BYTE PTR ds:0x497aac,al
        jne loc_004311E9
        test  BYTE PTR ds:0x497aad,al
        jne loc_00431203
        test  BYTE PTR ds:0x497aae,al
        jne loc_00431221
        test  BYTE PTR ds:0x497aaf,al
        jne loc_0043123F
        test  BYTE PTR ds:0x497ab0,al
        jne loc_0043125D
        test  BYTE PTR ds:0x497ab1,al
        jne loc_0043127B
        mov  cl,BYTE PTR ds:0x497ab2
        jmp loc_00431297
        cmp  DWORD PTR [ebp+0x2b4],0xa
        jne loc_00431352
        mov  esi,DWORD PTR ds:0x4776e0
        push  0x43c40000
        push  0x43f00000
        call FUN_0040c540
        push  0x0
        push  0x0
        push  0x0
        push  0x20
        push  0x5
        mov  ebx,0x2b
        call FUN_0043c8b0
    loc_00431352:
        cmp  DWORD PTR [ebp+0x2b4],0x28
        jl loc_004313EB
        lea  esi,[ebp+0x24]
        mov  eax,esi
        call FUN_0044be20
        mov  ecx,0x3
        mov  eax,ebp
        call FUN_0042c5c0
        mov  eax,DWORD PTR [esi]
        inc  eax
        lea  ecx,[eax+eax*2]
        shl  ecx,0x4
        add  ecx,0x474788
        push  0x40c00000
        mov  DWORD PTR ds:0x477848,ecx
        mov  ds:0x474c7c,eax
        mov  ds:0x474c80,eax
        call FUN_00420c30
        pop  edi
        pop  esi
        pop  ebx
        mov  DWORD PTR ds:0x491fb8,0x7
        mov  eax,0x1
        pop  ebp
        ret  0x4
        cmp  DWORD PTR [ebp+0x2b4],0x6
        jl loc_004313EB
        mov  esi,0x6a
        mov  edi,ebp
        call FUN_0042c6d0
        mov  esi,DWORD PTR ds:0x474c68
        add  esi,0x6b
        call FUN_0042c6d0
        mov  ecx,0x8
        mov  eax,ebp
        call FUN_0042c5c0
        lea  eax,[ebp+0x24]
        call FUN_0044be70
    loc_004313EB:
        pop  edi
        pop  esi
        pop  ebx
    loc_004313EE:
        mov  eax,0x1
        pop  ebp
        ret  0x4
    }
}
