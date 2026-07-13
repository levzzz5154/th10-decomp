// 0041C680: FUN_0041c680
// Original size: 336 bytes, actual code: 50 instructions
extern "C" void FUN_0041c030(void);

extern "C" __declspec(naked) void FUN_0041c680(void) {
    __asm {
        push  esi
        push  edi
        mov  edx,ebx
        call FUN_0041c030
        mov  DWORD PTR [ebx],0x46da10
        xor  eax,eax
        mov  esi,0xfffffffe
        lea  edx,[ebx+0x424]
        mov  edi,edx
        mov  ecx,0x7e
        rep stosd
        mov  DWORD PTR [edx+0x2c],0x41000000
        mov  edi,DWORD PTR [ebx+0x688]
        lea  edx,[ebx+0x61c]
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
        mov  edi,edx
        mov  ecx,0xeb
        rep stosd
        mov  WORD PTR [edx+0x384],0xffff
        mov  edi,DWORD PTR [ebx+0xa34]
        lea  edx,[ebx+0x9c8]
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
