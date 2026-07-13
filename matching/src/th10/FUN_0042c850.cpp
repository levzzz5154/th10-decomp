// 0042C850: FUN_0042c850
// Original size: 112 bytes, actual code: 22 instructions

extern "C" __declspec(naked) void FUN_0042c850(void) {
    __asm {
        mov  cl,BYTE PTR [eax+0x1d888]
        test  cl,cl
        jne loc_0042C88F
        mov  cl,BYTE PTR [eax+0x1d889]
        test  cl,cl
        jne loc_0042C88F
        mov  cl,BYTE PTR [eax+0x1d88a]
        test  cl,cl
        jne loc_0042C88F
        mov  cl,BYTE PTR [eax+0x1d88b]
        test  cl,cl
        jne loc_0042C88F
        mov  cl,BYTE PTR [eax+0x1d88c]
        test  cl,cl
        jne loc_0042C88F
        mov  cl,BYTE PTR [eax+0x1d88d]
        test  cl,cl
        jne loc_0042C88F
        xor  eax,eax
        ret
    loc_0042C88F:
        mov  eax,0x1
        ret
    }
}
