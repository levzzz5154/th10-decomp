// 0041F8D0: FUN_0041f8d0
// Original size: 96 bytes, actual code: 22 instructions
extern "C" void FUN_00447280(void);
extern "C" void FUN_0044b810(void);

extern "C" __declspec(naked) void FUN_0041f8d0(void) {
    __asm {
        mov  edx,DWORD PTR ds:0x491c10
        push  0x46d254
        mov  ecx,0x6
        call FUN_00447280
        test  eax,eax
        jne loc_0041F8F0
        push  0x46cb68
        jmp loc_0041F90E
    loc_0041F8F0:
        mov  edx,DWORD PTR ds:0x491c10
        push  0x46cd88
        mov  ecx,0x7
        call FUN_00447280
        test  eax,eax
        jne loc_0041F91F
        push  0x46cd54
    loc_0041F90E:
        mov  ecx,0x474f70
        call FUN_0044b810
        add  esp,0x4
        or   eax,0xffffffff
        ret
    loc_0041F91F:
        xor  eax,eax
        ret
    }
}
