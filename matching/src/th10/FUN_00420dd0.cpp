// 00420DD0: FUN_00420dd0
// Original size: 208 bytes, actual code: 81 instructions
extern "C" void FUN_00452730(void);
extern "C" void _strncmp(void);
extern "C" void _sscanf(void);

extern "C" __declspec(naked) void FUN_00420dd0(void) {
    __asm {
        sub  esp,0x8
        push  ebx
        mov  ebx,DWORD PTR [eax+0x764]
        test  ebx,ebx
        jne loc_00420DE7
        xor  eax,eax
        pop  ebx
        add  esp,0x8
        ret  0xc
    loc_00420DE7:
        push  ebp
        mov  ebp,DWORD PTR [eax+0x760]
        mov  eax,DWORD PTR [esp+0x14]
        push  0x5
        push  0x46dca4
        push  eax
        call _strncmp
        add  esp,0xc
        test  eax,eax
        jne loc_00420E0E
        pop  ebp
        pop  ebx
        add  esp,0x8
        ret  0xc
    loc_00420E0E:
        push  esi
        push  edi
        mov  edi,0x46dca4
        mov  esi,0x46dc9c
        mov  ecx,0x6
        xor  edx,edx
        repz cmps BYTE PTR ds:[esi],BYTE PTR es:[edi]
        jne loc_00420E31
    loc_00420E25:
        pop  edi
        pop  esi
        pop  ebp
        xor  eax,eax
        pop  ebx
        add  esp,0x8
        ret  0xc
    loc_00420E31:
        test  ebp,ebp
        jbe loc_00420E90
    loc_00420E35:
        mov  eax,DWORD PTR [esp+0x1c]
        push  0x5
        push  ebx
        push  eax
        call _strncmp
        add  esp,0xc
        test  eax,eax
        jne loc_00420E7A
        lea  ecx,[esp+0x14]
        push  ecx
        lea  edx,[esp+0x14]
        push  edx
        add  ebx,0x6
        push  0x46dc94
        push  ebx
        call _sscanf
        mov  eax,DWORD PTR [esp+0x30]
        mov  ecx,DWORD PTR [esp+0x20]
        add  esp,0x10
        cmp  ecx,eax
        jne loc_00420E7A
        mov  ecx,DWORD PTR [esp+0x24]
        cmp  DWORD PTR [esp+0x14],ecx
        je loc_00420E25
    loc_00420E7A:
        push  0xa
        push  ebx
        mov  esi,ebx
        call FUN_00452730
        add  esp,0x8
        inc  eax
        mov  ebx,eax
        sub  esi,ebx
        add  ebp,esi
        jne loc_00420E35
    loc_00420E90:
        pop  edi
        pop  esi
        pop  ebp
        or   eax,0xffffffff
        pop  ebx
        add  esp,0x8
        ret  0xc
    }
}
