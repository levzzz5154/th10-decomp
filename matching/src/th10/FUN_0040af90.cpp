// 0040AF90: FUN_0040af90
// Original size: 384 bytes, actual code: 35 instructions
extern "C" void FUN_0040ae70(void);
extern "C" void FUN_0040af00(void);
extern "C" void operator_new(void);
extern "C" void _free(void);

extern "C" __declspec(naked) void FUN_0040af90(void) {
    __asm {
        push  ebx
        push  0x18
        call operator_new
        add  esp,0x4
        test  eax,eax
        je loc_0040AFC0
        xor  ecx,ecx
        mov  edx,eax
        mov  DWORD PTR [edx],ecx
        mov  DWORD PTR [edx+0x4],ecx
        mov  DWORD PTR [edx+0x8],ecx
        mov  DWORD PTR [edx+0xc],ecx
        mov  DWORD PTR [edx+0x10],ecx
        mov  DWORD PTR [edx+0x14],ecx
        or   DWORD PTR [eax],0x2
        mov  ds:0x4776fc,eax
        mov  ebx,eax
        jmp loc_0040AFC2
    loc_0040AFC0:
        xor  ebx,ebx
    loc_0040AFC2:
        call FUN_0040ae70
        test  eax,eax
        je loc_0040AFE2
        test  ebx,ebx
        je loc_0040AFDE
        push  ebx
        call FUN_0040af00
        push  ebx
        call _free
        add  esp,0x4
    loc_0040AFDE:
        xor  eax,eax
        pop  ebx
        ret
    loc_0040AFE2:
        mov  eax,ebx
        pop  ebx
        ret
    }
}
