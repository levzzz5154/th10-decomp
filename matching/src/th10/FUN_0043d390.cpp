// 0043D390: FUN_0043d390
// Original size: 768 bytes, actual code: 225 instructions
extern "C" void FUN_0043d250(void);
extern "C" void FUN_0044b810(void);
extern "C" void _free(void);
extern "C" void _strncmp(void);
extern "C" void __security_check_cookie(void);

extern "C" __declspec(naked) void FUN_0043d390(void) {
    __asm {
        sub  esp,0x5c
        mov  eax,ds:0x473660
        xor  eax,esp
        mov  DWORD PTR [esp+0x58],eax
        mov  eax,DWORD PTR [esp+0x60]
        push  ebx
        mov  ebx,edx
        mov  DWORD PTR [esp+0x8],eax
        mov  eax,DWORD PTR [ebx+0x610]
        test  eax,eax
        push  esi
        mov  esi,ecx
        jne loc_0043D3CB
        pop  esi
        xor  eax,eax
        pop  ebx
        mov  ecx,DWORD PTR [esp+0x58]
        xor  ecx,esp
        call __security_check_cookie
        add  esp,0x5c
        ret  0x4
    loc_0043D3CB:
        mov  eax,DWORD PTR [ebx+esi*4+0x8]
        test  eax,eax
        push  edi
        lea  edi,[ebx+esi*4+0x8]
        mov  DWORD PTR [esp+0x24],edi
        je loc_0043D3E8
        mov  ecx,DWORD PTR [eax]
        push  eax
        call  DWORD PTR [ecx+0x8]
        mov  DWORD PTR [edi],0x0
    loc_0043D3E8:
        mov  eax,DWORD PTR [ebx+esi*4+0x5230]
        test  eax,eax
        push  ebp
        jne loc_0043D41B
        mov  edi,DWORD PTR ds:0x4660ac
        mov  ebp,0x2
        nop
    loc_0043D400:
        push  0xa
        call  edi
        cmp  DWORD PTR ds:0x4977b4,ebp
        je loc_0043D625
        mov  eax,DWORD PTR [ebx+esi*4+0x5230]
        test  eax,eax
        je loc_0043D400
    loc_0043D41B:
        mov  edi,DWORD PTR [ebx+esi*4+0x5230]
        test  edi,edi
        mov  DWORD PTR [esp+0x10],edi
        mov  DWORD PTR [ebx+esi*4+0x5230],0x0
        je loc_0043D466
        push  0x4
        push  0x46fda4
        push  edi
        call _strncmp
        add  esp,0xc
        test  eax,eax
        je loc_0043D47E
        mov  edx,DWORD PTR [esp+0x14]
        push  edx
        push  0x46fd88
    loc_0043D453:
        mov  ecx,0x474f70
        call FUN_0044b810
        push  edi
    loc_0043D45E:
        call _free
        add  esp,0xc
    loc_0043D466:
        pop  ebp
        pop  edi
        pop  esi
        or   eax,0xffffffff
        pop  ebx
        mov  ecx,DWORD PTR [esp+0x58]
        xor  ecx,esp
        call __security_check_cookie
        add  esp,0x5c
        ret  0x4
    loc_0043D47E:
        mov  ebp,DWORD PTR [edi+0x4]
        lea  esi,[edi+0x4]
        push  0x4
        add  esi,0x4
        push  0x46fd80
        push  esi
        call _strncmp
        add  esp,0xc
        test  eax,eax
        je loc_0043D4A7
        mov  eax,DWORD PTR [esp+0x14]
        push  eax
        push  0x46fd64
        jmp loc_0043D453
    loc_0043D4A7:
        add  esi,0x4
        add  ebp,0xfffffff4
        push  0x46fd5c
        mov  eax,ebp
        lea  edi,[esp+0x30]
        mov  ecx,esi
        call FUN_0043d250
        test  eax,eax
        je loc_0043D4FB
        mov  ecx,DWORD PTR [eax]
        mov  DWORD PTR [esp+0x30],ecx
        mov  edx,DWORD PTR [eax+0x4]
        mov  DWORD PTR [esp+0x34],edx
        mov  ecx,DWORD PTR [eax+0x8]
        mov  DWORD PTR [esp+0x38],ecx
        mov  edx,DWORD PTR [eax+0xc]
        mov  DWORD PTR [esp+0x3c],edx
        mov  ax,WORD PTR [eax+0x10]
        mov  WORD PTR [esp+0x40],ax
        push  0x46fd54
        mov  eax,ebp
        mov  ecx,esi
        call FUN_0043d250
        mov  ebp,eax
        test  ebp,ebp
        jne loc_0043D519
    loc_0043D4FB:
        mov  ecx,DWORD PTR [esp+0x14]
        push  ecx
        push  0x46fd64
        mov  ecx,0x474f70
        call FUN_0044b810
        mov  edx,DWORD PTR [esp+0x18]
        push  edx
        jmp loc_0043D45E
    loc_0043D519:
        mov  edi,DWORD PTR [esp+0x28]
        mov  ebx,DWORD PTR [ebx]
        mov  esi,DWORD PTR [esp+0x2c]
        xor  eax,eax
        mov  DWORD PTR [esp+0x44],eax
        mov  DWORD PTR [esp+0x48],eax
        mov  DWORD PTR [esp+0x4c],eax
        mov  DWORD PTR [esp+0x50],eax
        mov  DWORD PTR [esp+0x54],eax
        mov  DWORD PTR [esp+0x58],eax
        mov  DWORD PTR [esp+0x5c],eax
        mov  DWORD PTR [esp+0x60],eax
        push  eax
        mov  DWORD PTR [esp+0x68],eax
        push  edi
        lea  eax,[esp+0x4c]
        lea  ecx,[esp+0x38]
        push  eax
        mov  DWORD PTR [esp+0x50],0x24
        mov  DWORD PTR [esp+0x54],0x80c8
        mov  DWORD PTR [esp+0x58],esi
        mov  DWORD PTR [esp+0x60],ecx
        mov  edx,DWORD PTR [ebx]
        push  ebx
        call  DWORD PTR [edx+0xc]
        test  eax,eax
        jge loc_0043D588
        mov  ecx,DWORD PTR [esp+0x10]
        push  ecx
        call _free
        add  esp,0x4
        jmp loc_0043D466
    loc_0043D588:
        mov  eax,DWORD PTR [edi]
        mov  edx,DWORD PTR [eax]
        push  0x0
        lea  ecx,[esp+0x20]
        push  ecx
        lea  ecx,[esp+0x28]
        push  ecx
        lea  ecx,[esp+0x24]
        push  ecx
        lea  ecx,[esp+0x34]
        push  ecx
        push  esi
        push  0x0
        push  eax
        call  DWORD PTR [edx+0x2c]
        test  eax,eax
        jge loc_0043D5BF
        mov  edx,DWORD PTR [esp+0x10]
        push  edx
        call _free
        add  esp,0x4
        jmp loc_0043D466
    loc_0043D5BF:
        mov  ecx,DWORD PTR [esp+0x18]
        mov  edi,DWORD PTR [esp+0x24]
        mov  eax,ecx
        shr  ecx,0x2
        mov  esi,ebp
        rep movsd
        mov  ecx,eax
        and  ecx,0x3
        rep movs BYTE PTR es:[edi],BYTE PTR ds:[esi]
        mov  ecx,DWORD PTR [esp+0x1c]
        test  ecx,ecx
        je loc_0043D5FC
        mov  edx,DWORD PTR [esp+0x18]
        mov  edi,DWORD PTR [esp+0x20]
        mov  eax,ecx
        shr  ecx,0x2
        lea  esi,[edx+ebp*1]
        rep movsd
        mov  ecx,eax
        and  ecx,0x3
        rep movs BYTE PTR es:[edi],BYTE PTR ds:[esi]
        mov  ecx,DWORD PTR [esp+0x1c]
    loc_0043D5FC:
        mov  edx,DWORD PTR [esp+0x28]
        mov  eax,DWORD PTR [edx]
        mov  edx,DWORD PTR [eax]
        push  ecx
        mov  ecx,DWORD PTR [esp+0x24]
        push  ecx
        mov  ecx,DWORD PTR [esp+0x20]
        push  ecx
        mov  ecx,DWORD PTR [esp+0x30]
        push  ecx
        push  eax
        call  DWORD PTR [edx+0x4c]
        mov  edx,DWORD PTR [esp+0x10]
        push  edx
        call _free
        add  esp,0x4
    loc_0043D625:
        mov  ecx,DWORD PTR [esp+0x68]
        pop  ebp
        pop  edi
        pop  esi
        pop  ebx
        xor  ecx,esp
        xor  eax,eax
        call __security_check_cookie
        add  esp,0x5c
        ret  0x4
    }
}
