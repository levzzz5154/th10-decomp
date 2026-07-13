// 0044B4D0: FUN_0044b4d0
// Original size: 112 bytes, actual code: 28 instructions

extern "C" __declspec(naked) void FUN_0044b4d0(void) {
    __asm {
        push  0x4922a4
        call  DWORD PTR ds:0x4660b0
        mov  al,ds:0x49231e
        push  0x0
        push  0x8000080
        push  0x3
        push  0x0
        inc  al
        push  0x1
        mov  ds:0x49231e,al
        mov  eax,DWORD PTR [esp+0x18]
        push  0x80000000
        push  eax
        call  DWORD PTR ds:0x4660c4
        cmp  eax,0xffffffff
        je loc_0044B529
        push  eax
        call  DWORD PTR ds:0x4660cc
        push  0x4922a4
        call  DWORD PTR ds:0x4660b4
        dec  BYTE PTR ds:0x49231e
        mov  eax,0x1
        ret  0x4
    loc_0044B529:
        push  0x4922a4
        call  DWORD PTR ds:0x4660b4
        dec  BYTE PTR ds:0x49231e
        xor  eax,eax
        ret  0x4
    }
}
