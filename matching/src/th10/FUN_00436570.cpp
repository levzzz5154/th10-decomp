// 00436570: FUN_00436570
// Original size: 240 bytes, actual code: 61 instructions

extern "C" __declspec(naked) void FUN_00436570(void) {
    __asm {
        sub  esp,0x54
        push  esi
        xor  esi,esi
        mov  eax,0x80000000
        mov  DWORD PTR [esp+0x24],eax
        mov  DWORD PTR [esp+0x28],eax
        mov  DWORD PTR [esp+0x2c],eax
        mov  DWORD PTR [esp+0x30],eax
        lea  eax,[esp+0x4]
        push  eax
        mov  eax,DWORD PTR [esp+0x60]
        lea  ecx,[esp+0x18]
        push  ecx
        push  esi
        push  esi
        push  0x20
        push  esi
        push  esi
        push  esi
        push  edx
        push  eax
        mov  DWORD PTR [esp+0x3c],0x44
        mov  DWORD PTR [esp+0x40],esi
        mov  DWORD PTR [esp+0x44],esi
        mov  DWORD PTR [esp+0x48],esi
        mov  DWORD PTR [esp+0x5c],0x50
        mov  DWORD PTR [esp+0x60],0x19
        mov  DWORD PTR [esp+0x64],esi
        mov  DWORD PTR [esp+0x68],esi
        mov  WORD PTR [esp+0x6c],0xa
        mov  WORD PTR [esp+0x6e],si
        mov  DWORD PTR [esp+0x70],esi
        mov  DWORD PTR [esp+0x74],esi
        mov  DWORD PTR [esp+0x78],esi
        mov  DWORD PTR [esp+0x7c],esi
        call  DWORD PTR ds:0x4660e0
        test  eax,eax
        jne loc_004365FE
        or   eax,0xffffffff
        pop  esi
        add  esp,0x54
        ret  0x8
    loc_004365FE:
        cmp  DWORD PTR [esp+0x60],esi
        je loc_00436630
        mov  esi,DWORD PTR ds:0x4660e4
        mov  DWORD PTR [esp+0x5c],0x103
    loc_00436612:
        mov  edx,DWORD PTR [esp+0x4]
        lea  ecx,[esp+0x5c]
        push  ecx
        push  edx
        call  esi
        mov  eax,DWORD PTR [esp+0x5c]
        cmp  eax,0x103
        je loc_00436612
        pop  esi
        add  esp,0x54
        ret  0x8
    loc_00436630:
        xor  eax,eax
        pop  esi
        add  esp,0x54
        ret  0x8
    }
}
