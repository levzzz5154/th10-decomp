// 00405F70: FUN_00405f70
// Original size: 240 bytes, actual code: 61 instructions
extern "C" void FUN_004493e0(void);
extern "C" void FUN_00449f60(void);
extern "C" void _eh_vector_destructor_iterator_(void);

extern "C" __declspec(naked) void FUN_00405f70(void) {
    __asm {
        mov  eax,fs:0x0
        push  0xffffffff
        push  0x46553c
        push  eax
        mov  DWORD PTR fs:0x0,esp
        push  ebx
        push  ebp
        push  esi
        push  edi
        mov  DWORD PTR [esp+0x18],0x0
        mov  eax,DWORD PTR [esp+0x20]
        mov  esi,DWORD PTR [eax+0x8]
        test  esi,esi
        mov  edi,DWORD PTR ds:0x491be4
        mov  ebx,DWORD PTR ds:0x4660b0
        mov  ebp,DWORD PTR ds:0x4660b4
        je loc_00405FD1
        push  0x492274
        call  ebx
        inc  BYTE PTR ds:0x49231c
        mov  ecx,esi
        mov  edx,edi
        call FUN_00449f60
        push  0x492274
        call  ebp
        dec  BYTE PTR ds:0x49231c
    loc_00405FD1:
        mov  ecx,DWORD PTR [esp+0x20]
        mov  esi,DWORD PTR [ecx+0xc]
        test  esi,esi
        mov  edi,DWORD PTR ds:0x491be4
        je loc_00406005
        push  0x492274
        call  ebx
        inc  BYTE PTR ds:0x49231c
        mov  ecx,esi
        mov  edx,edi
        call FUN_00449f60
        push  0x492274
        call  ebp
        dec  BYTE PTR ds:0x49231c
    loc_00406005:
        mov  edx,DWORD PTR [esp+0x20]
        mov  edx,DWORD PTR [edx+0x3e0b50]
        mov  eax,ds:0x491c10
        call FUN_004493e0
        push  0x405de0
        mov  DWORD PTR [esp+0x1c],0xffffffff
        mov  eax,DWORD PTR [esp+0x24]
        push  0x7d1
        push  0x7f0
        add  eax,0x60
        push  eax
        mov  DWORD PTR ds:0x4776f0,0x0
        call _eh_vector_destructor_iterator_
        mov  ecx,DWORD PTR [esp+0x10]
        pop  edi
        pop  esi
        pop  ebp
        mov  DWORD PTR fs:0x0,ecx
        pop  ebx
        add  esp,0xc
        ret  0x4
    }
}
