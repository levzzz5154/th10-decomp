// 0041C1C0: FUN_0041c1c0
// Original size: 208 bytes, actual code: 62 instructions
extern "C" void FUN_00449f60(void);
extern "C" void _free(void);

extern "C" __declspec(naked) void FUN_0041c1c0(void) {
    __asm {
        mov  eax,DWORD PTR [esp+0x4]
        push  ebx
        mov  ebx,DWORD PTR ds:0x4660b0
        push  ebp
        mov  ebp,DWORD PTR ds:0x4660b4
        push  esi
        mov  esi,DWORD PTR [eax+0x8]
        test  esi,esi
        push  edi
        mov  edi,DWORD PTR ds:0x491be4
        je loc_0041C204
        push  0x492274
        call  ebx
        inc  BYTE PTR ds:0x49231c
        mov  ecx,esi
        mov  edx,edi
        call FUN_00449f60
        push  0x492274
        call  ebp
        dec  BYTE PTR ds:0x49231c
    loc_0041C204:
        mov  ecx,DWORD PTR [esp+0x14]
        mov  esi,DWORD PTR [ecx+0xc]
        test  esi,esi
        mov  edi,DWORD PTR ds:0x491be4
        je loc_0041C238
        push  0x492274
        call  ebx
        inc  BYTE PTR ds:0x49231c
        mov  ecx,esi
        mov  edx,edi
        call FUN_00449f60
        push  0x492274
        call  ebp
        dec  BYTE PTR ds:0x49231c
    loc_0041C238:
        mov  edx,DWORD PTR [esp+0x14]
        mov  esi,DWORD PTR [edx+0x18]
        test  esi,esi
        je loc_0041C272
    loc_0041C243:
        mov  eax,DWORD PTR [esi]
        mov  edi,DWORD PTR [esi+0x8]
        mov  ecx,esi
        call  DWORD PTR [eax+0x10]
        mov  ecx,DWORD PTR [esi+0x4]
        mov  edx,DWORD PTR [esi+0x8]
        mov  DWORD PTR [ecx+0x8],edx
        mov  eax,DWORD PTR [esi+0x8]
        test  eax,eax
        je loc_0041C263
        mov  ecx,DWORD PTR [esi+0x4]
        mov  DWORD PTR [eax+0x4],ecx
    loc_0041C263:
        push  esi
        call _free
        add  esp,0x4
        test  edi,edi
        mov  esi,edi
        jne loc_0041C243
    loc_0041C272:
        pop  edi
        pop  esi
        pop  ebp
        mov  DWORD PTR ds:0x47781c,0x0
        pop  ebx
        ret  0x4
    }
}
