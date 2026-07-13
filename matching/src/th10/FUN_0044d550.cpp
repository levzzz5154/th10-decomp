// 0044D550: FUN_0044d550
// Original size: 96 bytes, actual code: 36 instructions

extern "C" __declspec(naked) void FUN_0044d550(void) {
    __asm {
        mov  eax,DWORD PTR [edi+0x4]
        test  eax,eax
        jne loc_0044D55D
        mov  eax,0x800401f0
        ret
    loc_0044D55D:
        mov  eax,DWORD PTR [edi+0x10]
        push  ebx
        push  esi
        xor  ebx,ebx
        xor  esi,esi
        test  eax,eax
        mov  DWORD PTR [edi+0x30],ebx
        jbe loc_0044D596
        nop
    loc_0044D570:
        mov  eax,DWORD PTR [edi+0x4]
        mov  eax,DWORD PTR [eax+esi*4]
        mov  ecx,DWORD PTR [eax]
        push  eax
        call  DWORD PTR [ecx+0x48]
        mov  edx,DWORD PTR [edi+0x4]
        or   ebx,eax
        mov  eax,DWORD PTR [edx+esi*4]
        mov  ecx,DWORD PTR [eax]
        push  0x0
        push  eax
        call  DWORD PTR [ecx+0x34]
        or   ebx,eax
        mov  eax,DWORD PTR [edi+0x10]
        inc  esi
        cmp  esi,eax
        jb loc_0044D570
    loc_0044D596:
        pop  esi
        mov  eax,ebx
        mov  DWORD PTR [edi+0x1c],0x0
        pop  ebx
        ret
    }
}
