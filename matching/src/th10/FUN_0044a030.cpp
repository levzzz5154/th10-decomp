// 0044A030: FUN_0044a030
// Original size: 144 bytes, actual code: 15 instructions
extern "C" void FUN_00449b70(void);
extern "C" void FUN_00449ed0(void);

extern "C" __declspec(naked) void FUN_0044a030(void) {
    __asm {
        push  esi
        push  eax
        call FUN_00449ed0
        mov  ecx,DWORD PTR [esp+0x8]
        mov  edx,DWORD PTR ds:0x491be4
        mov  esi,eax
        mov  DWORD PTR [esi+0x20],ecx
        mov  ecx,DWORD PTR [esi+0x4]
        or   ecx,0x2
        push  edx
        mov  DWORD PTR [esi+0x4],ecx
        call FUN_00449b70
        mov  eax,esi
        pop  esi
        ret  0x4
    }
}
