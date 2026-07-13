// 0042B570: FUN_0042b570
// Original size: 240 bytes, actual code: 64 instructions
extern "C" void FUN_00449f60(void);
extern "C" void _free(void);

extern "C" __declspec(naked) void FUN_0042b570(void) {
    __asm {
        mov  eax,fs:0x0
        push  0xffffffff
        push  0x46523b
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
        je loc_0042B5CF
        push  0x492274
        call  ebp
        inc  BYTE PTR ds:0x49231c
        mov  ecx,esi
        mov  edx,edi
        call FUN_00449f60
        push  0x492274
        call  DWORD PTR ds:0x4660b4
        dec  BYTE PTR ds:0x49231c
    loc_0042B5CF:
        mov  esi,DWORD PTR [ebx+0xc]
        test  esi,esi
        mov  edi,DWORD PTR ds:0x491be4
        je loc_0042B603
        push  0x492274
        call  ebp
        inc  BYTE PTR ds:0x49231c
        mov  ecx,esi
        mov  edx,edi
        call FUN_00449f60
        push  0x492274
        call  DWORD PTR ds:0x4660b4
        dec  BYTE PTR ds:0x49231c
    loc_0042B603:
        mov  eax,DWORD PTR [ebx+0x370]
        xor  ecx,ecx
        cmp  eax,ecx
        mov  DWORD PTR ds:0x477840,ecx
        je loc_0042B63D
        push  eax
        call _free
        add  esp,0x4
        mov  DWORD PTR [ebx+0x370],0x0
        mov  ecx,DWORD PTR [esp+0x10]
        mov  DWORD PTR fs:0x0,ecx
        pop  edi
        pop  esi
        pop  ebp
        pop  ebx
        add  esp,0xc
        ret  0x4
    loc_0042B63D:
        pop  edi
        mov  DWORD PTR [ebx+0x370],ecx
        mov  ecx,DWORD PTR [esp+0xc]
        pop  esi
        pop  ebp
        mov  DWORD PTR fs:0x0,ecx
        pop  ebx
        add  esp,0xc
        ret  0x4
    }
}
