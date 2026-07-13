// 0040CC70: FUN_0040cc70
// Original size: 176 bytes, actual code: 39 instructions

extern "C" __declspec(naked) void FUN_0040cc70(void) {
    __asm {
        mov  ecx,DWORD PTR [edx+0x12c]
        push  ebx
        push  ebp
        mov  ebp,0xfffffffe
        and  ecx,ebp
        mov  DWORD PTR [edx+0x12c],ecx
        and  DWORD PTR [edx+0x17c],ebp
        mov  ebx,DWORD PTR [edx+0x1c8]
        push  esi
        and  ebx,ebp
        mov  DWORD PTR [edx+0x1c8],ebx
        push  edi
        and  DWORD PTR [edx+0x204],ebp
        and  DWORD PTR [edx+0x240],ebp
        and  DWORD PTR [edx+0x27c],ebp
        and  DWORD PTR [edx+0x2b8],ebp
        lea  esi,[edx+0x2c4]
        mov  ebx,0x8
        mov  edi,edi
    loc_0040CCC0:
        xor  eax,eax
        mov  edi,esi
        mov  ecx,0x84
        rep stosd
        mov  DWORD PTR [esi+0x204],0xffffffff
        add  esi,0x210
        dec  ebx
        jne loc_0040CCC0
        mov  ecx,DWORD PTR [edx+0x142c]
        and  ecx,ebp
        pop  edi
        mov  DWORD PTR [edx+0x142c],ecx
        mov  eax,DWORD PTR [edx+0x1440]
        and  eax,ebp
        pop  esi
        pop  ebp
        mov  DWORD PTR [edx+0x1440],eax
        mov  eax,edx
        pop  ebx
        ret
    }
}
