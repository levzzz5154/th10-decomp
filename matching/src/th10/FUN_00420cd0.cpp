// 00420CD0: FUN_00420cd0
// Original size: 256 bytes, actual code: 17 instructions
extern "C" void FUN_00442f50(void);

extern "C" __declspec(naked) void FUN_00420cd0(void) {
    __asm {
        mov  eax,DWORD PTR [edi+0x750]
        test  eax,eax
        je loc_00420D02
        push  esi
        mov  esi,DWORD PTR ds:0x491c10
        call FUN_00442f50
        mov  eax,DWORD PTR [edi+0x8]
        push  0x0
        push  0x1c
        mov  DWORD PTR [edi+0x750],0x0
        mov  ecx,DWORD PTR [eax]
        push  eax
        call  DWORD PTR [ecx+0xe4]
        pop  esi
        ret
    loc_00420D02:
        xor  eax,eax
        ret
    }
}
