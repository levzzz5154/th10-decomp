// 004145F0: FUN_004145f0
// Original size: 576 bytes, actual code: 161 instructions
extern "C" void FUN_00414370(void);
extern "C" void FUN_004492a0(void);
extern "C" void FUN_004493e0(void);
extern "C" void FUN_00449f60(void);
extern "C" void _free(void);
extern "C" void _eh_vector_destructor_iterator_(void);

extern "C" __declspec(naked) void FUN_004145f0(void) {
    __asm {
        push  0xffffffff
        push  0x46574e
        mov  eax,fs:0x0
        push  eax
        mov  DWORD PTR fs:0x0,esp
        push  ecx
        push  ebx
        push  ebp
        push  esi
        mov  esi,DWORD PTR [esp+0x20]
        push  edi
        push  esi
        mov  DWORD PTR [esp+0x20],0x6
        call FUN_00414370
        mov  edi,DWORD PTR [esi+0x8]
        test  edi,edi
        mov  ebp,DWORD PTR ds:0x491be4
        mov  ebx,DWORD PTR ds:0x4660b0
        je loc_00414656
        push  0x492274
        call  ebx
        inc  BYTE PTR ds:0x49231c
        mov  ecx,edi
        mov  edx,ebp
        call FUN_00449f60
        push  0x492274
        call  DWORD PTR ds:0x4660b4
        dec  BYTE PTR ds:0x49231c
    loc_00414656:
        mov  edi,DWORD PTR [esi+0xc]
        test  edi,edi
        mov  ebp,DWORD PTR ds:0x491be4
        je loc_0041468A
        push  0x492274
        call  ebx
        inc  BYTE PTR ds:0x49231c
        mov  ecx,edi
        mov  edx,ebp
        call FUN_00449f60
        push  0x492274
        call  DWORD PTR ds:0x4660b4
        dec  BYTE PTR ds:0x49231c
    loc_0041468A:
        mov  ebp,DWORD PTR ds:0x491c10
        mov  DWORD PTR [esi+0x8],0x0
        mov  eax,DWORD PTR [esi+0x9e50]
        push  eax
        mov  edx,ebp
        call FUN_004492a0
        xor  edi,edi
        mov  DWORD PTR [esi+0x9e50],edi
        lea  ebx,[esi+0x9df4]
        mov  DWORD PTR [esp+0x10],0x8
        jmp loc_004146C0
        nop
    loc_004146C0:
        mov  edx,DWORD PTR [ebx]
        cmp  edx,edi
        je loc_0041472F
        mov  eax,DWORD PTR [ebp+0x72dad4]
        cmp  eax,edi
        je loc_004146DD
    loc_004146D0:
        mov  ecx,DWORD PTR [eax]
        cmp  DWORD PTR [ecx],edx
        je loc_004146F6
        mov  eax,DWORD PTR [eax+0x4]
        cmp  eax,edi
        jne loc_004146D0
    loc_004146DD:
        mov  eax,DWORD PTR [ebp+0x72dadc]
        cmp  eax,edi
        je loc_0041472F
    loc_004146E7:
        mov  ecx,DWORD PTR [eax]
        cmp  DWORD PTR [ecx],edx
        je loc_004146F6
        mov  eax,DWORD PTR [eax+0x4]
        cmp  eax,edi
        jne loc_004146E7
        jmp loc_0041472F
    loc_004146F6:
        mov  eax,DWORD PTR [eax]
        cmp  eax,edi
        je loc_0041472F
        mov  ecx,DWORD PTR [eax+0x35c]
        mov  edx,0x4000000
        or   ecx,edx
        mov  DWORD PTR [eax+0x35c],ecx
        cmp  DWORD PTR [eax+0x18],edi
        jne loc_0041472F
        mov  eax,DWORD PTR [eax+0x14]
        cmp  eax,edi
        je loc_0041472F
        jmp loc_00414720
        nop
    loc_00414720:
        mov  ecx,DWORD PTR [eax]
        or   DWORD PTR [ecx+0x35c],edx
        mov  eax,DWORD PTR [eax+0x4]
        cmp  eax,edi
        jne loc_00414720
    loc_0041472F:
        mov  eax,DWORD PTR [esp+0x10]
        mov  DWORD PTR [ebx],edi
        add  ebx,0x4
        dec  eax
        mov  DWORD PTR [esp+0x10],eax
        jne loc_004146C0
        mov  edx,DWORD PTR [esi+0x9ec8]
        mov  eax,ebp
        call FUN_004493e0
        mov  eax,DWORD PTR [esi+0x9da0]
        cmp  eax,edi
        mov  DWORD PTR ds:0x47770c,edi
        je loc_00414765
        push  eax
        call _free
        add  esp,0x4
    loc_00414765:
        push  0x401ff0
        push  0x7
        push  0x3ac
        lea  ecx,[esi+0x8094]
        push  ecx
        mov  DWORD PTR [esi+0x9da0],edi
        mov  BYTE PTR [esp+0x2c],0x4
        call _eh_vector_destructor_iterator_
        push  0x401ff0
        push  0x2
        push  0x3ac
        lea  edx,[esi+0x793c]
        push  edx
        mov  BYTE PTR [esp+0x2c],0x3
        call _eh_vector_destructor_iterator_
        push  0x401ff0
        push  0x4
        push  0x3ac
        lea  eax,[esi+0x6a8c]
        push  eax
        mov  BYTE PTR [esp+0x2c],0x2
        call _eh_vector_destructor_iterator_
        push  0x401ff0
        push  0x9
        push  0x3ac
        lea  ecx,[esi+0x4980]
        push  ecx
        mov  BYTE PTR [esp+0x2c],0x1
        call _eh_vector_destructor_iterator_
        push  0x401ff0
        push  0xa
        push  0x3ac
        lea  edx,[esi+0x24c8]
        push  edx
        mov  BYTE PTR [esp+0x2c],0x0
        call _eh_vector_destructor_iterator_
        push  0x401ff0
        push  0xa
        push  0x3ac
        add  esi,0x10
        push  esi
        mov  DWORD PTR [esp+0x2c],0xffffffff
        call _eh_vector_destructor_iterator_
        mov  ecx,DWORD PTR [esp+0x14]
        pop  edi
        pop  esi
        pop  ebp
        pop  ebx
        mov  DWORD PTR fs:0x0,ecx
        add  esp,0x10
        ret  0x4
    }
}
