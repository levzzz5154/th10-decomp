// 004091C0: FUN_004091c0
// Original size: 112 bytes, actual code: 33 instructions
extern "C" void FUN_00408d60(void);
extern "C" void FUN_004451c0(void);

extern "C" __declspec(naked) void FUN_004091c0(void) {
    __asm {
        test  BYTE PTR [ebx+0x378c],0x1
        je loc_00409219
        push  esi
        push  edi
        lea  esi,[ebx+0x778]
        mov  edi,0x8
        jmp loc_004091E0
        nop
        nop
    loc_004091E0:
        mov  ecx,DWORD PTR ds:0x491c10
        mov  eax,esi
        call FUN_004451c0
        add  esi,0x3ac
        dec  edi
        jne loc_004091E0
        lea  esi,[ebx+0x24d8]
        mov  edi,0x5
    loc_00409201:
        mov  ecx,DWORD PTR ds:0x491c10
        mov  eax,esi
        call FUN_004451c0
        add  esi,0x3ac
        dec  edi
        jne loc_00409201
        pop  edi
        pop  esi
    loc_00409219:
        mov  eax,0x1
        ret
    }
}
