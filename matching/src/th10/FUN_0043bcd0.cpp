// 0043BCD0: FUN_0043bcd0
// Original size: 208 bytes, actual code: 20 instructions
extern "C" void FUN_0043bc40(void);
extern "C" void FUN_00442f50(void);

extern "C" __declspec(naked) void FUN_0043bcd0(void) {
    __asm {
        push  esi
        mov  esi,DWORD PTR ds:0x491c10
        test  esi,esi
        je loc_0043BCE0
        call FUN_00442f50
    loc_0043BCE0:
        mov  eax,ds:0x491c30
        push  0x491cf4
        mov  DWORD PTR ds:0x491cf4,0x0
        mov  DWORD PTR ds:0x491cf8,0x0
        mov  DWORD PTR ds:0x491cfc,0x280
        mov  DWORD PTR ds:0x491d00,0x1e0
        mov  DWORD PTR ds:0x491d04,0x0
        mov  DWORD PTR ds:0x491d08,0x3f800000
        mov  ecx,DWORD PTR [eax]
        push  eax
        call  DWORD PTR [ecx+0xbc]
        mov  esi,DWORD PTR [esp+0x8]
        call FUN_0043bc40
        pop  esi
        ret  0x4
    }
}
