// 00422360: FUN_00422360
// Original size: 144 bytes, actual code: 27 instructions
extern "C" void FUN_004220e0(void);
extern "C" void FUN_00422150(void);
extern "C" void FUN_00422220(void);
extern "C" void operator_new(void);
extern "C" void _free(void);

extern "C" __declspec(naked) void FUN_00422360(void) {
    __asm {
        push  ebx
        push  0x2c8
        call operator_new
        add  esp,0x4
        test  eax,eax
        je loc_0042237D
        mov  edx,eax
        call FUN_004220e0
        mov  ebx,eax
        jmp loc_0042237F
    loc_0042237D:
        xor  ebx,ebx
    loc_0042237F:
        call FUN_00422150
        test  eax,eax
        je loc_0042239F
        test  ebx,ebx
        je loc_0042239B
        push  ebx
        call FUN_00422220
        push  ebx
        call _free
        add  esp,0x4
    loc_0042239B:
        xor  eax,eax
        pop  ebx
        ret
    loc_0042239F:
        mov  eax,ebx
        pop  ebx
        ret
    }
}
