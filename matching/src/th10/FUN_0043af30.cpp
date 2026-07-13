// 0043AF30: FUN_0043af30
// Original size: 480 bytes, actual code: 146 instructions
extern "C" void FUN_0043ace0(void);
extern "C" void FUN_0043b110(void);
extern "C" void FUN_0043b7a0(void);
extern "C" void __allmul(void);
extern "C" void __aulldiv(void);
extern "C" void FUN_00463b2c(void);

extern "C" __declspec(naked) void FUN_0043af30(void) {
    __asm {
        sub  esp,0xc
        push  ebx
        push  ebp
        push  esi
        push  edi
        mov  edi,ecx
        mov  ecx,DWORD PTR [edi+0x12c]
        mov  eax,DWORD PTR [edi+0x120]
        push  ecx
        mov  ecx,DWORD PTR [edi+0x128]
        cdq
        push  ecx
        push  edx
        xor  ebp,ebp
        push  eax
        mov  DWORD PTR [esp+0x24],ebp
        call __allmul
        push  ebp
        push  0x3e8
        push  edx
        push  eax
        call __allmul
        mov  ecx,eax
        mov  eax,DWORD PTR [edi+0x124]
        mov  esi,edx
        cdq
        push  edx
        push  eax
        push  esi
        push  ecx
        call __aulldiv
        mov  ecx,DWORD PTR [edi+0x134]
        mov  esi,edx
        mov  edx,DWORD PTR [edi+0x130]
        mov  ebx,eax
        mov  eax,DWORD PTR [edi+0x2e0]
        add  ebx,edx
        adc  esi,ecx
        cmp  eax,ebp
        je loc_0043B000
        mov  eax,DWORD PTR [edi+0x2e8]
        mov  ecx,DWORD PTR [edi+0x2e4]
        cmp  eax,ecx
        mov  DWORD PTR [esp+0x10],eax
        mov  DWORD PTR [esp+0x18],ecx
        jge loc_0043B0FB
        fild  DWORD PTR [esp+0x10]
        fidiv DWORD PTR [esp+0x18]
        fsubr DWORD PTR ds:0x470afc
        fst  DWORD PTR [edi+0x2c8]
        fmul  DWORD PTR ds:0x470bf4
        call FUN_00463b2c
        cmp  eax,DWORD PTR [edi+0x2cc]
        je loc_0043AFE3
        push  ebp
        call FUN_0043b7a0
    loc_0043AFE3:
        fld  DWORD PTR [edi+0x2c8]
        fmul  DWORD PTR ds:0x470bf4
        call FUN_00463b2c
        mov  DWORD PTR [edi+0x2cc],eax
        inc  DWORD PTR [edi+0x2e8]
    loc_0043B000:
        cmp  DWORD PTR [edi+0x118],ebp
        mov  DWORD PTR [esp+0x10],ebp
        jle loc_0043B0C9
    loc_0043B010:
        mov  edx,DWORD PTR [edi+0x138]
        cmp  DWORD PTR [edx+ebp*1],0x0
        je loc_0043B0AD
        mov  DWORD PTR [esp+0x14],0x1
        jmp loc_0043B030
        lea  ebx,[ebx+0x0]
    loc_0043B030:
        mov  eax,DWORD PTR [edi+0x138]
        lea  ecx,[eax+ebp*1]
        mov  eax,DWORD PTR [ecx+0x4]
        cdq
        cmp  edx,esi
        ja loc_0043B0AD
        jb loc_0043B047
        cmp  eax,ebx
        ja loc_0043B0AD
    loc_0043B047:
        push  ecx
        push  edi
        call FUN_0043b110
        mov  ecx,DWORD PTR [edi+0x12c]
        mov  eax,DWORD PTR [edi+0x120]
        push  ecx
        mov  ecx,DWORD PTR [edi+0x128]
        cdq
        push  ecx
        push  edx
        push  eax
        call __allmul
        push  0x0
        push  0x3e8
        push  edx
        push  eax
        call __allmul
        mov  ecx,eax
        mov  eax,DWORD PTR [edi+0x124]
        mov  esi,edx
        cdq
        push  edx
        push  eax
        push  esi
        push  ecx
        call __aulldiv
        mov  ecx,DWORD PTR [edi+0x134]
        mov  esi,edx
        mov  edx,DWORD PTR [edi+0x130]
        mov  ebx,eax
        add  ebx,edx
        mov  edx,DWORD PTR [edi+0x138]
        mov  eax,DWORD PTR [edx+ebp*1]
        adc  esi,ecx
        test  eax,eax
        jne loc_0043B030
    loc_0043B0AD:
        mov  eax,DWORD PTR [esp+0x10]
        mov  ecx,DWORD PTR [edi+0x118]
        inc  eax
        add  ebp,0x20
        cmp  eax,ecx
        mov  DWORD PTR [esp+0x10],eax
        jl loc_0043B010
        xor  ebp,ebp
    loc_0043B0C9:
        mov  edx,DWORD PTR [edi+0x128]
        mov  ecx,DWORD PTR [edi+0x12c]
        mov  eax,DWORD PTR [esp+0x14]
        add  edx,0x1
        adc  ecx,ebp
        cmp  eax,ebp
        mov  DWORD PTR [edi+0x128],edx
        mov  DWORD PTR [edi+0x12c],ecx
        jne loc_0043B0F3
        call FUN_0043ace0
    loc_0043B0F3:
        pop  edi
        pop  esi
        pop  ebp
        pop  ebx
        add  esp,0xc
        ret
    loc_0043B0FB:
        mov  DWORD PTR [edi+0x2c8],ebp
        pop  edi
        pop  esi
        pop  ebp
        pop  ebx
        add  esp,0xc
        ret
    }
}
