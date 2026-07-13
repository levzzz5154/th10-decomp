// 0043DD10: FUN_0043dd10
// Original size: 224 bytes, actual code: 44 instructions
extern "C" void FUN_00463b2c(void);

extern "C" __declspec(naked) void FUN_0043dd10(void) {
    __asm {
        fld  DWORD PTR [esp+0x4]
        push  ebp
        fmul  DWORD PTR ds:0x470b20
        movsx ebp,WORD PTR [ebx*8+0x4749ce]
        push  edi
        call FUN_00463b2c
        xor  ecx,ecx
        lea  edx,[esi+0x620]
    loc_0043DD31:
        mov  edi,DWORD PTR [edx]
        test  edi,edi
        jl loc_0043DD7A
        cmp  edi,ebx
        je loc_0043DD49
        inc  ecx
        add  edx,0x4
        cmp  ecx,0xc
        jl loc_0043DD31
        pop  edi
        pop  ebp
        ret  0x4
    loc_0043DD49:
        mov  edx,DWORD PTR [esi+ecx*4+0x650]
        cmp  edx,0x80
        jge loc_0043DDA0
        mov  edi,ecx
        shl  edi,0x7
        add  edi,edx
        mov  DWORD PTR [esi+edi*4+0x680],eax
        mov  eax,DWORD PTR [esi+ecx*4+0x650]
        inc  eax
        pop  edi
        mov  DWORD PTR [esi+ecx*4+0x650],eax
        pop  ebp
        ret  0x4
    loc_0043DD7A:
        cmp  ecx,0xc
        jge loc_0043DDA0
        mov  edx,ecx
        shl  edx,0x9
        mov  DWORD PTR [esi+ecx*4+0x620],ebx
        mov  DWORD PTR [esi+ebx*4+0x408],ebp
        mov  DWORD PTR [edx+esi*1+0x680],eax
        inc  DWORD PTR [esi+ecx*4+0x650]
    loc_0043DDA0:
        pop  edi
        pop  ebp
        ret  0x4
    }
}
