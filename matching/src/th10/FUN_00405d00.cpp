// 00405D00: FUN_00405d00
// Original size: 224 bytes, actual code: 65 instructions

extern "C" __declspec(naked) void FUN_00405d00(void) {
    __asm {
        push  ebx
        mov  ebx,ecx
        mov  eax,DWORD PTR [ebx+0x74]
        lea  edx,[ebx+0x8]
        push  esi
        mov  esi,0xfffffffe
        and  eax,esi
        mov  DWORD PTR [edx+0x6c],eax
        push  edi
        and  DWORD PTR [edx+0xb0],esi
        and  DWORD PTR [edx+0xfc],esi
        and  DWORD PTR [edx+0x128],esi
        and  DWORD PTR [edx+0x174],esi
        and  DWORD PTR [edx+0x1b0],esi
        and  DWORD PTR [edx+0x1fc],esi
        and  DWORD PTR [edx+0x228],esi
        mov  ecx,DWORD PTR [edx+0x378]
        xor  eax,eax
        and  ecx,esi
        mov  DWORD PTR [edx+0x378],ecx
        mov  edi,edx
        mov  ecx,0xeb
        rep stosd
        mov  WORD PTR [edx+0x384],0xffff
        and  DWORD PTR [ebx+0x408],esi
        and  DWORD PTR [ebx+0x41c],esi
        mov  edx,DWORD PTR [ebx+0x624]
        lea  eax,[ebx+0x614]
        add  eax,0x34
        and  edx,esi
        mov  DWORD PTR [eax-0x24],edx
        mov  edi,DWORD PTR [eax+0x10]
        add  eax,0x34
        and  edi,esi
        mov  DWORD PTR [eax-0x24],edi
        mov  ecx,DWORD PTR [eax+0x10]
        add  eax,0x34
        and  ecx,esi
        mov  DWORD PTR [eax-0x24],ecx
        mov  edx,DWORD PTR [eax+0x10]
        add  eax,0x34
        and  edx,esi
        mov  DWORD PTR [eax-0x24],edx
        and  DWORD PTR [eax+0x10],esi
        mov  ecx,DWORD PTR [eax+0x44]
        add  eax,0x34
        and  ecx,esi
        mov  DWORD PTR [eax+0x10],ecx
        mov  edx,DWORD PTR [eax+0x44]
        add  eax,0x34
        and  edx,esi
        mov  DWORD PTR [eax+0x10],edx
        mov  edi,DWORD PTR [eax+0x44]
        add  eax,0x34
        and  edi,esi
        mov  DWORD PTR [eax+0x10],edi
        mov  ecx,DWORD PTR [eax+0x44]
        add  eax,0x34
        and  ecx,esi
        mov  DWORD PTR [eax+0x10],ecx
        mov  eax,ebx
        pop  edi
        pop  esi
        pop  ebx
        ret
    }
}
