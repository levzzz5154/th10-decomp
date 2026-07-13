// 00435340: FUN_00435340
// Original size: 48 bytes, actual code: 13 instructions

extern "C" __declspec(naked) void FUN_00435340(void) {
    __asm {
        push  esi
        mov  esi,ecx
        mov  eax,DWORD PTR [esi+0x4]
        cmp  eax,0xffffffff
        mov  DWORD PTR [esi],0x46f230
        je loc_00435366
        push  eax
        call  DWORD PTR ds:0x4660cc
        mov  DWORD PTR [esi+0x4],0xffffffff
        mov  DWORD PTR [esi+0x8],0x0
    loc_00435366:
        mov  DWORD PTR [esi],0x46f210
        pop  esi
        ret
    }
}
