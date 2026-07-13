// 0041C290: FUN_0041c290
// Original size: 160 bytes, actual code: 37 instructions
extern "C" void FUN_0041c030(void);
extern "C" void FUN_0041c120(void);
extern "C" void FUN_0041c1c0(void);
extern "C" void operator_new(void);
extern "C" void _free(void);

extern "C" __declspec(naked) void FUN_0041c290(void) {
    __asm {
        push  esi
        push  0x45c
        call operator_new
        mov  esi,eax
        add  esp,0x4
        test  esi,esi
        je loc_0041C2C1
        push  edi
        lea  edx,[esi+0x10]
        call FUN_0041c030
        mov  ecx,0x117
        xor  eax,eax
        mov  edi,esi
        rep stosd
        mov  DWORD PTR ds:0x47781c,esi
        pop  edi
        jmp loc_0041C2C3
    loc_0041C2C1:
        xor  esi,esi
    loc_0041C2C3:
        push  ebx
        mov  ebx,esi
        call FUN_0041c120
        test  eax,eax
        pop  ebx
        je loc_0041C2E7
        test  esi,esi
        je loc_0041C2E3
        push  esi
        call FUN_0041c1c0
        push  esi
        call _free
        add  esp,0x4
    loc_0041C2E3:
        xor  eax,eax
        pop  esi
        ret
    loc_0041C2E7:
        mov  eax,esi
        pop  esi
        ret
    }
}
