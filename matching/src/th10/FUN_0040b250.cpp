// 0040B250: FUN_0040b250
// Original size: 336 bytes, actual code: 24 instructions
extern "C" void operator_new(void);

extern "C" __declspec(naked) void FUN_0040b250(void) {
    __asm {
        push  ebx
        push  esi
        push  edi
        push  0x2c
        mov  esi,edx
        mov  ebx,ecx
        call operator_new
        mov  DWORD PTR [ebx+0x358],eax
        mov  edi,eax
        mov  ecx,0xb
        rep movsd
        mov  ecx,DWORD PTR [eax]
        add  ebx,0x340
        mov  DWORD PTR [ebx],ecx
        mov  edx,DWORD PTR [eax+0x4]
        add  esp,0x4
        mov  DWORD PTR [ebx+0x4],edx
        mov  eax,DWORD PTR [eax+0x8]
        pop  edi
        mov  DWORD PTR [ebx+0x8],eax
        pop  esi
        xor  eax,eax
        pop  ebx
        ret
    }
}
