// 0042A8A0: FUN_0042a8a0
// Original size: 144 bytes, actual code: 22 instructions

extern "C" __declspec(naked) void FUN_0042a8a0(void) {
    __asm {
        mov  ecx,DWORD PTR [eax+0x5460]
        mov  WORD PTR [ecx],dx
        mov  ecx,DWORD PTR [eax+0x5460]
        mov  dx,WORD PTR [esp+0x4]
        mov  WORD PTR [ecx+0x2],dx
        mov  ecx,DWORD PTR [eax+0x5460]
        mov  dx,WORD PTR [esp+0x8]
        mov  WORD PTR [ecx+0x4],dx
        mov  ecx,DWORD PTR [eax+0x5460]
        add  ecx,0x6
        mov  DWORD PTR [eax+0x5460],ecx
        sub  ecx,eax
        mov  eax,0x2aaaaaab
        imul  ecx
        mov  eax,edx
        shr  eax,0x1f
        add  eax,edx
        xor  ecx,ecx
        cmp  eax,0xe10
        setge cl
        mov  eax,ecx
        ret  0x8
    }
}
