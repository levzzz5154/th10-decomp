// 0044D600: FUN_0044d600
// Original size: 160 bytes, actual code: 70 instructions

extern "C" __declspec(naked) void FUN_0044d600(void) {
    __asm {
        mov  eax,DWORD PTR [edi+0x4]
        test  eax,eax
        jne loc_0044D60D
        mov  eax,0x800401f0
        ret
    loc_0044D60D:
        mov  eax,DWORD PTR [edi+0x10]
        push  ebx
        push  esi
        xor  ebx,ebx
        xor  esi,esi
        test  eax,eax
        jbe loc_0044D638
        lea  ebx,[ebx+0x0]
    loc_0044D620:
        mov  eax,DWORD PTR [edi+0x4]
        mov  eax,DWORD PTR [eax+esi*4]
        mov  ecx,DWORD PTR [eax]
        push  0x0
        push  eax
        call  DWORD PTR [ecx+0x34]
        or   ebx,eax
        mov  eax,DWORD PTR [edi+0x10]
        inc  esi
        cmp  esi,eax
        jb loc_0044D620
    loc_0044D638:
        pop  esi
        mov  eax,ebx
        pop  ebx
        ret
    }
}
