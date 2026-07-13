// 00422C30: FUN_00422c30
// Original size: 80 bytes, actual code: 17 instructions
extern "C" void FUN_0043e460(void);
extern "C" void FUN_004492a0(void);

extern "C" __declspec(naked) void FUN_00422c30(void) {
    __asm {
        mov  eax,ds:0x477810
        mov  ecx,DWORD PTR [eax+0x58]
        and  ecx,0xffffffef
        push  0x0
        mov  DWORD PTR [eax+0x58],ecx
        push  0x7
        mov  edx,0x46e0b8
        mov  eax,0x492590
        call FUN_0043e460
        mov  eax,DWORD PTR [esi+0x1dc]
        mov  edx,DWORD PTR ds:0x491c10
        push  eax
        call FUN_004492a0
        mov  DWORD PTR [esi+0x1dc],0x0
        mov  ecx,DWORD PTR [esi+0x2c0]
        mov  DWORD PTR ds:0x476f78,ecx
        ret
    }
}
