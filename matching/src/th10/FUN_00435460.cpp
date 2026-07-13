// 00435460: FUN_00435460
// Original size: 288 bytes, actual code: 11 instructions

extern "C" __declspec(naked) void FUN_00435460(void) {
    __asm {
        push  esi
        mov  esi,ecx
        mov  eax,DWORD PTR [esi+0x4]
        cmp  eax,0xffffffff
        je loc_00435480
        push  eax
        call  DWORD PTR ds:0x4660cc
        mov  DWORD PTR [esi+0x4],0xffffffff
        mov  DWORD PTR [esi+0x8],0x0
    loc_00435480:
        pop  esi
        ret
    }
}
