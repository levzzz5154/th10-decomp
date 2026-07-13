// 00401260: FUN_00401260
// Original size: 480 bytes, actual code: 123 instructions
extern "C" void FUN_00447810(void);
extern "C" void FUN_00449f60(void);
extern "C" void _free(void);
extern "C" void _free(void);

extern "C" __declspec(naked) void FUN_00401260(void) {
    __asm {
        push  0xffffffff
        push  0x4652f9
        mov  eax,fs:0x0
        push  eax
        mov  DWORD PTR fs:0x0,esp
        push  ecx
        push  ebx
        push  ebp
        mov  ebp,DWORD PTR [esp+0x1c]
        push  esi
        push  edi
        mov  DWORD PTR [ebp+0x0],0x46cb14
        mov  DWORD PTR [esp+0x1c],0x1
        mov  esi,DWORD PTR [ebp+0xc]
        test  esi,esi
        mov  eax,ds:0x491be4
        mov  edi,DWORD PTR ds:0x4660b0
        mov  ebx,DWORD PTR ds:0x4660b4
        mov  DWORD PTR [esp+0x10],eax
        je loc_004012CE
        push  0x492274
        call  edi
        inc  BYTE PTR ds:0x49231c
        mov  edx,DWORD PTR [esp+0x10]
        mov  ecx,esi
        call FUN_00449f60
        push  0x492274
        call  ebx
        dec  BYTE PTR ds:0x49231c
    loc_004012CE:
        mov  esi,DWORD PTR [ebp+0x10]
        test  esi,esi
        mov  ecx,DWORD PTR ds:0x491be4
        mov  DWORD PTR [esp+0x10],ecx
        je loc_00401304
        push  0x492274
        call  edi
        inc  BYTE PTR ds:0x49231c
        mov  edx,DWORD PTR [esp+0x10]
        mov  ecx,esi
        call FUN_00449f60
        push  0x492274
        call  ebx
        dec  BYTE PTR ds:0x49231c
    loc_00401304:
        mov  esi,DWORD PTR [ebp+0x89a8]
        test  esi,esi
        mov  edx,DWORD PTR ds:0x491be4
        mov  DWORD PTR [esp+0x10],edx
        je loc_0040133D
        push  0x492274
        call  edi
        inc  BYTE PTR ds:0x49231c
        mov  edx,DWORD PTR [esp+0x10]
        mov  ecx,esi
        call FUN_00449f60
        push  0x492274
        call  ebx
        dec  BYTE PTR ds:0x49231c
    loc_0040133D:
        mov  esi,DWORD PTR ds:0x491c10
        mov  edi,DWORD PTR [esi+0x3ad074]
        add  esi,0x3ad074
        test  edi,edi
        je loc_00401369
        call FUN_00447810
        mov  eax,DWORD PTR [esi]
        push  eax
        call _free
        add  esp,0x4
        mov  DWORD PTR [esi],0x0
    loc_00401369:
        mov  esi,DWORD PTR ds:0x491c10
        mov  edi,DWORD PTR [esi+0x3ad06c]
        add  esi,0x3ad06c
        test  edi,edi
        je loc_00401395
        call FUN_00447810
        mov  ecx,DWORD PTR [esi]
        push  ecx
        call _free
        add  esp,0x4
        mov  DWORD PTR [esi],0x0
    loc_00401395:
        mov  esi,DWORD PTR ds:0x491c10
        mov  edi,DWORD PTR [esi+0x3ad078]
        add  esi,0x3ad078
        test  edi,edi
        je loc_004013C1
        call FUN_00447810
        mov  edx,DWORD PTR [esi]
        push  edx
        call _free
        add  esp,0x4
        mov  DWORD PTR [esi],0x0
    loc_004013C1:
        mov  eax,DWORD PTR [ebp+0x718]
        test  eax,eax
        mov  DWORD PTR ds:0x4776e0,0x0
        je loc_004013DE
        push  eax
        call _free
        add  esp,0x4
    loc_004013DE:
        xor  ecx,ecx
        mov  DWORD PTR [ebp+0x718],ecx
        mov  eax,DWORD PTR [ebp+0x36c]
        cmp  eax,ecx
        je loc_00401418
        push  eax
        call _free
        add  esp,0x4
        pop  edi
        pop  esi
        mov  DWORD PTR [ebp+0x36c],0x0
        pop  ebp
        pop  ebx
        mov  ecx,DWORD PTR [esp+0x4]
        mov  DWORD PTR fs:0x0,ecx
        add  esp,0x10
        ret  0x4
    loc_00401418:
        pop  edi
        mov  DWORD PTR [ebp+0x36c],ecx
        mov  ecx,DWORD PTR [esp+0x10]
        pop  esi
        pop  ebp
        pop  ebx
        mov  DWORD PTR fs:0x0,ecx
        add  esp,0x10
        ret  0x4
    }
}
