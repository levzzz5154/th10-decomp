// 0044B6B0: FUN_0044b6b0
// Original size: 144 bytes, actual code: 37 instructions

extern "C" __declspec(naked) void FUN_0044b6b0(void) {
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
        mov  ds:0x474c38,eax
        jne loc_0044B734
        push  0x0
        push  0x0
        lea  ecx,[esp+0xc]
        push  ecx
        push  0x400
        call  DWORD PTR ds:0x46610c
        push  eax
        push  0x0
        push  0x1300
        call  DWORD PTR ds:0x466124
        mov  edx,DWORD PTR [esp+0x4]
        push  edx
        call  DWORD PTR ds:0x466128
        push  0x4922a4
        call  DWORD PTR ds:0x4660b4
        dec  BYTE PTR ds:0x49231e
        mov  eax,0xffffffff
        ret  0x4
    loc_0044B734:
        xor  eax,eax
        ret  0x4
    }
}
