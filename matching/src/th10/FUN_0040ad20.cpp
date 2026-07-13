// 0040AD20: FUN_0040ad20
// Original size: 336 bytes, actual code: 18 instructions

extern "C" __declspec(naked) void FUN_0040ad20(void) {
    __asm {
        mov  eax,DWORD PTR [edx+0x8]
        test  eax,eax
        je loc_0040AD3C
        cmp  ecx,eax
        jl loc_0040AD2F
        dec  eax
        mov  DWORD PTR [edx],eax
        ret
    loc_0040AD2F:
        xor  eax,eax
        test  ecx,ecx
        setl  al
        dec  eax
        and  eax,ecx
        mov  DWORD PTR [edx],eax
        ret
    loc_0040AD3C:
        mov  DWORD PTR [edx],ecx
        mov  eax,ecx
        ret
    }
}
