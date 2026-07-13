// 004246C0: FUN_004246c0
// Original size: 304 bytes, actual code: 59 instructions

extern "C" __declspec(naked) void FUN_004246c0(void) {
    __asm {
        mov  ecx,DWORD PTR [esi+0x80]
        lea  edx,[esi+0x14]
        push  ebx
        mov  ebx,0xfffffffe
        and  ecx,ebx
        mov  DWORD PTR [edx+0x6c],ecx
        and  DWORD PTR [edx+0xb0],ebx
        push  edi
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
        and  DWORD PTR [esi+0x470],ebx
        and  DWORD PTR [esi+0x484],ebx
        and  DWORD PTR [esi+0x498],ebx
        lea  eax,[esi+0x4ac]
        mov  ecx,0x80
    loc_00424736:
        and  DWORD PTR [eax],ebx
        add  eax,0x5c
        dec  ecx
        jne loc_00424736
        mov  edi,DWORD PTR [esi+0x3320]
        lea  eax,[esi+0x32a0]
        and  edi,ebx
        mov  DWORD PTR [eax+0x80],edi
        mov  ecx,DWORD PTR [eax+0x118]
        add  eax,0x98
        and  ecx,ebx
        mov  DWORD PTR [eax+0x80],ecx
        mov  edx,DWORD PTR [eax+0x118]
        add  eax,0x98
        and  edx,ebx
        mov  DWORD PTR [eax+0x80],edx
        and  DWORD PTR [eax+0x118],ebx
        lea  eax,[esi+0x3560]
        mov  ecx,0x21
        nop
    loc_00424790:
        and  DWORD PTR [eax],ebx
        add  eax,0x6c
        dec  ecx
        jne loc_00424790
        and  DWORD PTR [esi+0x431c],ebx
        xor  eax,eax
        mov  ecx,0x111e
        mov  edi,esi
        rep stosd
        pop  edi
        mov  DWORD PTR ds:0x477834,esi
        mov  eax,esi
        pop  ebx
        ret
    }
}
