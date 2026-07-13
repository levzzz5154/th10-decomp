// 00401000: FUN_00401000
// Original size: 272 bytes, actual code: 53 instructions

extern "C" __declspec(naked) void FUN_00401000(void) {
    __asm {
        mov  DWORD PTR [esi],0x46cb14
        mov  eax,DWORD PTR [esi+0x80]
        lea  edx,[esi+0x14]
        push  ebx
        mov  ebx,0xfffffffe
        push  edi
        and  eax,ebx
        mov  DWORD PTR [edx+0x6c],eax
        and  DWORD PTR [edx+0xb0],ebx
        and  DWORD PTR [edx+0xfc],ebx
        and  DWORD PTR [edx+0x128],ebx
        and  DWORD PTR [edx+0x174],ebx
        and  DWORD PTR [edx+0x1b0],ebx
        and  DWORD PTR [edx+0x1fc],ebx
        and  DWORD PTR [edx+0x228],ebx
        and  DWORD PTR [edx+0x378],ebx
        xor  eax,eax
        mov  edi,edx
        mov  ecx,0xeb
        rep stosd
        mov  WORD PTR [edx+0x384],0xffff
        mov  eax,DWORD PTR [esi+0x42c]
        lea  edx,[esi+0x3c0]
        and  eax,ebx
        mov  DWORD PTR [edx+0x6c],eax
        and  DWORD PTR [edx+0xb0],ebx
        and  DWORD PTR [edx+0xfc],ebx
        and  DWORD PTR [edx+0x128],ebx
        and  DWORD PTR [edx+0x174],ebx
        and  DWORD PTR [edx+0x1b0],ebx
        and  DWORD PTR [edx+0x1fc],ebx
        and  DWORD PTR [edx+0x228],ebx
        and  DWORD PTR [edx+0x378],ebx
        xor  eax,eax
        mov  ecx,0xeb
        mov  edi,edx
        rep stosd
        mov  WORD PTR [edx+0x384],0xffff
        mov  ecx,0x226b
        mov  edi,esi
        rep stosd
        or   DWORD PTR [esi+0x4],0x2
        mov  eax,0x3f800000
        mov  DWORD PTR ds:0x4776e0,esi
        mov  DWORD PTR [esi+0x8974],0xffffffff
        mov  DWORD PTR [esi+0x8978],eax
        mov  DWORD PTR [esi+0x897c],eax
        pop  edi
        mov  DWORD PTR [esi+0x8984],0x0
        mov  DWORD PTR [esi+0x898c],0x9
        mov  eax,esi
        pop  ebx
        ret
    }
}
