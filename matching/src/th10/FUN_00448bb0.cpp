// 00448BB0: FUN_00448bb0
// Original size: 336 bytes, actual code: 88 instructions
extern "C" void FUN_00401de0(void);
extern "C" void _free(void);
extern "C" void _free(void);

extern "C" __declspec(naked) void FUN_00448bb0(void) {
    __asm {
        mov  ecx,DWORD PTR [edi+0x72dad8]
        lea  eax,[esi+0x4]
        cmp  eax,ecx
        jne loc_00448BC6
        mov  ecx,DWORD PTR [esi+0xc]
        mov  DWORD PTR [edi+0x72dad8],ecx
    loc_00448BC6:
        cmp  eax,DWORD PTR [edi+0x72dad4]
        jne loc_00448BD7
        mov  edx,DWORD PTR [esi+0x8]
        mov  DWORD PTR [edi+0x72dad4],edx
    loc_00448BD7:
        cmp  eax,DWORD PTR [edi+0x72dae0]
        jne loc_00448BE8
        mov  ecx,DWORD PTR [esi+0xc]
        mov  DWORD PTR [edi+0x72dae0],ecx
    loc_00448BE8:
        cmp  eax,DWORD PTR [edi+0x72dadc]
        jne loc_00448BF9
        mov  edx,DWORD PTR [esi+0x8]
        mov  DWORD PTR [edi+0x72dadc],edx
    loc_00448BF9:
        mov  ecx,DWORD PTR [eax+0x4]
        push  ebx
        xor  ebx,ebx
        cmp  ecx,ebx
        je loc_00448C09
        mov  edx,DWORD PTR [eax+0x8]
        mov  DWORD PTR [ecx+0x8],edx
    loc_00448C09:
        mov  ecx,DWORD PTR [eax+0x8]
        cmp  ecx,ebx
        je loc_00448C16
        mov  edx,DWORD PTR [eax+0x4]
        mov  DWORD PTR [ecx+0x4],edx
    loc_00448C16:
        mov  DWORD PTR [eax+0x4],ebx
        mov  DWORD PTR [eax+0x8],ebx
        mov  eax,DWORD PTR [esi+0x14]
        cmp  eax,ebx
        je loc_00448C29
        mov  ecx,DWORD PTR [esi+0x18]
        mov  DWORD PTR [eax+0x8],ecx
    loc_00448C29:
        mov  eax,DWORD PTR [esi+0x18]
        cmp  eax,ebx
        je loc_00448C36
        mov  edx,DWORD PTR [esi+0x14]
        mov  DWORD PTR [eax+0x4],edx
    loc_00448C36:
        lea  eax,[edi+0x68]
        cmp  esi,eax
        mov  DWORD PTR [esi+0x14],ebx
        mov  DWORD PTR [esi+0x18],ebx
        jb loc_00448C92
        lea  ecx,[edi+0x3ac068]
        cmp  esi,ecx
        jae loc_00448C92
        mov  ecx,esi
        sub  ecx,edi
        sub  ecx,0x68
        mov  eax,0x8b70344b
        imul  ecx
        add  edx,ecx
        sar  edx,0x9
        mov  eax,edx
        shr  eax,0x1f
        add  eax,edx
        mov  BYTE PTR [eax+edi*1+0x3ac068],bl
        mov  eax,DWORD PTR [esi+0x358]
        cmp  eax,ebx
        je loc_00448C81
        push  eax
        call _free
        add  esp,0x4
    loc_00448C81:
        mov  edx,esi
        mov  DWORD PTR [esi+0x358],ebx
        call FUN_00401de0
        xor  eax,eax
        pop  ebx
        ret
    loc_00448C92:
        cmp  esi,ebx
        je loc_00448CB8
        mov  eax,DWORD PTR [esi+0x358]
        cmp  eax,ebx
        je loc_00448CA9
        push  eax
        call _free
        add  esp,0x4
    loc_00448CA9:
        push  esi
        mov  DWORD PTR [esi+0x358],ebx
        call _free
        add  esp,0x4
    loc_00448CB8:
        xor  eax,eax
        pop  ebx
        ret
    }
}
