// 00424ED0: FUN_00424ed0
// Original size: 336 bytes, actual code: 81 instructions
extern "C" void FUN_00447810(void);
extern "C" void FUN_004493e0(void);
extern "C" void FUN_00449f60(void);
extern "C" void _free(void);
extern "C" void _free(void);

extern "C" __declspec(naked) void FUN_00424ed0(void) {
    __asm {
        mov  eax,fs:0x0
        push  0xffffffff
        push  0x46528b
        push  eax
        mov  DWORD PTR fs:0x0,esp
        push  ebx
        mov  ebx,DWORD PTR [esp+0x14]
        push  ebp
        push  esi
        push  edi
        mov  DWORD PTR [esp+0x18],0x0
        mov  esi,DWORD PTR [ebx+0x8]
        test  esi,esi
        mov  edi,DWORD PTR ds:0x491be4
        mov  ebp,DWORD PTR ds:0x4660b0
        je loc_00424F2F
        push  0x492274
        call  ebp
        inc  BYTE PTR ds:0x49231c
        mov  ecx,esi
        mov  edx,edi
        call FUN_00449f60
        push  0x492274
        call  DWORD PTR ds:0x4660b4
        dec  BYTE PTR ds:0x49231c
    loc_00424F2F:
        mov  esi,DWORD PTR [ebx+0xc]
        test  esi,esi
        mov  edi,DWORD PTR ds:0x491be4
        je loc_00424F63
        push  0x492274
        call  ebp
        inc  BYTE PTR ds:0x49231c
        mov  ecx,esi
        mov  edx,edi
        call FUN_00449f60
        push  0x492274
        call  DWORD PTR ds:0x4660b4
        dec  BYTE PTR ds:0x49231c
    loc_00424F63:
        test  BYTE PTR ds:0x474ca0,0x1
        mov  DWORD PTR ds:0x477834,0x0
        je loc_00424F90
        mov  edx,DWORD PTR [ebx+0x10]
        mov  eax,ds:0x491c10
        call FUN_004493e0
        mov  eax,DWORD PTR [ebx+0x45c]
        mov  ds:0x491bf0,eax
        jmp loc_00424FE3
    loc_00424F90:
        mov  esi,DWORD PTR ds:0x491c10
        mov  edi,DWORD PTR [esi+0x3ad08c]
        add  esi,0x3ad08c
        test  edi,edi
        je loc_00424FBC
        call FUN_00447810
        mov  ecx,DWORD PTR [esi]
        push  ecx
        call _free
        add  esp,0x4
        mov  DWORD PTR [esi],0x0
    loc_00424FBC:
        mov  eax,DWORD PTR [ebx+0x45c]
        test  eax,eax
        je loc_00424FD9
        push  eax
        call _free
        add  esp,0x4
        mov  DWORD PTR [ebx+0x45c],0x0
    loc_00424FD9:
        mov  DWORD PTR ds:0x491bf0,0x0
    loc_00424FE3:
        mov  eax,DWORD PTR [ebx+0x36c]
        test  eax,eax
        je loc_00424FF6
        push  eax
        call _free
        add  esp,0x4
    loc_00424FF6:
        mov  ecx,DWORD PTR [esp+0x10]
        pop  edi
        pop  esi
        mov  DWORD PTR [ebx+0x36c],0x0
        pop  ebp
        mov  DWORD PTR fs:0x0,ecx
        pop  ebx
        add  esp,0xc
        ret  0x4
    }
}
