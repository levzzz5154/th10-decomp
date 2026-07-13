// 0042B660: FUN_0042b660
// Original size: 144 bytes, actual code: 30 instructions
extern "C" void FUN_0042b430(void);
extern "C" void FUN_0042b4d0(void);
extern "C" void FUN_0042b570(void);
extern "C" void operator_new(void);
extern "C" void _free(void);

extern "C" __declspec(naked) void FUN_0042b660(void) {
    __asm {
        push  esi
        push  0xb884
        call operator_new
        add  esp,0x4
        test  eax,eax
        je loc_0042B67F
        push  ebx
        mov  ebx,eax
        call FUN_0042b430
        mov  esi,eax
        pop  ebx
        jmp loc_0042B681
    loc_0042B67F:
        xor  esi,esi
    loc_0042B681:
        mov  eax,esi
        call FUN_0042b4d0
        test  eax,eax
        je loc_0042B6A3
        test  esi,esi
        je loc_0042B69F
        push  esi
        call FUN_0042b570
        push  esi
        call _free
        add  esp,0x4
    loc_0042B69F:
        xor  eax,eax
        pop  esi
        ret
    loc_0042B6A3:
        mov  eax,esi
        pop  esi
        ret
    }
}
