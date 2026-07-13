// 0040C9A0: FUN_0040c9a0
// Original size: 48 bytes, actual code: 17 instructions
extern "C" void FUN_0040c9d0(void);
extern "C" void FUN_0041bb00(void);

extern "C" __declspec(naked) void FUN_0040c9a0(void) {
    __asm {
        push  esi
        mov  esi,eax
        mov  eax,DWORD PTR [edi]
        test  eax,eax
        jle loc_0040C9C2
        push  0x400ccccd
        push  0xbfc90fdb
        push  0xffffffff
        push  eax
        mov  eax,ds:0x477818
        mov  ecx,esi
        call FUN_0041bb00
    loc_0040C9C2:
        push  edi
        call FUN_0040c9d0
        mov  DWORD PTR [edi],0x0
        pop  esi
        ret
    }
}
