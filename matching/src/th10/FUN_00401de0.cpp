// 00401DE0: FUN_00401de0
// Original size: 528 bytes, actual code: 67 instructions

extern "C" __declspec(naked) void FUN_00401de0(void) {
    __asm {
        sub  esp,0x10
        push  ebx
        push  ebp
        push  esi
        lea  esi,[edx+0x340]
        mov  eax,esi
        mov  ebx,DWORD PTR [eax]
        mov  ebp,DWORD PTR [eax+0x4]
        mov  ecx,DWORD PTR [eax+0x8]
        mov  eax,DWORD PTR [edx+0x20]
        push  edi
        mov  DWORD PTR [esp+0x1c],ecx
        mov  DWORD PTR [esp+0x10],eax
        xor  eax,eax
        mov  ecx,0xeb
        mov  edi,edx
        rep stosd
        mov  ecx,DWORD PTR [esp+0x10]
        mov  eax,DWORD PTR [esp+0x1c]
        mov  DWORD PTR [esi],ebx
        mov  DWORD PTR [esi+0x4],ebp
        mov  DWORD PTR [edx+0x20],ecx
        mov  DWORD PTR [esi+0x8],eax
        xor  eax,eax
        mov  DWORD PTR [edx+0x2fc],0xffffffff
        mov  ecx,0x3f800000
        mov  DWORD PTR [edx+0x3c],ecx
        mov  DWORD PTR [edx+0x40],ecx
        mov  DWORD PTR [edx+0x274],eax
        mov  DWORD PTR [edx+0x270],eax
        mov  DWORD PTR [edx+0x26c],eax
        mov  DWORD PTR [edx+0x268],eax
        mov  DWORD PTR [edx+0x260],eax
        mov  DWORD PTR [edx+0x25c],eax
        mov  DWORD PTR [edx+0x258],eax
        mov  DWORD PTR [edx+0x254],eax
        mov  DWORD PTR [edx+0x24c],eax
        mov  DWORD PTR [edx+0x248],eax
        mov  DWORD PTR [edx+0x244],eax
        mov  DWORD PTR [edx+0x240],eax
        mov  DWORD PTR [edx+0x278],ecx
        mov  DWORD PTR [edx+0x264],ecx
        mov  DWORD PTR [edx+0x250],ecx
        mov  DWORD PTR [edx+0x23c],ecx
        mov  WORD PTR [edx+0x35c],0x7
        mov  DWORD PTR [edx+0x60],eax
        mov  DWORD PTR [edx+0x5c],0xfff0bdc1
        mov  DWORD PTR [edx+0x64],eax
        pop  edi
        mov  DWORD PTR [edx+0xb4],eax
        mov  DWORD PTR [edx+0x100],eax
        mov  DWORD PTR [edx+0x12c],eax
        mov  DWORD PTR [edx+0x178],eax
        mov  DWORD PTR [edx+0x1b4],eax
        mov  DWORD PTR [edx+0x200],eax
        mov  DWORD PTR [edx+0x22c],eax
        pop  esi
        mov  DWORD PTR [edx+0x4],edx
        mov  DWORD PTR [edx+0x8],eax
        mov  DWORD PTR [edx+0xc],eax
        pop  ebp
        mov  DWORD PTR [edx+0x10],edx
        mov  DWORD PTR [edx+0x14],eax
        mov  DWORD PTR [edx+0x18],eax
        pop  ebx
        add  esp,0x10
        ret
    }
}
