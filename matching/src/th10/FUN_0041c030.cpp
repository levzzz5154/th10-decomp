// 0041C030: FUN_0041c030
// Original size: 240 bytes, actual code: 30 instructions

extern "C" __declspec(naked) void FUN_0041c030(void) {
    __asm {
        mov  DWORD PTR [edx],0x46dab0
        and  DWORD PTR [edx+0x20],0xfffffffe
        lea  eax,[edx+0x68]
        mov  ecx,0x12
        push  edi
    loc_0041C043:
        and  DWORD PTR [eax],0xfffffffe
        add  eax,0x34
        dec  ecx
        jne loc_0041C043
        and  DWORD PTR [edx+0x420],0xfffffffe
        xor  eax,eax
        mov  ecx,0x109
        mov  edi,edx
        rep stosd
        mov  eax,DWORD PTR [edx+0x20]
        xor  ecx,ecx
        test  al,0x1
        pop  edi
        jne loc_0041C082
        or   eax,0x1
        mov  DWORD PTR [edx+0x14],ecx
        mov  DWORD PTR [edx+0x10],0xfff0bdc1
        mov  DWORD PTR [edx+0x18],ecx
        mov  DWORD PTR [edx+0x1c],0x476f78
        mov  DWORD PTR [edx+0x20],eax
    loc_0041C082:
        mov  DWORD PTR [edx+0x14],ecx
        mov  DWORD PTR [edx+0x18],ecx
        mov  DWORD PTR [edx+0x10],0xffffffff
        mov  eax,edx
        ret
    }
}
