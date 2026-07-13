// 0042B430: FUN_0042b430
// Original size: 160 bytes, actual code: 38 instructions

extern "C" __declspec(naked) void FUN_0042b430(void) {
    __asm {
        lea  edx,[ebx+0x18]
        push  esi
        push  edi
        mov  edi,DWORD PTR [edx+0x6c]
        mov  esi,0xfffffffe
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
        mov  WORD PTR [edx+0x384],0xffff
        lea  eax,[ebx+0x3f0]
        mov  ecx,0x2d3
    loc_0042B491:
        and  DWORD PTR [eax],esi
        add  eax,0x40
        dec  ecx
        jne loc_0042B491
        xor  eax,eax
        mov  ecx,0x2e21
        mov  edi,ebx
        rep stosd
        mov  eax,DWORD PTR [ebx]
        or   eax,0x2
        pop  edi
        mov  DWORD PTR [ebx],eax
        mov  DWORD PTR ds:0x477840,ebx
        mov  eax,ebx
        pop  esi
        ret
    }
}
