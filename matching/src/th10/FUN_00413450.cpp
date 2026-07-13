// 00413450: FUN_00413450
// Original size: 96 bytes, actual code: 24 instructions
extern "C" void FUN_00449f60(void);
extern "C" void _free(void);

extern "C" __declspec(naked) void FUN_00413450(void) {
    __asm {
        test  ebx,ebx
        je loc_004134A3
        push  esi
        mov  esi,DWORD PTR [ebx+0xc]
        test  esi,esi
        push  edi
        mov  edi,DWORD PTR ds:0x491be4
        je loc_0041348E
        push  0x492274
        call  DWORD PTR ds:0x4660b0
        inc  BYTE PTR ds:0x49231c
        mov  ecx,esi
        mov  edx,edi
        call FUN_00449f60
        push  0x492274
        call  DWORD PTR ds:0x4660b4
        dec  BYTE PTR ds:0x49231c
    loc_0041348E:
        push  ebx
        mov  DWORD PTR ds:0x477708,0x0
        call _free
        add  esp,0x4
        pop  edi
        pop  esi
    loc_004134A3:
        ret
    }
}
