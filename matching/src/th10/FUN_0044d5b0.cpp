// 0044D5B0: FUN_0044d5b0
// Original size: 32 bytes, actual code: 11 instructions

extern "C" __declspec(naked) void FUN_0044d5b0(void) {
    __asm {
        mov  eax,DWORD PTR [ecx+0x4]
        test  eax,eax
        jne loc_0044D5BD
        mov  eax,0x800401f0
        ret
    loc_0044D5BD:
        mov  DWORD PTR [ecx+0x30],0x0
        mov  eax,DWORD PTR [eax]
        mov  ecx,DWORD PTR [eax]
        push  eax
        call  DWORD PTR [ecx+0x48]
        ret
    }
}
