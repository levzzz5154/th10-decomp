// 004349E0: FUN_004349e0
// Original size: 64 bytes, actual code: 29 instructions

extern "C" __declspec(naked) void FUN_004349e0(void) {
    __asm {
        mov  cl,BYTE PTR [eax]
        cmp  cl,0xa
        je loc_004349FD
    loc_004349E7:
        cmp  cl,0xd
        je loc_004349FD
        mov  ecx,DWORD PTR [edx]
        test  ecx,ecx
        je loc_00434A1A
        inc  eax
        dec  ecx
        mov  DWORD PTR [edx],ecx
        mov  cl,BYTE PTR [eax]
        cmp  cl,0xa
        jne loc_004349E7
    loc_004349FD:
        cmp  DWORD PTR [edx],0x0
        je loc_00434A1A
    loc_00434A02:
        mov  cl,BYTE PTR [eax]
        cmp  cl,0xa
        je loc_00434A0E
        cmp  cl,0xd
        jne loc_00434A1A
    loc_00434A0E:
        mov  ecx,DWORD PTR [edx]
        test  ecx,ecx
        je loc_00434A1A
        inc  eax
        dec  ecx
        mov  DWORD PTR [edx],ecx
        jmp loc_00434A02
    loc_00434A1A:
        ret
    }
}
