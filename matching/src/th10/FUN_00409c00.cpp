// 00409C00: FUN_00409c00
// Original size: 400 bytes, actual code: 102 instructions
extern "C" void FUN_00409e50(void);
extern "C" void FUN_004172e0(void);
extern "C" void FUN_0043dc90(void);
extern "C" void FUN_00448d00(void);
extern "C" void FUN_004492a0(void);

extern "C" __declspec(naked) void FUN_00409c00(void) {
    __asm {
        push  ecx
        push  esi
        mov  esi,eax
        test  BYTE PTR [esi+0x378c],0x1
        je loc_00409D8C
        mov  eax,ds:0x4776e8
        push  ebp
        push  edi
        or   DWORD PTR [eax+0x2a18],0x1
        lea  eax,[esi+0x768]
        call FUN_00409e50
        lea  eax,[esi+0x76c]
        call FUN_00409e50
        lea  eax,[esi+0x770]
        call FUN_00409e50
        mov  edx,DWORD PTR [esi+0x378c]
        mov  ebp,DWORD PTR ds:0x491c10
        and  edx,0xfffffffe
        mov  DWORD PTR [esi+0x378c],edx
        mov  eax,DWORD PTR [esi+0x774]
        push  eax
        mov  edx,ebp
        call FUN_004492a0
        mov  DWORD PTR [esi+0x774],0x0
        test  BYTE PTR [esi+0x378c],0x2
        je loc_00409D52
        mov  ecx,DWORD PTR [esi+0x3790]
        mov  eax,0x66666667
        imul  ecx
        mov  eax,ds:0x474c44
        sar  edx,0x2
        mov  ecx,edx
        shr  ecx,0x1f
        add  ecx,edx
        add  eax,ecx
        cmp  eax,0x3b9aca00
        mov  ds:0x474c44,eax
        jl loc_00409CAE
        mov  DWORD PTR ds:0x474c44,0x3b9ac9ff
    loc_00409CAE:
        mov  edx,DWORD PTR [esi+0x3790]
        mov  eax,ds:0x47770c
        push  edx
        push  eax
        xor  eax,eax
        call FUN_004172e0
        mov  ecx,DWORD PTR ds:0x477838
        cmp  DWORD PTR [ecx+0x10],0x1
        je loc_00409D3C
        mov  eax,ds:0x474c68
        mov  edx,DWORD PTR ds:0x474c6c
        lea  ecx,[edx+eax*2]
        mov  edx,DWORD PTR ds:0x47783c
        add  ecx,eax
        mov  eax,DWORD PTR [esi+0x3788]
        imul  ecx,ecx,0x437c
        lea  eax,[eax+eax*8]
        add  ecx,edx
        shl  eax,0x4
        lea  eax,[eax+ecx*1+0x5a4]
        mov  ecx,DWORD PTR [eax+0x80]
        cmp  ecx,0x1869f
        jge loc_00409D14
        inc  ecx
        mov  DWORD PTR [eax+0x80],ecx
    loc_00409D14:
        mov  esi,DWORD PTR [esi+0x3788]
        lea  ecx,[esi+esi*8]
        shl  ecx,0x4
        lea  eax,[ecx+edx*1+0x19a8c]
        mov  ecx,DWORD PTR [eax+0x80]
        cmp  ecx,0x1869f
        jge loc_00409D3C
        inc  ecx
        mov  DWORD PTR [eax+0x80],ecx
    loc_00409D3C:
        push  0x0
        mov  edi,0x2d
        mov  ecx,0x492590
        call FUN_0043dc90
        pop  edi
        pop  ebp
        pop  esi
        pop  ecx
        ret
    loc_00409D52:
        mov  edi,DWORD PTR ds:0x47770c
        mov  edx,DWORD PTR [edi+0x9e14]
        lea  esi,[edi+0x9e14]
        push  edx
        mov  edx,ebp
        call FUN_004492a0
        push  0xf
        mov  DWORD PTR [esi],0x0
        mov  eax,DWORD PTR [edi+0x9ec8]
        push  0x48
        push  eax
        lea  edi,[esp+0x18]
        call FUN_00448d00
        mov  ecx,DWORD PTR [eax]
        pop  edi
        mov  DWORD PTR [esi],ecx
        pop  ebp
    loc_00409D8C:
        pop  esi
        pop  ecx
        ret
    }
}
