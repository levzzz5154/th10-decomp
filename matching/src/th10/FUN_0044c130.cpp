// 0044C130: FUN_0044c130
// Original size: 32 bytes, actual code: 8 instructions
extern "C" void FUN_0044c150(void);

extern "C" __declspec(naked) void FUN_0044c130(void) {
    __asm {
        push  esi
        mov  esi,ecx
        mov  DWORD PTR [ecx],0x4703e4
        call FUN_0044c150
        pop  esi
        ret
        mov  DWORD PTR [eax+0xc],0x1
        ret
    }
}
