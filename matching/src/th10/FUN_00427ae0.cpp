// 00427AE0: FUN_00427ae0
// Original size: 112 bytes, actual code: 33 instructions
extern "C" void FUN_00449470(void);

extern "C" __declspec(naked) void FUN_00427ae0(void) {
    __asm {
        mov  eax,ds:0x477834
        push  ebx
        mov  ebx,DWORD PTR [eax+0x4474]
        test  ebx,ebx
        mov  eax,DWORD PTR [edi+0x84]
        push  esi
        jne loc_00427B1D
        test  eax,eax
        je loc_00427B08
        lea  eax,[edi+0x68]
        mov  esi,0x6
        call FUN_00449470
    loc_00427B08:
        mov  ecx,DWORD PTR [edi+0x3c]
        mov  DWORD PTR [edi+0x4c],ecx
        mov  edx,DWORD PTR [edi+0x40]
        mov  DWORD PTR [edi+0x50],edx
        pop  esi
        mov  DWORD PTR [edi+0x84],ebx
        pop  ebx
        ret
    loc_00427B1D:
        test  eax,eax
        jne loc_00427B2E
        lea  eax,[edi+0x68]
        mov  esi,0x3
        call FUN_00449470
    loc_00427B2E:
        mov  eax,DWORD PTR [edi+0x4c]
        mov  DWORD PTR [edi+0x34],eax
        mov  ecx,DWORD PTR [edi+0x50]
        mov  DWORD PTR [edi+0x38],ecx
        pop  esi
        mov  DWORD PTR [edi+0x84],ebx
        pop  ebx
        ret
    }
}
