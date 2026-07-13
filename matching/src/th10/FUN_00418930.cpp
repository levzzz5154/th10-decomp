// 00418930: FUN_00418930
// Original size: 208 bytes, actual code: 58 instructions
extern "C" void FUN_00448d00(void);
extern "C" void FUN_004492a0(void);

extern "C" __declspec(naked) void FUN_00418930(void) {
    __asm {
        push  ebp
        mov  ebp,DWORD PTR [esp+0x8]
        push  esi
        mov  esi,eax
        mov  ax,WORD PTR [esi+0x8]
        cmp  ax,0x64
        jl loc_00418949
        pop  esi
        xor  eax,eax
        pop  ebp
        ret  0x4
    loc_00418949:
        add  eax,ebp
        cmp  ax,0x64
        mov  WORD PTR [esi+0x8],ax
        jle loc_0041899B
        mov  edx,DWORD PTR ds:0x491c10
        push  ebx
        push  edi
        mov  edi,DWORD PTR ds:0x47770c
        mov  WORD PTR [esi+0x8],0x64
        mov  eax,DWORD PTR [edi+0x9e18]
        lea  ebx,[edi+0x9e18]
        push  eax
        call FUN_004492a0
        push  0xf
        mov  DWORD PTR [ebx],0x0
        mov  ecx,DWORD PTR [edi+0x9ec8]
        push  0x49
        push  ecx
        lea  edi,[esp+0x20]
        call FUN_00448d00
        mov  edx,DWORD PTR [eax]
        pop  edi
        mov  DWORD PTR [ebx],edx
        pop  ebx
    loc_0041899B:
        movsx esi,WORD PTR [esi+0x8]
        movsx eax,bp
        mov  ecx,esi
        sub  ecx,eax
        mov  eax,0x66666667
        imul  ecx
        sar  edx,0x3
        mov  ecx,edx
        shr  ecx,0x1f
        add  ecx,edx
        mov  eax,0x66666667
        imul  esi
        sar  edx,0x3
        mov  eax,edx
        shr  eax,0x1f
        add  eax,edx
        xor  edx,edx
        cmp  ecx,eax
        setne dl
        pop  esi
        pop  ebp
        mov  eax,edx
        ret  0x4
    }
}
