// 0044BA80: FUN_0044ba80
// Original size: 160 bytes, actual code: 46 instructions
extern "C" void __security_check_cookie(void);

extern "C" __declspec(naked) void FUN_0044ba80(void) {
    __asm {
        sub  esp,0xc
        mov  eax,ds:0x473660
        xor  eax,esp
        mov  DWORD PTR [esp+0x8],eax
        xor  eax,eax
        mov  ax,WORD PTR [ecx]
        xor  ax,0x9630
        xor  edx,edx
        sub  eax,0x6553
        mov  dx,ax
        shl  eax,0x2
        shr  dx,0xe
        add  eax,edx
        mov  WORD PTR [ecx],ax
        mov  WORD PTR [esp],ax
        xor  eax,0x9630
        sub  eax,0x6553
        xor  edx,edx
        mov  dx,ax
        shr  dx,0xe
        shl  eax,0x2
        add  eax,edx
        mov  WORD PTR [ecx],ax
        mov  WORD PTR [esp+0x2],ax
        xor  eax,0x9630
        sub  eax,0x6553
        mov  edx,eax
        xor  eax,eax
        mov  ax,dx
        shr  ax,0xe
        shl  edx,0x2
        add  eax,edx
        xor  eax,0x9630
        sub  eax,0x6553
        xor  edx,edx
        mov  dx,ax
        shr  dx,0xe
        shl  eax,0x2
        add  edx,eax
        add  DWORD PTR [ecx+0x4],0x4
        mov  eax,DWORD PTR [esp]
        mov  WORD PTR [ecx],dx
        mov  ecx,DWORD PTR [esp+0x8]
        xor  ecx,esp
        add  esp,0xc
        jmp __security_check_cookie
    }
}
