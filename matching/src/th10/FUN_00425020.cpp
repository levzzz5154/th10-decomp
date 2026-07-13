// 00425020: FUN_00425020
// Original size: 144 bytes, actual code: 29 instructions
extern "C" void FUN_004246c0(void);
extern "C" void FUN_004247f0(void);
extern "C" void FUN_00424ed0(void);
extern "C" void operator_new(void);
extern "C" void _free(void);

extern "C" __declspec(naked) void FUN_00425020(void) {
    __asm {
        push  ebx
        push  0x4478
        call operator_new
        add  esp,0x4
        test  eax,eax
        je loc_0042503F
        push  esi
        mov  esi,eax
        call FUN_004246c0
        mov  ebx,eax
        pop  esi
        jmp loc_00425041
    loc_0042503F:
        xor  ebx,ebx
    loc_00425041:
        call FUN_004247f0
        test  eax,eax
        je loc_00425061
        test  ebx,ebx
        je loc_0042505D
        push  ebx
        call FUN_00424ed0
        push  ebx
        call _free
        add  esp,0x4
    loc_0042505D:
        xor  eax,eax
        pop  ebx
        ret
    loc_00425061:
        mov  eax,ebx
        pop  ebx
        ret
    }
}
