// 00419090: FUN_00419090
// Original size: 144 bytes, actual code: 27 instructions
extern "C" void FUN_00418d40(void);
extern "C" void FUN_00418e30(void);
extern "C" void FUN_00418ee0(void);
extern "C" void operator_new(void);
extern "C" void _free(void);

extern "C" __declspec(naked) void FUN_00419090(void) {
    __asm {
        push  ebx
        push  0x1a8
        call operator_new
        add  esp,0x4
        test  eax,eax
        je loc_004190AD
        mov  edx,eax
        call FUN_00418d40
        mov  ebx,eax
        jmp loc_004190AF
    loc_004190AD:
        xor  ebx,ebx
    loc_004190AF:
        call FUN_00418e30
        test  eax,eax
        je loc_004190CF
        test  ebx,ebx
        je loc_004190CB
        push  ebx
        call FUN_00418ee0
        push  ebx
        call _free
        add  esp,0x4
    loc_004190CB:
        xor  eax,eax
        pop  ebx
        ret
    loc_004190CF:
        mov  eax,ebx
        pop  ebx
        ret
    }
}
