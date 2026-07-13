// 00408AF0: FUN_00408af0
// Original size: 416 bytes, actual code: 104 instructions
extern "C" void FUN_004492a0(void);
extern "C" void FUN_00449f60(void);
extern "C" void _eh_vector_destructor_iterator_(void);

extern "C" __declspec(naked) void FUN_00408af0(void) {
    __asm {
        push  0xffffffff
        push  0x46560f
        mov  eax,fs:0x0
        push  eax
        mov  DWORD PTR fs:0x0,esp
        push  ecx
        push  ebx
        push  ebp
        push  esi
        mov  esi,DWORD PTR [esp+0x20]
        push  edi
        mov  DWORD PTR [esp+0x1c],0x2
        mov  eax,DWORD PTR [esi+0x768]
        mov  edi,DWORD PTR ds:0x491c10
        push  eax
        mov  edx,edi
        call FUN_004492a0
        xor  ebx,ebx
        mov  DWORD PTR [esi+0x768],ebx
        mov  ecx,DWORD PTR [esi+0x76c]
        push  ecx
        mov  edx,edi
        call FUN_004492a0
        mov  DWORD PTR [esi+0x76c],ebx
        mov  edx,DWORD PTR [esi+0x770]
        push  edx
        mov  edx,edi
        call FUN_004492a0
        mov  ebp,DWORD PTR ds:0x491be4
        mov  DWORD PTR [esi+0x770],ebx
        mov  edi,DWORD PTR [esi+0x8]
        cmp  edi,ebx
        mov  ebx,DWORD PTR ds:0x4660b0
        je loc_00408B98
        push  0x492274
        call  ebx
        inc  BYTE PTR ds:0x49231c
        mov  ecx,edi
        mov  edx,ebp
        call FUN_00449f60
        mov  ebp,DWORD PTR ds:0x4660b4
        push  0x492274
        call  ebp
        dec  BYTE PTR ds:0x49231c
        jmp loc_00408B9E
    loc_00408B98:
        mov  ebp,DWORD PTR ds:0x4660b4
    loc_00408B9E:
        mov  edi,DWORD PTR [esi+0xc]
        test  edi,edi
        mov  eax,ds:0x491be4
        mov  DWORD PTR [esp+0x10],eax
        je loc_00408BD3
        push  0x492274
        call  ebx
        inc  BYTE PTR ds:0x49231c
        mov  edx,DWORD PTR [esp+0x10]
        mov  ecx,edi
        call FUN_00449f60
        push  0x492274
        call  ebp
        dec  BYTE PTR ds:0x49231c
    loc_00408BD3:
        mov  edi,DWORD PTR [esi+0x37ac]
        test  edi,edi
        mov  ecx,DWORD PTR ds:0x491be4
        mov  DWORD PTR [esp+0x10],ecx
        je loc_00408C0C
        push  0x492274
        call  ebx
        inc  BYTE PTR ds:0x49231c
        mov  edx,DWORD PTR [esp+0x10]
        mov  ecx,edi
        call FUN_00449f60
        push  0x492274
        call  ebp
        dec  BYTE PTR ds:0x49231c
    loc_00408C0C:
        push  0x401ff0
        push  0x5
        push  0x3ac
        lea  edx,[esi+0x24d8]
        push  edx
        mov  DWORD PTR ds:0x4776f4,0x0
        mov  BYTE PTR [esp+0x2c],0x1
        call _eh_vector_destructor_iterator_
        push  0x401ff0
        push  0x8
        push  0x3ac
        lea  eax,[esi+0x778]
        push  eax
        mov  BYTE PTR [esp+0x2c],0x0
        call _eh_vector_destructor_iterator_
        push  0x401ff0
        push  0x2
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
