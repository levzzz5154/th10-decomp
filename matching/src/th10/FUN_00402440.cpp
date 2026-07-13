// 00402440: FUN_00402440
// Original size: 512 bytes, actual code: 125 instructions
extern "C" void FUN_00447810(void);
extern "C" void FUN_00449f60(void);
extern "C" void _free(void);
extern "C" void _free(void);
extern "C" void _eh_vector_destructor_iterator_(void);

extern "C" __declspec(naked) void FUN_00402440(void) {
    __asm {
        push  0xffffffff
        push  0x4652d6
        mov  eax,fs:0x0
        push  eax
        mov  DWORD PTR fs:0x0,esp
        push  ecx
        push  ebx
        push  ebp
        push  esi
        mov  esi,DWORD PTR [esp+0x20]
        push  edi
        mov  DWORD PTR [esp+0x1c],0x1
        mov  edi,DWORD PTR [esi+0x8]
        test  edi,edi
        mov  eax,ds:0x491be4
        mov  ebp,DWORD PTR ds:0x4660b0
        mov  ebx,DWORD PTR ds:0x4660b4
        mov  DWORD PTR [esp+0x10],eax
        je loc_004024A7
        push  0x492274
        call  ebp
        inc  BYTE PTR ds:0x49231c
        mov  edx,DWORD PTR [esp+0x10]
        mov  ecx,edi
        call FUN_00449f60
        push  0x492274
        call  ebx
        dec  BYTE PTR ds:0x49231c
    loc_004024A7:
        mov  edi,DWORD PTR [esi+0xc]
        test  edi,edi
        mov  ecx,DWORD PTR ds:0x491be4
        mov  DWORD PTR [esp+0x10],ecx
        je loc_004024DD
        push  0x492274
        call  ebp
        inc  BYTE PTR ds:0x49231c
        mov  edx,DWORD PTR [esp+0x10]
        mov  ecx,edi
        call FUN_00449f60
        push  0x492274
        call  ebx
        dec  BYTE PTR ds:0x49231c
    loc_004024DD:
        mov  edi,DWORD PTR [esi+0x2a40]
        test  edi,edi
        mov  edx,DWORD PTR ds:0x491be4
        mov  DWORD PTR [esp+0x10],edx
        je loc_00402516
        push  0x492274
        call  ebp
        inc  BYTE PTR ds:0x49231c
        mov  edx,DWORD PTR [esp+0x10]
        mov  ecx,edi
        call FUN_00449f60
        push  0x492274
        call  ebx
        dec  BYTE PTR ds:0x49231c
    loc_00402516:
        mov  eax,DWORD PTR [esi+0x10]
        test  eax,eax
        je loc_0040252D
        push  eax
        call _free
        add  esp,0x4
        mov  DWORD PTR [esi+0x10],0x0
    loc_0040252D:
        mov  eax,DWORD PTR [esi+0x2a44]
        test  eax,eax
        je loc_0040254A
        push  eax
        call _free
        add  esp,0x4
        mov  DWORD PTR [esi+0x2a44],0x0
    loc_0040254A:
        mov  eax,DWORD PTR [esi+0x17c]
        test  eax,eax
        mov  DWORD PTR [esi+0x2a44],0x0
        je loc_00402571
        push  eax
        call _free
        add  esp,0x4
        mov  DWORD PTR [esi+0x17c],0x0
    loc_00402571:
        test  BYTE PTR ds:0x474ca0,0x1
        jne loc_004025BD
        mov  eax,DWORD PTR [esi+0x2a30]
        and  eax,0x1
        add  eax,0x4
        js loc_004025BD
        cmp  eax,0x21
        jae loc_004025BD
        mov  ecx,DWORD PTR ds:0x491c10
        mov  edi,DWORD PTR [ecx+eax*4+0x3ad06c]
        test  edi,edi
        lea  ebp,[ecx+eax*4+0x3ad06c]
        je loc_004025BD
        call FUN_00447810
        mov  eax,DWORD PTR [ebp+0x0]
        push  eax
        call _free
        add  esp,0x4
        mov  DWORD PTR [ebp+0x0],0x0
    loc_004025BD:
        cmp  DWORD PTR ds:0x4776e8,esi
        jne loc_004025CF
        mov  DWORD PTR ds:0x4776e8,0x0
    loc_004025CF:
        cmp  DWORD PTR ds:0x4776e4,esi
        jne loc_004025E1
        mov  DWORD PTR ds:0x4776e4,0x0
    loc_004025E1:
        push  0x401ff0
        push  0x3
        push  0x3ac
        lea  edx,[esi+0x1f08]
        push  edx
        mov  BYTE PTR [esp+0x2c],0x0
        call _eh_vector_destructor_iterator_
        push  0x401ff0
        push  0x8
        push  0x3ac
        add  esi,0x180
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
