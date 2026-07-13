// 00405B60: FUN_00405b60
// Original size: 128 bytes, actual code: 12 instructions

extern "C" __declspec(naked) void FUN_00405b60(void) {
    __asm {
        mov  edx,DWORD PTR [eax+0x58]
        add  edx,ecx
        mov  ecx,edx
        cmp  ecx,0x400
        mov  DWORD PTR [eax+0x58],edx
        jle loc_00405B7A
        mov  DWORD PTR [eax+0x58],0x400
        ret
    loc_00405B7A:
        cmp  ecx,0xfffffc00
        jge loc_00405B89
        mov  DWORD PTR [eax+0x58],0xfffffc00
    loc_00405B89:
        ret
    }
}
