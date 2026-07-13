// 004392E0: FUN_004392e0
// Original size: 176 bytes, actual code: 38 instructions

extern "C" __declspec(naked) void FUN_004392e0(void) {
    __asm {
        push  esi
        mov  esi,DWORD PTR ds:0x466258
        push  0x0
        push  0x49251c
        push  0x0
        push  0x10
        call  esi
        push  0x0
        push  0x492520
        push  0x0
        push  0x53
        call  esi
        push  0x0
        push  0x492524
        push  0x0
        push  0x54
        call  esi
        push  0x2
        push  0x0
        push  0x0
        push  0x11
        call  esi
        push  0x2
        push  0x0
        push  0x0
        push  0x55
        call  esi
        push  0x2
        push  0x0
        push  0x0
        push  0x56
        call  esi
        push  0x492508
        call  DWORD PTR ds:0x466114
        push  0x492510
        call  DWORD PTR ds:0x4660fc
        pop  esi
        ret
    }
}
