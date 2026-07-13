// 00405860: FUN_00405860
// Original size: 400 bytes, actual code: 117 instructions
extern "C" void FUN_004054b0(void);
extern "C" void FUN_00405500(void);
extern "C" void FUN_0043dd10(void);
extern "C" void FUN_00448db0(void);

extern "C" __declspec(naked) void FUN_00405860(void) {
    __asm {
        push  ebp
        mov  ebp,DWORD PTR [esp+0x8]
        mov  eax,DWORD PTR [ebp+0x28]
        xor  ecx,ecx
        cmp  eax,ecx
        je loc_00405875
        or   eax,0xffffffff
        pop  ebp
        ret  0x4
    loc_00405875:
        mov  edx,0x1
        mov  DWORD PTR [ebp+0x28],edx
        mov  eax,DWORD PTR [ebp+0x24]
        test  dl,al
        jne loc_0040589D
        or   eax,edx
        mov  DWORD PTR [ebp+0x18],ecx
        mov  DWORD PTR [ebp+0x14],0xfff0bdc1
        mov  DWORD PTR [ebp+0x1c],ecx
        mov  DWORD PTR [ebp+0x20],0x476f78
        mov  DWORD PTR [ebp+0x24],eax
    loc_0040589D:
        mov  eax,ds:0x477834
        mov  DWORD PTR [ebp+0x18],ecx
        mov  DWORD PTR [ebp+0x1c],ecx
        mov  DWORD PTR [ebp+0x14],0xffffffff
        push  esi
        add  eax,0x3c0
        mov  DWORD PTR [ebp+0x3c],0x42000000
        mov  DWORD PTR [ebp+0x40],0x40800000
        mov  esi,DWORD PTR [eax]
        push  edi
        lea  edi,[ebp+0x30]
        mov  ecx,edi
        mov  DWORD PTR [ecx],esi
        mov  esi,DWORD PTR [eax+0x4]
        mov  DWORD PTR [ecx+0x4],esi
        mov  eax,DWORD PTR [eax+0x8]
        mov  DWORD PTR [ecx+0x8],eax
        mov  eax,ds:0x4776f4
        test  BYTE PTR [eax+0x378c],dl
        je loc_004058F6
        mov  ecx,DWORD PTR [eax+0x3788]
        cmp  ecx,0x5d
        jl loc_004058F6
        cmp  ecx,0x60
        jle loc_00405912
    loc_004058F6:
        cmp  DWORD PTR [eax+0x3788],0x6d
        je loc_00405912
        mov  eax,ds:0x474c68
        neg  eax
        sbb  eax,eax
        and  eax,0x7
        add  eax,0x190
        jmp loc_00405917
    loc_00405912:
        mov  eax,0x1b9
    loc_00405917:
        mov  edx,DWORD PTR ds:0x4776f0
        push  ebx
        push  eax
        mov  eax,DWORD PTR [edx+0x3e0b50]
        lea  ecx,[esp+0x18]
        push  ecx
        push  eax
        call FUN_00448db0
        mov  edx,DWORD PTR [edi]
        mov  ecx,DWORD PTR [eax]
        push  edx
        mov  ebx,0x26
        mov  esi,0x492590
        mov  DWORD PTR [ebp+0x2c],ecx
        call FUN_0043dd10
        movsx eax,WORD PTR ds:0x474c48
        cdq
        mov  ecx,0x14
        idiv  ecx
        mov  esi,DWORD PTR ds:0x47770c
        imul  edx,edx,0x64
        mov  ecx,eax
        mov  eax,0x66666667
        imul  edx
        sar  edx,0x3
        mov  eax,edx
        shr  eax,0x1f
        add  eax,edx
        push  eax
        mov  edx,ecx
        call FUN_004054b0
        mov  esi,DWORD PTR ds:0x4776f4
        mov  eax,esi
        call FUN_00405500
        mov  eax,ds:0x474c98
        sub  eax,0x80
        cmp  eax,0x400
        mov  ds:0x474c98,eax
        pop  ebx
        jle loc_004059AA
        mov  DWORD PTR ds:0x474c98,0x400
        jmp loc_004059BB
    loc_004059AA:
        cmp  eax,0xfffffc00
        jge loc_004059BB
        mov  DWORD PTR ds:0x474c98,0xfffffc00
    loc_004059BB:
        mov  cl,BYTE PTR [esi+0x378c]
        mov  eax,0x1
        test  al,cl
        je loc_004059DE
        cmp  DWORD PTR [esi+0x3738],0x3c
        jl loc_004059DE
        pop  edi
        mov  DWORD PTR [ebp+0x44],eax
        pop  esi
        xor  eax,eax
        pop  ebp
        ret  0x4
    loc_004059DE:
        pop  edi
        pop  esi
        mov  DWORD PTR [ebp+0x44],0x0
        xor  eax,eax
        pop  ebp
        ret  0x4
    }
}
