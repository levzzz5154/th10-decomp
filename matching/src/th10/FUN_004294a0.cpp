// 004294A0: FUN_004294a0
// Original size: 368 bytes, actual code: 105 instructions
extern "C" void FUN_0042ab20(void);
extern "C" void FUN_00449f60(void);
extern "C" void _free(void);
extern "C" void _eh_vector_destructor_iterator_(void);

extern "C" __declspec(naked) void FUN_004294a0(void) {
    __asm {
        push  0xffffffff
        push  0x465268
        mov  eax,fs:0x0
        push  eax
        mov  DWORD PTR fs:0x0,esp
        push  ecx
        push  ebx
        push  ebp
        push  esi
        push  edi
        mov  edi,DWORD PTR [esp+0x24]
        xor  ebp,ebp
        mov  DWORD PTR [esp+0x1c],ebp
        mov  eax,DWORD PTR [edi+0x14]
        push  eax
        call _free
        add  esp,0x4
        xor  esi,esi
    loc_004294D2:
        mov  eax,esi
        mov  ecx,edi
        call FUN_0042ab20
        inc  esi
        cmp  esi,0x8
        jl loc_004294D2
        mov  eax,DWORD PTR [edi+0x18]
        push  eax
        call _free
        add  esp,0x4
        mov  DWORD PTR [edi+0x18],ebp
        lea  esi,[edi+0x1c]
        mov  ebx,0x8
    loc_004294F8:
        mov  eax,DWORD PTR [esi]
        push  eax
        call _free
        mov  DWORD PTR [esi],ebp
        add  esp,0x4
        add  esi,0x4
        dec  ebx
        jne loc_004294F8
        mov  esi,DWORD PTR [edi+0x8]
        mov  ebx,DWORD PTR ds:0x4660b0
        cmp  esi,ebp
        mov  ebp,DWORD PTR ds:0x4660b4
        je loc_0042954C
        mov  eax,ds:0x491be4
        push  0x492274
        mov  DWORD PTR [esp+0x14],eax
        call  ebx
        inc  BYTE PTR ds:0x49231c
        mov  edx,DWORD PTR [esp+0x10]
        mov  ecx,esi
        call FUN_00449f60
        push  0x492274
        call  ebp
        dec  BYTE PTR ds:0x49231c
    loc_0042954C:
        mov  eax,DWORD PTR [edi+0x1cc]
        test  eax,eax
        mov  DWORD PTR [esp+0x10],eax
        je loc_0042958D
        mov  esi,DWORD PTR ds:0x491be4
        push  0x492274
        call  ebx
        mov  dl,BYTE PTR ds:0x49231c
        mov  ecx,DWORD PTR [esp+0x10]
        inc  dl
        mov  BYTE PTR ds:0x49231c,dl
        mov  edx,esi
        call FUN_00449f60
        push  0x492274
        call  ebp
        dec  BYTE PTR ds:0x49231c
    loc_0042958D:
        mov  eax,DWORD PTR [edi+0xc]
        test  eax,eax
        mov  DWORD PTR [esp+0x10],eax
        je loc_004295CB
        mov  esi,DWORD PTR ds:0x491be4
        push  0x492274
        call  ebx
        mov  dl,BYTE PTR ds:0x49231c
        mov  ecx,DWORD PTR [esp+0x10]
        inc  dl
        mov  BYTE PTR ds:0x49231c,dl
        mov  edx,esi
        call FUN_00449f60
        push  0x492274
        call  ebp
        dec  BYTE PTR ds:0x49231c
    loc_004295CB:
        cmp  edi,DWORD PTR ds:0x477838
        jne loc_004295DD
        mov  DWORD PTR ds:0x477838,0x0
    loc_004295DD:
        push  0x42ac60
        push  0x8
        push  0x24
        add  edi,0xa0
        push  edi
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
