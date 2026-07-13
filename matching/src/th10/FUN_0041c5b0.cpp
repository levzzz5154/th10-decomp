// 0041C5B0: FUN_0041c5b0
// Original size: 208 bytes, actual code: 46 instructions
extern "C" void FUN_0041c030(void);

extern "C" __declspec(naked) void FUN_0041c5b0(void) {
    __asm {
        push  esi
        push  edi
        mov  edx,ebx
        call FUN_0041c030
        mov  DWORD PTR [ebx],0x46da60
        lea  edx,[ebx+0x600]
        xor  eax,eax
        mov  esi,0xfffffffe
        mov  ecx,0x77
        lea  edi,[ebx+0x424]
        rep stosd
        and  DWORD PTR [edx+0x6c],esi
        and  DWORD PTR [edx+0xb0],esi
        and  DWORD PTR [edx+0xfc],esi
        and  DWORD PTR [edx+0x128],esi
        and  DWORD PTR [edx+0x174],esi
        and  DWORD PTR [edx+0x1b0],esi
        and  DWORD PTR [edx+0x1fc],esi
        and  DWORD PTR [edx+0x228],esi
        and  DWORD PTR [edx+0x378],esi
        xor  eax,eax
        mov  edi,edx
        mov  ecx,0xeb
        rep stosd
        mov  WORD PTR [edx+0x384],0xffff
        mov  edi,DWORD PTR [ebx+0xa18]
        lea  edx,[ebx+0x9ac]
        and  edi,esi
        mov  DWORD PTR [edx+0x6c],edi
        and  DWORD PTR [edx+0xb0],esi
        and  DWORD PTR [edx+0xfc],esi
        and  DWORD PTR [edx+0x128],esi
        and  DWORD PTR [edx+0x174],esi
        and  DWORD PTR [edx+0x1b0],esi
        and  DWORD PTR [edx+0x1fc],esi
        and  DWORD PTR [edx+0x228],esi
        and  DWORD PTR [edx+0x378],esi
        xor  eax,eax
        mov  ecx,0xeb
        mov  edi,edx
        rep stosd
        pop  edi
        mov  WORD PTR [edx+0x384],0xffff
        mov  eax,ebx
        pop  esi
        ret
    }
}
