// 0042AE60: FUN_0042ae60
// Original size: 192 bytes, actual code: 49 instructions
extern "C" void FUN_0042acb0(void);
extern "C" void FUN_0042add0(void);
extern "C" void FUN_0042b030(void);
extern "C" void FUN_0044b360(void);

extern "C" __declspec(naked) void FUN_0042ae60(void) {
    __asm {
        push  ecx
        push  ebx
        push  esi
        mov  ebx,eax
        push  edi
        xor  eax,eax
        mov  ecx,0x772d
        mov  edi,ebx
        rep stosd
        push  0x1
        lea  eax,[esp+0x10]
        push  eax
        mov  eax,0x46e848
        call FUN_0044b360
        lea  edx,[ebx+0x1d86c]
        mov  DWORD PTR [ebx],eax
        call FUN_0042add0
        lea  esi,[ebx+0x8]
        mov  ecx,esi
        sub  ecx,ebx
        lea  edi,[ecx-0x8]
        mov  eax,0x79641cb1
        imul  edi
        sar  edx,0xd
        mov  eax,edx
        shr  eax,0x1f
        add  eax,edx
        cmp  eax,0x7
        jae loc_0042AED8
        nop
    loc_0042AEB0:
        push  esi
        call FUN_0042acb0
        add  edi,0x437c
        mov  eax,0x79641cb1
        imul  edi
        sar  edx,0xd
        mov  ecx,edx
        shr  ecx,0x1f
        add  ecx,edx
        add  esi,0x437c
        cmp  ecx,0x7
        jb loc_0042AEB0
    loc_0042AED8:
        call FUN_0042b030
        pop  edi
        pop  esi
        mov  eax,ebx
        pop  ebx
        pop  ecx
        ret
    }
}
