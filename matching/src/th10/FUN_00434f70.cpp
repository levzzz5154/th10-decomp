// 00434F70: FUN_00434f70
// Original size: 352 bytes, actual code: 128 instructions
extern "C" void FUN_004350d0(void);
extern "C" void FUN_00435dc0(void);
extern "C" void FUN_0044b0d0(void);
extern "C" void _free(void);
extern "C" void _malloc(void);

extern "C" __declspec(naked) void FUN_00434f70(void) {
    __asm {
        sub  esp,0x14
        mov  ecx,DWORD PTR [esi+0xc]
        test  ecx,ecx
        mov  DWORD PTR [esp],0x0
        jne loc_00434F89
        xor  al,al
        add  esp,0x14
        ret  0x4
    loc_00434F89:
        mov  edx,DWORD PTR ds:0x474908
        mov  eax,DWORD PTR [ecx]
        push  ebx
        push  ebp
        push  edi
        push  edx
        mov  edx,DWORD PTR [esp+0x28]
        push  edx
        call  DWORD PTR [eax]
        test  al,al
        je loc_004350AE
        mov  ecx,DWORD PTR [esi+0xc]
        mov  eax,DWORD PTR [ecx]
        push  0x10
        lea  edx,[esp+0x14]
        push  edx
        call  DWORD PTR [eax+0x8]
        test  eax,eax
        je loc_004350AE
        push  0x10
        push  0x10
        push  0x37
        lea  eax,[esp+0x1c]
        push  0x10
        push  eax
        mov  al,0x1b
        call FUN_0044b0d0
        cmp  DWORD PTR [esp+0x10],0x31414854
        jne loc_004350AE
        mov  ecx,DWORD PTR [esp+0x14]
        mov  eax,DWORD PTR [esp+0x18]
        sub  ecx,0x75bcd15
        mov  DWORD PTR [esp+0x14],ecx
        mov  ecx,DWORD PTR [esp+0x1c]
        add  ecx,0xf7e7f8ac
        mov  DWORD PTR [esi+0x4],ecx
        mov  ecx,DWORD PTR [esi+0xc]
        sub  eax,0x3ade68b1
        mov  DWORD PTR [esp+0x18],eax
        mov  edx,DWORD PTR [ecx]
        call  DWORD PTR [edx+0x14]
        mov  ebp,DWORD PTR [esp+0x18]
        mov  ecx,DWORD PTR [esi+0xc]
        sub  eax,ebp
        mov  ebp,eax
        mov  eax,DWORD PTR [ecx]
        push  0x0
        push  ebp
        call  DWORD PTR [eax+0x18]
        mov  ebx,DWORD PTR [esp+0x18]
        push  ebx
        call _malloc
        mov  edi,eax
        add  esp,0x4
        test  edi,edi
        je loc_004350AE
        mov  ecx,DWORD PTR [esi+0xc]
        mov  edx,DWORD PTR [ecx]
        push  ebx
        push  edi
        call  DWORD PTR [edx+0x8]
        test  eax,eax
        je loc_00435094
        push  ebx
        push  0x80
        push  0x9b
        push  ebx
        push  edi
        mov  al,0x3e
        call FUN_0044b0d0
        mov  eax,DWORD PTR [esp+0x14]
        push  eax
        push  0x0
        push  ebx
        push  edi
        call FUN_00435dc0
        mov  ebx,eax
        test  ebx,ebx
        je loc_00435098
        mov  ecx,DWORD PTR [esi+0x4]
        push  ebp
        push  ecx
        push  ebx
        call FUN_004350d0
        test  eax,eax
        mov  DWORD PTR [esi],eax
        je loc_00435098
        push  edi
        call _free
        push  ebx
        call _free
        add  esp,0x8
        pop  edi
        pop  ebp
        mov  al,0x1
        pop  ebx
        add  esp,0x14
        ret  0x4
    loc_00435094:
        mov  ebx,DWORD PTR [esp+0xc]
    loc_00435098:
        push  edi
        call _free
        add  esp,0x4
        test  ebx,ebx
        je loc_004350AE
        push  ebx
        call _free
        add  esp,0x4
    loc_004350AE:
        mov  ecx,DWORD PTR [esi+0xc]
        test  ecx,ecx
        je loc_004350BC
        mov  edx,DWORD PTR [ecx]
        push  0x1
        call  DWORD PTR [edx+0x1c]
    loc_004350BC:
        pop  edi
        pop  ebp
        mov  DWORD PTR [esi+0xc],0x0
        xor  al,al
        pop  ebx
        add  esp,0x14
        ret  0x4
    }
}
