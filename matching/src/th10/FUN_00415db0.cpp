// 00415DB0: FUN_00415db0
// Original size: 224 bytes, actual code: 33 instructions
extern "C" void FUN_00415b00(void);
extern "C" void operator_new(void);

extern "C" __declspec(naked) void FUN_00415db0(void) {
    __asm {
        push  0xffffffff
        push  0x46582b
        mov  eax,fs:0x0
        push  eax
        mov  DWORD PTR fs:0x0,esp
        push  ecx
        push  0x90
        call operator_new
        add  esp,0x4
        mov  DWORD PTR [esp],eax
        test  eax,eax
        mov  DWORD PTR [esp+0xc],0x0
        je loc_00415DF7
        mov  ecx,DWORD PTR [edi+0x9ebc]
        mov  edx,DWORD PTR [ecx+esi*8+0x4]
        add  edx,ecx
        push  edx
        push  eax
        call FUN_00415b00
        jmp loc_00415DF9
    loc_00415DF7:
        xor  eax,eax
    loc_00415DF9:
        mov  DWORD PTR [edi+0x9eb8],eax
        mov  DWORD PTR [eax],esi
        mov  ecx,DWORD PTR ds:0x474c84
        lea  eax,[esi+0x1]
        cmp  ecx,eax
        mov  ds:0x474c84,eax
        je loc_00415E1D
        mov  DWORD PTR ds:0x474c8c,0x0
    loc_00415E1D:
        mov  ecx,DWORD PTR [esp+0x4]
        mov  DWORD PTR fs:0x0,ecx
        add  esp,0x10
        ret
    }
}
