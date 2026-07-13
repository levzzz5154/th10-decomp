// 004491C0: FUN_004491c0
// Original size: 80 bytes, actual code: 31 instructions

extern "C" __declspec(naked) void FUN_004491c0(void) {
    __asm {
        mov  ecx,DWORD PTR [esp+0x4]
        test  ecx,ecx
        jne loc_004491CD
        xor  eax,eax
        ret  0x4
    loc_004491CD:
        mov  eax,DWORD PTR [edx+0x72dad4]
        test  eax,eax
        push  esi
        je loc_004491E5
    loc_004491D8:
        mov  esi,DWORD PTR [eax]
        cmp  DWORD PTR [esi],ecx
        je loc_00449203
        mov  eax,DWORD PTR [eax+0x4]
        test  eax,eax
        jne loc_004491D8
    loc_004491E5:
        mov  eax,DWORD PTR [edx+0x72dadc]
        test  eax,eax
        je loc_004491FD
        nop
    loc_004491F0:
        mov  edx,DWORD PTR [eax]
        cmp  DWORD PTR [edx],ecx
        je loc_00449203
        mov  eax,DWORD PTR [eax+0x4]
        test  eax,eax
        jne loc_004491F0
    loc_004491FD:
        xor  eax,eax
        pop  esi
        ret  0x4
    loc_00449203:
        mov  eax,DWORD PTR [eax]
        pop  esi
        ret  0x4
    }
}
