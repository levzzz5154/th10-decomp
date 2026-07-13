// 00401440: FUN_00401440
// Original size: 224 bytes, actual code: 28 instructions
extern "C" void FUN_00401000(void);
extern "C" void FUN_00401110(void);
extern "C" void FUN_00401260(void);
extern "C" void operator_new(void);
extern "C" void _free(void);

extern "C" __declspec(naked) void FUN_00401440(void) {
    __asm {
        push  esi
        push  0x89ac
        call operator_new
        add  esp,0x4
        test  eax,eax
        je loc_0040145D
        mov  esi,eax
        call FUN_00401000
        mov  esi,eax
        jmp loc_0040145F
    loc_0040145D:
        xor  esi,esi
    loc_0040145F:
        mov  eax,esi
        call FUN_00401110
        test  eax,eax
        je loc_00401481
        test  esi,esi
        je loc_0040147D
        push  esi
        call FUN_00401260
        push  esi
        call _free
        add  esp,0x4
    loc_0040147D:
        xor  eax,eax
        pop  esi
        ret
    loc_00401481:
        mov  eax,esi
        pop  esi
        ret
    }
}
