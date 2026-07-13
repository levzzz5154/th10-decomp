// 0043EDA0: FUN_0043eda0
// Original size: 144 bytes, actual code: 55 instructions

extern "C" __declspec(naked) void FUN_0043eda0(void) {
    __asm {
        push  esi
        mov  esi,0x1
        shl  esi,cl
        movzx ecx,WORD PTR [esp+0x8]
        test  ecx,esi
        pop  esi
        je loc_0043EDF9
        mov  ecx,DWORD PTR [eax]
        add  ecx,0xffffd8f0
        cmp  ecx,0x9
        ja loc_0043EDF9
        jmp  DWORD PTR [ecx*4+0x43edfc]
        lea  eax,[edx+0x30c]
        ret  0x4
        lea  eax,[edx+0x310]
        ret  0x4
        lea  eax,[edx+0x314]
        ret  0x4
        lea  eax,[edx+0x318]
        ret  0x4
        lea  eax,[edx+0x32c]
        ret  0x4
        lea  eax,[edx+0x330]
    loc_0043EDF9:
        ret  0x4
        (bad]
        in   eax,dx
        inc  ebx
        add  bh,cl
        in   eax,dx
        inc  ebx
        add  al,bl
        in   eax,dx
        inc  ebx
        add  cl,ah
        in   eax,dx
        inc  ebx
        add  cl,bh
        in   eax,dx
        inc  ebx
        add  cl,bh
        in   eax,dx
        inc  ebx
        add  cl,bh
        in   eax,dx
        inc  ebx
        add  cl,bh
        in   eax,dx
        inc  ebx
        add  dl,ch
        in   eax,dx
        inc  ebx
        add  bl,dh
        in   eax,dx
        inc  ebx
        add  ah,cl
    }
}
