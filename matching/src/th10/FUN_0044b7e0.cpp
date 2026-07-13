// 0044B7E0: FUN_0044b7e0
// Original size: 48 bytes, actual code: 10 instructions

extern "C" __declspec(naked) void FUN_0044b7e0(void) {
    __asm {
        mov  eax,ds:0x474c38
        cmp  eax,0xffffffff
        je loc_0044B802
        push  eax
        call  DWORD PTR ds:0x4660cc
        push  0x4922a4
        call  DWORD PTR ds:0x4660b4
        dec  BYTE PTR ds:0x49231e
    loc_0044B802:
        xor  eax,eax
        ret
    }
}
