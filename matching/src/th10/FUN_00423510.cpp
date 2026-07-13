// 00423510: FUN_00423510
// Original size: 96 bytes, actual code: 21 instructions
extern "C" void FUN_00409e50(void);

extern "C" __declspec(naked) void FUN_00423510(void) {
    __asm {
        mov  DWORD PTR [esi+0x4],0xd
        mov  eax,DWORD PTR [esi+0x20]
        xor  ecx,ecx
        test  al,0x1
        jne loc_0042353A
        or   eax,0x1
        mov  DWORD PTR [esi+0x14],ecx
        mov  DWORD PTR [esi+0x10],0xfff0bdc1
        mov  DWORD PTR [esi+0x18],ecx
        mov  DWORD PTR [esi+0x1c],0x476f78
        mov  DWORD PTR [esi+0x20],eax
    loc_0042353A:
        lea  eax,[esi+0x1d8]
        mov  DWORD PTR [esi+0x14],ecx
        mov  DWORD PTR [esi+0x18],ecx
        mov  DWORD PTR [esi+0x10],0xffffffff
        call FUN_00409e50
        lea  eax,[esi+0x1d4]
        call FUN_00409e50
        mov  eax,DWORD PTR [esi+0x2c0]
        mov  ds:0x476f78,eax
        ret
    }
}
