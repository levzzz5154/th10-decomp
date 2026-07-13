// 0044B740: FUN_0044b740
// Original size: 80 bytes, actual code: 28 instructions

extern "C" __declspec(naked) void FUN_0044b740(void) {
    __asm {
        push  ecx
        mov  eax,ds:0x474c38
        cmp  eax,0xffffffff
        jne loc_0044B74F
        or   eax,eax
        pop  ecx
        ret
    loc_0044B74F:
        push  0x0
        lea  ecx,[esp+0x4]
        push  ecx
        push  esi
        push  edx
        push  eax
        call  DWORD PTR ds:0x4660d4
        cmp  esi,DWORD PTR [esp]
        je loc_0044B788
        mov  eax,ds:0x474c38
        push  eax
        call  DWORD PTR ds:0x4660cc
        push  0x4922a4
        call  DWORD PTR ds:0x4660b4
        dec  BYTE PTR ds:0x49231e
        mov  eax,0xfffffffe
        pop  ecx
        ret
    loc_0044B788:
        xor  eax,eax
        pop  ecx
        ret
    }
}
