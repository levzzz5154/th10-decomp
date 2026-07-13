// 00403850: FUN_00403850
// Original size: 320 bytes, actual code: 102 instructions
extern "C" void FUN_00447280(void);
extern "C" void FUN_0044b360(void);
extern "C" void FUN_0044b810(void);
extern "C" void _malloc(void);

extern "C" __declspec(naked) void FUN_00403850(void) {
    __asm {
        mov  eax,DWORD PTR [ebx+0x2a44]
        test  eax,eax
        push  esi
        push  edi
        jne loc_004038B3
        mov  eax,DWORD PTR [esp+0xc]
        mov  BYTE PTR ds:0x497c38,0x0
        mov  esi,eax
        nop
    loc_00403870:
        mov  cl,BYTE PTR [eax]
        inc  eax
        test  cl,cl
        jne loc_00403870
        mov  edi,0x497c38
        sub  eax,esi
        dec  edi
        nop
    loc_00403880:
        mov  cl,BYTE PTR [edi+0x1]
        inc  edi
        test  cl,cl
        jne loc_00403880
        mov  ecx,eax
        shr  ecx,0x2
        rep movsd
        mov  ecx,eax
        push  0x0
        lea  eax,[ebx+0x2a48]
        and  ecx,0x3
        push  eax
        mov  eax,0x497c38
        rep movs BYTE PTR es:[edi],BYTE PTR ds:[esi]
        call FUN_0044b360
        test  eax,eax
        mov  DWORD PTR [ebx+0x2a44],eax
        je loc_0040391B
    loc_004038B3:
        mov  eax,DWORD PTR [ebx+0x2a48]
        push  eax
        call _malloc
        mov  ecx,DWORD PTR [ebx+0x2a48]
        mov  esi,DWORD PTR [ebx+0x2a44]
        mov  edx,ecx
        shr  ecx,0x2
        mov  DWORD PTR [ebx+0x10],eax
        mov  edi,eax
        rep movsd
        mov  ecx,edx
        mov  edx,DWORD PTR ds:0x491c10
        and  ecx,0x3
        rep movs BYTE PTR es:[edi],BYTE PTR ds:[esi]
        mov  eax,DWORD PTR [ebx+0x10]
        mov  ecx,DWORD PTR [ebx+0x2a30]
        add  esp,0x4
        add  eax,0x10
        and  ecx,0x1
        push  eax
        add  ecx,0x4
        call FUN_00447280
        test  eax,eax
        mov  DWORD PTR [ebx+0x178],eax
        jne loc_00403923
        push  0x46cbc0
        mov  ecx,0x474f70
        call FUN_0044b810
        add  esp,0x4
    loc_0040391B:
        pop  edi
        or   eax,0xffffffff
        pop  esi
        ret  0x4
    loc_00403923:
        mov  eax,DWORD PTR [ebx+0x10]
        lea  ecx,[eax+0x90]
        mov  DWORD PTR [ebx+0x14],ecx
        mov  edx,DWORD PTR [eax+0x4]
        add  edx,eax
        mov  DWORD PTR [ebx+0x18],edx
        mov  ecx,DWORD PTR [eax+0x8]
        add  ecx,eax
        mov  DWORD PTR [ebx+0x1c],ecx
        xor  ecx,ecx
        cmp  WORD PTR [eax],cx
        jle loc_00403961
    loc_00403946:
        mov  edx,DWORD PTR [ebx+0x14]
        mov  esi,DWORD PTR [edx+ecx*4]
        lea  eax,[edx+ecx*4]
        mov  edx,DWORD PTR [ebx+0x10]
        add  esi,edx
        mov  DWORD PTR [eax],esi
        mov  eax,DWORD PTR [ebx+0x10]
        movsx edx,WORD PTR [eax]
        inc  ecx
        cmp  ecx,edx
        jl loc_00403946
    loc_00403961:
        mov  eax,DWORD PTR [ebx+0x10]
        movsx eax,WORD PTR [eax+0x2]
        imul  eax,eax,0x3ac
        push  eax
        call _malloc
        add  esp,0x4
        pop  edi
        mov  DWORD PTR [ebx+0x17c],eax
        xor  eax,eax
        pop  esi
        ret  0x4
    }
}
