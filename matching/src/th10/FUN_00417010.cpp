// 00417010: FUN_00417010
// Original size: 48 bytes, actual code: 20 instructions

extern "C" __declspec(naked) void FUN_00417010(void) {
    __asm {
        push  esi
        push  edi
        mov  edi,eax
        mov  cl,0x77
        mov  dl,0x7
        mov  esi,0x497d40
        nop
    loc_00417020:
        mov  al,BYTE PTR [edi]
        xor  al,cl
        mov  BYTE PTR [esi],al
        inc  esi
        add  cl,dl
        inc  edi
        add  dl,0x10
        test  al,al
        jne loc_00417020
        pop  edi
        mov  eax,0x497d40
        pop  esi
        ret
    }
}
