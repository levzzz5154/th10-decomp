// 00402050: FUN_00402050
// Original size: 272 bytes, actual code: 22 instructions

extern "C" __declspec(naked) void FUN_00402050(void) {
    __asm {
        mov  edx,ecx
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
        mov  eax,edx
        pop  edi
        ret
    }
}
