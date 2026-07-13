// 0041F850: FUN_0041f850
// Original size: 128 bytes, actual code: 33 instructions

extern "C" __declspec(naked) void FUN_0041f850(void) {
    __asm {
        mov  DWORD PTR [esi+0x10],0x4703e4
        lea  edx,[esi+0x30]
        xor  eax,eax
        mov  DWORD PTR [esi+0x14],eax
        mov  DWORD PTR [esi+0x18],eax
        mov  DWORD PTR [esi+0x1c],eax
        mov  DWORD PTR [esi+0x20],eax
        mov  ecx,DWORD PTR [edx+0x6c]
        mov  eax,0xfffffffe
        and  ecx,eax
        mov  DWORD PTR [edx+0x6c],ecx
        push  edi
        and  DWORD PTR [edx+0xb0],eax
        and  DWORD PTR [edx+0xfc],eax
        and  DWORD PTR [edx+0x128],eax
        and  DWORD PTR [edx+0x174],eax
        and  DWORD PTR [edx+0x1b0],eax
        and  DWORD PTR [edx+0x1fc],eax
        and  DWORD PTR [edx+0x228],eax
        and  DWORD PTR [edx+0x378],eax
        xor  eax,eax
        mov  ecx,0xeb
        mov  edi,edx
        rep stosd
        mov  WORD PTR [edx+0x384],0xffff
        mov  ecx,0xfc
        mov  edi,esi
        rep stosd
        or   DWORD PTR [esi],0x2
        mov  DWORD PTR ds:0x477820,esi
        mov  eax,esi
        pop  edi
        ret
    }
}
