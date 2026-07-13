// 0040AF00: FUN_0040af00
// Original size: 144 bytes, actual code: 40 instructions
extern "C" void FUN_00449f60(void);

extern "C" __declspec(naked) void FUN_0040af00(void) {
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
        je loc_0040AF44
        push  0x492274
        call  ebx
        inc  BYTE PTR ds:0x49231c
        mov  ecx,esi
        mov  edx,edi
        call FUN_00449f60
        push  0x492274
        call  ebp
        dec  BYTE PTR ds:0x49231c
    loc_0040AF44:
        mov  ecx,DWORD PTR [esp+0x14]
        mov  esi,DWORD PTR [ecx+0xc]
        test  esi,esi
        mov  edi,DWORD PTR ds:0x491be4
        je loc_0040AF78
        push  0x492274
        call  ebx
        inc  BYTE PTR ds:0x49231c
        mov  ecx,esi
        mov  edx,edi
        call FUN_00449f60
        push  0x492274
        call  ebp
        dec  BYTE PTR ds:0x49231c
    loc_0040AF78:
        pop  edi
        pop  esi
        pop  ebp
        mov  DWORD PTR ds:0x4776fc,0x0
        pop  ebx
        ret  0x4
    }
}
