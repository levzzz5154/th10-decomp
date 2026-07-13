// 00434A20: FUN_00434a20
// Original size: 96 bytes, actual code: 43 instructions

extern "C" __declspec(naked) void FUN_00434a20(void) {
    __asm {
        cmp  BYTE PTR [ecx],0xa
        mov  eax,ecx
        je loc_00434A3B
    loc_00434A27:
        cmp  BYTE PTR [eax],0xd
        je loc_00434A3B
        mov  edx,DWORD PTR [edi]
        test  edx,edx
        je loc_00434A79
        inc  eax
        dec  edx
        mov  DWORD PTR [edi],edx
        cmp  BYTE PTR [eax],0xa
        jne loc_00434A27
    loc_00434A3B:
        cmp  DWORD PTR [edi],0x0
        je loc_00434A79
        push  esi
        mov  esi,DWORD PTR [esp+0x8]
        mov  BYTE PTR [eax],0x0
        sub  esi,ecx
        lea  ebx,[ebx+0x0]
    loc_00434A50:
        mov  dl,BYTE PTR [ecx]
        mov  BYTE PTR [esi+ecx*1],dl
        inc  ecx
        test  dl,dl
        jne loc_00434A50
        mov  ecx,DWORD PTR [edi]
        inc  eax
        dec  ecx
        mov  DWORD PTR [edi],ecx
        mov  edx,ecx
        pop  esi
    loc_00434A63:
        mov  cl,BYTE PTR [eax]
        cmp  cl,0xa
        je loc_00434A6F
        cmp  cl,0xd
        jne loc_00434A79
    loc_00434A6F:
        test  edx,edx
        je loc_00434A79
        inc  eax
        dec  edx
        mov  DWORD PTR [edi],edx
        jmp loc_00434A63
    loc_00434A79:
        ret  0x4
    }
}
