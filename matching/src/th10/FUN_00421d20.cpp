// 00421D20: FUN_00421d20
// Original size: 224 bytes, actual code: 8 instructions

extern "C" __declspec(naked) void FUN_00421d20(void) {
    __asm {
        mov  eax,DWORD PTR [esi+0xc]
        test  eax,eax
        je loc_00421D34
        mov  ecx,DWORD PTR [eax]
        push  eax
        call  DWORD PTR [ecx+0x8]
        mov  DWORD PTR [esi+0xc],0x0
    loc_00421D34:
        ret
    }
}
